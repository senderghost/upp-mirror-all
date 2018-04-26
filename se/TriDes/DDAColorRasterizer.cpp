#include "DDAColorRasterizer.h"

namespace Upp {

DDAColorRasterizer::DDAColorRasterizer()
{
	cy = 0;
	p0 = p1 = Point(0, 0);
	j1 = j2 = Null;
	b1 = b2 = Null;
	close = false;
	width = 1;

	miny = INT_MAX;
	maxy = 0;
}

void DDAColorRasterizer::AHorz(int x, int y, int cx, RGBA c1, RGBA c2)
{
	if(cx) {
		if(cx < 0) {
			x = x + cx + 1;
			cx = -cx;
			Swap(c1, c2);
		}
		if(y >= 0 && y < cy) {
			Segment& m = segment.At(y).Add();
			m.l = x;
			m.h = x + cx;
			m.lc = c1;
			m.rc = c2;
			m.flag = flag;
			miny = min(y, miny);
			maxy = max(y, maxy);
		}
		flag = true;
	}
}

void DDAColorRasterizer::AVert(int x, int y, int cy)
{
	if(cy) {
		if(cy < 0) {
			y = y + cy + 1;
			cy = -cy;
		}
		for(int i = 0; i < cy; i++)
			AddSegment(x, x + cx, c1, c2y + i, 1);
	}
}

inline
RGBA Blend(RGBA a, RGBA b, int a, int sz)
{
	BLEND(c)   r = a.c * (sz - a) / a + b.c * a / sz;
}

void DDAColorRasterizer::DoLine(Point p1, Point p2, bool last)
{
	dirx = sgn(p2.x - p1.x);
	diry = sgn(p2.y - p1.y);
	int dx = abs(p2.x - p1.x);
	int dy = abs(p2.y - p1.y);
	int x = p1.x;
	int y = p1.y;
	int x0 = x;
	int y0 = y;
	if(dx < dy) {
		int dda = dy >> 1;
		int n = dy + last;
		for(;;) {
			if(x != x0) {
				AVert(x0, y0, y - y0);
				x0 = x;
				y0 = y;
			}
			if(n-- <= 0)
				break;
			y += diry;
			dda -= dx;
			if(dda < 0) {
				dda += dy;
				x += dirx;
			}
		}
		AVert(x0, y0, y - y0);
	}
	else {
		int dda = dx >> 1;
		int n = dx + last;
		for(;;) {
			if(y != y0) {
				AHorz(x0, y0, x - x0);
				x0 = x;
				y0 = y;
			}
			if(n-- <= 0)
				break;
			x += dirx;
			dda -= dy;
			if(dda < 0) {
				dda += dx;
				y += diry;
			}
		}
		AHorz(x0, y0, x - x0);
	}
}

DDAColorRasterizer& DDAColorRasterizer::Move(Point p)
{
	if(pseg)
		Close();
	p0 = p1 = p;
	return *this;
}

DDAColorRasterizer& DDAColorRasterizer::Line(Point p)
{
	if(pseg) {
		Point a = p1;
		Point b = p;
		if(a.y > b.y)
			Swap(a, b);
		pseg->flag = false;
		pseg->DoLine(a, b, true);
		p1 = p;
	}
	else {
		if(width <= 1)
			DoLine(p1, p, false);
		else
			FatLine(p);
		p1 = p;
	}
	return *this;
}

DDAColorRasterizer& DDAColorRasterizer::Close()
{
	if(p1 != p0) {
		close = true;
		Line(p0);
		close = false;
		if(!pseg)
			b1 = b2 = Null;
	}
	return *this;
}

DDAColorRasterizer& DDAColorRasterizer::Polygon()
{
	pseg.Create();
	pseg->Cy(cy);
	return *this;
}

DDAColorRasterizer& DDAColorRasterizer::Fill()
{
	ASSERT(pseg);
	Close();
	for(int y = pseg->miny; y <= pseg->maxy; y++) {
		Vector<Segment>& gg = pseg->segment[y];
		Sort(gg);
		int i = 0;
		bool flag = false;
		while(i < gg.GetCount()) {
			int l = gg[i].l;
			int h = gg[i].h;
			flag ^= gg[i++].flag;
			while(i < gg.GetCount() && flag) {
				h = gg[i].h;
				flag ^= gg[i++].flag;
			}
			PutHorz(l, y, h - l);
		}
	}
	pseg.Clear();
	return *this;
}

DDAColorRasterizer::~DDAColorRasterizer() {}

}
