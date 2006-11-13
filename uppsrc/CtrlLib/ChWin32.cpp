#include "CtrlLib.h"

#define LLOG(x)   // RLOG(x)
#define LTIMING(x) // RTIMING(x)

#ifdef PLATFORM_WIN32

#ifdef PLATFORM_WINCE

void ChSysInit()
{
	CtrlImg::Reset();
	CtrlsImg::Reset();
	ChReset();
	ChSet("GUI_GlobalStyle", GUISTYLE_CLASSIC);
}

void ChDetectStyle() {}

#else

#include <uxtheme.h>
#include <tmschema.h>

#define DLLFILENAME "uxtheme.dll"
#define DLIMODULE   XpTheme
#define DLIHEADER   <CtrlLib/XpTheme.dli>
#define DLLCALL     STDAPICALLTYPE
#define WIDGET(x)
#include <Core/dli.h>
#undef  WIDGET

#define FN(a, b, c)
#define WIDGET(x)    XP_##x,
enum {
#include "XPTheme.dli"
	XP_COUNT
};

#undef  WIDGET
#define WIDGET(x)   #x,

static const char *xp_widget_name[] = {
#include "XPTheme.dli"
	NULL
};

#undef  WIDGET
#undef  FN

struct XpElement : Moveable<XpElement> {
	int16 widget;
	int8  part;
	int8  state;

	bool  whista;
	bool  contentm;

	bool  operator==(const XpElement& e) const {
		return e.widget == widget && e.part == part && e.state == state;
	}

	unsigned GetHashValue() const { return widget ^ part ^ state; }

	XpElement() { contentm = whista = false; }
};

static HANDLE xp_widget_handle[XP_COUNT];
static VectorMap<XpElement, int> xp_margin;
static VectorMap<XpElement, int> xp_opaque;

void XpClear()
{
	memset(xp_widget_handle, 0, sizeof(xp_widget_handle));
	xp_margin.Clear();
	xp_opaque.Clear();
}

HANDLE XpWidget(int widget)
{
	if(xp_widget_handle[widget] == NULL && XpTheme())
		xp_widget_handle[widget] = XpTheme().OpenThemeData(NULL,
		                            (WCHAR *)(const wchar *)WString(xp_widget_name[widget]));
	return xp_widget_handle[widget];
}

Image XpImage(int widget, int part, int state, Color color = Null, Size sz = Null)
{
	HANDLE theme = XpWidget(widget);
	if(!theme)
		return Null;
	if(IsNull(sz))
		XpTheme().GetThemePartSize(theme, ScreenInfo().GetHandle(), part, state, NULL,
		                           1 /*TS_TRUE*/, sz);
	Color c = White;
	Image m[2];
	for(int q = 0; q < 2; q++) {
		ImageDraw iw(sz);
		iw.DrawRect(sz, Nvl(color, c));
		HDC hdc = iw.BeginGdi();
		Rect r(sz);
		XpTheme().DrawThemeBackground(theme, hdc, part, state, r, NULL);
		iw.EndGdi();
		m[q] = iw;
		if(!IsNull(color))
			return m[q];
		c = Black;
	}
	ImageBuffer r(sz);
	const RGBA *ws = m[0];
	const RGBA *bs = m[1];
	RGBA *t = r;
	RGBA *e = t + r.GetLength();
	while(t < e) {
		t->a = bs->r - ws->r + 255;
		if(t->a) {
			t->r = bs->r * 255 / t->a;
			t->g = bs->g * 255 / t->a;
			t->b = bs->b * 255 / t->a;
		}
		else
			t->r = t->g = t->b = 0;
		t++;
		bs++;
		ws++;
	}
	return r;
}

int XpMargin(const XpElement& e)
{
	int q = xp_margin.Find(e);
	if(q >= 0)
		return xp_margin[q];
	Image m = XpImage(e.widget, e.part, e.state, White, Size(30, 30));
	Color c = m[4][4];
	int d;
	for(d = 4; d > 0; d--)
		if(Diff(m[d][d], c) > 10)
			break;
	q = d + 1;
	xp_margin.Add(e, q);
	return q;
}

