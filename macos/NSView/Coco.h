#ifndef _NSView_Coco_h_
#define _NSView_Coco_h_

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_header.h>

using namespace Upp;

struct MyTest : Ctrl {
	virtual void Layout();
	virtual void Paint(Draw& draw);
	virtual void MouseMove(Point p, dword flags);
	virtual bool Key(dword key, int count);
	
	Array<String> text;
	
	void Add(const String& text);
	
	MyTest();
};

#endif
