#include "RichEdit.h"

void RichEdit::FinishNF()
{
	anchorp = text.GetRichPos(anchor);
	cursorp = text.GetRichPos(cursor);
	tablesel = 0;
	if(anchor != cursor) {
		RichPos p = text.GetRichPos(cursor, anchorp.level);
		if(anchorp.level == 0 || anchorp.level < cursorp.level) {
			cursor = text.AdjustCursor(anchor, cursor);
			cursorp = text.GetRichPos(cursor);
		}
		else
		if(p.table != anchorp.table) {
			tablesel = anchorp.table;
			if(cursor < anchor) {
				cells.left = 0;
				cells.right = anchorp.cell.x;
				cells.top = 0;
				cells.bottom = anchorp.cell.y;
			}
			else {
				cells.left = anchorp.cell.x;
				cells.right = anchorp.tabsize.cx - 1;
				cells.top = anchorp.cell.y;
				cells.bottom = anchorp.tabsize.cy - 1;
			}
			text.AdjustTableSel(tablesel, cells);
		}
		else
		if(p.cell != anchorp.cell) {
			tablesel = anchorp.table;
			cells.left = min(anchorp.cell.x, p.cell.x);
			cells.right = max(anchorp.cell.x, p.cell.x);
			cells.top = min(anchorp.cell.y, p.cell.y);
			cells.bottom = max(anchorp.cell.y, p.cell.y);
			text.AdjustTableSel(tablesel, cells);
		}
	}
	cursorc = text.GetCaret(cursor, pagesz);
	Size sz = GetSize();
	SetSb();
	Rect r = PlaceCaret();
	if(r.top == GetPosY(text.GetCaret(0, pagesz)))
		sb = 0;
	else
		sb.ScrollInto(r.top, r.Height());
	PageY top, bottom;
	int sell = min(cursor, anchor);
	int selh = max(cursor, anchor);
	if(tablesel)
		Refresh();
	else
	if(text.GetInvalid(top, bottom, pagesz, sell, selh, osell, oselh)) {
		int y = GetPosY(top);
		Refresh(0, y - sb, sz.cx, GetPosY(bottom) - y);
		y = GetPosY(text.GetHeight(pagesz)) - sb;
		if(y < sz.cy)
			Refresh(0, y, sz.cx, sz.cy - y);
	}
	osell = sell;
	oselh = selh;
	text.Validate();
	FixObjectRect();
	SetupRuler();
}

void RichEdit::Finish()
{
	FinishNF();
	ReadFormat();
}

void RichEdit::MoveNG(int newpos, bool select)
{
	if(newpos < 0) newpos = 0;
	if(newpos >= text.GetLength() + select) newpos = text.GetLength() + select;
	CloseFindReplace();
	cursor = newpos;
	if(!select)
		anchor = cursor;
	objectpos = -1;
	Finish();
}

void RichEdit::Move(int newpos, bool select)
{
	MoveNG(newpos, select);
	gx = cursorc.left;
}

void RichEdit::MoveUpDown(int dir, bool select, int pg)
{
	Rect page = pagesz;
	PageY h = text.GetHeight(pagesz);
	if(dir > 0 && cursor >= GetLength() && select) {
		Move(GetLength() + 1, true);
		return;
	}
	if(dir < 0 && cursor > GetLength()) {
		Move(GetLength(), select);
		return;
	}
	int c = text.GetVertMove(min(GetLength(), cursor), gx, page, dir);
	if(c >= 0)
		MoveNG(c, select);
	else
		Move(dir < 0 ? 0 : GetLength(), select);
	if(pg) {
		RichCaret pr = text.GetCaret(cursor, pagesz);
		PageY py;
		py.page = pr.page;
		py.y = pr.top + dir * pg;
		while(py.y > pagesz.cy) {
			py.y -= pagesz.cy;
			py.page++;
		}
		while(py.y < 0) {
			py.y += pagesz.cy;
			py.page--;
		}
		MoveNG(text.GetPos(pr.left, py, pagesz), select);
	}
}

void RichEdit::MovePageUpDown(int dir, bool select)
{
	PageRect p = text.GetCaret(cursor, pagesz);
	int q = GetPosY(p) - sb;
	MoveUpDown(dir, select, 4 * GetTextRect().Height() / GetZoom() / 5);
	p = text.GetCaret(cursor, pagesz);
	sb = GetPosY(p) - q;
}

void RichEdit::MoveHomeEnd(int dir, bool select)
{
	int c = cursor;
	while(c + dir >= 0 && c + dir <= text.GetLength()) {
		PageRect p1 = text.GetCaret(c + dir, pagesz);
		if(p1.page != cursorc.page || p1.top != cursorc.top)
			break;
		c += dir;
	}
	Move(c, select);
}

bool RichEdit::IsW(int c)
{
	return IsLetter(c) || IsDigit(c) || c == '_';
}

void RichEdit::MoveWordRight(bool select)
{
	int c = cursor;
	bool a = IsW(text[c]);
	while(c <= text.GetLength() && IsW(text[c]) == a)
		c++;
	Move(c, select);
}

void RichEdit::MoveWordLeft(bool select)
{
	int c = cursor;
	if(c == 0) return;
	bool a = IsW(text[c - 1]);
	while(c > 0 && IsW(text[c - 1]) == a)
		c--;
	Move(c, select);
}

bool RichEdit::SelBeg(bool select)
{
	if(IsSelection() && !select) {
		Move(min(cursor, anchor), false);
		return true;
	}
	return false;
}

bool RichEdit::SelEnd(bool select)
{
	if(IsSelection() && !select) {
		Move(max(cursor, anchor), false);
		return true;
	}
	return false;
}

