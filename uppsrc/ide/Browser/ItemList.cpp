#include "Browser.h"

int CppItemInfoDisplay::DoPaint(Draw& w, const Rect& r, const Value& q,
	                            Color _ink, Color paper, dword style) const
{
	const CppItemInfo& m = ValueTo<CppItemInfo>(q);
	w.DrawRect(r, paper);
	bool focuscursor = (style & (FOCUS|CURSOR)) == (FOCUS|CURSOR) || (style & SELECT);
	if(IsNull(q)) return 0;
	int x = r.left;
	if(m.access == PROTECTED)
		w.DrawImage(x, r.top + 1, BrowserImg::mprotected());
	else
	if(m.access == PRIVATE)
		w.DrawImage(x, r.top + 1, BrowserImg::mprivate());
	else
	if(m.access == WITHBODY)
		w.DrawImage(x, r.top + 1, BrowserImg::impl());
	x += 6;
	Image img = BrowserImg::unknown();
	Image bk;
	switch(m.kind) {
	case FUNCTIONTEMPLATE:
		bk = BrowserImg::template_function();
	case FUNCTION:
		img = BrowserImg::function();
		break;
	case INSTANCEFUNCTIONTEMPLATE:
		bk = BrowserImg::template_function();
	case INSTANCEFUNCTION:
		img = BrowserImg::instance_function();
		break;
	case CLASSFUNCTIONTEMPLATE:
		bk = BrowserImg::template_function();
	case CLASSFUNCTION:
		img = BrowserImg::class_function();
		break;
	case STRUCTTEMPLATE:
		bk = BrowserImg::template_struct();
	case STRUCT:
		img = BrowserImg::type_struct();
		break;
	case INSTANCEVARIABLE:
		img = BrowserImg::instance_data();
		break;
	case CLASSVARIABLE:
		img = BrowserImg::class_data();
		break;
	case VARIABLE:
		img = BrowserImg::data();
		break;
	case ENUM:
		img = BrowserImg::type_enum();
		break;
	case INLINEFRIEND:
		img = BrowserImg::inline_friend();
		break;
	case TYPEDEF:
		img = BrowserImg::type_def();
		break;
	case CONSTRUCTOR:
		img = BrowserImg::constructor();
		break;
	case DESTRUCTOR:
		img = BrowserImg::destructor();
		break;
	case MACRO:
		img = BrowserImg::macro();
		break;
	}

	int ry = (r.top + r.bottom) / 2;
	int by = ry - bk.GetSize().cy / 2;
	int iy = ry - img.GetSize().cy / 2;

	if(focuscursor) {
		DrawHighlightImage(w, x, by, bk);
		w.DrawImage(x, iy, img);
	}
	else {
		w.DrawImage(x, by, bk);
		w.DrawImage(x, iy, img);
	}
	if(m.inherited) {
		w.DrawImage(x + 10, r.top, BrowserImg::inherited());
		for(int i = 1; i < min(m.inherited, 5); i++)
			w.DrawRect(x + 10, r.top + 7 + 2 * i, 7, 1, SColorText);
	}
	x += 20;
	int y = r.top;
	int x0 = x;
	Vector<ItemTextPart> n = ParseItemNatural(m);
	for(int i = 0; i < n.GetCount(); i++) {
		ItemTextPart& p = n[i];
		Font f = BrowserFont();
		Color ink = SColorText;
		switch(p.type) {
		case ITEM_PNAME:
			f.Bold();
		case ITEM_NUMBER:
			ink = Red;
			break;
		case ITEM_TNAME:
			ink = Green;
		case ITEM_NAME:
			f.Bold();
			break;
		case ITEM_UPP:
			ink = Cyan;
			break;
		case ITEM_CPP_TYPE:
		case ITEM_CPP:
			ink = LtBlue;
			break;
		case ITEM_SIGN:
			ink = Magenta;
			break;
		}
		if(m.overed)
			f.Italic();
		Size fsz = GetTextSize(~m.natural + p.pos, f, p.len);
		w.DrawText(x, y, ~m.natural + p.pos, f, focuscursor ? _ink : ink, p.len);
		x += fsz.cx;
	}
	if(m.virt || m.over)
		w.DrawRect(x0, r.bottom - 2, x - x0, 1, m.over ? m.virt ? LtRed : LtBlue : SColorText);
	if(m.inherited && m.IsType())
		w.DrawRect(r.left, r.top, r.Width(), 1, SColorDisabled);

	String k = m.nesting;
	if(k != "::")
		k << "::";
	k << m.key;
	int cnt = GetRefLinks(k).GetCount();
	if(cnt) {
		Size sz = BrowserImg::Ref().GetSize();
		int xx = r.right - sz.cx - 1;
		int yy = r.top + (r.Height() - sz.cy) / 2;
		DrawHighlightImage(w, xx, yy, BrowserImg::Ref());
		if(cnt > 1) {
			String txt = AsString(cnt);
			Font fnt = Arial(10).Bold();
			Size tsz = GetTextSize(txt, fnt);
			Point p(xx + (sz.cx - tsz.cx) / 2, yy + (sz.cy - tsz.cy) / 2);
			for(int ax = -1; ax <= 1; ax++)
				for(int ay = -1; ay <= 1; ay++)
					w.DrawText(p.x + ax, p.y + ay, txt, fnt, White);
			w.DrawText(p.x, p.y, txt, fnt, Blue);
		}
		x += sz.cx + 3;
	}

	return x;
}

void CppItemInfoDisplay::Paint(Draw& w, const Rect& r, const Value& q,
                                  Color _ink, Color paper, dword style) const {
	DoPaint(w, r, q, _ink, paper, style);
}

Size CppItemInfoDisplay::GetStdSize(const Value& q) const
{
	NilDraw w;
	return Size(DoPaint(w, Rect(0, 0, INT_MAX, INT_MAX), q, Null, Null, 0),
	            max(16, BrowserFont().Info().GetHeight()));
}

String ItemList::Item(int i)
{
	const CppItemInfo& m = ValueTo<CppItemInfo>(Get(i));
	String k = m.nesting;
	if(k != "::")
		k << "::";
	k << m.key;
	return k;
}

int ItemList::GetTopic(Point p, String& key)
{
	if(!active_topics)
		return -1;
	int i = GetItem(p);
	if(i < 0)
		return -1;
	String m = Item(i);
	int c = GetRefLinks(m).GetCount();
	Size sz = BrowserImg::Ref().GetSize();
	Rect r = GetItemRect(i);
	p.y -= r.top + (r.Height() - sz.cy) / 2;
	if(p.y >= 0 && p.y <  sz.cy) {
		i = (r.right - 1 - p.x) / sz.cx;
		if(i >= 0 && i < c) {
			key = m;
			return i;
		}
	}
	return -1;
}

void ItemList::Clear()
{
	display.htopic = -1;
	ColumnList::Clear();
}

ItemList::ItemList()
{
	display.htopic = -1;
	SetDisplay(display);
	ItemHeight(BrowserFont().Info().GetHeight() + 3);
	NoRoundSize();
	NoWantFocus();
	active_topics = false;
}
