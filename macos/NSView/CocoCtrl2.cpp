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
//	w.DrawText(10, 10, text);
//	w.DrawText(10, 40, AsString(GetRect()));
//	return;
	for(int i = 0; i < text.GetCount(); i++)
		w.DrawText(0, i * StdFont().GetCy(), text[i]);
}

void MyTest::Add(const String& s)
{
	text.Add(s);
	while(text.GetCount() > 8)
		text.Remove(0);
	Refresh();
}

void MyTest::MouseMove(Point p, dword flags)
{
	DLOG("MouseMove " << p);
	Add("MouseMove " + AsString(p));
	Refresh();
}

void MyTest::LeftDown(Point p, dword flags)
{
	Zoomable(!IsZoomable());
}

bool MyTest::Key(dword key, int count)
{
	String kkk = GetKeyDesc(key);
	DDUMP(kkk);
	DUMPHEX(kkk);
	Add(Format("%d %x", (int)key, (int)key) + "  " + kkk);
	Refresh();
	return true;
}

MyTest::MyTest()
{
}
