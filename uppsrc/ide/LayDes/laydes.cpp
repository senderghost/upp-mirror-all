#include "LayDes.h"

using namespace LayoutKeys;

#define IMAGECLASS LayImg
#define IMAGEFILE  <ide/LayDes/LayDes.iml>
#include <Draw/iml_source.h>

#define LTIMING(x) // TIMING(x)

#define MARGIN 8

static void sLay1(int& pos, int& r, int align, int a, int b, int sz)
{
	pos = a;
	int size = b;
	switch(align) {
	case Ctrl::CENTER:
		pos = (sz - b) / 2 + a;
		break;
	case Ctrl::RIGHT:
		pos = sz - (a + b);
		break;
	case Ctrl::SIZE:
		size = sz - (a + b);
		break;
	}
	r = pos + max(size, 0);
}

Rect CalcRect(Ctrl::LogPos pos, Size sz)
{
	Rect r;
	sLay1(r.left, r.right, pos.x.GetAlign(), pos.x.GetA(), pos.x.GetB(), sz.cx);
	sLay1(r.top, r.bottom, pos.y.GetAlign(), pos.y.GetA(), pos.y.GetB(), sz.cy);
	return r;
}

void LayDes::AddHandle(Draw& w, int x, int y)
{
	w.DrawRect(x, y, 6, 6, SLtBlue);
	handle.Add(Point(x, y));
}

Point LayDes::Normalize(Point p)
{
	p += sb;
	p.Offset(-MARGIN, -MARGIN);
	return p;
}

void LayDes::SetSb()
{
	Size sz = Size(0, 0);
	if(currentlayout >= 0) {
		LayoutData& l = CurrentLayout();
		sz = l.size;
		for(int i = 0; i < l.item.GetCount(); i++)
			sz = max(sz, (Size)::CalcRect(l.item[i].pos, l.size).BottomRight());
	}
	sb.SetTotal(sz + Size(MARGIN, MARGIN));
	sb.SetPage(sb.GetReducedViewSize());
}

void LayDes::Scroll()
{
	Refresh();
}

void LayDes::Layout()
{
	SetSb();
	layoutlist.ScrollIntoCursor();
}

void LayDes::GetSprings(Rect& l, Rect& t, Rect& r, Rect& b)
{
	if(currentlayout < 0 || !cursor.GetCount()) {
		l = t = r = b = Null;
		return;
	}
	Rect ir = ::CalcRect(CurrentItem().pos, CurrentLayout().size);
	int h4 = ir.Height() / 4;
	int w4 = ir.Width() / 4;
	l = RectC(-MARGIN, ir.top + h4 - 5, ir.left + MARGIN, 10);
	t = RectC(ir.left + w4 - 5, -MARGIN, 10, ir.top + MARGIN);
	r = RectC(ir.right, ir.bottom - h4 - 5, 9999, 10);
	b = RectC(ir.right - w4 - 5, ir.bottom, 10, 9999);
}

void LayDes::DrawSpring(Draw& w, const Rect& r, bool horz, bool hard)
{
	if(hard)
		w.DrawRect(horz ? r.DeflatedVert(4) : r.DeflatedHorz(4), SRed);
	else
		if(horz)
			for(int x = r.left; x < r.right; x += 4)
				w.DrawRect(x, r.top, 1, r.Height(), SGray);
		else
			for(int y = r.top; y < r.bottom; y += 4)
				w.DrawRect(r.left, y, r.Width(), 1, SGray);
}

int LayDes::ParseLayoutRef(String cls, String& base) const
{
	const char *p = cls;
	if(p[0] != 'W' || p[1] != 'i' || p[2] != 't' || p[3] != 'h')
		return -1;
	const char *b = (p += 4);
	while(IsAlNum(*p) || *p == '_')
		p++;
	if(p <= b)
		return -1;
	String layoutid(b, p);
	int fi = FindFieldIndex(layout, &LayoutData::name, layoutid);
	if(fi < 0)
		return -1;
	while(*p && (byte)*p <= ' ')
		p++;
	if(*p++ != '<')
		return -1;
	while(*p && (byte)*p <= ' ')
		p++;
	const char *e = cls.End();
	while(e > p && (byte)e[-1] <= ' ')
		e--;
	if(e > p && e[-1] == '>')
		e--;
	while(e > p && (byte)e[-1] <= ' ')
		e--;
	base = String(p, e);
	return fi;
}

void LayDes::PaintLayoutItems(Draw& w, int layid, Size size, Index<int>& passed, const Vector<bool>& cursor)
{
	if(passed.Find(layid) >= 0)
		return;
	passed.Add(layid);
	LayoutData& l = layout[layid];
	bool nocursor = true;
	for(int i = 0; i < l.item.GetCount(); i++) {
		LayoutItem& m = l.item[i];
		if(m.hide)
			continue;
		Rect r = ::CalcRect(m.pos, size);
		String dummy;
		int lr = ParseLayoutRef(m.type, dummy);
		DrawFrame(w, r, SWhiteGray);
		w.Clipoff(r);
		if(lr < 0)
			m.Paint(w, r.Size());
		else if(i >= cursor.GetCount() ? nocursor : cursor[i])
		{
			PaintLayoutItems(w, lr, r.Size(), passed, Vector<bool>());
			nocursor = false;
		}
		w.End();
	}
	passed.Drop();
}

