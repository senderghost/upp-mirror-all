#include "CtrlLib.h"

#define LTIMING(x) // RTIMING(x)

ArrayCtrl::Column::Column() {
	convert = NULL;
	edit = NULL;
	display = &StdDisplay();
	accel = NULL;
	margin = -1;
	cached = false;
	clickedit = true;
}

ArrayCtrl::Column& ArrayCtrl::Column::Cache() {
	cached = true;
	return *this;
}

ArrayCtrl::Column& ArrayCtrl::Column::Edit(Ctrl& e) {
	e.Hide();
	e.SetFrame(NullFrame());
	edit = &e;
	arrayctrl->AddChild(edit);
	return *this;
}

ArrayCtrl::Column& ArrayCtrl::Column::SetConvert(const Convert& c) {
	convert = &c;
	ClearCache();
	arrayctrl->Refresh();
	return *this;
}

ArrayCtrl::Column& ArrayCtrl::Column::SetFormat(const char *fmt)
{
	FormatConvert::SetFormat(fmt);
	return SetConvert(*this);
}

ArrayCtrl::Column& ArrayCtrl::Column::SetDisplay(const Display& d)
{
	display = &d;
	ClearCache();
	arrayctrl->SyncCtrls();
	arrayctrl->Refresh();
	return *this;
}

ArrayCtrl::Column& ArrayCtrl::Column::Ctrls(Callback1<One<Ctrl>&> _factory)
{
	factory = _factory;
	arrayctrl->hasctrls = arrayctrl->headerctrls = true;
	arrayctrl->SyncCtrls();
	arrayctrl->Refresh();
	return *this;
}

void ArrayCtrl::Column::ClearCache() {
	cache.Clear();
}

void ArrayCtrl::Column::InvalidateCache(int i) {
	if(i < 0) return;
	if(cache.Is< Vector<String> >() && i < cache.Get< Vector<String> >().GetCount())
		cache.Get< Vector<String> >()[i] = String::GetVoid();
	if(cache.Is< Vector<Value> >() && i < cache.Get< Vector<Value> >().GetCount())
		cache.Get< Vector<Value> >()[i] = Value();
}

void ArrayCtrl::Column::InsertCache(int i) {
	if(i < 0) return;
	if(cache.Is< Vector<String> >() && i < cache.Get< Vector<String> >().GetCount())
		cache.Get< Vector<String> >().Insert(i) = String::GetVoid();
	if(cache.Is< Vector<Value> >() && i < cache.Get< Vector<Value> >().GetCount())
		cache.Get< Vector<Value> >().Insert(i);
}

void ArrayCtrl::Column::RemoveCache(int i) {
	if(i < 0) return;
	if(cache.Is< Vector<String> >() && i < cache.Get< Vector<String> >().GetCount())
		cache.Get< Vector<String> >().Remove(i);
	if(cache.Is< Vector<Value> >() && i < cache.Get< Vector<Value> >().GetCount())
		cache.Get< Vector<Value> >().Remove(i);
}

ArrayCtrl::Column& ArrayCtrl::Column::InsertValue(const Value& v) {
	arrayctrl->IndexInfo(arrayctrl->Pos(pos[0])).InsertValue(v);
	return *this;
}

ArrayCtrl::Column& ArrayCtrl::Column::InsertValue(ValueGen& g) {
	arrayctrl->IndexInfo(arrayctrl->Pos(pos[0])).InsertValue(g);
	return *this;
}

HeaderCtrl::Column& ArrayCtrl::Column::HeaderTab() {
	return arrayctrl->header.Tab(arrayctrl->column.GetIndex(*this));
}

void ArrayCtrl::InvalidateCache(int ri)
{
	for(int i = 0; i < column.GetCount(); i++)
		column[i].InvalidateCache(ri);
}

void ArrayCtrl::CellCtrl::LeftDown(Point, dword)
{
	if(ctrl->IsWantFocus())
		ctrl->SetFocus();
}

void ArrayCtrl::CellInfo::Set(Ctrl *ctrl)
{
	CellCtrl *cc = new CellCtrl;
	cc->ctrl = ctrl;
	cc->Add(*ctrl);
	cc->Color(SColorPaper);
	ptr.Set1(cc);
}

ArrayCtrl::CellInfo::~CellInfo()
{
	if(ptr.GetBit()) {
		CellCtrl *cc = (CellCtrl *)ptr.GetPtr();
		delete cc->ctrl;
		delete cc;
	}
}

Ctrl& ArrayCtrl::SetCtrl(int i, int j, Ctrl *newctrl)
{
	newctrl->SetData(GetColumn(i, j));
	hasctrls = true;
	RefreshRow(i);
	CellInfo& ci = cellinfo.At(i).At(j);
	ci.Set(newctrl);
	Ctrl& c = ci.GetCtrl();
	if(newctrl->GetPos().x.GetAlign() == LEFT && newctrl->GetPos().x.GetB() == 0)
		newctrl->HSizePos().VCenterPos(STDSIZE);
	j--;
	for(;;) {
		while(j >= 0) {
			if(IsCtrl(i, j)) {
				AddChild(&c, &GetCtrl(i, j));
				return c;
			}
			j--;
		}
		i--;
		if(i < 0) {
			AddChild(&c, NULL);
			return c;
		}
		j = cellinfo[i].GetCount();
	}
}

bool  ArrayCtrl::IsCtrl(int i, int j) const
{
	return i < cellinfo.GetCount() && j < cellinfo[i].GetCount() && cellinfo[i][j].IsCtrl();
}

ArrayCtrl::CellCtrl& ArrayCtrl::GetCtrl(int i, int j)
{
	return cellinfo[i][j].GetCtrl();
}

const ArrayCtrl::CellCtrl& ArrayCtrl::GetCtrl(int i, int j) const
{
	return cellinfo[i][j].GetCtrl();
}

void ArrayCtrl::SetDisplay(int i, int j, const Display& d)
{
	cellinfo.At(i).At(j).Set(d);
	RefreshRow(i);
}

const Display& ArrayCtrl::GetDisplay(int i, int j)
{
	if(i < cellinfo.GetCount() && j < cellinfo[i].GetCount() && cellinfo[i][j].IsDisplay())
		return cellinfo[i][j].GetDisplay();
	return *column[j].display;
}

const Display& ArrayCtrl::GetDisplay(int j)
{
	return *column[j].display;
}

int ArrayCtrl::Pos(int pos) const {
	if(pos >= 0) return pos;
	pos = idx.Find(Id(-pos));
	ASSERT(pos >= 0);
	return pos;
}

Value ArrayCtrl::Get0(int i, int ii) const {
	ASSERT(ii >= 0);
	if(hasctrls)
		for(int j = 0; j < column.GetCount(); j++)
			if(IsCtrl(i, j)) {
				const Column& m = column[j];
				ASSERT(m.pos.GetCount() == 1);
				if(Pos(m.pos[0]) == ii)
					return GetCtrl(i, j).ctrl->GetData();
			}
	if(i < array.GetCount()) {
		const Vector<Value>& v = array[i].line;
		if(ii < v.GetCount())
			return v[ii];
	}
	return Null;
}

Value ArrayCtrl::Get(int ii) const {
	ASSERT(IsCursor());
	int i;
	for(i = 0; i < column.GetCount(); i++) {
		const Column& m = column[i];
		if(m.edit)
			for(int j = 0; j < m.pos.GetCount(); j++)
				if(Pos(m.pos[j]) == ii) {
					Value v = m.edit->GetData();
					return m.pos.GetCount() > 1 && IsValueArray(v) ? ValueArray(v)[j] : v;
				}
	}
	for(i = 0; i < control.GetCount(); i++) {
		const Control& c = control[i];
		if(Pos(c.pos) == ii)
			return c.ctrl->GetData();
	}
	return Get0(cursor, ii);
}

