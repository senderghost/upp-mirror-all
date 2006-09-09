#include "CtrlLib.h"

void StaticText::Paint(Draw& w)
{
	Size sz = GetSize();
	if(!IsTransparent())
		w.DrawRect(0, 0, sz.cx, sz.cy, SColorFace);
	PaintLabel(w, 0, 0, sz.cx, sz.cy, !IsShowEnabled(), false, false, VisibleAccessKeys());
}

Size StaticText::GetMinSize() const
{
	return GetLabelSize();
}

void StaticText::LabelUpdate() {
	Refresh();
}

StaticText::StaticText()
{
	NoWantFocus();
	IgnoreMouse();
	Transparent();
	SetAlign(ALIGN_LEFT);
}

Label& Label::SetText(const char *text)
{
	LabelBase::SetText(text);
	lbl.accesskey = 0;
	noac = false;
	return *this;
}

Label& Label::SetLabel(const char *_text)
{
	String text;
	byte accesskey = ExtractAccessKey(_text, text);
	LabelBase::SetText(text);
	lbl.accesskey = accesskey;
	return *this;
}

bool Label::HotKey(dword key) {
	if(CompareAccessKey(lbl.accesskey, key)) {
		IterateFocusForward(this, GetParent());
		return true;
	}
	return false;
}

dword Label::GetAccessKeys() const
{
	return AccessKeyBit(lbl.accesskey);
}

void  Label::AssignAccessKeys(dword used)
{
	if(noac)
		return;
	Ctrl *next = GetNext();
	if(!lbl.accesskey && next && next->IsInitFocus()) {
		next->AssignAccessKeys(used);
		if(!next->GetAccessKeysDeep()) {
			lbl.accesskey = ChooseAccessKey(GetText(), used);
			if(lbl.accesskey) Refresh();
			used |= AccessKeyBit(lbl.accesskey);
		}
	}
	Ctrl::AssignAccessKeys(used);
}

Label::Label() {
	noac = false;
}

Label::~Label() {}

CH_COLOR(LabelBoxTextColor, LtBlue());
CH_COLOR(LabelBoxColor, SColorShadow());

LabelBox::LabelBox()
{
	SetInk(LabelBoxTextColor);
	SetVAlign(ALIGN_TOP);
}

void  LabelBox::AssignAccessKeys(dword used)
{
	Ctrl::AssignAccessKeys(used);
}

LabelBox::~LabelBox() {}

Rect LabelBox::GetVoidRect()
{
	Rect r = GetSize();
	r.left += 2;
	r.top += max(GetLabelSize().cy, 2);
	r.bottom -= 2;
	r.right -= 2;
	return r;
}

void LabelBox::Paint(Draw& w)
{
	Size sz = GetSize();
	if(!IsTransparent())
		w.DrawRect(sz, SColorFace);
	Size lsz = GetLabelSize();
	int d = lsz.cy >> 1;
	bool hline = sz.cy < 2 * Draw::GetStdFontCy();
	bool vline = sz.cx < 2 * Draw::GetStdFontCy();
	int ty = hline ? (sz.cy - lsz.cy) / 2 : 0;
	Size ts = PaintLabel(w, d + 2, ty, sz.cx, sz.cy, !IsShowEnabled(), false, false, VisibleAccessKeys());
	w.Begin();
	w.ExcludeClip(d, ty, ts.cx + 4, ts.cy);
	if(IsXPStyle()) {
		if(hline) {
			d = sz.cy / 2;
			w.DrawRect(0, d - 1, sz.cx, 1, SColorLight);
			w.DrawRect(0, d, sz.cx, 1, SColorShadow);
			w.DrawRect(0, d + 1, sz.cx, 1, SColorLight);
		}
		else
		if(vline) {
			d = sz.cx / 2;
			w.DrawRect(d - 1, 0, 1, sz.cy, SColorLight);
			w.DrawRect(d, 0, 1, sz.cy, SColorShadow);
			w.DrawRect(d + 1, 0, 1, sz.cy, SColorLight);
		}
		else {
			w.DrawRect(0, d + 2, 1, sz.cy - d - 4, LabelBoxColor);
			w.DrawRect(sz.cx - 1, d + 2, 1, sz.cy - d - 4, LabelBoxColor);
			w.DrawRect(2, sz.cy - 1, sz.cx - 4, 1, LabelBoxColor);
			w.DrawRect(2, d, sz.cx - 4, 1, LabelBoxColor);

			w.DrawRect(1, d + 1, 2, 1, LabelBoxColor);
			w.DrawRect(1, d + 2, 1, 1, LabelBoxColor);

			w.DrawRect(sz.cx - 3, d + 1, 2, 1, LabelBoxColor);
			w.DrawRect(sz.cx - 2, d + 2, 1, 1, LabelBoxColor);

			w.DrawRect(1, sz.cy - 2, 2, 1, LabelBoxColor);
			w.DrawRect(1, sz.cy - 3, 1, 1, LabelBoxColor);

			w.DrawRect(sz.cx - 3, sz.cy - 2, 2, 1, LabelBoxColor);
			w.DrawRect(sz.cx - 2, sz.cy - 3, 1, 1, LabelBoxColor);
		}
	}
	else {
		if(hline) {
			d = sz.cy / 2;
			w.DrawRect(0, d, sz.cx, 1, SColorShadow);
			w.DrawRect(0, d + 1, sz.cx, 1, SColorLight);
		}
		else
		if(vline) {
			d = sz.cx / 2;
			w.DrawRect(d, 0, 1, sz.cy, SColorShadow);
			w.DrawRect(d - 1, 1, 0, sz.cy, SColorLight);
		}
		else {
			w.DrawRect(1, d, sz.cx - 2, 1, SColorShadow);
			w.DrawRect(1, d + 1, sz.cx - 2, 1, SColorLight);

			w.DrawRect(0, d, 1, sz.cy - d - 1, SColorShadow);
			w.DrawRect(1, d + 1, 1, sz.cy - d - 2, SColorLight);

			w.DrawRect(sz.cx - 2, d, 1, sz.cy - d, SColorShadow);
			w.DrawRect(sz.cx - 1, d, 1, sz.cy - d, SColorLight);

			w.DrawRect(1, sz.cy - 2, sz.cx - 2, 1, SColorShadow);
			w.DrawRect(1, sz.cy - 1, sz.cx - 2, 1, SColorLight);
		}
	}
	w.End();
}

