#include "DockCtrl.h"

PaneFrame& PaneFrame::Attach(DockableCtrl& ctrl)
{
	if(ctrl.IsTabbed()) 
		return AttachAsTab(ctrl);
	else if(ctrl.IsAutoHidden())
		return AttachAsAuto(ctrl);
	else if(ctrl.IsDocked())
		return AttachAsDock(ctrl);
	else
		return *this;
}

PaneFrame& PaneFrame::AttachAsDock(DockableCtrl& ctrl)
{
	if(DnDHasSource())
	{
		int position = dndpos;
		DnDSourceoutofRange();
		if(dockcontainer.IsAnimating()) dockcontainer.StopAnimation();
	}
	if(ctrl.IsDocked() && !ctrl.IsHidden())	ShowFrame(ctrl.SizeHint());
	dockcontainer.AddChildDock(ctrl, dndpos ? dndpos : ctrl.Position());
	dndpos = 0;
	return RefreshPaneFrame();
}

PaneFrame& PaneFrame::AttachAsTab(DockableCtrl& ctrl)
{
	int position = ctrl.Position();
	if(DnDHasSource())
	{
		position = dndpos;
		DnDSourceoutofRange();
		if(HasTabWindow(GetActiveTabWindow()))
			if(GetActiveTabWindow()->IsTabAnimating())
				GetActiveTabWindow()->StopTabAnimation();
	}
	else
	{
		DockableCtrl* targetctrl = dockcontainer.GetChildAt(position);

		if(!targetctrl)
		{
			int cc = dockcontainer.GetChildCount();
			if(cc == 0) 
			{
				ctrl.Style(GetType(), DockableCtrl::STATE_SHOW, 0);
				return AttachAsDock(ctrl);
			}
			else
			{
				targetctrl = dockcontainer.GetChildAt(cc);
				if(targetctrl) position = targetctrl->Position();
				else return *this;
			}
		}
	}
	
	AddtoTabWindow(ctrl.Posit(position));
	SetActiveTabWindow(NULL);
	dndpos = 0;
	RefreshTabWindowList();
	return RefreshPaneFrame();
}

PaneFrame& PaneFrame::AttachAsAuto(DockableCtrl& ctrl)
{
	bool horizontal = GetType() == LEFT || GetType() == RIGHT;
	AutoHideBar& bar = GetBase().GetHideBar(GetType());
	Size sz = ctrl.SizeHint();
	if(horizontal)
		sz.cx < 4 ? ctrl.SetSizeHint(Size(maxsize, sz.cy)) : 0;
	else
		sz.cy < 4 ? ctrl.SetSizeHint(Size(sz.cx, maxsize)) : 0;
		                             
	bar.Attach(ctrl);
	GetBase().RefreshWidgetLayout();
	return RefreshPaneFrame();
}

PaneFrame& PaneFrame::Detach(DockableCtrl& ctrl)
{
	if(!ctrl.IsDocked()) return *this;
	if(HasChild(ctrl) && !ctrl.IsShut()) 
		dockcontainer.RemoveChildDock(ctrl);
	if(!dockcontainer.HasChild())  
		HideFrame(); 
	return RefreshPaneFrame();		
}

DockableCtrl* PaneFrame::GetChild(int position)
{
	return dockcontainer.GetChildAt(position);
}

int PaneFrame::GetCount()
{
	return dockcontainer.GetChildCount();
}

bool PaneFrame::HasChild(DockableCtrl& ctrl)
{
	if(dockcontainer.HasChild())
		for(int i = 1; i <= dockcontainer.GetCount(); i++)
			if(&ctrl == dockcontainer.GetChildAt(i))	
				return true;
	return false;
}

void PaneFrame::ShowFrame()
{
	SetSize(200); 
	RefreshPaneFrame().Enable();
}

void PaneFrame::ShowFrame(Size& sz)
{
	bool horizontal = GetType() == LEFT || GetType() == RIGHT;
	
	if(!dockcontainer.HasChild())
	{
		if(horizontal)
			SetSize((sz.cx > 4 && sz.cx < maxsize) ? sz.cx : maxsize);
		else
			SetSize((sz.cy > 4 && sz.cy < maxsize) ? sz.cy : maxsize);
	}
	else SetSize(size);
	RefreshPaneFrame();
	if(!IsEnabled()) Enable();  
}

