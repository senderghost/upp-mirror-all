#include "GLCamera.h"

#include <GLDraw/GLDraw.h>

GLCamera::GLCamera()
{
	Add(view.SizePos());
	view.RedirectMouse(this);
	view.WhenGLPaint << [=] {
		ONCELOCK {
			InitScene();
		};
//		GLDraw ww(GetSize());
//		ww.DrawRect(100, 100, 100, 100, Blue());
//		return;
#if 0
		LOG("HERE");
		Size sz = GetSize();
		
		{
			GLDraw w(sz);
			w.DrawText(500, 500, "Hello world!");
		}
#endif
		PaintScene(GetSize());
	};
}

void GLCamera::MouseMove(Point p, dword keyflags)
{
	mouse_move(p.x, p.y);
	view.Refresh();
}

void GLCamera::MouseWheel(Point p, int zdelta, dword keyflags)
{
	mouse_scroll(0, sgn(zdelta));
	view.Refresh();
}

GUI_APP_MAIN
{
	GLCamera().Run();
}
