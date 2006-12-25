#include "CtrlLib.h"

NAMESPACE_UPP

HeaderCtrl::Column::Column()
{
	ratio = 1;
	visible = true;
	min = 0;
	max = INT_MAX;
	margin = 4;
	header = NULL;
	SetAlign(ALIGN_LEFT);
	paper = Null;
}

HeaderCtrl::Column&  HeaderCtrl::Column::SetMargin(int m)
{
	if(m != margin) {
		margin = m;
		LabelUpdate();
	}
	return *this;
}

HeaderCtrl::Column&  HeaderCtrl::Column::SetRatio(double wd)
{
	ratio = wd ? wd : 1;
	LabelUpdate();
	return *this;
}

void  HeaderCtrl::Column::LabelUpdate()
{
	if(header) {
		header->RefreshParentLayout();
		header->Refresh();
		header->WhenLayout();
		header->SbTotal();
	}
}

CH_LOOKS(HeaderTabLook, 4, CtrlsImgLook(CtrlsImg::I_HTB));
CH_INT(HeaderTabGridAdjustment, 0);
CH_INT(HeaderTabPressOffsetFlag, ButtonPressOffsetFlag());

void HeaderCtrl::Column::Paint(bool& first, Draw& w,
                               int x, int y, int cx, int cy, bool disabled, bool push, bool hl)
{
	if(first) {
		if(cx >= -HeaderTabGridAdjustment()) {
			cx -= HeaderTabGridAdjustment();
			if(cx < 0)
				cx = 0;
			first = false;
		}
	}
	else
		x -= HeaderTabGridAdjustment();
	bool p = push && HeaderTabPressOffsetFlag();
	Color bg = Nvl(paper, SColorFace());
	int q = CTRL_NORMAL;
	if(hl)
		q = CTRL_HOT;
	if(push)
		q = CTRL_PRESSED;
	if(disabled)
		q = CTRL_DISABLED;
	ChPaint(w, x, y, cx, cy, HeaderTabLook(q));
	x += margin;
	cx -= 2 * margin;
	w.Clip(x + 2, y, cx - 4, cy);
	PaintLabel(w, x + 2, y + 1, cx - 4, cy - 4, disabled, p);
	w.End();
}

HeaderCtrl::Column& HeaderCtrl::Tab(int i) {
	if(i >= col.GetCount())
		for(int j = col.GetCount(); j <= i; j++) {
			Column& c = col.Add();
			c.header = this;
		}
	return col[i];
}

void HeaderCtrl::SetHeight(int cy)
{
	height = cy;
	RefreshParentLayout();
}

int  HeaderCtrl::GetHeight() const
{
	int cy = 0;
	for(int i = 0; i < col.GetCount(); i++)
		cy = max(cy, col[i].GetLabelSize().cy);
	return max(height, cy + 4);
}

HeaderCtrl::Column& HeaderCtrl::Add()
{
	return Tab(col.GetCount());
}

HeaderCtrl::Column& HeaderCtrl::Add(const char *text, double ratio)
{
	HeaderCtrl::Column& c = Add();
	c.ratio = ratio ? ratio : 1;
	c.SetText(text);
	SbTotal();
	return c;
}

void HeaderCtrl::SetTabRatio(int i, double ratio)
{
	col[i].ratio = ratio;
	oszcx = -1;
	Refresh();
	WhenLayout();
}

double HeaderCtrl::Denominator() const {
	double rs = 0;
	for(int i = 0; i < col.GetCount(); i++)
		if(col[i].visible)
			rs += col[i].ratio;
	return rs;
}

void HeaderCtrl::SbTotal()
{
	if(mode == SCROLL) {
		int cx = 0;
		for(int i = 0; i < col.GetCount(); i++)
			cx += (int)col[i].ratio;
		sb.SetTotal(cx);
	}
	else
		sb.SetTotal(0);
}

