#ifndef _NSView_Coco_h_
#define _NSView_Coco_h_

#include <CtrlLib/CtrlLib.h>

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
	virtual void LeftUp(Point p, dword flags);
	virtual void RightDown(Point, dword);
	virtual Image  CursorImage(Point p, dword keyflags);
	virtual Size   GetMinSize() const { return Size(200, 20); }
	virtual Size   GetMaxSize() const { return Size(300, 300); }

	Array<String> text;
	
	void Add(const String& text);
	
	MyTest();
};

#endif
