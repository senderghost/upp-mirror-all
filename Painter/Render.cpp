#include "Painter.h"
#include "Fillers.h"

namespace Upp {

#define LLOG(x) // DLOG(x)

void PainterTarget::Fill(double width, SpanSource *ss, const RGBA& color) {}

void BufferPainter::ClearOp(const RGBA& color)
{
	UPP::Fill(~ib, color, ib.GetLength());
}

Buffer<ClippingLine> BufferPainter::RenderPath(double width, Event<One<SpanSource>&> ss, const RGBA& color)
{
	PAINTER_TIMING("RenderPath");
	Buffer<ClippingLine> newclip;
	if(width == 0) {
		current = Null;
		return newclip;
	}

	if(width < 0)
		Close();
	
	if(co && width != CLIP && width != ONPATH && !ss && !alt && mode == MODE_ANTIALIASED) {
		for(const String& p : path) {
			while(jobcount >= cojob.GetCount())
				cojob.Add().rasterizer.Create(ib.GetWidth(), ib.GetHeight(), false);
			CoJob& job = cojob[jobcount++];
			job.path = p;
			job.attr = pathattr;
			job.width = width;
			job.color = color;
			job.ischar = ischar;
			job.path_min = path_min;
			job.path_max = path_max;
			current = Null;
			if(jobcount >= 64)
				Finish();
		}
		return newclip;
	}
	
	Finish();
	
	rasterizer.Reset();

	PathJob j(rasterizer, width, ischar, dopreclip, path_min, path_max, pathattr);
	
	bool doclip = width == CLIP;
	auto fill = [&](CoWork *co) {
		int opacity = int(256 * pathattr.opacity);
		Rasterizer::Filler *rg;
		SpanFiller          span_filler;
		SolidFiller         solid_filler;
		SubpixelFiller      subpixel_filler;
		ClipFiller          clip_filler(render_cx);
		NoAAFillerFilter    noaa_filler;
		MaskFillerFilter    mf;
		subpixel_filler.sbuffer = subpixel;
		subpixel_filler.invert = pathattr.invert;
		Buffer<RGBA>        co_span;
		One<SpanSource>     rss;
		
		if(doclip) {
			rg = &clip_filler;
			newclip.Alloc(ib.GetHeight());
		}
		else
		if(ss) {
			ss(rss);
			RGBA           *lspan;
			if(co) {
				co_span.Alloc((subpixel ? 3 : 1) * ib.GetWidth() + 3);
				lspan = co_span;
			}
			else {
				if(!span)
					span.Alloc((subpixel ? 3 : 1) * ib.GetWidth() + 3);
				lspan = span;
			}
			if(subpixel) {
				subpixel_filler.ss = ~rss;
				subpixel_filler.buffer = lspan;
				subpixel_filler.alpha = opacity;
				rg = &subpixel_filler;
			}
			else {
				span_filler.ss = ~rss;
				span_filler.buffer = lspan;
				span_filler.alpha = opacity;
				rg = &span_filler;
			}
		}
		else {
			if(subpixel) {
				subpixel_filler.color = Mul8(color, opacity);
				subpixel_filler.ss = NULL;
				rg = &subpixel_filler;
			}
			else {
				solid_filler.c = Mul8(color, opacity);
				solid_filler.invert = pathattr.invert;
				rg = &solid_filler;
			}
		}
		if(mode == MODE_NOAA) {
			noaa_filler.Set(rg);
			rg = &noaa_filler;
		}
		if(width != ONPATH) {
			if(alt)
				alt->Fill(width, ~rss, color);
			else {
				PAINTER_TIMING("Fill");
				int ii = 0;
				for(;;) {
					int y = (co ? co->Next() : ii++) + rasterizer.MinY();
					if(y > rasterizer.MaxY())
						break;
					solid_filler.t = subpixel_filler.t = span_filler.t = ib[y];
					subpixel_filler.end = subpixel_filler.t + ib.GetWidth();
					span_filler.y = subpixel_filler.y = y;
					Rasterizer::Filler *rf = rg;
					if(clip.GetCount()) {
						const ClippingLine& s = clip.Top()[y];
						if(s.IsEmpty()) goto empty;
						if(!s.IsFull()) {
							mf.Set(rg, s);
							rf = &mf;
						}
					}
					if(doclip)
						clip_filler.Clear();
					rasterizer.Render(y, *rf, j.evenodd);
					if(doclip)
						clip_filler.Finish(newclip[y]);
				empty:;
				}
			}
		}
	};
	PAINTER_TIMING("RenderPath2");
	for(const auto& p : path) {
		RenderPathSegments(j.g, p, j.regular ? &pathattr : NULL, j.tolerance);
		int n = rasterizer.MaxY() - rasterizer.MinY();
		if(n >= 0) {
			if(co && !doclip && !alt && n > 6) {
				CoWork co;
				co * [&] { fill(&co); };
			}
			else
				fill(NULL);
			rasterizer.Reset();
		}
	}
	current = Null;
	if(width == ONPATH) {
		onpath = pick(j.onpathtarget.path);
		pathlen = j.onpathtarget.len;
	}
	return newclip;
}

void BufferPainter::FillOp(const RGBA& color)
{
	RenderPath(FILL, Null, color);
}

void BufferPainter::StrokeOp(double width, const RGBA& color)
{
	RenderPath(width, Null, color);
}

void BufferPainter::ClipOp()
{
	Finish();
	Buffer<ClippingLine> newclip = RenderPath(CLIP, Null, RGBAZero());
	if(attr.hasclip)
		clip.Top() = pick(newclip);
	else {
		clip.Add() = pick(newclip);
		attr.hasclip = true;
		attr.cliplevel = clip.GetCount();
	}
}

}