void RichEdit::SelCell(int dx, int dy)
{
	Move(text.GetCellPos(tablesel, minmax(cursorp.cell.y + dy, 0, cursorp.tabsize.cy - 1),
	                               minmax(cursorp.cell.x + dx, 0, cursorp.tabsize.cx - 1)).pos, true);
}

bool RichEdit::CursorKey(dword key, int count)
{
	bool select = key & K_SHIFT;
	if(select && tablesel)
		switch(key & ~K_SHIFT) {
		case K_LEFT:
			SelCell(-1, 0);
			break;
		case K_RIGHT:
			SelCell(1, 0);
			break;
		case K_UP:
			SelCell(0, -1);
			break;
		case K_DOWN:
			SelCell(0, 1);
			break;
		default:
			return false;
		}
	else
		switch(key & ~K_SHIFT) {
		case K_LEFT:
			if(!SelBeg(select))
				Move(cursor - 1, select);
			break;
		case K_RIGHT:
			if(!SelEnd(select))
				Move(cursor + 1, select);
			break;
		case K_UP:
			if(!SelBeg(select))
				MoveUpDown(-1, select);
			break;
		case K_DOWN:
			if(!SelEnd(select))
				MoveUpDown(1, select);
			break;
		case K_PAGEUP:
			if(!SelBeg(select))
				MovePageUpDown(-1, select);
			break;
		case K_PAGEDOWN:
			if(!SelEnd(select))
				MovePageUpDown(1, select);
			break;
		case K_END:
			MoveHomeEnd(1, select);
			break;
		case K_HOME:
			MoveHomeEnd(-1, select);
			break;
		case K_CTRL_LEFT:
			if(!SelBeg(select))
				MoveWordLeft(select);
			break;
		case K_CTRL_RIGHT:
			if(!SelEnd(select))
				MoveWordRight(select);
			break;
		case K_CTRL_UP:
			sb.PrevLine();
			break;
		case K_CTRL_DOWN:
			sb.NextLine();
			break;
		case K_CTRL_HOME:
		case K_CTRL_PAGEUP:
			Move(0, select);
			break;
		case K_CTRL_END:
		case K_CTRL_PAGEDOWN:
			Move(text.GetLength(), select);
			break;
		case K_CTRL_A:
			Move(0, false);
			Move(text.GetLength(), true);
			break;
		default:
			return false;
		}
	Sync();
	return true;
}

bool RichEdit::IsSelection() const
{
	return anchor >= 0 && anchor != cursor;
}

bool RichEdit::GetSelection(int& l, int& h) const
{
	if(IsSelection()) {
		l = min(anchor, cursor);
		h = max(anchor, cursor);
		return true;
	}
	l = h = cursor;
	return false;
}

void RichEdit::CancelSelection()
{
	if(IsSelection()) {
		tablesel = 0;
		anchor = cursor;
		found = notfoundfw = false;
		CloseFindReplace();
		Finish();
	}
}

bool RichEdit::RemoveSelection(bool joinnext)
{
	if(IsSelection()) {
		if(tablesel) {
			NextUndo();
			SaveTable(tablesel);
			text.ClearTable(tablesel, cells);
			Move(text.GetCellPos(tablesel, cells.top, cells.left).pos);
		}
		else {
			int c = min(cursor, anchor);
			Remove(c, abs(cursor - anchor), joinnext);
			found = notfoundfw = false;
			CloseFindReplace();
			Move(c);
		}
		return true;
	}
	return false;
}

WString RichEdit::GetWordAtCursor()
{
	WString w;
	int c = cursor;
	if(IsLetter(text[c])) {
		while(c > 0 && IsLetter(text[c - 1]))
			c--;
		while(w.GetLength() < 64 && IsLetter(text[c])) {
			w.Cat(text[c]);
			c++;
		}
	}
	return w;
}

void RichEdit::AddUserDict()
{
	if(IsSelection()) return;
	WString w = GetWordAtCursor();
	if(w.IsEmpty()) return;
	SpellerAdd(w, formatinfo.language);
	text.ClearSpelling();
	Refresh();
}

void RichEdit::Goto()
{
	SetFocus();
	if(gototable.IsCursor())
	{
		Move(gototable.Get(1), false);
		Move(gototable.Get(2), true);
	}
}

void RichEdit::GotoType(int type, Ctrl& l)
{
	Vector<RichValPos> f = text.GetValPos(pagesz, type);
	gototable.Clear();
	for(int i = 0; i < f.GetCount(); i++) {
		const RichValPos& q = f[i];
		int endpos = q.pos;
		if(type == RichText::INDEXENTRIES) {
			WString ie = text.GetRichPos(endpos).format.indexentry;
			int l = text.GetLength();
			while(endpos < l) {
				RichPos p = text.GetRichPos(++endpos);
				if(p.format.indexentry != ie || p.chr == '\n')
					break;
			}
		}
		gototable.Add(q.data, q.pos, endpos);
	}
	if(gototable.GetCount())
		gototable.PopUp(&l);
}

void RichEdit::GotoLbl()
{
	GotoType(RichText::LABELS, label);
}

void RichEdit::GotoEntry()
{
	GotoType(RichText::INDEXENTRIES, indexentry);
}

void RichEdit::GotoLabel(const String& lbl)
{
	Vector<RichValPos> f = text.GetValPos(pagesz, RichText::LABELS);
	for(int i = 0; i < f.GetCount(); i++)
		if(f[i].data == WString(lbl)) {
			Move(f[i].pos);
			break;
		}
}
