#include "Core.h"

#ifdef PLATFORM_WIN32
typedef VectorMap<int, LCID> LCIDMap;
GLOBAL_VAR(LCIDMap, GetLCIDMap)

String GetLocaleInfoA(LCID lcid, LCTYPE lctype)
{
	char cbuf[1000];
	GetLocaleInfoA(lcid, lctype, cbuf, __countof(cbuf));
	return cbuf;
}

WString GetLocaleInfoW(LCID lcid, LCTYPE lctype)
{
	union {
		wchar wbuf[1000];
		char abuf[1000];
	};
	Zero(wbuf);
	if(GetLocaleInfoW(lcid, lctype, (WCHAR *)wbuf, __countof(wbuf)))
		return wbuf;
	GetLocaleInfoA(lcid, lctype, abuf, __countof(abuf));
	return ToUnicode(abuf, CHARSET_DEFAULT);
}

static BOOL CALLBACK sEnumLocale(char *locale_string)
{
	LLOG(locale_string);
	LCID lcid = stou(locale_string, NULL, 16);
	char buffer[10];
	GetLocaleInfo(lcid, LOCALE_SISO639LANGNAME, buffer, 10);
	int language = (ToUpper(buffer[0]) << 24) + (ToUpper(buffer[1]) << 16);
	GetLocaleInfo(lcid, LOCALE_SISO3166CTRYNAME, buffer, 10);
	language += (ToUpper(buffer[0]) << 8) + (ToUpper(buffer[1]) << 0);
	LLOG(FormatIntHex(language, 8) << ", " << LNGAsText(language) << "->" << FormatIntHex(lcid, 8));
	GetLCIDMap().GetAdd(language, lcid);
	return TRUE;
}

LCID GetLanguageLCID(int language)
{
	if(language == 0)
		return 0x400;
	if(GetLCIDMap().IsEmpty())
		EnumSystemLocales(&sEnumLocale, LCID_SUPPORTED);
	return GetLCIDMap().Get(language, MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT));
}
#endif

String GetLangName(int language)
{
	return GetLanguageInfo(language).english_name;
}
*/
String GetNativeLangName(int language) {
	return GetLanguageInfo(language).native_name.ToString();
/*
	char buffer[200];
	return GetLocaleInfo(MAKELCID(language, SORT_DEFAULT), LOCALE_SNATIVELANGNAME, buffer, 200)
	       ? buffer : ~GetLangName(language);
*/
}