void LayDes::Paint(Draw& w)
{
	LTIMING("Paint");
	Size sz = GetSize();
	w.DrawRect(sz, SWhite);
	if(!IsNull(fileerror))
		w.DrawText(16, 16, "FILE ERROR: " + fileerror, Arial(14).Bold(), SRed);
	if(currentlayout < 0)
		return;
	w.Offset(-sb.Get());
	LayoutData& l = CurrentLayout();
	w.Offset(MARGIN, MARGIN);
	w.DrawRect(0, 0, l.size.cx, l.size.cy, SLtGray);
	if(setting.paintgrid) {
		int gx = minmax((int)~setting.gridx, 1, 32);
		int gy = minmax((int)~setting.gridy, 1, 32);
		for(int x = 0; x < l.size.cx; x += gx)
			for(int y = 0; y < l.size.cy; y += gy)
				w.DrawRect(x, y, 1, 1, SWhite);
	}
	DrawFrame(w, -1, -1, l.size.cx + 2, l.size.cy + 2, SBlack);
	handle.Clear();
	AddHandle(w, l.size.cx, l.size.cy / 2 - 3);
	AddHandle(w, l.size.cx / 2 - 3, l.size.cy);
	AddHandle(w, l.size.cx, l.size.cy);
	int i;
	Index<int> passed;
	Vector<bool> cursorflags;
	if(!cursor.IsEmpty()) {
		cursorflags.SetCount(l.item.GetCount(), cursor.IsEmpty());
		for(i = 0; i < cursor.GetCount(); i++)
			cursorflags[cursor[i]] = true;
	}
	PaintLayoutItems(w, currentlayout, l.size, passed, cursorflags);
	if(!HasCapture() || draghandle == 14) {
		for(i = 0; i < cursor.GetCount(); i++) {
			LayoutItem& m = l.item[cursor[i]];
			Rect r = ::CalcRect(m.pos, l.size);
			DrawFatFrame(w, r, i == cursor.GetCount() - 1 ? SCyan : SBrown, -3);
			if(i == cursor.GetCount() - 1) {
				int lrm = r.left + r.Width() / 2 - 3;
				int tbm = r.top + r.Height() / 2 - 3;
				AddHandle(w, r.left - 6, r.top - 6);
				AddHandle(w, lrm, r.top - 6);
				AddHandle(w, r.right, r.top - 6);
				AddHandle(w, r.left - 6, tbm);
				AddHandle(w, r.right, tbm);
				AddHandle(w, r.left - 6, r.bottom);
				AddHandle(w, lrm, r.bottom);
				AddHandle(w, r.right, r.bottom);
			}
		}
		if(cursor.GetCount()) {
			LayoutItem& m = CurrentItem();
			Rect l, t, r, b;
			GetSprings(l, t, r, b);
			DrawSpring(w, l, true, m.pos.x.GetAlign() & Ctrl::LEFT);
			DrawSpring(w, r, true, m.pos.x.GetAlign() & Ctrl::RIGHT);
			DrawSpring(w, t, false, m.pos.y.GetAlign() & Ctrl::TOP);
			DrawSpring(w, b, false, m.pos.y.GetAlign() & Ctrl::BOTTOM);
		}
	}
	if(HasCapture() && draghandle == 14)
		DrawFrame(w, dragrect.Normalized(), SLtRed);
	w.End();
	w.End();
}

void  LayDes::SaveState()
{
	if(currentlayout < 0)
		return;
	CurrentLayout().SaveState();
	SetBar();
}

void  LayDes::SetStatus(bool down)
{
	String s;
	if(currentlayout >= 0) {
		Size sz = CurrentLayout().size;
		s << sz;
		if(cursor.GetCount()) {
			Rect r = ::CalcRect(CurrentItem().pos, sz);
			s << ": " << r << " - {" << sz.cx - r.right << ", " << sz.cy - r.bottom << '}';
		}
	}
	status.SetLabel(s);
	Refresh();
	SetBar();
	SetSb();
}

int   LayDes::FindHandle(Point p)
{
	for(int i = 0; i < handle.GetCount(); i++) {
		Point h = handle[i];
		if(p.x >= h.x - 1 && p.x < h.x + 7 && p.y >= h.y - 1 && p.y < h.y + 7)
			return i;
	}
	return -1;
}

int   LayDes::FindItem(Point p)
{
	if(currentlayout < 0)
		return -1;
	LayoutData& l = CurrentLayout();
	int ii = -1;
	int min = INT_MAX;
	for(int i = 0; i < l.item.GetCount(); i++) {
		LayoutItem& m = l.item[i];
		if(m.hide)
			continue;
		Rect r = ::CalcRect(m.pos, l.size);
		if(r.Contains(p)) {
			int mm = r.Width() * r.Height();
			if(mm < min) {
				ii = i;
				min = mm;
			}
		}
	}
	return ii;
}

Image LayDes::CursorImage(Point p, dword keyflags)
{
	int hi;
	if(HasCapture())
		hi = draghandle;
	else
	 	hi = FindHandle(Normalize(p));
	const Image& (*id[11])() = {
		CtrlImg::SizeHorz0, CtrlImg::SizeVert0, CtrlImg::SizeHoVe0,
		CtrlImg::SizeHoVe0, CtrlImg::SizeVert0, CtrlImg::SizeVeHo0,
		CtrlImg::SizeHorz0, CtrlImg::SizeHorz0,
		CtrlImg::SizeVeHo0, CtrlImg::SizeVert0, CtrlImg::SizeHoVe0,
	};
	if(hi >= 0 && hi < 11)
		return (*id[hi])();
	return Image::Arrow();
}

Ctrl::Logc MakeLogc(int align, int a, int b, int sz)
{
	int isz = b - a;
	switch(align) {
	case Ctrl::LEFT:
		return Ctrl::PosLeft(a, isz);
	case Ctrl::RIGHT:
		return Ctrl::PosRight(sz - b, isz);
	case Ctrl::CENTER:
		return Ctrl::PosCenter(isz, a - (sz - isz) / 2);
	}
	return Ctrl::PosSize(a, sz - b);
}

Ctrl::LogPos MakeLogPos(int ax, int ay, const Rect& r, Size sz)
{
	return Ctrl::LogPos(MakeLogc(ax, r.left, r.right, sz.cx),
	                    MakeLogc(ay, r.top, r.bottom, sz.cy));
}

Ctrl::LogPos MakeLogPos(Ctrl::LogPos p, const Rect& r, Size sz)
{
	return MakeLogPos(p.x.GetAlign(), p.y.GetAlign(), r, sz);
}

struct IDisplay : public Display {
	Color paper, ink;
	void Paint(Draw& w, const Rect& r, const Value& q,
	           Color, Color, dword s) const {
		w.DrawRect(r, paper);
		DrawSmartText(w, r.left + 8, r.top, r.Width(),
					  String(IsString(q) ? q : StdConvert().Format(q)), StdFont(), ink);
	}
	IDisplay(Color paper, Color ink)
		: paper(paper), ink(ink) {}
};

struct TDisplay : public Display {
	Color paper, ink;

