#include "CtrlLib.h"

#define LDUMP(x) // DUMP(x)

Switch& Switch::Set(int i, const Value& val) {
	cs.At(i).value = val;
	Refresh();
	return *this;
}

Switch& Switch::Set(int i, const Value& val, const char *text) {
	Case& v = cs.At(i);
	if(value.IsVoid())
		value = val;
	SetLabel(i, text);
	v.value = val;
	Refresh();
	return *this;
}

Switch& Switch::Add(const Value& val, const char *text) {
	Set(cs.GetCount(), val, text);
	return *this;
}

Switch& Switch::Add(const char *text) {
	Set(cs.GetCount(), cs.GetCount(), text);
	return *this;
}

int Switch::GetIndex() {
	for(int i = 0; i < cs.GetCount(); i++)
		if(cs[i].value == value)
			return i;
	return -1;
}

Switch&  Switch::SetLabel(int i, const char *text) {
	if(i >= cs.GetCount())
		cs.At(i).value = i;
	Case& v = cs[i];
	v.accesskey = ExtractAccessKey(text, v.label);
	Refresh();
	return *this;
}

dword Switch::GetAccessKeys() const
{
	dword keys = 0;
	for(int i = 0; i < cs.GetCount(); i++)
		keys |= AccessKeyBit(cs[i].accesskey);
	return keys;
}

void  Switch::AssignAccessKeys(dword used)
{
	for(int i = 0; i < cs.GetCount(); i++) {
		Case& v = cs[i];
		if(!v.accesskey) {
			v.accesskey = ChooseAccessKey(v.label, used);
			if(v.accesskey) Refresh();
			used |= AccessKeyBit(v.accesskey);
		}
	}
	Ctrl::AssignAccessKeys(used);
}

Switch& Switch::SetLabel(const char *text) {
	const char *q = text;
	int i = 0;
	const char *s = text;
	while(*s) {
		if(*s == '\r') {
			SetLabel(i++, String(q, s));
			q = ++s;
			if(*q == '\n') {
				q++;
				s++;
			}
		}
		else
		if(*s == '\n') {
			SetLabel(i++, String(q, s));
			q = ++s;
		}
		else
			s++;
	}
	SetLabel(i++, String(q, s));
	cs.SetCount(i);
	return *this;
}

void  Switch::SetData(const Value& val) {
	if(val != value) {
		RefreshCase(GetIndex());
		value = val;
		RefreshCase(GetIndex());
		Update();
	}
}

Value Switch::GetData() const {
	return value;
}

Rect  Switch::GetCaseRect(int i) const {
	Size sz = GetSize();
	if(posx.GetCount())
		return RectC(i ? posx[i - 1] : 0, 0, posx[i], sz.cy);
	else
		return RectC(0, linecy * i, sz.cx, linecy);
}

Rect  Switch::GetCheckRect(int i) const {
	Size sz = GetSize();
	int cx = IsXPStyle() ? CtrlImg::Radio0().GetSize().cx : CtrlImg::switch0().GetSize().cx;
	if(posx.GetCount())
		return RectC(i ? posx[i - 1] : 0, 0, cx, sz.cy);
	else
		return RectC(0, linecy * i, cx, linecy);
}

void Switch::EnableCase(int i, bool enable) {
	cs.At(i).enabled = enable;
	Refresh(GetCaseRect(i));
}

void Switch::EnableValue(const Value& val, bool enable) {
	for(int i = 0; i < cs.GetCount(); i++)
		if(cs[i].value == val)
			EnableCase(i, enable);
}

void  Switch::RefreshCase(int i) {
	if(i >= 0 && i < cs.GetCount())
		Refresh(HasFocus() ? GetCaseRect(i) : GetCheckRect(i));
}

void Switch::GotFocus() {
	RefreshCase(GetIndex());
}

void Switch::LostFocus() {
	int i = GetIndex();
	if(i >= 0 && i < cs.GetCount())
		Refresh(GetCaseRect(i));
}

