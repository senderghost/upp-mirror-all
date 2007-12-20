#include "CtrlLib.h"

#ifdef PLATFORM_X11

#ifdef flagNOGTK

NAMESPACE_UPP

void ChHostSkin() {}

END_UPP_NAMESPACE

#else

#define Time    XTime
#define Font    XFont
#define Display XDisplay
#define Picture XPicture

#include <limits.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#undef Picture
#undef Time
#undef Font
#undef Display

NAMESPACE_UPP

GtkWidget *gtk__parent()
{
	static GtkWidget *p;
	if(!p) {
		p = gtk_window_new(GTK_WINDOW_POPUP);
		gtk_widget_realize(p);
	}
	return p;
}

GtkWidget *Setup(GtkWidget *widget)
{
	static GtkWidget *fl;
	if (!fl) {
		fl = gtk_fixed_new();
		gtk_container_add(GTK_CONTAINER(gtk__parent()), fl);
		gtk_widget_realize(fl);
	}

	gtk_fixed_put(GTK_FIXED(fl), widget, 0, 0);
	gtk_widget_realize(widget);
	gtk_widget_show(widget);
	return widget;
}

enum {
	GTK_BOX,
	GTK_CHECK,
	GTK_OPTION,
	GTK_ARROW,
	GTK_SLIDER,
	GTK_ICON,
	GTK_EXT,

	GTK_MARGIN1 = 0x0010,
	GTK_MARGIN2 = 0x0020,
	GTK_MARGIN3 = 0x0030,
	GTK_MARGIN4 = 0x0040,

	GTK_VAL1    = 0x0100,
	GTK_VAL2    = 0x0200,
	GTK_VAL3    = 0x0300,
	GTK_VAL4    = 0x0400,

	GTK_TOP     = 0x1000,
	GTK_VCENTER = 0x2000,
	GTK_BOTTOM  = 0x3000,
	GTK_LEFT    = 0x4000,
	GTK_HCENTER = 0x5000,
	GTK_RIGHT   = 0x6000,
};

static Image sLastImage;

