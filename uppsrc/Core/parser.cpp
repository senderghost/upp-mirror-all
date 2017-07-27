#include "Core.h"

NAMESPACE_UPP

#define LLOG(x)    // DLOG(x)
#define LTIMING(x) // RTIMING(x)

void CParser::ThrowError(const char *s) {
	LLOG("CParser::Error: " << s);
	LLOG(~String(term, min((int)strlen((const char *)term), 512)));
	Pos pos = GetPos();
	Error err(fn + Format("(%d,%d): ", line, pos.GetColumn()) + s);
//	err.term = (const char *)term;
	throw err;
}

CParser& CParser::SkipComments(bool b)
{
	skipcomments = b;
	term = wspc;
	Spaces0();
	return *this;
}

bool CParser::Spaces0() {
	LTIMING("Spaces");
	if((byte)*term > ' ' &&
	   !(term[0] == '/' && term[1] == '/') &&
	   !(term[0] == '/' && term[1] == '*'))
		return false;
	for(;;) {
		if(*term == LINEINFO_ESC) {
			term++;
			fn.Clear();
			while(*term) {
				if(*term == LINEINFO_ESC) {
					++term;
					break;
				}
				if(*term == '\3') {
					line = atoi(++term);
					while(*term) {
						if(*term == LINEINFO_ESC) {
							++term;
							break;
						}
						term++;
					}
					break;
				}
				fn.Cat(*term++);
			}
			continue;
		}
		else
		if(term[0] == '/' && term[1] == '/' && skipcomments) {
			term += 2;
			while(*term && *term != '\n')
				term++;
		}
		else
		if(term[0] == '/' && term[1] == '*' && skipcomments) {
			term += 2;
			while(*term) {
				if(term[0] == '*' && term[1] == '/') {
					term += 2;
					break;
				}
				if(*term++ == '\n') line++;
			}
		}
		if(!*term) break;
		if((byte)*term > ' ') break;
		if(*term == '\n') {
			line++;
			lineptr = term + 1;
		}
		term++;
	}
	return true;
}

String CParser::LineInfoComment(const String& file, int line, int column)
{
	return String().Cat() << (char)LINEINFO_ESC << file << '\3'
	                      << line << '\3' << column << (char)LINEINFO_ESC;
}

String CParser::GetLineInfoComment(int tabsize) const
{
	return LineInfoComment(GetFileName(), GetLine(), GetColumn(tabsize));
}

const char *CParser::IsId0(const char *s) const {
	const char *t = term + 1;
	s++;
	while(*s) {
		if(*t != *s)
			return NULL;
		t++;
		s++;
	}
	return IsAlNum(*t) || *t == '_' ? NULL : t;
}

bool CParser::Id0(const char *s) {
	LTIMING("Id");
	const char *t = IsId0(s);
	if(!t)
		return false;
	term = t;
	DoSpaces();
	return true;
}

void CParser::PassId(const char *s) throw(Error) {
	LTIMING("PassId");
	if(!Id(s))
		ThrowError(String("missing '") + s + "\'");
}

void CParser::PassChar(char c) throw(Error) {
	LTIMING("PassChar");
	if(!Char(c))
		ThrowError(String("missing '") + c + "\'");
}

void CParser::PassChar2(char c1, char c2) throw(Error) {
	LTIMING("PassChar2");
	if(!Char2(c1, c2))
		ThrowError(String("missing '") + c1 + c2 + "\'");
}

void CParser::PassChar3(char c1, char c2, char c3) throw(Error) {
	LTIMING("PassChar3");
	if(!Char3(c1, c2, c3))
		ThrowError(String("missing '") + c1 + c2 + c3 + "\'");
}

String CParser::ReadId() throw(Error) {
	LTIMING("ReadId");
	if(!IsId())
		ThrowError("missing id");
	String result;
	const char *b = term;
	const char *p = b;
	while(iscid(*p))
		p++;
	term = p;
	DoSpaces();
	return String(b, (int)(uintptr_t)(p - b));
}

