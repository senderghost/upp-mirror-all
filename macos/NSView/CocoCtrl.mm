#include <CtrlCore/CocoMM.h>

void DrawNSImage(Upp::Draw& w)
{
	CGContextRef cg = (CGContextRef) ((Upp::SystemDraw *)&w)->GetCGHandle();

//	NSImage *img = [NSImage imageNamed:NSImageNameCaution];
//	NSImage *img = [NSImage imageNamed:NSImageNameInfo];
	NSImage *img = [NSImage imageNamed:NSImageNameStopProgressFreestandingTemplate];


    NSGraphicsContext *gc = [NSGraphicsContext graphicsContextWithCGContext:cg flipped:NO];
    
    NSGraphicsContext* cgc = [NSGraphicsContext currentContext];
    [NSGraphicsContext setCurrentContext:gc];
    [img drawInRect:NSMakeRect(0, 0, 48, 48)];
	[NSGraphicsContext setCurrentContext:cgc];
}

void DrawColors(Upp::Draw& w, Upp::Size sz)
{
	w.DrawRect(sz, Upp::White());

	int x = 0;
	int y = 0;
	int ii = 1;
	
	auto advance = [&] (int cx, int cy) {
		x += cx;
		if(x + cx > sz.cx) {
			x = 0;
			y += cy;
		}
		ii++;
	};

	CGRect cr;

#define NSCOLOR(color) \
	if(pass == 0) \
		w.DrawText(x, y, #color); \
	else { \
		CGContextSetFillColorWithColor(cg, [NSColor color].CGColor); \
		cr = CGRectMake(x, sz.cy - y - 30 - 20, 200, 30); \
		CGContextFillRect(cg, cr); \
	} \
	advance(200, 50);

	CGContextRef cg = (CGContextRef) ((Upp::SystemDraw *)&w)->GetCGHandle();
	CGContextSaveGState(cg);
	
	for(int pass = 0; pass < 2; pass++) {
		x = 0;
		y = 0;
		NSCOLOR(labelColor)
		NSCOLOR(secondaryLabelColor)
		NSCOLOR(tertiaryLabelColor)
		NSCOLOR(quaternaryLabelColor)
		NSCOLOR(textColor)
	//	NSCOLOR(placeholderTextColor)
		NSCOLOR(selectedTextColor)
		NSCOLOR(textBackgroundColor)
		NSCOLOR(selectedTextBackgroundColor)
		NSCOLOR(keyboardFocusIndicatorColor)
	//	NSCOLOR(linkColor)
	//	NSCOLOR(separatorColor)
		NSCOLOR(selectedMenuItemTextColor)
		NSCOLOR(gridColor)
		NSCOLOR(headerTextColor)
	//	NSCOLOR(alternatingContentBackgroundColors)
	//	NSCOLOR(controlAccentColor)
		NSCOLOR(controlColor)
		NSCOLOR(controlBackgroundColor)
		NSCOLOR(controlTextColor)
		NSCOLOR(disabledControlTextColor)
	//	NSCOLOR(currentControlTint)
		NSCOLOR(selectedControlColor)
		NSCOLOR(selectedControlTextColor)
		NSCOLOR(alternateSelectedControlTextColor)
		NSCOLOR(scrubberTexturedBackgroundColor)
		NSCOLOR(windowBackgroundColor)
		NSCOLOR(windowFrameTextColor)
		NSCOLOR(underPageBackgroundColor)
	//	NSCOLOR(findHighlightColor)
		NSCOLOR(highlightColor)
		NSCOLOR(shadowColor)
	}

	CGContextRestoreGState(cg);
	
#if 0
	void *cg = ((SystemDraw *)&w)->GetCGHandle();
	
	int y = 10;
	for(int type = COCO_BUTTON; type <= COCO_SCROLLTRACK; type++)
		for(int value = 0; value <= 2; value++) {
			for(int state = CTRL_NORMAL; state <= CTRL_DISABLED; state++)
				Coco_ThemePaint(cg, RectC(state * 60 + 10, y, 50, 30), type, value, state, false);
			y += 40;
		}
		
	Coco_ThemePaint(cg, RectC(800, 20, scrollcx, 100), COCO_SCROLLTRACK, 0, 0, false);
	
	Coco_ThemePaint(cg, RectC(850, 20, 50, 50), COCO_BRUSH, 1, 0, false);

//	PaintButton();
	w.DrawEllipse(GetSize(), Magenta());
	w.DrawLine(100, 100, 500, 140, 4, LtRed());
//	w.DrawText(10, 10, text);
//	w.DrawText(10, 40, AsString(GetRect()));
//	return;
	for(int i = 0; i < text.GetCount(); i++)
		w.DrawText(0, i * StdFont().GetCy(), text[i], StdFont().Bold());
/*
	w.Offset(600, 100);
	w.DrawRect(0, 0, 100, 100, Blue());
	w.End();
	
	DLOG("HERE");
	w.Clip(600, 100, 75, 75);
	w.DrawRect(0, 0, 1500, 2500, LtBlue());
	w.End();

	DLOG("CLIPOFF");
	w.Clipoff(600, 100, 50, 50);
	w.DrawRect(-30, -30, 1500, 2500, Red());
	w.End();
*/	
	StdDisplay().Paint(w, RectC(300, 20, 200, 20), "Just a test",
		               Black(), Yellow(), 0);

	w.DrawText(0, 500, String() << GetOwner() << ", key: " << GetActiveCtrl() << ", this: " << this);
#endif
}