Value ArrayCtrl::Get(Id id) const {
	return Get(GetPos(id));
}

Value ArrayCtrl::GetOriginal(int ii) const {
	return Get0(cursor, ii);
}

Value ArrayCtrl::GetOriginal(Id id) const {
	return GetOriginal(GetPos(id));
}

Value ArrayCtrl::GetKey() const {
	return IsCursor() ? Get(0) : Null;
}

Value ArrayCtrl::GetOriginalKey() const {
	return IsCursor() ? GetOriginal(0) : Null;
}

bool ArrayCtrl::IsModified(int ii) const {
	ASSERT(IsCursor());
	int i;
	if(ii < modify.GetCount() && modify[ii]) return true;
	for(i = 0; i < column.GetCount(); i++) {
		const Column& m = column[i];
		if(m.edit)
			for(int j = 0; j < m.pos.GetCount(); j++)
				if(Pos(m.pos[j]) == ii && m.edit->IsModified())
					return true;
	}
	for(i = 0; i < control.GetCount(); i++) {
		const Control& c = control[i];
		if(Pos(c.pos) == ii && c.ctrl->IsModified())
			return true;
	}
	return false;
}

bool ArrayCtrl::IsModified(Id id) const {
	return IsModified(GetPos(id));
}

void ArrayCtrl::ColEditSetData(int j) {
	ASSERT(IsCursor());
	Column& m = column[j];
	if(m.edit)
		m.edit->SetData(GetColumn(cursor, j));
}

void ArrayCtrl::CtrlSetData(int j) {
	ASSERT(IsCursor());
	Control& c = control[j];
	c.ctrl->Enable();
	if(IsNull(c.pos))
		c.ctrl->SetData(cursor);
	else
		c.ctrl->SetData(GetOriginal(Pos(c.pos)));
}

void ArrayCtrl::SetCtrlValue(int i, int ii, const Value& v)
{
	if(hasctrls)
		for(int j = 0; j < column.GetCount(); j++)
			if(IsCtrl(i, j)) {
				const Column& m = column[j];
				ASSERT(m.pos.GetCount() == 1);
				if(Pos(m.pos[0]) == ii) {
					GetCtrl(i, j).ctrl->SetData(v);
					return;
				}
			}
}

void ArrayCtrl::Set(int ii, const Value& v) {
	ASSERT(IsCursor());
	array.At(cursor).line.At(ii) = v;
	int i;
	for(i = 0; i < column.GetCount(); i++) {
		Column& m = column[i];
		if(m.edit)
			for(int j = 0; j < m.pos.GetCount(); j++)
				if(Pos(m.pos[j]) == ii) {
					ColEditSetData(i);
					break;
				}
	}
	for(i = 0; i < control.GetCount(); i++) {
		const Control& c = control[i];
		if(Pos(c.pos) == ii)
			CtrlSetData(i);
	}
	SetCtrlValue(cursor, ii, v);
	modify.At(ii, false) = true;
	InvalidateCache(cursor);
	RefreshRow(cursor);
}

void ArrayCtrl::Set(Id id, const Value& v) {
	Set(GetPos(id), v);
}

void ArrayCtrl::Set0(int i, int ii, const Value& v) {
	if(i == cursor)
		Set(ii, v);
	else
		SetCtrlValue(i, ii, v);
	array.At(i).line.At(ii) = v;
}

void ArrayCtrl::AfterSet(int i)
{
	SetSb();
	Refresh();
	SyncCtrls(i);
	InvalidateCache(cursor);
}

void ArrayCtrl::Set(int i, int ii, const Value& v)
{
	Set0(i, ii, v);
	AfterSet(i);
}

void ArrayCtrl::Set(int i, Id id, const Value& v) {
	Set(i, GetPos(id), v);
}

Value ArrayCtrl::Get(int i, int ii) const {
	return i == cursor ? Get(ii) : Get0(i, ii);
}

Value ArrayCtrl::Get(int i, Id id) const {
	return Get(i, GetPos(id));
}

void  ArrayCtrl::SetCount(int n) {
	ASSERT(n >= 0);
	if(cursor >= n)
		CancelCursor();
	array.SetCount(n);
	if(cellinfo.GetCount() > array.GetCount())
		cellinfo.SetCount(array.GetCount());
	Refresh();
	SyncCtrls();
	SetSb();
	PlaceEdits();
}

Value ArrayCtrl::GetColumn(int row, int col) const {
	const Column& c = column[col];
	if(c.pos.GetCount() == 0) return row;
	if(c.pos.GetCount() == 1) return Get0(row, Pos(c.pos[0]));
	ValueArray va;
	for(int i = 0; i < c.pos.GetCount(); i++)
		va.Add(Get0(row, Pos(c.pos[i])));
	return va;
}

Value ArrayCtrl::GetConvertedColumn(int i, int col) {
	LTIMING("GetConvertedColumn");
	Column& m = column[col];
	Value v = GetColumn(i, col);
	if(!m.convert) return v;
	if(m.cache.Is< Vector<String> >() && i < m.cache.Get< Vector<String> >().GetCount()) {
		const String& s = m.cache.Get< Vector<String> >()[i];
		if(!s.IsVoid()) return s;
	}
	if(m.cache.Is< Vector<Value> >() && i < m.cache.Get< Vector<Value> >().GetCount()) {
		const Value& v = m.cache.Get< Vector<Value> >()[i];
		if(!v.IsVoid()) return v;
	}
	Value r = m.convert->Format(v);
	if(m.cached) {
		if(m.cache.IsEmpty())
			m.cache.Create< Vector<String> >();
		if(IsString(r) && m.cache.Is< Vector<String> >())
			m.cache.Get< Vector<String> >().At(i, String::GetVoid()) = r;
		if(!IsString(r) && m.cache.Is< Vector<String> >())
			m.cache.Create< Vector<Value> >();
		if(m.cache.Is< Vector<Value> >())
			m.cache.Get< Vector<Value> >().At(i) = r;
		ASSERT(m.pos.GetCount() || m.cache.IsEmpty());
	}
	return r;
}

int ArrayCtrl::GetCount() const {
	return max(virtualcount, array.GetCount());
}

void ArrayCtrl::SetVirtualCount(int c) {
	virtualcount = c;
	Refresh();
	SetSb();
}

void ArrayCtrl::SetSb() {
	sb.SetTotal(GetTotalCy() + IsInserting() * (GetLineCy() + horzgrid));
	sb.SetPage(GetSize().cy);
}

void ArrayCtrl::Layout() {
	SetSb();
	HeaderScrollVisibility();
	PlaceEdits();
	SyncCtrls();
}

void ArrayCtrl::Reline(int i, int y)
{
	while(i < ln.GetCount()) {
		Ln& p = ln[i];
		p.y = y;
		y += Nvl(p.cy, linecy) + horzgrid;
		i++;
	}
	SetSb();
}

int  ArrayCtrl::GetLineY(int i) const
{
	return i < ln.GetCount() ? ln[i].y
	                         : (ln.GetCount() ? ln.Top().y + Nvl(ln.Top().cy, linecy) + horzgrid : 0)
	                           + (linecy + horzgrid) * (i - ln.GetCount());
}

ArrayCtrl& ArrayCtrl::SetLineCy(int cy)
{
	linecy = cy;
	Reline(0, 0);
	sb.SetLine(cy);
	return *this;
}

void ArrayCtrl::SetLineCy(int i, int cy)
{
	int q = ln.GetCount();
	if(i < q) {
		ln[i].cy = cy;
		Reline(i, ln[i].y);
	}
	else {
		while(ln.GetCount() <= i)
			ln.Add().cy = linecy;
		ln[i].cy = cy;
		if(q > 0)
			Reline(q - 1, ln[q - 1].y);
		else
			Reline(0, 0);
	}
}