HeaderCtrl& HeaderCtrl::Proportional() { mode = PROPORTIONAL; SbTotal(); return *this; }
HeaderCtrl& HeaderCtrl::ReduceNext()   { mode = REDUCENEXT; SbTotal(); return *this; }
HeaderCtrl& HeaderCtrl::ReduceLast()   { mode = REDUCELAST; SbTotal(); return *this; }
HeaderCtrl& HeaderCtrl::Absolute()     { mode = SCROLL; SbTotal(); return *this; }

int  HeaderCtrl::SumMin(int from)
{
	int mincx = 0;
	for(int i = from; i < col.GetCount(); i++)
		if(col[i].visible)
			mincx += col[i].min;
	return mincx;
}

int  HeaderCtrl::SumMax(int from)
{
	int maxcx = 0;
	for(int i = from; i < col.GetCount(); i++)
		if(col[i].visible) {
			if(col[i].max == INT_MAX)
				return INT_MAX;
			maxcx += col[i].max;
		}
	return maxcx;
}

void HeaderCtrl::ReCompute()
{
	int szcx = GetSize().cx;
	tabrect.Clear();
	Rect r;
	r.top = 0;
	r.bottom = GetSize().cy;
	r.right = 0;
	if(mode == SCROLL)
		for(int i = 0; i < col.GetCount(); i++) {
			r.left = r.right;
			if(col[i].visible) {
				r.right += (int)col[i].ratio;
			}
			tabrect.Add(r);
		}
	else {
		double rs = Denominator();
		double rr = 0;
		double eps = rs / 2.0e5;
		Vector<int> ci = GetVisibleCi(0);
		for(int i = 0; i < ci.GetCount() - 1; i++) {
			int cii = ci[i];
			r.left = r.right;
			while(tabrect.GetCount() < cii)
				tabrect.Add(r);
			rr += rs ? col[cii].ratio : 1;
			r.right = int(rr * szcx / (rs ? rs : ci.GetCount()) + eps);
			tabrect.Add(r);
		}
		r.left = r.right;
		if(!ci.IsEmpty()) {
			int cii = ci.Top();
			while(tabrect.GetCount() < cii)
				tabrect.Add(r);
			r.right = szcx;
			tabrect.Add(r);
		}
		r.left = r.right;
		tabrect.SetCount(col.GetCount(), r);
	}
}

void HeaderCtrl::Distribute(const Vector<int>& sci, double delta)
{
	double rest = 0;
	Vector<int> ci(sci, 1);
	int szcx = GetSize().cx;
	if(szcx == 0)
		return;
	double rs = Denominator();
	double eps = max(1.0e-6, rs / 1.0e6);
	double epsr = max(1.0e-4, rs / 1.0e4);
	bool checkmin = SumMin(0) < szcx;
	for(;;) {
		double psm = 0;
		for(int i = 0; i < ci.GetCount(); i++)
			psm += col[ci[i]].ratio;
		if(fabs(psm) < eps)
			return;
		double q = 1 + delta / psm;
		double x = 0;
		Vector<int> nci;
		for(int i = 0; i < ci.GetCount(); i++) {
			Column& c = col[ci[i]];
			c.ratio *= q;
			if(c.ratio < epsr)
				c.ratio = epsr;
			else
			if(c.ratio < c.min * rs / szcx && checkmin) {
				c.ratio = c.min * rs / szcx;
				if(delta > 0)
					nci.Add(ci[i]);
			}
			else
			if(c.ratio > c.max * rs / szcx) {
				c.ratio = c.max * rs / szcx;
				if(delta < 0)
					nci.Add(ci[i]);
			}
			else
				nci.Add(ci[i]);
			x += c.ratio;
		}

		delta = (psm + delta) - x;

		if(fabs(delta) < eps)
			break;
		ci = nci;
		if(ci.GetCount() == 0) {
			double psm = 0;
			for(int i = 0; i < sci.GetCount(); i++)
				psm += col[sci[i]].ratio;
			if(fabs(psm) < eps)
				return;
			double q = 1 + delta / psm;
			for(int i = 0; i < sci.GetCount(); i++)
				col[sci[i]].ratio *= q;
			return;
		}
	}
}

