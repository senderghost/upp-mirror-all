#include "Local.h"

#include "Turtle.brc"

#ifdef GUI_TURTLE

NAMESPACE_UPP

#define LLOG(x)     // LLOG(x)
#define LDUMP(x)    // RDUMP(x)
#define LTIMING(x)

static Point MousePos;

Size   DesktopSize = Size(1000, 1000);

StaticRect& Desktop()
{
	static StaticRect x;
	return x;
}

HttpHeader  http;
TcpSocket   server;
TcpSocket   socket;
WebSocket   websocket;

BiVector<String> event_queue;

String           hostname;

void SetHostName(const String& h)
{
	hostname = h;
}

bool Ctrl::Connect()
{
	LLOG("Connect");
	if(!server.Listen(8088, 10)) {
		LLOG("Cannot open server port for listening\r\n");
		Exit(1);
	}
	LLOG("Starting to listen on 8088");
	socket.Timeout(20000);
	for(;;) {
		if(socket.Accept(server)) {
			if(http.Read(socket)) {
				LLOG("Accepted, header read");
				if(websocket.WebAccept(socket, http))
				#ifdef _DEBUG
					break;
				#else
					if(fork() == 0)
						break;
					else {
						socket.Close();
						continue;
					}
				#endif
				LLOG("Sending HTML");
				String html = String(turtle_html, turtle_html_length);
			#ifdef _DEBUG
				html.Replace("%%host%%", Nvl(GetIniKey("turtle_host"), Nvl(hostname, "ws://localhost:8088")));
			#else
				html.Replace("%%host%%", "ws://eventcraft.eu:8088");
			#endif
				HttpResponse(socket, http.scgi, 200, "OK", "text/html", html);
			}
			socket.Close();
		}
	}
	LLOG("Connection established");
	server.Close();
	if(socket.IsError())
		LLOG("CONNECT ERROR: " << socket.GetErrorDesc());
	return true;
}

void Ctrl::InitTelpp(const String& hostname_)
{
	LLOG("InitTelpp");

	hostname = hostname_;

	Connect();
	
	LLOG("WebSocket connected");

	Ctrl::GlobalBackBuffer();
	Ctrl::InitTimer();

#ifdef PLATFORM_POSIX
	SetStdFont(ScreenSans(12)); //FIXME general handling
#endif
	ChStdSkin();

	Desktop().Color(Cyan());
	Desktop().SetRect(0, 0, DesktopSize.cx, DesktopSize.cy);
	SetDesktop(Desktop());
}

void Ctrl::TimerAndPaint()
{
	LLOG("TimerAndPaint " << msecs());
	TimerProc(GetTickCount());
	DefferedFocusSync();
	SyncCaret();
	SyncTopWindows();
	SweepMkImageCache();
	DoPaint();
	socket.Timeout(20000);
	websocket.SendBinary(ZCompress(String(SystemDraw::DISABLESENDING, 1))); // Do not send events until data transfered and processed
	String s = turtle_stream.FlushStream();
	if(s.GetCount() > 10)
		LLOG("Sending " << s.GetLength());
	websocket.SendBinary(s);
}

bool Ctrl::IsWaitingEvent()
{
	GuiLock __;
	while(socket.Timeout(0).WaitRead()) {
		socket.Timeout(20000);
		String s = websocket.Recieve();
		LLOG("Recieved data " << s);
		StringStream ss(s);
		while(!ss.IsEof())
			event_queue.AddTail(ss.GetLine());
	}
	socket.Timeout(20000);
	if(socket.IsError())
		LLOG("ERROR: " << socket.GetErrorDesc());
	return event_queue.GetCount();
}

bool Ctrl::ProcessEvents(bool *quit)
{
	GuiLock __;
	LLOG("---- Process events");
	bool r = false;
	while(IsWaitingEvent()) {
		while(event_queue.GetCount() >= 2 && *event_queue[0] == 'M' && *event_queue[1] == 'M')
			event_queue.DropHead(); // MouseMove compression
		String ev = event_queue[0];
		event_queue.DropHead();
		ProcessEvent(ev);
		r = true;
	}
	TimerAndPaint();
	return r;
}

