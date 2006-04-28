#include "CodeEditor.h"

#define LLOG(x) // RLOG(x)
#define LTIMING(x) // RTIMING(x)

#define IMAGEVECTOR Vector
#define IMAGECLASS  CodeEditorImg
#define IMAGEFILE   <CodeEditor/CodeEditor.iml>
#include <Draw/iml_source.h>

void CodeEditor::DirtyFrom(int line) {
	for(int i = 0; i < 4; i++)
		if(scache[i].line >= line)
			scache[i].Clear();
}

inline bool IsComment(int a, int b) {
	return a == '/' && b == '*' || a == '*' && b == '/' || a == '/' && b == '/';
}

void CodeEditor::PreInsert(int pos, const WString& text) {
	if(IsFullRefresh()) return;
	rm_ins = ScanSyntax(GetLine(pos) + 1);
}

inline bool RBR(int c) {
	return isbrkt(c);
}

void CodeEditor::PostInsert(int pos, const WString& text) {
	if(IsFullRefresh()) return;
	if(!ScanSyntax(GetLine(pos + text.GetLength()) + 1).MatchHilite(rm_ins)) {
		if(text.GetLength() == 1 && *text == '(' || *text == '[' || *text == ']' || *text == ')')
			RefreshChars(RBR);
		else
			Refresh();
		bar.Refresh();
	}
}

void CodeEditor::PreRemove(int pos, int size) {
	if(IsFullRefresh()) return;
	if(size == 1)
		rmb = Get(pos, size)[0];
	else
		rmb = 0;
	rm_ins = ScanSyntax(GetLine(pos + size) + 1);
}

void CodeEditor::PostRemove(int pos, int size) {
	if(IsFullRefresh()) return;
	if(!ScanSyntax(GetLine(pos) + 1).MatchHilite(rm_ins)) {
		if(rmb == '(' || rmb == '[' || rmb == ']' || rmb == ')')
			RefreshChars(RBR);
		else
			Refresh();
		bar.Refresh();
	}
	CheckBrackets();
}

void CodeEditor::ClearLines() {
	bar.ClearLines();
}

void CodeEditor::InsertLines(int line, int count) {
	bar.InsertLines(line, count);
}

void CodeEditor::RemoveLines(int line, int count) {
	bar.RemoveLines(line, count);
}

void CodeEditor::NewScrollPos() {
	bar.Scroll();
}

void CodeEditor::CheckBracket(int li, int pos, int ppos, int pos0, WString ln, int d, int limit)
{
	int li0 = li;
	int lvl = 1;
	pos += d;
	ppos += d;
	for(;;) {
		int c;
		for(;;) {
			while(pos < 0 || pos >= ln.GetLength()) {
				li += d;
				if(d * li >= d * limit)
					return;
				ln = GetWLine(li);
				pos = d < 0 ? ln.GetLength() - 1 : 0;
				ppos += d;
			}
			c = ln[pos];
			if((c == '\"' || c == '\'') && (pos == 0 || ln[pos - 1] != '\\' && ln[pos - 1] != '\'')) {
				pos += d;
				ppos += d;
				int lc = c;
				while(pos < ln.GetLength() && pos > 0) {
					if(ln[pos] == lc && (pos == 0 || ln[pos - 1] != '\\')) {
						pos += d;
						ppos += d;
						break;
					}
					pos += d;
					ppos += d;
				}
			}
			else
				break;
		}
		if(islbrkt(c))
			lvl += d;
		if(isrbrkt(c))
			lvl -= d;
		if(lvl <= 0) {
			highlight_bracket_pos0 = pos0;
			highlight_bracket_pos = ppos;
			RefreshLine(li);
			RefreshLine(li0);
			bracket_start = GetTimeClick();
			return;
		}
		pos += d;
		ppos += d;
	}
}

