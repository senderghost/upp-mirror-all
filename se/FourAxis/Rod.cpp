#include "Hot4d.h"

Rod::Rod()
{
	CtrlLayout(*this);

	central <<= 15;
	leadin <<= 10;
	leadoutp <<= 0;
	left_x <<= 30;
	left_y <<= 20;
	right_x <<= 30;
	right_y <<= 20;
	rect_x <<= 5;
	rect_y <<= 5;
	steps <<= 1000;
}

Vector<Pointf> Rod::Get()
{
	Vector<Pointf> path;

	int n4 = (int)~steps / 4;

	Sizef rect(~rect_x, ~rect_y);
	Sizef left(~left_x, ~left_y);
	Sizef right(~right_x, ~right_y);

	Pointf center((double)~leadin + left.cx / 2 + rect.cx / 2, ~central);

	path.Add(Pointf(0, center.y));
	
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
			path.Add(Pointf(rx * -cos(angle) + c.x, ry * sin(angle) + c.y));
		}
	}
	path.Add(Pointf(center.x - left.cx / 2 - rect.cx / 2, center.y + rect.cy / 2));
	return path;
}

void Rod::Load(const ValueMap& json)
{
	SetValues(*this, json);
}

ValueMap Rod::Save()
{
	return GetValues(*this);
}
