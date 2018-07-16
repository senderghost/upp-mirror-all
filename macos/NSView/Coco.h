#ifndef _NSView_Coco_h_
#define _NSView_Coco_h_

#include <CocoDraw/CocoDraw.h>

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_header.h>

using namespace Upp;

#include <Draw/Draw.h>

using namespace Upp;

struct CocoWindow {
	void      Paint(Draw& draw);
	void      LeftDown(Upp::Point p);
	void      LeftUp(Upp::Point p);
	void      Drag(Upp::Point p);
	void      Move(Upp::Point p);
	void      Text(const String& h) { text = h; Refresh(); }

	struct Top;
	
	Top      *top = NULL;
	
	String    text;

	void      Refresh();
	Size      GetSize() const;
	
	void Create(const Upp::Rect& r, const char *title);
	~CocoWindow();
};

#endif