Vector<int> HeaderCtrl::GetVisibleCi(int from)
{
	Vector<int> sci;
	for(int i = from; i < col.GetCount(); i++)
		if(col[i].visible)
			sci.Add(i);
	return sci;
}

void HeaderCtrl::RefreshDistribution()
{
	int szcx = GetSize().cx;
	if(oszcx != szcx) {
		if(mode == SCROLL)
			for(int i = 0; i < col.GetCount(); i++) {
				Column& c = col[i];
				c.ratio = minmax((int)c.ratio, c.min, c.max);
			}
		else {
			Distribute(GetVisibleCi(0), 0);
			oszcx = szcx;
		}
		ReCompute();
	}
}

Rect HeaderCtrl::GetTabRect(int q)
{
	RefreshDistribution();
	return tabrect[q];
}

int  HeaderCtrl::GetTabWidth(int ci)
{
	return GetTabRect(ci).Width();
}

void HeaderCtrl::SetTabWidth0(int i, int cx)
{
	Column& c = col[i];
	int szcx = GetSize().cx;
	Rect ir = GetTabRect(i);
	bool checkmin = SumMin(0) < szcx;
	cx = checkmin ? minmax(cx, c.min, c.max) : min(cx, c.max);
	if(mode != SCROLL) {
		if(checkmin)
			cx = min(cx, szcx - SumMin(i + 1) - ir.left);
		cx = max(cx, szcx - SumMax(i + 1) - ir.left);
	}
	if(cx < 0)
		cx = 0;

	double rs = Denominator();
	int ocx = ir.Width();
	if(szcx == 0) return;

	double delta = rs * (cx - ocx) / szcx;
	if(ocx == cx) return;
	col[i].ratio += delta;

	switch(mode) {
	case PROPORTIONAL:
		Distribute(GetVisibleCi(i + 1), -delta);
		break;
	case REDUCELAST:
		for(int q = col.GetCount() - 1; q >= i; q--)
			Reduce(q, delta, rs, szcx, checkmin);
		break;
	case REDUCENEXT:
		for(int q = i + 1; q < col.GetCount(); q++)
			Reduce(q, delta, rs, szcx, checkmin);
		if(delta > 0)
			Reduce(i, delta, rs, szcx, checkmin);
		break;
	case SCROLL:
		col[i].ratio = cx;
		SbTotal();
		break;
	}

	ReCompute();
	Refresh();
}

void HeaderCtrl::Reduce(int i, double& delta, double rs, int szcx, bool checkmin)
{
	if(col[i].visible) {
		Column& c = col[i];
		double q = minmax(c.ratio - delta, checkmin ? c.min * rs / szcx : 0, c.max * rs / szcx);
		if(q < 0)
			q = 0;
		delta -= c.ratio - q;
		c.ratio = q;
	}
}

void HeaderCtrl::SetTabWidth(int i, int cx) {
	SetTabWidth0(i, cx);
	WhenLayout();
}

void HeaderCtrl::Paint(Draw& w) {
	RefreshDistribution();
	Size sz = GetSize();
	bool ds = !IsShowEnabled();
	double rs = Denominator();
	double rr = 0;
	int x = -sb;
	light = -1;
	bool first = true;
	for(int i = 0; i < col.GetCount(); i++) {
		if(col[i].visible) {
			Rect r;
			if(mode == SCROLL) {
				int cx = (int)col[i].ratio;
				r = RectC(x, 0, cx, sz.cy);
				x += cx;
			}
			else {
				rr += rs ? col[i].ratio : 1;
				int xx = int(rr * sz.cx / (rs ? rs : col.GetCount()));
				r = RectC(x, 0, i == col.GetCount() - 1 ? sz.cx - x : xx - x, sz.cy);
				x = xx;
			}
			bool mousein = HasMouseIn(r.Deflated(1, 0)) && col[i].WhenAction && pushi < 0;
			if(mousein)
				light = i;
			col[i].Paint(first, w,
			             r.left, r.top, r.Width(), r.Height(), ds, push && i == pushi, mousein);
		}
		if(x >= sz.cx) break;
	}
	Column h;
	h.Paint(first, w, x, 0, 999, sz.cy, false, false, false);
}

