#ifndef _GLCamera_GLCamera_h
#define _GLCamera_GLCamera_h

#include <CtrlLib/CtrlLib.h>
#include <GLCtrl/GLCtrl.h>
#include <GLDraw/GLDraw.h>

using namespace Upp;

class GLCamera : public TopWindow {
public:
	virtual void MouseMove(Point p, dword keyflags);

	GLCtrl view;

	GLCamera();
};

void InitScene();
void PaintScene(Size sz);

void mouse_move(double xpos, double ypos);
void mouse_scroll(double xoffset, double yoffset);

#endif