	void Paint(Draw& w, const Rect& r, const Value& q,
	           Color, Color, dword s) const {
		w.DrawRect(r, paper);
		int dx = r.Height() * 8 / 3;
		Image icon = GetTypeIcon(String(q), dx, r.Height(), 1, paper);
		w.DrawImage(r.left + 8, r.top + (r.Height() - icon.GetSize().cy) / 2, icon);
		DrawSmartText(w, r.left + dx + 12, r.top, r.Width(), String(q), StdFont(), ink);
	}
	TDisplay(Color paper, Color ink)
		: paper(paper), ink(ink) {}
};

struct IDisplayH : public Display {
	Color paper, ink;
	void Paint(Draw& w, const Rect& r, const Value& q,
	           Color, Color, dword s) const {
		w.DrawRect(r, paper);
		DrawSmartText(w, r.left + 8, r.top, r.Width(),
					  String(IsString(q) ? q : StdConvert().Format(q)), StdFont().Italic(), ink);
	}
	IDisplayH(Color paper, Color ink)
		: paper(paper), ink(ink) {}
};

struct TDisplayH : public Display {
	Color paper, ink;

	void Paint(Draw& w, const Rect& r, const Value& q,
	           Color, Color, dword s) const {
		w.DrawRect(r, paper);
		int dx = r.Height() * 8 / 3;
		Image icon = GetTypeIcon(String(q), dx, r.Height(), 1, paper);
		w.DrawImage(r.left + 8, r.top + (r.Height() - icon.GetSize().cy) / 2, icon);
		DrawSmartText(w, r.left + dx + 12, r.top, r.Width(), String(q), StdFont().Italic(), ink);
	}
	TDisplayH(Color paper, Color ink)
		: paper(paper), ink(ink) {}
};

void LayDes::SyncItems()
{
	LTIMING("SyncItems");
	if(currentlayout < 0)
		return;
	int i;
	for(i = 0; i < item.GetCount(); i++)
		SyncItem(i, 0);
	for(i = 0; i < cursor.GetCount(); i++)
		SyncItem(cursor[i], 1);
	if(cursor.GetCount()) {
		SyncItem(cursor.Top(), 2);
		item.SetCursor(cursor.Top());
	}
	else
		item.KillCursor();
	SetStatus();
	SyncProperties(true);
}

void LayDes::SyncItem(int i, int style)
{
	if(CurrentLayout().item[i].hide) {
		static IDisplayH dnormal(SWhite, SBlack);
		static IDisplayH dselect(SWhiteGray, SBlack);
		static IDisplayH dcursor(SLtGray, SBlack);
		static TDisplayH tnormal(SWhite, SBlack);
		static TDisplayH tselect(SWhiteGray, SBlack);
		static TDisplayH tcursor(SLtGray, SBlack);
		static IDisplayH lnormal(SWhite, SGreen);
		static IDisplayH lselect(SWhiteGray, SGreen);
		static IDisplayH lcursor(SLtGray, SGreen);
		const Display *noicon[] = { &dnormal, &dselect, &dcursor };
		const Display *isicon[] = { &tnormal, &tselect, &tcursor };
		const Display *label[] = { &lnormal, &lselect, &lcursor };
		bool icons = setting.showicons;
		item.SetDisplay(i, 0, *(icons ? isicon : noicon)[style]);
		item.SetDisplay(i, 1, *(IsNull(CurrentLayout().item[i].variable) ? label : noicon)[style]);
	}
	else {
		static IDisplay dnormal(SWhite, SBlack);
		static IDisplay dselect(SWhiteGray, SBlack);
		static IDisplay dcursor(SLtGray, SBlack);
		static TDisplay tnormal(SWhite, SBlack);
		static TDisplay tselect(SWhiteGray, SBlack);
		static TDisplay tcursor(SLtGray, SBlack);
		static IDisplay lnormal(SWhite, SGreen);
		static IDisplay lselect(SWhiteGray, SGreen);
		static IDisplay lcursor(SLtGray, SGreen);
		const Display *noicon[] = { &dnormal, &dselect, &dcursor };
		const Display *isicon[] = { &tnormal, &tselect, &tcursor };
		const Display *label[] = { &lnormal, &lselect, &lcursor };
		bool icons = setting.showicons;
		item.SetDisplay(i, 0, *(icons ? isicon : noicon)[style]);
		item.SetDisplay(i, 1, *(IsNull(CurrentLayout().item[i].variable) ? label : noicon)[style]);
	}
}

void LayDes::SyncProperties(bool sync_type_var)
{
	property.Clear();
	if(sync_type_var) {
		type.Disable();
		variable.Disable();
		type <<= variable <<= Null;
	}
	if(cursor.GetCount()) {
		LayoutItem& m = CurrentItem();
		int i;
		for(i = 0; i < m.property.GetCount(); i++) {
			property.Add(m.property[i]);
			m.property[i].WhenAction = THISBACK(PropertyChanged);
		}
		if(sync_type_var) {
			String tp = m.type;
			type <<= m.type;
			for(i = 0; i < cursor.GetCount() - 1; i++)
				if(CurrentLayout().item[cursor[i]].type != tp) {
					type <<= Null;
					break;
				}
			variable <<= m.variable;
			type.Enable();
			variable.Enable();
		}
	}
}

void LayDes::SelectOne(int ii, dword flags)
{
	if(ii < 0) {
		if(flags & (K_SHIFT|K_CTRL))
			return;
		cursor.Clear();
	}
	else
	if(flags & (K_SHIFT|K_CTRL)) {
		int q = FindIndex(cursor, ii);
		if(q >= 0)
			cursor.Remove(q);
		else
			cursor.Add(ii);
	}
	else {
		cursor.Clear();
		cursor.Add(ii);
	}
	SyncItems();
}

void LayDes::StoreItemRects()
{
	if(currentlayout < 0)
		return;
	LayoutData& l = CurrentLayout();
	itemrect.SetCount(cursor.GetCount());
	for(int i = 0; i < cursor.GetCount(); i++)
		itemrect[i] = ::CalcRect(l.item[cursor[i]].pos, l.size);
}

