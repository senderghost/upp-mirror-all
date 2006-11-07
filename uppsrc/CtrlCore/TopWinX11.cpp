#include "CtrlCore.h"
#pragma hdrstop

#define LLOG(x)  // LOG(x)

#ifdef PLATFORM_X11

void TopWindow::SyncSizeHints()
{
	Size min = GetMinSize();
	Size max = GetMaxSize();
	if(!sizeable)
		min = max = GetRect().Size();
	if(min != xminsize || max != xmaxsize) {
		xminsize = min;
		xmaxsize = max;
		XSizeHints sh;
		size_hints->min_width = min.cx;
		size_hints->min_height = min.cy;
		size_hints->max_width = max.cx;
		size_hints->max_height = max.cy;
		size_hints->flags = PMinSize|PMaxSize;
		Window w = GetWindow();
		if(w)
			XSetWMNormalHints(Xdisplay, w, &sh);
	}
}

void TopWindow::EndIgnoreTakeFocus()
{
	ignoretakefocus = false;
}

void TopWindow::EventProc(XWindow& w, XEvent *event)
{
	Ptr<Ctrl> this_ = this;
	if(event->type == ClientMessage)
		if(event->xclient.format == 32 && event->xclient.message_type)
			if(event->xclient.message_type == XAtom("WM_PROTOCOLS")) {
				Atom a = event->xclient.data.l[0];
				if(a == XAtom("WM_DELETE_WINDOW") && IsEnabled()) {
					LLOG("DELETE_WINDOW " << Name());
					WhenClose();
					return;
				}
				if(a == XAtom("WM_TAKE_FOCUS")) {
					LLOG("TAKE_FOCUS serial: " << event->xclient.serial);
					Xeventtime = event->xclient.data.l[1];
					TakeFocus();
					return;
				}
			}
	if(this_) Ctrl::EventProc(w, event);
	if(this_) SyncSizeHints();
}

void TopWindow::DefSyncTitle()
{
	if(title2 == title)
		return;
	title2 = title;
	if(IsOpen() && GetWindow()) {
		Window w = GetWindow();
		XStoreName(Xdisplay, w, title.ToString());
		XSetIconName(Xdisplay, w, title.ToString());
		String utf8title = FromUnicode(title, CHARSET_UTF8);
		XChangeProperty(Xdisplay, w, XAtom("_NET_WM_NAME"), XAtom("UTF8_STRING"),
		                8, PropModeReplace,
		                (const unsigned char *)~utf8title, utf8title.GetLength());
		XChangeProperty(Xdisplay, w, XAtom("_NET_WM_ICON_NAME"), XAtom("XA_UTF8_STRING"),
		                8, PropModeReplace,
		                (const unsigned char *)~utf8title, utf8title.GetLength());
	}
}

void TopWindow::SyncTitle()
{
	LLOG("SyncTitle: " << title);
	KillTimeCallback(TIMEID_DEFSYNCTITLE);
	SetTimeCallback(0, THISBACK(DefSyncTitle), TIMEID_DEFSYNCTITLE);
}

void TopWindow::SyncCaption()
{
	LLOG("SyncCaption");
	SyncTitle();
	if(IsOpen() && GetWindow()) {
		unsigned long wina[5];
		int n = 0;
		Window w = GetWindow();
		if(GetOwner())
			wina[n++] = XAtom("_NET_WM_WINDOW_TYPE_DIALOG");
		if(tool)
			wina[n++] = XAtom("_NET_WM_WINDOW_TYPE_TOOLBAR");
		wina[n++] = XAtom("_NET_WM_WINDOW_TYPE_NORMAL");
		XChangeProperty(Xdisplay, GetWindow(), XAtom("_NET_WM_WINDOW_TYPE"), XAtom("ATOM"), 32,
		                PropModeReplace, (const unsigned char *)wina, n);
		n = 0;
		if(topmost)
			wina[n++] = XAtom("_NET_WM_STATE_ABOVE");
		if(state == MAXIMIZED) {
			wina[n++] = XAtom("_NET_WM_STATE_MAXIMIZED_HORZ");
			wina[n++] = XAtom("_NET_WM_STATE_MAXIMIZED_VERT");
		}
		XChangeProperty(Xdisplay, GetWindow(), XAtom("_NET_WM_STATE"), XAtom("ATOM"), 32,
		                PropModeReplace, (const unsigned char *)wina, n);
		wm_hints->flags = InputHint|WindowGroupHint|StateHint;
		wm_hints->initial_state = NormalState;
		wm_hints->input = XTrue;
		Ctrl *owner = GetOwner();
		wm_hints->window_group = owner ? owner->GetWindow() : w;
		if(!icon.IsEmpty()) {
			Size isz = icon.GetSize();
			int len = 2 + isz.cx * isz.cy;
			Buffer<unsigned long> data(len);
			unsigned long *t = data;
			*t++ = isz.cx;
			*t++ = isz.cy;
			for(int y = 0; y < isz.cy; y++) {
				const RGBA *q = icon[y];
				for(int x = isz.cx; x--;) {
					*t++ = ((dword)q->a << 24) |
					       (dword)q->b | ((dword)q->g << 8) | ((dword)q->r << 16);
					q++;
				}
			}
			XChangeProperty(Xdisplay, w, XAtom("_NET_WM_ICON"), XA_CARDINAL, 32, PropModeReplace,
			                (const unsigned char *)~data, len);
		}
		XSetWMHints(Xdisplay, w, wm_hints);
	}
}

