#include <CtrlCore/CocoMM.h>

#include "Coco.h"

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_source.h>

GUI_APP_MAIN {
// int main(int argc, const char *argv[]) {
   LOG("U++ logging 2");
   
//   for(int i = 0; i < Font::GetFaceCount(); i++)
  //     DDUMP(Font::GetFaceName(i));
   
//   DDUMP(GetTextSize("Hello world!", Arial(12)));
  // DDUMP(GetTextSize("Hello world!", Arial(12).Bold()));
//   DDUMP(Arial(12).GetAscent());
//   DDUMP(Arial(12).GetDescent());
   
//    ListFonts();


	MyTest win;
	win.Create(RectC(100, 100, 300, 300), "Just a test window", false);

	Ctrl::EventLoop();
 
    return;

    NSApplication *app = [NSApplication sharedApplication];

#if 0
    NSRect frame = NSMakeRect( 100., 100., 300., 300. );

    NSWindow *window = [[NSWindow alloc]
        initWithContentRect:frame
                  styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
                   | NSWindowStyleMaskResizable
                    backing:NSBackingStoreBuffered
                      defer:false];

    [window setTitle:@"Testing"];

    TestView *view = [[[TestView alloc] initWithFrame:frame] autorelease];
    [window setContentView:view];
    [window setDelegate:view];
    [window makeKeyAndOrderFront:nil];

    /* someone mentioned:
     *  [NSApp activateIgnoringOtherApps:YES]; 
     * not sure where to put it... */
#endif
#if 0
	CocoWindow win;
	win.Create(RectC(100, 100, 300, 300), "Just a test window");

    [app run];

    [pool release];
#endif
//    return( EXIT_SUCCESS );
}
