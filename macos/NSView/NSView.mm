#include "CocoUtil.h"

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS TestImg
#define IMAGEFILE <NSView/test.iml>
#include <Draw/iml_source.h>

@interface TestView : NSView <NSWindowDelegate> { }
-(void)drawRect:(NSRect)rect;
//- (BOOL) isFlipped;
@end

@implementation TestView
/*
- (BOOL) isFlipped
{
    return YES;
}
*/

-(void)drawRect:(NSRect)rect {
    [[NSColor blueColor] set];
    NSRectFill( [self bounds] );
    
    CGContext *cgContext = [[NSGraphicsContext currentContext] CGContext];

    {
        DDUMP(cgContext);
        SystemDraw w(cgContext, [self bounds].size.height);

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

		return;
    }

    CGContextSaveGState( cgContext );
//    CGContextTranslateCTM(cgContext, 0, NSHeight([self bounds]));
  //  CGContextScaleCTM(cgContext, 1, -1);

//	DrawRect(cgContext, RectC(10, 10, 200, 100 ), Red());

	CFRef<CFStringRef> s = CFStringCreateWithCString(NULL, "Times New Roman", kCFStringEncodingUTF8);
    CFRef<CTFontRef> ctfont0 = CTFontCreateWithName(s, 32, NULL);

    CTFontSymbolicTraits symbolicTraits = 0;
    symbolicTraits |= kCTFontBoldTrait;
    symbolicTraits |= kCTFontItalicTrait;

    CGAffineTransform transform = CGAffineTransformIdentity;

	CFRef<CTFontRef> ctfont = CTFontCreateCopyWithSymbolicTraits(ctfont0, 32, &transform, symbolicTraits, symbolicTraits);
    
    wchar h = 'A';
    
    CGGlyph glyph;
    CTFontGetGlyphsForCharacters(ctfont, (const UniChar*)&h, &glyph, 1);
    
    DDUMP(glyph);

    CGSize advance;
    CTFontGetAdvancesForGlyphs(ctfont, kCTFontOrientationHorizontal, &glyph, &advance, 1);
    
    DDUMP(advance.height);
    DDUMP(advance.width);
    
    DDUMP(CTFontGetAscent(ctfont));
    DDUMP(CTFontGetDescent(ctfont));
    DDUMP(CTFontGetLeading(ctfont));
    DDUMP(CTFontGetXHeight(ctfont));
    DDUMP(CTFontGetUnderlinePosition(ctfont));
   
	CFRef<CGFontRef> cgFont = CTFontCopyGraphicsFont(ctfont, NULL);
	DDUMP(~cgFont);
   
	CGContextSetFont(cgContext, cgFont);
   
	CGContextSetTextPosition(cgContext, 0, 0);

	CGPoint p;
	p.x = 50;
	p.y = 10;

    int ascent = ceil(CTFontGetAscent(ctfont));
    int descent = ceil(CTFontGetDescent(ctfont));

//	CGContextClipToRect(cgContext, CGRectMake(52, 8, 13, 15));

//    DrawRect(cgContext, p.x, p.y - descent, advance.width, descent, Cyan);
  //  DrawRect(cgContext, p.x, p.y, advance.width, ascent, Brown);

	CGContextSetFontSize(cgContext, 32);

    CGContextSetTextDrawingMode(cgContext, kCGTextFill);
    CGContextSetRGBFillColor(cgContext, 1, 1, 1, 1.0);
    
    CGContextRotateCTM(cgContext, 0.23);

    CGContextShowGlyphsAtPositions(cgContext, &glyph, &p, 1);

    CGContextRestoreGState(cgContext);
}

-(void)windowWillClose:(NSNotification *)note {
    [[NSApplication sharedApplication] terminate:self];
}

@end

void ListFonts();

int main(int argc, const char *argv[]) {
   LOG("U++ logging");
   
   for(int i = 0; i < Font::GetFaceCount(); i++)
       DDUMP(Font::GetFaceName(i));
   
//   DDUMP(GetTextSize("Hello world!", Arial(12)));
  // DDUMP(GetTextSize("Hello world!", Arial(12).Bold()));
//   DDUMP(Arial(12).GetAscent());
//   DDUMP(Arial(12).GetDescent());
   
//    ListFonts();

    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    NSApplication *app = [NSApplication sharedApplication];
    NSRect frame = NSMakeRect( 100., 100., 300., 300. );

    NSWindow *window = [[NSWindow alloc]
        initWithContentRect:frame
                  styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
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

    [app run];

    [pool release];
    return( EXIT_SUCCESS );
}
