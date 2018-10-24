#include <CtrlLib/CtrlLib.h>
#include <GLDraw/GLDraw.h>
#include <GLCtrl/GLCtrl.h>

using namespace Upp;

Image image;

void GeomTest(Draw& w, Size sz)
{
	w.DrawRect(sz, White());
	static const int d[] = { PEN_NULL, PEN_SOLID, PEN_DASH, PEN_DOT, PEN_DASHDOT, PEN_DASHDOTDOT, 1, 2, 3, 10 };
	for(int i = 0; i < __countof(d); i++) {
		w.DrawLine(10, i * 10, 200, i * 10, d[i], Red());
		w.DrawLine(300, i * 10, 400, i * 10 + 15, d[i], Red());
		w.DrawLine(450 + i * 10, 10, 450 + i * 10, 200, d[i], Red());
	}

	Point points[12][2][4];
	int subpolygon_counts[12][2];
	int disjunct_counts[12];
	Point lpoints[12][5];
	int lcounts[12][2];
	Pointf center(300, 300);
	static const double out_delta = 2 * M_PI / 24;
	static const double in_delta = 2 * M_PI / 48;
	for(int i = 0; i < 12; i++) {
		double angle = i * 2 * M_PI / 12;
		points[i][0][0] = Polar(center, 200, angle);
		points[i][0][1] = Polar(center, 120, angle - out_delta);
		points[i][0][2] = Polar(center, 40, angle);
		points[i][0][3] = Polar(center, 120, angle + out_delta);
		points[i][1][0] = Polar(center, 160, angle);
		points[i][1][1] = Polar(center, 120, angle + in_delta);
		points[i][1][2] = Polar(center, 80, angle);
		points[i][1][3] = Polar(center, 120, angle - in_delta);
		subpolygon_counts[i][0] = 4;
		subpolygon_counts[i][1] = 4;
		disjunct_counts[i] = subpolygon_counts[i][0] + subpolygon_counts[i][1];
		
		lpoints[i][0] = Polar(center, 260, angle + in_delta);
		lpoints[i][1] = Polar(center, 230, angle);
		lpoints[i][2] = Polar(center, 260, angle - in_delta);
		lcounts[i][0] = 3;
		lpoints[i][3] = Polar(center, 280, angle + in_delta);
		lpoints[i][4] = Polar(center, 280, angle - in_delta);
		lcounts[i][1] = 2;
	}
	w.DrawPolyPolyPolygon(points[0][0], sizeof(points) / sizeof(Point),
		subpolygon_counts[0], sizeof(subpolygon_counts) / sizeof(int),
		disjunct_counts, sizeof(disjunct_counts) / sizeof(int),
		LtBlue(), 4, LtRed(), I64(0xF0F0F0F00F0F0F0F));
	w.DrawPolyPolyline(lpoints[0], sizeof(lpoints) / sizeof(Point),
		lcounts[0], sizeof(lcounts) / sizeof(int),
		4, Color(0, 192, 0));
	
	w.DrawRect(sz.cx - 200, sz.cy - 100, 200, 100, Yellow());
	w.DrawEllipse(sz.cx - 200, sz.cy - 100, 200, 100, Gray(), 3, LtBlue());
	w.DrawEllipse(0, sz.cy - 100, 150, 100, Gray(), PEN_DASHDOTDOT, LtBlue());

	{
		Pointf center(sz.cx - 320, 300);
		for(int i = 0; i < 13; i++) {
			double angle = (i - 3) * M_PI / 6;
			Pointf box_center = Polar(center, 250, angle);
			Size radius(60, 20);
			Rect box(Point(box_center), Size(1, 1));
			box.Inflate(radius);
			w.DrawRect(box, Yellow());
			for(int j = 0; j < 12; j++) {
				double ang2 = j * M_PI / 6;
				Sizef hand = Polar(Pointf(0, 0), 1, ang2);
				Point h1(box_center + Sizef(radius) * hand);
				Point h2(box_center + Sizef(radius) * 0.7 * hand);
				w.DrawLine(h1, h2, 1, LtBlue());
			}
			Sizef hand = Polar(Pointf(0, 0), 1, angle);
			w.DrawArc(box, Point(box_center + radius * hand), box.TopCenter(), PEN_DASHDOT, LtRed());
		}
	}
}

struct OpenGLExample : GLCtrl {
	Point point;
	
	TimeCallback cb;
	
	OpenGLExample() {
//		cb.Set(-4, [=] { Refresh(); });
		SetMSAA(4);
	}
	