int XpIsOpaque(const XpElement& e)
{
	int q = xp_opaque.Find(e);
	if(q >= 0)
		return xp_opaque[q];
	Image m1 = XpImage(e.widget, e.part, e.state, Black, Size(30, 30));
	Image m2 = XpImage(e.widget, e.part, e.state, White, Size(30, 30));
	q = m1 == m2;
	xp_opaque.Add(e, q);
	return q;
}

Color XpColor(int widget, int part, int state, int type)
{
	COLORREF cref = 0;
	HANDLE theme = XpWidget(widget);
	if(!theme)
		return Null;
	int r = XpTheme().GetThemeColor(theme, part, state, type, &cref);
	return r == S_OK ? Color::FromCR(cref) : Null;
}

int XpInt(int widget, int part, int state, int type)
{
	HANDLE theme = XpWidget(widget);
	if(!theme)
		return Null;
	int n = Null;
	int x = 0;
	int r = XpTheme().GetThemeInt(theme, part, state, type, &n);
	return r == S_OK ? n : Null;
}

int XpBool(int widget, int part, int state, int type)
{
	HANDLE theme = XpWidget(widget);
	if(!theme)
		return Null;
	int x = 0;
	BOOL flag = false;
	int r = XpTheme().GetThemeBool(theme, part, state, type, &flag);
	return r == S_OK ? flag : Null;
}

void SetXpImages(int uii, int n, int widget, int part, int state)
{
	for(int i = 0; i < n; i++) {
		Image m = XpImage(widget, part, state++);
		if(!IsNull(m))
			CtrlsImg::Set(uii++, m);
	}
}

void SetXpColors(const char *chcolor, int n, int widget, int part, int state, int type)
{
	int ii = 0;
	for(int i = 0; i < n; i++) {
		Color c = XpColor(widget, part, state++, type);
		if(!IsNull(c))
			ChSet(chcolor, ii++, c);
	}
}

Value XpLookFn(Draw& w, const Rect& rect, const Value& v, int op)
{
	if(IsTypeRaw<XpElement>(v)) {
		const XpElement& e = ValueTo<XpElement>(v);
		HANDLE htheme = XpWidget(e.widget);
		int q;
		switch(op) {
		case LOOK_MARGINS:
			if(e.contentm && htheme) {
				Rect r(0, 0, 100, 100);
				Rect cr;
				XpTheme().GetThemeBackgroundContentRect(htheme, NULL, e.part, e.state, r, cr);
				cr.bottom = 100 - cr.bottom;
				cr.right = 100 - cr.right;
				return cr;
			}
			q = XpMargin(e);
			return Rect(q, q, q, q);
		case LOOK_ISOPAQUE:
			return XpIsOpaque(e);
		}
		if(op == LOOK_PAINT || op == LOOK_PAINTEDGE) {
			LTIMING("XpPaint");
			Rect r = rect;
			if(op == LOOK_PAINTEDGE) {
				q = XpMargin(e);
				w.Begin();
				w.ExcludeClip(r.left + q, r.top + q,
				              r.Width() - 2 * q, r.Height() - 2 * q);
			}
			if(e.whista) {
				w.Clip(r);
				r.right++;
				r.top--;
				r.bottom++;
			}
//			w.DrawRect(r, SColorFace); //TODO - improve by adding the real transparency support
			if(htheme) {
				HDC hdc = w.BeginGdi();
				XpTheme().DrawThemeBackground(htheme, hdc, e.part, e.state, r, NULL);
				w.EndGdi();
			}
			if(e.whista)
				w.End();
			if(op == LOOK_PAINTEDGE)
				w.End();
			return 1;
		}
	}
	return Null;
}

struct chCtrlsImg {
	int id;
	int count;
	int widget;
	int part;
	int state;
};

static chCtrlsImg sImgs[] = {
	{ CtrlsImg::I_SizeGrip, 1, XP_STATUS, SP_GRIPPER, 0 },
	{ CtrlsImg::I_S0, 4, XP_BUTTON, BP_RADIOBUTTON, RBS_UNCHECKEDNORMAL },
	{ CtrlsImg::I_S1, 4, XP_BUTTON, BP_RADIOBUTTON, RBS_CHECKEDNORMAL },
	{ CtrlsImg::I_O0, 4, XP_BUTTON, BP_CHECKBOX, CBS_UNCHECKEDNORMAL },
	{ CtrlsImg::I_O1, 4, XP_BUTTON, BP_CHECKBOX, CBS_CHECKEDNORMAL },
	{ CtrlsImg::I_O2, 4, XP_BUTTON, BP_CHECKBOX, CBS_MIXEDNORMAL },
};

