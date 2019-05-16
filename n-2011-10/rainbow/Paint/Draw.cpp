#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct App : public Ctrl {
	EditString x;
	ArrayCtrl a;
	
	void Paint(Draw& w)
	{
		Size sz = GetSize();
		w.DrawRect(0, 0, sz.cx, sz.cy, SWhite);
		w.DrawRect(10, 10, 30, 30, SRed);
		w.DrawLine(45, 45, 80, 120, 4, Blue);
		w.DrawLine(80, 90, 400, 0, PEN_DASHDOT);
		w.DrawEllipse(200, 200, 50, 100, Green);
		w.DrawImage(200, 10, CtrlImg::HandCursor());
		const char *text = "This text is centered";
		Size tsz = GetTextSize(text, Arial(25).Bold());
		w.DrawText((sz.cx - tsz.cx) / 2, (sz.cy - tsz.cy) / 2, text, Arial(27).Bold(), SBlue);
		w.Clipoff(200, 50, 95, 100);
		w.DrawText(0, 80, "CLIPPED", Roman(25));
		w.End();
	}

	App()
	{
		x <<= "Hello world!";
		Add(x.LeftPos(100, 100).TopPos(500, 20));
		a.AddColumn("first");
		a.AddColumn("second");
		for(int i = 0; i < 100; i++)
			a.Add(i, FormatIntRoman(i));
		Add(a.LeftPos(300, 150).TopPos(10, 300));
//		Sizeable();
	}
};

GUI_APP_MAIN
{
	App app;
	ChStdSkin();
	SetDesktop(app);
	app.SetFocus();
	Ctrl::EventLoop();
}
