#include <CtrlCore/CtrlCore.h>

#ifdef GUI_FB

NAMESPACE_UPP

#define LLOG(x)

Vector<Ctrl *> fb_window;
ImageBuffer    framebuffer;

int FindFBWindowIndex(const Ctrl *x)
{
	return FindIndex(fb_window, x);
}

void Ctrl::RefreshFB(const Rect& r)
{
	SystemDraw painter(framebuffer);
	painter.Draw::Clip(r);
	for(int i = 0; i < fb_window.GetCount(); i++)
		fb_window[i]->UpdateArea(painter, fb_window[i]->GetRect().GetSize());
	painter.End();
}

void Ctrl::RefreshFBAll()
{
	RefreshFB(framebuffer.GetSize());
}

void Ctrl::InitFB()
{
	Ctrl::InitTimer();
	framebuffer.Create(1000, 1000);
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
	return Vector<Ctrl *>(fb_window, 1);
}

void  Ctrl::SetMouseCursor(const Image& image)
{
	GuiLock __;
}

Ctrl *Ctrl::GetOwner()
{
	GuiLock __;
	return NULL;
}

Ctrl *Ctrl::GetActiveCtrl()
{
	GuiLock __;
	return fb_window.GetCount() ? fb_window.Top() : NULL;
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

bool Ctrl::IsWaitingEvent()
{
	return FBIsWaitingEvent();
}

bool Ctrl::ProcessEvent(bool *quit)
{
	ASSERT(IsMainThread());
	if(DoCall())
		return false;
	if(FBEndSession())
		return false;
	if(!GetMouseLeft() && !GetMouseRight() && !GetMouseMiddle())
		ReleaseCtrlCapture();
	if(FBProcessEvent(quit)) {
		DefferedFocusSync();
		SyncCaret();
		return true;
	}
	return false;
}

bool Ctrl::ProcessEvents(bool *quit)
{
	if(ProcessEvent(quit)) {
		while(ProcessEvent(quit) && (!LoopCtrl || LoopCtrl->InLoop())); // LoopCtrl-MF 071008
		TimerProc(GetTickCount());
		SweepMkImageCache();
		return true;
	}
	SweepMkImageCache();
	TimerProc(GetTickCount());
	return false;
}

void Ctrl::EventLoop0(Ctrl *ctrl)
{
	GuiLock __;
	ASSERT(IsMainThread());
	ASSERT(LoopLevel == 0 || ctrl);
	LoopLevel++;
	LLOG("Entering event loop at level " << LoopLevel << BeginIndent);
	Ptr<Ctrl> ploop;
	if(ctrl) {
		ploop = LoopCtrl;
		LoopCtrl = ctrl;
		ctrl->inloop = true;
	}

	bool quit = false;
	ProcessEvents(&quit);
	while(!FBEndSession() && !quit && ctrl ? ctrl->IsOpen() && ctrl->InLoop() : GetTopCtrls().GetCount())
	{
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / GuiSleep");
		SyncCaret();
		GuiSleep(1000);
		if(FBEndSession()) break;
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / ProcessEvents");
		ProcessEvents(&quit);
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / after ProcessEvents");
	}

	if(ctrl)
		LoopCtrl = ploop;
	LoopLevel--;
	LLOG(EndIndent << "Leaving event loop ");
}

void Ctrl::GuiSleep0(int ms)
{
	GuiLock __;
	ASSERT(IsMainThread());
	LLOG("GuiSleep");
	if(FBEndSession())
		return;
	LLOG("GuiSleep 2");
	int level = LeaveGMutexAll();
	FBSleep(ms);
	EnterGMutex(level);
}

Rect Ctrl::GetWndUpdateRect() const
{
	GuiLock __;
	Rect r;
	return Rect(0, 0, 1000, 1000);
}

Rect Ctrl::GetWndScreenRect() const
{
	GuiLock __;
	return GetRect();
}

void Ctrl::WndShow0(bool b)
{
	GuiLock __;
	RefreshFB(GetRect());
}

void Ctrl::WndUpdate0()
{
	GuiLock __;
	RefreshFB(GetRect());
}

bool Ctrl::IsWndOpen() const {
	GuiLock __;
	return FindFBWindowIndex(this) >= 0;
}

void Ctrl::SetAlpha(byte alpha)
{
	GuiLock __;
}

Rect Ctrl::GetWorkArea() const
{
	GuiLock __;
	return framebuffer.GetSize();
}

void Ctrl::GetWorkArea(Array<Rect>& rc)
{
	GuiLock __;
	Array<Rect> r;
	r.Add(framebuffer.GetSize());
}

Rect Ctrl::GetVirtualWorkArea()
{
	return framebuffer.GetSize();
}

Rect Ctrl::GetWorkArea(Point pt)
{
	return framebuffer.GetSize();
}

Rect Ctrl::GetVirtualScreenArea()
{
	GuiLock __;
	return framebuffer.GetSize();
}

Rect Ctrl::GetPrimaryWorkArea()
{
	Rect r;
	return framebuffer.GetSize();
}

Rect Ctrl::GetPrimaryScreenArea()
{
	return framebuffer.GetSize();
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

void Ctrl::WndDestroy0()
{
	int q = FindFBWindowIndex(this);
	if(q < 0) return;
	Rect r = GetRect();
	fb_window.Remove(q);
	RefreshFB(r);
}

void Ctrl::SetWndForeground0()
{
	GuiLock __;
	int q = FindFBWindowIndex(this);
	if(q < 0) return;
	fb_window.Remove(q);
	fb_window.Add(this);
	RefreshFB(GetRect());
}

bool Ctrl::IsWndForeground() const
{
	GuiLock __;
	return fb_window.Top() == this;
}

void Ctrl::WndEnable0(bool *b)
{
	GuiLock __;
	RefreshFB(GetRect());	
}

void Ctrl::SetWndFocus0(bool *b)
{
	GuiLock __;
	if(IsWndOpen()) {
		SetWndForeground0();
		*b = true;
	}
	else
		*b = false;
}

bool Ctrl::HasWndFocus() const
{
	GuiLock __;
	return IsWndForeground();
}

bool Ctrl::SetWndCapture()
{
	GuiLock __;
	ASSERT(IsMainThread());
	return false;
}

bool Ctrl::ReleaseWndCapture()
{
	GuiLock __;
	ASSERT(IsMainThread());
	return false;
}

bool Ctrl::HasWndCapture() const
{
	GuiLock __;
	return false;
}

void Ctrl::WndInvalidateRect0(const Rect& r)
{
	GuiLock __;
	RefreshFB(r.Offseted(GetRect().TopLeft()));
}

void Ctrl::WndSetPos0(const Rect& rect)
{
	GuiLock __;
	RefreshFBAll();
}

void Ctrl::WndUpdate0r(const Rect& r)
{
	GuiLock __;
	RefreshFBAll();
}

void  Ctrl::WndScrollView0(const Rect& r, int dx, int dy)
{
	GuiLock __;
	RefreshFBAll();
}

void Ctrl::PopUp(Ctrl *owner, bool savebits, bool activate, bool dropshadow, bool topmost)
{
}

Rect Ctrl::GetDefaultWindowRect() {
	return Rect(0, 0, 100, 100);
}

ViewDraw::ViewDraw(Ctrl *ctrl)
{
	EnterGuiMutex();
}

ViewDraw::~ViewDraw()
{
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