void CodeEditor::CopyWord() {
   int p = GetCursor();
   if(iscid(GetChar(p)) || (p > 0 && iscid(GetChar(--p))))
   {
      int e = GetLength();
      int f = p;
      while(--p >= 0 && iscid(GetChar(p)));
      ++p;
      while(++f < e && iscid(GetChar(f)));
      WString txt = GetW(p, f - p);
      WriteClipboardUnicodeText(txt);
      WriteClipboardText(txt.ToString(), false);
   }
}

void CodeEditor::SwapChars() {
   int i = GetLine(cursor);
   int j = GetPos(i);
   if (j < cursor && (cursor-j) < line[i].GetLength())
   {
      int p = cursor;
      WString txt(GetChar(p-1),1);
      Remove(p-1,1);
      Insert(p, txt, true);
      PlaceCaret(p);
   }
}

void CodeEditor::CheckLeftBracket(int pos)
{
	LTIMING("CheckLeftBracket");
	if(pos < 0 || pos >= GetLength())
		return;
	int ppos = pos;
	int li = GetLinePos(pos);
	WString ln = GetWLine(li);
	if(islbrkt(ln[pos]))
		CheckBracket(li, pos, ppos, ppos, ln, 1, min(li + 3000, GetLineCount()));
}

void CodeEditor::CheckRightBracket(int pos)
{
	LTIMING("CheckRightBracket");
	if(pos < 0 || pos >= GetLength())
		return;
	int ppos = pos;
	int li = GetLinePos(pos);
	WString ln = GetWLine(li);
	int c = ln[pos];
	if(c == ')' || c == '}' || c == ']')
		CheckBracket(li, pos, ppos, ppos, ln, -1, max(li - 3000, 0));
}

void CodeEditor::CancelBracketHighlight(int& pos)
{
	if(pos >= 0) {
		RefreshLine(GetLine(pos));
		pos = -1;
	}
}

void CodeEditor::Periodic()
{
	bool b = (((GetTimeClick() - bracket_start) >> 8) & 1) == 0;
	if(b != bracket_flash && hilite_bracket == 2) {
		bracket_flash = b;
		if(highlight_bracket_pos0 >= 0)
			RefreshLine(GetLine(highlight_bracket_pos0));
		if(highlight_bracket_pos >= 0)
			RefreshLine(GetLine(highlight_bracket_pos));
	}
}

void CodeEditor::SelectionChanged()
{
	if(!foundsel) {
		CloseFindReplace();
		found = false;
		notfoundfw = notfoundbk = false;
		findreplace.amend.Disable();
	}
	CheckBrackets();
}

void CodeEditor::CheckBrackets()
{
	CancelBracketHighlight(highlight_bracket_pos0);
	CancelBracketHighlight(highlight_bracket_pos);
	if(!IsSelection()) {
		CheckLeftBracket(GetCursor());
		if(highlight_bracket_pos < 0)
			CheckRightBracket(GetCursor());
		if(highlight_bracket_pos < 0)
			CheckLeftBracket(GetCursor() - 1);
		if(highlight_bracket_pos < 0)
			CheckRightBracket(GetCursor() - 1);
	}
	WhenSelection();
}

bool CodeEditor::InsertRS(int chr, int count) {
	if(IsReadOnly()) return true;
	if(IsSelection()) {
		InsertChar(chr, count);
		return true;
	}
	return false;
}

void CodeEditor::IndentEnter(int count) {
	if(InsertRS('\n', count)) return;
	while(count--) {
		int pp = GetCursor();
		int cl = GetLinePos(pp);
		WString pl = GetWLine(cl);
		InsertChar('\n', 1);
		SyntaxState st;
		int p = GetCursor();
		int l = GetLinePos(p);
		if(highlight >= 0 && GetLineLength(l) == p)
			st = ScanSyntax(GetCursorLine());
		if(st.par.GetCount() && st.par.Top().line == cl && !no_parenthesis_indent) {
			for(int i = 0; i < st.par.Top().pos && i < pl.GetLength(); i++)
				InsertChar(pl[i] == '\t' ? '\t' : ' ', 1);
			return;
		}
		if(st.endstmtline == cl && st.seline >= 0 && st.seline < GetLineCount())
			pl = GetWLine(st.seline);
		else {
			int i;
			for(i = 0; i < pl.GetLength(); i++) {
				if(pl[i] != ' ' && pl[i] != '\t')
					break;
			}
			if(pp < i)
				return;
		}
		const wchar *s = pl;
		while(*s == '\t' || *s == ' ')
			InsertChar(*s++, 1);
		if(st.stmtline == cl || st.blk.GetCount() && st.blk.Top() == cl)
			if(indent_spaces || (s > pl && s[-1] == ' '))
				InsertChar(' ', indent_amount);
			else
				InsertChar('\t', 1);
	}
}