String CParser::ReadIdt() throw(Error) {
	if(!IsId())
		ThrowError("missing id");
	StringBuffer result;
	int lvl = 0;
	while(IsAlNum(*term) || *term == '_' || *term == '<' || *term == '>' ||
	      *term == ':' || (*term == ',' || *term == ' ' ) && lvl > 0 ) {
		if(*term == '<') lvl++;
		if(*term == '>') lvl--;
		result.Cat(*term++);
	}
	DoSpaces();
	return result;
}

bool CParser::IsInt() const {
	LTIMING("IsInt");
	const char *t = term;
	if(*t == '-' || *t == '+') {
		t++;
		while(*t <= ' ')
			t++;
	}
	return IsDigit(*t);
}

int  CParser::Sgn()
{
	int sign = 1;
	if(*term == '-') {
		sign = -1;
		term++;
	}
	else
	if(*term == '+')
		term++;
	Spaces();
	return sign;
}

int  CParser::ReadInt() throw(Error) {
	LTIMING("ReadInt");
	int sign = Sgn();
	uint32 n = ReadNumber(10);
	if(sign > 0 ? n > INT_MAX : n > (uint32)INT_MAX + 1)
		ThrowError("number is too big");
	return sign * (int)n;
}

int CParser::ReadInt(int min, int max) throw(Error)
{
	int n = ReadInt();
	if(n < min || n > max)
		ThrowError("number is out of range");
	return n;
}

int64 CParser::ReadInt64() throw(Error)
{
	LTIMING("ReadInt64");
	int sign = Sgn();
	uint64 n = ReadNumber64(10);
	if(sign > 0 ? n > INT64_MAX : n > (uint64)INT64_MAX + 1)
		ThrowError("number is too big");
	return sign * n;
}

int64 CParser::ReadInt64(int64 min, int64 max) throw(Error)
{
	int64 n = ReadInt64();
	if(n < min || n > max)
		ThrowError("number is out of range");
	return n;
}

bool CParser::IsNumber(int base) const
{
	if(IsDigit(*term))
		return true;
	int q = ToUpper(*term) - 'A';
	return q >= 0 && q < base - 10;
}

uint32  CParser::ReadNumber(int base) throw(Error)
{
	LTIMING("ReadNumber");
	uint32 n = 0;
	int q = ctoi(*term);
	if(q < 0 || q >= base)
		ThrowError("missing number");
	for(;;) {
		int c = ctoi(*term);
		if(c < 0 || c >= base)
			break;
		uint32 n1 = n;
		n = base * n + c;
		if(n1 > n)
			ThrowError("number is too big");
		term++;
	}
	DoSpaces();
	return n;
}

uint64  CParser::ReadNumber64(int base) throw(Error)
{
	LTIMING("ReadNumber");
	uint64 n = 0;
	int q = ctoi(*term);
	if(q < 0 || q >= base)
		ThrowError("missing number");
	for(;;) {
		int c = ctoi(*term);
		if(c < 0 || c >= base)
			break;
		uint64 n1 = n;
		n = base * n + c;
		if(n1 > n)
			ThrowError("number is too big");
		term++;
	}
	DoSpaces();
	return n;
}

double CParser::ReadDouble() throw(Error)
{
	LTIMING("ReadDouble");
	int sign = Sgn();
	if(!IsDigit(*term) && *term != '.')
		ThrowError("missing number");
	double n = 0;
	while(IsDigit(*term))
		n = 10 * n + *term++ - '0';
	if(Char('.')) {
		double q = 1;
		while(IsDigit(*term)) {
			q = q / 10;
			n += q * (*term++ - '0');
		}
	}
	if(Char('e') || Char('E'))
		n *= pow(10.0, ReadInt());
	DoSpaces();
	n = sign * n;
	if(!IsFin(n))
		ThrowError("number is too big");
	return n;
}

dword CParser::ReadHex()
{
	int hex = 0;
	while(IsXDigit(*++term))
		hex = (hex << 4) + ctoi(*term);
	return hex;
}

