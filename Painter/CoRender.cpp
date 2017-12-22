#include "Painter.h"
#include "Fillers.h"

#define LLOG(x)

namespace Upp {

void BufferPainter::CoJob::DoPath(const BufferPainter& sw)
{
	Transformer trans(attr.mtx);
	Stroker stroker;
	Dasher dasher;
	bool evenodd = attr.evenodd;
	bool regular = attr.mtx.IsRegular() && width < 0 && !ischar;
	double tolerance;
	LinearPathConsumer *g = &rasterizer;
	Rectf preclip = Null;
	if(sw.dopreclip && width != ONPATH) {
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
	if(width > 0) {
		stroker.Init(width, attr.miter_limit, tolerance, attr.cap, attr.join, preclip);
		stroker.target = g;
		if(attr.dash.GetCount()) {
			dasher.Init(attr.dash, attr.dash_start);
			dasher.target = &stroker;
			g = &dasher;
		}
		else
			g = &stroker;
		evenodd = false;
	}
	Pointf pos = Pointf(0, 0);
	int i = 0;
	const byte *data = path.data;
	while(i < path.type.GetCount())
		data = BufferPainter::RenderPathSegments(g, pos, path, data, i, attr, regular, tolerance);
}

// void BufferPainter::PrepareRendering(Rasterizer& rasterizer, Stroker& stroker, Dasher& dasher, bool& regular

const byte *BufferPainter::RenderPathSegments(LinearPathConsumer *g, Pointf& pos, const Path& path, const byte *data, int& i,
                                      const Attr& attr, bool regular, double tolerance)
{
	while(i < path.type.GetCount()) {
		switch(path.type[i++]) {
		case MOVE: {
			const LinearData *d = (LinearData *)data;
			data += sizeof(LinearData);
			g->Move(pos = regular ? attr.mtx.Transform(d->p) : d->p);
			break;
		}
		case LINE: {
			PAINTER_TIMING("LINE");
			const LinearData *d = (LinearData *)data;
			data += sizeof(LinearData);
			g->Line(pos = regular ? attr.mtx.Transform(d->p) : d->p);
			break;
		}
		case QUADRATIC: {
			PAINTER_TIMING("QUADRATIC");
			const QuadraticData *d = (QuadraticData *)data;
			data += sizeof(QuadraticData);
			if(regular) {
				Pointf p = attr.mtx.Transform(d->p);
				ApproximateQuadratic(*g, pos, attr.mtx.Transform(d->p1), p, tolerance);
				pos = p;
			}
			else {
				ApproximateQuadratic(*g, pos, d->p1, d->p, tolerance);
				pos = d->p;
			}
			break;
		}
		case CUBIC: {
			PAINTER_TIMING("CUBIC");
			const CubicData *d = (CubicData *)data;
			data += sizeof(CubicData);
			if(regular) {
				Pointf p = attr.mtx.Transform(d->p);
				ApproximateCubic(*g, pos, attr.mtx.Transform(d->p1),
				                 attr.mtx.Transform(d->p2), p, tolerance);
				pos = p;
			}
			else {
				ApproximateCubic(*g, pos, d->p1, d->p2, d->p, tolerance);
				pos = d->p;
			}
			break;
		}
		case CHAR:
			ApproximateChar(*g, *(CharData *)data, tolerance);
			data += sizeof(CharData);
			break;
		case DIV:
			return data;
		default:
			NEVER();
			return data;
		}
	}
	return data;
}

/*
	int opacity = int(256 * attr.opacity);

	Rasterizer::Filler *rg;
	SpanFiller          span_filler;
	SolidFiller         solid_filler;
	SubpixelFiller      subpixel_filler;
	NoAAFillerFilter    noaa_filler;
	MaskFillerFilter    mf;
	bool doclip = width == CLIP;
	subpixel_filler.sbuffer = subpixel;
	subpixel_filler.invert = attr.invert;
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
			solid_filler.invert = attr.invert;
			rg = &solid_filler;
		}
	}
	if(mode == MODE_NOAA) {
		noaa_filler.Set(rg);
		rg = &noaa_filler;
	}
*/

void BufferPainter::Finish()
{
	CoWork co;
}

};