struct chLooks {
	const char *id;
	int   start_count;
	int   widget;
	int   part;
	int   state;
	bool  contentm;
};

static chLooks sLooks[] = {
	{ "ButtonLook", 4, XP_BUTTON, BP_PUSHBUTTON, 1 },
	{ "OkButtonLook", 4, XP_BUTTON, BP_PUSHBUTTON, 1 },
	{ "ScrollBarHorzUpper", 4, XP_SCROLLBAR, SBP_LOWERTRACKHORZ, 1 },
	{ "ScrollBarHorzLower", 4, XP_SCROLLBAR, SBP_UPPERTRACKHORZ, 1 },
	{ "ScrollBarVertUpper", 4, XP_SCROLLBAR, SBP_LOWERTRACKVERT, 1 },
	{ "ScrollBarVertLower", 4, XP_SCROLLBAR, SBP_UPPERTRACKVERT, 1 },
	{ "ScrollBarUp", 4, XP_SCROLLBAR, SBP_ARROWBTN, ABS_UPNORMAL },
	{ "ScrollBarDown", 4, XP_SCROLLBAR, SBP_ARROWBTN, ABS_DOWNNORMAL },
	{ "ScrollBarLeft", 4, XP_SCROLLBAR, SBP_ARROWBTN, ABS_LEFTNORMAL },
	{ "ScrollBarRight", 4, XP_SCROLLBAR, SBP_ARROWBTN, ABS_RIGHTNORMAL },
	{ "SpinUpLook", 4, XP_SPIN, SPNP_UP, 1 },
	{ "SpinDownLook", 4, XP_SPIN, SPNP_DOWN, 1 },
	{ "DropBoxBtn", 4, XP_COMBOBOX, CP_DROPDOWNBUTTON, 1 },
	{ "DropBoxSquaredBtn", 4, XP_COMBOBOX, CP_DROPDOWNBUTTON, 1 },
	{ "DropBoxEdge", 1, XP_COMBOBOX, 0, 0 },
	{ "HeaderTabLook", 4, XP_HEADER, HP_HEADERITEM, 1 },
	{ "ProgressIndicatorLook", 1, XP_PROGRESS, PP_BAR, 0, true },
	{ "VertProgressIndicatorLook", 1, XP_PROGRESS, PP_BARVERT, 0, true },
	{ "ProgressIndicatorChunkLook", 1, XP_PROGRESS, PP_CHUNK },
	{ "VertProgressIndicatorChunkLook", 1, XP_PROGRESS, PP_CHUNKVERT },
	{ "TabCtrlLook", 4, XP_TAB, TABP_TABITEM, 1 },
	{ "TabCtrlLook", MAKELONG(4, 4), XP_TAB, TABP_TABITEMLEFTEDGE, 1 },
	{ "TabCtrlLook", MAKELONG(4, 8), XP_TAB, TABP_TABITEM/*RIGHTEDGE*/, 1 },
	{ "TabCtrlLook", MAKELONG(4, 12), XP_TAB, TABP_TABITEMBOTHEDGE, 1 },
	{ "TabCtrlLook", MAKELONG(1, 16), XP_TAB, TABP_PANE, 1 },
	{ "ToolButtonLook", 6, XP_TOOLBAR, 1, 1 },
};

void ChSet(const char *id, int i, const XpElement& e)
{
	ChSet(id, i, RawToValue(e));
}

