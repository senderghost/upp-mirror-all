#include <CtrlCore/CtrlCore.h>

#ifdef GUI_GTK

NAMESPACE_UPP

#define LLOG(x)      DLOG(x)
#define LOGTIMING 0

#ifdef _DEBUG
#define LOGMESSAGES 0
#endif

#define ELOGW(x)  // RLOG(GetSysTime() << ": " << x) // Only activate in MT!
#define ELOG(x)   // RLOG(GetSysTime() << ": " << x)

Vector<Ctrl::Win> Ctrl::wins;

int        Ctrl::WndCaretTime;
bool       Ctrl::WndCaretVisible;

int Ctrl::FindCtrl(Ctrl *ctrl)
{
	for(int i = 0; i < wins.GetCount(); i++)
		if(wins[i].ctrl == ctrl)
			return i;
	return -1;
}

int Ctrl::FindGtkWindow(GtkWidget *gtk)
{
	for(int i = 0; i < wins.GetCount(); i++)
		if(wins[i].gtk == gtk)
			return i;
	return -1;
}

int Ctrl::FindGdkWindow(GdkWindow *gdk)
{
	for(int i = 0; i < wins.GetCount(); i++)
		if(wins[i].gdk == gdk)
			return i;
	return -1;
}

bool Ctrl::IsAlphaSupported()
{
	return false;
}

bool Ctrl::IsCompositedGui()
{
	return false;
}

Vector<Ctrl *> Ctrl::GetTopCtrls()
{
	GuiLock __;
	Vector<Ctrl *> h;
	for(int i = 0; i < wins.GetCount(); i++)
		h.Add(wins[i].ctrl);
	return h;
}

void  Ctrl::SetMouseCursor(const Image& image)
{
	GuiLock __;
	int64 id = image.GetSerialId();
	Ctrl *topctrl = NULL;
	Top *top = NULL;
	if(mouseCtrl)
		topctrl = mouseCtrl->GetTopCtrl();
	if(topctrl)
		top = topctrl->top;
	if(top && id != top->cursor_id) {
		top->cursor_id = id;
		int64 aux = image.GetAuxData();
		GdkCursor *c = NULL;
		if(aux)
			c = gdk_cursor_new((GdkCursorType)(aux - 1));
		else
		if(IsNull(image))
			c = gdk_cursor_new(GDK_BLANK_CURSOR);
		else {
			Point p = image.GetHotSpot();
			ImageGdk m;
			m.Set(image);
			GdkPixbuf *pb = m;
			if(pb)
				c = gdk_cursor_new_from_pixbuf(gdk_display_get_default(), pb, p.x, p.y);
		}
		if(c) {
			gdk_window_set_cursor(topctrl->gdk(), c);
			gdk_cursor_unref(c);
		}
	}
}

Ctrl *Ctrl::GetOwner()
{
	GuiLock __;
	return top ? top->owner : NULL;
}

Ctrl *Ctrl::GetActiveCtrl()
{
	GuiLock __;
	return focusCtrl ? focusCtrl->GetTopCtrl() : NULL;
}

// Vector<Callback> Ctrl::hotkey;

int Ctrl::RegisterSystemHotKey(dword key, Callback cb)
{
/*	ASSERT(key >= K_DELTA);
	int q = hotkey.GetCount();
	for(int i = 0; i < hotkey.GetCount(); i++)
		if(!hotkey[i]) {
			q = i;
			break;
		}
	hotkey.At(q) = cb;
	dword mod = 0;
	if(key & K_ALT)
		mod |= MOD_ALT;
	if(key & K_SHIFT)
		mod |= MOD_SHIFT;
	if(key & K_CTRL)
		mod |= MOD_CONTROL;
	
	return RegisterHotKey(NULL, q, mod, key & 0xffff) ? q : -1;*/
	return -1;
}

void Ctrl::UnregisterSystemHotKey(int id)
{
/*	if(id >= 0 && id < hotkey.GetCount()) {
		UnregisterHotKey(NULL, id);
		hotkey[id].Clear();
	}*/
}