Image GetGTK(GtkWidget *widget, int state, int shadow, const char *detail, int type, int cx, int cy)
{
	GdkPixbuf *icon;
	if(type == GTK_ICON) {
		gtk_widget_set_sensitive(widget, 1);
		gtk_widget_set_state(widget, GTK_STATE_NORMAL);
		icon = gtk_widget_render_icon(widget, detail, (GtkIconSize)state, NULL);
		if(!icon) return Null;
		cx = gdk_pixbuf_get_width(icon);
		cy = gdk_pixbuf_get_height(icon);
	}
	else {
		gtk_widget_set_sensitive(widget, state != 4);
		gtk_widget_set_state(widget, (GtkStateType)state);
	}
	Rect rect;
	int ht = type & 0xf000;
	rect.top = ht == GTK_VCENTER ? cy : ht == GTK_BOTTOM ? 2 * cy : 0;
	rect.left = ht == GTK_HCENTER ? cx : ht == GTK_RIGHT ? 2 * cx : 0;
	rect.SetSize(cx, cy);
	if(type >= GTK_LEFT && type <= GTK_RIGHT)
		cx *= 3;
	if(type >= GTK_TOP && type <= GTK_BOTTOM)
		cy *= 3;
	type &= ~0xf000;
	GdkRectangle& allocation = ((GtkWidget*)widget)->allocation;
	allocation.x = 0;
	allocation.y = 0;
	allocation.width = cx;
	allocation.height = cy;
	Image m[2];
	Color back = White;
	int margin = (type >> 4) & 15;
	for(int i = 0; i < 2; i++) {
		ImageDraw iw(cx + 2 * margin, cy + 2 * margin);
		iw.DrawRect(0, 0, cx + 2 * margin, cy + 2 * margin, back);
		static GdkColormap *cm = gdk_x11_colormap_foreign_new(
			                        gdkx_visual_get(XVisualIDFromVisual(Xvisual)), Xcolormap);
		GdkPixmap *pixmap = gdk_pixmap_foreign_new(iw.GetDrawable());
		gdk_drawable_set_colormap(pixmap, cm);
		GdkRectangle cr;
		cr.x = 0;
		cr.y = 0;
		cr.width = cx;
		cr.height = cy;
		GtkStyle *style = gtk_widget_get_style(widget);
		int rcx = max(rect.GetWidth() - 2 * margin, 0);
		int rcy = max(rect.GetHeight() - 2 * margin, 0);
		int t1 = (type & 0xf00) >> 8;
		switch(type & 15) {
		case GTK_BOX:
			gtk_paint_box(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                    widget, detail,
			                    rect.left + margin, rect.top + margin, rcx, rcy);
			break;
		case GTK_CHECK:
			gtk_paint_check(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                      widget, detail,
			                      rect.left + margin, rect.top + margin, rcx, rcy);
			break;
		case GTK_OPTION:
			gtk_paint_option(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                       widget, detail,
			                       rect.left + margin, rect.top + margin, rcx, rcy);
			break;
		case GTK_ARROW:
			gtk_paint_arrow(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                      widget, detail, (GtkArrowType)t1, 1,
			                      rect.left + margin, rect.top + margin, rcx, rcy);
			break;
		case GTK_SLIDER:
			gtk_paint_slider(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                       widget, detail,
			                       rect.left + margin, rect.top + margin, rcx, rcy,
			                       (GtkOrientation)t1);
			break;
		case GTK_ICON:
			gdk_draw_pixbuf(pixmap, NULL, icon, 0, 0, 0, 0, -1, -1, (GdkRgbDither)0, 0, 0);
			break;
		case GTK_EXT:
			gtk_paint_extension(style, pixmap, (GtkStateType)state, (GtkShadowType)shadow, &cr,
			                          widget, (gchar *)detail,
			                          rect.left + margin, rect.top + margin, rcx, rcy,
			                          (GtkPositionType)t1);
			break;
		}
		g_object_unref(pixmap);
		m[i] = Crop(iw, rect.Inflated(margin));
		back = Black;
	}
	if(type == GTK_ICON)
		g_object_unref(icon);
	sLastImage = RecreateAlpha(m[0], m[1]);
	return sLastImage;
}

struct ChGtkI : Moveable<ChGtkI> {
	GtkWidget  *widget;
	const char *detail;
	int         type;
};

Vector<ChGtkI>& ChGtkIs()
{
	static Vector<ChGtkI> x;
	return x;
}

GtkWidget *ChGtkLast()
{
	return ChGtkIs().Top().widget;
}

const char *ChGtkLastDetail()
{
	return ChGtkIs().Top().detail;
}

int ChGtkLastType()
{
	return ChGtkIs().Top().type;
}

void ChGtkNew(GtkWidget *widget, const char *detail, int type)
{
	if(gtk_widget_get_parent(widget) == NULL)
		Setup(widget);
	ChGtkI& q = ChGtkIs().Add();
	q.widget = widget;
	q.detail = detail;
	q.type = type;
}

void ChGtkNew(const char *detail, int type)
{
	ChGtkNew(ChGtkLast(), detail, type);
}

struct GtkElement {
	word gtki;
	byte state;
	byte shadow;
};

struct GtkImageMaker : ImageMaker {
	GtkElement e;
	ChGtkI     eg;
	Size       sz;

	virtual String Key() const {
		StringBuffer key;
		key.Cat((char *)&eg.widget, sizeof(eg.widget));
		key.Cat((char *)&eg.detail, sizeof(eg.detail));
		key.Cat((char *)&eg.type, sizeof(eg.type));
		key.Cat((char *)&e.gtki, sizeof(e.gtki));
		key.Cat((char *)&e.state, sizeof(e.state));
		key.Cat((char *)&e.shadow, sizeof(e.shadow));
		key.Cat((char *)&sz, sizeof(sz));
		return key;
	}
	virtual Image Make() const {
		return GetGTK(eg.widget, e.state, e.shadow & 0x7f, eg.detail, eg.type, sz.cx, sz.cy);
	}
};