Rect ParentCtrl::GetVoidRect()
{
	return GetSize();
}

ParentCtrl::ParentCtrl()
{
	NoWantFocus();
	Transparent();
}

StaticRect& StaticRect::Color(class ::Color _color)
{
	if(color != _color) {
		color = _color;
		Refresh();
	}
	return *this;
}

void StaticRect::Paint(Draw& w) {
	Size sz = GetSize();
	w.DrawRect(0, 0, sz.cx, sz.cy, color);
}

StaticRect::StaticRect() {
	color = SColorFace;
	NoWantFocus();
}

StaticRect::~StaticRect() {}

void ImageCtrl::Paint(Draw& w)
{
	if(!img) return;
	Size sz = GetSize();
	Size bsz = GetStdSize();
	w.DrawImage((sz.cx - bsz.cx) / 2, (sz.cy - bsz.cy) / 2, img);
}

Size ImageCtrl::GetStdSize() const
{
	return img.GetSize();
}

Size ImageCtrl::GetMinSize() const
{
	return img.GetSize();
}

void Picture::Paint(Draw& w) {
	Size sz = GetSize();
	w.DrawRect(0, 0, sz.cx, sz.cy, background);
	if(!picture) return;
	int dx = 0;
	int dy = 0;
	Size rz = sz;
	if(ratio) {
		Size sr = picture.GetSize();
		if(sr.cx * sz.cx < sz.cy * sr.cy) {
			rz.cy = sr.cy * sz.cx / sr.cx;
			dy = (sz.cy - rz.cy) / 2;
		}
		else {
			rz.cx = sr.cx * sz.cy / sr.cy;
			dx = (sz.cx - rz.cx) / 2;
		}
	}
	w.Clipoff(dx, dy, rz.cx, rz.cy);
	w.DrawDrawing(0, 0, rz.cx, rz.cy, picture);
	w.End();
}

Picture::Picture() {
	ratio = true;
	background = White;
}

Size SeparatorCtrl::GetMinSize() const {
	return Size(size, size);
}

void SeparatorCtrl::Paint(Draw& w) {
	Size sz = GetSize();
	if(sz.cx > sz.cy) {
		int q = sz.cy / 2;
		w.DrawRect(margin, q - 1, sz.cx - 2 * margin, 1, SColorShadow);
		if(!IsXPStyle())
			w.DrawRect(margin, q, sz.cx - 2 * margin, 1, SColorLight);
	}
	else {
		int q = sz.cx / 2;
		w.DrawRect(q - 1, margin, 1, sz.cy - 2 * margin, SColorShadow);
		if(!IsXPStyle())
			w.DrawRect(q, margin, 1, sz.cy - 2 * margin, SColorLight);
	}
};

SeparatorCtrl& SeparatorCtrl::Margin(int w)
{
	if(w != margin) {
		margin = w;
		Refresh();
	}
	return *this;
}

SeparatorCtrl& SeparatorCtrl::SetSize(int w)
{
	if(w != size) {
		size = w;
		Refresh();
	}
	return *this;
}

SeparatorCtrl::SeparatorCtrl()
{
	NoWantFocus();
	Transparent();
	margin = 2;
	size = 7;
}