	virtual void GLPaint()
	{

		Size sz = GetSize();

		GLDraw w;
		
		w.Init(sz);

		w.Flush();
		
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		static GLVertexData mesh;
		/*ONCELOCK*/ {
			Vector<Vector<Pointf>> polygon;
			Vector<Pointf>& c = polygon.Add();
/*			for(int i = 0; i < 360; i += 20) {
				c.Add(300 * Polar(M_2PI * i / 360.0));
				c.Add(200 * Polar(M_2PI * (i + 10) / 360.0));
			}
*/
			for(int pass = 0; pass < 2; pass++) {
				Vector<Pointf>& c = polygon.Add();
				double rot = msecs() / 50000.0;
				double amp = 1;
				for(int i = 0; i < 360; i += 2) {
					double f = pass ? 0.8 : 1;
					c.Add(amp * f * 300 * Polar(M_2PI * i / 360.0 + rot));
					c.Add(amp * f * 200 * Polar(M_2PI * (i + 1) / 360.0 + rot));
				}
			}


			glFinish(); TIMING("Create mesh");

			GLPolygons(mesh, polygon);
			
			glFinish();
		}

		GLContext2D dd(sz);
		
		static GLVertexData lmesh, lmesh2;
		static GLTexture tex;
		ONCELOCK {
			Vector<Vector<Pointf>> line;
			line.Add();
			for(int i = 0; i < 4 * sz.cx; i += 5) {
				line.Top().Add(Pointf(i, 200 * sin(M_2PI * i / 360.0)));
			}
			GLPolylines(lmesh, line);

			line.Clear();
			line.Add();
			for(int i = 0; i < 360; i += 120)
				line.Top().Add(300 * Polar(M_2PI * i / 360.0));
			line.Top().Add(line.Top()[0]);
			
			Vector<Vector<Pointf>> lines;
			Vector<double> dash;
			dash << 10 << 20 << 30;
			DashPolyline(lines, line.Top(), dash, 0);
			
			GLPolylines(lmesh2, lines);
	
			Size sz(100, 100);
			GLTextureDraw w(sz, 0);
			GLContext2D dd(sz);
			GLDrawEllipse(dd, Sizef(50, 50), Sizef(50, 50), Black(), 0, Green());
			GLDrawEllipse(dd, Sizef(50, 50), Sizef(20, 20), LtRed(), 0, Blue());
			tex = w;
		}
		
		{ glFinish(); RTIMING("DrawEllipse");
		GLDrawEllipse(dd, Sizef(sz) / 2, Sizef(sz) / 2, Blue(), 4, LtGreen());
		glFinish();}
		{ glFinish(); RTIMING("DrawPolygon");
		// GLDrawPolygons(dd, point, mesh, Sizef(2, 1), Blue(), 0.7);
		glFinish();}
		{ glFinish(); RTIMING("Draw Image");
//		GLDrawImage(dd, RectC(point.x, point.y, 400, 400), CtrlImg::exclamation(), 1);
		glFinish();}
		
		GLDrawTexture(dd, RectC(point.x, point.y, 100, 100), tex);

		GLDrawPolylines(dd, Pointf(0, sz.cy / 3), lmesh, Sizef(1, 1), 12, Green());
		GLDrawPolylines(dd, Pointf(0, sz.cy / 2), lmesh, Sizef(1, 0.1), 12, Red());
		GLDrawPolylines(dd, Pointf(0, sz.cy / 2 + 300), lmesh, Sizef(2, 0.3), 12, Red());

		GLDrawPolylines(dd, Sizef(sz) / 2, lmesh2, Sizef(1, 1), 12, LtCyan());

		GLDrawTexture(dd, RectC(0, 200, 100, 100), tex, RectC(30, 30, 40, 40));
		
		GLTexture gtex = GetGlyphGLTextureCached(10, 'A', Serif(100), Red());
		Size tsz = gtex.GetSize();
		GLDrawTexture(dd, RectC(300, 20, tsz.cx, tsz.cy), gtex);
		
		GLDrawText(dd, Pointf(300, 120), 0, String("Hello world!").ToWString(), Serif(80), Blue());

		for(int angle = 0; angle < 360; angle += 30)
			GLDrawText(dd, Pointf(sz.cx / 2, sz.cy / 2), M_2PI * angle / 360, String("      angle " + AsString(angle)).ToWString(), Arial(40), LtRed());
		
		{
			DrawGL w(sz, 0.5);
			w.Clip(20, 20, 40, 40);
			w.DrawRect(10, 10, 100, 100, Yellow());
			w.DrawImage(10, 10, CtrlImg::information());
			w.End();
			w.DrawImage(100, 10, CtrlImg::information(), Black());
			w.DrawText(100, 100, "DrawGL 0.99!");
			w.DrawEllipse(100, 200, 100, 200, Green(), 3, Brown());
			
			for(int angle = 0; angle < 360; angle += 30)
				w.DrawLine(Point(100, 500), Point(100, 500) + Point(100 * Polar(M_2PI * angle / 360)), 20, LtGreen());
		}
		
		if(0) {
			DrawGL w(sz, 1);
			GeomTest(w, sz);
		}
	}


	virtual void MouseMove(Point p, dword) {
		point = p;
		Refresh();
	}
};

namespace Upp {
extern int max_texture_memory;
extern int max_texture_count;
};

#include <typeindex>

GUI_APP_MAIN
{
	max_texture_memory = 1024*1024*1024;
//	image = StreamRaster::LoadFileAny("C:/xxx/IMG_20180818_183724382.jpg");
//	image = CtrlImg::HelpCursor1();
//	DDUMP(image.GetSize());
//	Ctrl::GlobalBackPaint();

	TopWindow win;
	OpenGLExample gl1, gl2;
#if 0
	Splitter sp;
	gl1.SetFrame(InsetFrame());
	gl2.SetFrame(InsetFrame());
	sp.Add(gl2);
	sp.Add(gl1);
//	win.Add(gl2.HSizePos(10, 10).BottomPos(0, 500));
//	win.Add(gl1.HSizePos(10, 10).VSizePos(10, 500));
	win.Add(sp);
#else
	win.Add(gl1.SizePos());
#endif
	win.Sizeable().Zoomable();
	win.Open();
	win.Run();
}