int  ArrayCtrl::GetTotalCy() const
{
	int i = GetCount();
	return i ? GetLineY(i - 1) + GetLineCy(i - 1) + horzgrid: 0;
}

int  ArrayCtrl::GetLineCy(int i) const {
	return i < ln.GetCount() ? Nvl(ln[i].cy, linecy) : linecy;
}

int  ArrayCtrl::GetLineAt(int y) const {
	if(!GetCount()) return Null;
	if(y < 0 || y >= GetTotalCy()) return Null;
	int l = 0;
	int h = GetCount();
	while(l < h) {
		int m = (l + h) / 2;
		int yy = GetLineY(m);
		if(yy == y) return m;
		if(yy < y)
			l = m + 1;
		else
			h = m;
	}
	return l > 0 ? l - 1 : l;
}

void  ArrayCtrl::SyncCtrls(int from)
{
	LTIMING("SyncCtrls");
	if(!hasctrls)
		return;
	Ptr<Ctrl> restorefocus = GetFocusChildDeep();
	Size sz = GetSize();
	Ctrl *p = NULL;
	for(int i = from; i < array.GetCount(); i++)
		for(int j = 0; j < column.GetCount(); j++) {
			bool ct = IsCtrl(i, j);
			if(!ct && column[j].factory) {
				One<Ctrl> newctrl;
				column[j].factory(newctrl);
				newctrl->SetData(GetColumn(i, j));
				newctrl->WhenAction << Proxy(WhenCtrlsAction);
				if(newctrl->GetPos().x.GetAlign() == LEFT && newctrl->GetPos().x.GetB() == 0)
					newctrl->HSizePos().VCenterPos(STDSIZE);
				CellInfo& ci = cellinfo.At(i).At(j);
				ci.Set(newctrl.Detach());
				Ctrl& c = ci.GetCtrl();
				AddChild(&c, p);
				ct = true;
			}
			if(ct) {
				Rect r = GetCellRectM(i, j);
				Ctrl& c = GetCtrl(i, j);
				p = &c;
				if(r.bottom < 0 || r.top > sz.cy)
					c.SetRect(-1000, -1000, 1, 1);
				else
					c.SetRect(r);
			}
		}
	if(restorefocus)
		restorefocus->SetFocus();
}

Point ArrayCtrl::FindCellCtrl(Ctrl *ctrl)
{
	if(hasctrls)
		for(int i = 0; i < cellinfo.GetCount(); i++) {
			Vector<CellInfo>& ci = cellinfo[i];
			for(int j = 0; j < ci.GetCount(); j++)
				if(IsCtrl(i, j)) {
					CellCtrl& c = GetCtrl(i, j);
					if(&c == ctrl || c.ctrl == ctrl)
						return Point(j, i);
				}
		}
	return Null;
}

void ArrayCtrl::ChildGotFocus()
{
	if(cursor >= 0)
		RefreshRow(cursor);
	Point p = FindCellCtrl(GetFocusCtrl());
	if(!IsNull(p))
		if(nocursor)
			ScrollInto(p.y);
		else
			SetCursor(p.y);
	Ctrl::ChildGotFocus();
}

void ArrayCtrl::ChildLostFocus()
{
	if(cursor >= 0)
		RefreshRow(cursor);
	Ctrl::ChildLostFocus();
}

void  ArrayCtrl::Paint(Draw& w) {
	LTIMING("Paint");
	Size size = GetSize();
	Rect r;
	r.bottom = 0;
	bool hasfocus = HasFocusDeep();
	int i = GetLineAt(sb);
	int xs = -header.GetScroll();
	int js;
	for(js = 0; js < column.GetCount(); js++) {
		int cw = header.GetTabWidth(js);
		if ( ( xs + cw - vertgrid + (js == column.GetCount() - 1)) >= 0)
			break;
		xs += cw;
	}
	Color fc = Blend(SColorDisabled, SColorPaper);
	if(!IsNull(i))
		while(i < GetCount()) {
			r.top = GetLineY(i) - sb;
			if(r.top > size.cy) break;
			r.bottom = r.top + GetLineCy(i);
			int x = xs;
			for(int j = js; j < column.GetCount(); j++) {
				int cw = header.GetTabWidth(j);
				int cm = column[j].margin;
				if(cm < 0)
					cm = header.Tab(j).GetMargin();
				if(x > size.cx) break;
				r.left = x;
				r.right = x + cw - vertgrid + (j == column.GetCount() - 1);
				Color bg = i & 1 ? evenpaper : oddpaper;
				Color fg = i & 1 ? evenink : oddink;
				bool ct = IsCtrl(i, j);
				dword st = 0;
				if(IsReadOnly())
					st |= Display::READONLY;
				if(i < array.GetCount() && array[i].select) {
					st |= Display::SELECT;
					fg = hasfocus ? SColorHighlightText : SColorText;
					bg = hasfocus ? SColorHighlight : fc;
				}
				if(i == cursor && !nocursor) {
					st |= Display::CURSOR;
					fg = hasfocus ? SColorHighlightText : SColorText;
					bg = hasfocus ? (GetSelectCount() > 1 ? Blend(SColorPaper, SColorHighlight)
					                                      : SColorHighlight) : fc;
				}
				if(hasfocus) st |= Display::FOCUS;
				const Display& d = ct ? StdDisplay() : GetDisplay(i, j);
				Value q = ct ? Null : GetConvertedColumn(i, j);
				if(w.IsPainting(r))
					if(cw < 2 * cm || editmode && i == cursor && column[j].edit)
						d.PaintBackground(w, r, q, fg, bg, st);
					else {
						d.PaintBackground(w, RectC(r.left, r.top, cm, r.Height()), q, fg, bg, st);
						r.left += cm;
						r.right -= cm;
						d.PaintBackground(w, RectC(r.right, r.top, cm, r.Height()), q, fg, bg, st);
						w.Clip(r);
						if(ct)
							GetCtrl(i, j).Color(bg);
						else
							GetDisplay(i, j).Paint(w, r, q, fg, bg, st);
						w.End();
					}
				x += cw;
				if(vertgrid)
					w.DrawRect(x - 1, r.top, 1, r.Height(), gridcolor);
			}
			if(horzgrid)
				w.DrawRect(0, r.bottom, size.cx, 1, gridcolor);
			r.left = x;
			r.right = size.cx;
			r.bottom += horzgrid;
			w.DrawRect(r, SColorPaper);
			i++;
		}
	r.left = 0;
	r.right = size.cx;
	r.top = r.bottom;
	if(IsAppendLine() && !IsCursor()) {
		r.bottom = r.top + linecy;
		w.DrawRect(r, HasFocus() ? SColorHighlight : SColorFace);
		r.top = r.bottom;
	}
	r.bottom = size.cy;
	w.DrawRect(r, SColorPaper);
	scroller.Set(Point(header.GetScroll(), sb));
}

void ArrayCtrl::Scroll() {
	SyncCtrls();
	PlaceEdits();
	scroller.Scroll(*this, GetSize(), Point(header.GetScroll(), sb)); //TODO
}

void ArrayCtrl::HeaderLayout() {
	Refresh();
	SyncCtrls();
	PlaceEdits();
}

void ArrayCtrl::HeaderScrollVisibility()
{
	scrollbox.Height(ScrollBarSize());
	if(header.IsScroll())
		sb.SetFrame(scrollbox);
	else
		sb.SetFrame(NullFrame());
}

void ArrayCtrl::RefreshRow(int i) {
	if(i >= 0 && i < GetCount())
		Refresh(0, GetLineY(i) - sb, GetSize().cx, GetLineCy(i) + horzgrid);
	if(IsAppendLine())
		Refresh(0, GetLineY(GetCount()) - sb, GetSize().cx, linecy + horzgrid);
}

