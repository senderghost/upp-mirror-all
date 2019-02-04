#include <CtrlLib/CtrlLib.h>
#include <plugin/earcut/earcut.h>
#include <Painter/Painter.h>

using namespace Upp;

Vector<Vector<Pointf>> TestData();

Vector<Vector<Pointf>> data;
Vector<Pointf>         pt;
Vector<int>            tri;
Pointf                 pt_min(1e30, 1e30);
Pointf                 pt_max(-1e30, -1e30);

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		DrawPainter iw(w, sz);
		iw.Clear(White());
		iw.Scale(sz.cx / (pt_max.x - pt_min.x), sz.cy / (pt_max.y - pt_min.y));
		iw.Offset(-pt_min);
		DDUMP(Pointf(sz.cx / (pt_max.x - pt_min.x), sz.cy / (pt_max.y - pt_min.y)));
#if 0
	for(auto& h: data) {
		bool first = 0;
		for(Pointf p : h) {
			if(first)
				iw.Move(p);
			else
				iw.Line(p);
		}
		iw.Close();
	}
	iw.Fill(LtBlue());
//	iw.Stroke(1, Red());
#else
		for(int i = 0; i < tri.GetCount(); i += 3) {
			iw.Move(pt[tri[i]]);
			iw.Line(pt[tri[i + 1]]);
			iw.Line(pt[tri[i + 2]]);
			DDUMP(pt[tri[i]]);
			DDUMP(pt[tri[i + 1]]);
			DDUMP(pt[tri[i + 2]]);
			DLOG("=============");
			iw.Fill(LtBlue());
			iw.Stroke(1, Red());
		}
#endif
	}
};

GUI_APP_MAIN
{
//	data = TestData();

	data.Add({{100, 0}, {100, 100}, {0, 100}, {0, 0}});
	data.Add({{75, 25}, {75, 75}, {25, 75}, {25, 25}});

	tri = EarCut(data);
	
	DDUMP(tri.GetCount());
	DDUMPC(tri);
	
	for(auto& h: data)
		for(Pointf p : h) {
			pt_min.x = min(pt_min.x, p.x);
			pt_min.y = min(pt_min.y, p.y);
			pt_max.x = max(pt_max.x, p.x);
			pt_max.y = max(pt_max.y, p.y);
			pt.Add(p);
		}
	
	DDUMP(pt.GetCount());
	DDUMP(pt_min);
	DDUMP(pt_max);

	Pointf scale = 1000 * Pointf(1 / (pt_max.x - pt_min.x), 1 / (pt_max.y - pt_min.y));
	
	DDUMP(scale);
	
//	for(auto& p : pt)
//		p = scale * (p - pt_min);
	
	MyApp().Run();
}