void Ctrl::GuiSleep(int ms)
{
	GuiLock __;
	ASSERT(IsMainThread());
//	LLOG("GuiSleep");
	int level = LeaveGuiMutexAll();
	socket.Timeout(ms).WaitRead();
	socket.Timeout(20000);
	EnterGuiMutex(level);
}

dword lastbdowntime[8] = {0};
dword isdblclick[8] = {0};

void Ctrl::MouseEventFB(Ptr<Ctrl> t, int event, Point p, int zdelta)
{
	if(!t->IsEnabled())
		return;
	Rect rr = t->GetRect();
	if((event & Ctrl::ACTION) == DOWN) {
		Ptr<Ctrl> q = t;
		TopWindowFrame *wf = dynamic_cast<TopWindowFrame *>(~t);
		if(wf)
			q = wf->window;			
		if(q) q->ClickActivateWnd();
		if(q) q->SetForeground();
		if(ignoreclick)
			return;
	}
	if(t)
		t->DispatchMouse(event, p - rr.TopLeft(), zdelta);
	if(t)
		t->PostInput();
}

Ctrl *Ctrl::FindMouseTopCtrl()
{
	for(int i = topctrl.GetCount() - 1; i >= 0; i--) {
		Ctrl *t = topctrl[i];
		if(t->GetRect().Contains(MousePos))
			return t->IsEnabled() ? t : NULL;
	}
	return desktop->IsEnabled() ? desktop : NULL;
}

void Ctrl::SetCaret(int x, int y, int cx, int cy)
{
	GuiLock __;
	caretx = x;
	carety = y;
	caretcx = cx;
	caretcy = cy;
	fbCaretTm = GetTickCount();
	SyncCaret();
}

void Ctrl::SyncCaret()
{
	CursorSync();
}

void Ctrl::CursorSync()
{
//	LLOG("@ CursorSync");
	Point p = GetMousePos() - fbCursorImage.GetHotSpot();
	Rect cr = Null;
	if(focusCtrl && (((GetTickCount() - fbCaretTm) / 500) & 1) == 0)
		cr = (RectC(focusCtrl->caretx, focusCtrl->carety, focusCtrl->caretcx, focusCtrl->caretcy)
		      + focusCtrl->GetScreenView().TopLeft()) & focusCtrl->GetScreenView();
	if(fbCursorPos != p && !SystemCursor || cr != fbCaretRect) {
		fbCaretRect = cr;
		fbCursorPos = p;
		Invalidate();
	}
}

void Ctrl::PaintScene(SystemDraw& draw)
{
	if(!desktop)
		return;
	LLOG("@ DoPaint");
	LTIMING("DoPaint paint");
	draw.Init(DesktopSize);
	draw.Begin();
	Vector<Rect> invalid;
	invalid.Add(DesktopSize); _TODO_
	for(int i = topctrl.GetCount() - 1; i >= 0; i--) {
		Rect r = topctrl[i]->GetRect();
		Rect ri = GetClipBound(invalid, r);
		if(!IsNull(ri)) {
			draw.Clipoff(r);
			topctrl[i]->UpdateArea(draw, ri - r.TopLeft());
			draw.End();
			Subtract(invalid, r);
			draw.ExcludeClip(r);
		}
	}
	Rect ri = GetClipBound(invalid, desktop->GetRect().GetSize());
	if(!IsNull(ri))
		desktop->UpdateArea(draw, ri);
	draw.End();
}

