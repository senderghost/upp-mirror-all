#ifndef _NSView_Coco_h_
#define _NSView_Coco_h_

#include <CtrlLib/CtrlLib.h>
#include <CtrlLib/ChCoco.h>

using namespace Upp;

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_header.h>

using namespace Upp;

struct MyTest : TopWindow {
	virtual void Layout();
	virtual void Paint(Draw& draw);
	virtual void MouseMove(Point p, dword flags);
	virtual bool Key(dword key, int count);
	virtual void LeftDown(Point p, dword flags);
	virtual void RightDown(Point, dword);
	virtual void LeftDrag(Point, dword);
	virtual Image  CursorImage(Point p, dword keyflags);
	
//	virtual Size   GetMinSize() const { return Size(200, 20); }
//	virtual Size   GetMaxSize() const { return Size(300, 300); }

	void Add(const String& text);
	
	String text;
	Image img;
	
	MyTest();
};

void PaintButton(void *cg);

void DrawColors(Draw& w, Size sz);

void DrawNSImage(Draw& w);

#endif
