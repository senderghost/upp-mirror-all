#ifndef _Glyph_glyph_h_
#define _Glyph_glyph_h_

#include <Draw/Draw.h>
#include <Painter/Painter.h>

using namespace Upp;


Image  AutoCrop(const Image& m, RGBA c);
Image  RenderGlyph(Font fnt, int chr);
String CompressGlyph(const Image& m);
Image  DecompressGlyph(const String& g, Color c);

struct FDraw : Draw {
	struct Cloff {
		Vector<Rect> clip;
		Point        offset;
	};
	
	Array<Cloff> cloff;
	
	virtual dword GetInfo() const;

	virtual void BeginOp();
	virtual bool ClipOp(const Rect& r);
	virtual bool ClipoffOp(const Rect& r);
	virtual bool IntersectClipOp(const Rect& r);
	virtual bool IsPaintingOp(const Rect& r) const;
	virtual void OffsetOp(Point p);
	virtual bool ExcludeClipOp(const Rect& r);
	virtual void EndOp();


	virtual void SysDrawImageOp(int x, int y, const Image& img, Color color);
	virtual void SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color);
	virtual void DrawRectOp(int x, int y, int cx, int cy, Color color);

	virtual void DrawTextOp(int x, int y, int angle, const wchar *text, Font font, Color ink, int n, const int *dx);

	virtual void DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color);
	virtual void DrawDrawingOp(const Rect& target, const Drawing& w);
	virtual void DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor);
	virtual void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color);
	virtual void DrawPaintingOp(const Rect& target, const Painting& w);
	virtual void DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count, const int *subpolygon_counts, int scc, const int *disjunct_polygon_counts, int dpcc, Color color, int width, Color outline, uint64 pattern, Color doxor);
	virtual void DrawPolyPolylineOp(const Point *vertices, int vertex_count, const int *counts, int count_count, int width, Color color, Color doxor);

	virtual void PutImage(Point p, const Image& m, const Rect& src) = 0;
	virtual void PutRect(const Rect& r, Color color) = 0;
};

struct TestDraw : FDraw {
	Draw *draw;

	virtual void PutImage(Point p, const Image& m, const Rect& src);
	virtual void PutRect(const Rect& r, Color color);
};

#endif
