#ifndef _CocoDraw_CocoDraw_h
#define _CocoDraw_CocoDraw_h

#include <Draw/Draw.h>

#define Point NS_Point
#define Rect  NS_Rect
#define Size  NS_Size
#include <AppKit/AppKit.h>
#undef  Point
#undef  Rect
#undef  Size

namespace Upp {

template <class T>
struct CFRef {
	T ptr;
	T operator~()   { return ptr; }
	operator T()    { return ptr; }
	T  operator->() { return ptr; }
	T  Detach()     { T h = ptr; ptr = NULL; return h; }
	CFRef(T p)      { ptr = p; }
	~CFRef()        { if(ptr) CFRelease(ptr); }
};

struct AutoreleasePool {
	NSAutoreleasePool *pool;

	AutoreleasePool() {
		pool = [[NSAutoreleasePool alloc] init];
	}
	~AutoreleasePool() {
	    [pool release];
	}
};

WString ToWString(CFStringRef s);
String ToString(CFStringRef s);

struct GuiLock {};

class SystemDraw : public Draw {
	virtual dword GetInfo() const;

	virtual void BeginOp();
	virtual void EndOp();
	virtual void OffsetOp(Point p);
	virtual bool ClipOp(const Rect& r);
	virtual bool ClipoffOp(const Rect& r);
	virtual bool ExcludeClipOp(const Rect& r);
	virtual bool IntersectClipOp(const Rect& r);
	virtual bool IsPaintingOp(const Rect& r) const;
	virtual Rect GetPaintRect() const;

	virtual	void DrawRectOp(int x, int y, int cx, int cy, Color color);
	virtual void SysDrawImageOp(int x, int y, const Image& img, Color color);
	virtual void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color);

	virtual void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                                const int *counts, int count_count,
	                                int width, Color color, Color doxor);
	virtual void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
	                                   const int *subpolygon_counts, int scc,
	                                   const int *disjunct_polygon_counts, int dpcc,
	                                   Color color, int width, Color outline,
	                                   uint64 pattern, Color doxor);
	virtual void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color);

	virtual void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor);
	virtual void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		                    Color ink, int n, const int *dx);

private:
	Vector<Point> offset;
	Vector<Rect>  clip;

	int   top;
	Color fill = Null;
	
	void   Push();
	void   Pop();
	CGContextRef cgContext;
	
	void   ClipCG(const Rect& r);
	void   FlipY(int& y)           { y = top - y; }
	Rect   GetClip() const         { return clip.GetCount() ? clip.Top() : Rect(-999999, -999999, 999999, 999999); }
	Point  GetOffset() const       { return offset.GetCount() ? offset.Top() : Point(0, 0); }
	CGRect Convert(int x, int y, int cx, int cy);
	CGRect Convert(const Rect& r)  { return Convert(r.left, r.top, r.GetWidth(), r.GetHeight()); }

	void  Set(Color c);

	void Init(CGContext *cgContext_, int cy);

	SystemDraw() {}
	
	friend class ImageDraw;
	friend class BackDraw;
	friend class ViewDraw;

public:
	bool     CanSetSurface()          { return false; }
	static void Flush()               {} // TODO?

	SystemDraw(CGContext *cgContext, int cy);
	~SystemDraw();
};

 
inline void SetSurface(SystemDraw& w, const Rect& dest, const RGBA *pixels, Size srcsz, Point poff)
{ // TODO: Unless we can do this...
	NEVER();
}

class ImageDraw : public SystemDraw {
	ImageBuffer ib;
	
	One<ImageDraw> alpha;

	void Init(int cx, int cy);

public:
	Draw& Alpha();

	operator Image();

	Image GetStraight();

	ImageDraw(Size sz);
	ImageDraw(int cx, int cy);
	~ImageDraw();
};

};

#endif