void PaneFrame::HideFrame()
{
	SetSize(0);
	RefreshPaneFrame().Disable();
}

void PaneFrame::LockFrame()
{
	if(IsLocked()) return;
}

void PaneFrame::UnlockFrame()
{
	if(!IsLocked()) return;
}
Vector<TabWindow*>& PaneFrame::GetTabWindows()
{
	return tabwindows;
}

TabWindow* PaneFrame::AddTabWindow(DockableCtrl& ctrl)
{
	Size tabnewsize;
	int position = ctrl.Position();
	if(position == 0) ++position;
	TabWindow *tabwindow = FindTabWindow(position);
	if(tabwindow) return activetabwindow = tabwindow;
	tabwindows.Add(tabwindow = new TabWindow());
	tabwindow->SetStyle(*GetBase().GetStyle());
	tabwindow->SetBase(&GetBase()).Style(GetType(), DockableCtrl::STATE_SHOW, position);

	if(dockcontainer.HasChild())
	{
		DockableCtrl* child = dockcontainer.GetChildAt(position);
		if(child)
		{
			child->Shut();
			tabwindow->Attach(*child);
			tabnewsize = child->SizeHint();
		}
	}
	if(!tabwindow->IsTabbed())
		if(tabwindow->IsDocked() && !tabwindow->IsHidden()) ShowFrame(tabnewsize);
		dockcontainer.AddChildDock(*tabwindow, (dndpos == 0 || tabwindow->Position()) ? tabwindow->Position() : dndpos);
	RefreshTabWindowList();
	return activetabwindow = tabwindow;	
}

void PaneFrame::RemoveTabWindow(TabWindow* tabwindow)
{
	for(int i = 0 ; i < tabwindows.GetCount(); i++)
		if(tabwindows[i] == tabwindow)
		{
			delete tabwindows[i];							
			if(tabwindow == GetActiveTabWindow()) 
				SetActiveTabWindow(NULL);
		}
}

void PaneFrame::RemoveTabWindow(int position)
{
	if(position == 0) return;
	for(int i = 0; i < tabwindows.GetCount(); i++)
		if(tabwindows.At(i)->Position() == position) tabwindows.Remove(i);	// TODO: change ??? 
			SetActiveTabWindow(NULL);
}

void PaneFrame::RemoveTabWindows()
{
	for(int i = 0 ; i < tabwindows.GetCount(); i++)
		if(tabwindows.At(i)) delete tabwindows.At(i);
	SetActiveTabWindow(NULL);	
}

void PaneFrame::RefreshTabWindowList()
{
	for(int i = 0; i < tabwindows.GetCount(); i++)
		if(tabwindows.At(i)->IsDestroyed())
		{
			TabWindow *t = tabwindows.At(i);
			tabwindows.Remove(i);
			if(t == GetActiveTabWindow())
				SetActiveTabWindow(NULL);
			delete t;
		}
}

void PaneFrame::AddtoTabWindow(DockableCtrl& ctrl)
{
	TabWindow* tabwindow 	=	FindTabWindow(ctrl.Position());
	if(!tabwindow) tabwindow = AddTabWindow(ctrl);
	tabwindow->Attach(ctrl);
}

void PaneFrame::RemovefromTabWindow(DockableCtrl& ctrl)
{
	TabWindow* tabwindow = FindTabWindow(ctrl.Position());
	if(!tabwindow) return;
	ctrl.Shut();
	if(tabwindow && tabwindow->IsShut())
		delete tabwindow;
}

void PaneFrame::RemovefromTabWindow(int position)
{
}

TabWindow* PaneFrame::FindTabWindow(int position)
{
	if(position <= 0) return NULL;
	TabWindow * tabwindow = NULL;
	
	for(int i = 0; i < tabwindows.GetCount(); i++)
	{
		tabwindow = tabwindows.At(i);
		if(tabwindow->Position() == position && 
			tabwindow->Alignment() == GetType() &&
			tabwindow->State() != DockableCtrl::STATE_TABBED)
		return tabwindow;
	}
	return NULL;
}