ArrayCtrl::IdInfo& ArrayCtrl::IndexInfo(int i) {
	return idx[i];
}

ArrayCtrl::IdInfo& ArrayCtrl::IndexInfo(Id id) {
	return idx.Get(id);
}

ArrayCtrl::IdInfo& ArrayCtrl::AddIndex(Id id) {
	return idx.Add(id);
}

ArrayCtrl::IdInfo& ArrayCtrl::AddIndex() {
	return idx.Add(Id());
}

ArrayCtrl::IdInfo& ArrayCtrl::SetId(int i, Id id) {
	while(idx.GetCount() < i + 1)
		idx.Add(Id());
	idx.SetKey(i, id);
	return idx[i];
}

ArrayCtrl::Column& ArrayCtrl::AddColumn(const char *text, int w) {
	AddIndex();
	return AddColumnAt(idx.GetCount() - 1, text, w);
}

ArrayCtrl::Column& ArrayCtrl::AddColumn(Id id, const char *text, int w) {
	AddIndex(id);
	return AddColumnAt(idx.GetCount() - 1, text, w);
}

ArrayCtrl::Column& ArrayCtrl::AddColumnAt(int pos, const char *text, int w) {
	header.Add(text, w);
	Column& m = column.Add();
	m.arrayctrl = this;
	m.Add(pos);
	return m;
}

ArrayCtrl::Column& ArrayCtrl::AddColumnAt(Id id, const char *text, int w) {
	header.Add(text, w);
	Column& m = column.Add();
	m.arrayctrl = this;
	m.Add(id);
	return m;
}

ArrayCtrl::Column& ArrayCtrl::AddRowNumColumn(const char *text, int w) {
	header.Add(text, w);
	Column& m = column.Add();
	m.arrayctrl = this;
	return m;
}

int ArrayCtrl::FindColumnWithPos(int pos) const
{
	for(int i = 0; i < column.GetCount(); i++) {
		const Mitor<int>& m = column[i].pos;
		for(int j = 0; j < m.GetCount(); j++)
			if(Pos(m[j]) == pos) return i;
	}
	return -1;
}

int ArrayCtrl::FindColumnWithId(Id id) const
{
	return FindColumnWithPos(GetPos(id));
}

ArrayCtrl::IdInfo& ArrayCtrl::AddCtrl(Ctrl& ctrl) {
	IdInfo& f = AddIndex();
	AddCtrlAt(idx.GetCount() - 1, ctrl);
	return f;
}

ArrayCtrl::IdInfo& ArrayCtrl::AddCtrl(Id id, Ctrl& ctrl) {
	IdInfo& f = AddIndex(id);
	AddCtrlAt(idx.GetCount() - 1, ctrl);
	return f;
}

void ArrayCtrl::AddCtrlAt(int ii, Ctrl& ctrl) {
	Control& c = control.Add();
	c.pos = ii;
	c.ctrl = &ctrl;
	ctrl.Disable();
	ctrl <<= Null;
}

void ArrayCtrl::AddCtrlAt(Id id, Ctrl& ctrl) {
	AddCtrlAt(-id.AsNdx(), ctrl);
}

void ArrayCtrl::AddRowNumCtrl(Ctrl& ctrl) {
	AddCtrlAt(Null, ctrl);
}

Rect ArrayCtrl::GetCellRect(int i, int col)
{
	Rect r;
	r.top = GetLineY(i) - sb;
	r.bottom = r.top + GetLineCy(i);
	int x = 0;
	for(i = 0; i < col; i++)
		x += header.GetTabWidth(i);
	r.left = x - header.GetScroll();
	r.right = r.left + header.GetTabWidth(col);
	return r;
}

Rect ArrayCtrl::GetCellRectM(int i, int col)
{
	Rect r = GetCellRect(i, col);
	int cm = column[col].margin;
	if(cm < 0)
		cm = header.Tab(col).GetMargin();
	r.left += cm;
	r.right -= cm;
	return r;
}

void ArrayCtrl::Remove0(int i) {
	array.Remove(i);
	for(int j = 0; j < column.GetCount(); j++)
		column[j].RemoveCache(i);
	if(i < ln.GetCount()) {
		int y = ln[i].y;
		ln.Remove(i);
		Reline(i, y);
	}
	if(i < cellinfo.GetCount())
		cellinfo.Remove(i);
	if(virtualcount > 0) virtualcount--;
	Refresh();
	PlaceEdits();
	SyncCtrls();
	SetSb();
	selectiondirty = true;
}

void ArrayCtrl::DisableCtrls() {
	for(int i = 0; i < control.GetCount(); i++) {
		Ctrl& c = *control[i].ctrl;
		c <<= Null;
		c.Disable();
	}
}

void ArrayCtrl::RejectRow() {
	bool rm_cursor = false;
	if(IsCursor()) {
		int i;
		for(i = 0; i < column.GetCount(); i++) {
			Column& m = column[i];
			if(m.edit) m.edit->Reject();
		}
		for(i = 0; i < control.GetCount(); i++)
			control[i].ctrl->Reject();
		if(IsInsert()) {
			Remove0(cursor);
			DisableCtrls();
			cursor = -1;
			rm_cursor = true;
		}
		else
			RefreshRow(cursor);
	}
	EndEdit();
	WhenArrayAction();
	if(rm_cursor)
		WhenCursor();
}

void ArrayCtrl::Reject() {
	RejectRow();
}

void ArrayCtrl::CancelCursor() {
	RejectRow();
	DisableCtrls();
	cursor = anchor = -1;
	WhenCursor();
}

bool ArrayCtrl::UpdateRow() {
	ASSERT(IsCursor());
	bool iv = false;
	int i;
	for(i = 0; i < column.GetCount(); i++) {
		Column& m = column[i];
		if(m.edit && m.edit->IsModified()) {
			Value v = m.edit->GetData();
			if(m.pos.GetCount() == 1) {
				Value& vv = array.At(cursor).line.At(Pos(m.pos[0]));
				if(vv != v) {
					iv = true;
					vv = v;
				}
			}
			else
			if(m.pos.GetCount() > 1) {
				ValueArray va = v;
				for(int j = 0; j < m.pos.GetCount(); j++) {
					Value& vv = array.At(cursor).line.At(Pos(m.pos[j]));
					if(vv != va[j]) {
						iv = true;
						vv = va[j];
					}
				}
			}
		}
	}
	for(i = 0; i < control.GetCount(); i++) {
		Control& c = control[i];
		if(!IsNull(c.pos) && c.ctrl->IsModified()) {
			Value v = c.ctrl->GetData();
			Value& vv = array.At(cursor).line.At(Pos(c.pos));
			if(vv != v) {
				iv = true;
				vv = v;
			}
		}
	}
	if(iv) {
		InvalidateCache(cursor);
		WhenArrayAction();
	}
	WhenUpdateRow();
	return true;
}

void ArrayCtrl::ClearModify() {
	int i;
	modify.Set(0, false, idx.GetCount());
	for(i = 0; i < column.GetCount(); i++)
		if(column[i].edit)
			column[i].edit->ClearModify();
	for(i = 0; i < control.GetCount(); i++)
		control[i].ctrl->ClearModify();
}

bool ArrayCtrl::AcceptRow() {
	ASSERT(IsCursor());
	int i;
	for(i = 0; i < column.GetCount(); i++) {
		Column& m = column[i];
		if(m.edit && !m.edit->Accept())
			return false;
	}
	for(i = 0; i < control.GetCount(); i++)
		if(!control[i].ctrl->Accept())
			return false;
	if(!WhenAcceptRow()) return false;
	if(!UpdateRow()) return false;
	bool b = editmode;
	EndEdit();
	SetCtrls();
	ClearModify();
	if(b)
		WhenAcceptEdit();
	return true;
}

