#include "CocoUtil.h"

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
	window->ns_size = Upp::Size(r.size.width, r.size.height);
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

void CocoWindow::Create(const Upp::Rect& r, const char *title)
{
    NSRect frame = NSMakeRect(r.left, r.top, r.GetWidth(), r.GetHeight());
	NSWindow *window = [[NSWindow alloc] initWithContentRect:frame
	                   styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
	                             | NSWindowStyleMaskResizable
	                   backing:NSBackingStoreBuffered
	                   defer:false];
	
	CFRef<CFStringRef> s = CFStringCreateWithCString(NULL, title, kCFStringEncodingUTF8);
	[window setTitle:(NSString *)~s];

	window.backgroundColor = nil;
		
	view = [[[CocoView alloc] initWithFrame:frame] autorelease];
	view->window = this;
	[window setContentView:view];
	[window setDelegate:view];
	[window setAcceptsMouseMovedEvents:YES];
	[window makeFirstResponder:view];
	[window makeKeyAndOrderFront:view];
	

	NSRect nr = [view bounds];
	ns_size = Upp::Size(nr.size.width, nr.size.height);
}

void CocoWindow::Paint(Draw& w)
{
	w.DrawRect(GetSize(), White());
	w.DrawText(10, 10, text);
	return;

    ImageDraw iw(100, 30);
    iw.DrawRect(0, 0, 100, 30, Cyan());
    iw.DrawText(0, 0, "Hello world!", Arial(20), Black());
    
    Draw& aw = iw.Alpha();
    aw.DrawRect(0, 0, 100, 30, White());
    aw.DrawRect(5, 10, 30, 3, Black());
    
    Image h = iw;
    
    w.DrawImage(0, 40, TestImg::TEST());
    w.Offset(17, 17);
    w.DrawRect(0, 0, 20, 20, LtRed());
    w.DrawRect(20, 20, 20, 20, LtGreen());
    w.DrawRect(0, 0, 20, 20, LtGray());
    w.DrawImage(50, 40, TestImg::TEST(), Magenta());

    w.DrawImage(50, 80, 40, 40, TestImg::TEST());
 
	Upp::Size sz = GetTextSize("Hello worldy!", Serif(40));
	w.Clip(30, 40, 50, 40);
	w.DrawRect(30, 30, sz.cx, sz.cy, Yellow());
    w.DrawImage(25, 35, 40, 40, TestImg::TEST());
    w.DrawText(30, 30, "Hello worldy!", Serif(40), LtMagenta());
    w.DrawRect(40, 40, 30, 10, InvertColor());
    w.End();
    
    w.DrawImage(5, 120, h);
    
    w.DrawText(150, 150, 0, "Rotated 0", Arial(16), White());
    w.DrawText(150, 150, 20, "Rotated 2", Arial(16), LtGray());
    w.DrawText(150, 150, 90, "Rotated 9", Arial(16), LtGreen());
    w.DrawText(150, 150, 900, "Rotated 90", Arial(16), LtRed());
}

void CocoWindow::LeftDown(Upp::Point p)
{
	text = "LeftDown " << p;
	Refresh();
	[window setAcceptsMouseMovedEvents:YES];
	[window makeFirstResponder:view];
	
	SetImageCursor(TestImg::TEST());
}

void CocoWindow::LeftUp(Upp::Point p)
{
	[[NSCursor pointingHandCursor] set];
	text = "LeftUp " << p;
	Refresh();
}

void CocoWindow::Drag(Upp::Point p)
{
	text = "Drag " << p;
	Refresh();
}

void CocoWindow::Move(Upp::Point p)
{
	text = "Move " << p;
	Refresh();
}

void CocoWindow::Refresh()
{
	[view setNeedsDisplay:YES];
	// - (BOOL)needsToDrawRect:(NSRect)rect;
}
