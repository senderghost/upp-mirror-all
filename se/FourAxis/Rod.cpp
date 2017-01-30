#include "Hot4d.h"

Rod::Rod()
{
	CtrlLayout(*this);

	y <<= 23;
	x <<= 10;

	left_x <<= 10;
	left_y <<= 10;
	right_x <<= 10;
	right_y <<= 10;
	rect_x <<= 50;
	rect_y <<= 40;

	inner_depth <<= 5;
	inner_left_x <<= 0;
	inner_left_y <<= 0;
	inner_right_x <<= 0;
	inner_right_y <<= 0;
	inner_rect_x <<= 30;
	inner_rect_y <<= 20;
}

void Qel(Path& path, double cx, double cy, double rx, double ry, double from = 0)
{
	int n4 = int(sqrt(rx * rx + ry * ry) / 0.5);
	if(n4)
		for(int a = 0; a <= n4; a++) {
			double angle = M_PI * a / n4 / 2 + from;
			path.Kerf(rx * cos(angle) + cx, ry * sin(angle) + cy);
			if(a == 0)
				path.NewSegment();
		}
	else
		path.Kerf(cx, cy);
	path.NewSegment();
}

Path Rod::Get()
{
	Path path;

	int n4 = 50;

	double depth = Nvl((double)~inner_depth);
	Sizef rect = MakePoint(rect_x, rect_y);
	Sizef left = MakePoint(left_x, left_y);
	Sizef right = MakePoint(right_x, right_y);

	rect /= 2;
	left /= 2;
	right /= 2;

	Pt center = MakePoint(x, y);
	center.x += rect.cx;

	path.To(0, center.y);

	Pt begin(center.x - rect.cx, center.y);

	path.NewSegment();
	path.MainShape();
	path.Kerf(begin);
	Qel(path, center.x - rect.cx + left.cx, center.y + rect.cy - left.cy, -left.cx, left.cy);
//	path.Kerf(center.x + rect.cx, center.y + rect.cy + right.cy);
	Qel(path, center.x + rect.cx - right.cx, center.y + rect.cy - right.cy, -right.cx, right.cy, M_PI / 2);
	
	if(inner) {
		path.NewSegment();
		Pt h(center.x + rect.cx, center.y);
		path.To(h);
		path.EndMainShape();

		Sizef irect = MakePoint(inner_rect_x, inner_rect_y);
		Sizef ileft = MakePoint(inner_left_x, inner_left_y);
		Sizef iright = MakePoint(inner_right_x, inner_right_y);

		irect /= 2;
		ileft /= 2;
		iright /= 2;

		Pt icenter(center.x + rect.cx - irect.cx - depth, center.y);

		path.Kerf(icenter.x + irect.cx, icenter.y);

		Qel(path, icenter.x + irect.cx - iright.cx, icenter.y + irect.cy - iright.cy, iright.cx, iright.cy);
		Qel(path, icenter.x - irect.cx + ileft.cx, icenter.y + irect.cy - ileft.cy, ileft.cx, ileft.cy, M_PI / 2);
		Qel(path, icenter.x - irect.cx + ileft.cx, icenter.y - irect.cy + ileft.cy, ileft.cx, ileft.cy, M_PI);
		Qel(path, icenter.x + irect.cx - iright.cx, icenter.y - irect.cy + iright.cy, iright.cx, iright.cy, 3 * M_PI / 2);

		path.Kerf(icenter.x + irect.cx, icenter.y);

		path.To(h);
		path.NewSegment();
		path.MainShape();
	}

//	path.Kerf(center.x + rect.cx + right.cx, center.y - rect.cy);
	Qel(path, center.x + rect.cx - right.cx, center.y - rect.cy + right.cy, -right.cx, right.cy, M_PI);
	Qel(path, center.x - rect.cx + left.cx, center.y - rect.cy + left.cy, -left.cx, left.cy, 3 * M_PI / 2);
	path.NewSegment();
	path.Kerf(begin);
	path.EndMainShape();

	Vector<Spar> spars;
	double w = center.x;
	ReadSpar(spars, TOP_SPAR, w, top_spar, top_spar_width, top_spar_height, top_spar_circle);
	ReadSpar(spars, BOTTOM_SPAR, w, bottom_spar, bottom_spar_width, bottom_spar_height, bottom_spar_circle);

	Path r;
	r.segment = 1000;
	for(int i = 0; i < path.GetCount(); i++)
		if(!(path[i].mainshape && DoSpars(r, path, i, spars)))
			r.Add(path[i]);

	r.NewSegment();
	r.To(0, center.y);

	return r;
}
