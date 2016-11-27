#include <CtrlLib/CtrlLib.h>
#include <Report/Report.h>

using namespace Upp;

#include <CtrlLib/CtrlLib.h>

using namespace Upp;


void PaintPtr(Draw& w, double pos, double m, int d, Color color, Size sz2)
{
	w.DrawLine(sz2.cx, sz2.cy,
	           sz2.cx + int(m * sin(pos * 2 * M_PI) * sz2.cx),
	           sz2.cy - int(m * cos(pos * 2 * M_PI) * sz2.cy),
	           d, color);
}

void PaintCenteredText(Draw& w, int x, int y, const char *text, Font fnt, Color c)
{
	Size tsz = GetTextSize(text, fnt);
	w.DrawText(x - tsz.cx / 2, y - tsz.cy / 2, text, fnt, c);
}

Drawing Work(int size)
{
	DrawingDraw w(size, size);
	Size sz = Size(size, size);
	w.DrawRect(sz, White);
	int ln = size / 100;
	sz -= 2 * ln;
	w.Offset(ln, ln);
	Pointf center(size / 2, size / 2);;
	w.DrawEllipse(0, 0, sz.cx, sz.cy, SWhite, ln, SBlack);
	w.DrawEllipse(sz.cx / 2 - 100, sz.cy / 2 - 100, 200, 200, SWhite, ln, SBlack);
	w.DrawEllipse(sz.cx / 2 - 20, sz.cy / 2 - 20, 40, 40, SWhite, ln, SBlack);
	Font fnt = Arial(size / 10);
	for(int i = 0; i <= 10; i++) {
		double angle = (i * 280 / 10 + 130) * M_PI / 180;
		DDUMP(angle);
		Pointf h = center + 0.8 * Polar(angle) * center.x;
		PaintCenteredText(w, (int)h.x, (int)h.y, AsString(i), fnt, Black());
	}
	for(int i = 0; i <= 40; i++) {
		double angle = (i * 280 / 40 + 130) * M_PI / 180;
		Pointf h = center.x * Polar(angle);
		Pointf p1 = center + h * 0.5;
		Pointf p2 = center + h * ((i & 1) ? 0.6 : i % 4 == 0 ? 0.7 : 0.65);
		w.DrawLine(int(p1.x), int(p1.y), int(p2.x), int(p2.y), ln, Black);
	}

	w.End();
	return w;
}

struct App : TopWindow {
	virtual void Paint(Draw& w)
	{
		Drawing iw = Work(1000);
		w.DrawDrawing(0, 0, iw);
	}

	void Timer()
	{
		Refresh();
	}

	App()
	{
		SetRect(0, 0, 1000, 1000);
		Sizeable().Zoomable();
		BackPaint();
		SetTimeCallback(-1000, callback(this, &App::Timer));
		Title("Clock");
	}
};

GUI_APP_MAIN
{
	Report r;
	r.DrawDrawing(0, 0, Work(500));
	r.DrawDrawing(1200, 0, Work(600));
	r.DrawDrawing(2500, 0, Work(700));
	r.DrawDrawing(0, 1500, Work(800));
	r.DrawDrawing(1800, 1500, Work(900));
	Perform(r);
}
