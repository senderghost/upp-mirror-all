#include "Painter.h"
#include "Fillers.h"

namespace Upp {
	
#define CTIMING(x)

void PainterBackend::RenderPath(double width, SpanSource *ss, const RGBA& color,
                                const PainterPathInfo& f, const char *path, const char *end,
                                LinearPathConsumer *alt)
{
	Buffer<ClippingLine> newclip;
	if((dopreclip == 1 || dopreclip == 2 && f.pathattr.dash.GetCount()) && width != PainterFrontend::ONPATH) {
		CTIMING("Preclip test");
		if(f.pathattr.mtx_serial != preclip_serial) {
			CTIMING("Preclip test 2");
			preclip_serial = f.pathattr.mtx_serial;
			Pointf tl, br, a;
			Xform2D imx = Inverse(f.pathattr.mtx);
			tl = br = imx.Transform(view.TopLeft());
			a = imx.Transform(view.TopRight());
			tl = min(a, tl);
			br = max(a, br);
			a = imx.Transform(view.BottomLeft());
			tl = min(a, tl);
			br = max(a, br);
			a = imx.Transform(view.BottomRight());
			tl = min(a, tl);
			br = max(a, br);
			preclip = Rectf(tl, br);
		}

		double ex = max(width, 0.0) * (1 + f.pathattr.miter_limit);

		CTIMING("Preclip test 3");
		if(f.path_max.y + ex < preclip.top || f.path_min.y - ex > preclip.bottom ||
		   f.path_max.x + ex < preclip.left || f.path_min.x + ex > preclip.right) {
		    CTIMING("Preclipped");
			return;
		}
	    CTIMING("Passed");
	}

	rasterizer.Reset();

	Transformer trans(f.pathattr.mtx);
	Stroker stroker;
	Dasher dasher;
	bool evenodd = f.pathattr.evenodd;
	bool regular = f.pathattr.mtx.IsRegular() && width < 0 && !f.ischar;
	double tolerance;
	LinearPathConsumer *g = alt ? (LinearPathConsumer *)alt : &rasterizer;

	if(regular)
		tolerance = 0.3;
	else {
		trans.target = g;
		g = &trans;
		tolerance = 0.3 / f.pathattr.mtx.GetScale();
	}

	if(width == PainterFrontend::ONPATH) {
		g = alt;
		regular = false;
	}
	else
	if(width > 0) {
		stroker.Init(width, f.pathattr.miter_limit, tolerance, f.pathattr.cap, f.pathattr.join, preclip);
		stroker.target = g;
		if(f.pathattr.dash.GetCount()) {
			dasher.Init(f.pathattr.dash, f.pathattr.dash_start);
			dasher.target = &stroker;
			g = &dasher;
		}
		else
			g = &stroker;
		evenodd = false;
	}

	int opacity = int(256 * f.pathattr.opacity);
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
	subpixel_filler.invert = f.pathattr.invert;
	bool doclip = width == PainterFrontend::CLIP;
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
			solid_filler.invert = f.pathattr.invert;
			rg = &solid_filler;
		}
	}
	if(mode == MODE_NOAA) {
		noaa_filler.Set(rg);
		rg = &noaa_filler;
	}

	for(;;) {
		int type = ((PainterFrontend::PathElement *)path)->type;
		if(path >= end || type == PainterFrontend::DIV) {
			g->End();
			if(width != PainterFrontend::ONPATH) {
				if(!alt) {
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
			if(path >= end)
				break;
			PainterFrontend::ReadElement<PainterFrontend::PathElement>(path);
		}
		else
		switch(type) {
		case PainterFrontend::MOVE: {
			const auto& d = PainterFrontend::ReadElement<PainterFrontend::LinearData>(path);
			g->Move(pos = regular ? f.pathattr.mtx.Transform(d.p) : d.p);
			break;
		}
		case PainterFrontend::LINE: {
			PAINTER_TIMING("LINE");
			const auto& d = PainterFrontend::ReadElement<PainterFrontend::LinearData>(path);
			g->Line(pos = regular ? f.pathattr.mtx.Transform(d.p) : d.p);
			break;
		}
		case PainterFrontend::QUADRATIC: {
			PAINTER_TIMING("QUADRATIC");
			const auto& d = PainterFrontend::ReadElement<PainterFrontend::QuadraticData>(path);
			if(regular) {
				Pointf p = f.pathattr.mtx.Transform(d.p);
				ApproximateQuadratic(*g, pos, f.pathattr.mtx.Transform(d.p1), p, tolerance);
				pos = p;
			}
			else {
				ApproximateQuadratic(*g, pos, d.p1, d.p, tolerance);
				pos = d.p;
			}
			break;
		}
		case PainterFrontend::CUBIC: {
			PAINTER_TIMING("CUBIC");
			const auto& d = PainterFrontend::ReadElement<PainterFrontend::CubicData>(path);
			if(regular) {
				Pointf p = f.pathattr.mtx.Transform(d.p);
				ApproximateCubic(*g, pos, f.pathattr.mtx.Transform(d.p1),
				                 f.pathattr.mtx.Transform(d.p2), p, tolerance);
				pos = p;
			}
			else {
				ApproximateCubic(*g, pos, d.p1, d.p2, d.p, tolerance);
				pos = d.p;
			}
			break;
		}
		case PainterFrontend::CHAR: {
			const auto& d = PainterFrontend::ReadElement<PainterFrontend::CharData>(path);
			ApproximateChar(*g, d.p, d.ch, d.fnt, tolerance);
			break;
		}
		default:
			NEVER();
			return;
		}
	}
}

void PainterBackend::Init(RGBA *p, Size sz, int mode, double offsety)
{
	size = sz;
	pixels = p;
	rasterizer.Create(sz.cx, sz.cy, mode == MODE_SUBPIXEL, offsety);
	render_cx = sz.cx;
	view = (Sizef)size;
	view.Offset(0, offsety);
	if(mode == MODE_SUBPIXEL) {
		render_cx *= 3;
		subpixel.Alloc(render_cx + 30);
	}
}

};