#include "Painter.h"
#include "Fillers.h"

namespace Upp {

#define LLOG(x) // DLOG(x)

void PainterTarget::Fill(double width, SpanSource *ss, const RGBA& color) {}

void BufferPainter::ClearOp(const RGBA& color)
{
	UPP::Fill(~ib, color, ib.GetLength());
}

struct BufferPainter::OnPathTarget : LinearPathConsumer {
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
};

Buffer<ClippingLine> BufferPainter::RenderPath(double width, SpanSource *ss, const RGBA& color)
{
	PAINTER_TIMING("RenderPath");
	Buffer<ClippingLine> newclip;
	if(width == 0) {
		current = Null;
		return newclip;
	}

	if(co && width != CLIP && width != ONPATH && !ss && cojob.GetCount() < 16 && !alt) {
		if(width < 0)
			Close();
		CoJob& job = cojob.Add();
		job.path.data = clone(path.data);
		job.path.type = clone(path.type);
		job.attr = pathattr;
		job.width = width;
		job.color = color;
		job.ischar = ischar;
		job.path_min = path_min;
		job.path_max = path_max;
		job.rasterizer.Create(ib.GetWidth(), ib.GetHeight(), mode == MODE_SUBPIXEL);
		current = Null;
		if(cojob.GetCount() > 16)
			Finish();
		return newclip;
	}
	
	Finish();
	
	Transformer trans(pathattr.mtx);
	Stroker stroker;
	Dasher dasher;
	OnPathTarget onpathtarget;
	bool evenodd = pathattr.evenodd;
	bool regular = pathattr.mtx.IsRegular() && width < 0 && !ischar;
	double tolerance;
	LinearPathConsumer *g = alt ? (LinearPathConsumer *)alt : &rasterizer;
	Rectf preclip = Null;
	if(dopreclip && width != ONPATH) {
		preclip = rasterizer.GetClip();
		Xform2D imx = Inverse(pathattr.mtx);
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
				Rectf(path_min, path_max).Inflated(max(width, 0.0) * (1 + pathattr.miter_limit)))) {
			LLOG("Preclipped " << preclip << ", min " << path_min << ", max " << path_max);
			current = Null;
			return newclip;
		}
	}
	if(!IsNull(alt_tolerance))
		tolerance = alt_tolerance;
	else
	if(regular)
		tolerance = 0.3;
	else {
		trans.target = g;
		g = &trans;
		tolerance = 0.3 / pathattr.mtx.GetScale();
	}
	if(width == ONPATH) {
		g = &onpathtarget;
		regular = false;
	}
	else
	if(width > 0) {
		stroker.Init(width, pathattr.miter_limit, tolerance, pathattr.cap, pathattr.join, preclip);
		stroker.target = g;
		if(pathattr.dash.GetCount()) {
			dasher.Init(pathattr.dash, pathattr.dash_start);
			dasher.target = &stroker;
			g = &dasher;
		}
		else
			g = &stroker;
		evenodd = false;
	}
	else
		Close();
	byte *data = path.data;
	int opacity = int(256 * pathattr.opacity);
	Pointf pos = Pointf(0, 0);
	int i = 0;
	Rasterizer::Filler *rg;
	SpanFiller          span_filler;
	SolidFiller         solid_filler;
	SubpixelFiller      subpixel_filler;
	ClipFiller          clip_filler(render_cx);
	NoAAFillerFilter    noaa_filler;
	MaskFillerFilter    mf;
	bool doclip = width == CLIP;
	subpixel_filler.sbuffer = subpixel;
	subpixel_filler.invert = pathattr.invert;
	if(doclip) {
		rg = &clip_filler;
		newclip.Alloc(ib.GetHeight());
	}
	else
	if(ss) {
		if(!span)
			span.Alloc((subpixel ? 3 : 1) * ib.GetWidth() + 3);
		if(subpixel) {
			subpixel_filler.ss = ss;
			subpixel_filler.buffer = span;
			subpixel_filler.alpha = opacity;
			rg = &subpixel_filler;
		}
		else {
			span_filler.ss = ss;
			span_filler.buffer = span;
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
	PAINTER_TIMING("RenderPath2");
	while(i < path.type.GetCount()) {
		RenderPathSegments(g, pos, path, data, i, attr, regular, tolerance);
		g->End();
		if(width != ONPATH) {
			if(alt)
				alt->Fill(width, ss, color);
			else {
				PAINTER_TIMING("Fill");
				for(int y = rasterizer.MinY(); y <= rasterizer.MaxY(); y++) {
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
					rasterizer.Render(y, *rf, evenodd);
					if(doclip)
						clip_filler.Finish(newclip[y]);
				empty:;
				}
				rasterizer.Reset();
			}
		}
	}
	current = Null;
	if(width == ONPATH) {
		onpath = pick(onpathtarget.path);
		pathlen = onpathtarget.len;
	}
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
	Buffer<ClippingLine> newclip = RenderPath(CLIP, NULL, RGBAZero());
	if(attr.hasclip)
		clip.Top() = pick(newclip);
	else {
		clip.Add() = pick(newclip);
		attr.hasclip = true;
		attr.cliplevel = clip.GetCount();
	}
}

}