LanguageInfo::LanguageInfo(int lang_)
: language(lang_)
{
	charset = CHARSET_DEFAULT;

#ifdef PLATFORM_WIN32
	LCID lcid = GetLanguageLCID(lang_);
	english_name = GetLocaleInfoA(lcid, LOCALE_SENGLANGUAGE);
	native_name = GetLocaleInfoW(lcid, LOCALE_SNATIVELANGNAME);
	thousand_separator = GetLocaleInfoA(lcid, LOCALE_STHOUSAND);
	decimal_point = GetLocaleInfoA(lcid, LOCALE_SDECIMAL);
	static const LCTYPE months[] =
	{
		LOCALE_SMONTHNAME1,  LOCALE_SMONTHNAME2,  LOCALE_SMONTHNAME3,
		LOCALE_SMONTHNAME4,  LOCALE_SMONTHNAME5,  LOCALE_SMONTHNAME6,
		LOCALE_SMONTHNAME7,  LOCALE_SMONTHNAME8,  LOCALE_SMONTHNAME9,
		LOCALE_SMONTHNAME10, LOCALE_SMONTHNAME11, LOCALE_SMONTHNAME12,
	};
	static const LCTYPE smonths[] =
	{
		LOCALE_SABBREVMONTHNAME1,  LOCALE_SABBREVMONTHNAME2,  LOCALE_SABBREVMONTHNAME3,
		LOCALE_SABBREVMONTHNAME4,  LOCALE_SABBREVMONTHNAME5,  LOCALE_SABBREVMONTHNAME6,
		LOCALE_SABBREVMONTHNAME7,  LOCALE_SABBREVMONTHNAME8,  LOCALE_SABBREVMONTHNAME9,
		LOCALE_SABBREVMONTHNAME10, LOCALE_SABBREVMONTHNAME11, LOCALE_SABBREVMONTHNAME12,
	};
	ASSERT(__countof(months) == __countof(month_names));
	int i;
	for(i = 0; i < __countof(months); i++)
	{
		month_names[i] = GetLocaleInfoW(lcid, months[i]);
		short_month_names[i] = GetLocaleInfoW(lcid, smonths[i]);
	}
	static const LCTYPE days[] =
	{
		LOCALE_SDAYNAME1, LOCALE_SDAYNAME2, LOCALE_SDAYNAME3, LOCALE_SDAYNAME4,
		LOCALE_SDAYNAME5, LOCALE_SDAYNAME6, LOCALE_SDAYNAME7,
	};
	static const LCTYPE sdays[] =
	{
		LOCALE_SABBREVDAYNAME1, LOCALE_SABBREVDAYNAME2, LOCALE_SABBREVDAYNAME3, LOCALE_SABBREVDAYNAME4,
		LOCALE_SABBREVDAYNAME5, LOCALE_SABBREVDAYNAME6, LOCALE_SABBREVDAYNAME7,
	};
	ASSERT(__countof(days) == __countof(day_names));
	for(i = 0; i < __countof(days); i++)
	{
		day_names[i] = GetLocaleInfoW(lcid, days[i]);
		short_day_names[i] = GetLocaleInfoW(lcid, sdays[i]);
	}

	static struct { byte charset; dword codepage; } tab[] =
	{
		{ CHARSET_WIN1252,    1252 },
		{ CHARSET_WIN1251,    1251 },
		{ CHARSET_WIN1250,    1250 },
		{ CHARSET_WIN1253,    1253 },
		{ CHARSET_WIN1254,    1254 },
		{ CHARSET_WIN1257,    1257 },
		{ CHARSET_WIN1255,    1255 },
		{ CHARSET_WIN1256,    1256 },
//		{ SHIFTJIS_CHARSET,    932 },
//		{ HANGEUL_CHARSET,     949 },
//		{ GB2312_CHARSET,      936 },
//		{ CHINESEBIG5_CHARSET, 950 },
	};
	int codepage = atoi(GetLocaleInfoA(lcid, LOCALE_IDEFAULTANSICODEPAGE));
	for(i = 0; i < __countof(tab); i++)
		if(tab[i].codepage == codepage)
		{
			charset = tab[i].charset;
			break;
		}
#endif

#ifdef PLATFORM_POSIX
	String langtext = LNGAsText(language);
	char ltext[6];
	ltext[0] = ToLower(langtext[0]);
	ltext[1] = ToLower(langtext[1]);
	ltext[2] = '_';
	ltext[3] = ToUpper(langtext[3]);
	ltext[4] = ToUpper(langtext[4]);
	ltext[5] = 0;
	String oldloc = setlocale(LC_ALL, NULL);
//	puts(String() << "setting locale " << ltext << ", old locale = " << oldloc);
	if(setlocale(LC_ALL, ltext))
	{
//		puts(String() << "set locale " << ltext << " succeeded");
		const struct lconv *lc = localeconv();
		decimal_point = lc->decimal_point;
		thousand_separator = lc->thousands_sep;
		//lc->grouping - controls thousands grouping
		static const int months[] =
		{
			MON_1, MON_2, MON_3, MON_4, MON_5, MON_6, MON_7, MON_8, MON_9, MON_10, MON_11, MON_12,
		};
		static const int smonths[] =
		{
			ABMON_1, ABMON_2, ABMON_3, ABMON_4, ABMON_5, ABMON_6, ABMON_7, ABMON_8, ABMON_9, ABMON_10, ABMON_11, ABMON_12,
		};
		ASSERT(__countof(months) == __countof(month_names) && __countof(smonths) == __countof(month_names));
		int i;
		for(i = 0; i < __countof(months); i++)
		{
			month_names[i] = nl_langinfo(months[i]);
			short_month_names[i] = nl_langinfo(smonths[i]);
		}
		static const int days[] =
		{ // Linux locale starts with Sunday
			DAY_2, DAY_3, DAY_4, DAY_5, DAY_6, DAY_7, DAY_1,
		};
		static const int sdays[] =
		{
			ABDAY_2, ABDAY_3, ABDAY_4, ABDAY_5, ABDAY_6, ABDAY_7, ABDAY_1,
		};
		ASSERT(__countof(days) == __countof(day_names) && __countof(sdays) == __countof(day_names));
		for(i = 0; i < __countof(days); i++)
		{
			day_names[i] = nl_langinfo(days[i]);
			short_day_names[i] = nl_langinfo(sdays[i]);
		}

		setlocale(LC_ALL, oldloc);
	}
#endif
}

