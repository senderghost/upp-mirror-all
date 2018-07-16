#include "MMDraw.h"

namespace Upp {

void SystemDraw::Init(void *cgContext, int cy)
{
	handle = cgContext;
	top = cy;
	Push();
	CGContextSetTextPosition(cgHandle, 0, 0);
    CGContextSetTextDrawingMode(cgHandle, kCGTextFill);
}

SystemDraw::SystemDraw(void *cgContext, int cy)
{
	Init(cgContext, cy);
}

SystemDraw::~SystemDraw()
{
	Pop();
}

void SystemDraw::Set(Color c)
{
	if(c != fill) {
		fill = c;
	    CGContextSetRGBFillColor(cgHandle, c.GetR() / 255.0, c.GetG() / 255.0, c.GetB() / 255.0, 1.0);
	}
}

dword SystemDraw::GetInfo() const
{
	return DRAWTEXTLINES;
}

void SystemDraw::Push()
{
	CGContextSaveGState(cgHandle);
	offset.Add(GetOffset());
	clip.Add(GetClip());
}

void SystemDraw::Pop()
{
	if(offset.GetCount())
		offset.Drop();
	if(clip.GetCount())
		clip.Drop();
    CGContextRestoreGState(cgHandle);
    fill = Null;
}

void SystemDraw::BeginOp()
{
	Push();
}

void SystemDraw::EndOp()
{
	Pop();
}

void SystemDraw::OffsetOp(Point p)
{
	Push();
	offset.Top() += p;
}

#if 0
CGRect SystemDraw::AsCG(const Rect& r)
{
	Point p = r.TopLeft();
	Size sz = r.GetSize();
	Convert(p.x, p.y);
	CGRect cgr;
	cgr.origin.x = p.x;
	cgr.origin.y = p.y;
	cgr.size.width = sz.cx;
	cgr.size.height = sz.cy;
	return cgr;
}
#endif


RectCG SystemDraw::Convert(int x, int y, int cx, int cy)
{
	Point p = GetOffset(); // TODO: Optimize
	x += p.x;
	y += p.y;
	return RectCG(x, top - y - cy, cx, cy);
}

RectCG SystemDraw::Convert(const Rect& r)
{
	return Convert(r.left, r.top, r.GetWidth(), r.GetHeight());
}


void SystemDraw::ClipCG(const Rect& r)
{
	Size sz = r.GetSize();
	CGContextClipToRect(cgHandle, CGRectMake(r.left, top - r.top - sz.cy, sz.cx, sz.cy));
}

bool SystemDraw::ClipOp(const Rect& r)
{
	Push();
	clip.Top() &= r.Offseted(GetOffset());
	ClipCG(clip.Top());
	return true;
}

bool SystemDraw::ClipoffOp(const Rect& r)
{
	Push();
	clip.Top() &= r.Offseted(GetOffset());
	offset.Top() += r.TopLeft();
	ClipCG(clip.Top());
	return true;
}

bool SystemDraw::ExcludeClipOp(const Rect& r)
{
	// TODO, perhaps use CGContextClipToRects
	return true;
}

bool SystemDraw::IntersectClipOp(const Rect& r)
{
	ClipCG(r.Offseted(GetOffset()));
	return true;
}

bool SystemDraw::IsPaintingOp(const Rect& r) const
{
	// TODO
	Rect cr = r.Offseted(GetOffset());
	cr.Intersect(GetClip());
	return !cr.IsEmpty();
}

Rect SystemDraw::GetPaintRect() const
{
	return Rect(0, 0, INT_MAX, INT_MAX);
}

void SystemDraw::DrawRectOp(int x, int y, int cx, int cy, Color color)
{
	DLOG("DrawRectOp");
	CGRect cgr = Convert(x, y, cx, cy);
	if(color == InvertColor()) {
		Set(White());
		CGContextSetBlendMode(cgHandle, kCGBlendModeExclusion);
		CGContextFillRect(cgHandle, cgr);
		CGContextSetBlendMode(cgHandle, kCGBlendModeNormal);
	}
	else {
		Set(color);
		CGContextFillRect(cgHandle, cgr);
	}
}

};