void  LayDes::LeftDown(Point p, dword keyflags)
{
	if(currentlayout < 0)
		return;
	SaveState();
	SetFocus();
	SetCapture();
	LayoutData& l = CurrentLayout();
	draglayoutsize = l.size;
	p = Normalize(p);
	dragbase = p;
	draghandle = FindHandle(dragbase);
	if(draghandle >= 0)
		StoreItemRects();
	else {
		int ii = FindItem(p);
		if(ii >= 0) {
			if(GetShift() || GetCtrl() || FindIndex(cursor, ii) < 0)
				SelectOne(ii, keyflags);
			if(cursor.GetCount()) {
				draghandle = 11;
				StoreItemRects();
				SetStatus();
			}
		}
		else {
			if(cursor.GetCount()) {
				LayoutItem& m = CurrentItem();
				StoreItemRects();
				Rect lr, tr, rr, br;
				GetSprings(lr, tr, rr, br);
				int xa = m.pos.x.GetAlign();
				int ya = m.pos.y.GetAlign();
				if(lr.Contains(p))
					xa ^= 1;
				if(rr.Contains(p))
					xa ^= 2;
				if(tr.Contains(p))
					ya ^= 1;
				if(br.Contains(p))
					ya ^= 2;
				if(xa != m.pos.x.GetAlign() || ya != m.pos.y.GetAlign()) {
					SetSprings(MAKELONG(xa, ya));
					SetStatus();
					return;
				}
			}
			dragrect.left = dragrect.right = p.x;
			dragrect.top = dragrect.bottom = p.y;
			draghandle = 14;
			if(GetCtrl() || GetShift())
				basesel = cursor.GetCount();
			else {
				basesel = 0;
				cursor.Clear();
			}
			SyncItems();
		}
	}
	SetStatus(true);
}

void  LayDes::LeftRepeat(Point p, dword keyflags)
{
	MouseMove(p, keyflags);
}

void  LayDes::MouseMove(Point p, dword keyflags)
{
	if(!HasCapture() || currentlayout < 0)
		return;
	p = Normalize(p);
	LayoutData& l = CurrentLayout();
	bool smallmove = max(abs(p.x - dragbase.x), abs(p.y - dragbase.y)) < 4;
	if(draghandle == 14) {
		dragrect.right = p.x;
		dragrect.bottom = p.y;
		cursor.SetCount(basesel);
		Rect r = dragrect.Normalized();
		int mind = INT_MAX;
		int mini = -1;
		for(int i = 0; i < l.item.GetCount(); i++) {
			LayoutItem& m = l.item[i];
			Rect ir = ::CalcRect(m.pos, l.size);
			if(r.Contains(ir) && FindIndex(cursor, i) < 0) {
				Point ip = ir.CenterPoint();
				int mm = (ip.x - dragrect.left) * (ip.x - dragrect.left)
				       + (ip.y - dragrect.top) * (ip.y - dragrect.top);
				if(mm < mind) {
					mind = mm;
					mini = cursor.GetCount();
				}
				cursor.Add(i);
			}
		}
		if(mini >= 0)
			Swap(cursor.Top(), cursor[mini]);
		if(cursor.GetCount())
			item.SetCursor(cursor.Top());
		else
			item.KillCursor();
		SyncItems();
		SetStatus(false);
		LTIMING("MouseMove Sync");
		Sync();
		return;
	}
	int gx = 1;
	int gy = 1;
	if(usegrid == !(keyflags & K_ALT)) {
		gx = minmax((int)~setting.gridx, 1, 32);
		gy = minmax((int)~setting.gridy, 1, 32);
	}
	p -= dragbase;
	if(draghandle < 3) {
		if((draghandle + 1) & 1)
			l.size.cx = max(0, draglayoutsize.cx + p.x) / gx * gx;
		if((draghandle + 1) & 2)
			l.size.cy = max(0, draglayoutsize.cy + p.y) / gy * gy;
		SetStatus(true);
		SetSb();
		Sync();
		return;
	}
	if(!item.IsCursor())
		return;
	if(draghandle == 11) {
		if(smallmove)
			return;
		draghandle = 12;
	}
	Point md = Point(0, 0);
	for(int i = 0; i < cursor.GetCount(); i++) {
		LayoutItem& m = l.item[cursor[i]];
		Rect r = itemrect[i];
		Size minsize = ignoreminsize ? Size(0, 0) : m.GetMinSize();
		if(keyflags & K_CTRL)
			minsize = Size(0, 0);
		if(draghandle == 3 || draghandle == 4 || draghandle == 5)
			r.top = min(r.bottom - minsize.cy, (r.top + p.y) / gy * gy);
		if(draghandle == 8 || draghandle == 9 || draghandle == 10)
			r.bottom = max(r.top + minsize.cy, (r.bottom + p.y) / gy * gy);
		if(draghandle == 3 || draghandle == 6 || draghandle == 8)
			r.left = min(r.right - minsize.cx, (r.left + p.x) / gy * gy);
		if(draghandle == 5 || draghandle == 7 || draghandle == 10)
			r.right = max(r.left + minsize.cx, (r.right + p.x) / gy * gy);
		if(draghandle == 12) {
			Size sz = r.Size();
			if(i == 0) {
				Rect q = r;
				r.left = (r.left + p.x) / gx * gx;
				r.top = (r.top + p.y) / gy * gy;
				md = r.TopLeft() - q.TopLeft();
			}
			else
				r += md;
			r.SetSize(sz);
		}
		m.pos = MakeLogPos(m.pos, r, draglayoutsize);
//		if(i == cursor.GetCount() - 1)
//			sb.ScrollInto(r.Offseted(MARGIN, MARGIN));
	}
	SetStatus(true);
	Sync();
}

void  LayDes::LeftUp(Point p, dword keyflags)
{
	if(draghandle == 11 && (keyflags & (K_SHIFT|K_CTRL)) == 0)
		SelectOne(FindItem(Normalize(p)), 0);
	draghandle = -1;
	SyncItems();
}

void LayDes::CreateCtrl(const String& _type)
{
	if(currentlayout < 0)
		return;
	LayoutData& l = CurrentLayout();
	int c = l.item.GetCount();
	if(cursor.GetCount())
		c = Max(cursor) + 1;
	LayoutItem& m = l.item.Insert(c);
	m.Create(_type);
	Point p = dragbase;
	if(usegrid) {
		p.x = p.x / (int)~setting.gridx * (int)~setting.gridx;
		p.y = p.y / (int)~setting.gridy * (int)~setting.gridy;
	}
	Rect r(p, m.GetStdSize());
	m.pos = MakeLogPos(Ctrl::LEFT, Ctrl::TOP, r, l.size);
	cursor.Clear();
	cursor.Add(c);
	ReloadItems();
	if(IsNull(_type))
		type.SetFocus();
	else {
		int q = m.FindProperty("SetLabel");
		if(q >= 0)
			m.property[q].SetFocus();
		else
			variable.SetFocus();
	}
}