Value GtkLookFn(Draw& w, const Rect& rect, const Value& v, int op)
{
	if(IsTypeRaw<GtkElement>(v)) {
		const GtkElement& e = ValueTo<GtkElement>(v);
		ChGtkI& eg = ChGtkIs()[e.gtki];
		switch(op) {
		case LOOK_MARGINS:
			return Rect(0, 0, 0, 0);
		case LOOK_ISOPAQUE:
			return false;
		}
		if(op == LOOK_PAINT || op == LOOK_PAINTEDGE) {
			Rect r = rect.Inflated((eg.type >> 4) & 15);
			GtkImageMaker gm;
			gm.e = e;
			gm.eg = eg;
			gm.sz = r.Size();
			Image m;
			if(e.shadow & 0x80) {
				m = MakeImage(gm);
				w.DrawImage(r.left, r.top,
				            m, RectC(0, 0, gm.sz.cx, gm.sz.cy - 7));
				w.DrawImage(r.left + 4, r.bottom - 7,
				            m, RectC(4, gm.sz.cy - 7, gm.sz.cx - 8, 5));
			}
			else
				w.DrawImage(r.left, r.top, MakeImagePaintOnly(gm));
			return 1;
		}
	}
	return Null;
}

Value GtkMakeCh(int shadow, int state)
{
	GtkElement e;
	e.gtki = ChGtkIs().GetCount() - 1;
	e.shadow = shadow;
	e.state = state;
	return RawToValue(e);
}

void GtkCh(Value& look, int shadow, int state)
{
	look = GtkMakeCh(shadow, state);
}

void GtkCh(Value *look, const char *d)
{
	GtkCh(look[CTRL_NORMAL], d[4] - '0', d[0] - '0');
	GtkCh(look[CTRL_HOT], d[5] - '0', d[1] - '0');
	GtkCh(look[CTRL_PRESSED], d[6] - '0', d[2] - '0');
	GtkCh(look[CTRL_DISABLED], d[7] - '0', d[3] - '0');
}

void GtkCh(Value *look)             { GtkCh(look, "02140000"); }
void GtkChButton(Value *look)       { GtkCh(look, "02142212"); }
void GtkChSlider(Value *look)       { GtkCh(look, "02242222"); }
void GtkChTrough(Value *look)       { GtkCh(look, "11141111"); }

void GtkChWith(Value& look, int shadow, int state, const Image& img, Color c)
{
	GtkElement e;
	e.gtki = ChGtkIs().GetCount() - 1;
	e.shadow = shadow;
	e.state = state;
	look = ChLookWith(GtkMakeCh(shadow, state), img, c);
}

void GtkChWith(Value *look, const char *d, const Image& img)
{
	GtkChWith(look[CTRL_NORMAL], d[4] - '0', d[0] - '0', img, ButtonMonoColor(0));
	GtkChWith(look[CTRL_HOT], d[5] - '0', d[1] - '0', img, ButtonMonoColor(1));
	GtkChWith(look[CTRL_PRESSED], d[6] - '0', d[2] - '0', img, ButtonMonoColor(2));
	GtkChWith(look[CTRL_DISABLED], d[7] - '0', d[3] - '0', img, ButtonMonoColor(3));
}

void GtkChButtonWith(Value *look, const Image& img) { GtkChWith(look, "02142222", img); }
void GtkChArrow(Value *look, const Image& img) { GtkChWith(look, "02142212", img); }

int  GtkInt(GtkWidget *widget, const char *id)
{
	int x = 0;
	gtk_widget_style_get(widget, id, &x, NULL);
	return x;
}

int  GtkInt(const char *id)
{
	return GtkInt(ChGtkLast(), id);
}

