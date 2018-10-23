#include <CtrlLib/CtrlLib.h>
#include <GLPainter/GLPainter.h>
#include <GLCtrl/GLCtrl.h>

using namespace Upp;

Image image;

struct OpenGLExample : GLCtrl {
	Point point;
	
	TimeCallback cb;
	
	OpenGLExample() {
		cb.Set(-4, [=] { Refresh(); });
		SetMSAA(8);
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
			for(int i = 0; i < 360; i += 120) {
				line.Top().Add(300 * Polar(M_2PI * i / 360.0));
			}
			line.Top().Add(line.Top()[0]);
			GLPolylines(lmesh2, line);
	
			Size sz(100, 100);
			GLTextureDraw w(sz, 4);
			GLContext2D dd(sz);
			GLDrawEllipse(dd, Sizef(50, 50), Sizef(50, 50), Black(), 0, Green(), 0.5);
			GLDrawEllipse(dd, Sizef(50, 50), Sizef(20, 20), LtRed(), 0, Blue(), 0.5);
			tex = w;
		}
		
		{ glFinish(); RTIMING("DrawEllipse");
		GLDrawEllipse(dd, Sizef(sz) / 2, Sizef(sz) / 2, Blue(), 4, LtGreen(), 0.5);
		glFinish();}
		{ glFinish(); RTIMING("DrawPolygon");
//		GLDrawPolygon(dd, point, mesh, Sizef(2, 1), Blue(), 0.7);
		glFinish();}
		{ glFinish(); RTIMING("Draw Image");
//		GLDrawImage(dd, RectC(point.x, point.y, 400, 400), CtrlImg::exclamation(), 1);
		glFinish();}
		
		GLDrawTexture(dd, RectC(point.x, point.y, 100, 100), tex, 1);

		GLDrawPolylines(dd, Pointf(0, sz.cy / 3), lmesh, Sizef(1, 1), 12, Green(), 1);
		GLDrawPolylines(dd, Pointf(0, sz.cy / 2), lmesh, Sizef(1, 0.1), 12, Red(), 0.6);
		GLDrawPolylines(dd, Pointf(0, sz.cy / 2 + 300), lmesh, Sizef(2, 0.3), 12, Red(), 0.6);

		GLDrawPolylines(dd, Sizef(sz) / 2, lmesh2, Sizef(1, 1), 12, LtCyan(), 0.7);

		GLDrawTexture(dd, RectC(0, 200, 100, 100), tex, RectC(30, 30, 40, 40), 1);
		
		GLTexture gtex = GetGlyphGLTextureCached(10, 'A', Serif(100), Red());
		Size tsz = gtex.GetSize();
		GLDrawTexture(dd, RectC(300, 20, tsz.cx, tsz.cy), gtex, 1);
		
		GLDrawText(dd, Pointf(300, 120), 0, String("Hello world!").ToWString(), Serif(80), Blue());

		for(int angle = 0; angle < 360; angle += 30)
			GLDrawText(dd, Pointf(sz.cx / 2, sz.cy / 2), M_2PI * angle / 360, String("      angle " + AsString(angle)).ToWString(), Arial(40), Blue());
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
	Splitter sp;
	gl1.SetFrame(InsetFrame());
	gl2.SetFrame(InsetFrame());
	sp.Add(gl2);
	sp.Add(gl1);
//	win.Add(gl2.HSizePos(10, 10).BottomPos(0, 500));
//	win.Add(gl1.HSizePos(10, 10).VSizePos(10, 500));
	win.Add(sp);
	win.Sizeable().Zoomable();
	win.Open();
	win.Run();
}
