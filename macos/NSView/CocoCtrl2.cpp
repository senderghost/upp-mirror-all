#include "Coco.h"

void MyTest::Layout()
{
	Refresh();
}

void MyTest::Paint(Draw& w)
{
	DLOG("PAINT");
	DDUMP(GetSize());
	w.DrawRect(GetSize(), White());
	w.DrawText(10, 10, text);
	w.DrawText(10, 40, AsString(GetRect()));
//	return;
}

void MyTest::MouseMove(Point p, dword flags)
{
	text = AsString(p);
}