void HeaderCtrl::Layout()
{
	sb.SetPage(GetSize().cx);
}

int HeaderCtrl::GetNextTabWidth(int i) {
	while(++i < col.GetCount())
		if(col[i].visible)
			return GetTabWidth(i);
	return 0;
}

int HeaderCtrl::GetLastVisibleTab() {
	int i = col.GetCount();
	while(--i >= 0)
		if(col[i].visible) return i;
	return -1;
}

int HeaderCtrl::GetSplit(int px) {
	RefreshDistribution();
	px += sb;
	int cx = GetSize().cx;
	double rs = Denominator();
	int n = col.GetCount();
	int l = GetLastVisibleTab();
	if(mode != SCROLL && abs(px - cx) <= 4 && n > 0 && l >= 0 && GetTabWidth(l) < 4)
		while(--n >= 0)
			if(GetTabWidth(n) >= 4)
				return n;
	double rr = 0;
	int x = 0;
	int first_move = 0;
	while(first_move < n && (!col[first_move].visible || col[first_move].min == col[first_move].max))
		first_move++;
	int last_move = n - 1;
	while(last_move >= 0 && (!col[last_move].visible || col[last_move].min == col[last_move].max))
		last_move--;
	if(mode == PROPORTIONAL)
		last_move--;
	for(int i = 0; i < n; i++) {
		Column& cl = col[i];
		if(cl.visible) {
			bool canmove = (i >= first_move && i <= last_move);
			if(cl.min == cl.max) {
				int j = i;
				while(++j < n && !col[j].visible)
					;
				if(j >= n || col[j].min == col[j].max)
					canmove = false;
			}
			if(mode == SCROLL) {
				x += (int)col[i].ratio;
				if(canmove && px >= x - 3 && px < x + 3 && (i >= n - 1 || GetNextTabWidth(i) >= 4 || px < x))
					return i;
			}
			else {
				rr += rs ? col[i].ratio : 1;
				x = int(rr * cx / (rs ? rs : col.GetCount()));
				if(canmove && px >= x - 3 && px < x + 3 && i < n - 1 && (i >= n - 1 || GetNextTabWidth(i) >= 4 || px < x))
					return i;
			}
			if(px < x)
				return -1 - i;
		}
	}
	return Null;
}

Image HeaderCtrl::CursorImage(Point p, dword) {
	if(HasCapture())
		return split >= 0 ? CtrlsImg::HorzPos() : Image::Arrow();
	int q = GetSplit(p.x);
	return q < 0 ? Image::Arrow()
	             : GetTabWidth(q) < 4 ? CtrlsImg::HorzSplit()
	                                  : CtrlsImg::HorzPos();
}

void HeaderCtrl::LeftDown(Point p, dword keyflags) {
#ifdef _DEBUG
	if(keyflags & K_CTRL) {
		String text;
		for(int i = 0; i < col.GetCount(); i++)
			text += Format(i ? " %d" : "%d", GetTabWidth(i));
		WriteClipboardText(".ColumnWidths(\"" + text + "\");");
		BeepExclamation();
	}
#endif
	split = GetSplit(p.x);
	if(IsNull(split)) return;
	SetCapture();
	if(split >= 0) {
		colRect = GetTabRect(split);
		return;
	}
	pushi = -1 - split;
	if(!col[pushi].WhenAction) {
		pushi = -1;
		return;
	}
	colRect = GetTabRect(pushi);
	push = true;
	Refresh();
}

void HeaderCtrl::StartSplitDrag(int s)
{
	split = s;
	colRect = GetTabRect(split);
	SetCapture();
}