void CodeEditor::IndentInsert(int chr) {
	if(InsertRS(chr)) return;
	int cl = GetCursorLine();
	WString l = GetWLine(cl);
	if(chr != '{' && chr != '}') {
		InsertChar(chr, 1, true);
		return;
	}
	const wchar *s;
	for(s = l; s < l.End(); s++)
		if(*s != ' ' && *s != '\t') {
			InsertChar(chr, 1);
			return;
		}
	int len = l.GetLength();
	SyntaxState st = ScanSyntax(cl);
	WString tl;
	int pos = GetPos(cl);
	if(chr == '{' && cl > 0 && st.stmtline == cl - 1 && highlight >= 0)
		tl = GetWLine(cl - 1);
	else
	if(chr == '}' && st.blk.GetCount() && highlight >= 0)
		tl = GetWLine(st.blk.Top());
	else {
		InsertChar(chr, 1);
		return;
	}
	SetCursor(pos);
	Remove(pos, len);
	s = tl;
	while(*s == '\t' || *s == ' ')
		InsertChar(*s++, 1);
	InsertChar(chr, 1);
}

void CodeEditor::MakeTabsOrSpaces(bool maketabs) {
	Point cursor = GetColumnLine(GetCursor());
	Point scroll = GetScrollPos();
	int l, h;
	bool is_sel = GetSelection(l, h);
	if(!is_sel) { l = 0; h = GetLength(); }
	if(h <= l)
	{
		BeepExclamation();
		return;
	}
	l = GetPos(GetLine(l));
	h = GetPos(GetLine(h - 1) + 1);
	String substring = Get(l, h - l);
	String out;
	int tab = GetTabSize();
	if(tab <= 0) tab = 8;
	for(const char *p = substring.Begin(), *e = substring.End(); p < e;)
	{
		int pos = 0;
		for(; p < e; p++)
			if(*p == '\t')
				pos = (pos / tab + 1) * tab;
			else if(*p == ' ')
				pos++;
			else
				break;
		if(maketabs)
		{
			out.Cat('\t', pos / tab);
			const char *b = p;
			while(p < e && *p++ != '\n')
				;
			out.Cat(b, p - b);
		}
		else
		{
			out.Cat(' ', pos);
			for(; p < e && *p != '\n'; p++)
				if(*p == '\t')
				{
					int npos = (pos / tab + 1) * tab;
					out.Cat(' ', npos - pos);
					pos = npos;
				}
				else
				{
					out.Cat(*p);
					pos++;
				}
			if(p < e)
				out.Cat(*p++);
		}
	}
	if(out == substring)
	{
		BeepInformation();
		return;
	}
	Remove(l, h - l);
	Insert(l, out.ToWString());
	if(is_sel)
		SetSelection(l, l + out.GetLength());
	SetCursor(GetGPos(cursor.y, cursor.x));
	SetScrollPos(scroll);
}

void CodeEditor::MoveNextWord(bool sel) {
	int p = GetCursor();
	int e = GetLength();
	if(iscid(GetChar(p)))
		while(p < e && iscid(GetChar(p))) p++;
	else
		while(p < e && !iscid(GetChar(p))) p++;
	PlaceCaret(p, sel);
}

