#include "Fb.h"

#ifdef GUI_FB

NAMESPACE_UPP

#define LLOG(x)  // LOG(x)

void TopWindow::SyncFrameRect(const Rect& r)
{
	frame->SetClient(r);
}

void TopWindow::DestroyFrame()
{
	if(frame->IsOpen())
		frame->Close();
}

void TopWindow::GripResize()
{
	frame->GripResize();
}

void TopWindow::SyncSizeHints()
{
	SyncCaption0();
}

void TopWindow::SyncTitle0()
{
	SyncCaption0();
}

void TopWindow::SyncCaption0()
{
	GuiLock __;
	frame->title = title.ToString();
	frame->minsize = minsize;
	frame->close.Show(!noclosebox);
	frame->maximize.Show(maximizebox);
	frame->sizeable = sizeable;
	frame->RefreshLayout();
	frame->Refresh();
	frame->close <<= Proxy(WhenClose);
	frame->icon = icon;
}

void TopWindow::SyncRect()
{
	frame->SyncRect();
	Rect r = frame->GetClient();
	if(r != GetRect()) {
		SetRect(r);
	}
}

void TopWindow::Open(Ctrl *owner)
{
	GuiLock __;
	Rect r = GetRect();
	if(r.IsEmpty())
		SetRect(GetDefaultWindowRect());
	else
	if(r.left == 0 && r.top == 0)
		if(owner && center == 1)
			SetRect(owner->GetRect().CenterRect(r.GetSize()));
		else
		if(center)
			SetRect(GetWorkArea().CenterRect(r.GetSize()));
	frame->SetClient(GetRect());
	frame->PopUp(owner, false, true);
	PopUp(frame, false, true);
	popup = false;
	SetRect(frame->GetClient());
	SyncCaption0();
	if(state == MAXIMIZED)
		frame->Maximize();
}

void TopWindow::Open()
{
	Open(GetActiveCtrl());
}

void TopWindow::OpenMain()
{
	Open(NULL);
}

void TopWindow::Minimize(bool effect)
{
//	state = MINIMIZED;
}

TopWindow& TopWindow::FullScreen(bool b)
{
	return *this;
}

void TopWindow::Maximize(bool effect)
{
	state = MAXIMIZED;
	frame->Maximize();
}

void TopWindow::Overlap(bool effect)
{
	GuiLock __;
	state = OVERLAPPED;
	frame->Overlap();
}

TopWindow& TopWindow::TopMost(bool b, bool stay_top)
{
	GuiLock __;
	return *this;
}

bool TopWindow::IsTopMost() const
{
	return true;
}

void TopWindow::GuiPlatformConstruct()
{
	frame = new TopWindowFrame;
}

void TopWindow::GuiPlatformDestruct()
{
	delete frame;
}

void TopWindow::SerializePlacement(Stream& s, bool reminimize)
{
	GuiLock __;
}

END_UPP_NAMESPACE

#endif