bool CParser::ReadHex(dword& hex, int n)
{
	hex = 0;
	while(n--) {
		if(!IsXDigit(*++term))
			return false;
		hex = (hex << 4) + ctoi(*term);
	}
	term++;
	return true;
}

void CatUtf8(StringBuffer& result, dword codepoint)
{
	if(codepoint < 0x80)
		result.Cat((char)codepoint);
	else
	if(codepoint < 0x800) {
		result.Cat(0xc0 | byte(codepoint >> 6));
		result.Cat(0x80 | byte(codepoint & 0x3f));
	}
	else
	if((codepoint & 0xFFFFFF00) == 0xEE00) // ERROR ESCAPE
		result.Cat((char) codepoint);
	else
	if(codepoint < 0x10000) {
		result.Cat(0xe0 | byte(codepoint >> 12));
		result.Cat(0x80 | byte((codepoint >> 6) & 0x3f));
		result.Cat(0x80 | byte(codepoint & 0x3f));
	}
	else
	if(codepoint < 0x110000) {
		result.Cat(0xf0 | byte(codepoint >> 18));
		result.Cat(0x80 | byte((codepoint >> 12) & 0x3f));
		result.Cat(0x80 | byte((codepoint >> 6) & 0x3f));
		result.Cat(0x80 | byte(codepoint & 0x3f));
	}
}

String CParser::ReadOneString(int delim, bool chkend) throw(Error) {
	if(!IsChar(delim))
		ThrowError("missing string");
	term++;
	StringBuffer result;
	for(;;) {
		if(*term == delim) {
			term++;
			DoSpaces();
			return result;
		}
		else
		if(*term == '\\') {
			switch(*++term) {
			case 'a': result.Cat('\a'); term++; break;
			case 'b': result.Cat('\b'); term++; break;
			case 't': result.Cat('\t'); term++; break;
			case 'v': result.Cat('\v'); term++; break;
			case 'n': result.Cat('\n'); term++; break;
			case 'r': result.Cat('\r'); term++; break;
			case 'f': result.Cat('\f'); term++; break;
			case 'x': {
				int hex = ReadHex();
				result.Cat(hex);
				break;
			}
			case 'u':
				if(uescape) {
					dword hex;
					if(!ReadHex(hex, 4))
						ThrowError("Incomplete universal character");
					if(hex >= 0xD800 && hex < 0xDBFF) {
						if(term[0] == '\\' && term[1] == 'u') {
							term++;
							dword hex2;
							if(!ReadHex(hex2, 4))
								ThrowError("Incomplete universal character");
							if(hex2 >= 0xDC00 && hex2 <= 0xDFFF) {
								CatUtf8(result, ((hex & 0x3ff) << 10) | (hex2 & 0x3ff) + 0x10000);
								break;
							}
						}
						ThrowError("Invalid UTF-16 surrogate pair");
					}
					else
						result.Cat(ToUtf8((wchar)hex));
				}
				else
					result.Cat(*term++);
				break;
			case 'U':
				if(uescape) {
					dword hex;
					if(!ReadHex(hex, 8))
						ThrowError("Incomplete universal character");
					if(hex > 0x10ffff)
						ThrowError("Universal character is out of unicode range");
					CatUtf8(result, hex);
				}
				else
					result.Cat(*term++);
				break;
			default:
				if(*term >= '0' && *term <= '7') {
					int oct = *term++ - '0';
					if(*term >= '0' && *term <= '7')
						oct = 8 * oct + *term++ - '0';
					if(*term >= '0' && *term <= '7')
						oct = 8 * oct + *term++ - '0';
					result.Cat(oct);
				}
				else
					result.Cat(*term++);
				break;
			}
		}
		else {
			if((byte)*term < ' ' && *term != '\t') {
				if(chkend) {
					ThrowError("Unterminated string");
					return result;
				}
				if(*term == '\0')
					return result;
			}
			result.Cat(*term++);
		}
	}
	DoSpaces();
	return result;
}

