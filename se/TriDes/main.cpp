#include <CtrlLib/CtrlLib.h>

#define IMAGECLASS TridesImg
#define IMAGEFILE <TriDes/trides.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS TridesImg
#define IMAGEFILE <TriDes/trides.iml>
#include <Draw/iml_source.h>

using namespace Upp;

void Tri(Draw& w, Point p1, Point p2, Point p3)
{
}

typedef Point ColoredVertex;

/*struct ColoredVertex : Point, Moveable<ColoredVertex> {
	RGBA color;
};
*/

void DrawShape(Draw& w, const Array<ColoredVertex>& shape)
{
	for(int i = 0; i < shape.GetCount(); i++) {
		const Point& p0 = shape[i];
		int dist1 = INT_MAX;
		int dist2 = INT_MAX;
		int best1 = -1;
		int best2 = -1;
		
		for(int j = 0; j < shape.GetCount(); j++) {
			const Point& p1 = shape[j];
			int dist = Distance(Pointf(p0), Pointf(p1));
			if(j != i) {
				if(dist < dist1) {
					best2 = best1;
					dist2 = dist1;
					best1 = j;
					dist1 = dist;
				}
				else
				if(dist < dist2) {
					dist2 = dist;
					best2 = j;
				}
			}
		}
		
		if(best1 > 0 && best2 > 0) {
			DLOG("=============");
			DDUMP(best1);
			DDUMP(best2);
			DDUMP(i);
			w.DrawLine(shape[i], shape[best1]);
			w.DrawLine(shape[best1], shape[best2]);
			w.DrawLine(shape[best2], shape[i]);
		}
	}
}

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) {
		Array<ColoredVertex> shape;
		Image m = TridesImg::test();
		for(int x = 0; x < m.GetWidth(); x++)
			for(int y = 0; y < m.GetHeight(); y++) {
				if(m[y][x] == LtGreen())
					shape.Add(Pointf(4 * x, 4 * y));
			}
		Size sz = GetSize();
		w.DrawRect(sz, White());
		DrawShape(w, shape);
	}
};
		

GUI_APP_MAIN
{
	MyApp().Run();
}