void Switch::Paint(Draw& w) {
	if(cs.GetCount() == 0) return;
	Size sz = GetSize();
	if(!IsTransparent())
		w.DrawRect(0, 0, sz.cx, sz.cy, SLtGray);
	int tcy = w.GetTextSize("W", font).cy;
	linecy = max(16, tcy + 2);
	int y = 0;
	int x = 0;
	int ty = (linecy - tcy) / 2;
	bool horz = linecy * cs.GetCount() > sz.cy;
	if(horz)
		posx.SetCount(cs.GetCount());
	else
		posx.Clear();
	bool ds = !IsShowEnabled();
	int i;
	light = -1;
	for(i = 0; i < cs.GetCount(); i++) {
		Case& v = cs[i];
		bool fs = HasFocus() && (pushindex == i || v.value == value && pushindex < 0);
		bool dv = ds || !v.enabled;

		Size isz = (IsXPStyle() ? GetPushImage(I_RADIO0, I_NORMAL) : CtrlImg::option0()).GetSize();
		Size tsz = GetSmartTextSize(w, v.label, font);
		int iy = (tsz.cy - isz.cy) / 2;

		Rect hr = RectC(x, y, horz ? tsz.cx + isz.cx + 4 : sz.cx, linecy);
		bool mousein = HasMouseIn(hr);
		if(mousein)
			light = i;
		Image img;
		if(IsXPStyle()) {
			int q = dv ? I_DISABLED :
			        pushindex == i ? I_PUSH :
			        mousein || fs ? I_HIGHLIGHT :
			        I_NORMAL;
			fs = false;
			img = GetPushImage(v.value == value ? I_RADIO1 : I_RADIO0, q);
		}
		else {
			img = v.value == value ? dv ? CtrlImg::switch1d()
										: pushindex == i ? CtrlImg::switch1f()
														 : CtrlImg::switch1()
								   : dv ? CtrlImg::switch0d()
										: pushindex == i ? CtrlImg::switch0f()
														 : CtrlImg::switch0();
		}
		w.DrawImage(x, y + iy, img);
		DrawSmartText(w, x + isz.cx + 4, y, sz.cx, v.label, font,
		              dv ? SColorDisabled : IsReadOnly() ? SLtBlue : SColorText,
		              VisibleAccessKeys() ? v.accesskey : 0);
		if(horz) {
			x += hr.Width() + sz.cy / 2;
			posx[i] = x;
		}
		else
			y += linecy;
	}
	if(horz)
		posx[i - 1] = sz.cx;
}

int Switch::GetIndex(Point p) {
	if(posx.GetCount()) {
		for(int i = 0; i < posx.GetCount(); i++)
			if(p.x < posx[i]) return cs[i].enabled ? i : -1;
		return -1;
	}
	else {
		int i = p.y / linecy;
		i = i >= 0 && i < cs.GetCount() ? i : -1;
		return i < 0 ? -1 : cs[i].enabled ? i : -1;
	}
}

void Switch::MouseMove(Point p, dword keyflags) {
	if(IsReadOnly()) return;
	int i = GetIndex(p);
	int a = -1;
	if(keyflags & K_MOUSELEFT)
		a = i;
	if(pushindex != a) {
		RefreshCase(pushindex);
		RefreshCase(a);
		pushindex = a;
	}
	if(i != light) {
		RefreshCase(light);
		RefreshCase(i);
	}
}

void Switch::LeftDown(Point p, dword keyflags) {
	if(IsReadOnly()) return;
	if(Ctrl::ClickFocus()) SetWantFocus();
	pushindex = GetIndex();
	MouseMove(p, keyflags);
}

void Switch::LeftUp(Point p, dword keyflags) {
	if(IsReadOnly()) return;
	if(pushindex >= 0 && pushindex < cs.GetCount()) {
		RefreshCase(GetIndex());
		const Value& v = cs[pushindex].value;
		if(v != value) {
			value = v;
			UpdateAction();
		}
		RefreshCase(pushindex);
	}
	pushindex = -1;
}

void Switch::MouseLeave() {
	RefreshCase(light);
	RefreshCase(pushindex);
	pushindex = -1;
}

bool Switch::Key(dword key, int) {
	if(IsReadOnly()) return false;
	int index, i;
	index = i = GetIndex();
	if(key == K_UP || key == K_LEFT) {
		for(int t = 0; t < cs.GetCount(); t++) {
			if(--index < 0) index = cs.GetCount() - 1;
			if(cs[index].enabled)
				break;
		}
	}
	else
	if(key == K_DOWN || key == K_RIGHT) {
		for(int t = 0; t < cs.GetCount(); t++) {
			if(++index >= cs.GetCount()) index = 0;
			if(cs[index].enabled)
				break;
		}
	}
	else
		return false;
	if(i != index && cs[index].enabled) {
		value = cs[index].value;
		RefreshCase(i);
		RefreshCase(index);
		UpdateAction();
	}
	return true;
}

bool Switch::HotKey(dword key) {
	if(IsReadOnly()) return false;
	for(int i = 0; i < cs.GetCount(); i++) {
		if(cs[i].enabled && CompareAccessKey(cs[i].accesskey, key)) {
			value = cs[i].value;
			UpdateActionRefresh();
			return true;
		}
	}
	return false;
}

void Switch::CancelMode() {
	pushindex = -1;
}

Switch::Switch() {
	linecy = 16;
	Transparent();
	NoInitFocus();
}

Switch::~Switch() {}
