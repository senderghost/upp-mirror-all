#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

#ifdef flatMAIN

using namespace Upp;

void Tesselate(Vector<Vector<Pointf>>& shape, Vector<Pointf>& vertex, Vector<Tuple<int, int, int>>& triangle);

struct MyApp : TopWindow {
	Vector<Vector<Pointf>> polygon;
	
	void Paint(Draw& w) {
		{
			ImageBuffer ib(GetSize());
			BufferPainter iw(ib);
			iw.Clear(White());
			for(const auto& c : polygon) {
				bool first = true;
				for(const Pointf& p : c) {
					if(first)
						iw.Move(p);
					else
						iw.Line(p);
					first = false;
				}
				iw.Close();
			}
			iw.Fill(Gray());
			
			Vector<Pointf> vertex;
			Vector<Tuple<int, int, int>> triangle;
			Tesselate(polygon, vertex, triangle);
			
			DDUMP(vertex.GetCount());
			
			for(auto& t : triangle) {
				DDUMP(t.a);
				DDUMP(t.b);
				DDUMP(t.c);
				iw.Move(vertex[t.a]);
				iw.Line(vertex[t.b]);
				iw.Line(vertex[t.c]);
				iw.Close();
				iw.Stroke(2, LtRed());
			}
			
			w.DrawImage(0, 0, ib);
		}
	}

	MyApp();
};

MyApp::MyApp()
{
	Vector<Pointf>& c = polygon.Add();
#if 1
	c.Add(Pointf(10, 10));
	c.Add(Pointf(400, 10));
	c.Add(Pointf(10, 400));
	c.Add(Pointf(400, 400));
#else
	for(int i = 0; i < 360; i += 20) {
		c.Add(300 * Polar(M_2PI * i / 360.0) + Pointf(350, 350));
		c.Add(200 * Polar(M_2PI * (i + 10) / 360.0) + Pointf(350, 350));
	}
#endif
}

GUI_APP_MAIN
{
	MyApp().Run();
}

#endif