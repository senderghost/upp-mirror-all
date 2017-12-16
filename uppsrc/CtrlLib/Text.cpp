#include <CtrlLib/CtrlLib.h>

#define LTIMING(x)  // RTIMING(x)

namespace Upp {

TextCtrl::TextCtrl()
{
	Unicode();
	undosteps = 1000;
	Clear();
	undoserial = 0;
	incundoserial = false;
	undo_op = false;
	WhenBar = THISBACK(StdBar);
	charset = CHARSET_UNICODE;
	color[INK_NORMAL] = SColorText;
	color[INK_DISABLED] = SColorDisabled;
	color[INK_SELECTED] = SColorHighlightText;
	color[PAPER_NORMAL] = SColorPaper;
	color[PAPER_READONLY] = SColorFace;
	color[PAPER_SELECTED] = SColorHighlight;
	color[WHITESPACE] = Blend(SColorLight, SColorHighlight);
	color[WARN_WHITESPACE] = Blend(SColorLight, SRed);
	processtab = true;
	processenter = true;
	nobg = false;
	rectsel = false;
#ifdef CPU_64
	max_total = 2047 * 1024 * 1024;
#else
#ifdef _DEBUG
	max_total = 100 * 1024 * 1024;
#else
	max_total = 200 * 1024 * 1024;
#endif
#endif
	max_line_len = 100000;
	truncated = false;
}

TextCtrl::~TextCtrl() {}

void TextCtrl::MiddleDown(Point p, dword flags)
{
	if(IsReadOnly())
		return;
	if(AcceptText(Selection())) {
		WString w = GetWString(Selection());
		selclick = false;
		LeftDown(p, flags);
		Paste(w);
		Action();
	}
}

void TextCtrl::CancelMode()
{
	selclick = false;
	dropcaret = Null;
	isdrag = false;
}

void TextCtrl::Clear()
{
	view = NULL;
	cline = cpos = 0;
	total = 0;
	truncated = false;
	lin.Clear();
	ClearLines();
	lin.Add();
	InsertLines(0, 1);
	DirtyFrom(0);
	undo.Clear();
	redo.Clear();
	ClearDirty();
	anchor = -1;
	cursor = 0;
	SetSb();
	PlaceCaret(0);
	SelectionChanged();
	Refresh();
}

void TextCtrl::DirtyFrom(int line) {}
void TextCtrl::SelectionChanged() {}
void TextCtrl::ClearLines() {}
void TextCtrl::InsertLines(int line, int count) {}
void TextCtrl::RemoveLines(int line, int count) {}
void TextCtrl::PreInsert(int pos, const WString& text) {}
void TextCtrl::PostInsert(int pos, const WString& text) {}
void TextCtrl::PreRemove(int pos, int size) {}
void TextCtrl::PostRemove(int pos, int size) {}
void TextCtrl::RefreshLine(int i) {}
void TextCtrl::InvalidateLine(int i) {}
void TextCtrl::SetSb() {}
void TextCtrl::PlaceCaret(int newcursor, bool sel) {}

int TextCtrl::RemoveRectSelection() { return 0; }
WString TextCtrl::CopyRectSelection() { return Null; }
int TextCtrl::PasteRectSelection(const WString& s) { return 0; }

void   TextCtrl::CachePos(int pos)
{
	int p = pos;
	cline = GetLinePos(p);
	cpos = pos - p;
}

void   TextCtrl::CacheLinePos(int linei)
{
	if(linei >= 0 && linei < GetLineCount()) {
		cpos = GetPos(linei);
		cline = linei;
	}
}

bool   TextCtrl::IsUnicodeCharset(byte charset)
{
	return findarg(charset, CHARSET_UTF8, CHARSET_UTF8_BOM, CHARSET_UTF16_LE, CHARSET_UTF16_BE,
	                        CHARSET_UTF16_LE_BOM, CHARSET_UTF16_BE_BOM) >= 0;
}

int   TextCtrl::Load0(Stream& in, byte charset, bool view) {
	Clear();
	lin.Clear();
	ClearLines();
	total = 0;
	SetCharset(charset);
	charset = ResolveCharset(charset);
	truncated = false;
	this->view = NULL;
	if(view) {
		this->view = &in;
		SetReadOnly();
	}
	if(charset == CHARSET_UTF8_BOM && in.GetLeft() >= 3) {
		int64 pos = in.GetPos();
		byte h[3];
		if(!(in.Get(h, 3) == 3 && h[0] == 0xEF && h[1] == 0xBB && h[2] == 0xBF))
			in.Seek(pos);
		charset = CHARSET_UTF8;
	}
	int be16 = findarg(charset, CHARSET_UTF16_LE_BOM, CHARSET_UTF16_BE_BOM);
	if(be16 >= 0 && in.GetLeft() >= 2) {
		int64 pos = in.GetPos();
		dword h = in.Get16le();
		if(h != (be16 ? 0xfffe : 0xfeff))
			in.Seek(pos);
		charset = be16 ? CHARSET_UTF16_BE : CHARSET_UTF16_LE;
	}
	int m = Load2(lin, total, in, charset, view);
	InsertLines(0, lin.GetCount());
	Update();
	SetSb();
	PlaceCaret(0);
	return m;
}

int   TextCtrl::Load2(Vector<Ln>& ls, int& total, Stream& in, byte charset, bool view)
{
	StringBuffer ln;
	bool cr = false;
	byte b8 = 0;
	int64 linepos = in.GetPos();
	auto add_pos = [&](int len, int slen) {
		Ln& ln = ls.Add();
		ln.len = len;
		ln.SetPos(linepos, slen);
	};
	if(charset == CHARSET_UTF16_LE || charset == CHARSET_UTF16_BE) {
		WStringBuffer wln;
		auto put_wln = [&]() {
			if(view)
				add_pos(wln.GetCount(), wln.GetCount() * 2);
			else
				ls.Add().Set(wln);
		};
		for(;;) {
			int c = charset == CHARSET_UTF16_LE ? in.Get16le() : in.Get16be();
			if(c < 0) {
				total += wln.GetCount();
				put_wln();
				goto finish;
			}
			if(c == '\r')
				cr = true;
			else
			if(c == '\n') {
			truncate_line:
				total += wln.GetCount() + 1;
				put_wln();
				wln.Clear();
				linepos = in.GetPos();
			}
			else {
				wln.Cat(c);
				if(wln.GetCount() >= max_line_len)
					goto truncate_line;
			}
		}
	}
	else
		for(;;) {
			byte h[200];
			int size;
			int64  pos = in.GetPos();
			const byte *s = in.GetSzPtr(size);
			if(size == 0)  {
				size = in.Get(h, 200);
				s = h;
				if(size == 0)
					break;
			}
			const byte *posptr = s;
			const byte *e = s + size;
			while(s < e) {
				const byte *b = s;
				const byte *ee = s + min(size_t(e - s), size_t(max_line_len - ln.GetCount()));
				{
					while(s < ee && *s != '\r' && *s != '\n') {
						b8 |= *s++;
						while(s < ee && *s >= ' ' && *s < 128) // Interestingly, this speeds things up
							s++;
						while(s < ee && *s >= ' ')
							b8 |= *s++;
					}
				}
				if(b < s) {
					if(s - b + ln.GetCount() > max_total)
						ln.Cat((const char *)b, max_total - ln.GetCount());
					else
						ln.Cat((const char *)b, (const char *)s);
				}
				auto put_ln = [&]() -> bool {
					int len = charset == CHARSET_UTF8 && (b8 & 0x80) ? utf8len(~ln, ln.GetCount()) : ln.GetCount();
					if(total + len + 1 > max_total) {
						truncated = true;
						return false;
					}
					total += len + 1;
					if(view)
						add_pos(len, ln.GetCount());
					else {
						Ln& l = ls.Add();
						l.len = len;
						l.Set(ln, charset);
					}
					return true;
				};
				while(ln.GetCount() >= max_line_len) {
					int ei = max_line_len;
					if(charset == CHARSET_UTF8)
						while(ei > 0 && ei > max_line_len - 6 && !((byte)ln[ei] < 128 || IsUtf8Lead((byte)ln[ei]))) // break lse at whole utf8 codepoint if possible
							ei--;
					String nln(~ln + ei, ln.GetCount() - ei);
					ln.SetCount(ei);
					truncated = true;
					if(!put_ln())
						goto out_of_limit;
					ln = nln;
				}
				if(s < e && *s == '\r') {
					s++;
					cr = true;
				}
				if(s < e && *s == '\n') {
					if(!put_ln())
						goto out_of_limit;
					ln.Clear();
					b8 = 0;
					s++;
					linepos = s - posptr + pos;
				}
			}
		}

out_of_limit:
	{
		WString w = ToUnicode(~ln, ln.GetCount(), charset);
		if(total + w.GetLength() <= max_total) {
			ls.Add().Set(w);
			total += w.GetLength();
		}
	}
finish:
	return ls.GetCount() > 1 ? cr ? LE_CRLF : LE_LF : LE_DEFAULT;
}

String TextCtrl::GetUtf8Line(int i) const
{
	if(view) {
		view->Seek(lin[i].GetPos()); // TODO: Conversion!
		return view->Get(lin[i].GetSLen()); // TODO: What if error?
	}
	return lin[i].GetString();
}

TextCtrl::LnText TextCtrl::GetLnText(int i) const
{
	LnText h;
	if(view) {
		h.h = GetUtf8Line(i);
		h.text = ~h.h;
		h.size = h.h.GetCount();
	}
	else {
		h.text = lin[i].Get();
		h.size = lin[i].GetSize();
	}
	return h;
}

void   TextCtrl::Save(Stream& s, byte charset, int line_endings) const {
	if(charset == CHARSET_UTF8_BOM) {
		static byte bom[] = { 0xEF, 0xBB, 0xBF };
		s.Put(bom, 3);
		charset = CHARSET_UTF8;
	}
	if(charset == CHARSET_UTF16_LE_BOM) {
		s.Put16le(0xfeff);
		charset = CHARSET_UTF16_LE;
	}
	if(charset == CHARSET_UTF16_BE_BOM) {
		s.Put16be(0xfeff);
		charset = CHARSET_UTF16_BE;
	}
	charset = ResolveCharset(charset);
	String le = "\n";
#ifdef PLATFORM_WIN32
	if(line_endings == LE_DEFAULT)
		le = "\r\n";
#endif
	if(line_endings == LE_CRLF)
		le = "\r\n";
	int be16 = findarg(charset, CHARSET_UTF16_LE, CHARSET_UTF16_BE);
	if(be16 >= 0) {
		String wle;
		for(int i = 0; i < le.GetCount(); i++) {
			if(be16)
				wle.Cat(0);
			wle.Cat(le[i]);
			if(!be16)
				wle.Cat(0);
		}
		for(int i = 0; i < lin.GetCount(); i++) {
			if(i)
				s.Put(wle);
			WString txt = GetWLine(i);
			const wchar *e = txt.End();
			if(be16)
				for(const wchar *w = txt; w != e; w++)
					s.Put16be(*w);
			else
				for(const wchar *w = txt; w != e; w++)
					s.Put16le(*w);
		}
		return;
	}
	for(int i = 0; i < lin.GetCount(); i++) {
		if(i)
			s.Put(le);
		if(charset == CHARSET_UTF8)
			s.Put(lin[i].Get(), lin[i].GetSize());
		else {
			String txt = FromUnicode(GetWLine(i), charset);
			const char *e = txt.End();
			for(const char *w = txt; w != e; w++)
				s.Put(*w == DEFAULTCHAR ? '?' : *w);
		}
	}
}

void   TextCtrl::Set(const String& s, byte charset) {
	StringStream ss(s);
	Load(ss, charset);
}

String TextCtrl::Get(byte charset) const
{
	StringStream ss;
	Save(ss, charset);
	return ss;
}

int TextCtrl::GetInvalidCharPos(byte charset) const
{
	int q = 0;
	if(!IsUnicodeCharset(charset))
		for(int i = 0; i < GetLineCount(); i++) {
			WString txt = GetWLine(i);
			WString ctxt = ToUnicode(FromUnicode(txt, charset), charset);
			for(int w = 0; w < txt.GetLength(); w++)
				if(txt[w] != ctxt[w])
					return q + w;
			q += txt.GetLength() + 1;
		}
	return -1;
}

void   TextCtrl::ClearDirty()
{
	dirty = 0;
	ClearModify();
	WhenState();
}

TextCtrl::UndoData TextCtrl::PickUndoData()
{
	UndoData data;
	data.undo = pick(undo);
	data.redo = pick(redo);
	data.undoserial = undoserial;
	return data;
}

void TextCtrl::SetPickUndoData(TextCtrl::UndoData&& data)
{
	undo = pick(data.undo);
	redo = pick(data.redo);
	undoserial = data.undoserial;
	incundoserial = true;
}

void TextCtrl::Set(const WString& s)
{
	Clear();
	Insert0(0, s);
}

void  TextCtrl::SetData(const Value& v)
{
	Set((WString)v);
}

Value TextCtrl::GetData() const
{
	return GetW();
}

String TextCtrl::GetEncodedLine(int i, byte charset) const
{
	charset = ResolveCharset(charset);
	if(charset == CHARSET_UTF8)
		return GetUtf8Line(i);
	LnText h = GetLnText(i);
	return FromUnicode(FromUtf8(h.text, h.size), charset);
}

int   TextCtrl::GetLinePos(int& pos) const {
	if(pos < cpos && cpos - pos < pos) {
		int i = cline;
		int ps = cpos;
		for(;;) {
			ps -= GetLineLength(--i) + 1;
			if(ps <= pos) {
				pos = pos - ps;
				return i;
			}
		}
	}
	else {
		int i = 0;
		if(pos >= cpos) {
			pos -= cpos;
			i = cline;
		}
		for(;;) {
			int n = GetLineLength(i) + 1;
			if(pos < n) return i;
			pos -= n;
			i++;
			if(i >= GetLineCount()) {
				pos = GetLineLength(GetLineCount() - 1);
				return GetLineCount() - 1;
			}
		}
	}
}

int   TextCtrl::GetPos(int ln, int lpos) const {
	ln = minmax(ln, 0, GetLineCount() - 1);
	int i, pos;
	if(ln < cline && cline - ln < ln) {
		pos = cpos;
		i = cline;
		while(i > ln)
			pos -= GetLineLength(--i) + 1;
	}
	else {
		if(ln >= cline) {
			pos = cpos;
			i = cline;
		}
		else {
			pos = 0;
			i = 0;
		}
		while(i < ln)
			pos += GetLineLength(i++) + 1;
	}
	return pos + min(GetLineLength(ln), lpos);
}

WString TextCtrl::GetW(int pos, int size) const
{
	int i = GetLinePos(pos);
	WStringBuffer r;
	for(;;) {
		if(i >= GetLineCount()) break;
		WString ln = GetWLine(i++);
		int sz = min(ln.GetLength() - pos, size);
		if(pos == 0 && sz == ln.GetLength())
			r.Cat(ln);
		else
			r.Cat(ln.Mid(pos, sz));
		size -= sz;
		if(size == 0) break;
#ifdef PLATFORM_WIN32
		r.Cat('\r');
#endif
		r.Cat('\n');
		size--;
		if(size == 0) break;
		pos = 0;
	}
	return r;
}

String TextCtrl::Get(int pos, int size, byte charset) const
{
	if(charset == CHARSET_UTF8) {
		int i = GetLinePos(pos);
		StringBuffer r;
		for(;;) {
			if(i >= GetLineCount()) break;
			int sz = min(GetLineLength(i) - pos, size);
			LnText h = GetLnText(i);
			const char *s = h.text;
			int n = h.size;
			i++;
			if(pos == 0 && sz == n)
				r.Cat(s, n);
			else
				r.Cat(FromUtf8(s, n).Mid(pos, sz).ToString());
			size -= sz;
			if(size == 0) break;
	#ifdef PLATFORM_WIN32
			r.Cat('\r');
	#endif
			r.Cat('\n');
			size--;
			if(size == 0) break;
			pos = 0;
		}
		return r;
	}
	return FromUnicode(GetW(pos, size), charset);
}

int  TextCtrl::GetChar(int pos) const {
	if(pos < 0 || pos >= GetLength())
		return 0;
	int i = GetLinePos(pos);
	WString ln = GetWLine(i);
	int c = ln.GetLength() == pos ? '\n' : ln[pos];
	return c;
}

int TextCtrl::Insert0(int pos, const WString& txt) { // TODO: Do this with utf8
	int inspos = pos;
	PreInsert(inspos, txt);
	if(pos < cpos)
		cpos = cline = 0;
	int i = GetLinePos(pos);
	DirtyFrom(i);
	int size = 0;

	WStringBuffer lnb;
	Vector<WString> iln;
	const wchar *s = txt;
	while(s < txt.End())
		if(*s >= ' ') {
			const wchar *b = s;
			while(*s >= ' ') // txt is zero teminated...
				s++;
			int sz = int(s - b);
			lnb.Cat(b, sz);
			size += sz;
		}
		else
		if(*s == '\t') {
			lnb.Cat(*s);
			size++;
			s++;
		}
		else
		if(*s == '\n') {
			iln.Add(lnb);
			size++;
			lnb.Clear();
			s++;
		}
		else
			s++;
	WString ln = lnb;
	WString l = GetWLine(i);
	if(iln.GetCount()) {
		iln[0] = l.Mid(0, pos) + iln[0];
		ln.Cat(l.Mid(pos));
		SetLine(i, ln);
		InvalidateLine(i);
		LineInsert(i, iln.GetCount());
		for(int j = 0; j < iln.GetCount(); j++)
			SetLine(i + j, iln[j]);
		InsertLines(i, iln.GetCount());
		Refresh();
	}
	else {
		SetLine(i, l.Mid(0, pos) + ln + l.Mid(pos));
		InvalidateLine(i);
		RefreshLine(i);
	}
	total += size;
	SetSb();
	Update();
	PostInsert(inspos, txt);
	return size;
}

void TextCtrl::Remove0(int pos, int size) {
	int rmpos = pos, rmsize = size;
	PreRemove(rmpos, rmsize);
	total -= size;
	if(pos < cpos)
		cpos = cline = 0;
	int i = GetLinePos(pos);
	DirtyFrom(i);
	WString ln = GetWLine(i);
	int sz = min(ln.GetLength() - pos, size);
	ln.Remove(pos, sz);
	size -= sz;
	SetLine(i, ln);
	if(size == 0) {
		InvalidateLine(i);
		RefreshLine(i);
	}
	else {
		size--;
		int j = i + 1;
		for(;;) {
			int sz = GetLineLength(j) + 1;
			if(sz > size) break;
			j++;
			size -= sz;
		}
		WString p1 = GetWLine(i);
		WString p2 = GetWLine(j);
		p1.Insert(p1.GetLength(), p2.Mid(size, p2.GetLength() - size));
		SetLine(i, p1);
		LineRemove(i + 1, j - i);
		RemoveLines(i + 1, j - i);
		InvalidateLine(i);
		Refresh();
	}
	Update();
	PostRemove(rmpos, rmsize);
	SetSb();
}

void TextCtrl::Undodo()
{
	while(undo.GetCount() > undosteps)
		undo.DropHead();
	redo.Clear();
}

void TextCtrl::NextUndo()
{
	undoserial += incundoserial;
	incundoserial = false;
}

void TextCtrl::IncDirty() {
	dirty++;
	if(dirty == 0 || dirty == 1)
	{
		if(dirty)
			SetModify();
		else
			ClearModify();
		WhenState();
	}
}

void TextCtrl::DecDirty() {
	dirty--;
	if(dirty == 0 || dirty == -1)
	{
		if(dirty)
			SetModify();
		else
			ClearModify();
		WhenState();
	}
}

int TextCtrl::InsertU(int pos, const WString& txt, bool typing) {
	int sz = Insert0(pos, txt);
	if(undosteps) {
		if(undo.GetCount() > 1 && typing && *txt != '\n' && IsDirty()) {
			UndoRec& u = undo.Tail();
			if(u.typing && u.pos + u.size == pos) {
				u.size += txt.GetLength();
				return sz;
			}
		}
		UndoRec& u = undo.AddTail();
		incundoserial = true;
		IncDirty();
		u.serial = undoserial;
		u.pos = pos;
		u.size = sz;
		u.typing = typing;
	}
	return sz;
}

void TextCtrl::RemoveU(int pos, int size) {
	if(size + pos > total)
		size = int(total - pos);
	if(size <= 0) return;
	if(undosteps) {
		UndoRec& u = undo.AddTail();
		incundoserial = true;
		IncDirty();
		u.serial = undoserial;
		u.pos = pos;
		u.size = 0;
		u.text = Get(pos, size, CHARSET_UTF8);
		u.typing = false;
	}
	Remove0(pos, size);
}

int TextCtrl::Insert(int pos, const WString& _txt, bool typing) {
	if(pos + _txt.GetCount() > max_total)
		return 0;
	WString txt = _txt;
	if(!IsUnicodeCharset(charset))
		for(int i = 0; i < txt.GetCount(); i++)
			if(FromUnicode(txt[i], charset) == DEFAULTCHAR)
				txt.Set(i, '?');
	int sz = InsertU(pos, txt, typing);
	Undodo();
	return sz;
}

int TextCtrl::Insert(int pos, const String& txt, byte charset)
{
	return Insert(pos, ToUnicode(txt, charset), false);
}

void TextCtrl::Remove(int pos, int size) {
	RemoveU(pos, size);
	Undodo();
}

void TextCtrl::Undo() {
	if(undo.IsEmpty()) return;
	undo_op = true;
	int nc = 0;
	int s = undo.Tail().serial;
	while(undo.GetCount()) {
		const UndoRec& u = undo.Tail();
		if(u.serial != s)
			break;
		UndoRec& r = redo.AddTail();
		r.serial = s;
		r.typing = false;
		nc = r.pos = u.pos;
		CachePos(r.pos);
		if(u.size) {
			r.size = 0;
			r.text = Get(u.pos, u.size, CHARSET_UTF8);
			Remove0(u.pos, u.size);
		}
		else {
			WString text = FromUtf8(u.text);
			r.size = Insert0(u.pos, text);
			nc += r.size;
		}
		undo.DropTail();
		DecDirty();
	}
	ClearSelection();
	PlaceCaret(nc, false);
	Action();
	undo_op = false;
}

void TextCtrl::Redo() {
	if(!redo.GetCount()) return;
	NextUndo();
	int s = redo.Tail().serial;
	int nc = 0;
	while(redo.GetCount()) {
		const UndoRec& r = redo.Tail();
		if(r.serial != s)
			break;
		nc = r.pos + r.size;
		CachePos(r.pos);
		if(r.size)
			RemoveU(r.pos, r.size);
		else
			nc += InsertU(r.pos, FromUtf8(r.text));
		redo.DropTail();
		IncDirty();
	}
	ClearSelection();
	PlaceCaret(nc, false);
	Action();
}

void  TextCtrl::ClearSelection() {
	anchor = -1;
	Refresh();
	SelectionChanged();
	WhenSel();
}

void   TextCtrl::SetSelection(int l, int h) {
	if(l != h) {
		PlaceCaret(minmax(l, 0, total), false);
		PlaceCaret(minmax(h, 0, total), true);
	}
	else
		SetCursor(l);
}

bool   TextCtrl::GetSelection(int& l, int& h) const {
	if(anchor < 0) {
		l = h = cursor;
		return false;
	}
	else {
		l = min(anchor, cursor);
		h = max(anchor, cursor);
		return !rectsel;
	}
}

String TextCtrl::GetSelection(byte charset) const {
	int l, h;
	if(GetSelection(l, h))
		return Get(l, h - l, charset);
	return String();
}

WString TextCtrl::GetSelectionW() const {
	int l, h;
	if(GetSelection(l, h))
		return GetW(l, h - l);
	return WString();
}

bool   TextCtrl::RemoveSelection() {
	int l, h;
	if(anchor < 0) return false;
	if(IsRectSelection())
		l = RemoveRectSelection();
	else {
		GetSelection(l, h);
		Remove(l, h - l);
	}
	anchor = -1;
	Refresh();
	PlaceCaret(l);
	Action();
	return true;
}

void TextCtrl::RefreshLines(int l1, int l2) {
	int h = max(l1, l2);
	for(int i = min(l1, l2); i <= h; i++)
		RefreshLine(i);
}

void TextCtrl::Cut() {
	if(!IsReadOnly() && IsAnySelection()) {
		Copy();
		RemoveSelection();
	}
}

void TextCtrl::Copy() {
	int l, h;
	if(!GetSelection(l, h) && !IsAnySelection()) {
		int i = GetLine(cursor);
		l = GetPos(i);
		h = l + GetLineLength(i) + 1;
	}
	WString txt;
	if(IsRectSelection())
		txt = CopyRectSelection();
	else
		txt = GetW(l, h - l);
	ClearClipboard();
	AppendClipboardUnicodeText(txt);
	AppendClipboardText(txt.ToString());
}

void TextCtrl::SelectAll() {
	SetSelection();
}

int  TextCtrl::Paste(const WString& text) {
	if(IsReadOnly()) return 0;
	int n;
	if(IsRectSelection())
		n = PasteRectSelection(text);
	else {
		RemoveSelection();
		n = Insert(cursor, text);
		PlaceCaret(cursor + n);
	}
	Refresh();
	return n;
}

String TextCtrl::GetPasteText()
{
	return Null;
}

void TextCtrl::Paste() {
	WString w = ReadClipboardUnicodeText();
	if(w.IsEmpty())
		w = ReadClipboardText().ToWString();
	if(w.IsEmpty())
		w = GetPasteText().ToWString();
	Paste(w);
	Action();
}

void TextCtrl::StdBar(Bar& menu) {
	NextUndo();
	if(undosteps) {
		menu.Add(undo.GetCount() && IsEditable(), t_("Undo"), CtrlImg::undo(), THISBACK(Undo))
			.Key(K_ALT_BACKSPACE)
			.Key(K_CTRL_Z);
		menu.Add(redo.GetCount() && IsEditable(), t_("Redo"), CtrlImg::redo(), THISBACK(Redo))
			.Key(K_SHIFT|K_ALT_BACKSPACE)
			.Key(K_SHIFT_CTRL_Z);
		menu.Separator();
	}
	menu.Add(IsEditable() && IsAnySelection(),
			t_("Cut"), CtrlImg::cut(), THISBACK(Cut))
		.Key(K_SHIFT_DELETE)
		.Key(K_CTRL_X);
	menu.Add(IsAnySelection(),
			t_("Copy"), CtrlImg::copy(), THISBACK(Copy))
		.Key(K_CTRL_INSERT)
		.Key(K_CTRL_C);
	bool canpaste = IsEditable() && IsClipboardAvailableText();
	menu.Add(canpaste,
			t_("Paste"), CtrlImg::paste(), THISBACK(DoPaste))
		.Key(K_SHIFT_INSERT)
		.Key(K_CTRL_V);
	LineEdit *e = dynamic_cast<LineEdit *>(this);
	if(e) {
		menu.Add(canpaste,
				 t_("Paste in column"), CtrlImg::paste_vert(), callback(e, &LineEdit::DoPasteColumn))
			.Key(K_ALT_V|K_SHIFT);
		menu.Add(e->IsRectSelection(),
				 t_("Sort"), CtrlImg::sort(), callback(e, &LineEdit::Sort));
	}
	menu.Add(IsEditable() && IsAnySelection(),
			t_("Erase"), CtrlImg::remove(), THISBACK(DoRemoveSelection))
		.Key(K_DELETE);
	menu.Separator();
	menu.Add(GetLength(),
			t_("Select all"), CtrlImg::select_all(), THISBACK(SelectAll))
		.Key(K_CTRL_A);
}

String TextCtrl::GetSelectionData(const String& fmt) const
{
	return GetTextClip(GetSelectionW(), fmt);
}

}