void CodeEditor::MovePrevWord(bool sel) {
	int p = GetCursor();
	if(p == 0) return;
	if(iscid(GetChar(p - 1)))
		while(p > 0 && iscid(GetChar(p - 1))) p--;
	else
		while(p > 0 && !iscid(GetChar(p - 1))) p--;
	PlaceCaret(p, sel);
}

void CodeEditor::MoveNextBrk(bool sel) {
	int p = GetCursor();
	int e = GetLength();
	int c = GetChar(p);
	if(!islbrkt(GetChar(p)))
		while(p < e && !islbrkt(GetChar(p))) p++;
	else {
		int lvl = 1;
		p++;
		for(;;) {
			if(p >= e) break;
			int c = GetChar(p++);
			if(islbrkt(c)) lvl++;
			if(isrbrkt(c) && --lvl == 0) break;
		}
	}
	PlaceCaret(p, sel);
}

void CodeEditor::MovePrevBrk(bool sel) {
	int p = GetCursor();
	if(p < 2) return;
	if(!isrbrkt(GetChar(p - 1)))
		while(p > 0 && !isrbrkt(GetChar(p - 1))) p--;
	else {
		int lvl = 1;
		p -= 2;
		for(;;) {
			if(p <= 1) break;
			int c = GetChar(p);
			if(isrbrkt(c)) lvl++;
			if(islbrkt(c) && --lvl == 0) break;
			p--;
		}
	}
	PlaceCaret(p, sel);
}

bool isspctab(int c) {
	return c == ' ' || c == '\t';
}

void CodeEditor::DeleteWord() {
	if(IsReadOnly() || RemoveSelection()) return;
	int p = GetCursor();
	int e = GetLength();
	int c = GetChar(p);
	if(iscid(c))
		while(p < e && iscid(GetChar(p))) p++;
	else
	if(isspctab(c))
		while(p < e && isspctab(GetChar(p))) p++;
	else {
		DeleteChar();
		return;
	}
	Remove(GetCursor(), p - GetCursor());
}

void CodeEditor::DeleteWordBack() {
	if(IsReadOnly() || RemoveSelection()) return;
	int p = GetCursor();
	if(p < 1) return;
	int c = GetChar(p - 1);
	if(iscid(GetChar(p - 1)))
		while(p > 1 && iscid(GetChar(p - 1))) p--;
	else
	if(isspctab(c))
		while(p > 1 && isspctab(GetChar(p - 1))) p--;
	else {
		Backspace();
		return;
	}
	Remove(p, GetCursor() - p);
	PlaceCaret(p);
}

void CodeEditor::SetLineSelection(int l, int h) {
	SetSelection(GetPos(l), GetPos(h));
}

bool CodeEditor::GetLineSelection(int& l, int& h) {
	if(!GetSelection(l, h)) return false;
	l = GetLine(l);
	int pos = h;
	h = GetLinePos(pos);
	if(pos && h < GetLineCount()) h++;
	SetLineSelection(l, h);
	return true;
}

void CodeEditor::TabRight() {
	int l, h;
	if(!GetLineSelection(l, h)) return;
	int ll = l;
	while(l < h)
		Insert(GetPos(l++), "\t");
	SetLineSelection(ll, h);
}

void CodeEditor::TabLeft() {
	int l, h;
	if(!GetLineSelection(l, h)) return;
	int ll = l;
	while(l < h) {
		WString ln = GetWLine(l);
		int spc = 0;
		while(spc < tabsize && ln[spc] == ' ') spc++;
		if(spc < tabsize && ln[spc] == '\t') spc++;
		Remove(GetPos(l++), spc);
	}
	SetLineSelection(ll, h);
}

bool CodeEditor::GetWordPos(int pos, int& l, int& h) {
	l = h = pos;
	if(!iscid(GetChar(pos))) return false;
	while(l > 0 && iscid(GetChar(l - 1))) l--;
	while(iscid(GetChar(h))) h++;
	return true;
}