void TopWindow::CenterRect(Ctrl *owner)
{
	SetupRect();
	if(owner && center == 1 || center == 2) {
		Size sz = GetRect().Size();
		Rect r, wr;
		wr = Ctrl::GetWorkArea();
		Rect fm = windowFrameMargin;
		if((fm.left|fm.right|fm.top|fm.bottom) == 0)
			fm = Rect(8, 32, 8, 8);
		if(center == 1)
			r = owner->GetRect();
		else
			r = wr;
		Point p = r.CenterPos(sz);
		r = RectC(p.x, p.y, sz.cx, sz.cy);
		wr.left += fm.left;
		wr.right -= fm.right;
		wr.top += fm.top;
		wr.bottom -= fm.bottom;
		if(r.top < wr.top) {
			r.bottom += wr.top - r.top;
			r.top = wr.top;
		}
		if(r.bottom > wr.bottom)
			r.bottom = wr.bottom;
		minsize.cx = min(minsize.cx, r.GetWidth());
		minsize.cy = min(minsize.cy, r.GetHeight());
		SetRect(r);
	}
}

void TopWindow::Open(Ctrl *owner)
{
	if(dokeys && (!GUI_AKD_Conservative() || GetAccessKeysDeep() <= 1))
		DistributeAccessKeys();
	UsrLogT(3, "OPEN " + Desc(this));
	LLOG("OPEN " << Name() << " owner: " << ::Name(owner));
	IgnoreMouseUp();
	CenterRect(owner);
	LLOG("Open NextRequest " << NextRequest(Xdisplay));
	Create(owner, false, false);
	xminsize.cx = xmaxsize.cx = Null;
	title2.Clear();
	LLOG("SyncCaption");
	SyncCaption();
	LLOG("SyncSizeHints");
	size_hints->flags = 0;
	SyncSizeHints();
	Rect r = GetRect();
	size_hints->x = r.left;
	size_hints->y = r.top;
	size_hints->width = r.Width();
	size_hints->height = r.Height();
	size_hints->win_gravity = StaticGravity;
	size_hints->flags |= PPosition|PSize|PWinGravity;
	if(owner) {
		ASSERT(owner->IsOpen());
		LLOG("XSetTransientForHint");
		XSetTransientForHint(Xdisplay, GetWindow(), owner->GetWindow());
	}
	LLOG("XSetWMNormalHints");
	XSetWMNormalHints(Xdisplay, GetWindow(), size_hints);
	Atom protocols[2];
	protocols[0] = XAtom("WM_DELETE_WINDOW");
	protocols[1] = XAtom("WM_TAKE_FOCUS");
	LLOG("XSetWMProtocols");
	XSetWMProtocols(Xdisplay, GetWindow(), protocols, 2);
	String x = GetExeTitle().ToString();
	const char *progname = ~x;
	class_hint->res_name = (char *)progname;
	class_hint->res_class = (char *)progname;
	XSetClassHint(Xdisplay, GetWindow(), class_hint);
	LLOG("WndShow(" << visible << ")");
	WndShow(visible);
	if(visible) {
		XEvent e;
		LLOG("XWindowEvent");
		XWindowEvent(Xdisplay, top->window, VisibilityChangeMask, &e);
		ignoretakefocus = true;
		SetTimeCallback(500, THISBACK(EndIgnoreTakeFocus));
		LLOG("SetWndFocus");
		SetWndFocus();
		for(int i = 0; i < 50; i++) {
			if(XCheckTypedWindowEvent(Xdisplay, top->window, FocusIn, &e)) {
				ProcessEvent(&e);
				if(e.xfocus.window = top->window)
					break;
			}
			Sleep(10);
		}
	}
	LLOG(">Open NextRequest " << NextRequest(Xdisplay));
	LLOG(">OPENED " << Name());
	PlaceFocus();
	StateH(OPEN);
	Vector<int> fe = GetPropertyInts(top->window, XAtom("_NET_FRAME_EXTENTS"));
	if(fe.GetCount() >= 4) {
		windowFrameMargin.left = max(windowFrameMargin.left, fe[0]);
		windowFrameMargin.right = max(windowFrameMargin.right, fe[1]);
		windowFrameMargin.top = max(windowFrameMargin.top, fe[2]);
		windowFrameMargin.bottom = max(windowFrameMargin.bottom, fe[3]);
	}
}

void TopWindow::Open()
{
	Open(GetActiveWindow());
}

void TopWindow::OpenMain()
{
	Open(NULL);
}

void TopWindow::Minimize(bool)
{
	state = MINIMIZED;
	XIconifyWindow(Xdisplay, GetWindow(), Xscreenno);
}

void TopWindow::Maximize(bool effect)
{
	state = MAXIMIZED;
}

void TopWindow::Overlap(bool effect)
{
	state = OVERLAPPED;

}

TopWindow& TopWindow::TopMost(bool b, bool)
{
	topmost = b;
	return *this;
}

bool TopWindow::IsTopMost() const
{
	return topmost;
}

#endif
