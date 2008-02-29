#include "DockTabBar.h"

#include "DockCont.h"
#define ANIM_SPEED 10
#define ANIM_FRAMES 10

// DockTabBar
int AutoHideBar::autohide_timeout = 1000;

void DockTabBar::FrameLayout(Rect& r)
{
	if (IsAutoHide()) return Hide();
	Show();
	TabBar::FrameLayout(r);	
}

void DockTabBar::FrameAddSize(Size& sz)
{
	if (!IsAutoHide()) 
		TabBar::AddFrameSize(sz);
}

void DockTabBar::DrawTabData(Draw& w, Point p, const Size &sz, const Value& q, const Font &font, Color ink, dword style)
{
	DockableCtrl *d;
	WString txt;
	ink = (style == CTRL_DISABLED) ? SColorDisabled : ink;
	
	if (IsTypeRaw<DockCont *>(q)) {
		DockCont *c = ValueTo<DockCont *>(q);
		d = &c->GetCurrent();
		txt = c->GetTitle();
	}
	else {
		ASSERT(IsTypeRaw<DockableCtrl *>(q));
		d = ValueTo<DockableCtrl *>(q);
		txt = d->GetTitle();
	}

	TabCenterText(p, sz, font);
	if(icons)
	{
		const Image &icon = (style == CTRL_DISABLED) ? DisabledImage(d->GetIcon()) : d->GetIcon();
		int al = GetAlign();
		Point ip = p;
		Size isz = icon.GetSize();
		if (al == RIGHT)
			ip.x -= font.GetHeight();
		else if (al == LEFT)
			ip.y -= isz.cy;
		if (IsVert()) {
			w.DrawImage(ip.x-1, ip.y, icon);
			p.y += (isz.cy + QT_SPACEICON) * ((al == LEFT) ? -1 : 1);
		}
		else {			
			w.DrawImage(ip.x, ip.y-2, icon);
			p.x += isz.cx + QT_SPACEICON;
		}	
	}
	w.DrawText(p.x, p.y, TextAngle(), txt, font, ink);
}

Size DockTabBar::GetStdSize(Value &q)
{
	DockableCtrl *d;
	Value v;
	if (IsTypeRaw<DockCont *>(q)) {
		DockCont *c = ValueTo<DockCont *>(q);
		d = &c->GetCurrent();
		v = c->GetTitle();
	}
	else {
		ASSERT(IsTypeRaw<DockableCtrl *>(q));
		d = ValueTo<DockableCtrl *>(q);
		v = d->GetTitle();
	}
	Size sz = TabBar::GetStdSize(v);
	sz.cx += (IsVert() ? d->GetIcon().GetHeight() : d->GetIcon().GetWidth()) + QT_SPACEICON;
	return sz;
}

void DockTabBar::RightDown(Point p, dword keyflags)
{
	if (GetHighlight() >= 0) 
		WhenContext(GetHighlight());	
	else 
		TabBar::RightDown(p, keyflags);
}

void DockTabBar::LeftDrag(Point p, dword keyflags)
{
	if (keyflags & K_CTRL || keyflags & K_SHIFT)
		return TabBar::LeftDrag(p, keyflags &= ~K_SHIFT);
	if (GetHighlight() >= 0)
		WhenDrag(GetHighlight());	
//	clip = NULL;
//	TabBar::LeftDrag(p, keyflags);
}
/*
void DockTabBar::DragAndDrop(Point p, PasteClip& d)
{
	if (&GetInternal<TabBar>(d) != this) return;	
	clip = &d;
	TabBar::DragAndDrop(p, d);
}

void DockTabBar::DragLeave()
{
	if (!GetShift() && clip) {
		ReleaseCapture();
		clip->Reject();
		clip = NULL;
		if (GetHighlight() >= 0)
			WhenDrag(GetHighlight());
	}
	return TabBar::DragLeave();
}
*/
DockTabBar::DockTabBar()
{
	autohide = -1; 
	icons = true;
//	clip = NULL;
}

// AutoHide bar
void AutoHideBar::MouseEnter(Point p, dword keyflags)
{
	if (ctrl && ctrl->IsOpen())
		KillTimeCallback(TIMEID_HIDE_TIMEOUT);			
	DockTabBar::MouseEnter(p, keyflags);
}

void AutoHideBar::MouseLeave()
{
	if (ctrl && ctrl->IsOpen())
		KillSetTimeCallback(autohide_timeout, THISBACK1(HideAnimate, ctrl), TIMEID_HIDE_TIMEOUT);				
	DockTabBar::MouseLeave();
}

void AutoHideBar::AddCtrl(DockCont &c, const String &group)
{ 
	TabBar::Add(RawToValue<DockCont *>(&c), group); 
	if (GetCount() == autohide+1)
		RefreshParentLayout();		
}

void AutoHideBar::RemoveCtrl(DockCont &c, int ix)
{
	if (c.IsOpen()) c.Close();

	if (ctrl == &c) {
		if (popup.IsOpen())
			popup.Close();
		ctrl->Remove();
		//KillTimeCallback(TIMEID_ANIMATE);
		KillTimeCallback(TIMEID_HIDE_TIMEOUT);			
		ctrl = NULL;				
	}
	if (ix >= 0) DockTabBar::Close(ix);
	if (GetCount() == autohide)
		RefreshParentLayout();	
}

