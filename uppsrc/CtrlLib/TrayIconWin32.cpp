#include "CtrlLib.h"

#ifdef PLATFORM_WIN32
#ifndef PLATFORM_WINCE

#include <commdlg.h>
#include <cderr.h>
#include <ShellApi.h>

#endif
#endif

NAMESPACE_UPP


#ifdef PLATFORM_WIN32

#ifndef PLATFORM_WINCE
#define LLOG(x)

enum {
	UM_TASKBAR = WM_USER + 1024,
};

TrayIcon::TrayIcon()
{
	Create(NULL, WS_POPUP, 0, false, 0, 0);
	Ctrl::Hide();
	Zero(nid);
	nid.sz = IsWin2K() ? sizeof(NotifyIconNew) : sizeof(NotifyIconOld);
	nid.message = UM_TASKBAR;
	nid.hwnd = GetHWND();
	static int id;
	nid.id = ++id;
	visible = false;
	Show();
}

TrayIcon::~TrayIcon()
{
	Hide();
	if(nid.icon)
		DestroyIcon(nid.icon);
}

void TrayIcon::Notify(dword msg)
{
	if(visible) {
		nid.flags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
		if(nid.icon)
			DestroyIcon(nid.icon);
		nid.icon = IconWin32(icon);
		int len = min(tip.GetLength(), 60);
		memcpy(nid.tip, tip, len);
		nid.tip[len] = 0;
		VERIFY(Shell_NotifyIcon(msg, (NOTIFYICONDATA *)&nid));
    }
}

void TrayIcon::Message(int type, const char *title, const char *text, int timeout)
{
	if(!IsWin2K())
	    return;
	nid.flags = 0x10;
	*nid.info = *nid.title = 0;
	if(text) {
		memcpy(nid.info, text, min((int)strlen(text), 255) + 1);
		nid.info[255] = 0;
	}
	if(title) {
		memcpy(nid.title, title, min((int)strlen(title), 63) + 1);
		nid.title[63] = 0;
	}
	nid.infoflags = type;
	nid.timeout = minmax(timeout, 10, 30) * 1000;
	Shell_NotifyIcon(NIM_MODIFY, (NOTIFYICONDATA *)&nid);
}

void TrayIcon::Show(bool b)
{
	if(b == visible)
		return;
	if(visible)
		Notify(NIM_DELETE);
	visible = b;
	if(visible)
		Notify(NIM_ADD);
}

TrayIcon& TrayIcon::Icon(const Image &img)
{
	icon = img;
	Notify(NIM_MODIFY);
	return *this;
}

TrayIcon& TrayIcon::Tip(const char *text)
{
	tip = text;
	Notify(NIM_MODIFY);
	return *this;
}

void TrayIcon::Menu(Bar& bar)
{
	WhenBar(bar);
}

void TrayIcon::LeftDown()
{
	WhenLeftDown();
}

void TrayIcon::LeftUp()
{
	WhenLeftUp();
}

void TrayIcon::LeftDouble()
{
	WhenLeftDouble();
}

void TrayIcon::DoMenu(Bar& bar)
{
	Menu(bar);
}

LRESULT TrayIcon::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(message == UM_TASKBAR)
		switch(lParam) {
		case WM_LBUTTONDOWN:
			LeftDown();
			return TRUE;
		case WM_LBUTTONUP:
			LeftUp();
			return TRUE;
		case WM_LBUTTONDBLCLK:
			::SetForegroundWindow(nid.hwnd);
			LeftDouble();
			return TRUE;
		case WM_RBUTTONDOWN:
			::SetForegroundWindow(nid.hwnd);
			MenuBar::Execute(NULL, THISBACK(DoMenu), GetMousePos());
			return TRUE;
		}
	return Ctrl::WindowProc(message, wParam, lParam);
}

#endif
#endif

END_UPP_NAMESPACE