void LayDes::Group(Bar& bar, const String& group)
{
	int i;
	Vector<String> type;
	for(i = 0; i < LayoutTypes().GetCount(); i++) {
		LayoutType& m = LayoutTypes()[i];
		if((IsNull(group) || m.group == group) && m.kind == LAYOUT_CTRL)
			type.Add(LayoutTypes().GetKey(i));
	}
	Sort(type);
	int h = ScreenInfo().GetFontInfo(StdFont()).GetHeight();
	int w = 8 * h / 3;
	((MenuBar&)bar).LeftGap(w + 2);
	int q = 0;
	for(i = 0; i < type.GetCount(); i++) {
		bar.Add(type[i], GetTypeIcon(type[i], w, h, 0, SLtGray),
		        THISBACK1(CreateCtrl, type[i]));
		if((q++ + 2) % 16 == 0)
			bar.Break();
	}
}

void LayDes::TemplateGroup(Bar& bar, TempGroup tg)
{
	int i;
	Vector<String> type;
	for(i = 0; i < LayoutTypes().GetCount(); i++) {
		LayoutType& m = LayoutTypes()[i];
		if((IsNull(tg.group) || m.group == tg.group) && m.kind == LAYOUT_CTRL)
			type.Add(LayoutTypes().GetKey(i));
	}
	Sort(type);
	int h = ScreenInfo().GetFontInfo(StdFont()).GetHeight();
	int w = 8 * h / 3;
	((MenuBar&)bar).LeftGap(w + 2);
	int q = 0;
	for(i = 0; i < type.GetCount(); i++) {
		bar.Add(type[i], GetTypeIcon(type[i], w, h, 0, SLtGray),
		        THISBACK1(CreateCtrl, tg.temp + '<' + type[i] + '>'));
		if((q++ + 2) % 16 == 0)
			bar.Break();
	}
}

void LayDes::Template(Bar& bar, const String& temp)
{
	Index<String> group;
	Vector<String> type;
	int h = ScreenInfo().GetFontInfo(StdFont()).GetHeight();
	int w = 8 * h / 3;
	((MenuBar&)bar).LeftGap(w + 2);
	int i;
	for(i = 0; i < LayoutTypes().GetCount(); i++) {
		LayoutType& m = LayoutTypes()[i];
		if(!IsNull(m.group))
			group.FindAdd(m.group);
		else
		if(m.kind == LAYOUT_CTRL)
			type.Add(LayoutTypes().GetKey(i));
	}
	Vector<String> sg = group.PickKeys();
	Sort(sg);
	Sort(type);
	int q = 0;
	for(i = 0; i < sg.GetCount(); i++) {
		bar.Add(sg[i], THISBACK1(TemplateGroup, TempGroup(temp, sg[i])));
		if((q++ + 2) % 16 == 0)
			bar.Break();
	}
	bar.Add("All", THISBACK1(TemplateGroup, TempGroup(temp, String())));
	if((q++ + 2) % 16 == 0)
		bar.Break();
	for(i = 0; i < type.GetCount(); i++) {
		bar.Add(type[i], GetTypeIcon(type[i], w, h, 0, SLtGray),
		        THISBACK1(CreateCtrl, temp + '<' + type[i] + '>'));
		if((q++ + 2) % 16 == 0)
			bar.Break();
	}
}

void LayDes::Templates(Bar& bar)
{
	Vector<String> temp;
	int i;
	for(i = 0; i < LayoutTypes().GetCount(); i++)
		if(LayoutTypes()[i].kind == LAYOUT_TEMPLATE)
			temp.Add(LayoutTypes().GetKey(i));
	Sort(temp);
	int q = 0;
	for(i = 0; i < temp.GetCount(); i++) {
		bar.Add(temp[i], THISBACK1(Template, temp[i]));
		if((q++ + 2) % 16 == 0)
			bar.Break();
	}
}

void LayDes::RightDown(Point p, dword keyflags)
{
	if(currentlayout < 0 || HasCapture()) return;
	dragbase = Normalize(p);
	MenuBar menu;
	int h = ScreenInfo().GetFontInfo(StdFont()).GetHeight();
	int w = 8 * h / 3;
	menu.LeftGap(w + 2);
	menu.Add("User class", THISBACK1(CreateCtrl, ""));
	menu.Separator();
	Index<String> group;
	Vector<String> type;
	int i;
	for(i = 0; i < LayoutTypes().GetCount(); i++) {
		LayoutType& m = LayoutTypes()[i];
		if(!IsNull(m.group))
			group.FindAdd(m.group);
		else
		if(m.kind == LAYOUT_CTRL)
			type.Add(LayoutTypes().GetKey(i));
	}
	Vector<String> sg = group.PickKeys();
	Sort(sg);
	Sort(type);
	int q = 0;
	for(i = 0; i < sg.GetCount(); i++) {
		menu.Add(sg[i], THISBACK1(Group, sg[i]));
		if((q++ + 2) % 16 == 0)
			menu.Break();
	}
	menu.Add("All", THISBACK1(Group, String()));
	menu.Add("Templates", THISBACK(Templates));
	if((q++ + 2) % 16 == 0)
		menu.Break();
	for(i = 0; i < type.GetCount(); i++) {
		menu.Add(type[i], GetTypeIcon(type[i], w, h, 0, SLtGray),
		                  THISBACK1(CreateCtrl, type[i]));
		if((q++ + 2) % 16 == 0)
			menu.Break();
	}
	menu.Execute();
}

void  LayDes::LoadItems()
{
	int nitems = CurrentLayout().item.GetCount();
	item.SetCount(nitems);
	LayoutData& l = CurrentLayout();
	for(int i = 0; i < nitems; i++)
		LoadItem(i);
	property.Clear();
}

String GetLabel(const LayoutItem& m)
{
	EscValue l = m.ExecuteMethod("GetLabelMethod");
	if(l.IsVoid())
		for(int p = 0; p < m.property.GetCount(); p++)
			if(m.property[p].name == "SetLabel") {
				Value prop = ~m.property[p];
				return IsString(prop) && !IsNull(prop) ? AsCString(prop) : Null;
			}
	return l;
}