String CodeEditor::GetWord()
{
	int l, h;
	GetWordPos(cursor, l, h);
	return Get(l, h - l);
}

void CodeEditor::LeftDouble(Point p, dword keyflags) {
	int l, h;
	int pos = GetMousePos(p);
	if(GetWordPos(pos, l, h))
		SetSelection(l, h);
	else
		SetSelection(pos, pos + 1);
}

void CodeEditor::LeftDown(Point p, dword keyflags) {
	LineEdit::LeftDown(p, keyflags);
	WhenLeftDown();
}

void CodeEditor::MouseMove(Point p, dword f) {
	LineEdit::MouseMove(p, f);
	if(IsSelection()) return;
	int pos = GetMousePos(p);
	int l, h;
	if(GetWordPos(pos, l, h) || pos > 0 && GetWordPos(pos - 1, l, h))
		WhenDbgView(Get(l, h - l));
}

WString CodeEditor::GetI()
{
	int l, h;
	WString ft;
	if(GetSelection(l, h) || GetWordPos(GetCursor(), l, h)) {
		while(l < h) {
			int c = GetChar(l++);
			if(c == '\n')
				break;
			ft.Cat(c);
		}
	}
	return ft;
}

void CodeEditor::FindWord(bool back) {
	WString I = GetI();
	if(!IsNull(I))
		Find(back, I, true, false, false, false);
}

void CodeEditor::SetI(Ctrl *edit)
{
	*edit <<= GetI();
}

void CodeEditor::Goto() {
	String line = AsString(GetCursorLine());
	if(EditText(line, "Go to", "Line:"))
		SetCursor(GetPos(atoi(line) - 1));
}

void CodeEditor::Enclose(const char *c1, const char *c2)
{
	int l, h;
	if(!GetSelection(l, h))
		return;
	Insert(l, WString(c1));
	Insert(h + strlen(c1), WString(c2));
	ClearSelection();
	SetCursor(h + strlen(c1) + strlen(c2));
}

bool CodeEditor::Key(dword code, int count) {
	Time key_time = GetSysTime();
	double diff;
	if(!IsNull(last_key_time) && (diff = key_time - last_key_time) <= 3)
		stat_edit_time += diff;
	last_key_time = key_time;

	NextUndo();
	switch(code) {
	case K_CTRL_DELETE:
		DeleteWord();
		return true;
	case K_CTRL_BACKSPACE:
		DeleteWordBack();
		return true;
	case K_ENTER:
		IndentEnter(count);
		return true;
	}
	bool sel = code & K_SHIFT;
	switch(code & ~K_SHIFT) {
	case K_F3:
		Find(sel);
		return true;
	case K_CTRL_F3:
		FindWord(sel);
		return true;
	case K_CTRL_RIGHT:
		MoveNextWord(sel);
		return true;
	case K_CTRL_LEFT:
		MovePrevWord(sel);
		return true;
	case K_CTRL_RBRACKET:
		MoveNextBrk(sel);
		return true;
	case K_CTRL_LBRACKET:
		MovePrevBrk(sel);
		return true;
	case K_TAB:
		if(IsSelection()) {
			if(sel)
				TabLeft();
			else
				TabRight();
			return true;
		}
	default:
		if(IsSelection() && auto_enclose) {
			if(code == '(') {
				Enclose("(", ")");
				return true;
			}
			if(code == '{') {
				Enclose("{", "}");
				return true;
			}
			if(code == '\"') {
				Enclose("\"", "\"");
				return true;
			}
			if(code == '[') {
				Enclose("[", "]");
				return true;
			}
			if(code == '/') {
				Enclose("/*", "*/");
				return true;
			}
		}
  		if(code >= 32 && code < 128 && count == 1) {
			IndentInsert(code);
			return true;
		}
		if(code == 9 && IsSelection())
			return true;
	}
	if(GetCharset() != CHARSET_UTF8)
		if(code >= 128 && code < 65536 && FromUnicode((wchar)code, GetCharset()) == DEFAULTCHAR)
			return true;
	return LineEdit::Key(code, count);
}

