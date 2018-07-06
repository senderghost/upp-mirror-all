#include "CocoDraw.h"

namespace Upp {

void SystemDraw::Init(CGContext *cgContext_, int cy)
{
	cgContext = cgContext_;
	top = cy;
	Push();
	CGContextSetTextPosition(cgContext, 0, 0);
    CGContextSetTextDrawingMode(cgContext, kCGTextFill);
}

SystemDraw::SystemDraw(CGContext *cgContext_, int cy)
{
	Init(cgContext_, cy);
}

SystemDraw::~SystemDraw()
{
	Pop();
}

void SystemDraw::Set(Color c)
{
	if(c != fill) {
		fill = c;
	    CGContextSetRGBFillColor(cgContext, c.GetR() / 255.0, c.GetG() / 255.0, c.GetB() / 255.0, 1.0);
	}
}

dword SystemDraw::GetInfo() const
{
	return DRAWTEXTLINES;
}

void SystemDraw::Push()
{
	CGContextSaveGState(cgContext);
	offset.Add(GetOffset());
	clip.Add(GetClip());
}

void SystemDraw::Pop()
{
	if(offset.GetCount())
		offset.Drop();
	if(clip.GetCount())
		clip.Drop();
    CGContextRestoreGState(cgContext);
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


CGRect SystemDraw::Convert(int x, int y, int cx, int cy)
{
	Point p = GetOffset(); // TODO: Optimize
	x += p.x;
	y += p.y;
	return CGRectMake(x, top - y - cy, cx, cy);
}

void SystemDraw::ClipCG(const Rect& r)
{
	Size sz = r.GetSize();
	CGContextClipToRect(cgContext, CGRectMake(r.left, top - r.top - sz.cy, sz.cx, sz.cy));
}

bool SystemDraw::ClipOp(const Rect& r)
{
	Push();
	DDUMP(r);
	DDUMP(clip.Top());
	DDUMP(GetOffset());
	clip.Top() &= r.Offseted(GetOffset());
	DDUMP(clip.Top());
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
	// TODO
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
		CGContextSetBlendMode(cgContext, kCGBlendModeExclusion);
		CGContextFillRect(cgContext, cgr);
		CGContextSetBlendMode(cgContext, kCGBlendModeNormal);
	}
	else {
		Set(color);
		CGContextFillRect(cgContext, cgr);
	}
}

};
