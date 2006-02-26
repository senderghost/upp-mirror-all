#include "CtrlCore.h"

#ifdef flagSO
CtrlFrame::CtrlFrame() {}
CtrlFrame::~CtrlFrame() {}
#endif

void CtrlFrame::FramePaint(Draw& draw, const Rect& r) {}
void CtrlFrame::FrameAdd(Ctrl& ctrl) {}
void CtrlFrame::FrameRemove() {}

struct NullFrameClass : public CtrlFrame
{
	virtual void FrameLayout(Rect& r) {}
	virtual void FramePaint(Draw& draw, const Rect& r) {}
	virtual void FrameAddSize(Size& sz) {}
};

CtrlFrame& GLOBAL_V(NullFrameClass, NullFrame);

#ifdef flagSO
BorderFrame::BorderFrame(const ColorF *border) : border(border) {}
BorderFrame::~BorderFrame() {}
#endif

void BorderFrame::FrameLayout(Rect& r)
{
	int n = (int)(intptr_t)*border;
	r.Deflate(n);
}

void BorderFrame::FrameAddSize(Size& sz)
{
	sz += 2 * (int)(intptr_t)*border;
}

void BorderFrame::FramePaint(Draw& draw, const Rect& r)
{
	DrawBorder(draw, r.left, r.top, r.Width(), r.Height(), border);
}

CtrlFrame& GLOBAL_VP(BorderFrame, InsetFrame, (InsetBorder()));
CtrlFrame& GLOBAL_VP(BorderFrame, ThinInsetFrame, (ThinInsetBorder()));
CtrlFrame& GLOBAL_VP(BorderFrame, ButtonFrame, (ButtonBorder()));
CtrlFrame& GLOBAL_VP(BorderFrame, BlackFrame, (BlackBorder()));
CtrlFrame& GLOBAL_VP(BorderFrame, OutsetFrame, (OutsetBorder()));
CtrlFrame& GLOBAL_VP(BorderFrame, ThinOutsetFrame, (ThinOutsetBorder()));

class XPFieldFrameCls : public CtrlFrame {
	virtual void FrameLayout(Rect& r)                   { r.Deflate(2); }
	virtual void FramePaint(Draw& w, const Rect& r) {
		DrawFrame(w, r, Blend(SColorHighlight, SColorShadow));
		DrawFrame(w, r.Deflated(1), SColorPaper);
	}
	virtual void FrameAddSize(Size& sz) { sz += 4; }
};

CtrlFrame& XPFieldFrame() { return Single<XPFieldFrameCls>(); }

CtrlFrame& FieldFrame() { return Ctrl::IsXPStyle() ? XPFieldFrame() : InsetFrame(); }

class TopSeparatorFrameCls : public CtrlFrame {
	virtual void FrameLayout(Rect& r)                   { r.top += 2; }
	virtual void FramePaint(Draw& w, const Rect& r) {
		w.DrawRect(r.left, r.top, r.Width(), 1, SGray);
		w.DrawRect(r.left, r.top + 1, r.Width(), 1, SWhite);
	}
	virtual void FrameAddSize(Size& sz) { sz.cy += 2; }
};

class BottomSeparatorFrameCls : public CtrlFrame {
	virtual void FrameLayout(Rect& r)                   { r.bottom -= 2; }
	virtual void FramePaint(Draw& w, const Rect& r) {
		w.DrawRect(r.left, r.bottom - 2, r.Width(), 1, SGray);
		w.DrawRect(r.left, r.bottom - 1, r.Width(), 1, SWhite);
	}
	virtual void FrameAddSize(Size& sz) { sz.cy += 2; }
};

class LeftSeparatorFrameCls : public CtrlFrame {
	virtual void FrameLayout(Rect& r)                   { r.left += 2; }
	virtual void FramePaint(Draw& w, const Rect& r) {
		w.DrawRect(r.left, r.top, 1, r.Height(), SGray);
		w.DrawRect(r.left + 1, r.top, 1, r.Height(), SWhite);
	}
	virtual void FrameAddSize(Size& sz) { sz.cx += 2; }
};

class RightSeparatorFrameCls : public CtrlFrame {
	virtual void FrameLayout(Rect& r)                   { r.right -= 2; }
	virtual void FramePaint(Draw& w, const Rect& r) {
		w.DrawRect(r.right - 2, r.top, 1, r.Height(), SGray);
		w.DrawRect(r.right - 1, r.top, 1, r.Height(), SWhite);
	}
	virtual void FrameAddSize(Size& sz) { sz.cx += 2; }
};

CtrlFrame& BottomSeparatorFrame() { return Single<BottomSeparatorFrameCls>(); }
CtrlFrame& TopSeparatorFrame()    { return Single<TopSeparatorFrameCls>(); }
CtrlFrame& RightSeparatorFrame()  { return Single<RightSeparatorFrameCls>(); }
CtrlFrame& LeftSeparatorFrame()   { return Single<LeftSeparatorFrameCls>(); }

void LayoutFrameLeft(Rect& r, Ctrl *ctrl, int cx)
{
	if(ctrl) {
		cx *= ctrl->IsShown();
		ctrl->SetFrameRect(r.left, r.top, cx, r.Height());
		r.left += cx;
	}
}

void LayoutFrameRight(Rect& r, Ctrl *ctrl, int cx)
{
	if(ctrl) {
		cx *= ctrl->IsShown();
		ctrl->SetFrameRect(r.right - cx, r.top, cx, r.Height());
		r.right -= cx;
	}
}

void LayoutFrameTop(Rect& r, Ctrl *ctrl, int cy)
{
	if(ctrl) {
		cy *= ctrl->IsShown();
		ctrl->SetFrameRect(r.left, r.top, r.Width(), cy);
		r.top += cy;
	}
}

void LayoutFrameBottom(Rect& r, Ctrl *ctrl, int cy)
{
	if(ctrl) {
		cy *= ctrl->IsShown();
		ctrl->SetFrameRect(r.left, r.bottom - cy, r.Width(), cy);
		r.bottom -= cy;
	}
}
