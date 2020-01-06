#include <CtrlCore/CtrlCore.h>

#ifdef GUI_GTK

namespace Upp {

#define LLOG(x)   //   DLOG(x)

Ptr<Ctrl> Ctrl::grabwindow;
Ptr<Ctrl> Ctrl::grabpopup;

GdkSeat *Ctrl::GetSeat()
{
	return gdk_display_get_default_seat(gdk_display_get_default());
}

GdkDevice *Ctrl::GetMouseDevice()
{
	return gdk_seat_get_pointer(GetSeat());
}

bool Ctrl::MouseIsGrabbed()
{
	return gdk_display_device_is_grabbed(gdk_display_get_default(), GetMouseDevice());
}

void Ctrl::StopGrabPopup()
{
	if(grabpopup && MouseIsGrabbed()) {
		gdk_seat_ungrab(GetSeat());
		grabpopup = NULL;
	}
}

void Ctrl::StartGrabPopup()
{
	if(activePopup.GetCount() && !grabpopup) {
		Ctrl *w = activePopup[0];
		if(w && w->IsOpen()) {
			ReleaseWndCapture0();
			if(gdk_seat_grab(GetSeat(), w->gdk(), GDK_SEAT_CAPABILITY_ALL_POINTING, true, NULL, NULL, NULL, 0) == GDK_GRAB_SUCCESS)
				grabpopup = w;
		}
	}
}

bool Ctrl::SetWndCapture()
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("SetWndCapture " << Name());
	if(!IsOpen())
		return false;
	StopGrabPopup();
	ReleaseWndCapture();
	if(gdk_seat_grab(GetSeat(), gdk(), GDK_SEAT_CAPABILITY_ALL_POINTING, true, NULL, NULL, NULL, 0) == GDK_GRAB_SUCCESS) {
		grabwindow = this;
		return true;
	}
	return false;
}

bool Ctrl::ReleaseWndCapture0()
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("ReleaseWndCapture");
	if(grabwindow) {
		gdk_seat_ungrab(GetSeat());
		grabwindow = NULL;
		StartGrabPopup();
		return true;
	}
	return false;
}

bool Ctrl::ReleaseWndCapture()
{
	return ReleaseWndCapture0();
}

bool Ctrl::HasWndCapture() const
{
	GuiLock __;
	return this == grabwindow && grabwindow->IsOpen() && MouseIsGrabbed();
}

void Ctrl::CaptureSync()
{
	if(grabwindow && grabwindow->IsOpen() && !MouseIsGrabbed() &&
	   gdk_seat_grab(GetSeat(), grabwindow->gdk(), GDK_SEAT_CAPABILITY_ALL_POINTING, true, NULL, NULL, NULL, 0) != GDK_GRAB_SUCCESS)
		grabwindow = NULL;
}

#if 0
void Ctrl::StopGrabPopup()
{
	if(grabpopup && gdk_pointer_is_grabbed()) {
		gdk_pointer_ungrab(CurrentTime);
		grabpopup = NULL;
	}
}

void Ctrl::StartGrabPopup()
{
	if(activePopup.GetCount() && !grabpopup) {
		Ctrl *w = activePopup[0];
		if(w && w->IsOpen()) {
			ReleaseWndCapture0();
			static GdkCursor *NormalArrowCursor;
			ONCELOCK {
				NormalArrowCursor = gdk_cursor_new(GDK_LEFT_PTR);
			}
			if(gdk_pointer_grab(w->gdk(), FALSE,
							    GdkEventMask(GDK_BUTTON_RELEASE_MASK|GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK),
							    NULL, NormalArrowCursor, CurrentTime) == GDK_GRAB_SUCCESS)
				grabpopup = w;
		}
	}
}

bool Ctrl::SetWndCapture()
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("SetWndCapture " << Name());
	if(!IsOpen())
		return false;
	StopGrabPopup();
	ReleaseWndCapture();
	if(gdk_pointer_grab(gdk(), FALSE,
					    GdkEventMask(GDK_BUTTON_RELEASE_MASK|GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK),
					    NULL, NULL, CurrentTime) == GDK_GRAB_SUCCESS) {
		grabwindow = this;
		return true;
	}
	return false;
}

bool Ctrl::ReleaseWndCapture0()
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("ReleaseWndCapture");
	if(grabwindow) {
		gdk_pointer_ungrab(CurrentTime);
		grabwindow = NULL;
		StartGrabPopup();
		return true;
	}
	return false;
}

bool Ctrl::ReleaseWndCapture()
{
	return ReleaseWndCapture0();
}

bool Ctrl::HasWndCapture() const
{
	GuiLock __;
	return this == grabwindow && grabwindow->IsOpen() && gdk_pointer_is_grabbed();
}

void Ctrl::CaptureSync()
{
	if(grabwindow && grabwindow->IsOpen() && !gdk_pointer_is_grabbed()) {
		if(gdk_pointer_grab(grabwindow->gdk(), FALSE,
		                    GdkEventMask(GDK_BUTTON_RELEASE_MASK|GDK_BUTTON_PRESS_MASK|GDK_POINTER_MOTION_MASK),
		                    NULL, NULL, CurrentTime) != GDK_GRAB_SUCCESS) {
			grabwindow = NULL;
		}
	}
}
#endif

}

#endif