void AutoHideBar::RemoveCtrl(int ix)
{
	if (ix >= 0) {
		DockCont *c = GetCtrl(ix);
		ASSERT(c);
		RemoveCtrl(*c, ix);
	}		
}

void AutoHideBar::TabHighlight()
{
	Ctrl *c = NULL;
	int ix = TabBar::GetHighlight();
	if (ix >= 0)
		c = GetCtrl(ix);
	if (!c || ctrl == c) 
		return;
	else if (ctrl) {
		if (c) {
			if (popup.IsOpen())
				popup.Close();
			ctrl->Remove();
			ctrl = NULL;
		}
		else 
			HideAnimate(ctrl);
	}
	if (c) {
		SetCursor(ix);
		ShowAnimate(c);
	}
}

void AutoHideBar::TabClose(Value v)
{
	RemoveCtrl(*(ValueTo<DockCont *>(v)), -1);
	if (GetCount() == autohide-1)
		RefreshParentLayout();	
}

void AutoHideBar::ShowAnimate(Ctrl *c)
{
	if (c == ctrl) return;
	if (popup.IsPopUp()) popup.Close();
	
	Rect r = Ctrl::GetScreenRect();
	Size sz = c->GetStdSize();
	switch (GetAlign()) {
	 	case DockTabBar::LEFT: 
	 		sz.cy = r.Height();
	 		r.left = r.right;
	 		r.right += 5; // Popups don't work on Linux if width or hieght is 0
	 		break;
	 	case DockTabBar::TOP:
	 		sz.cx = r.Width();
	 		r.top = r.bottom;
	 		r.bottom += 5; // Popups don't work on Linux if width or hieght is 0
	 		break;
	 	case DockTabBar::RIGHT: 
	 		sz.cy = r.Height();
	 		r.right = r.left;
	 		r.left -= 5; // Popups don't work on Linux if width or hieght is 0
	 		break;
	 	case DockTabBar::BOTTOM:
	 		sz.cx = r.Width();
	 		r.bottom = r.top;
	 		r.top -= 5; // Popups don't work on Linux if width or hieght is 0
	 		break;
	};
	// use _NET_FRAME_EXTENTS to properly set ctrl size if popup has additional frame added by window manager?
	c->SetRect(sz);
	popup << *(ctrl = c);
	c->Show();
	popup.SetRect(r);
	popup.PopUp(GetParent(), false, true, false, false);
	AdjustSize(r, c->GetStdSize());
	Animate(popup, r, GUIEFFECT_SLIDE);
}

void AutoHideBar::HideAnimate(Ctrl *c)
{
	ASSERT(ctrl);
	Rect r = popup.GetRect();
	AdjustSize(r, -r.GetSize());
	Animate(popup, r, GUIEFFECT_SLIDE);
	popup.Close();
	ctrl->Remove();
	ctrl = NULL;
	DockTabBar::SetCursor(-1);
}
/*
void AutoHideBar::AnimateSizeMinus(Size sz)
{
	Rect r = popup.GetScreenRect();
	AdjustSize(r, sz);
	if ((IsVert() && r.Width() <= 12) || (!IsVert() && r.Height() <= 12)) {
		popup.Close();
		ctrl->Remove();
		ctrl = NULL;
		Ctrl::KillTimeCallback(TIMEID_ANIMATE);
	}
	else
		popup.SetRect(r);
}
*/

void AutoHideBar::AdjustSize(Rect &r, const Size &sz)
{
	switch (DockTabBar::GetAlign()) {
	 	case DockTabBar::LEFT: 
	 		r.right += sz.cx;
	 		break;
	 	case DockTabBar::TOP: 
	 		r.bottom += sz.cy;
	 		break;
	 	case DockTabBar::RIGHT:
	 		r.left -= sz.cx;
	 		break;
	 	case DockTabBar::BOTTOM:
	 		r.top -= sz.cy;
	 		break;
	};		
}

int AutoHideBar::FindCtrl(DockCont &c) const
{
	if (&c == ctrl) return GetCursor();
	for (int i = 0; i < GetCount(); i++) {
		DockCont *v = ValueTo<DockCont *>(Get(i));
		if (v == &c) return i;
	}
	return -1;
}

AutoHideBar::AutoHideBar()
{
	ctrl = NULL;
	AutoHideMin(0).CanEmpty();
	popup.WhenEnter = THISBACK2(MouseEnter, Point(0, 0), 0);
	popup.WhenLeave = THISBACK(MouseLeave);
	popup.AddFrame(FieldFrame());
	DockTabBar::WhenHighlight = THISBACK(TabHighlight);
	TabBar::WhenClose = THISBACK(TabClose);
}

void AutoHideBar::HidePopup::ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags)
{
	if (event == MOUSELEAVE)
		WhenLeave();
	else if (event != MOUSEMOVE) 
		WhenEnter();
}

CH_STYLE(TabBar, Style, StyleDefault)
{
	Assign(TabCtrl::StyleDefault());
	TabBar::ResetStyles();
}

