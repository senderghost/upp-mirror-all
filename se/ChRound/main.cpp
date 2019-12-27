#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

#define IMAGECLASS TestImg
#define IMAGEFILE <ChRound/test.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS TestImg
#define IMAGEFILE <ChRound/test.iml>
#include <Draw/iml_source.h>

using namespace Upp;

struct MyApp : TopWindow {
	virtual void Paint(Draw& w);
};

void MyApp::Paint(Draw& sw)
{
	DrawPainter w(sw, GetSize());
	w.DrawRect(GetSize(), WhiteGray());
	Image h = Combine(CtrlsImg::RoundFill(), TestImg::test(), CtrlsImg::RoundBox(), Red());
	w.DrawImage(100, 100, h);
	ChPaint(w, 100, 150, 400, 20, h);

	Image m = MakeButton(5, TestImg::test(), 2, Brown(), 0xffff);
	w.DrawImage(0, 0, m);
	ChPaint(w, 600, 300, 120, 60, m);
	
	int y = 500;
	RoundedRect(w, 100, y, 200, 50, 5, 5, 0); w.Fill(Green()); y += 60;
	RoundedRect(w, 100, y, 200, 50, 5, 5, 0xffff); w.Fill(Green()); y += 60;
	RoundedRect(w, 100, y, 200, 50, 5, 5, CORNER_TOP_LEFT|CORNER_TOP_RIGHT); w.Fill(Green()); y += 60;
	RoundedRect(w, 100, y, 200, 50, 5, 5, CORNER_TOP_LEFT|CORNER_BOTTOM_RIGHT); w.Fill(Green()); y += 60;
}

GUI_APP_MAIN
{
	MyApp().Run();
}
