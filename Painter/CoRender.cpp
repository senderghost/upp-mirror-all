#include "Painter.h"
#include "Fillers.h"

#define LLOG(x)

namespace Upp {

BufferPainter::PathJob::PathJob(Rasterizer& rasterizer, double width, bool ischar, bool dopreclip,
                                Pointf path_min, Pointf path_max, const Attr& attr)
:	trans(attr.mtx)
{
	evenodd = attr.evenodd;
	regular = attr.mtx.IsRegular() && width < 0 && !ischar;

	g = &rasterizer;
	Rectf preclip = Null;
	if(dopreclip && width != ONPATH) {
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
}

void BufferPainter::CoJob::DoPath(const BufferPainter& sw)
{
	TIMING("DoPath");
	rasterizer.Reset();

	PathJob j(rasterizer, width, ischar, sw.dopreclip, path_min, path_max, attr);
	evenodd = j.evenodd;
	BufferPainter::RenderPathSegments(j.g, path, j.regular ? &attr : NULL, j.tolerance);
}

void BufferPainter::RenderPathSegments(LinearPathConsumer *g, const String& path,
                                       const Attr *attr, double tolerance)
{
	Pointf pos = Pointf(0, 0);
	const char *data = ~path;
	const char *end = path.end();
	while(data < end)
		switch(*data++) {
		case MOVE: {
			const LinearData *d = (LinearData *)data;
			data += sizeof(LinearData);
			g->Move(pos = attr ? attr->mtx.Transform(d->p) : d->p);
			break;
		}
		case LINE: {
			PAINTER_TIMING("LINE");
			const LinearData *d = (LinearData *)data;
			data += sizeof(LinearData);
			g->Line(pos = attr ? attr->mtx.Transform(d->p) : d->p);
			break;
		}
		case QUADRATIC: {
			PAINTER_TIMING("QUADRATIC");
			const QuadraticData *d = (QuadraticData *)data;
			data += sizeof(QuadraticData);
			if(attr) {
				Pointf p = attr->mtx.Transform(d->p);
				ApproximateQuadratic(*g, pos, attr->mtx.Transform(d->p1), p, tolerance);
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
			break;
		}
		case CHAR:
			ApproximateChar(*g, *(CharData *)data, tolerance);
			data += sizeof(CharData);
			break;
		default:
			NEVER();
			g->End();
			return;
		}
	g->End();
}

void BufferPainter::Finish()
{
	if(jobcount == 0)
		return;
	RTIMING("Finish");
	CoWork co;
	const int TH = 3;
	if(jobcount >= TH)
		co * [&] {
			int i;
			while((i = co.Next()) < jobcount)
				cojob[i].DoPath(*this);
		};
	int miny = ib.GetHeight() - 1;
	int maxy = 0;
	for(int i = 0; i < jobcount; i++) {
		CoJob& j = cojob[i];
		if(jobcount < TH)
			j.DoPath(*this);
		miny = min(miny, j.rasterizer.MinY());
		maxy = max(maxy, j.rasterizer.MaxY());
		j.c = Mul8(j.color, int(256 * j.attr.opacity));
	}
	auto fill = [&](CoWork *co) {
		SolidFiller solid_filler;
		int y;
		int ii = 0;
		while((y = (co ? co->Next() : ii++) + miny) <= maxy)
			for(int i = 0; i < jobcount; i++) {
				CoJob& j = cojob[i];
				if(y >= j.rasterizer.MinY() && y <= j.rasterizer.MaxY()) {
					solid_filler.c = j.c;
					solid_filler.invert = j.attr.invert;
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
	if(n >= 0)
		if(n > 6)
			co * [&] { fill(&co); };
		else
			fill(NULL);

	jobcount = 0;
}

};