void LayDes::LoadItem(int ii)
{
	const LayoutItem& m = CurrentLayout().item[ii];
	String varlbl = m.variable;
	if(IsNull(varlbl))
		varlbl = GetLabel(m);
	item.Set(ii, 0, m.type);
	item.Set(ii, 1, varlbl);
	item.Set(ii, 2, m.hide);
}

void  LayDes::ReloadItems()
{
	int q = item.GetScroll();
	LoadItems();
	item.ScrollTo(q);
	SyncItems();
}

void  LayDes::Undo()
{
	if(currentlayout < 0)
		return;
	if(CurrentLayout().IsUndo()) {
		CurrentLayout().Undo();
		cursor.Clear();
		ReloadItems();
	}
}

void LayDes::Redo()
{
	if(currentlayout < 0)
		return;
	if(CurrentLayout().IsRedo()) {
		CurrentLayout().Redo();
		cursor.Clear();
		ReloadItems();
	}
}

void LayDes::Cut()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	Copy();
	Delete();
}

void LayDes::Delete()
{
	SaveState();
	Vector<int> sel(cursor, 1);
	Sort(sel);
	cursor.Clear();
	CurrentLayout().item.Remove(sel);
	ReloadItems();
}

String LayDes::SaveSelection()
{
	return CurrentLayout().Save(charset, cursor) + "\r\n";
}

LayoutData LayDes::LoadLayoutData(const String& s)
{
	try {
		LayoutData l;
		CParser p(s);
		l.Read(p, charset);
		return l;
	}
	catch(CParser::Error) {}
	return LayoutData();
}

void LayDes::Copy()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	WriteClipboardUnicodeText(ToUnicode(SaveSelection(), charset));
}

void LayDes::SelectAll()
{
	if(currentlayout < 0)
		return;
	LayoutData& l = CurrentLayout();
	int q = cursor.GetCount() ? cursor.Top() : -1;
	cursor.Clear();
	for(int i = 0; i < l.item.GetCount(); i++)
		if(i != q)
			cursor.Add(i);
	if(q >= 0)
		cursor.Add(q);
	SyncItems();
}

void LayDes::Duplicate()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	SaveState();
	LayoutData& l = CurrentLayout();
	LayoutData d = LoadLayoutData(SaveSelection());
	int q = Max(cursor) + 1;
	cursor.Clear();
	for(int i = 0; i < d.item.GetCount(); i++) {
		LayoutItem& m = d.item[i];
		d.item[i].pos = MakeLogPos(m.pos, ::CalcRect(m.pos, l.size).Offseted(20, 20), l.size);
		cursor.Add(q + i);
	}
	CurrentLayout().item.InsertPick(q, d.item);
	ReloadItems();
}

void LayDes::Matrix()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	SaveState();
	if(matrix.Execute() != IDOK)
		return;
	LayoutData& l = CurrentLayout();
	Rect r = ::CalcRect(l.item[cursor[0]].pos, l.size);
	for(int i = 1; i < cursor.GetCount(); i++)
		r.Union(::CalcRect(l.item[cursor[i]].pos, l.size));
	String ls = SaveSelection();
	int q = Max(cursor) + 1;
	for(int x = 0; x < Nvl((int)~matrix.nx, 1); x++)
		for(int y = 0; y < Nvl((int)~matrix.ny, 1); y++)
			if(x || y) {
				LayoutData d = LoadLayoutData(ls);
				for(int i = 0; i < d.item.GetCount(); i++) {
					LayoutItem& m = d.item[i];
					Rect r = ::CalcRect(m.pos, l.size);
					r.Offset((r.Width() + Nvl((int)~matrix.dx)) * x,
					         (r.Height() + Nvl((int)~matrix.dy)) * y);
					d.item[i].pos = MakeLogPos(m.pos, r, l.size);
					cursor.Add(q + i);
				}
				int w = d.item.GetCount();
				CurrentLayout().item.InsertPick(q, d.item);
				q += w;
			}
	ReloadItems();
}

void LayDes::Paste()
{
	if(currentlayout < 0)
		return;
	SaveState();
	try {
		LayoutData l = LoadLayoutData(FromUnicode(ReadClipboardUnicodeText(), charset));
		int q = item.GetCount();
		if(cursor.GetCount())
		{
			q = 0;
			for(int i = 0; i < cursor.GetCount(); i++)
				q = max(q, cursor[i] + 1);
		}
		cursor.Clear();
		for(int i = 0; i < l.item.GetCount(); i++)
			cursor.Add(i + q);
		CurrentLayout().item.InsertPick(q, l.item);
		ReloadItems();
	}
	catch(CParser::Error) {}
}

void LayDes::Align(int type)
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	SaveState();
	LayoutData& l = CurrentLayout();
	Rect cr = ::CalcRect(l.item[cursor.Top()].pos, l.size);
	for(int i = 0; i < cursor.GetCount(); i++) {
		LayoutItem& m = l.item[cursor[i]];
		Rect r = ::CalcRect(m.pos, l.size);
		switch(type) {
		case A_LEFT:
			r.OffsetHorz(cr.left - r.left);
			break;
		case A_HCENTER:
			r.OffsetHorz(cr.left + (cr.Width() - r.Width()) / 2 - r.left);
			break;
		case A_RIGHT:
			r.OffsetHorz(cr.right - r.right);
			break;
		case A_TOP:
			r.OffsetVert(cr.top - r.top);
			break;
		case A_VCENTER:
			r.OffsetVert(cr.top + (cr.Height() - r.Height()) / 2 - r.top);
			break;
		case A_BOTTOM:
			r.OffsetVert(cr.bottom - r.bottom);
			break;
		case A_SAMEWIDTH:
			r.right = r.left + cr.Width();
			break;
		case A_SAMEHEIGHT:
			r.bottom = r.top + cr.Height();
			break;
		case A_SAMESIZE:
			r.SetSize(cr.Size());
			break;
		case A_HORZCENTER:
			r.OffsetHorz((l.size.cx - r.Width()) / 2 - r.left);
			break;
		case A_VERTCENTER:
			r.OffsetVert((l.size.cy - r.Height()) / 2 - r.top);
			break;
		case A_MINWIDTH:
			r.SetSize(m.GetMinSize().cx, r.Height());
			break;
		case A_MINHEIGHT:
			r.SetSize(r.Width(), m.GetMinSize().cy);
			break;
		case A_LABEL:
			if(m.type == "Label") {
				Rect rr = r;
				int q = cursor[i] - 1;
				while(q >= 0) {
					if(l.item[q].type != "Label") {
						rr = ::CalcRect(l.item[q].pos, l.size);
						break;
					}
					q--;
				}
				q = cursor[i] + 1;
				while(q < l.item.GetCount()) {
					if(l.item[q].type != "Label") {
						rr = ::CalcRect(l.item[q].pos, l.size);
						break;
					}
					q++;
				}
				r.OffsetVert(rr.top + (rr.Height() - r.Height()) / 2 - r.top);
			}
			break;
		}
		m.pos = MakeLogPos(m.pos, r, l.size);
//		if(i == cursor.GetCount() - 1)
//			sb.ScrollInto(r.Offseted(MARGIN, MARGIN));
	}
	SetStatus();
}