String CParser::ReadOneString(bool chkend) throw(Error)
{
	return ReadOneString('\"', chkend);
}

String CParser::ReadString(int delim, bool chkend) throw(Error) {
	LTIMING("ReadString");
	String result;
	do
		result.Cat(ReadOneString(delim, chkend));
	while(IsChar(delim));
	return result;
}

String CParser::ReadString(bool chkend) throw(Error)
{
	return ReadString('\"', chkend);
}

char CParser::GetChar()
{
	char c = *term++;
	if(c == '\n')
		line++;
	return c;
}

void CParser::SkipTerm()
{
	LTIMING("SkipTerm");
	if(IsId())
		while(iscid(*term))
			term++;
	else
	if(IsNumber())
		while(IsDigit(*term))
			term++;
	else
	if(IsString())
		ReadString();
	else
	if(IsChar('\''))
		ReadString('\'', false);
	else		
	if(*term) {
		if(*term == '\n')
			line++;
		term++;
	}
	DoSpaces();
}

CParser::Pos CParser::GetPos() const
{
	Pos p;
	p.line = line;
	p.fn = fn;
	p.ptr = term;
	p.wspc = wspc;
	p.lineptr = lineptr;
	return p;
}

int CParser::Pos::GetColumn(int tabsize) const
{
	int pos = 1;
	for(const char *s = lineptr; s < ptr; s++) {
		if(*s == CParser::LINEINFO_ESC) {
			s++;
			while(s < ptr && *s != CParser::LINEINFO_ESC)
				if(*s++ == '\3')
					pos = atoi(s);
		}
		else
		if(*s == '\t')
			pos = (pos + tabsize - 1) / tabsize * tabsize + 1;
		else
			pos++;
	}
	return pos;
}

int CParser::GetColumn(int tabsize) const
{
	return GetPos().GetColumn(tabsize);
}

void CParser::SetPos(const CParser::Pos& p)
{
	LLOG("SetPos " << p.fn << ":" << p.line);
	line = p.line;
	fn = p.fn;
	term = p.ptr;
	wspc = p.wspc;
	lineptr = p.lineptr;
	if(skipspaces)
		DoSpaces();
}

CParser::CParser(const char *ptr)
: term(ptr), wspc(ptr), lineptr(ptr)
{
	line = 1;
	skipspaces = skipcomments = true;
	uescape = true;
	Spaces();
}

CParser::CParser(const char *ptr, const char *fn, int line)
: term(ptr), wspc(ptr), lineptr(ptr), line(line), fn(fn)
{
	skipspaces = skipcomments = true;
	uescape = true;
	Spaces();
}

CParser::CParser()
{
	term = lineptr = wspc = NULL;
	line = 0;
	skipspaces = true;
	uescape = true;
}

void CParser::Set(const char *_ptr, const char *_fn, int _line)
{
	term = lineptr = wspc = _ptr;
	fn = _fn;
	line = _line;
	if(skipspaces)
		Spaces();
	LLOG("Set " << fn << ":" << line);
}

void CParser::Set(const char *_ptr)
{
	Set(_ptr, "", 1);
}

inline void NextCStringLine(StringBuffer& t, const char *linepfx, int& pl)
{
	t << "\"\r\n" << (linepfx ? linepfx : "") << "\"";
	pl = t.GetLength();
}

inline int HexDigit(int c)
{
	return "0123456789ABCDEF"[c & 15];
}

static inline void sCatHex(StringBuffer& t, word q)
{
	char h[6];
	h[0] = '\\';
	h[1] = 'u';
	h[2] = HexDigit(q >> 12);
	h[3] = HexDigit(q >> 8);
	h[4] = HexDigit(q >> 4);
	h[5] = HexDigit(q);
	t.Cat(h, 6);
}

