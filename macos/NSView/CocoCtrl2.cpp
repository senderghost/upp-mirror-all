#include "Coco.h"

void MyTest::Layout()
{
	Add("ScreenView " + AsString(GetScreenView()));
	Refresh();
}

void MyTest::Paint(Draw& w)
{
	w.DrawRect(GetSize(), White());
	w.DrawEllipse(GetSize(), Magenta());
	w.DrawLine(100, 100, 500, 140, 4, LtRed());
//	w.DrawText(10, 10, text);
//	w.DrawText(10, 40, AsString(GetRect()));
//	return;
	for(int i = 0; i < text.GetCount(); i++)
		w.DrawText(0, i * StdFont().GetCy(), text[i], StdFont().Bold());
/*
	w.Offset(600, 100);
	w.DrawRect(0, 0, 100, 100, Blue());
	w.End();
	
	DLOG("HERE");
	w.Clip(600, 100, 75, 75);
	w.DrawRect(0, 0, 1500, 2500, LtBlue());
	w.End();

	DLOG("CLIPOFF");
	w.Clipoff(600, 100, 50, 50);
	w.DrawRect(-30, -30, 1500, 2500, Red());
	w.End();
*/	
	StdDisplay().Paint(w, RectC(300, 20, 200, 20), "Just a test",
		               Black(), Yellow(), 0);

	w.DrawText(0, 500, String() << GetOwner() << ", key: " << GetActiveCtrl() << ", this: " << this);
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
	Add("MouseMove " + AsString(p));
	Refresh();
}

void MyTest::LeftTriple(Point p, dword)
{
}

void MyTest::LeftDown(Point p, dword flags)
{
	ViewDraw w(this);
	w.DrawRect(-1000, -1000, 3000, 3000, Yellow());
	w.DrawText(0, 0, "TRIPPLE!", Arial(100));
/*	Zoomable(!IsZoomable());
	SetCapture();*/
}

void MyTest::LeftUp(Point p, dword flags)
{
	ReleaseCapture();
}

void MyTest::RightDown(Point, dword)
{
	SetRect(500, 50, 600, 600);
}

bool MyTest::Key(dword key, int count)
{
	String kkk = GetKeyDesc(key);
	Add(Format("%d %x", (int)key, (int)key) + "  " + kkk);
	Refresh();
	return true;
}

Image MyTest::CursorImage(Point p, dword keyflags)
{
	return Image::Hand();
}

MyTest::MyTest()
{
}
