#include "Painter.h"

namespace Upp {

Buffer<ClippingLine> PainterBackend::RenderPath(double width, SpanSource *ss, const RGBA& color)
{
	rasterizer.Reset();
	
	Rectf preclip = Null;

	if((dopreclip == 1 || dopreclip == 2 && attr.dash.GetCount()) && width != ONPATH) {
		preclip = rasterizer.GetClip();
		Pointf tl, br, a;
		Xform2D imx = Inverse(attr.mtx);
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

		double ex = max(width, 0.0) * (1 + attr.miter_limit);
		if(path_max.y + ex < preclip.top || path_min.y - ex > preclip.bottom ||
		   path_max.x + ex < preclip.left || path_min.x + ex > preclip.right) {
		}
	}

	Transformer trans(pathattr.mtx);
	Stroker stroker;
	Dasher dasher;
	OnPathTarget onpathtarget;
	bool evenodd = pathattr.evenodd;
	bool regular = pathattr.mtx.IsRegular() && width < 0 && !ischar;
	double tolerance;
	LinearPathConsumer *g = alt ? (LinearPathConsumer *)alt : &rasterizer;

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
		if(attr.dash.GetCount()) {
			dasher.Init(attr.dash, attr.dash_start);
			dasher.target = &stroker;
			g = &dasher;
		}
		else
			g = &stroker;
		evenodd = false;
	}

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
	subpixel_filler.sbuffer = subpixel;
	subpixel_filler.invert = pathattr.invert;
	bool doclip = width == CLIP;
	if(doclip) {
		rg = &clip_filler;
		newclip.Alloc(size.cy);
	}
	else
	if(ss) {
		if(!span)
			span.Alloc((subpixel ? 3 : 1) * size.cx + 3);
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

	const char *data = ~path;
	const char *end = path.end();
	for(;;) {
		int type = ((PathElement *)data)->type;
		if(data >= end || type == DIV) {
			g->End();
			if(width != ONPATH) {
				if(alt)
					alt->Fill(width, ss, color);
				else {
					PAINTER_TIMING("Fill");
					for(int y = rasterizer.MinY(); y <= rasterizer.MaxY(); y++) {
						solid_filler.t = subpixel_filler.t = span_filler.t = PixelLine(y);
						subpixel_filler.end = subpixel_filler.t + size.cx;
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
			if(data >= end)
				break;
			ReadElement<PathElement>(data);
		}
		else
		switch(type) {
		case MOVE: {
			const auto& d = ReadElement<LinearData>(data);
			g->Move(pos = regular ? pathattr.mtx.Transform(d.p) : d.p);
			break;
		}
		case LINE: {
			PAINTER_TIMING("LINE");
			const auto& d = ReadElement<LinearData>(data);
			g->Line(pos = regular ? pathattr.mtx.Transform(d.p) : d.p);
			break;
		}
		case QUADRATIC: {
			PAINTER_TIMING("QUADRATIC");
			const auto& d = ReadElement<QuadraticData>(data);
			if(regular) {
				Pointf p = pathattr.mtx.Transform(d.p);
				ApproximateQuadratic(*g, pos, pathattr.mtx.Transform(d.p1), p, tolerance);
				pos = p;
			}
			else {
				ApproximateQuadratic(*g, pos, d.p1, d.p, tolerance);
				pos = d.p;
			}
			break;
		}
		case CUBIC: {
			PAINTER_TIMING("CUBIC");
			const auto& d = ReadElement<CubicData>(data);
			if(regular) {
				Pointf p = pathattr.mtx.Transform(d.p);
				ApproximateCubic(*g, pos, pathattr.mtx.Transform(d.p1),
				                 pathattr.mtx.Transform(d.p2), p, tolerance);
				pos = p;
			}
			else {
				ApproximateCubic(*g, pos, d.p1, d.p2, d.p, tolerance);
				pos = d.p;
			}
			break;
		}
		case CHAR:
			ApproximateChar(*g, ReadElement<CharData>(data), tolerance);
			break;
		default:
			NEVER();
			return newclip;
		}
	}
	current = Null;
	if(width == ONPATH) {
		onpath = pick(onpathtarget.path);
		pathlen = onpathtarget.len;
	}
	return newclip;
}

};