String LanguageInfo::ToString() const
{
	String out;
	out << "LANGUAGE={" << LNGAsText(language) << "}\n"
#ifdef PLATFORM_WIN32
		<< NFormat("LCID={%08x}\n", (int)GetLanguageLCID(language))
#endif
		<< "ENGLISH_NAME={" << english_name << "}\n"
		"NATIVE_NAME={" << FromUnicode(native_name) << "}\n"
		"CHARSET={" << charset << "}\n"
		"THOUSAND_SEPARATOR={" << thousand_separator << "}\n"
		"DECIMAL_POINT={" << decimal_point << "}\n"
		"MONTH_NAMES={\n";
	int i;
	for(i = 0; i < __countof(month_names); i++)
		out << "    {" << FromUnicode(month_names[i]) << "} / {" << FromUnicode(short_month_names[i]) << "}\n";
	out << "}\n"
		"DAY_NAMES={\n";
	for(i = 0; i < __countof(day_names); i++)
		out << "    {" << FromUnicode(day_names[i]) << "} / {" << FromUnicode(short_day_names[i]) << "}\n";
	out << "}\n";
	return out;
}

static const char *NlsFindDigits(const char *src, String& dest)
{
	if(*src && !IsDigit(*src))
	{
		const char *start = src;
		while(*++src && !IsDigit(*src))
			;
		dest.Cat(start, src - start);
	}
	return src;
}

static const char *NlsCopyDigits(const char *src, String& dest, String thousands)
{
	if(IsDigit(*(src = NlsFindDigits(src, dest))))
	{
		const char *p = src;
		while(IsDigit(*++src))
			;
		int first = (src - p + 2) % 3 + 1;
		while(p < src)
		{
			dest.Cat(p, first);
			if((p += first) < src)
			{
				dest.Cat(thousands);
				first = 3;
			}
		}
	}
	return src;
}

static String NlsFormatRaw(const char *n, String thousands, String decimals)
{
	if(*n == 0)
		return Null;
//	puts(String() << "NlsFormatRaw, n = <" << n << ">, thousands <" << thousands << ">, decimal <" << decimals << ">");
	String result;
	n = NlsCopyDigits(n, result, thousands);
	if(*n == (wchar)'.')
	{ // decimal separator
		n++;
		result.Cat(decimals);
		const char *s = n;
		while(IsDigit(*n))
			n++;
		result.Cat(s, n - s);
	}
	if(*(n = NlsCopyDigits(n, result, thousands)))
		result.Cat(n);
	return result;
}

String LanguageInfo::FormatInt(int value) const
{
	if(IsNull(value))
		return Null;
	String dest;
	String is = ::FormatInt(value);
	const char *p = NlsCopyDigits(is, dest, thousand_separator);
	if(*p)
		dest.Cat(p);
	return dest;
}

String LanguageInfo::FormatDouble(double value, int digits, int FD_flags, int fill_exp) const
{
	if(IsNull(value))
		return Null;
//	puts(String() << "LanguageInfo(" << LNGAsText(language) << "): thousands <" << thousand_separator << ">, decimal <" << decimal_point << ">");
	return NlsFormatRaw(::FormatDouble(value, digits, FD_flags, fill_exp), thousand_separator, decimal_point);
}

String LanguageInfo::FormatDate(Date date) const
{
	return ::FormatDate(date, date_format, language);
}

String LanguageInfo::FormatTime(Time time) const
{
	return ::FormatTime(time, time_format, language);
}

/*
int LanguageInfo::ScanInt(const char *text, const char **endptr) const
{
	return ScanInt(text, endptr); //!! todo
}
*/

/*
double LanguageInfo::ScanDouble(const char *text, const char **endptr) const
{
	return ScanDouble(text, endptr); //!! todo
}
*/

/*
Date LanguageInfo::ScanDate(const char *text, const char **endptr, Date base_date) const
{
	return ::ScanDate(text, endptr, date_format, language, base_date);
}
*/

/*
Time LanguageInfo::ScanTime(const char *text, const char **endptr, Time base_time) const
{
	return ::ScanTime(text, endptr, time_format, language, base_time);
}
*/

