#include "Coco.h"

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
//	[top->window setAcceptsMouseMovedEvents:YES];
//	[window makeFirstResponder:view];
	
//	Ctrl::SetImageCursor(TestImg::TEST());
}

void CocoWindow::LeftUp(Upp::Point p)
{
//	[[NSCursor pointingHandCursor] set];
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