TabWindow* PaneFrame::FindTabWindow(DockableCtrl& ctrl)
{
	return NULL;
}

TabWindow* PaneFrame::GetActiveTabWindow()
{
	return activetabwindow;
}

void PaneFrame::SetActiveTabWindow(TabWindow* tabwindow)
{
	activetabwindow = tabwindow;
}

bool PaneFrame::HasTabWindow(TabWindow* tabwindow)
{
	for(int i = 0; i < tabwindows.GetCount(); i++)
		if(tabwindow == tabwindows.At(i))
			return true;
	return false;
}


bool PaneFrame::HasCtrlInRange(DockableCtrl& ctrl, Point p)
{
	Ctrl* first = NULL;
	Ctrl* last  = NULL;

	if(!dockcontainer.HasChild())
		return CalculateEmptyRange(ctrl, p);	
	if(!(first = dockcontainer.GetFirstChild()) || !(last = dockcontainer.GetLastChild())) 
		return false;
	if((first == last) && (first != dockcontainer.GetAnimationCtrl()))
		return CalculateCtrlRange(ctrl, *first, p);
	else
	{
		Ctrl* ctrl0 = first;
		while(ctrl0)
		{
			if(ctrl0 != dockcontainer.GetAnimationCtrl())
				if(CalculateCtrlRange(ctrl, *ctrl0, p)) return true;
			ctrl0 = ctrl0->GetNext();
		}
	}
	return false;
}

bool PaneFrame::CalculateCtrlRange(DockableCtrl& t, Ctrl& c, Point p)
{
	DockWindow* ctrl = reinterpret_cast<DockWindow*>(&c);
	ASSERT(ctrl);
	Rect r = ctrl->GetCtrlView();
	int	 position 	= ctrl->Position();
	int	 hrange  	= r.GetWidth()  / 3;
	int	 vrange		= r.GetHeight() / 3;

	if(!DnDHasSource())
	{
		if(!GetActiveTabWindow() || 
			(GetActiveTabWindow() && 
			!GetActiveTabWindow()->IsTabAnimating()))
		{
			if(Rect(r.left + hrange, r.top + vrange, r.right - hrange, r.bottom - vrange).Contains(p))
			{
				DnDSourceinRange();
				StartTabWindowAnimation(*ctrl, position);
				t.SetDropTarget(GetType(), DockableCtrl::STATE_TABBED);
				return true;
			}
		}
		if(dockcontainer.IsVert() && 
			!GetActiveTabWindow() && 
			!dockcontainer.IsAnimating())
		{
			if(Rect(r.left, r.top, r.right, r.top + vrange).Contains(p) || 
		   	Rect(r.left, r.bottom - vrange, r.right, r.bottom).Contains(p))
		    {
				DnDSourceinRange();
				StartPaneFrameAnimation(*ctrl, p.y > r.bottom - vrange ? ++position : position); 
				t.SetDropTarget(GetType(), DockableCtrl::STATE_SHOW);
				return true;
		    }
		}
		if(dockcontainer.IsHorz() && 
			!GetActiveTabWindow() && 
			!dockcontainer.IsAnimating())
		{
			if(Rect(r.left, r.top, r.left + hrange, r.bottom).Contains(p) || 
			Rect(r.right - hrange, r.top, r.right, r.bottom).Contains(p))
			{
				DnDSourceinRange();
				StartPaneFrameAnimation(*ctrl, p.x < r.left + hrange ? position : ++position);
				t.SetDropTarget(GetType(), DockableCtrl::STATE_SHOW);
		   		return true;
		  	}
		}
		return false;
	}
	if(DnDHasSource())
	{
		if(dockcontainer.IsHorz() && dockcontainer.IsAnimating() && 
			dockcontainer.AnimationArea().Contains(p)) return true;
		if(dockcontainer.IsVert())
		{
			r = dockcontainer.AnimationArea();
			r.bottom += 5;
			r.top 	 -= 5;
			if(dockcontainer.IsAnimating() && r.Contains(p)) return true;
		}

		if(GetActiveTabWindow())
			if(GetActiveTabWindow()->IsTabAnimating() && 
				GetActiveTabWindow()->HasCtrlInRange()) return true;
		DnDSourceoutofRange(); 
		DnDAnimate(position);
		return false;
			
	}
	return false;
}