bool ArrayCtrl::Accept() {
	return IsCursor() ? AcceptRow() : true;
}

bool ArrayCtrl::KillCursor0() {
	if(IsCursor()) {
		if(!AcceptRow()) return false;
		int c = cursor;
		DisableCtrls();
		WhenKillCursor();
		cursor = -1;
		RefreshRow(c);
	}
	return true;
}

bool ArrayCtrl::KillCursor() {
	bool b = KillCursor0();
	if(b) WhenCursor();
	return b;
}

void ArrayCtrl::SetCtrls() {
	int i;
	for(i = 0; i < column.GetCount(); i++)
		ColEditSetData(i);
	for(i = 0; i < control.GetCount(); i++)
		CtrlSetData(i);
}

void ArrayCtrl::ScrollInto(int line)
{
	if(line < 0)
		sb.Begin();
	else
	if(line >= GetCount())
		sb.End();
	else
		sb.ScrollInto(GetLineY(line), GetLineCy(line));
}

void ArrayCtrl::ScrollIntoCursor()
{
	if(IsCursor())
		ScrollInto(cursor);
}

bool ArrayCtrl::SetCursor0(int i, bool dosel) {
	if(nocursor || GetCount() == 0)
		return false;
	i = minmax(i, 0, GetCount() - 1);
	if(i != cursor) {
		RefreshRow(cursor);
		if(cursor >= 0) {
			if(!KillCursor0()) return false;
		}
		cursor = i;
		if(dosel && multiselect) {
			ClearSelection();
			anchor = cursor;
			Select(cursor);
		}
		ScrollIntoCursor();
		RefreshRow(cursor);
		SetCtrls();
		for(int j = 0; j < column.GetCount(); j++)
			if(IsCtrl(cursor, j) && GetCtrl(cursor, j).ctrl->HasFocus())
				goto nosetfocus;
		if(!IsEdit() && cursor >= 0 && hasctrls)
			for(int j = 0; j < column.GetCount(); j++)
				if(IsCtrl(cursor, j) && GetCtrl(cursor, j).ctrl->SetWantFocus())
					break;
	nosetfocus:
		ClearModify();
		Action();
		WhenEnterRow();
		WhenCursor();
	}
	return true;
}

bool ArrayCtrl::SetCursor(int i)
{
	return SetCursor0(i);
}


void ArrayCtrl::ShowAppendLine() {
	sb.ScrollInto(GetTotalCy(), GetLineCy());
}

void ArrayCtrl::GoBegin() {
	if(nocursor)
		sb.Begin();
	else
		SetCursor(0);
}

void ArrayCtrl::GoEnd() {
	if(nocursor)
		sb.End();
	else
		SetCursor(GetCount() - 1);
}

int  ArrayCtrl::GetCursorSc() const {
	return IsCursor() ? GetLineY(cursor) - sb : 0;
}

void ArrayCtrl::ScCursor(int a) {
	if(IsCursor())
		sb = GetLineY(cursor) - max(a, 0);
}

void ArrayCtrl::SyncSelection() const
{
	if(!selectiondirty)
		return;
	selectcount = 0;
	for(int i = 0; i < array.GetCount(); i++)
		if(array[i].select)
			selectcount++;
	selectiondirty = false;
}

int ArrayCtrl::GetSelectCount() const
{
	SyncSelection();
	return selectcount;
}

void ArrayCtrl::Select(int i, bool sel)
{
	array[i].select = sel;
	selectiondirty = true;
	RefreshRow(i);
	WhenSelection();
}

void ArrayCtrl::Select(int i, int count, bool sel)
{
	while(count--) {
		array[i].select = sel;
		RefreshRow(i++);
	}
	selectiondirty = true;
	WhenSelection();
}

void ArrayCtrl::ClearSelection()
{
	if(IsSelection()) {
		for(int i = 0; i < array.GetCount(); i++)
			if(array[i].select) {
				RefreshRow(i);
				array[i].select = false;
			}
		selectiondirty = false;
		selectcount = 0;
		WhenSelection();
	}
}

int  ArrayCtrl::GetScroll() const
{
	return sb;
}

void ArrayCtrl::ScrollTo(int sc)
{
	sb = sc;
}

void ArrayCtrl::CenterCursor() {
	if(IsCursor())
		ScCursor((GetSize().cy - GetLineCy(cursor)) / 2);
}

void ArrayCtrl::Page(int q) {
	q = q * max(GetSize().cy - (linecy + horzgrid), linecy + horzgrid);
	int a = GetCursorSc();
	if(IsCursor()) {
		SetCursor(cursor + q / (linecy + horzgrid));
		ScCursor(a);
	}
	else
	if(q > 0)
		sb.NextPage();
	else
		sb.PrevPage();
}

void ArrayCtrl::DoPoint(Point p, bool dosel) {
	p.y += sb;
	if(p.y >= GetTotalCy() && IsAppendLine())
		KillCursor();
	clickpos.y = GetLineAt(p.y);
	if(!IsNull(clickpos.y))
		SetCursor0(clickpos.y, dosel);
	else
	if(IsCursor())
		AcceptRow();
	if(!HasFocusDeep())
		SetWantFocus();
}

void ArrayCtrl::ClickColumn(Point p)
{
	clickpos.x = Null;
	if(clickpos.y >= 0)
		for(int i = 0; i < column.GetCount(); i++)
			if(GetCellRect(clickpos.y, i).Contains(p)) {
				clickpos.x = i;
				break;
			}
}

void ArrayCtrl::LeftDown(Point p, dword flags)
{
	if(IsReadOnly()) return;
	int q = header.GetSplit(p.x);
	if(q >= 0) {
		header.StartSplitDrag(q);
		return;
	}
	int c = cursor;
	bool b = HasFocus();
	DoPoint(p, false);
	ClickColumn(p);
	if(!IsNull(clickpos.x) && c == cursor && cursor >= 0 && b && column[clickpos.x].clickedit)
		StartEdit(clickpos.x);
	else {
		if(cursor >= 0 && multiselect) {
			if(flags & K_CTRL) {
				Select(cursor, !IsSelected(cursor));
				anchor = cursor;
			}
			else {
				ClearSelection();
				if((flags & K_SHIFT) && anchor >= 0)
					Select(min(anchor, cursor), abs(anchor - cursor) + 1);
				else {
					anchor = cursor;
					Select(cursor);
				}
			}
			Action();
		}
	}
	WhenLeftClick();
}

void ArrayCtrl::LeftDouble(Point p, dword) {
	if(IsReadOnly()) return;
	DoPoint(p);
	ClickColumn(p);
	if((IsInserting() || IsAppending()) && IsAppendLine() && !IsCursor())
		DoAppend();
	WhenLeftDouble();
}

void ArrayCtrl::MouseMove(Point p, dword)
{
	if(IsReadOnly()) return;
	if(mousemove) {
		int i = GetLineAt(p.y + sb);
		if(!IsNull(i)) SetCursor(i);
	}
}

Image ArrayCtrl::CursorImage(Point p, dword)
{
	return header.GetSplit(p.x) < 0 ? Image::Arrow() : CtrlsImg::HorzPos();
}

void ArrayCtrl::RightDown(Point p, dword flags) {
	if((flags & (K_CTRL|K_SHIFT)) == 0) {
		int c = cursor;
		bool b = HasFocus();
		DoPoint(p, false);
		ClickColumn(p);
		if(cursor >= 0 && multiselect) {
			if(!IsSelected(cursor)) {
				ClearSelection();
				Select(anchor = cursor);
			}
			Action();
		}
	}
	MenuBar::Execute(WhenBar);
}