WString LanguageInfo::GetIndexLetter(const wchar *text) const
{
	return IsLetter(*text) ? WString(text, 1) : WString(Null);
}

static int LangCompareDigits(const wchar *&a, const wchar *&b, const wchar *e1, const wchar *e2)
{
	const wchar *p1 = a, *p2 = b;
	while(p1 < e1 && *p1 == '0')
		p1++;
	while(p2 < e2 && *p2 == '0')
		p2++;
	const wchar *x1 = p1, *x2 = p2;
	while(p1 < e1 && IsDigit(*p1))
		p1++;
	while(p2 < e2 && IsDigit(*p2))
		p2++;
	if(p1 - x1 != p2 - x2)
		return cmp(p1 - x1, p2 - x2);
	for(; x1 != p1; x1++, x2++)
		if(*x1 != *x2)
			return *x1 > *x2 ? 1 : -1;
	a = p1;
	b = p2;
	return 0;
}

int LanguageInfo::Compare(const wchar *a, const wchar *b, int a_length, int b_length) const
{
	ASSERT(language != LNG_CZECH); // use RegisterLanguageInfoCS to register true czech compare

	int  little = 0, middle = 0;
	const wchar *p1 = a, *e1 = a + a_length, *p2 = b, *e2 = b + b_length;

	while(p1 < e1 && p2 < e2)
	{
		wchar c1 = *p1++;
		wchar c2 = *p2++;

		int level1 = (IsLetter(c1) ? 3 : IsDigit(c1) ? 2 : c1 == ' ' ? 0 : 1);
		int level2 = (IsLetter(c2) ? 3 : IsDigit(c2) ? 2 : c2 == ' ' ? 0 : 1);
		if(level1 != level2)
			return cmp(level1, level2);
		if(level1 <= 1)
		{
			if(c1 != c2)
				return cmp(c1, c2);
			continue;
		}
		if(level1 == 2)
		{ // digits
			const wchar *dp1 = --p1, *dp2 = --p2;
			int res = LangCompareDigits(dp1, dp2, e1, e2);
			if(res)
				return res;
			p1 = dp1;
			p2 = dp2;
			continue;
		}

		int u1, u2, i1, i2;

		i1 = ToAscii(u1 = ToUpper(c1));
		i2 = ToAscii(u2 = ToUpper(c2));

		if(i1 != i2)
			return i1 >= i2 ? 1 : -1;

		if(u1 != u2) // different diacritics
			if(middle == 0)
				middle = u1 - u2;

		if(c1 != c2) // different case
		{
			if(little == 0)
				little = (u1 != c1) - (u2 != c2);
		}
	}
	little += 4 * middle;
	if(little == 0)
		little = a_length - b_length;
	return sgn(little);
}

static bool ContainsAccents(const wchar *s)
{
	for(; *s; s++)
		if(*s != ToAscii(*s))
			return true;
	return false;
}

class DefaultWildcardCompare : public LanguageInfo::WildcardCompare
{
public:
	DefaultWildcardCompare(const wchar *templ)
	{
		raw_templ = 0;
//		cvt_ascii = true;
		if(*templ == 0)
			return;
//		if((*templ == '.' && templ[1] != 0 && *++templ != '.') || ContainsAccents(templ))
//			cvt_ascii = true;
		raw_templ = templ;
//		if(cvt_ascii)
//			cvt_templ = ToUpper(ToAscii(raw_templ));
//		else
			cvt_templ = ToUpper(raw_templ);
	}

	virtual bool Matches(const wchar *s) const
	{
		return !raw_templ || RawMatches(s, cvt_templ);
	}

private:
	bool RawMatches(const wchar *s, const wchar *templ) const
	{
		for(;;)
			switch(*templ++)
			{
			case 0: return true;
			case '.': if(*templ == 0) return *s == 0; // force end of string
			case '?': if(*s++ == 0) return false; break;
			case '*':
				do
					if(RawMatches(s, templ))
						return true;
				while(*s++);
				return false;
			case '\\':
				if(*templ == 0 || *s++ != *templ++)
					return false;
				break;

			default:
//				if(templ[-1] != ToUpper(cvt_ascii ? ToAscii(*s) : *s))
				if(templ[-1] != ToUpper(*s))
					return false;
				s++;
				break;
			}
		return true;
	}

private:
	const wchar *raw_templ;
//	bool         cvt_ascii;
	WString      cvt_templ;
};