bool PaneFrame::CalculateEmptyRange(Ctrl& c, Point p)
{
	DockWindow* ctrl = reinterpret_cast<DockWindow*>(&c);
	ASSERT(ctrl);
	Rect r = GetScreenRect();
	if(!DnDHasSource() && !dockcontainer.HasChild() && !dockcontainer.IsAnimating())
	{
		bool state = false;
		switch(GetType())
		{
			case LEFT:
				((p.x < r.right + 20) && (p.x > r.left) && (p.y > r.top && p.y < r.bottom)) ?
					state = true : state = false; break;
			case RIGHT:
				((p.x > r.left - 20) && (p.x < r.right) && (p.y > r.top && p.y < r.bottom)) ?
					state = true : state = false; break;
			case TOP:
				((p.y < r.bottom + 20) && (p.y > r.top) && (p.x > r.left && p.x < r.right))  ? 
					state = true : state = false; break;
			case BOTTOM:
				((p.y > r.top - 20) && (p.y < r.bottom) && (p.x > r.left && p.x < r.right)) ?
					state = true : state = false; break;
		}
		if(state) 
		{
			ShowFrame(ctrl->SizeHint());
			DnDSourceinRange(); 
			StartPaneFrameAnimation(reinterpret_cast<DockableCtrl&>(c), 1);
			ctrl->SetDropTarget(GetType(), DockableCtrl::STATE_SHOW);
			return true;
		}
		return false;
	}

	if(DnDHasSource())
	{
	
		if(dockcontainer.IsAnimating() && dockcontainer.AnimationArea().Contains(p)) return true;
		HideFrame();
		DnDSourceoutofRange(); 
		StopPaneFrameAnimation();
		return false;
	}
	return false;
}


//----------------------------------------------------------------------------------------------

void PaneFrame::StartPaneFrameAnimation(DockableCtrl& ctrl, int position)
{
	if(DnDHasSource() && !dockcontainer.IsAnimating())
	{
		if(HasTabWindow(GetActiveTabWindow()))
	   		if(GetActiveTabWindow()->IsTabAnimating())
	   			GetActiveTabWindow()->StopTabAnimation();
		dockcontainer.StartAnimation(position);
		dndpos = position;
	}
	RefreshPaneFrame();
}

void PaneFrame::StartTabWindowAnimation(DockableCtrl& ctrl, int position)
{
	if(DnDHasSource() && &ctrl && (ctrl.Position() == position)) 
	{
		if(!HasTabWindow(GetActiveTabWindow())) activetabwindow = AddTabWindow(ctrl);
		if(!GetActiveTabWindow()->IsTabAnimating())
		{
			if(dockcontainer.IsAnimating())	dockcontainer.StopAnimation();
			GetActiveTabWindow()->StartTabAnimation();
		}
		dndpos = position;
	}
	RefreshPaneFrame();
}

void PaneFrame::StopPaneFrameAnimation()
{
	if(!DnDHasSource() && dockcontainer.IsAnimating())
		dockcontainer.StopAnimation();
	RefreshPaneFrame();
}

void PaneFrame::StopTabWindowAnimation()
{
	if(!DnDHasSource() && HasTabWindow(GetActiveTabWindow()))
		if(GetActiveTabWindow()->IsTabAnimating())
		{
			GetActiveTabWindow()->StopTabAnimation();
			SetActiveTabWindow(NULL);
		}
	RefreshPaneFrame();
}



void PaneFrame::DnDAnimate(int position)
{
	if(!(dockcontainer.IsAnimating() && dockcontainer.GetAnimationCtrl()->GetScreenRect().Contains(GetMousePos())))
		StopPaneFrameAnimation();
	if(HasTabWindow(GetActiveTabWindow()))
		if(!(GetActiveTabWindow()->IsTabAnimating() && GetActiveTabWindow()->HasCtrlInRange()))
			StopTabWindowAnimation();
}


