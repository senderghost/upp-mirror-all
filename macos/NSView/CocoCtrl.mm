#include <CocoDraw/MMDraw.h>
#include "Coco.h"

@interface CocoView : NSView <NSWindowDelegate>
{
	@public
	CocoWindow *window;
}
@end

struct CocoWindow::Top {
	NSWindow *window = NULL;
	CocoView *view = NULL;
	Upp::Size ns_size;
};

@implementation CocoView
-(void)drawRect:(NSRect)rect {
	SystemDraw w([[NSGraphicsContext currentContext] CGContext], [self bounds].size.height);
    window->Paint(w);
}

- (void)mouseDown:(NSEvent *)e {
	NSPoint p = [self convertPoint:[e locationInWindow] fromView:nil];
	window->LeftDown(Upp::Point(p.x, p.y));
}

- (void)mouseUp:(NSEvent *)e {
	NSPoint p = [self convertPoint:[e locationInWindow] fromView:nil];
	window->LeftUp(Upp::Point(p.x, p.y));
}

- (void)mouseMoved:(NSEvent *)e {
	NSPoint p = [self convertPoint:[e locationInWindow] fromView:nil];
	window->Move(Upp::Point(p.x, p.y));
}

- (void)mouseDragged:(NSEvent *)e {
    NSPoint p = [self convertPoint:[e locationInWindow] fromView:nil];
    window->Drag(Upp::Point(p.x, p.y));
}

- (void)keyDown:(NSEvent *)e {
	window->Text("keyDown flag: " + AsString(e.modifierFlags) + ", characters: " +
	             ToString((CFStringRef)(e.characters)) + ", keycode: " + AsString(e.keyCode));
}

- (void)keyUp:(NSEvent *)e {
	window->Text("keyUp ");
}

- (void)windowDidResize:(NSNotification *)notification {
	NSRect r = [self bounds];
	if(window->top)
		window->top->ns_size = Upp::Size(r.size.width, r.size.height);
}

- (void) rightMouseDown:(NSEvent*)e
{
    NSPoint p = [self convertPoint:[e locationInWindow] fromView:nil];
    window->Drag(Upp::Point(p.x, p.y));
}

- (void)windowDidBecomeKey:(NSNotification *)notification
{
	// THIS IS "GOT FOCUS"
}

- (BOOL)acceptsFirstResponder {	return YES; }
- (BOOL)canBecomeKeyView { return YES; }

@end

CocoWindow::~CocoWindow()
{
	if(top)
		delete top;
}

void CocoWindow::Create(const Upp::Rect& r, const char *title)
{
	top = new Top;

    NSRect frame = NSMakeRect(r.left, r.top, r.GetWidth(), r.GetHeight());
	top->window = [[NSWindow alloc] initWithContentRect:frame
	                   styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
	                             | NSWindowStyleMaskResizable
	                   backing:NSBackingStoreBuffered
	                   defer:false];
	
	CFRef<CFStringRef> s = CFStringCreateWithCString(NULL, title, kCFStringEncodingUTF8);
	[top->window setTitle:(NSString *)~s];

	top->window.backgroundColor = nil;
		
	top->view = [[[CocoView alloc] initWithFrame:frame] autorelease];
	top->view->window = this;
	[top->window setContentView:top->view];
	[top->window setDelegate:top->view];
	[top->window setAcceptsMouseMovedEvents:YES];
	[top->window makeFirstResponder:top->view];
	[top->window makeKeyAndOrderFront:top->view];

	NSRect nr = [top->view bounds];
	top->ns_size = Upp::Size(nr.size.width, nr.size.height);
}

void CocoWindow::Refresh()
{
	[top->view setNeedsDisplay:YES];
	// - (BOOL)needsToDrawRect:(NSRect)rect;
}

Upp::Size CocoWindow::GetSize() const
{
	return top ? top->ns_size : Size(0, 0);
}
