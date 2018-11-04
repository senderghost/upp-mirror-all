#include "Painter.h"
#include "Fillers.h"

namespace Upp {

#define LLOG(x)   // DLOG(x)
#define LDUMP(x)  // DDUMP(x)

void BufferPainter::ClearOp(const RGBA& color)
{
	UPP::Fill(backend.pixels, color, backend.size.cx * backend.size.cy);
}

BufferPainter& BufferPainter::Co()
{
	int bandcy = min(max(size.cy / CPU_Cores(), 8), size.cy); // TODO
//	bandcy = size.cy;
	for(int y = 0; y < size.cy; y += bandcy) {
		CoBand& b = co_band.Add();
		b.backend.Init(backend.pixels + size.cx * y, Size(size.cx, min(bandcy, size.cy - y)), backend.mode, y);
		b.backend.dopreclip = 1;
		dopreclip = 1;
	}
	return *this;
}

Buffer<ClippingLine> BufferPainter::RenderPath(double width, SpanSource *ss, const RGBA& color)
{
	PAINTER_TIMING("RenderPath");
	if(width == FILL)
		Close();

	if(width == 0 || !ss && color.a == 0 && width >= FILL) {
		current = Null;
		Buffer<ClippingLine> newclip;
		return newclip;
	}
	
	
	if(co_band.GetCount() && width != ONPATH) {
		Mutex::Lock __(co_mutex);
		while(co_queue.GetCount() && co_queue.Head().bands == 0) {
			co_queue.DropHead();
			co_first++;
			LLOG("Removing queue head, head now starts at: " << co_first);
		}
		LLOG("Adding to queue: " << co_queue.GetCount() + co_first << ", queue size: " << co_queue.GetCount());
		CoEntry& h = co_queue.AddTail();
		h.path = path;
		h.pf = *this;
		h.width = width;
		h.color = color;
		h.bands = co_band.GetCount();
		while(co_processors < CPU_Cores()) {
			co_processors++;
			LLOG("Schedule, now scheduled: " << co_processors);
			cw & [=] {
				Mutex::Lock __(co_mutex);
			next:
				for(CoBand& b : co_band)
					if(!b.owned && b.at - co_first < co_queue.GetCount()) {
						b.owned = true;
						LLOG("Starting band [" << b.backend.rasterizer.GetOffsetY() << "]");
						while(b.at - co_first < co_queue.GetCount()) {
							CoEntry& e = co_queue[b.at++ - co_first];
							co_mutex.Leave();
							b.backend.RenderPath(e.width, NULL, e.color, e.pf, ~e.path, e.path.End(), NULL);
							co_mutex.Enter();
							e.bands--;
							LLOG("Done " << b.at << "[" << b.backend.rasterizer.GetOffsetY() << "], remaining: " << e.bands);
						}
						b.owned = false;
						LLOG("Leaving band [" << b.backend.rasterizer.GetOffsetY() << "]");
						goto next;
					}
				co_processors--;
				LLOG("Leaving processor, now scheduled: " << co_processors);
			};
		}
	}
	else {
		struct OnPathTarget : LinearPathConsumer {
			Vector<BufferPainter::PathLine> path;
			Pointf pos;
			double len;
			
			virtual void Move(const Pointf& p) {
				BufferPainter::PathLine& t = path.Add();
				t.len = 0;
				pos = t.p = p;
			}
			virtual void Line(const Pointf& p) {
				BufferPainter::PathLine& t = path.Add();
				len += (t.len = Distance(pos, p));
				pos = t.p = p;
			}
			
			OnPathTarget() { len = 0; pos = Pointf(0, 0); }
		}
		onpathtarget;
	
		backend.dopreclip = dopreclip;
		backend.RenderPath(width, ss, color, *this, ~path, path.End(),
		                   width == ONPATH ? &onpathtarget : alt);

		if(width == ONPATH) {
			onpath = pick(onpathtarget.path);
			pathlen = onpathtarget.len;
		}
	}

	current = Null;

	Buffer<ClippingLine> newclip;
	return newclip;
}

void BufferPainter::FillOp(const RGBA& color)
{
	RenderPath(FILL, NULL, color);
}

void BufferPainter::StrokeOp(double width, const RGBA& color)
{
	RenderPath(width, NULL, color);
}

void BufferPainter::ClipOp()
{
	Finish();
#ifdef PAINTER_FULL
	Buffer<ClippingLine> newclip = RenderPath(CLIP, NULL, RGBAZero());
	if(attr.hasclip)
		clip.Top() = pick(newclip);
	else {
		clip.Add() = pick(newclip);
		attr.hasclip = true;
		attr.cliplevel = clip.GetCount();
	}
#endif
}

#if 0
Image CoPaint(Size sz, Event<BufferPainter&> paint, int bands)
{
	ImageBuffer ib(sz);
	int bandcy = sz.cy / bands;
	CoWork co;
	for(int y = 0; y < sz.cy; y += bandcy)
		co & [=, &ib] {
			BufferPainter sw(~ib + y * sz.cx, Size(sz.cx, min(bandcy, sz.cy - y)), MODE_ANTIALIASED, y);
			sw.PreClip();
			paint(sw);
		};
	co.Finish();
	return ib;
}
#endif

Image CoPaint(Size sz, Event<BufferPainter&> paint, int bands)
{
	ImageBuffer ib(sz);
	int bandcy = sz.cy / bands;
	CoWork co;
	co * [&] {
		for(;;) {
			int y = bandcy * co.Next();
			if(y > sz.cy)
				break;
			BufferPainter sw(~ib + y * sz.cx, Size(sz.cx, min(bandcy, sz.cy - y)), MODE_ANTIALIASED, y);
			sw.PreClip();
			paint(sw);
		}
	};
	co.Finish();
	return ib;
}

}