void CodeEditor::ForwardWhenBreakpoint(int i) {
	WhenBreakpoint(i);
}

void CodeEditor::GotoLine(int line)
{
	SetCursor(GetPos(GetLineNo(line)));
}

void CodeEditor::Serialize(Stream& s) {
	int version = 0;
	s / version;
	SerializeFind(s);
}

void CodeEditor::SetLineInfo(const LineInfo& lf)
{
	bar.SetLineInfo(lf, GetLineCount());
}

void CodeEditor::DefaultHlStyles()
{
	SetHlStyle(INK_COMMENT, Green, false, true);
	SetHlStyle(INK_CONST_STRING, Red);

	SetHlStyle(INK_CONST_STRINGOP, Green);
	SetHlStyle(INK_CONST_INT, Red);
	SetHlStyle(INK_CONST_FLOAT, Magenta);
	SetHlStyle(INK_CONST_HEX, Blue);
	SetHlStyle(INK_CONST_OCT, Blue);

	SetHlStyle(INK_OPERATOR, LtBlue);
	SetHlStyle(INK_KEYWORD, LtBlue, true);
	SetHlStyle(INK_UPP, Cyan);
	SetHlStyle(PAPER_LNG, Color(255, 255, 224));
	SetHlStyle(INK_ERROR, LtRed);
	SetHlStyle(INK_PAR0, SBlack);
	SetHlStyle(INK_PAR1, SGreen);
	SetHlStyle(INK_PAR2, SMagenta);
	SetHlStyle(INK_PAR3, SBrown);

	SetHlStyle(PAPER_BLOCK1, Blend(LtBlue, White, 240));
	SetHlStyle(PAPER_BLOCK2, Blend(LtGreen, White, 240));
	SetHlStyle(PAPER_BLOCK3, Blend(LtYellow, White, 240));
	SetHlStyle(PAPER_BLOCK4, Blend(LtMagenta, White, 240));

	SetHlStyle(INK_MACRO, Magenta);
	SetHlStyle(PAPER_MACRO, Color(255, 255, 230));
	SetHlStyle(PAPER_IFDEF, Color(230, 255, 255));
	SetHlStyle(INK_IFDEF, Color(170, 170, 170));

	SetHlStyle(PAPER_BRACKET0, LtYellow);
	SetHlStyle(PAPER_BRACKET, Yellow);

	SetHlStyle(INK_NORMAL, SColorText);
	SetHlStyle(INK_DISABLED, SColorDisabled);
	SetHlStyle(INK_SELECTED, SColorHighlightText);
	SetHlStyle(PAPER_NORMAL, SColorPaper);
	SetHlStyle(PAPER_READONLY, SColorFace);
	SetHlStyle(PAPER_SELECTED, SColorHighlight);
}


#define HL_COLOR(x, a, b)    #x,
static char *s_hl_color[] = {
#include "hl_color.i"
};
#undef  HL_COLOR

#define HL_COLOR(a, x, b)    x,
static char *s_hl_name[] = {
#include "hl_color.i"
};
#undef  HL_COLOR

#define HL_COLOR(a, b, x)    x,
static bool s_hl_font[] = {
#include "hl_color.i"
};
#undef  HL_COLOR

const CodeEditor::HlStyle& CodeEditor::GetHlStyle(int i)
{
	return hl_style[i];
}

const char *CodeEditor::GetHlName(int i)
{
	return s_hl_name[i];
}

bool CodeEditor::HasHlFont(int i)
{
	return s_hl_font[i];
}