bool ArrayCtrl::TestKey(int i, int key) {
	for(int j = 0; j < column.GetCount(); j++) {
		int (*af)(int) = column[j].accel;
		if(af) {
			int c = (*af)(key);
			if(c && (*af)(StdFormat(GetColumn(i, j))[0]) == c) {
				SetCursor(i);
				return true;
			}
		}
	}
	for(int ii = 0; ii < idx.GetCount(); ii++) {
		int (*af)(int) = idx[ii].accel;
		if(af) {
			int c = (*af)(key);
			if(c && (*af)(StdFormat(Get(i, ii))[0]) == c) {
				SetCursor(i);
				return true;
			}
		}
	}
	return false;
}

int ArrayCtrl::GetEditColumn() const {
	if(!IsEdit()) return -1;
	for(int i = 0; i < column.GetCount(); i++) {
		const Column& m = column[i];
		if(m.edit && m.edit->HasFocusDeep())
			return i;
	}
	return -1;
}

void ArrayCtrl::KeyMultiSelect(dword key)
{
	if(!multiselect)
		return;
	ClearSelection();
	if(key & K_SHIFT) {
		if(anchor >= 0)
			Select(min(anchor, cursor), abs(anchor - cursor) + 1);
	}
	else if(cursor >= 0) {
		anchor = cursor;
		Select(anchor);
	}
}

bool ArrayCtrl::Key(dword key, int) {
	if(IsReadOnly()) return false;
	if(!editmode) {
		if(key > 32 && key < 256) {
			int cr = cursor >= 0 ? cursor + 1 : 0;
			for(int j = 0; j < column.GetCount(); j++)
				if(column[j].accel) {
					int i;
					for(i = cr; i < array.GetCount(); i++)
						if(TestKey(i, key)) return true;
					for(i = 0; i < cr; i++)
						if(TestKey(i, key)) return true;
					return true;
				}
		}
		switch(key) {
		case K_PAGEUP:
		case K_SHIFT_PAGEUP:
			Page(-1);
			KeyMultiSelect(key);
			return true;
		case K_PAGEDOWN:
		case K_SHIFT_PAGEDOWN:
			if((IsInserting() || IsAppending()) && IsAppendLine() && cursor == GetCount() - 1)
				KillCursor();
			else {
				Page(1);
				KeyMultiSelect(key);
			}
			return true;
		case K_HOME:
		case K_CTRL_HOME:
		case K_CTRL_PAGEUP:
		case K_SHIFT_HOME:
		case K_SHIFT|K_CTRL_HOME:
		case K_SHIFT|K_CTRL_PAGEUP:
			GoBegin();
			KeyMultiSelect(key);
			return true;
		case K_END:
		case K_CTRL_END:
		case K_CTRL_PAGEDOWN:
		case K_SHIFT|K_END:
		case K_SHIFT|K_CTRL_END:
		case K_SHIFT|K_CTRL_PAGEDOWN:
			GoEnd();
			KeyMultiSelect(key);
			return true;
		case K_CTRL_A:
			if(multiselect) {
				GoEnd();
				anchor = 0;
				KeyMultiSelect(K_SHIFT);
			}
			return true;
		}
	}
	switch(key) {
	case K_UP:
	case K_SHIFT_UP:
		if(IsCursor()) {
			int d = GetEditColumn();
			if(SetCursor0(cursor - 1))
				if(d >= 0)
					StartEdit(d);
				else
					KeyMultiSelect(key);
		}
		else
		if((IsInserting() || IsAppending()) && IsAppendLine())
			SetCursor(GetCount() - 1);
		else
			sb.PrevLine();
		return true;
	case K_DOWN:
	case K_SHIFT_DOWN:
		if((IsInserting() || IsAppending()) && IsAppendLine() && cursor == GetCount() - 1 && !editmode)
			KillCursor();
		else
		if(IsCursor()) {
			int d = GetEditColumn();
			if(SetCursor0(cursor + 1) && d >= 0)
				StartEdit(d);
			else
				KeyMultiSelect(key);
		}
		else
			sb.NextLine();
		return true;
	case K_ENTER:
		if(!IsCursor() && (IsInserting() || IsAppending()) && IsAppendLine()) {
			DoAppend();
			return true;
		}
		if(editmode) {
			bool ins = IsInsert() && autoappend;
			if(AcceptEnter() && ins)
				DoAppend();
			return true;
		}
		if(WhenEnterKey && IsCursor()) {
			WhenEnterKey();
			return true;
		}
		break;
	case K_ESCAPE:
		if(IsEdit()) {
			int c = cursor;
			CancelCursor();
			SetCursor(c);
			return true;
		}
		break;
	}
	return MenuBar::Scan(WhenBar, key);
}

bool ArrayCtrl::AcceptEnter() {
	if(editmode) {
		bool ins = IsInsert();
		if(!Accept())
			return false;
		if(GetCursor() == array.GetCount() - 1 &&
		   (IsInserting() || IsAppending()) && IsAppendLine() && ins && !noinsertappend) {
		   	KillCursor();
		   	ShowAppendLine();
		}
	}
	return true;
}

void  ArrayCtrl::Set(int i, const Vector<Value>& v) {
	for(int ii = 0; ii < v.GetCount(); ii++)
		Set(i, ii, v[ii]);
	InvalidateCache(i);
	SetSb();
	RefreshRow(i);
}

void  ArrayCtrl::Add() {
	if(GetIndexCount()) {
		Vector<Value> x;
		x.SetCount(GetIndexCount());
		Set(array.GetCount(), x);
	}
	else {
		int i = array.GetCount();
		array.At(i);
		SetSb();
		Refresh();
		InvalidateCache(cursor);
		InvalidateCache(i);
		RefreshRow(i);
	}

}

void  ArrayCtrl::Add(const Vector<Value>& v) {
	Set(array.GetCount(), v);
}

#define E__Addv(I)    Set0(q, I - 1, p##I)
#define E__AddF(I) \
void ArrayCtrl::Add(__List##I(E__Value)) { \
	int q = array.GetCount(); \
	__List##I(E__Addv); \
	AfterSet(q); \
}
__Expand(E__AddF)

void  ArrayCtrl::Insert(int i) {
	if(i < array.GetCount()) {
		array.Insert(i);
		for(int j = 0; j < column.GetCount(); j++)
			column[j].InsertCache(i);
	}
	else
		array.At(i);
	if(i <= cursor) cursor++;
	if(i < cellinfo.GetCount())
		cellinfo.Insert(i);
	if(i < ln.GetCount()) {
		int y = ln[i].y;
		ln.Insert(i);
		Reline(i, y);
	}
	for(int ii = 0; ii < idx.GetCount(); ii++) {
		Value v = idx[ii].GetInsertValue();
		if(!IsNull(v))
			Set(i, ii, v);
	}
	if(virtualcount >= 0) virtualcount++;
	Refresh();
	SetSb();
	PlaceEdits();
	SyncCtrls();
}

void  ArrayCtrl::Insert(int i, const Vector<Value>& v) {
	Insert(i);
	Set(i, v);
}

void  ArrayCtrl::Remove(int i) {
	int c = cursor;
	if(i == cursor) CancelCursor();
	Remove0(i);
	if(c >= 0)
		SetCursor(c - (i < c));
	anchor = -1;
	PlaceEdits();
	SyncCtrls();
	SetSb();
	Refresh();
}

void ArrayCtrl::PlaceEdits() {
	for(int i = 0; i < column.GetCount(); i++) {
		Column& m = column[i];
		if(m.edit) {
			m.edit->Show(editmode);
			if(editmode)
				m.edit->SetRect(GetCellRectM(cursor, i));
		}
	}
}

bool ArrayCtrl::IsEditing() const {
	for(int i = 0; i < column.GetCount(); i++)
		if(column[i].edit) return true;
	return false;
}