void LayDes::SetSprings(dword s)
{
	if(currentlayout < 0)
		return;
	LayoutData& l = CurrentLayout();
	SaveState();
	int xa = (int16)LOWORD(s);
	int ya = (int16)HIWORD(s);
	for(int i = 0; i < cursor.GetCount(); i++) {
		Ctrl::LogPos& pos = l.item[cursor[i]].pos;
		Rect r = ::CalcRect(pos, l.size);
		if(xa >= 0)
			pos.x = MakeLogc(xa, r.left, r.right, l.size.cx);
		if(ya >= 0)
			pos.y = MakeLogc(ya, r.top, r.bottom, l.size.cy);
		if(xa == AUTOSPRING) {
			pos.x = MakeLogc((r.left < l.size.cx / 2 ? LEFT : 0) |
			                 (r.right > l.size.cx / 2 ? RIGHT : 0),
			                 r.left, r.right, l.size.cx);
			pos.y = MakeLogc((r.top < l.size.cy / 2 ? TOP : 0) |
			                 (r.bottom > l.size.cy/ 2 ? BOTTOM : 0),
			                 r.top, r.bottom, l.size.cy);
		}
	}
	SetStatus();
}

void LayDes::ShowSelection(bool s)
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	LayoutData& l = CurrentLayout();
	for(int i = 0; i < cursor.GetCount(); i++)
		l.item[cursor[i]].hide = !s;
	SyncItems();
	Refresh();
}

void LayDes::MoveUp()
{
	SaveState();
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	LayoutData& l = CurrentLayout();
	Vector<int> sc(cursor, 1);
	Sort(sc);
	int q = 0;
	while(q < sc.GetCount() && sc[q] == q)
		q++;
	int im = q;
	while(q < sc.GetCount()) {
		int i = sc[q++];
		l.item.Swap(i, i - 1);
	}
	for(q = 0; q < cursor.GetCount(); q++)
		if(cursor[q] >= im)
			cursor[q]--;
	ReloadItems();
}

void LayDes::MoveDown()
{
	SaveState();
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	LayoutData& l = CurrentLayout();
	Vector<int> sc(cursor, 1);
	Sort(sc);
	int q = sc.GetCount() - 1;
	int u = l.item.GetCount() - 1;
	while(q >= 0 && sc[q] == u--)
		q--;
	int im = q >= 0 ? sc[q] : -1;
	while(q >= 0) {
		int i = sc[q--];
		l.item.Swap(i, i + 1);
	}
	for(q = 0; q < cursor.GetCount(); q++)
		if(cursor[q] <= im)
			cursor[q]++;
	ReloadItems();
}

void LayDes::Flush()
{
	currentlayout = -1;
}

LayoutData& LayDes::CurrentLayout()
{
	return layout[currentlayout];
}

void LayDes::LayoutCursor()
{
	Flush();
	draghandle = -1;
	currentlayout = layoutlist.GetCursor();
	cursor.Clear();
	type.Disable();
	variable.Disable();
	property.Clear();
	if(currentlayout < 0)
		return;
	LoadItems();
	SyncItems();
	SetSb();
	SetFocus();
}

void LayDes::PrevLayout()
{
	layoutlist.Key(K_UP, 0);
}

void LayDes::NextLayout()
{
	layoutlist.Key(K_DOWN, 0);
}

void LayDes::SyncLayoutList()
{
	layoutlist.Clear();
	int i;
	for(i = 0; i < layout.GetCount(); i++)
		layoutlist.Add(layout[i].name);
	LayoutCursor();
}

int CharFilterCid(int c)
{
	return IsAlNum(c) || c == '_' ? c : 0;
}

void LayDes::AddLayout()
{
	String name;
	if(!EditText(name, "Add new layout", "Layout", CharFilterCid))
		return;
	int q = layout.GetCount();
	layout.Add().name = name;
	SyncLayoutList();
	layoutlist.SetCursor(q);
	LayoutCursor();
}

void LayDes::RenameLayout()
{
	if(currentlayout < 0)
		return;
	String name = layout[currentlayout].name;
	if(!EditText(name, "Rename layout", "Layout", CharFilterCid))
		return;
	int q = layoutlist.GetCursor();
	layout[currentlayout].name = name;;
	SyncLayoutList();
	layoutlist.SetCursor(q);
	LayoutCursor();
}

void LayDes::RemoveLayout()
{
	if(currentlayout < 0 || !PromptYesNo("Remove [* " + DeQtf(layout[currentlayout].name) + "] ?"))
		return;
	int q = layoutlist.GetCursor();
	layout.Remove(currentlayout);
	SyncLayoutList();
	if(q < layoutlist.GetCount())
		layoutlist.SetCursor(q);
	else
	if(layoutlist.GetCount())
		layoutlist.SetCursor(layoutlist.GetCount() - 1);
	LayoutCursor();
}

void LayDes::MoveLayoutUp()
{
	int q = layoutlist.GetCursor();
	if(layoutlist.GetCursor() > 0) {
		layout.Swap(q, q - 1);
		layoutlist.SwapUp();
	}
}

