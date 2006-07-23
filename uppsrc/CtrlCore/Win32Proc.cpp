#include "CtrlCore.h"

#define LLOG(x)  // LOG(x)

#ifdef PLATFORM_WIN32

#include <winnls.h>

dword Ctrl::KEYtoK(dword chr) {
	if(chr == VK_TAB)
		chr = K_TAB;
	else
	if(chr == VK_SPACE)
		chr = K_SPACE;
	else
	if(chr == VK_RETURN)
		chr = K_RETURN;
	else
		chr = chr + K_DELTA;
	if(chr == K_ALT_KEY || chr == K_CTRL_KEY || chr == K_SHIFT_KEY)
		return chr;
	if(GetCtrl()) chr |= K_CTRL;
	if(GetAlt()) chr |= K_ALT;
	if(GetShift()) chr |= K_SHIFT;
	return chr;
}


class NilDrawFull : public NilDraw {
	virtual bool IsPaintingOp(const Rect& r) const { return true; }
};

LRESULT Ctrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
//	LLOG("Ctrl::WindowProc(" << message << ") in " << ::Name(this) << ", focus " << (void *)::GetFocus());
	Ptr<Ctrl> _this = this;
	HWND hwnd = GetHWND();
	switch(message) {
	case WM_PALETTECHANGED:
		if((HWND)wParam == hwnd)
			break;
	case WM_QUERYNEWPALETTE:
		if(!Draw::AutoPalette()) break;
		{
			HDC hDC = GetDC(hwnd);
			HPALETTE hOldPal = SelectPalette(hDC, GetQlibPalette(), FALSE);
			int i = RealizePalette(hDC);
			SelectPalette(hDC, hOldPal, TRUE);
			RealizePalette(hDC);
			ReleaseDC(hwnd, hDC);
			LLOG("Realized " << i << " colors");
			if(i) InvalidateRect(hwnd, NULL, TRUE);
			return i;
		}
	case WM_PAINT:
		ASSERT(hwnd);
		if(IsVisible() && hwnd) {
			PAINTSTRUCT ps;
			SyncScroll();
			HDC dc = BeginPaint(hwnd, &ps);
			fullrefresh = false;
			Draw draw(dc);
			HPALETTE hOldPal;
			if(draw.PaletteMode() && Draw::AutoPalette()) {
				hOldPal = SelectPalette(dc, GetQlibPalette(), TRUE);
				int n = RealizePalette(dc);
				LLOG("In paint realized " << n << " colors");
			}
			Point p = GetSysWindowViewOffset();
			if(p.x || p.y)
				draw.Offset(-p);
			UpdateArea(draw, Rect(ps.rcPaint) + p);
			if(draw.PaletteMode() && Draw::AutoPalette())
				SelectPalette(dc, hOldPal, TRUE);
			EndPaint(hwnd, &ps);
		}
		return 0L;
	case WM_NCHITTEST:
		CheckMouseCtrl();
		if(ignoremouse) return HTTRANSPARENT;
		break;
	case WM_LBUTTONDOWN:
//		LLOG("WM_LBUTTONDOWN, ignoreclick = " << ignoreclick);
	case WM_MBUTTONDOWN:
		ClickActivateWnd();
		if(ignoreclick) return 0L;
		DoMouse(LEFTDOWN, Point(lParam), message == WM_MBUTTONDOWN ? MIDDLEBUTTON : 0);
		if(_this) PostInput();
		return 0L;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
		if(ignoreclick)
			EndIgnore();
		else
			DoMouse(LEFTUP, Point(lParam), message == WM_MBUTTONUP ? MIDDLEBUTTON : 0);
		if(!GetMouseRight() && !GetMouseMiddle() && !GetMouseLeft()) ReleaseCtrlCapture();
		if(_this) PostInput();
		return 0L;
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDBLCLK:
		ClickActivateWnd();
		if(ignoreclick) return 0L;
		DoMouse(LEFTDOUBLE, Point(lParam), message == WM_MBUTTONDBLCLK ? MIDDLEBUTTON : 0);
		if(_this) PostInput();
		return 0L;
	case WM_RBUTTONDOWN:
		ClickActivateWnd();
		if(ignoreclick) return 0L;
		DoMouse(RIGHTDOWN, Point(lParam));
		if(_this) PostInput();
		return 0L;
	case WM_NCLBUTTONDOWN:
	case WM_NCRBUTTONDOWN:
	case WM_NCMBUTTONDOWN:
		ClickActivateWnd();
		break;
	case WM_RBUTTONUP:
		if(ignoreclick)
			EndIgnore();
		else
			DoMouse(RIGHTUP, Point(lParam));
		if(!GetMouseLeft() && !GetMouseMiddle()) ReleaseCtrlCapture();
		if(_this) PostInput();
		return 0L;
	case WM_RBUTTONDBLCLK:
		ClickActivateWnd();
		if(ignoreclick) return 0L;
		DoMouse(RIGHTDOUBLE, Point(lParam));
		if(_this) PostInput();
		return 0L;
	case WM_MOUSEMOVE:
		LLOG("WM_MOUSEMOVE: ignoreclick = " << ignoreclick);
		if(ignoreclick) {
			EndIgnore();
			return 0L;
		}
		if(_this)
			DoMouse(MOUSEMOVE, Point(lParam));
		DoCursorShape();
		return 0L;
	case 0x20a: // WM_MOUSEWHEEL:
		if(ignoreclick) {
			EndIgnore();
			return 0L;
		}
		if(_this)
			DoMouse(MOUSEWHEEL, Point(lParam), (short)HIWORD(wParam));
		if(_this) PostInput();
		return 0L;
	case WM_SETCURSOR:
		if((HWND)wParam == hwnd && LOWORD(lParam) == HTCLIENT) {
			if(hCursor) SetCursor(hCursor);
			return TRUE;
		}
		break;
//	case WM_MENUCHAR:
//		return MAKELONG(0, MNC_SELECT);
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_CHAR:
		ignorekeyup = false;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		{
#if 0
			String msgdump;
			switch(message)
			{
			case WM_KEYDOWN:    msgdump << "WM_KEYDOWN"; break;
			case WM_KEYUP:      msgdump << "WM_KEYUP"; break;
			case WM_SYSKEYDOWN: msgdump << "WM_SYSKEYDOWN"; break;
			case WM_SYSKEYUP:   msgdump << "WM_SYSKEYUP"; break;
			case WM_CHAR:       msgdump << "WM_CHAR"; break;
			}
			msgdump << " wParam = 0x" << FormatIntHex(wParam, 8)
				<< ", lParam = 0x" << FormatIntHex(lParam, 8)
				<< ", ignorekeyup = " << (ignorekeyup ? "true" : "false");
			LLOG(msgdump);
#endif
			dword keycode = 0;
			if(message == WM_KEYDOWN)
				keycode = KEYtoK(wParam);
			else
			if(message == WM_KEYUP)
				keycode = KEYtoK(wParam) | K_KEYUP;
			else
			if(message == WM_SYSKEYDOWN /*&& ((lParam & 0x20000000) || wParam == VK_F10)*/)
				keycode = KEYtoK(wParam);
			else
			if(message == WM_SYSKEYUP /*&& ((lParam & 0x20000000) || wParam == VK_F10)*/)
				keycode = KEYtoK(wParam) | K_KEYUP;
			else
			if(message == WM_CHAR && wParam != 127 && wParam > 32) {
				if(IsWindowUnicode(hwnd)) // TRC 04/10/17: ActiveX Unicode patch
					keycode = wParam;
				else {
					char b[20];
					GetLocaleInfo(MAKELCID(LOWORD(GetKeyboardLayout(0)), SORT_DEFAULT),
					              LOCALE_IDEFAULTANSICODEPAGE, b, 20);
					int codepage = atoi(b);
					if(codepage >= 1250 && codepage <= 1258)
						keycode = ToUnicode(wParam, codepage - 1250 + CHARSET_WIN1250);
					else
						keycode = wParam;
				}
			}
			bool b = false;
			if(keycode) {
				b = DispatchKey(keycode, LOWORD(lParam));
				SyncCaret();
				if(_this) PostInput();
			}
//			LOG("key processed = " << b);
			bool PassWindowsKey(int wParam);
			if(b || (message == WM_SYSKEYDOWN || message == WM_SYSKEYUP)
			&& wParam != VK_F4 && !PassWindowsKey(wParam)) // 17.11.2003 Mirek -> invoke system menu
				return 0L;
			break;
		}
		break;
//	case WM_GETDLGCODE:
//		return wantfocus ? 0 : DLGC_STATIC;
	case WM_DESTROY:
		PreDestroy();
		break;
	case WM_ERASEBKGND:
		return 1L;
	case WM_NCDESTROY:
		if(!hwnd) break;
		if(HasChildDeep(mouseCtrl) || this == ~mouseCtrl) mouseCtrl = NULL;
		if(HasChildDeep(focusCtrl) || this == ~focusCtrl) focusCtrl = NULL;
		if(HasChildDeep(focusCtrlWnd) || this == ~focusCtrlWnd) {
			RLOG("WM_NCDESTROY: clearing focusCtrlWnd = " << ::Name(focusCtrlWnd));
			focusCtrlWnd = NULL;
			focusCtrl = NULL;
		}
		if(::GetFocus() == NULL) {
			Ctrl *owner = GetOwner();
			if(owner && (owner->IsForeground() || IsForeground()) && !owner->SetWantFocus())
				IterateFocusForward(owner, owner);
		}
		if(IsWindowUnicode(hwnd)) // TRC 04/10/17: ActiveX unicode patch
			DefWindowProcW(hwnd, message, wParam, lParam);
		else
			DefWindowProc(hwnd, message, wParam, lParam);
		hwnd = NULL;
		return 0L;
	case WM_CANCELMODE:
		if(this == ~captureCtrl || HasChildDeep(captureCtrl))
			ReleaseCtrlCapture();
		break;
	case WM_SHOWWINDOW:
		visible = (BOOL) wParam;
		StateH(SHOW);
		break;
	case WM_MOUSEACTIVATE:
		LLOG("WM_MOUSEACTIVATE " << Name() << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		if(!IsEnabled()) {
			if(lastActiveWnd && lastActiveWnd->IsEnabled()) {
				LLOG("WM_MOUSEACTIVATE -> ::SetFocus for " << ::Name(lastActiveWnd));
				::SetFocus(lastActiveWnd->GetHWND());
			}
			else
				MessageBeep(MB_OK);
			return MA_NOACTIVATEANDEAT;
		}
		if(IsPopUp()) return MA_NOACTIVATE;
		break;
	case WM_SIZE:
	case WM_MOVE:
		if(hwnd) {
			Rect rect;
			if(activex) {
				WINDOWPLACEMENT wp;
				wp.length = sizeof(WINDOWINFO);
				::GetWindowPlacement(hwnd, &wp);
				rect = wp.rcNormalPosition;
			}
			else
				rect = GetScreenClient(hwnd);
			LLOG("WM_MOVE / WM_SIZE: screen client = " << rect);
			if(GetRect() != rect)
				SetWndRect(rect);
			WndDestroyCaret();
			caretCtrl = NULL;
			SyncCaret();
		}
		return 0L;
	case WM_HELP:
		return TRUE;
	case WM_ACTIVATE:
		LLOG("WM_ACTIVATE " << Name() << ", wParam = " << (int)wParam << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		ignorekeyup = true;
		break;
	case WM_SETFOCUS:
		LLOG("WM_SETFOCUS " << Name() << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		if(this != focusCtrlWnd)
			if(IsEnabled())
				ActivateWnd();
			else {
				if(focusCtrlWnd && focusCtrlWnd->IsEnabled()) {
					if(!IsEnabled())
						MessageBeep(MB_OK);
					LLOG("WM_SETFOCUS -> ::SetFocus for " << ::Name(focusCtrlWnd));
					::SetFocus(focusCtrlWnd->GetHWND());
				}
				else
				if(lastActiveWnd && lastActiveWnd->IsEnabled()) {
					LLOG("WM_SETFOCUS -> ::SetFocus for " << ::Name(lastActiveWnd));
					::SetFocus(lastActiveWnd->GetHWND());
				}
				else {
					LLOG("WM_SETFOCUS - ::SetFocus(NULL)");
					::SetFocus(NULL);
				}
			}
		LLOG("//WM_SETFOCUS " << (void *)hwnd << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		return 0L;
	case WM_KILLFOCUS:
		LLOG("WM_KILLFOCUS " << (void *)(HWND)wParam << ", this = " << ::Name(this) << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		LLOG("Kill " << ::Name(CtrlFromHWND((HWND)wParam)));
		if(!CtrlFromHWND((HWND)wParam))
			KillFocusWnd();
		LLOG("//WM_KILLFOCUS " << (void *)(HWND)wParam << ", focusCtrlWnd = " << ::Name(focusCtrlWnd) << ", raw = " << (void *)::GetFocus());
		return 0L;
	case WM_ENABLE:
		if(!!wParam != enabled) {
			enabled = !!wParam;
			RefreshFrame();
			StateH(ENABLE);
		}
		return 0L;
	case WM_GETMINMAXINFO:
		{
			MINMAXINFO *mmi = (MINMAXINFO *)lParam;
			Rect minr(Point(50, 50), GetMinSize());
			Rect maxr(Point(50, 50), GetMaxSize());
			dword style = ::GetWindowLong(hwnd, GWL_STYLE);
			dword exstyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
			AdjustWindowRectEx(minr, style, FALSE, exstyle);
			AdjustWindowRectEx(maxr, style, FALSE, exstyle);
			mmi->ptMinTrackSize = Point(minr.Size());
			mmi->ptMaxTrackSize = Point(maxr.Size());
			LLOG("WM_GETMINMAXINFO: MinTrackSize = " << Point(mmi->ptMinTrackSize) << ", MaxTrackSize = " << Point(mmi->ptMaxTrackSize));
			LLOG("ptMaxSize = " << Point(mmi->ptMaxSize) << ", ptMaxPosition = " << Point(mmi->ptMaxPosition));
		}
		return 0L;
	case WM_SETTINGCHANGE:
	case 0x031A: // WM_THEMECHANGED
		ChSetStyle(ChGetStyle());
		RefreshLayoutDeep();
		RefreshFrame();
		break;
	}
	if(hwnd)
		if(IsWindowUnicode(hwnd)) // TRC 04/10/17: ActiveX Unicode patch
			return DefWindowProcW(hwnd, message, wParam, lParam);
		else
			return DefWindowProc(hwnd, message, wParam, lParam);
	return 0L;
}

void Ctrl::PreDestroy() {}

#endif