One<LanguageInfo::WildcardCompare> LanguageInfo::GetWildcardCompare(const wchar *wildcard_text) const
{
	return new DefaultWildcardCompare(wildcard_text);
}

typedef ArrayMap<int, LanguageInfo> LanguageInfoMap;
GLOBAL_VAR(LanguageInfoMap, LanguageInfo::Map)

void LanguageInfo::Register(One<LanguageInfo> info)
{
	int lang = info->language;
	int f = Map().Find(lang);
	if(f >= 0)
		Map().Set(f, -info);
	else
		Map().Add(lang, -info);
}

class LanguageInfoCS : public LanguageInfo
{
public:
	LanguageInfoCS();

	virtual WString GetIndexLetter(const wchar *text) const;

	virtual int     Compare(const wchar *a, const wchar *b, int a_length, int b_length) const;
	virtual One<WildcardCompare> GetWildcardCompare(const wchar *wildcard_text) const;

public:
};

LanguageInfoCS::LanguageInfoCS()
: LanguageInfo(LNG_CZECH)
{
	english_name = "Czech";
	native_name = ToUnicode("�esky", CHARSET_WIN1250); // __FILE__CHARSET__
//	charset = CHARSET_WIN1250;
//	thousand_separator = L" ";
//	decimal_point = L",";
}

WString LanguageInfoCS::GetIndexLetter(const wchar *s) const
{
	wchar temp[3];
	temp[0] = temp[1] = temp[2] = 0;
	if(*s <= 2047 && IsLetter(*s)) // IsLetter
	{
		temp[0] = ToUpper(*s);
		if(s[1] <= 2047 && IsLetter(s[1]))
			temp[1] = ToLower(s[1]);
		if(temp[0] != 'C' || temp[1] != 'h')
			temp[1] = 0;
		switch(ToUpper(ToAscii(*s)))
		{
		case 'A': case 'E': case 'I': case 'N':
		case 'O': case 'T': case 'U': case 'Y':
			temp[0] = ToAscii(temp[0]);
			break;
		}
	}
	return temp;
}

int LanguageInfoCS::Compare(const wchar *a, const wchar *b, int a_length, int b_length) const
{
	int  little = 0, middle = 0;
	const wchar *p1 = a, *e1 = a + a_length, *p2 = b, *e2 = b + b_length;

	while(p1 < e1 && p2 < e2)
	{
		wchar c1 = *p1++;
		wchar c2 = *p2++;

		int level1 = (IsLetter(c1) ? 3 : IsDigit(c1) ? 2 : c1 == ' ' ? 0 : 1);
		int level2 = (IsLetter(c2) ? 3 : IsDigit(c2) ? 2 : c2 == ' ' ? 0 : 1);
		if(level1 != level2)
			return cmp(level1, level2);
		if(level1 <= 1)
		{
			if(c1 != c2)
				return cmp(c1, c2);
			continue;
		}
		if(level1 == 2)
		{ // digits
			const wchar *dp1 = --p1, *dp2 = --p2;
			int res = LangCompareDigits(dp1, dp2, e1, e2);
			if(res)
				return res;
			p1 = dp1;
			p2 = dp2;
			continue;
		}

		int u1, u2, i1, i2;

		if((c1 == 'C' || c1 == 'c') && (p1 < e1 && (*p1 == 'H' || *p1 == 'h')))
		{ // CH
			i1 = 'H';
			u1 = 65535;
			p1++;
		}
		else
			i1 = ToAscii(u1 = ToUpper(c1));
		if((c2 == 'C' || c2 == 'c') && (p2 < e2 && (*p2 == 'H' || *p2 == 'h')))
		{ // CH
			i2 = 'H';
			u2 = 65535;
			p2++;
		}
		else
			i2 = ToAscii(u2 = ToUpper(c2));

		if(i1 != i2)
			return i1 >= i2 ? 1 : -1;

		if(u1 != u2) // different diacritics
			switch(i1)
			{
			case 'A': case 'E': case 'I': case 'N':
			case 'O': case 'T': case 'U': case 'Y':
				if(middle == 0)
					middle = u1 - u2;
				continue;
			default:
				return u1 >= u2 ? 1 : -1;
			}
		if(c1 != c2) // different case
		{
			if(little == 0)

				little = (u1 != c1) - (u2 != c2);
		}
	}
	little += 4 * middle;
	if(little == 0)
		little = a_length - b_length;
	return sgn(little);
}