void Ctrl::FocusSync()
{
	GuiLock __;
	if(focusCtrlWnd && gtk_window_is_active(focusCtrlWnd->gtk()))
		return;
	Ptr<Ctrl> focus = NULL;
	static Ctrl *ctrl;
	for(int i = 0; i < wins.GetCount(); i++)
		if(gtk_window_is_active((GtkWindow *)wins[i].gtk)) {
			focus = wins[i].ctrl;
			break;
		}
	if(focus != ctrl) {
		if(ctrl)
			ctrl->KillFocusWnd();
		ctrl = focus;
		if(ctrl)
			ctrl->SetFocusWnd();
	}
}

void Ctrl::PaintCaret(SystemDraw& w)
{
	GuiLock __;
	// LLOG("PaintCaret " << this << ", caretCtrl: " << caretCtrl << ", WndCaretVisible: " << WndCaretVisible);
	if(this == caretCtrl && WndCaretVisible)
		w.DrawRect(caretx, carety, caretcx, caretcy, InvertColor);
}

void Ctrl::SetCaret(int x, int y, int cx, int cy)
{
	GuiLock __;
	if(this == caretCtrl)
		RefreshCaret();
	caretx = x;
	carety = y;
	caretcx = cx;
	caretcy = cy;
	if(this == caretCtrl) {
		WndCaretTime = GetTickCount();
		RefreshCaret();
		AnimateCaret();
	}
}

void Ctrl::SyncCaret() {
	GuiLock __;
	if(focusCtrl != caretCtrl) {
		RefreshCaret();
		caretCtrl = focusCtrl;
		RefreshCaret();
	}
}

void  Ctrl::AnimateCaret()
{
	GuiLock __;
	int v = !(((GetTickCount() - WndCaretTime) / 500) & 1);
	if(v != WndCaretVisible) {
		RefreshCaret();
		WndCaretVisible = v;
	}
}

Rect Ctrl::GetWndScreenRect() const
{
	GuiLock __;
	if(top) {
		gint x, y;
		gdk_window_get_position(gdk(), &x, &y);
		gint width = gdk_window_get_width(gdk());
		gint height = gdk_window_get_height(gdk());
		return RectC(x, y, width, height);
	}
	return Null;
}

void Ctrl::WndShow0(bool b)
{
	GuiLock __;
	if(b)
		gtk_widget_show_now(top->window);
	else
		gtk_widget_hide(top->window);
}

bool Ctrl::IsWndOpen() const {
	GuiLock __;
	return top && top->window && top->window->window;
}

void Ctrl::SetAlpha(byte alpha)
{
	GuiLock __;
}

Rect Ctrl::GetWorkArea() const
{
	GuiLock __;
	return GetWorkArea(GetRect().TopLeft());
}

void Ctrl::GetWorkArea(Array<Rect>& rc)
{
	GuiLock __;
	GdkScreen *s = gdk_screen_get_default();
	int n = gdk_screen_get_n_monitors(s);
	rc.Clear();
	for(int i = 0; i < n; i++) {
		GdkRectangle r;
		gdk_screen_get_monitor_geometry(s, i, &r);  // TODO: Use WorkArea (for GTK 3.4)
		rc.Add(RectC(r.x, r.y, r.width, r.height));
	}
}

Rect Ctrl::GetWorkArea(Point pt)
{
	Array<Rect> rc;
	GetWorkArea(rc);
	for(int i = 0; i < rc.GetCount(); i++)
		if(rc[i].Contains(pt))
			return rc[i];
	return GetPrimaryWorkArea();
}

Rect Ctrl::GetVirtualWorkArea()
{
	Rect out = GetPrimaryWorkArea();
	Array<Rect> rc;
	GetWorkArea(rc);
	for(int i = 0; i < rc.GetCount(); i++)
		out |= rc[i];
	return out;
}

Rect Ctrl::GetVirtualScreenArea()
{
	GuiLock __;
	gint x, y, width, height;
	gdk_window_get_geometry(gdk_screen_get_root_window(gdk_screen_get_default()),
	                        &x, &y, &width, &height, NULL);
	return RectC(x, y, width, height);
}

Rect Ctrl::GetPrimaryWorkArea()
{
	Array<Rect> rc;
	GetWorkArea(rc);
	return rc.GetCount() ? rc[0] : RectC(0, 0, 0, 0);
}