void Ctrl::PaintCaretCursor(SystemDraw& draw)
{
	if(!IsNull(fbCaretRect))
		draw.DrawRect(fbCaretRect, InvertColor);
	int64 q = fbCursorImage.GetAuxData();
	if(q) {
		draw.Put8(SystemDraw::STD_CURSORIMAGE);
		draw.Put8(clamp((int)q, 1, 16));
	}
	else {
		String h;
		Point p = fbCursorImage.GetHotSpot();
		h << "url('data:image/png;base64,"
		  << Base64Encode(PNGEncoder().SaveString(fbCursorImage))
		  << "') " << p.x << ' ' << p.y << ", default";
		draw.Put8(SystemDraw::SETCURSORIMAGE);
		draw.Put16(0); // _TODO_ Cursor cache
		draw.Put(h);
		draw.Put8(SystemDraw::CURSORIMAGE);
		draw.Put16(0); // _TODO_ Cursor cache
	}
}

void Ctrl::DoPaint()
{ 
	if(!PaintLock) {
		if(invalid && desktop) {
			invalid = false;
			SystemDraw draw;
			PaintScene(draw);
			PaintCaretCursor(draw);
		}
	}
}

bool keyShift;
bool keyCtrl;
bool keyAlt;

bool GetShift()       { return keyShift; }
bool GetCtrl()        { return keyCtrl; }
bool GetAlt()         { return keyAlt; }
bool GetCapsLock()    { return false; } // Impossible to implement

dword fbKEYtoK(dword chr) {
	chr = chr + K_DELTA;
	if(chr == K_ALT_KEY || chr == K_CTRL_KEY || chr == K_SHIFT_KEY)
		return chr;
	if(GetCtrl()) chr |= K_CTRL;
	if(GetAlt()) chr |= K_ALT;
	if(GetShift()) chr |= K_SHIFT;
	return chr;
/*
	if(chr == SDLK_TAB)
		chr = K_TAB;
	else
	if(chr == SDLK_SPACE)
		chr = K_SPACE;
	else
	if(chr == SDLK_RETURN)
		chr = K_RETURN;
	else
		chr = chr + K_DELTA;
*/
}

void Ctrl::ReadKeyMods(CParser& p)
{
	const char *s = p.GetPtr();
	if(*s)
		keyShift = *s++ == '1';
	if(*s)
		keyCtrl = *s++ == '1';
	if(*s)
		keyAlt = *s++ == '1';
}

bool Ctrl::DoKeyFB(dword key, int cnt)
{
	LLOG("DoKeyFB [" << GetKeyDesc(key) << "] " << key << ", " << cnt);

	bool b = DispatchKey(key, cnt);
	SyncCaret();
	Ctrl *desktop = GetDesktop();
	if(desktop)
		desktop->PostInput();
	return b;
}


bool  mouseLeft, mouseMiddle, mouseRight;
Point mouseDownPos;
int64 mouseDownTime;

bool GetMouseLeft()   { return mouseLeft; }
bool GetMouseRight()  { return mouseRight; }
bool GetMouseMiddle() { return mouseMiddle; }

void Ctrl::DoMouseFB(int event, Point p, int zdelta, CParser& cp)
{
	ReadKeyMods(cp);
	MousePos = p;
	int a = event & ACTION;
	if(a == UP && Ctrl::ignoreclick) {
		EndIgnore();
		return;
	}
	else
	if(a == DOWN && ignoreclick)
		return;
	LLOG("### Mouse event: " << event << " position " << p << " zdelta " << zdelta << ", capture " << Upp::Name(captureCtrl));
	if(captureCtrl)
		MouseEventFB(captureCtrl->GetTopCtrl(), event, p, zdelta);
	else
		for(int i = topctrl.GetCount() - 1; i >= 0; i--) {
			Ptr<Ctrl> t = topctrl[i];
			Rect rr = t->GetRect();
			if(rr.Contains(p)) {
				MouseEventFB(t, event, p, zdelta);
				return;
			}
		}
	Ctrl *desktop = GetDesktop();
	if(desktop) {
		desktop->DispatchMouse(event, p, zdelta);
		desktop->PostInput();
	}
}

static int sDistMax(Point a, Point b)
{
	return IsNull(a) ? INT_MAX : max(abs(a.x - b.x), abs(a.y - b.y));
}

Point ReadPoint(CParser& p)
{
	Point pt;
	pt.x = p.ReadInt();
	pt.y = p.ReadInt();
	return pt;
}

