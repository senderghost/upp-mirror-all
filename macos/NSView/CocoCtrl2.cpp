#include "Coco.h"

void MyTest::LeftDrag(Point, dword)
{
	VectorMap<String, ClipData> data;
//	Append(data, CtrlImg::exclamation());
	Append(data, String("Hello world!"));
	text = decode(DoDragAndDrop(data, CtrlImg::exclamation()), DND_MOVE, "MOVE",
	                                                           DND_COPY, "COPY",
	                                                           "NONE");
}

void MyTest::Layout()
{
	Add("ScreenView " + AsString(GetScreenView()));
	Refresh();
}

extern int scrollcx;

void PaintColors1(Draw& w, Size sz)
{
	w.DrawRect(sz, White());

	int x = 0;
	int y = 0;
	int ii = 1;
	
	auto advance = [&] (int cx, int cy) {
		if(x + cx > sz.cx) {
			x = 0;
			y += cy;
		}
		else
			x += cx;
		ii++;
	};
	
	while(ii <= 58) {
		Color c = CocoBrush(ii);
		w.DrawRect(x, y, 150, 20, CocoBrush(ii));
		w.DrawText(x, y, AsString(ii) + " " + AsString(c), StdFont(), IsLight(c) ? Black() : White());
		advance(150, 20);
	}
	
	y += 20;
	x = 0;
	for(int type = COCO_MENU; type <= COCO_MENUITEM; type++)
		for(int state = CTRL_NORMAL; state <= CTRL_DISABLED; state++) {
			w.DrawImage(x, y, Coco_ThemeImage(50, 50, 10, type, 0, state));
			advance(60, 60);
		}

	for(int value = 0; value < 10; value++)
		for(int state = CTRL_NORMAL; state <= CTRL_DISABLED; state++) {
			w.DrawImage(x, y, Coco_ThemeImage(50, 50, 10, COCO_BACKGROUND, value, state));
			w.DrawText(x, y, AsString(value));
			advance(60, 60);
		}
	
}

void PaintButtons(Draw& w, Size sz)
{
	w.DrawRect(sz, SColorFace());
	int x = 0;
	int y = 0;
	int ii = 1;
	
	auto advance = [&] (int cx, int cy) {
		if(x + cx > sz.cx) {
			x = 0;
			y += cy;
		}
		else
			x += cx;
		ii++;
	};
	
	for(int i = 0; i <= 17; i++) {
		for(int value = 0; value < 2; value++) {
			w.DrawImage(x, y, Coco_ThemeImage(50, 50, 10, -i, value));
			w.DrawText(x, y, AsString(i));
			advance(55, 55);
		}
	}

	w.DrawImage(x, y, Coco_ThemeImage(50, 50, 10, 0, 1));
	advance(55, 55);
	w.DrawImage(x, y, Coco_ThemeImage(50, 50, 10, -16, 0));
	advance(55, 55);
	
	w.DrawRect(200, 200, 30, 30, GrayColor(188));
	Image ve = CtrlsImg::VE();
	w.DrawImage(150, 200, CtrlsImg::VE());
	w.DrawImage(100, 200, Magnify(CtrlsImg::VE(), 3, 3));
}

void MyTest::Paint(Draw& w)
{
	w.DrawRect(GetSize(), White());
	w.DrawText(10, 10, text, Arial(50));
//	PaintButtons(w, GetSize());
}

void MyTest::Add(const String& s)
{
//	text.Add(s);
//	while(text.GetCount() > 8)
//		text.Remove(0);
	Refresh();
}

void MyTest::MouseMove(Point p, dword flags)
{
	Add("MouseMove " + AsString(p));
	Refresh();
}

void MyTest::LeftDown(Point p, dword flags)
{
	PasteClip d = Ctrl::Clipboard();
	if(AcceptText(d)) {
		DLOG("TEXT");
		text = GetString(d);
	}
	if(AcceptImage(d))
		img = GetImage(d);
	if(AcceptFiles(d)) {
		Vector<String> x = GetFiles(d);
		text = AsString(x.GetCount()) + " " + Join(x, " ");
	}
	Refresh();
}

void MyTest::RightDown(Point, dword)
{
	WriteClipboardText("Hello world!");
//	Minimize(true);
}

bool MyTest::Key(dword key, int count)
{
	String kkk = GetKeyDesc(key);
	Add(Format("%d %x", (int)key, (int)key) + "  " + kkk);
	Refresh();
	if(key == K_ENTER)
		Overlap();
	return true;
}

Image MyTest::CursorImage(Point p, dword keyflags)
{
//	return Image::Arrow();
	return Image::Hand();
}

MyTest::MyTest()
{
	Sizeable().Zoomable();
}