bool ArrayCtrl::StartEdit(int d) {
	if(IsReadOnly()) return false;
	if(!IsEditing()) return false;
	editmode = true;
	PlaceEdits();
	for(int i = 0; i < column.GetCount(); i++) {
		Column& m = column[(i + d) % column.GetCount()];
		if(m.edit && (m.edit->SetWantFocus() || IterateFocusForward(m.edit, m.edit)))
			break;
	}
	NoWantFocus();
	RefreshRow(cursor);
	WhenStartEdit();
	return true;
}

void ArrayCtrl::EndEdit() {
	if(!IsEditing())
		return;
	bool f = HasFocusDeep();
	editmode = false;
	insertmode = false;
	PlaceEdits();
	WantFocus();
	if(f) SetWantFocus();
}

void ArrayCtrl::LostFocus() {
	if(IsSelection())
		Refresh();
	else
	if(IsCursor())
		RefreshRow(cursor);
}

void ArrayCtrl::GotFocus() {
	if(IsSelection())
		Refresh();
	else
	if(IsCursor())
		RefreshRow(cursor);
	else
		GoBegin();
}

void ArrayCtrl::DoEdit() {
	if(IsReadOnly()) return;
	if(!editmode)
		StartEdit();
}

void ArrayCtrl::DoInsert(int c) {
	if(IsReadOnly()) return;
	Insert(c);
	SetCursor(c);
	insertmode = true;
	DoEdit();
	if(!IsEdit())
		insertmode = false;
	WhenArrayAction();
}

void ArrayCtrl::DoInsertBefore() {
	DoInsert(IsCursor() ? GetCursor() : array.GetCount());
}

void ArrayCtrl::DoInsertAfter() {
	DoInsert(IsCursor() ? GetCursor() + 1 : array.GetCount());
}

void ArrayCtrl::DoAppend() {
	DoInsert(array.GetCount());
}

void ArrayCtrl::DoSelectAll()
{
	Select(0, GetCount());
}

String ArrayCtrl::RowFormat(const char *s)
{
	return Sprintf(s, ~row_name);
}

bool ArrayCtrl::DoRemove()
{
	if(IsReadOnly()) return false;
	if(!IsCursor() || askremove && !PromptOKCancel(RowFormat(t_("Do you really want to delete the selected %s ?"))))
		return false;
	Remove(cursor);
	WhenArrayAction();
	return true;
}

void ArrayCtrl::DoRemovem()
{
	DoRemove();
}

void ArrayCtrl::DoDuplicate() {
	if(IsReadOnly()) return;
	if(!IsCursor()) return;
	int c = cursor;
	if(!KillCursor()) return;
	Vector<Value> va = ReadRow(c);
	c = IsAppending() ? array.GetCount() : c + 1;
	Insert(c, va);
	SetCursor(c);
	DoEdit();
	WhenArrayAction();
}

void ArrayCtrl::StdBar(Bar& menu)
{
	bool e = IsEditable();
	bool c = !IsEdit() && e;
	bool d = c && IsCursor();
	if(inserting)
		menu.Add(e, RowFormat(t_("Insert %s")), THISBACK(DoInsertBefore))
			.Help(RowFormat(t_("Insert a new %s into the table.")))
			.Key(K_INSERT);
	if(bains == 1) {
		menu.Add(e, RowFormat(t_("Insert %s before")), THISBACK(DoInsertBefore))
		    .Help(RowFormat(t_("Insert a new %s into the table before the actual one")))
		    .Key(K_INSERT);
		menu.Add(e, RowFormat(t_("Insert %s after")), THISBACK(DoInsertAfter))
		    .Help(RowFormat(t_("Insert a new %s into the table after the actual one")))
		    .Key(K_SHIFT_INSERT);
	}
	if(bains == 2) {
		menu.Add(e, RowFormat(t_("Insert %s after")), THISBACK(DoInsertAfter))
		    .Help(RowFormat(t_("Insert a new %s into the table after the actual one")))
		    .Key(K_INSERT);
		menu.Add(e, RowFormat(t_("Insert %s before")), THISBACK(DoInsertBefore))
		    .Help(RowFormat(t_("Insert a new %s into the table before the actual one")))
		    .Key(K_SHIFT_INSERT);
	}
	if(IsAppending())
		menu.Add(c, RowFormat(t_("Append %s")), THISBACK(DoAppend))
			.Help(RowFormat(t_("Append a new %s at the end of the table.")))
			.Key(inserting ? (int)K_SHIFT_INSERT : (int)K_INSERT);
	if(duplicating)
		menu.Add(d, RowFormat(t_("Duplicate %s")), THISBACK(DoDuplicate))
			.Help(RowFormat(t_("Duplicate current table %s.")))
			.Key(K_CTRL_INSERT);
	if(IsEditing())
		menu.Add(d, RowFormat(t_("Edit %s")), THISBACK(DoEdit))
			.Help(RowFormat(t_("Edit active %s.")))
			.Key(K_CTRL_ENTER);
	if(removing)
		menu.Add(d, RowFormat(t_("Delete %s\tDelete")), THISBACK(DoRemovem))
			.Help(RowFormat(t_("Delete active %s.")))
			.Key(K_DELETE);
	if(moving) {
		menu.Add(GetCursor() > 0, RowFormat(t_("Move %s up")), THISBACK(SwapUp))
			.Help(RowFormat(t_("Swap %s with previous thus moving it up.")))
			.Key(K_CTRL_UP);
		menu.Add(GetCursor() >= 0 && GetCursor() < GetCount() - 1,
		         RowFormat(t_("Move %s down")), THISBACK(SwapDown))
			.Help(RowFormat(t_("Swap %s with next thus moving it down.")))
			.Key(K_CTRL_DOWN);
	}
	if(multiselect) {
		menu.Add(GetCount() > 0, RowFormat(t_("Select all")), THISBACK(DoSelectAll))
			.Help(t_("Select all table rows"))
			.Key(K_CTRL_A);
	}
}

int ArrayCtrl::Find(const Value& v, int ii, int i) const {
	ASSERT(ii >= 0);
	int n = GetCount();
	while(i < n) {
		if(Get(i, ii) == v) return i;
		i++;
	}
	return -1;
}

int  ArrayCtrl::Find(const Value& v, Id id, int i) const {
	return Find(v, GetPos(id), i);
}

bool ArrayCtrl::FindSetCursor(const Value& val, int ii, int i) {
	i = Find(val, ii, i);
	if(i < 0) return false;
	if(!SetCursor(i)) return false;
	CenterCursor();
	return true;
}

bool ArrayCtrl::FindSetCursor(const Value& val, Id id, int i) {
	return FindSetCursor(val, idx.Find(id), i);
}

void ArrayCtrl::ClearCache() {
	for(int i = 0; i < column.GetCount(); i++)
		column[i].ClearCache();
}

struct ArrayCtrl::SortPredicate {
	const ArrayCtrl::Order *order;
	bool operator()(const Line& a, const Line& b) const {
		return order->operator()(a.line, b.line);
	}
};

void ArrayCtrl::Sort(const ArrayCtrl::Order& order) {
	CHECK(KillCursor());
	ClearCache();
	SortPredicate sp;
	sp.order = &order;
	if(ln.GetCount()) {
		ln.SetCount(array.GetCount());
		::StableIndexSort(array, ln, sp);
		Reline(0, 0);
	}
	else
		StableSort(array, sp);
	Refresh();
}

void ArrayCtrl::Sort(int from, int count, const ArrayCtrl::Order& order) {
	CHECK(KillCursor());
	ClearCache();
	SortPredicate sp;
	sp.order = &order;
	StableSort(array.GetIter(from), array.GetIter(from + count), sp);
}