force_inline dword FetchUtf8(const char *&_s, const char *_lim)
{
	const byte *s = (const byte *)_s;
	const byte *lim = (const byte *)_lim;
	dword code = *s;
	if(code < 0x80) {
		_s++;
		return *s;
	}
	else
	if(code >= 0xC2) {
		dword c;
		if(code < 0xE0 && s + 1 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 &&
		   (c = ((code - 0xC0) << 6) + s[1] - 0x80) >= 0x80 && c < 0x800) {
			_s += 2;
			return c;
		}
		else
		if(code < 0xF0 && s + 2 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 && s[2] >= 0x80 && s[2] < 0xc0 &&
		   (c = ((code - 0xE0) << 12) + ((s[1] - 0x80) << 6) + s[2] - 0x80) >= 0x800 &&
		   !(c >= 0xEE00 && c <= 0xEEFF)) {
			_s += 3;
			return c;
		}
		else
		if(code < 0xF8 && s + 3 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 && s[2] >= 0x80 && s[2] < 0xc0 && s[3] >= 0x80 && s[3] < 0xc0 &&
		   (c = ((code - 0xF0) << 18) + ((s[1] - 0x80) << 12) + ((s[2] - 0x80) << 6) + s[3] - 0x80) >= 0x10000 &&
		   c < 0x110000) {
			_s += 4;
			return c;
		}
	}
	_s++;
	return 0xEE00 + code; // ERROR ESCAPE
}

String AsCString(const char *s, const char *lim, int linemax, const char *linepfx, dword flags)
{
	StringBuffer t;
	t.Cat('\"');
	int pl = 0;
	bool wasspace = false;
	byte cs = GetDefaultCharset();
	bool toutf8 = GetDefaultCharset() != CHARSET_UTF8;
	while(s < lim) {
		if(t.GetLength() - pl > linemax && (!(flags & ASCSTRING_SMART) || wasspace))
			NextCStringLine(t, linepfx, pl);
		wasspace = *s == ' ';
		switch(*s) {
		case '\a': t.Cat("\\a"); break;
		case '\b': t.Cat("\\b"); break;
		case '\f': t.Cat("\\f"); break;
		case '\t': t.Cat("\\t"); break;
		case '\v': t.Cat("\\v"); break;
		case '\r': t.Cat("\\r"); break;
		case '\"': t.Cat("\\\""); break;
		case '\\': t.Cat("\\\\"); break;
		case '\n': t.Cat("\\n"); wasspace = true; break;
		default:
			if(flags & ASCSTRING_JSON) {
				if((byte)*s < 32) {
					sCatHex(t, (byte)*s++);
				}
				else
				if((byte)*s >= 0x7f) {
					const char *s0 = s;
					dword c = toutf8 ? ToUnicode((byte)*s++, cs) : FetchUtf8(s, lim);
					if(c < 0x10000)
						t.Cat(s0, s);
					else {
						c -= 0x10000;
						sCatHex(t, wchar(0xD800 + (0x3ff & (c >> 10))));
						sCatHex(t, wchar(0xDC00 + (0x3ff & c)));
					}
				}
				else
					t.Cat(*s++);
				continue; // skip s++
			}
			else {
				if(byte(*s) < 32 || (byte)*s >= 0x7f && (flags & ASCSTRING_OCTALHI) || (byte)*s == 0xff || (byte)*s == 0x7f) {
					char h[4];
					int q = (byte)*s;
					h[0] = '\\';
					h[1] = (3 & (q >> 6)) + '0';
					h[2] = (7 & (q >> 3)) + '0';
					h[3] = (7 & q) + '0';
					t.Cat(h, 4);
				}
				else
					t.Cat(*s);
			}
			break;
		}
		s++;
	}
	t.Cat('\"');
	return t;
}

String AsCString(const char *s, int linemax, const char *linepfx, dword flags)
{
	return AsCString(s, s + strlen(s), linemax, linepfx, flags);
}

String AsCString(const String& s, int linemax, const char *linepfx, dword flags)
{
	return AsCString(s, s.End(), linemax, linepfx, flags);
}

END_UPP_NAMESPACE