void  CodeEditor::SetHlStyle(int i, Color c, bool bold, bool italic, bool underline)
{
	HlStyle& st = hl_style[i];
	st.color = c;
	st.bold = bold;
	st.italic = italic;
	st.underline = underline;
	SetColor(LineEdit::INK_NORMAL, hl_style[INK_NORMAL].color);
	SetColor(LineEdit::INK_DISABLED, hl_style[INK_DISABLED].color);
	SetColor(LineEdit::INK_SELECTED, hl_style[INK_SELECTED].color);
	SetColor(LineEdit::PAPER_NORMAL, hl_style[PAPER_NORMAL].color);
	SetColor(LineEdit::PAPER_READONLY, hl_style[PAPER_READONLY].color);
	SetColor(LineEdit::PAPER_SELECTED, hl_style[PAPER_SELECTED].color);
}

void CodeEditor::LoadHlStyles(const char *s)
{
	CParser p(s);
	try {
		while(!p.IsEof()) {
			String id = p.ReadId();
			Color c = ReadColor(p);
			bool bold = false;
			bool italic = false;
			bool underline = false;
			for(;;)
				if(p.Id("bold"))
					bold = true;
				else
				if(p.Id("italic"))
					italic = true;
				else
				if(p.Id("underline"))
					underline = true;
				else
					break;
			for(int i = 0; i < HL_COUNT; i++)
				if(id == s_hl_color[i]) {
					SetHlStyle(i, c, bold, italic, underline);
					break;
				}
			p.PassChar(';');
		}
	}
	catch(CParser::Error) {
		DefaultHlStyles();
	}
}

String CodeEditor::StoreHlStyles()
{
	String r;
	for(int i = 0; i < HL_COUNT; i++) {
		const HlStyle& s = GetHlStyle(i);
		r << Format("%-25s", s_hl_color[i]) << ' ' << FormatColor(s.color);
		if(s.bold)
			r << " bold";
		if(s.italic)
			r << " italic";
		if(s.underline)
			r << " underline";
		r << ";\r\n";
	}
	return r;
}

void CodeEditor::PutI(Ctrl& edit, FrameRight<Button>& I)
{
	edit.AddFrame(I);
	I.NoWantFocus();
	I.SetMonoImage(CodeEditorImg::I()).NoWantFocus();
	I.Tip("Set word/selection (Ctrl+I)");
	I <<= THISBACK1(SetI, &edit);
}

CodeEditor::CodeEditor() {
	stat_edit_time = 0;
	last_key_time = Null;
	CtrlLayout(findreplace);
	AddFrame(bar);
	bar.SetEditor(this);
	UndoSteps(10000);
	SetFont(Courier(16));
	findreplace.find.AddFrame(findwb);
	findwb.NoWantFocus();
	findwb.SetMonoImage(CtrlImg::smallright()).NoWantFocus();
	findwb <<= THISBACK(FindWildcard);
	findreplace.replace.AddFrame(replacewb);
	replacewb.NoWantFocus();
	replacewb.SetMonoImage(CtrlImg::smallright()).NoWantFocus();
	replacewb <<= THISBACK(ReplaceWildcard);
	PutI(findreplace.find, findI);
	PutI(findreplace.replace, replaceI);
	findreplace.amend <<= THISBACK(Replace);
	findreplace.cancel.Cancel();
	findreplace.ok.Ok();
	findreplace.findback <<= THISBACK(DoFindBack);
	found = notfoundfw = notfoundbk = foundsel = false;
	bar.WhenBreakpoint = THISBACK(ForwardWhenBreakpoint);
	highlight = HIGHLIGHT_NONE;
	hilite_scope = 0;
	hilite_bracket = 2;
	hilite_ifdef = 1;
	indent_spaces = false;
	indent_amount = GetTabSize();
	no_parenthesis_indent = false;
	sb.WithSizeGrip();
	DefaultHlStyles();
	sb.y.NoAutoHide();
	sb.y.AddFrame(topsbbutton);
	sb.y.AddFrame(topsbbutton1);
	topsbbutton.Hide();
	topsbbutton1.Hide();
	highlight_bracket_pos = 10;
	SetTimeCallback(-20, THISBACK(Periodic), TIMEID_PERIODIC);
	auto_enclose = false;
}

CodeEditor::~CodeEditor() {}