void LayDes::MoveLayoutDown()
{
	int q = layoutlist.GetCursor();
	if(q >= 0 && q < layoutlist.GetCount() - 1) {
		layout.Swap(q, q + 1);
		layoutlist.SwapDown();
	}
}

void LayDes::LayoutMenu(Bar& bar)
{
	bar.Add("Add new layout..", THISBACK(AddLayout));
	bar.Add("Rename layout..", THISBACK(RenameLayout));
	bar.Add("Remove layout..", THISBACK(RemoveLayout));
	bar.Separator();
	bar.Add(layoutlist.IsCursor() && layoutlist.GetCursor() > 0,
	        AK_MOVELAYOUTUP, LayImg::MoveUp(), THISBACK(MoveLayoutUp));
	bar.Add(layoutlist.IsCursor() && layoutlist.GetCursor() < layoutlist.GetCount() - 1,
	        AK_MOVELAYOUTDOWN, LayImg::MoveDown(), THISBACK(MoveLayoutDown));
}

LayoutItem& LayDes::CurrentItem()
{
	return CurrentLayout().item[cursor.Top()];
}

void LayDes::PropertyChanged()
{
	if(item.IsCursor())
	{
		CurrentItem().Invalidate();
		int c = item.GetCursor();
		LoadItem(c);
		SyncItem(c, 2);
	}
	Refresh();
	SetBar();
}

void LayDes::FrameFocus()
{
	if(property.HasFocusDeep()) {
		SaveState();
		SetStatus();
	}
}

void LayDes::ItemClick()
{
	if(currentlayout < 0)
		return;
	SaveState();
	int c = cursor.GetCount() ? cursor.Top() : -1;
	if(GetShift()) {
		if(cursor.GetCount()) {
			int i = minmax(item.GetCursor(), 0, cursor.Top());
			int m = max(item.GetCursor(), cursor.Top());
			cursor.Clear();
			while(i <= m)
				cursor.Add(i++);
			SyncItems();
		}
	}
	else if(item.IsCursor()) {
		if(!GetCtrl())
			cursor.Clear();
		cursor.Add(item.GetCursor());
	}
	SetFocus();
	SyncItems();
}

void LayDes::SyncUsc()
{
	type.ClearList();
	for(int i = 0; i < LayoutTypes().GetCount(); i++)
		type.AddList(LayoutTypes().GetKey(i));
	if(currentlayout >= 0) {
		LayoutData& d = CurrentLayout();
		for(int i = 0; i < d.item.GetCount(); i++)
			d.item[i].Invalidate();
	}
	Refresh();
}

void LayDes::TypeEdit()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	LayoutData& l = CurrentLayout();
	for(int i = 0; i < cursor.GetCount(); i++) {
		LayoutItem& m = l.item[cursor[i]];
		String s = m.SaveProperties(charset);
		m.Create(~type);
		try {
			CParser p(s);
			m.ReadProperties(p, charset, false);
		}
		catch(CParser::Error&) {}
		item.Set(cursor[i], 0, m.type);
	}
	SyncProperties(false);
	SetStatus();
}

void LayDes::VariableEdit()
{
	if(currentlayout < 0 || cursor.GetCount() == 0)
		return;
	LayoutData& l = CurrentLayout();
	LayoutItem& m = l.item[cursor.Top()];
	m.variable = ~variable;
	if(IsNull(m.variable))
		item.Set(cursor.Top(), 1, GetLabel(m));
	else
		item.Set(cursor.Top(), 1, m.variable);
	SyncItem(cursor.Top(), 2);
}

static int RoundStep(int org, int d, int g)
{
	return d ? itimesfloor(org + d * g + (d > 0 ? 0 : g - 1), g) - org : 0;
}

bool LayDes::Key(dword key, int count)
{
	SaveState();
	Point move(0, 0);
	if(currentlayout >= 0 && !cursor.IsEmpty()) {
		switch(key & ~K_CTRL) {
		case K_SHIFT_LEFT:   move.x = -1; break;
		case K_SHIFT_RIGHT:  move.x = +1; break;
		case K_SHIFT_UP:     move.y = -1; break;
		case K_SHIFT_DOWN:   move.y = +1; break;
		}
		if(move.x | move.y) {
			Size grid(1, 1);
			if(usegrid) {
				grid.cx = minmax<int>(~setting.gridx, 1, 32);
				grid.cy = minmax<int>(~setting.gridy, 1, 32);
			}
			LayoutData& l = CurrentLayout();
			Rect master = ::CalcRect(l.item[cursor.Top()].pos, l.size);
			Size shift;
			shift.cx = RoundStep(key & K_CTRL ? master.Width()  : master.left, move.x, grid.cx);
			shift.cy = RoundStep(key & K_CTRL ? master.Height() : master.top,  move.y, grid.cy);
			for(int i = 0; i < cursor.GetCount(); i++) {
				LayoutItem& item = l.item[cursor[i]];
				Rect rc = ::CalcRect(item.pos, l.size);
				rc.right  += shift.cx;
				rc.bottom += shift.cy;
				if(!(key & K_CTRL)) {
					rc.left += shift.cx;
					rc.top  += shift.cy;
				}
				item.pos = MakeLogPos(item.pos, rc, l.size);
			}
			SetStatus(false);
			return true;
		}
	}
	switch(key) {
	case K_PAGEUP:
		PrevLayout();
		return true;
	case K_PAGEDOWN:
		NextLayout();
		return true;
	case K_UP:
	case K_DOWN:
		{
			dword k = (key == K_PAGEUP ? K_UP : key == K_PAGEDOWN ? K_DOWN : key);
			Ptr<Ctrl> focus = GetFocusCtrl();
			if(!item.IsCursor() && item.GetCount() > 0)
				item.SetCursor(k = K_DOWN ? 0 : item.GetCount() - 1);
			else
				item.Key(k, count);
			ItemClick();
			if(!!focus)
				focus->SetWantFocus();
		}
		return true;
	default:
		if(key >= ' ' && key < 65536) {
			if(currentlayout < 0 || cursor.GetCount() == 0)
				return false;
			LayoutItem& m = CurrentItem();
			for(int i = 0; i < m.property.GetCount(); i++)
				if(m.property[i].name == "SetLabel")
					return m.property[i].PlaceFocus(key, count);
		}
		break;
	}
	return MenuBar::Scan(THISBACK(LayoutMenu), key);
}
