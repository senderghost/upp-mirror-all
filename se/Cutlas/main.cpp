#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

struct MyApp : TopWindow {
	int y = 500;
	Pointf p1 = Pointf(0, 0);
	Pointf p2 = Pointf(1000, 1000);
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		DrawPainter iw(w, sz);
		iw.Clear(White());
		iw.Move(0, y).Line(sz.cx, y).Stroke(1, LtBlue());
		
		iw.Move(p1).Line(p2).Stroke(1, Black());

		Pointf h = p2 - p1;
		double x = h.x / h.y * (y - p1.y) + p1.x;
		iw.Circle(x, y, 5).Stroke(2, LtRed());
	}
	
	virtual void MouseMove(Point p, dword keyflags) {
		p2 = p;
		Refresh();
	}

	virtual void LeftDown(Point p, dword keyflags) {
		p1 = p;
		Refresh();
	}

	virtual void RightDown(Point p, dword keyflags) {
		y = p.y;
		Refresh();
	}
};

GUI_APP_MAIN
{
	MyApp().Run();
}