void ChDetectStyle()
{
	ChSysInit();
	if(XpWidget(XP_BUTTON)) {
		LLOG("XP theme !");
		ChSysInit();
		ChSet("GUI_GlobalStyle", GUISTYLE_XP);
		ColoredOverride(CtrlsImg::Iml(), CtrlsImg::Iml());
		CtrlsImg::Reset();
		ChSet("EditFieldIsThin", 1);
		for(chCtrlsImg *m = sImgs; m < sImgs + __countof(sImgs); m++)
			SetXpImages(m->id, m->count, m->widget, m->part, m->state);
		XpElement e;
		for(chLooks *l = sLooks; l < sLooks + __countof(sLooks); l++) {
			for(int i = 0; i < LOWORD(l->start_count); i++) {
				e.widget = l->widget;
				e.part = l->part;
				e.state = l->state + i;
				e.contentm = l->contentm;
				ChSet(l->id, HIWORD(l->start_count) + i, e);
			}
		}
/*		Image m = XpImage(XP_WINDOW, WP_DIALOG, 0, SColorPaper());
		if(!IsNull(SimpleColor(m))) {
			e.widget = XP_WINDOW;
			e.part = WP_DIALOG;
			e.state = 0;
			ChSet("DialogFaceLook", e);
		}*/

		e.widget = XP_BUTTON;
		e.part = BP_PUSHBUTTON;
		e.state = PBS_DEFAULTED;
		ChSet("OkButtonLook", 0, e);
		ChSet("DropBoxInsideEdge", XpInt(XP_COMBOBOX, CP_DROPDOWNBUTTON, CBXS_NORMAL,
		                                 2403/*TMT_BORDERSIZE*/));
		ChSet("DropImg", Null);

		Image hm = XpImage(XP_HEADER, HP_HEADERITEM, 1, SColorPaper, Size(20, 10));
		RGBA textc = SColorText();
		int diff = Diff(hm[4][19], textc);
		int hdroll = 0;
		for(int i = 0; i < 4; i++) {
			int d = Diff(hm[4][i], textc);
			if(d < diff) {
				diff = d;
				hdroll = i + 1;
			}
			d = Diff(hm[4][19 - i], textc);
			if(d < diff) {
				diff = d;
				hdroll = -i;
			}
		}
		ChSet("HeaderTabGridAdjustment", hdroll);

		for(int i = 0; i < 4; i++) {
			e.widget = XP_SCROLLBAR;
			e.state = 1 + i;
			e.contentm = false;
			e.part = SBP_THUMBBTNHORZ;
			ChSet("ScrollBarHorzThumb", i,
			      ChLookWith(RawToValue(e), XpImage(XP_SCROLLBAR, SBP_GRIPPERHORZ, 1)));
			e.part = SBP_THUMBBTNVERT;
			ChSet("ScrollBarVertThumb", i,
			      ChLookWith(RawToValue(e), XpImage(XP_SCROLLBAR, SBP_GRIPPERVERT, 1)));

			Color paper = i == 3 ? SColorFace : SColorPaper;
			Image m = XpImage(XP_COMBOBOX, CP_DROPDOWNBUTTON, CBXS_NORMAL + i, paper);
			Size isz = m.GetSize();
			int cbs = XpInt(XP_COMBOBOX, CP_DROPDOWNBUTTON, CBXS_NORMAL + i, 2403/*TMT_BORDERSIZE*/);
			if(cbs == 0) {
				Image h = HorzSymm(m);
				ChSet("LeftEdgeButtonLook", i, Unglyph(Crop(h, 1, 1, isz.cx - 1, isz.cy - 2)));
				m = Crop(h, 0, 1, isz.cx - 1, isz.cy - 2);
			}
			if(cbs == 1 &&
			   XpBool(XP_COMBOBOX, CP_DROPDOWNBUTTON, CBXS_NORMAL + i, 2203/*TMT_BORDERONLY*/) == 0 &&
			   XpInt(XP_COMBOBOX, 0, 0, 2403/*TMT_BORDERSIZE*/) == 1 &&
			   XpBool(XP_COMBOBOX, 0, 0, 2203/*TMT_BORDERONLY*/) == 0) {
					m = Crop(m, 0, 1, isz.cx - 1, isz.cy - 2);
					e.widget = XP_COMBOBOX;
					e.part = CP_DROPDOWNBUTTON;
					e.state = CBXS_NORMAL + i;
					e.whista = true;
					ChSet("DropBoxBtn", i, e);
			}
			Color c;
			double gf;
			m = Unglyph(m, c, gf);
			if(i == 0 && gf > 150)
				CtrlsImg::Set(CtrlsImg::I_DA, ClassicCtrlsImg::DA());
			ChSet("ButtonMonoColor", i, c);
			ChSet("EdgeButtonLook", i, m);
			ChSet("DropBoxSquaredBtn", i, ChLookWith(m, CtrlsImg::DA(), c));
			m = Unglyph(XpImage(XP_SCROLLBAR, SBP_ARROWBTN, i + ABS_UPNORMAL, paper));
			Size msz = m.GetSize();
			ChSet("ScrollButtonLook", i,
			      VertBlend(m, Unglyph(XpImage(XP_SCROLLBAR, SBP_ARROWBTN, i + ABS_DOWNNORMAL,
			                                   paper)),
			                msz.cy / 3, msz.cy * 2 / 3));
		}
		int ebs = max(1, XpInt(XP_EDIT, EP_EDITTEXT, 1, 2403/*TMT_BORDERSIZE*/));
		Image ee = XpImage(XP_EDIT, EP_EDITTEXT, 1, SColorFace(), Size(10 * ebs, 10 * ebs));
		ImageBuffer eb(ee);
		eb.SetHotSpot(Point(ebs, ebs));
		ee = eb;
		ChSet("EditFieldEdge", ee);

		ebs = max(1, XpInt(XP_LISTVIEW, 0, 1, 2403/*TMT_BORDERSIZE*/));
		ee = XpImage(XP_LISTVIEW, 0, 1, SColorFace(), Size(10 * ebs, 10 * ebs));
		eb = ee;
		eb.SetHotSpot(Point(ebs + 1, ebs + 1));
		ee = eb;
		ChSet("ViewEdge", ee);
		ChSet("SpinWidth", FrameButtonWidth());
		ChSet("LabelBoxTextColor", XpColor(XP_BUTTON, BP_GROUPBOX, GBS_NORMAL, 3803/*TMT_TEXTCOLOR*/));
		ChSet("LabelBoxColor", XpColor(XP_BUTTON, BP_GROUPBOX, GBS_NORMAL, 3822/*TMT_BORDERCOLORHINT*/));
		SetXpColors("ButtonTextColor", 4, XP_BUTTON, BP_PUSHBUTTON, PBS_NORMAL, 3803/*TMT_TEXTCOLOR*/);

		ChLookFn(XpLookFn);
	}
	else
		ChSetStyleClassic();
}