void GtkIml(int uii, GtkWidget *w, int shadow, int state, const char *detail, int type, int cx, int cy)
{
	CtrlsImg::Set(uii, GetGTK(w, state, shadow, detail, type, cx, cy));
}

void GtkIml(int uii, GtkWidget *w, int shadow, const char *detail, int type, int cx, int cy)
{
	GtkIml(uii + 0, w, shadow, 0, detail, type, cx, cy);
	GtkIml(uii + 1, w, shadow, 2, detail, type, cx, cy);
	GtkIml(uii + 2, w, shadow, 1, detail, type, cx, cy);
	GtkIml(uii + 3, w, shadow, 4, detail, type, cx, cy);
}

Color ChGtkColor(int ii, GtkWidget *widget)
{
	GdkColor cc = ((GtkStyle *)gtk_widget_get_style(widget))->fg[ii];
	return Color(cc.red >> 8, cc.green >> 8, cc.blue >> 8);
}

void ChGtkColor(Color& c, int ii)
{
	c = ChGtkColor(ii, ChGtkLast());
}

void ChGtkColor(Color *c, int ii)
{
	ChGtkColor(c[0], ii + 0);
	ChGtkColor(c[1], ii + 2);
	ChGtkColor(c[2], ii + 1);
	ChGtkColor(c[3], ii + 4);
}

Image GtkImage(const char *id, int size, int maxh = INT_MAX)
{
	if(maxh != INT_MAX)
		maxh = Ctrl::VertLayoutZoom(maxh);
	Image m = GetGTK(gtk__parent(), size, 0, id, GTK_ICON, 0, 0);
	if(!IsNull(m)) {
		Size sz = m.GetSize();
		if(sz.cy > maxh && sz.cy)
			m = Rescale(m, sz.cx * maxh / sz.cy, maxh);
	}
	return m;
}

void ChCtrlImg(int ii, const char *id, int size, int maxh = INT_MAX)
{
	Image m = GtkImage(id, size, maxh);
	if(!IsNull(m))
		CtrlImg::Set(ii, m);
}

Image GtkChImgLook(int shadow, int state, int kind)
{
	Image m = GetGTK(ChGtkLast(), state, shadow, ChGtkLastDetail(), ChGtkLastType(), 16, 16);
	int g = ImageMargin(m, 4, 10);
	if(kind == 1)
		return Crop(m, 0, g, 16 - g, 16 - 2 * g);
	if(kind == 2)
		return Crop(m, g, g, 16 - g, 16 - 2 * g);
	return m;
}

void GtkChImgWith(Value& look, int shadow, int state, const Image& img, Color c, int kind)
{
	Value m = GtkChImgLook(shadow, state, kind);
	look = IsNull(img) ? m : ChLookWith(m, img, c);
}

void GtkChImgWith(Value *look, const Image& img, int kind)
{
	GtkChImgWith(look[CTRL_HOT], 2, 2, img, ButtonMonoColor(1), kind);
	GtkChImgWith(look[CTRL_PRESSED], 1, 1, img, ButtonMonoColor(2), kind);
	GtkChImgWith(look[CTRL_DISABLED], 2, 4, img, ButtonMonoColor(3), kind);
	GtkChImgWith(look[CTRL_NORMAL], 2, 0, img, ButtonMonoColor(0), kind);
}

bool IsEmptyImage(const Image& m)
{
	const RGBA *s = ~m;
	const RGBA *e = ~m + m.GetLength();
	while(s < e) {
		if(s->a)
			return false;
		s++;
	}
	return true;
}