void HeaderCtrl::MouseMove(Point p, dword keyflags) {
	int q = GetSplit(p.x);
	q = IsNull(q) || q >= 0 ? -1 : -1 - q;
	if(q != light)
		Refresh();
	if(!HasCapture())
		return;
	Size sz = GetSize();
	int x = mode == SCROLL ? p.x + sb : min(sz.cx, p.x);
	if(split >= 0) {
		int w = x - colRect.left;
		if(w < 0) w = 0;
		if(w != GetTabWidth(split)) {
			SetTabWidth0(split, w);
			Refresh();
			if(track) {
				Sync();
				Action();
				WhenLayout();
			}
		}
	}
}

void HeaderCtrl::MouseLeave()
{
	Refresh();
}

void HeaderCtrl::LeftUp(Point, dword) {
	if(pushi >= 0 && push)
		col[pushi].WhenAction();
	push = false;
	pushi = -1;
	Refresh();
	if(split >= 0 && !track) {
		Action();
		WhenLayout();
	}
}

void HeaderCtrl::CancelMode() {
	split = pushi = -1;
	push = false;
}

void HeaderCtrl::ShowTab(int i, bool show) {
	Column& cm = Tab(i);
	if(cm.visible == show) return;
	cm.visible = show;
	if(mode == PROPORTIONAL)
		InvalidateDistribution();
	Refresh();
	WhenLayout();
}

#pragma warning(push)
#pragma warning(disable: 4700) // MSVC6 complaint about n having not been initialized

void HeaderCtrl::Serialize(Stream& s) {
	int version = 0x01;
	s / version;
	if(version < 0x01) {
		int n = col.GetCount();
		s / n;
		for(int i = 0; i < n; i++)
			if(i < col.GetCount()) {
				int n;
				s / n;
				col[i].ratio = n;
			}
			else {
				int dummy = 0;
				s / dummy;
			}
	}
	else {
		int n = col.GetCount();
		s / n;
		for(int i = 0; i < n; i++)
			if(i < col.GetCount())
				s % col[i].ratio;
			else {
				int dummy = 0;
				s / dummy;
			}
	}
	if(s.IsLoading()) {
		Refresh();
		WhenLayout();
	}
}

#pragma warning(pop)

void HeaderCtrl::FrameAdd(Ctrl& parent)
{
	parent.Add(*this);
	parent.Add(sb);
}

void HeaderCtrl::FrameRemove()
{
	Remove();
	sb.Remove();
}

void HeaderCtrl::FrameLayout(Rect& r)
{
	LayoutFrameTop(r, this, invisible ? 0 : GetHeight());
	LayoutFrameBottom(r, &sb, sb.IsShown() ? ScrollBarSize() : 0);
}

void HeaderCtrl::FrameAddSize(Size& sz)
{
	if(!invisible)
		sz.cy += GetHeight();
	if(sb.IsVisible())
		sz.cy += ScrollBarSize();
}

HeaderCtrl& HeaderCtrl::Invisible(bool inv)
{
	invisible = inv;
	if(InFrame() && GetParent())
		RefreshParentLayout();
	return *this;
}

void HeaderCtrl::Reset()
{
	col.Clear();
	track = true;
	mode = PROPORTIONAL;
	oszcx = -1;
	invisible = false;
	height = 0;
}

void HeaderCtrl::WScroll()
{
	WhenLayout();
}

void HeaderCtrl::Scroll()
{
	Refresh();
	WhenScroll();
}

void HeaderCtrl::ScrollVisibility()
{
	WhenScrollVisibility();
}

HeaderCtrl::HeaderCtrl() {
	Reset();
	NoWantFocus();
	sb.AutoHide();
	sb.WhenScroll = THISBACK(Scroll);
	WhenScroll = THISBACK(WScroll);
	sb.WhenVisibility = THISBACK(ScrollVisibility);
}

HeaderCtrl::~HeaderCtrl() {}

END_UPP_NAMESPACE