struct ArrayCtrl::RowOrder : public ArrayCtrl::Order {
	int (*compare)(const Vector<Value>& v1, const Vector<Value>& v2);

	virtual bool operator()(const Vector<Value>& row1, const Vector<Value>& row2) const {
		return (*compare)(row1, row2) < 0;
	}
};

void ArrayCtrl::Sort(int (*compare)(const Vector<Value>& v1, const Vector<Value>& v2)) {
	RowOrder io;
	io.compare = compare;
	Sort(io);
}

struct ArrayCtrl::ItemOrder : public ArrayCtrl::Order {
	int ii;
	int (*compare)(const Value& v1, const Value& v2);

	virtual bool operator()(const Vector<Value>& row1, const Vector<Value>& row2) const {
		return (*compare)(row1[ii], row2[ii]) < 0;
	}
};

void ArrayCtrl::Sort(int ii, int (*compare)(const Value& v1, const Value& v2)) {
	ItemOrder io;
	io.ii = ii;
	io.compare = compare;
	Sort(io);
}

void ArrayCtrl::Sort(Id id, int (*compare)(const Value& v1, const Value& v2)) {
	Sort(idx.Find(id), compare);
}

void ArrayCtrl::Clear() {
	EndEdit();
	if(cursor >= 0) {
		WhenKillCursor();
		cursor = -1;
		WhenCursor();
	}
	array.Clear();
	cellinfo.Clear();
	ln.Clear();
	ClearCache();
	DisableCtrls();
	virtualcount = -1;
	anchor = -1;
	SetSb();
	Refresh();
}

void ArrayCtrl::Shrink() {
	array.Shrink();
	cellinfo.Shrink();
	ln.Shrink();
}

void ArrayCtrl::Reset() {
	Clear();
	linecy = Draw::GetStdFontCy();
	sb.SetLine(linecy);
	header.Reset();
	idx.Clear();
	column.Clear();
	control.Clear();
	nocursor = false;
	vertgrid = horzgrid = true;
	mousemove = false;
	inserting = false;
	appending = false;
	removing = false;
	askremove = true;
	duplicating = false;
	moving = false;
	appendline = false;
	noinsertappend = false;
	editmode = false;
	insertmode = false;
	multiselect = false;
	selectiondirty = false;
	hasctrls = false;
	headerctrls = false;
	selectcount = 0;
	bains = 0;
	row_name = t_("row");
	gridcolor = SColorShadow;
	autoappend = false;
}

void ArrayCtrl::MouseWheel(Point p, int zdelta, dword keyflags) {
	sb.Wheel(zdelta);
}

Vector<Value> ArrayCtrl::ReadRow(int i) const {
	Vector<Value> v;
	for(int j = 0; j < idx.GetCount(); j++)
		v.Add(Get(i, j));
	return v;
}

void ArrayCtrl::Move(int dir) {
	int c = GetCursor();
	int d = c + dir;
	if(c < 0 || c >= GetCount() || d < 0 || d >= GetCount()) return;
	Vector<Value> row(ReadRow(c), 0);
	Set(c, ReadRow(d));
	Set(d, row);
	SetCursor(d);
	WhenArrayAction();
}

void ArrayCtrl::SwapUp() {
	Move(-1);
}

void ArrayCtrl::SwapDown() {
	Move(1);
}

ArrayCtrl& ArrayCtrl::ColumnWidths(const char *s)
{
	Vector<String> w = Split(s, ' ');
	for(int i = 0; i < min(w.GetCount(), header.GetCount()); i++)
		header.SetTabRatio(i, atoi(w[i]));
	return *this;
}

ArrayCtrl& ArrayCtrl::OddRowColor(Color paper, Color ink)
{
	oddpaper = paper;
	oddink = ink;
	Refresh();
	return *this;
}

ArrayCtrl& ArrayCtrl::EvenRowColor(Color paper, Color ink)
{
	evenpaper = paper;
	evenink = ink;
	Refresh();
	return *this;
}

ArrayCtrl::ArrayCtrl() {
	cursor = -1;
	Reset();
	AddFrame(sb);
	AddFrame(header);
	header.WhenLayout = THISBACK(HeaderLayout);
	header.WhenScroll = sb.WhenScroll = THISBACK(Scroll);
	WhenAcceptRow = true;
	WhenBar = THISBACK(StdBar);
	SetFrame(ViewFrame());
	oddpaper = evenpaper = SColorPaper;
	oddink = evenink = SColorText;
}

ArrayCtrl::~ArrayCtrl() {}

ArrayOption::ArrayOption()
{
	array = NULL;
	f = 0;
	t = 1;
	hswitch = vswitch = false;
	threestate = false;
	frame = true;
}

ArrayOption::~ArrayOption()
{
}

void ArrayOption::Click()
{
	if(!array)
		return;
	int c;
	for(c = index.GetCount(); --c >= 0;)
		if(array->FindColumnWithPos(index[c]) == array->GetClickColumn())
			break;
	int cr = array->GetCursor();
	if(c >= 0 && cr >= 0) {
		Value v = array->Get(index[c]);
		if(!IsNull(v) && v != t && v != f) {
			BeepExclamation();
			return;
		}
		if(hswitch)
			for(int i = 0; i < index.GetCount(); i++)
				if(i != c)
					array->Set(index[i], f);
		array->Set(index[c], threestate && v == t
			? Value() : v != t && !(threestate && IsNull(v)) ? t : f);
		if(vswitch) {
			for(int r = 0; r < array->GetCount(); r++)
				if(r != cr) {
					if(hswitch)
						for(int i = 0; i < index.GetCount(); i++)
							if(i != c)
								array->Set(r, index[i], f);
					array->Set(r, index[c], f);
				}
		}
		WhenAction();
		array->Action();
		array->WhenArrayAction();
	}
}

void ArrayOption::Disconnect()
{
	array = NULL;
	index.Clear();
}

void ArrayOption::Connect(ArrayCtrl& a, int i)
{
	array = &a;
	if(index.IsEmpty()) {
		a.WhenLeftClick << THISBACK(Click);
		a.WhenLeftDouble << THISBACK(Click);
	}
	index.Add(i);
}

ArrayCtrl::Column& ArrayOption::AddColumn(ArrayCtrl& ac, const char *text, int w)
{
	return AddColumn(ac, Id(), text, w).NoClickEdit();
}

ArrayCtrl::Column& ArrayOption::AddColumn(ArrayCtrl& ac, Id id, const char *text, int w)
{
	Connect(ac, ac.GetIndexCount());
	return ac.AddColumn(id, text, w).SetDisplay(*this).InsertValue(f).NoClickEdit();
}

void ArrayOption::Paint(Draw& w, const Rect& r, const Value& q,
		                Color ink, Color paper, dword style) const
{
	w.DrawRect(r, paper);
	Size crsz = min(CtrlImg::smallcheck().GetSize() + 4, r.Size());
	Rect cr = r.CenterRect(crsz);
	bool focusCursor = (style & (CURSOR | SELECT)) && (style & FOCUS);
	bool gray = false;
	if(!array || array->IsEnabled()) {
		gray = threestate && IsNull(q) || !threestate && !IsNull(q) && q != f && q != t;
		w.DrawRect(cr, gray ? SColorFace() : paper);
	}
	if(frame)
		DrawFrame(w, cr, focusCursor ? White : Blend(SColorLight, SColorHighlight));
	Image icon;
	if(q != f) {
		Image icon = CtrlImg::smallcheck();
		Point p = cr.CenterPos(icon.GetSize());
//		w.DrawRect(p.x, p.y, 8, 8, LtGreen());
		if(focusCursor && !gray)
			w.DrawImage(p.x, p.y, icon, White());
		else
			w.DrawImage(p.x, p.y, icon);
	}
}
