#include "Painter.h"
#include "Fillers.h"

namespace Upp {

#define LLOG(x)   // DLOG(x)
#define LDUMP(x)  // DDUMP(x)

void PainterTarget::Fill(double width, SpanSource *ss, const RGBA& color) {}

void BufferPainter::ClearOp(const RGBA& color)
{
	UPP::Fill(~ib, color, ib.GetLength());
}

BufferPainter::PathJob::PathJob(Rasterizer& rasterizer, double width, bool ischar, int dopreclip,
                                Pointf path_min, Pointf path_max, const Attr& attr)
:	trans(attr.mtx)
{
	evenodd = attr.evenodd;
	regular = attr.mtx.IsRegular() && width < 0 && !ischar;

	g = &rasterizer;
	Rectf preclip = Null;
	preclipped = false;
	if((dopreclip == 1 || dopreclip == 2 && attr.dash) && width != ONPATH) {
		preclip = rasterizer.GetClip();
		Xform2D imx = Inverse(attr.mtx);
		Pointf tl, br, a;
		tl = br = imx.Transform(preclip.TopLeft());
		a = imx.Transform(preclip.TopRight());
		tl = min(a, tl);
		br = max(a, br);
		a = imx.Transform(preclip.BottomLeft());
		tl = min(a, tl);
		br = max(a, br);
		a = imx.Transform(preclip.BottomRight());
		tl = min(a, tl);
		br = max(a, br);
		preclip = Rectf(tl, br);
		
		if(!preclip.Intersects(
				Rectf(path_min, path_max).Inflated(max(width, 0.0) * (1 + attr.miter_limit)))) {
			LLOG("Preclipped " << preclip << ", min " << path_min << ", max " << path_max);
			preclipped = true;
			return;
		}
	}
	if(regular)
		tolerance = 0.3;
	else {
		trans.target = g;
		g = &trans;
		tolerance = 0.3 / attr.mtx.GetScale();
	}

	if(width == ONPATH) {
		g = &onpathtarget;
		regular = false;
	}
	else
	if(width > 0) {
		stroker.Init(width, attr.miter_limit, tolerance, attr.cap, attr.join, preclip);
		stroker.target = g;
		if(attr.dash) {
			dasher.Init(attr.dash, attr.dash_start);
			dasher.target = &stroker;
			g = &dasher;
		}
		else
			g = &stroker;
		evenodd = false;
	}
}

void BufferPainter::RenderPathSegments(LinearPathConsumer *g, const Vector<byte>& path,
                                       const Attr *attr, double tolerance)
{
	Pointf pos = Pointf(0, 0);
	const byte *data = path.begin();
	const byte *end = path.end();
	while(data < end) {
		const LinearData *d = (LinearData *)data;
		switch(d->type) {
		case MOVE: {
			g->Move(pos = attr ? attr->mtx.Transform(d->p) : d->p);
			data += sizeof(LinearData);
			break;
		}
		case LINE: {
			PAINTER_TIMING("LINE");
			g->Line(pos = attr ? attr->mtx.Transform(d->p) : d->p);
			data += sizeof(LinearData);
			break;
		}
		case QUADRATIC: {
			PAINTER_TIMING("QUADRATIC");
			const QuadraticData *d = (QuadraticData *)data;
			if(attr) {
				Pointf p = attr->mtx.Transform(d->p);
				ApproximateQuadratic(*g, pos, attr->mtx.Transform(d->p1), p, tolerance);
				pos = p;
			}
			else {
				ApproximateQuadratic(*g, pos, d->p1, d->p, tolerance);
				pos = d->p;
			}
			data += sizeof(QuadraticData);
			break;
		}
		case CUBIC: {
			PAINTER_TIMING("CUBIC");
			const CubicData *d = (CubicData *)data;
			if(attr) {
				Pointf p = attr->mtx.Transform(d->p);
				ApproximateCubic(*g, pos, attr->mtx.Transform(d->p1),
				                 attr->mtx.Transform(d->p2), p, tolerance);
				pos = p;
			}
			else {
				ApproximateCubic(*g, pos, d->p1, d->p2, d->p, tolerance);
				pos = d->p;
			}
			data += sizeof(CubicData);
			break;
		}
		case CHAR: {
			const CharData *ch = (CharData *)data;
			ApproximateChar(*g, ch->p, ch->ch, ch->fnt, tolerance);
			data += sizeof(CharData);
			break;
		}
		default:
			NEVER();
			g->End();
			return;
		}
	}
	g->End();
}

Buffer<ClippingLine> BufferPainter::RenderPath(double width, Event<One<SpanSource>&> ss, const RGBA& color)
{
	PAINTER_TIMING("RenderPath");
	Buffer<ClippingLine> newclip;

	if(width == FILL)
		Close();

	current = Null;

	if(width == 0 || !ss && color.a == 0 && width >= FILL)
		return newclip;
	
	if(co && width >= FILL && !ss && !alt && mode == MODE_ANTIALIASED) {
		for(int i = 0; i < path_info->path.GetCount(); i++) {
			while(jobcount >= cojob.GetCount())
				cojob.Add().rasterizer.Create(ib.GetWidth(), ib.GetHeight(), false);
			CoJob& job = cojob[jobcount++];
			job.path_info = path_info;
			job.subpath = i;
			job.width = width;
			job.color = color;
		}
		if(jobcount >= BATCH_SIZE)
			FinishPathJob();
		return newclip;
	}

	FinishPathJob();
	FinishFillJob();
	
	rasterizer.Reset();

	RTIMING("Span finish");
	PathJob j(rasterizer, width, path_info->ischar, dopreclip, path_info->path_min, path_info->path_max, path_info->attr);
	if(j.preclipped)
		return newclip;
	
	bool doclip = width == CLIP;
	auto fill = [&](CoWork *co) {
		int opacity = int(256 * path_info->attr.opacity);
		Rasterizer::Filler *rg;
		SpanFiller          span_filler;
		SolidFiller         solid_filler;
		SubpixelFiller      subpixel_filler;
		ClipFiller          clip_filler(render_cx);
		NoAAFillerFilter    noaa_filler;
		MaskFillerFilter    mf;
		subpixel_filler.sbuffer = subpixel;
		subpixel_filler.invert = path_info->attr.invert;
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
				solid_filler.invert = path_info->attr.invert;
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
	for(const auto& p : path_info->path) {
		RenderPathSegments(j.g, p, j.regular ? &path_info->attr : NULL, j.tolerance);
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
	if(width == ONPATH) {
		onpath = pick(j.onpathtarget.path);
		pathlen = j.onpathtarget.len;
	}
	return newclip;
}

void BufferPainter::CoJob::DoPath(const BufferPainter& sw)
{
	rasterizer.Reset();

	PathJob j(rasterizer, width, path_info->ischar, sw.dopreclip, path_info->path_min, path_info->path_max, path_info->attr);
	if(j.preclipped)
		return;
	evenodd = j.evenodd;
	BufferPainter::RenderPathSegments(j.g, path_info->path[subpath], j.regular ? &path_info->attr : NULL, j.tolerance);
}

void BufferPainter::FinishPathJob()
{
	if(jobcount == 0)
		return;
	RTIMING("Finish");
	const int TH = 2;
	if(jobcount >= TH) {
		CoWork co;
		co * [&] {
			int i;
			while((i = co.Next()) < jobcount)
				cojob[i].DoPath(*this);
		};
	}
		
	FinishFillJob();
	
	fillcount = jobcount;
	Swap(cofill, cojob); // Swap to keep allocated rasters (instead of pick)
	
	fill_job & [=] {
		int miny = ib.GetHeight() - 1;
		int maxy = 0;
		for(int i = 0; i < fillcount; i++) {
			CoJob& j = cofill[i];
			if(fillcount < TH)
				j.DoPath(*this);
			miny = min(miny, j.rasterizer.MinY());
			maxy = max(maxy, j.rasterizer.MaxY());
			j.c = Mul8(j.color, int(256 * j.path_info->attr.opacity));
		}
		auto fill = [&](int ymin, int ymax) {
			SolidFiller solid_filler;
			for(int i = 0; i < fillcount; i++) {
				CoJob& j = cofill[i];
				int jymin = max(j.rasterizer.MinY(), ymin);
				int jymax = min(j.rasterizer.MaxY(), ymax);
				for(int y = jymin; y <= jymax; y++)
					if(j.rasterizer.NotEmpty(y)) {
						solid_filler.c = j.c;
						solid_filler.invert = j.path_info->attr.invert;
						solid_filler.t = ib[y];
						if(clip.GetCount()) {
							MaskFillerFilter mf;
							const ClippingLine& s = clip.Top()[y];
							if(!s.IsEmpty() && !s.IsFull()) {
								mf.Set(&solid_filler, s);
								j.rasterizer.Render(y, mf, j.evenodd);
							}
						}
						else
							j.rasterizer.Render(y, solid_filler, j.evenodd);
					}
			}
		};
	
		int n = maxy - miny;
		if(n >= 0) {
			if(n > 6) {
				CoWork co;
				co * [&] {
					for(;;) {
					#if 0
						int y = co.Next() + miny;
						if(y > maxy)
							break;
						fill(y);
					#else
						const int N = 4;
						int y = N * co.Next() + miny;
						if(y > maxy)
							break;
						int e = min(y + N - 1, maxy);
						fill(y, min(y + N - 1, maxy));
					#endif
					}
				};
			}
			else
				fill(miny, maxy);
		}
	};

	jobcount = 0;
}

void BufferPainter::Finish()
{
	FinishPathJob();
	FinishFillJob();
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
	FinishPathJob();
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