struct sysColor {
	const char *id;
	int syscolor;
};

static sysColor sSysColor[] = {
	{ "SColorFace", COLOR_3DFACE },
	{ "SColorPaper", COLOR_WINDOW },
	{ "SColorText", COLOR_WINDOWTEXT },
	{ "SColorHighlight", COLOR_HIGHLIGHT },
	{ "SColorHighlightText", COLOR_HIGHLIGHTTEXT },
	{ "SColorMenu", COLOR_MENU },
	{ "SColorMenuText", COLOR_MENUTEXT },
	{ "SColorInfo", COLOR_INFOBK },
	{ "SColorInfoText", COLOR_INFOTEXT },
	{ "SColorLight", COLOR_3DHILIGHT },
	{ "SColorShadow", COLOR_3DSHADOW },
};

void ChSysInit()
{
	LLOG("ChInitWin");
	CtrlImg::Reset();
	CtrlsImg::Reset();
	ChReset();
	XpClear();

	CtrlImg::Set(CtrlImg::I_information, Win32Icon(IDI_INFORMATION));
	CtrlImg::Set(CtrlImg::I_question, Win32Icon(IDI_QUESTION));
	CtrlImg::Set(CtrlImg::I_exclamation, Win32Icon(IDI_EXCLAMATION));

	ChSet("FrameButtonWidth", GetSystemMetrics(SM_CYHSCROLL));
	ChSet("ScrollBarArrowSize", GetSystemMetrics(SM_CXHSCROLL));
	for(sysColor *s = sSysColor; s < sSysColor + __countof(sSysColor); s++)
		ChSet(s->id, Color::FromCR(GetSysColor(s->syscolor)));
	dword x = GetSysColor(COLOR_GRAYTEXT);
	ChSet("SColorDisabled", x ? Color::FromCR(x) : Color::FromCR(GetSysColor(COLOR_3DSHADOW)));
}

#endif

#endif
