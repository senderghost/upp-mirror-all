#include <CtrlCore/CtrlCore.h>

#ifdef GUI_GTK

//#include <winnls.h>

//#include "imm.h"

NAMESPACE_UPP

#define LLOG(x)  // LOG(x)

bool  GetShift() { return false; }
bool  GetCtrl() { return false; }
bool  GetAlt() { return false; }
bool  GetCapsLock() { return false; }
bool  GetMouseLeft() { return false; }
bool  GetMouseRight() { return false; }
bool  GetMouseMiddle() { return false; }
Point GetMousePos() { return Point(0, 0); }

bool Ctrl::Proc(GdkEvent *event)
{
	DDUMP((int)event->type);
	switch(event->type) {
	case GDK_EXPOSE:
	case GDK_DAMAGE: {
		fullrefresh = false;
		GdkEventExpose *e = (GdkEventExpose *)event;
		SystemDraw w(gdk_cairo_create(top->window->window));
		painting = true;
		UpdateArea(w, RectC(e->area.x, e->area.y, e->area.width, e->area.height));
		cairo_destroy(w);
		painting = false;
		return true;
	}
	case GDK_MOTION_NOTIFY: {
		GdkEventMotion *e = (GdkEventMotion *)event;
		DispatchMouse(MOUSEMOVE, Point(e->x, e->y));
		DoCursorShape();
		return true;
	}
	case GDK_BUTTON_PRESS:
		DLOG("EndLoop!");
		EndLoop();
		return true;
	default:;
	}
	return false;
}

END_UPP_NAMESPACE

#endif
