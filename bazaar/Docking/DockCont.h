#ifndef _Docking_DockCont_h_
#define _Docking_DockCont_h_

#include <Docking/DockMenu.h>
#include <Docking/DockableCtrl.h>
#include <Docking/DockTabBar.h>

NAMESPACE_UPP

class DockWindow;

struct ImgButton : public Pusher {
	private:
		const Value *look;
		Image img;
	public:		
		ImgButton()										{ Transparent(true); }
		virtual void Paint(Draw& w);
		virtual void MouseEnter(Point p, dword kflags) 	{ Refresh(); Pusher::MouseEnter(p, kflags); }
		virtual void MouseLeave() 						{ Refresh(); Pusher::MouseLeave(); }

		ImgButton& 	SetImage(const Image& _img) 		{ img = _img; Refresh(); return *this; }
		ImgButton& 	SetLook(const Value *_look) 		{ look = _look; Refresh(); return *this; }
};

#define DOCKCONT_WND_OFFSET 4 // Should get from API?

class DockCont : public TopWindow {
public:
	typedef DockCont CLASSNAME;

	virtual void LeftDown(Point p, dword keyflags)		{ SetFocus(); }
	virtual void RightDown(Point p, dword keyflags) 	{ WindowMenu(); }
	
	virtual void Layout();
	virtual void ChildRemoved(Ctrl *child);
	virtual void ChildAdded(Ctrl *child);
/*	virtual void ChildGotFocus() 						{ handle.RefreshFocus(true); TopWindow::ChildGotFocus(); }
	virtual void ChildLostFocus() 						{ handle.RefreshFocus(HasFocusDeep()); TopWindow::ChildLostFocus(); }
	virtual void GotFocus() 							{ handle.RefreshFocus(true); }
	virtual void LostFocus() 							{ handle.RefreshFocus(HasFocusDeep()); }*/
public:
#if defined(PLATFORM_WIN32)
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
#elif defined(PLATFORM_X11)
	virtual void EventProc(XWindow& w, XEvent *event);
#endif

	enum DockState {
		STATE_NONE = -1,
		STATE_FLOATING,
		STATE_DOCKED, 
		STATE_AUTOHIDE,
		STATE_TABBED
	};
private:
	class DockContMenu : public DockMenu {
	public:
		typedef DockContMenu CLASSNAME;
		DockCont *cont;
		
		DockContMenu(DockWindow *dockwindow = NULL) : DockMenu(dockwindow) { };
		
		void ContainerMenu(Bar& bar, DockCont *c, bool withgroups  = true);
	private:		
		virtual void MenuDock(int align, DockableCtrl *dc);
		virtual void MenuFloat(DockableCtrl *dc);
		virtual void MenuAutoHide(int align, DockableCtrl *dc);	
		virtual void MenuClose(DockableCtrl *dc);	
	};	
	friend class DockContMenu;
		
	class DockContFrame : public CtrlFrame {
		virtual void FrameLayout(Rect& r)                   { r.Deflate(2); }
		virtual void FramePaint(Draw& w, const Rect& r) {
			DrawFrame(w, r, SColorShadow());
			DrawFrame(w, r.Deflated(1), SColorPaper);
		}
		virtual void FrameAddSize(Size& sz) { sz += 4; }
	};		
		
	struct Handle : public FrameCtrl<Ctrl> {
		Callback WhenContext;
		Callback WhenLeftDrag;
		Callback WhenLeftDouble;
		Handle() 										{ dc = NULL; focus = false; }
		DockableCtrl *dc;
		bool focus;
		virtual void FrameLayout(Rect& r);
		virtual void FrameAddSize(Size& sz);
		
		virtual void Paint(Draw& w);
		virtual void LeftDrag(Point p, dword keyflags)	{ /*RefreshFocus(true);*/ WhenLeftDrag(); }
		virtual void LeftDouble(Point p, dword keyflags) { /*RefreshFocus(true);*/ WhenLeftDouble(); }
		virtual void RightDown(Point p, dword keyflags) { /*RefreshFocus(true);*/ WhenContext(); }
		
		//void	RefreshFocus(bool _focus);
		int		GetHandleSize(const DockableCtrl::Style& s) const;
	};
		
	int 		dragging;
	DockState	dockstate;	
	DockTabBar 	tabbar;
	Handle 		handle;
	ImgButton 	close, autohide, windowpos;	
	Size 		usersize;
	bool 		waitsync:1;	
	bool		animating:1;
	DockWindow *base;
	const DockableCtrl::Style *style;

	// Callbacks
	// Tab callbacks
	void 	TabSelected();
	void	TabDragged(int ix);
	void	TabContext(int ix);
	void	TabClosed(Value v);								
	// Menus/Buttons
	void 	Float();
	void 	Dock(int align);
	void 	AutoHide();
	void 	AutoHideAlign(int align);
	void	RestoreCurrent();