//----------------------------------------------------------------------------------------------

PaneFrame& PaneFrame::SetLayout(DockCtrl* basectrl, int alignment, int _maxsize)
{
	ASSERT(basectrl);
	base = basectrl;
	MaxSize(_maxsize);
	
	switch(alignment)
	{
		case LEFT:
			Left(dockcontainer.SizePos(), 0);
			break;
		case TOP:
			Top(dockcontainer.SizePos(), 0);
			break;
		case RIGHT:
			Right(dockcontainer.SizePos(), 0);
			break;
		case BOTTOM:
			Bottom(dockcontainer.SizePos(), 0);
			break;
	}
	HideFrame();
	created = true;
	return *this;
}

void PaneFrame::FrameAdd(Ctrl& parent)
{
	parent.Add(*this);
}

void PaneFrame::FrameRemove()
{
	this->Ctrl::Remove();
}

void PaneFrame::FrameAddSize(Size& sz)
{
	if(IsShown()) 
		if(type == LEFT || type == RIGHT)  
		{
			sz.cx += size;
			maxsize = sz.cx / 3;
		}
		else
		{
			sz.cy += size;
			maxsize = sz.cy / 3;
		}
}

int  PaneFrame::BoundSize()
{
	int maxsize = max(0, (type == LEFT || type == RIGHT ? parentsize.cx : parentsize.cy) - sizemin);
	return IsShown() ? max(1, minmax(size, minsize - 1, maxsize)) : 0;
}

void PaneFrame::FrameLayout(Rect& r)
{
	Rect rr = r;
	parentsize = r.GetSize();
	int sz = BoundSize();
	switch(type) {
	case LEFT:
		r.left += sz;
		rr.right = r.left;
		break;
	case RIGHT:
		r.right -= sz;
		rr.left = r.right;
		break;
	case TOP:
		r.top += sz;
		rr.bottom = r.top;
		break;
	case BOTTOM:
		r.bottom -= sz;
		rr.top = r.bottom;
		break;
	}
	SetFrameRect(rr);
}

void PaneFrame::Paint(Draw& draw)
{
	draw.DrawRect(
		Ctrl::GetSize(),
		HasCapture() ? GUI_GlobalStyle() >= GUISTYLE_XP ? Blend(SColorHighlight, SColorFace) : SColorShadow
		             : SColorFace()
	);
}

void PaneFrame::LeftDown(Point p, dword)
{
	SetCapture();
	Refresh();
	ref = GetMousePos();
	size0 = BoundSize();
}

void PaneFrame::MouseMove(Point p, dword keyflags)
{
	if(!HasCapture())
		return;
	p = GetMousePos();
	switch(type) {
	case LEFT: size = size0 + p.x - ref.x; break;
	case RIGHT: size = size0 + ref.x - p.x; break;
	case TOP: size = size0 + p.y - ref.y; break;
	case BOTTOM: size = size0 + ref.y - p.y; break;
	}
	RefreshParentLayout();
}

void PaneFrame::LeftUp(Point p, dword keyflags)
{
	Refresh();
}

Image PaneFrame::CursorImage(Point p, dword keyflags)
{
	return type == LEFT || type == RIGHT ? Image::SizeHorz() : Image::SizeVert();
}

PaneFrame& PaneFrame::Set(Ctrl& c, int _size, int _type)
{
	while(GetFirstChild())
		GetFirstChild()->Remove();
	type = _type;
	size = _size;
	Add(c.SizePos());
	switch(type) {
	case LEFT: c.HSizePos(0, 4); break;
	case RIGHT: c.HSizePos(4, 0); break;
	case TOP: c.VSizePos(0, 4); break;
	case BOTTOM: c.VSizePos(4, 0); break;
	}
	RefreshParentLayout();
	return *this;
}

PaneFrame::PaneFrame()
{
	type = LEFT;
	size = size0 = 1;
	minsize = 0;
	maxsize = 0;
	sizemin = 0;
	dndpos	= 0;
	ncount	= 0;
	locked 	= false;
	created = false;
	activetabwindow = NULL; 
}

PaneFrame::~PaneFrame()
{
	RemoveTabWindows();
}