class WildcardCompareCS : public LanguageInfo::WildcardCompare
{
public:
	WildcardCompareCS(const wchar *templ)
	{
		raw_templ = 0;
//		cvt_ascii = false;
		if(*templ == 0)
			return;
//		if((*templ == '.' && templ[1] != 0 && *++templ != '.') || ContainsAccents(templ))
//		{
//			exclude_ch = (ToUpper(*templ) == 'C' && templ[1] == 0);
//			cvt_ascii = false;
//		}
		raw_templ = templ;
//		if(cvt_ascii)
//			cvt_templ = ToUpper(ToAscii(raw_templ));
//		else
			cvt_templ = ToUpper(raw_templ);
	}

	virtual bool Matches(const wchar *s) const
	{
//		if(exclude_ch && *s && (s[1] == 'h' || s[1] == 'H'))
//			return false;
		return !raw_templ || RawMatches(s, cvt_templ);
	}

private:
	bool RawMatches(const wchar *s, const wchar *templ) const
	{
		for(;;)
			switch(*templ++)
			{
			case 0: return true;
			case '.': if(*templ == 0) return *s == 0; // force end of string
			case '?': if(*s++ == 0) return false; break;
			case '*':
				do
					if(RawMatches(s, templ))
						return true;
				while(*s++);
				return false;
			case '\\': if(*templ == 0 || *templ++ != *s++) return false; break;
			default: if(templ[-1] != ToUpper(*s++)) return false;
				break;
			}
		return true;
	}

private:
	const wchar *raw_templ;
//	bool         exclude_ch;
//	bool         cvt_ascii;
	WString      cvt_templ;
};

One<LanguageInfo::WildcardCompare> LanguageInfoCS::GetWildcardCompare(const wchar *wildcard_text) const
{
	return new WildcardCompareCS(wildcard_text);
}

class LanguageInfoEN : public LanguageInfo
{
public:
	LanguageInfoEN()
		: LanguageInfo(LNG_('E', 'N', 'U', 'S'))
	{
		english_name = "English";
		native_name = ToUnicode("English", CHARSET_DEFAULT);
//		thousand_separator = " ";
//		decimal_point = ".";
	}
};

class LanguageInfoGE : public LanguageInfo
{
public:
	LanguageInfoGE()
		: LanguageInfo(LNG_('D', 'E', 'D', 'E'))
	{
		english_name = "German";
		native_name = ToUnicode("Deutsch", CHARSET_WIN1250);
	}
};

class LanguageInfoFR : public LanguageInfo
{
public:
	LanguageInfoFR()
		: LanguageInfo(LNG_('F', 'R', 'F', 'R'))
	{
		english_name = "Franch";
		native_name = ToUnicode("Francaise", CHARSET_WIN1250);
	}
};

class LanguageInfoES : public LanguageInfo
{
public:
	LanguageInfoES()
		: LanguageInfo(LNG_('E', 'S', 'E', 'S'))
	{
		english_name = "Spanish";
		native_name = ToUnicode("Espagnnol", CHARSET_WIN1250);
	}
};

const LanguageInfo& GetLanguageInfo(int lcode)
{
	static bool init_std = false;
	if(!init_std)
	{
		init_std = true;
		LanguageInfo::Register(new LanguageInfoCS);
		LanguageInfo::Register(new LanguageInfoEN);
		LanguageInfo::Register(new LanguageInfoGE);
		LanguageInfo::Register(new LanguageInfoFR);
		LanguageInfo::Register(new LanguageInfoES);
	}

	static int recent = 0;
	LanguageInfo *rinfo = 0;
	if(rinfo && lcode == recent)
		return *rinfo;
	if(lcode == 0)
		lcode = GetCurrentLanguage(); //!! todo - decide on default / neutral language code
	LanguageInfoMap& map = LanguageInfo::Map();
	int f = map.Find(lcode);
	if(f < 0)
	{
		f  = map.GetCount();
		map.Add(lcode, new LanguageInfo(lcode));
	}
	recent = lcode;
	return *(rinfo = &map[f]);
}

const LanguageInfo& GetLanguageInfo()
{
	return GetLanguageInfo(GetCurrentLanguage());
}