void Ctrl::DoMouseButton(int event, CParser& p)
{
	int button = p.ReadInt();
	Point pt = ReadPoint(p);
	int64 tm = p.ReadInt64();
	(button == 0 ? mouseLeft : button == 2 ? mouseRight : mouseMiddle) = event == DOWN;
	if(event == DOWN)
		if(sDistMax(mouseDownPos, pt) < GUI_DragDistance() && tm - mouseDownTime < 800) {
			event = DOUBLE;
			mouseDownTime = 0;
		}
		else {
			mouseDownPos = pt;
			mouseDownTime = tm;
		}
	DoMouseFB(decode(button, 0, LEFT, 2, RIGHT, MIDDLE)|event, pt, 0, p);
}

bool Ctrl::ProcessEvent(const String& event)
{
	LLOG("Processing event " << event);
	CParser p(event);
	try {
		if(p.Id("I"))
			SystemDraw::ResetI();
		else
		if(p.Id("R")) {
			DesktopSize = ReadPoint(p);
			Desktop().SetRect(0, 0, DesktopSize.cx, DesktopSize.cy);				
		}
		if(p.Id("M")) {
			Point pt = ReadPoint(p);
			int64 tm = p.ReadInt64();
			DoMouseFB(MOUSEMOVE, pt, 0, p);
		}
		else
		if(p.Id("W")) {
			double w = p.ReadDouble();
			Point pt = ReadPoint(p);
			int64 tm = p.ReadInt64();
			DoMouseFB(MOUSEWHEEL, pt, w < 0 ? 120 : -120, p);
		}
		else
		if(p.Id("O")) {
			mouseLeft = mouseMiddle = mouseRight = false;
			mouseDownTime = 0;
		}
		else
		if(p.Id("D")) {
			DoMouseButton(DOWN, p);
		}
		else
		if(p.Id("U")) {
			DoMouseButton(UP, p);
		}
		else
		if(p.Id("K")) {
			int code = p.ReadInt();
			int which = p.ReadInt();
			ReadKeyMods(p);
			DoKeyFB(fbKEYtoK(which), 1);
		}
		else
		if(p.Id("k")) {
			int code = p.ReadInt();
			int which = p.ReadInt();
			ReadKeyMods(p);
			DoKeyFB(K_KEYUP|fbKEYtoK(which), 1);
		}
		else
		if(p.Id("C")) {
			int code = p.ReadInt();
			int which = p.ReadInt();
			ReadKeyMods(p);
			if(which && !keyAlt && !keyCtrl)
				DoKeyFB(which, 1);
		}
	}
	catch(CParser::Error) {}
	return true;
}

Point GetMousePos() {
	return MousePos;
}

void Ctrl::EventLoop(Ctrl *ctrl)
{
	GuiLock __;
	ASSERT(IsMainThread());
	ASSERT(LoopLevel == 0 || ctrl);
	LoopLevel++;
	LLOG("Entering event loop at level " << LoopLevel << LOG_BEGIN);
	Ptr<Ctrl> ploop;
	if(ctrl) {
		ploop = LoopCtrl;
		LoopCtrl = ctrl;
		ctrl->inloop = true;
	}

	bool quit = false;
	int64 loopno = ++EventLoopNo;
	ProcessEvents(&quit);
	while(loopno > EndSessionLoopNo && !quit && (ctrl ? ctrl->IsOpen() && ctrl->InLoop() : GetTopCtrls().GetCount()))
	{
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / GuiSleep");
		SyncCaret();
		GuiSleep(20);
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / ProcessEvents");
		ProcessEvents(&quit);
//		LLOG(GetSysTime() << " % " << (unsigned)msecs() % 10000 << ": EventLoop / after ProcessEvents");
//		LDUMP(loopno);
	}

	if(ctrl)
		LoopCtrl = ploop;
	LoopLevel--;
	LLOG(LOG_END << "Leaving event loop ");
}

END_UPP_NAMESPACE

#endif