	void 	CloseAll();

	DockableCtrl *Get0(int ix) const;
	DockableCtrl *GetCurrent0() const							{ return Get0(tabbar.GetCursor()); }
	
	void 	AddRemoveButton(Ctrl& c, bool state);
	bool 	IsDockAllowed0(int align, const Value& v) const;
	void	SyncButtons(DockableCtrl& dc);
	Ctrl   *FindFirstChild() const;

	void			State(DockWindow& dock, DockCont::DockState state);	

	Ctrl           *CtrlCast(const Value& v) const		{ return IsDockCont(v) ? (Ctrl *)ContCast(v) : (Ctrl *)DockCast(v); }
	DockCont       *ContCast(const Value& v) const 		{ return ValueTo<DockCont *>(v); } 
	DockableCtrl   *DockCast(const Value& v) const 		{ return ValueTo<DockableCtrl *>(v); }
	bool			IsDockCont(const Value& v) const	{ return IsType<DockCont *>(v); }
	Ctrl           *GetCtrl(int ix) const				{ return CtrlCast(tabbar.GetKey(ix)); }
	Value 			ValueCast(DockableCtrl *dc) const 	{ return RawToValue<DockableCtrl *>(dc); }
	Value 			ValueCast(DockCont *dc) const 		{ return RawToValue<DockCont *>(dc); }
public:
	void 			SetCursor(int ix)					{ tabbar.SetCursor(ix); TabSelected(); }	
	void 			SetCursor(Ctrl& c);
	int 			GetCursor()	const					{ return tabbar.GetCursor(); }
	DockableCtrl& 	Get(int ix) const					{ return *Get0(ix); }
	DockableCtrl& 	GetCurrent() const					{ return Get(tabbar.GetCursor()); }
	void 			AddFrom(DockCont& cont, int except = -1);
	int				GetCount() const					{ return tabbar.GetCount(); }
	void 			Clear();	
	
	virtual void 	MoveBegin();
	virtual void 	Moving();
	virtual void 	MoveEnd();		
	virtual void 	WindowMenu();	
		
	void 			Animate(Rect target, int ticks, int interval = 0);
		
	bool 			IsDocked() const			{ return dockstate == STATE_DOCKED; }
	int				GetDockAlign() const;		
	int				GetAutoHideAlign() const;		
	bool			IsFloating() const			{ return dockstate == STATE_FLOATING; }
	bool 			IsAutoHide() const			{ return dockstate == STATE_AUTOHIDE; }	
	bool			IsTabbed() const			{ return dockstate == STATE_TABBED; }
	bool 			IsDockedAny() const 		{ return dockstate != STATE_FLOATING && dockstate != STATE_NONE; }
	bool			IsHidden() const			{ return dockstate == STATE_NONE; }	
	DockState		GetDockState() const		{ return dockstate; }
	
	void			StateNotDocked(DockWindow *dock = NULL) 	{ if (dock) base = dock; dockstate = STATE_NONE; }
	void			StateDocked(DockWindow& dock)				{ State(dock, STATE_DOCKED); }
	void 			StateFloating(DockWindow& dock)				{ State(dock, STATE_FLOATING); }
	void			StateAutoHide(DockWindow& dock)				{ State(dock, STATE_AUTOHIDE); Hide(); }
	void			StateTabbed(DockWindow& dock)				{ State(dock, STATE_TABBED); Hide(); }	
	void			StartMouseDrag();
	
	void			SetAllDockerPos();
	
	DockWindow     *GetDockWindow() const			{ return base; }
	void			SyncButtons()					{ if (GetCount()) SyncButtons(GetCurrent()); }
	void			SyncTabs(int align, bool text);				
	void 			Lock(bool lock);
	void 			SyncFrames();
	void 			SyncFrames(bool lock);
	void			SignalStateChange();	
	
	void 			Grouping(bool grouping)			{ tabbar.Grouping(grouping); GroupRefresh(); }
	void			GroupRefresh();	
	void			GetGroups(Vector<String>& groups);
	
	void			WindowButtons(bool menu, bool hide, bool close);
	
	void			Highlight();
	Image 			GetHighlightImage();
	
	virtual Size	GetMinSize() const;
	virtual Size	GetMaxSize() const;
	virtual Size	GetStdSize() const;	
	Size			GetUserSize() const				{ return usersize; }
	void 			SetUserSize(Size sz)			{ usersize = sz; }
	void			SyncUserSize(bool h, bool v);		

	WString 		GetTitle(bool force_count = false) const; 
	
	bool			IsDockAllowed(int align, int dc_ix = -1) const;
		
	virtual void 	Serialize(Stream& s);
	
	DockCont();		
};

END_UPP_NAMESPACE

#endif
