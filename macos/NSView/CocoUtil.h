#ifndef _NSView_cocoutil_h_
#define _NSView_cocoutil_h_

#import <AppKit/AppKit.h>
#include <Draw/Draw.h>
#include <CocoDraw/CocoDraw.h>


#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_header.h>

using namespace Upp;

struct CocoWindow;

@interface CocoView : NSView <NSWindowDelegate>
{
	@public
	CocoWindow *window;
}
@end

struct CocoWindow {
	void      Paint(Draw& draw);
	void      LeftDown(Upp::Point p);
	void      LeftUp(Upp::Point p);
	void      Drag(Upp::Point p);
	void      Move(Upp::Point p);
	void      Text(const String& h) { text = h; Refresh(); }


	NSWindow *window = NULL;
	CocoView *view = NULL;
	Upp::Size ns_size;
	
	String    text;

	void      Refresh();
	Upp::Size GetSize() const   { return ns_size; }
	
	void Create(const Upp::Rect& r, const char *title);
};

#endif