Rect Ctrl::GetPrimaryScreenArea()
{
	return GetPrimaryWorkArea();
}

int Ctrl::GetKbdDelay()
{
	GuiLock __;
	return 500;
}

int Ctrl::GetKbdSpeed()
{
	GuiLock __;
	return 1000 / 32;
}

void Ctrl::SetWndForeground0()
{
	GuiLock __;
	if(top)
		gtk_window_present(gtk());
}

bool Ctrl::IsWndForeground() const
{
	GuiLock __;
	return top && gtk_window_is_active(gtk());
}

void Ctrl::WndEnable0(bool *b)
{
	GuiLock __;
	if(top)
		gtk_widget_set_sensitive(top->window, *b);
}

void Ctrl::SetWndFocus0(bool *b)
{
	GuiLock __;
	DLOG("SetWndFocus0 " << top);
	if(top) {
		DLOG("SetWndFocus0 DO " << top->window);
		DDUMP(gtk_widget_get_can_focus(top->window));
		gdk_window_focus(gdk(), gtk_get_current_event_time());
//		gtk_window_present(gtk());
		*b = true;
	}
}

bool Ctrl::HasWndFocus() const
{
	GuiLock __;
	return top && gtk_widget_is_focus(top->window);
}

void Ctrl::WndInvalidateRect(const Rect& r)
{
	GuiLock __;
	LLOG("WndInvalidateRect " << rect);
	gtk_widget_queue_draw_area(top->window, r.left, r.top, r.GetWidth(), r.GetHeight());
}

void  Ctrl::WndScrollView0(const Rect& r, int dx, int dy)
{
	GuiLock __;
	LLOG("ScrollView " << rect);
	WndInvalidateRect(r);
}

void Ctrl::WndSetPos0(const Rect& rect)
{
	GuiLock __;
	LLOG("WndSetPos0 " << rect);
	gtk_window_move(gtk(), rect.left, rect.top);
	gtk_window_resize(gtk(), rect.GetWidth(), rect.GetHeight());
}

void Ctrl::WndUpdate0r(const Rect& r)
{
	GuiLock __;
	LLOG("WndUpdate0r " << r);
	gtk_widget_draw(top->window, GdkRect(r));
	ProcessEvents();
	gdk_flush();
}

void Ctrl::WndUpdate0()
{
	GuiLock __;
	LLOG("WndUpdate0");
	gdk_window_process_updates(gdk(), TRUE);
	ProcessEvents();
	gdk_flush();
}

Rect Ctrl::GetDefaultWindowRect()
{
	GuiLock __; 
	Size sz = GetPrimaryWorkArea().GetSize();
	static int pos = min(sz.cx / 10, 50);
	pos += 10;
	int cx = sz.cx * 2 / 3;
	int cy = sz.cy * 2 / 3;
	if(pos + cx + 50 > sz.cx || pos + cy + 50 > sz.cy)
		pos = 0;
	return RectC(pos + 20, pos + 20, cx, cy);
}

ViewDraw::ViewDraw(Ctrl *ctrl)
{
	EnterGuiMutex();
	Ctrl *top = ctrl->GetTopCtrl();
	cr = gdk_cairo_create(top->gdk());
	Clipoff(ctrl->GetScreenView() - top->GetScreenRect().TopLeft());
}

ViewDraw::~ViewDraw()
{
	cairo_destroy(cr);
	LeaveGuiMutex();
}

Vector<WString> SplitCmdLine__(const char *cmd)
{
	Vector<WString> out;
	while(*cmd)
		if((byte)*cmd <= ' ')
			cmd++;
		else if(*cmd == '\"') {
			WString quoted;
			while(*++cmd && (*cmd != '\"' || *++cmd == '\"'))
				quoted.Cat(FromSystemCharset(String(cmd, 1)).ToWString());
			out.Add(quoted);
		}
		else {
			const char *begin = cmd;
			while((byte)*cmd > ' ')
				cmd++;
			out.Add(String(begin, cmd).ToWString());
		}
	return out;
}

END_UPP_NAMESPACE

#endif
