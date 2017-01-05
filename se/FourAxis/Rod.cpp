#include "Hot4d.h"

Rod::Rod()
{
	CtrlLayout(*this);

	central <<= 15;
	leadin <<= 10;

	left_x <<= 30;
	left_y <<= 20;
	right_x <<= 30;
	right_y <<= 20;
	rect_x <<= 5;
	rect_y <<= 5;

	inner_left_x <<= 15;
	inner_left_y <<= 10;
	inner_right_x <<= 15;
	inner_right_y <<= 10;
	inner_rect_x <<= 2;
	inner_rect_y <<= 2;
}

void Qel(Path& path, double cx, double cy, double rx, double ry, double from = 0)
{
	int n4 = 50;
	for(int a = 0; a < n4; a++) {
		double angle = M_PI * a / n4 / 2 + from;
		path.Kerf(rx * cos(angle) + cx, ry * sin(angle) + cy);
	}
}

Path Rod::Get()
{
	Path path;

	int n4 = 50;

	Sizef rect(Nvl((double)~rect_x), Nvl((double)~rect_y));
	Sizef left(Nvl((double)~left_x), Nvl((double)~left_y));
	Sizef right(Nvl((double)~right_x), Nvl((double)~right_y));

	rect /= 2;
	left /= 2;
	right /= 2;

	Pointf center((double)~leadin + left.cx + rect.cx, ~central);

	path.To(0, center.y);
	Pointf start(center.x - left.cx - rect.cx, center.y);

	path.To(start);

	Qel(path, center.x - rect.cx, center.y + rect.cy, -left.cx, left.cy);
	Qel(path, center.x + rect.cx, center.y + rect.cy, -right.cx, right.cy, M_PI / 2);

	
	if(inner) {
		Pointf h(center.x + rect.cx + right.cx, center.y);
		path.Kerf(h);

		Sizef rect(~inner_rect_x, ~inner_rect_y);
		Sizef left(~inner_left_x, ~inner_left_y);
		Sizef right(~inner_right_x, ~inner_right_y);

		rect /= 2;
		left /= 2;
		right /= 2;

		path.Kerf(center.x + rect.cx + right.cx, center.y);

		Qel(path, center.x + rect.cx, center.y + rect.cy, right.cx, right.cy);
		Qel(path, center.x - rect.cx, center.y + rect.cy, left.cx, left.cy, M_PI / 2);
		Qel(path, center.x - rect.cx, center.y - rect.cy, left.cx, left.cy, M_PI);
		Qel(path, center.x + rect.cx, center.y - rect.cy, right.cx, right.cy, 3 * M_PI / 2);

		path.Kerf(center.x + rect.cx + right.cx, center.y);

		path.Kerf(h);
	}

	Qel(path, center.x + rect.cx, center.y - rect.cy, -right.cx, right.cy, M_PI);
	Qel(path, center.x - rect.cx, center.y - rect.cy, -left.cx, left.cy, 3 * M_PI / 2);

#if 0
	for(int i = 0; i < 4; i++) {
		int ts = findarg(i, 0, 1) >= 0 ? 1 : -1;
		int rs = findarg(i, 0, 3) >= 0 ? -1 : 1;
	
		double rx = (findarg(i, 0, 3) >= 0 ? left.cx : right.cx) / 2;
		double ry = (findarg(i, 0, 3) >= 0 ? left.cy : right.cy) / 2;

		Pointf c;
		c.x = center.x + rs * rect.cx / 2;
		c.y = center.y + ts * rect.cy / 2;
		
		for(int a = 0; a <= n4; a++) {
			double angle = M_PI * a / n4 / 2 + i * M_PI / 2;
			path.To(rx * -cos(angle) + c.x, ry * sin(angle) + c.y, true);
			first = false;
		}
		
		if(inner && i == 1) {
			Sizef rect(~inner_rect_x, ~inner_rect_y);
			Sizef left(~inner_left_x, ~inner_left_y);
			Sizef right(~inner_right_x, ~inner_right_y);
		
			for(int i = 0; i < 4; i++) {
				int ts = findarg(i, 0, 1) >= 0 ? -1 : 1;
				int rs = findarg(i, 0, 3) >= 0 ? -1 : 1;
			
				double rx = (findarg(i, 0, 3) >= 0 ? right.cx : left.cx) / 2;
				double ry = (findarg(i, 0, 3) >= 0 ? left.cy : right.cy) / 2;
		
				Pointf c;
				c.x = center.x + rs * rect.cx / 2;
				c.y = center.y + ts * rect.cy / 2;
				
				for(int a = 0; a <= n4; a++) {
					double angle = M_PI * a / n4 / 2 + i * M_PI / 2;
					path.To(rx * -cos(angle) + c.x, ry * sin(angle) + c.y, true);
					first = false;
				}
			}
		}
	}
#endif
	path.Kerf(start);
	return path;
}
