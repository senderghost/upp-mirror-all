#include "GLCamera.h"

#include <GLDraw/GLDraw.h>

GLCamera::GLCamera()
{
	Add(view.SizePos());
	view.RedirectMouse(this);
	view.WhenGLPaint << [=] {
		ONCELOCK {
			Vector<Vector<float>> elevation;
			
			Size sz(256, 256);
			Point c = sz / 2;
			for(int i = 0; i < sz.cx; i++)
				for(int j = 0; j < sz.cy; j++) {
					double d = (i - c.x) * (i - c.y) + (j - c.x) * (j - c.y);
					elevation.At(i).At(j) = 10 * sin(d * d / 5000);
				}

			terrain.SetTerrain(1, sz, elevation, DataImg::container());

//			terrain.Test();
		};

		terrain.PaintScene(GetSize());
	};
}

void GLCamera::MouseMove(Point p, dword keyflags)
{
	terrain.mouse_move(p.x, p.y);
	view.Refresh();
}

void GLCamera::MouseWheel(Point p, int zdelta, dword keyflags)
{
	terrain.mouse_scroll(0, sgn(zdelta));
	view.Refresh();
}

GUI_APP_MAIN
{
	GLCamera().Run();
}