void ChHostSkin()
{
	static struct { void (*set)(Color); int ii; } col[] = {
		{ SColorPaper_Write, 6*5 + 0 },
		{ SColorFace_Write, 1*5 + 0 },
		{ SColorText_Write, 5*5 + 0 },
		{ SColorHighlight_Write, 6*5 + 3 },
		{ SColorHighlightText_Write, 5*5 + 3 },
		{ SColorMenu_Write, 6*5 + 0 },
		{ SColorMenuText_Write, 5*5 + 0 },
		{ SColorDisabled_Write, 5*5 + 4 },
		{ SColorLight_Write, 2*5 + 0 },
		{ SColorShadow_Write, 3*5 + 0 },
	};
	for(int i = 0; i < __countof(col); i++)
		(*col[i].set)(ChGtkColor(col[i].ii, gtk__parent()));

	int fontname = Font::ARIAL;
	int fontheight = 13;
	bool bold = false;
	bool italic = false;

	char *font_name = "";
	g_object_get(gtk_settings_get_default(), "gtk-font-name", &font_name, NULL);
#ifdef _DEBUG
	int xdpi = 100 * 1024;
#else
	int xdpi = 72 * 1024;
#endif
	g_object_get(gtk_settings_get_default(), "gtk-xft-dpi", &xdpi, NULL);

	const char *q = strrchr(font_name, ' ');
	if(q) {
		int h = atoi(q);
		if(h)
			fontheight = h;
		String face(font_name, q);
		fontname = Font::FindFaceNameIndex(face);

		if(fontname == 0) {
			for(;;) {
				const char *q = strrchr(face, ' ');
				if(!q) break;
				const char *s = q + 1;
				if(stricmp(s, "Bold") == 0 || stricmp(s, "Heavy") == 0)
					bold = true;
				else
				if(stricmp(s, "Italic") == 0 || stricmp(s, "Oblique") == 0)
					italic = true;
				else
				if(stricmp(s, "Regular") == 0 || stricmp(s, "Light") || stricmp(s, "Medium"))
					;
				else
					continue;
				face = String(~face, q);
			}
			fontname = Font::FindFaceNameIndex(face);
			if(fontname == 0)
				if(ToUpper(face[0]) == 'M')
					fontname = Font::COURIER;
				else
				if(ToUpper(face[0]) == 'S' && ToUpper(face[1]) == 'e')
					fontname = Font::ROMAN;
				else
					fontname = Font::ARIAL;
		}
	}

	Draw::SetStdFont(Font(fontname, (fontheight * xdpi + 512*72) / (1024*72))
	                 .Bold(bold).Italic(italic));

	ColoredOverride(CtrlsImg::Iml(), CtrlsImg::Iml());

	Color fc = Blend(SColorHighlight, SColorShadow);

	ChGtkIs().Clear();
	GtkWidget *w = Setup(gtk_radio_button_new(NULL));
	int is = GtkInt(w, "indicator-size") + 2;
	GTK_TOGGLE_BUTTON(w)->active = false;
	GTK_TOGGLE_BUTTON(w)->inconsistent = false;
	GtkIml(CtrlsImg::I_S0, w, 2, "radiobutton", GTK_OPTION|GTK_MARGIN1, is, is);
	GTK_TOGGLE_BUTTON(w)->active = true;
	GtkIml(CtrlsImg::I_S1, w, 1, "radiobutton", GTK_OPTION|GTK_MARGIN1, is, is);
	gtk_widget_destroy(w);

	w = Setup(gtk_check_button_new());
	GTK_TOGGLE_BUTTON(w)->active = false;
	GTK_TOGGLE_BUTTON(w)->inconsistent = false;
	GtkIml(CtrlsImg::I_O0, w, 2, "checkbutton", GTK_CHECK|GTK_MARGIN1, is, is);
	GTK_TOGGLE_BUTTON(w)->active = true;
	GtkIml(CtrlsImg::I_O1, w, 1, "checkbutton", GTK_CHECK|GTK_MARGIN1, is, is);
	GTK_TOGGLE_BUTTON(w)->active = false;
	GTK_TOGGLE_BUTTON(w)->inconsistent = true;
	GtkIml(CtrlsImg::I_O2, w, 3, "checkbutton", GTK_CHECK|GTK_MARGIN1, is, is);
	gtk_widget_destroy(w);

	{
		Button::Style& s = Button::StyleNormal().Write();
		s.overpaint = 3;
		static GtkWidget *button = gtk_button_new();
		ChGtkNew(button, "button", GTK_BOX|GTK_MARGIN3);
		GtkChButton(s.look);

		s.ok = GtkImage("gtk-ok", 4, 16);
		s.cancel = GtkImage("gtk-cancel", 4, 16);
		s.exit = GtkImage("gtk-quit", 4, 16);

		ChGtkColor(s.textcolor, 0 * 5);
		s.pressoffset.x = GtkInt("child-displacement-x");
		s.pressoffset.y = GtkInt("child-displacement-y");

		Color c = SColorPaper();
		for(int i = 0; i < 4; i++)
			s.monocolor[i] = c.GetR() + c.GetG() + c.GetB() < 3 * 128 ? White() : Black();
		s.monocolor[3] = Gray();

		ToolBar::Style& ts = ToolBar::StyleDefault().Write();
		GtkChButton(ts.buttonstyle.look);
		ts.buttonstyle.look[CTRL_NORMAL] = Null;
		ts.buttonstyle.look[CTRL_DISABLED] = Null;
		GtkCh(ts.buttonstyle.look[4], 1, 1);
		GtkCh(ts.buttonstyle.look[5], 1, 1);
	}

	{
		Button::Style& s = Button::StyleOk().Write();
		static GtkWidget *def_button;
		if(!def_button) {
			def_button = gtk_button_new();
			Setup(def_button);
			gtk_widget_set(def_button, "can-default", true, NULL);
			gtk_window_set_default(GTK_WINDOW(gtk__parent()), def_button);
			ChGtkNew(def_button, "button", GTK_BOX|GTK_MARGIN3);
		}
		GtkChButton(s.look);
	}

	{
		ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
		GtkObject *adj = gtk_adjustment_new(250, 0, 1000, 1, 1, 500);
		s.through = true;
		static GtkWidget *vscrollbar = gtk_vscrollbar_new(GTK_ADJUSTMENT(adj));
		ChGtkNew(vscrollbar, "slider", GTK_SLIDER|GTK_VAL1);
		GtkChSlider(s.vthumb);
		Image m = GetGTK(ChGtkLast(), 0, 0, "slider", GTK_SLIDER|GTK_VAL1, 16, 32);
		s.thumbmin = GtkInt("min-slider-length");
		s.barsize = GtkInt("slider-width");
		s.arrowsize = GtkInt("stepper-size");
		ChGtkNew("trough", GTK_BOX);
		GtkChTrough(s.vupper);
		GtkChTrough(s.vlower);
		is = min(s.barsize, s.arrowsize) / 2;
		bool atp = IsEmptyImage(GetGTK(ChGtkLast(), 2, 2, "vscrollbar", GTK_BOX|GTK_TOP, 16, 16));
		if(atp) {
			ChGtkNew("vscrollbar", GTK_ARROW);
			GtkCh(s.up.look, "02141111");
			ChGtkNew("vscrollbar", GTK_ARROW|GTK_VAL1);
			GtkCh(s.down.look, "02141111");

			static GtkWidget *btn = gtk_button_new();
			ChGtkNew(btn, "button", GTK_BOX);

			GtkChButton(Button::StyleScroll().Write().look);
			GtkChButton(Button::StyleEdge().Write().look);
			GtkChButton(Button::StyleLeftEdge().Write().look);

			{
				DropList::Style& s = DropList::StyleDefault().Write();
				GtkChButtonWith(s.look, CtrlsImg::DA());
				GtkChButtonWith(s.trivial, CtrlsImg::DA());
			}
			{
				SpinButtons::Style& s = SpinButtons::StyleDefault().Write();
				GtkChButtonWith(s.inc.look, CtrlsImg::SpU());
				GtkChButtonWith(s.dec.look, CtrlsImg::SpD());
			}
		}
		else {
			GtkIml(CtrlsImg::I_UA, ChGtkLast(), 0, 0, "vscrollbar", GTK_ARROW, is, is);
			GtkIml(CtrlsImg::I_DA, ChGtkLast(), 0, 0, "vscrollbar", GTK_ARROW|GTK_VAL1, is, is);

			ChGtkNew("vscrollbar", GTK_BOX|GTK_TOP);
			GtkChArrow(s.up.look, CtrlsImg::UA());
			ChGtkNew("vscrollbar", GTK_BOX|GTK_BOTTOM);
			GtkChArrow(s.down.look, CtrlsImg::DA());
			ChGtkNew("vscrollbar", GTK_BOX|GTK_VCENTER);

			GtkCh(Button::StyleScroll().Write().look, "02142222");

			GtkChImgWith(Button::StyleEdge().Write().look, Null, 1);
			GtkChImgWith(Button::StyleLeftEdge().Write().look, Null, 2);

			{
				DropList::Style& s = DropList::StyleDefault().Write();
				GtkChImgWith(s.look, CtrlsImg::DA(), 1);
				GtkChImgWith(s.trivial, CtrlsImg::DA(), 1);
			}
			{
				SpinButtons::Style& s = SpinButtons::StyleDefault().Write();
				GtkChImgWith(s.inc.look, CtrlsImg::SpU(), 1);
				GtkChImgWith(s.dec.look, CtrlsImg::SpD(), 1);
			}
		}

		int d = Diff(fc, SColorPaper());
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++) {
				RGBA c = sLastImage[x][y];
				if(c.a == 255) {
					int dd = Diff(c, SColorPaper());
					if(dd > d) {
						fc = c;
						d = dd;
					}
				}
			}
		FieldFrameColor_Write(fc);

		static GtkWidget *hscrollbar = gtk_hscrollbar_new(GTK_ADJUSTMENT(adj));
		ChGtkNew(hscrollbar, "slider", GTK_SLIDER);
		GtkChSlider(s.hthumb);
		ChGtkNew("trough", GTK_BOX);
		GtkChTrough(s.hupper);
		GtkChTrough(s.hlower);
		if(atp) {
			ChGtkNew("hscrollbar", GTK_ARROW|GTK_VAL2);
			GtkCh(s.left.look, "02141111");
			ChGtkNew("hscrollbar", GTK_ARROW|GTK_VAL3);
			GtkCh(s.right.look, "02141111");
		}
		else {
			GtkIml(CtrlsImg::I_LA, ChGtkLast(), 0, 0, "hscrollbar", GTK_ARROW|GTK_VAL2, is, is);
			GtkIml(CtrlsImg::I_RA, ChGtkLast(), 0, 0, "hscrollbar", GTK_ARROW|GTK_VAL3, is, is);
			ChGtkNew("hscrollbar", GTK_BOX|GTK_LEFT);
			GtkChArrow(s.left.look, CtrlsImg::LA());
			ChGtkNew("hscrollbar", GTK_BOX|GTK_RIGHT);
			GtkChArrow(s.right.look, CtrlsImg::RA());
			ChGtkNew("hscrollbar", GTK_BOX|GTK_VCENTER);
		}

		gtk_object_sink(adj);

		adj = gtk_adjustment_new(0, 0, 1000, 1, 1, 500);
		w = gtk_vscrollbar_new(NULL);
		Setup(w);
		s.overthumb = m != GetGTK(w, 0, 0, "slider", GTK_SLIDER|GTK_VAL1, 16, 32);
		gtk_widget_destroy(w);
		gtk_object_sink(adj);
	}

	{
		MenuBar::Style& s = MenuBar::StyleDefault().Write();
		static GtkWidget *menu_item = gtk_menu_item_new();
		ChGtkNew(menu_item, "menuitem", GTK_BOX);
		GtkCh(s.item, 2, 2);
		GtkCh(s.topitem, 2, 2);
	}

	{
		TabCtrl::Style& s = TabCtrl::StyleDefault().Write();
		static GtkWidget *tabctrl = gtk_notebook_new();
		ChGtkNew(tabctrl, "tab", GTK_EXT|GTK_VAL3|GTK_MARGIN3);
		ImageBuffer ib(9, 9);
		ImageBuffer ib1(9, 9);
		Image m = GetGTK(tabctrl, 0, 2, "tab", GTK_EXT|GTK_VAL3, 12, 24);
		for(int i = 0; i < 5; i++) {
			RGBA *t = ~ib + i * 9 + i;
			RGBA *t1 = ~ib1 + i * 9 + i;
			for(int n = 9 - 2 * i; n--; t += 9, t1 += 9) {
				Fill(t, m[21][i], 9 - 2 * i);
				Fill(t1, m[21][11 - i], 9 - 2 * i);
			}
		}
		{
			RGBA *t = ~ib + 9 + 8;
			RGBA *t1 = ~ib1 + 9 + 8;
			for(int i = 1; i < 9; i++) {
				memcpy(t, t1, i * sizeof(RGBA));
				t += 9 - 1;
				t1 += 9 - 1;
			}
		}
		ib.SetHotSpot(Point(4, 4));
		s.body = Image(ib);
		GtkCh(s.normal[0], 2, 1);
		GtkCh(s.normal[1], 2, 1);
		GtkCh(s.normal[2], 0x82, 0);
		GtkCh(s.normal[3], 2, 1);
		for(int i = 0; i < 4; i++)
			s.first[i] = s.last[i] = s.both[i] = s.normal[i];
		s.margin = 0;

		s.sel = Rect(0, 0, 0, 4);
		s.extendleft = 2;
	}

	ImageBuffer ib;
	ib.Create(3, 3);
	Fill(~ib, fc, ib.GetLength());
	ib[1][1] = Color(Null);
	ib.SetHotSpot(Point(1, 1));
	CtrlsImg::Set(CtrlsImg::I_EFE, ib);
	ib.Create(5, 5);
	Fill(~ib, fc, ib.GetLength());
	for(int x = 1; x < 4; x++)
		Fill(ib[x] + 1, SColorPaper(), 3);
	ib[2][2] = Color(Null);
	ib.SetHotSpot(Point(2, 2));
	CtrlsImg::Set(CtrlsImg::I_VE, ib);
	DropList::StyleDefault().Write().edge = CtrlsImg::EFE();

	static GtkWidget *popup;
	static int shadowtype;
	if(!popup) {
		GtkWidget *bar = gtk_menu_bar_new();
		Setup(bar);
		gtk_widget_style_get(bar, "shadow_type", &shadowtype, NULL);
		GtkWidget *item = gtk_menu_item_new();
		gtk_menu_shell_append(GTK_MENU_SHELL(bar), item);
		gtk_widget_realize(item);
		popup = gtk_menu_new();
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), popup);
		gtk_widget_realize(popup);
	}
	Color c = GetGTK(popup, 0, 2, "menu", GTK_BOX, 32, 32)[16][16];
	if(!IsNull(c) && Diff(c, SColorPaper()) < 200) //!!! ClearLooks patch
		SColorMenu_Write(c);

	ChCtrlImg(CtrlImg::I_information, "gtk-dialog-info", 6);
	ChCtrlImg(CtrlImg::I_question, "gtk-dialog-question", 6);
	ChCtrlImg(CtrlImg::I_exclamation, "gtk-dialog-warning", 6);

	static struct {
		void  (*set)(Image);
		const char *gtk;
	} bimg[] = {
		{ YesButtonImage_Write, "gtk-yes" },
		{ NoButtonImage_Write, "gtk-no" },
		{ AbortButtonImage_Write, "gtk-stop" },
		{ RetryButtonImage_Write, "gtk-refresh" },
	};

	for(int i = 0; i < __countof(bimg); i++)
		(*bimg[i].set)(GtkImage(bimg[i].gtk, 4, 16));

	ChLookFn(GtkLookFn);
}

END_UPP_NAMESPACE

#endif

#endif
