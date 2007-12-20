#include "CtrlLib.h"

NAMESPACE_UPP

#define LTIMING(x)  // TIMING(x)

CH_STYLE(ToolButton, Style, StyleDefault)
{
	CtrlsImageLook(look, CtrlsImg::I_TB, 6);
	font = StdFont();
	for(int i = 0; i < 6; i++)
		textcolor[i] = Button::StyleNormal().textcolor[i];
	textcolor[4] = Button::StyleNormal().textcolor[CTRL_NORMAL];
	textcolor[5] = Button::StyleNormal().textcolor[CTRL_HOT];
}

ToolButton::ToolButton()
{
	Reset();
	checked = false;
	paint_checked = false;
	Transparent();
}

ToolButton::~ToolButton() {}

void ToolButton::Reset()
{
	Tip("");
	Help("");
	Topic("");
	Description("");
	repeat = false;
	accel = 0;
	checked = false;
	NoWantFocus();
	minsize = Size(0, 0);
	maxiconsize = Size(INT_MAX, INT_MAX);
	style = &StyleDefault();
}

void ToolButton::UpdateTip()
{
	LTIMING("UpdateTip");
	String s = tiptext;
	if(IsNull(s) && kind == NOLABEL)
		s = text;
	if(accel) {
		if(s.GetCount())
			s << ' ';
		s << '(' << GetKeyDesc(accel) << ')';
	}
	Ctrl::Tip(s);
}

Bar::Item& ToolButton::Text(const char *txt)
{
	ExtractAccessKey(txt, text);
	UpdateTip();
	return *this;
}

Bar::Item& ToolButton::Check(bool check)
{
	checked = check;
	return *this;
}

Bar::Item& ToolButton::Radio(bool check)
{
	return Check(check);
}

Bar::Item& ToolButton::Key(dword key)
{
	if(key) {
		accel = key;
		UpdateTip();
	}
	return *this;
}

Bar::Item& ToolButton::Repeat(bool r)
{
	repeat = r;
	return *this;
}

ToolButton& ToolButton::Label(const char *text, int _kind)
{
	if(!(kind & FORCE)) {
		kind = _kind;
		Refresh();
	}
	Text(text);
	return *this;
}

Image ToolButton::GetImage() const
{
	return CachedRescale(img, min(img.GetSize(), maxiconsize));
}

Bar::Item& ToolButton::Image(const UPP::Image& img_)
{
	if(!img_.IsSame(img)) {
		img = img_;
		Refresh();
	}
	return *this;
}

Bar::Item& ToolButton::Enable(bool enable)
{
	Ctrl::Enable(enable);
	return *this;
}

Bar::Item& ToolButton::Tip(const char *tip)
{
	tiptext = tip;
	UpdateTip();
	return *this;
}

Bar::Item& ToolButton::Help(const char *help)
{
	HelpLine(help);
	return *this;
}

Bar::Item& ToolButton::Topic(const char *help)
{
	HelpTopic(help);
	return *this;
}

Bar::Item& ToolButton::Description(const char *desc)
{
	Ctrl::Description(desc);
	return *this;
}

void  ToolButton::Paint(Draw& w)
{
	LTIMING("ToolButton::Paint");
	paint_checked = checked;
	Size sz = GetSize();
	UPP::Image image = GetImage();
	Size isz = image.GetSize();
	Ctrl *q = GetParent()->GetParent();
	if(!q || !q->IsTransparent())
		w.DrawRect(sz, checked && !HasMouse() ? Blend(SColorFace, SColorLight) : SColorFace);
	int li = IsEnabled() ? HasMouse() ? GetMouseLeft() ? CTRL_PRESSED
						                               : checked ? 5 : CTRL_HOT
				                       : checked ? 4 : CTRL_NORMAL
					     : CTRL_DISABLED;
	ChPaint(w, sz, style->look[li]);
	Point ip = (sz - isz) / 2;
	Size tsz;
	if(kind != NOLABEL)
		tsz = GetTextSize(text, style->font);
	if(kind == BOTTOMLABEL) {
		ip.y = 3;
		w.DrawText((sz.cx - tsz.cx) / 2, isz.cy + 6, text, style->font, style->textcolor[li]);
	}
	
	if(kind == RIGHTLABEL) {
		ip.x = 3;
		w.DrawText(isz.cx + 6, (sz.cy - tsz.cy) / 2, text, style->font, style->textcolor[li]);
	}
	if(IsEnabled())
		DrawHighlightImage(w, ip.x, ip.y, image, HasMouse());
	else
		w.DrawImage(ip.x, ip.y, DisabledImage(image));
}

void  ToolButton::MouseEnter(Point, dword)
{
	BarCtrl::SendHelpLine(this);
	Refresh();
}

void  ToolButton::MouseLeave()
{
	BarCtrl::ClearHelpLine(this);
	Refresh();
}

Size  ToolButton::GetMinSize() const
{
	UPP::Image image = GetImage();
	Size sz = image.GetSize();
	if(sz.IsEmpty())
		sz = Size(16, 16);
	sz += 6;
	if(text.GetCount()) {
		Size tsz = GetTextSize(text, style->font);
		if(kind == BOTTOMLABEL) {
			sz.cy += tsz.cy + 3;
			sz.cx = max(sz.cx, tsz.cx + 9);
		}
		if(kind == RIGHTLABEL) {
			sz.cx += tsz.cx + 6;
			sz.cy = max(sz.cy, tsz.cy + 6);
		}
	}
	return max(sz, minsize);
}

void  ToolButton::LeftDown(Point, dword)
{
	Refresh();
	if(repeat)
		WhenAction();
}

void  ToolButton::LeftRepeat(Point, dword)
{
	Refresh();
	if(repeat)
		WhenAction();
}

void  ToolButton::LeftUp(Point, dword)
{
	Refresh();
	if(!repeat)
		WhenAction();
}

bool  ToolButton::HotKey(dword key)
{
	if(key == accel) {
		WhenAction();
		return true;
	}
	return false;
}

void ToolButton::FinalSync()
{
	if(checked != paint_checked)
		Refresh();
}

String ToolButton::GetDesc() const
{
	return tiptext;
}

END_UPP_NAMESPACE
