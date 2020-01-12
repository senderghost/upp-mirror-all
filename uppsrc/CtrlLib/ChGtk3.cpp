#include "CtrlLib.h"

#ifdef GUI_GTK

/*

TODO: overpaint

*/

namespace Upp {

int GtkSettingsInt(const char *name)
{
	gint h = Null;
	g_object_get(gtk_settings_get_default(), name, &h, NULL);
	return h;
}

int GtkSettingsBool(const char *name)
{
	gboolean h = false;
	g_object_get(gtk_settings_get_default(), name, &h, NULL);
	return h;
}

String GtkSettingsString(const char *name)
{
	const char *h = "";
	g_object_get(gtk_settings_get_default(), name, &h, NULL);
	return h;
}

void SetupFont()
{
	int fontface = Font::ARIAL;
	int fontheight = 13;
	bool bold = false;
	bool italic = false;

	String font_name = GtkSettingsString("gtk-font-name");
	int xdpi = Nvl(GtkSettingsInt("gtk-xft-dpi"), 72 * 1024);
	
	const char *q = strrchr(font_name, ' ');
	if(q) {
		int h = atoi(q);
		if(h)
			fontheight = h;
		String face(font_name, q);
		fontface = Font::FindFaceNameIndex(face);

		if(fontface == 0) {
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
			fontface = Font::FindFaceNameIndex(face);
			if(fontface == 0) {
				if(ToUpper(face[0]) == 'M')
					fontface = Font::COURIER;
				else
				if(ToUpper(face[0]) == 'S' && ToUpper(face[1]) == 'e')
					fontface = Font::ROMAN;
				else
					fontface = Font::ARIAL;
			}
		}
	}
	
	Font gui_font = Font(fontface, fround(Ctrl::SCL(fontheight) * xdpi + 512*72.0) / (1024*72)).Bold(bold).Italic(italic);
	Font::SetDefaultFont(gui_font);
}

static Image sCurrentImage;

Image CairoImage(int cx, int cy, Event<cairo_t *> draw)
{
	Image m[2];
	for(int i = 0; i < 2; i++) {
		ImageDraw iw(DPI(cx), DPI(cy));
		iw.DrawRect(0, 0, DPI(cx), DPI(cy), i ? Black() : White());
		cairo_t *cr = iw;
#if GTK_CHECK_VERSION(3, 20, 0)
		cairo_surface_set_device_scale(cairo_get_target(cr), DPI(1), DPI(1));
#endif
		draw(cr);
		m[i] = iw;
	}
	sCurrentImage = RecreateAlpha(m[0], m[1]);
	return sCurrentImage;
}

Image CairoImage(GtkStyleContext *ctx, int cx = 40, int cy = 32)
{
	return CairoImage(cx, cy, [&](cairo_t *cr) {
		gtk_render_background(ctx, cr, 0, 0, cx, cy);
		gtk_render_frame(ctx, cr,  0, 0, cx, cy);
	});
}

Color GetInkColor(GtkStyleContext *ctx, dword flags)
{
	GdkRGBA color;
	gtk_style_context_get_color(ctx, (GtkStateFlags)flags, &color);
	RGBA rgba;
	rgba.r = int(255 * color.red);
	rgba.g = int(255 * color.green);
	rgba.b = int(255 * color.blue);
	rgba.a = int(255 * color.alpha);
	RGBA t = SColorPaper();
	AlphaBlend(&t, &rgba, 1);
	return t;
}

#if GTK_CHECK_VERSION(3, 20, 0)

static GtkStyleContext *sCtx = NULL;
static GtkStateFlags sFlags;

void Gtk_Free()
{
	if(sCtx)
		g_object_unref(sCtx);
	sCtx = NULL;
}

void Gtk_State(int state, dword flags = 0)
{
	sFlags = static_cast<GtkStateFlags>(decode(state, CTRL_HOT, GTK_STATE_FLAG_PRELIGHT,
	                                                  CTRL_PRESSED, GTK_STATE_FLAG_ACTIVE,
	                                                  CTRL_DISABLED, GTK_STATE_FLAG_INSENSITIVE,
	                                                  GTK_STATE_FLAG_NORMAL) | flags) ;
	gtk_style_context_set_state(sCtx, sFlags);
}

static Size sCurrentSize;

void Gtk_New(const char *name, int state = 0, dword flags = 0)
{
	Gtk_Free();
	sCtx = NULL;
	for(const String& element : Split(name, ' ')) {
		GtkWidgetPath *path = sCtx ? gtk_widget_path_copy(gtk_style_context_get_path(sCtx))
		                           : gtk_widget_path_new();
		Vector<String> s = Split(element, '.');
		if(s.GetCount()) {
			gtk_widget_path_append_type(path, G_TYPE_NONE);
			gtk_widget_path_iter_set_object_name(path, -1, s[0]);
		}
		for(int i = 1; i < s.GetCount(); i++)
			gtk_widget_path_iter_add_class(path, -1, s[i]);

		GtkStyleContext *context2 = gtk_style_context_new();
		gtk_style_context_set_path(context2, path);
		gtk_style_context_set_parent(context2, sCtx);
		gtk_widget_path_unref(path);
		Gtk_Free();
		sCtx = context2;
	}
	ASSERT(sCtx);
	gtk_style_context_set_scale(sCtx, DPI(1));
	Gtk_State(state, flags);
	
	GtkBorder margin, border, padding;
	int min_width, min_height;
	
	GtkStateFlags f = gtk_style_context_get_state(sCtx);
	gtk_style_context_get_margin (sCtx, f, &margin);
	gtk_style_context_get_border (sCtx, f, &border);
	gtk_style_context_get_padding (sCtx, f, &padding);

	gtk_style_context_get(sCtx, f, "min-width", &min_width, "min-height", &min_height, NULL);
	
	min_width += margin.left + margin.right + border.left + border.right + padding.left + padding.right;
	min_height += margin.top + margin.bottom + border.top + border.bottom + padding.top + padding.bottom;
	
	sCurrentSize.cx = min_width;
	sCurrentSize.cy = min_height;
}

/*
bool GtkStyleBool(const char *name)
{
	return false;
	gboolean b = false;
	gtk_style_context_get(sCtx, gtk_style_context_get_state(sCtx), name, &b, NULL);
	return b;
}

int GtkStyleInt(const char *name)
{
	gint n = 0;
	gtk_style_context_get(sCtx, gtk_style_context_get_state(sCtx), name, &n, NULL);
	return n;
}
*/

Size GtkSize()
{
	return sCurrentSize;
}

void GtkSize(Size& sz)
{
	sz.cx = max(sz.cx, sCurrentSize.cx);
	sz.cy = max(sz.cy, sCurrentSize.cy);
}

Color GetInkColor()
{
	GetInkColor(sCtx, sFlags);
}

void SOImages(int imli, dword flags)
{
	for(int st = 0; st < 4; st++) {
		Gtk_State(st, flags);
		CtrlsImg::Set(imli++, CairoImage(16, 16, [&](cairo_t *cr) {
			gtk_render_background(sCtx, cr, 0, 0, 16, 16);
			gtk_render_frame(sCtx, cr,  0, 0, 16, 16);
			gtk_render_check(sCtx, cr, 0, 0, 16, 16);
		}));
	}
}

Image CairoImage(int cx = 40, int cy = 32)
{
	return CairoImage(sCtx, cx, cy);
}

Color GetBackgroundColor()
{
	Image m = CairoImage(30, 30);
	Image b = CreateImage(m.GetSize(), SColorPaper());
	Over(b, m);
	return AvgColor(b);
}

Image Gtk_Icon(const char *icon_name, int size)
{
	GdkPixbuf *pixbuf = gtk_icon_theme_load_icon_for_scale(gtk_icon_theme_get_default(), icon_name,
		                                                   size, 2, (GtkIconLookupFlags)0, NULL);
	if(pixbuf) {
		int cx = gdk_pixbuf_get_width(pixbuf);
		int cy = gdk_pixbuf_get_height(pixbuf);
	
		Image m = CairoImage(cx, cy, [&](cairo_t *cr) {
			gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
			cairo_paint(cr);
		});
		
		Size sz = m.GetSize();
		
		g_object_unref(pixbuf);
	
		return sz.cy > size && sz.cy ? Rescale(m, sz.cx * size / sz.cy, size) : m;
	}
	return Null;
}

void ChHostSkin()
{
	SetupFont();
	
	Gtk_New("label.view");
		SColorPaper_Write(GetBackgroundColor());
		SColorText_Write(GetInkColor());
	Gtk_New("window.background");
		SColorFace_Write(GetBackgroundColor());
	Gtk_New("entry");
		Gtk_State(CTRL_DISABLED);
		SColorDisabled_Write(GetInkColor());
	Gtk_New("entry selection");
		SColorHighlight_Write(GetBackgroundColor());
		SColorHighlightText_Write(GetInkColor());
	Gtk_New("label.view");
		SColorLabel_Write(GetInkColor());
#if 0
	Gtk_New("tooltip.background");
		SColorInfo_Write(GetBackgroundColor());
		SColorInfoText_Write(GetInkColor());
#else
	SColorInfo_Write(IsDark(SColorText()) ? LtYellow() : GrayColor(79));
	SColorInfoText_Write(SColorText());
#endif

	ColoredOverride(CtrlsImg::Iml(), CtrlsImg::Iml());

#if 0 // TODO (?)
		{ SColorLight_Write, 2*5 + 0 },
		{ SColorShadow_Write, 3*5 + 0 },
#endif

	Gtk_New("radiobutton radio");
	SOImages(CtrlsImg::I_S0, GTK_STATE_FLAG_NORMAL);
	SOImages(CtrlsImg::I_S1, GTK_STATE_FLAG_CHECKED);
	Gtk_New("checkbutton check");
	SOImages(CtrlsImg::I_O0, GTK_STATE_FLAG_NORMAL);
	SOImages(CtrlsImg::I_O1, GTK_STATE_FLAG_CHECKED);
	SOImages(CtrlsImg::I_O2, GTK_STATE_FLAG_INCONSISTENT);

	CtrlImg::Set(CtrlImg::I_MenuCheck0, CtrlsImg::O0());
	CtrlImg::Set(CtrlImg::I_MenuCheck1, CtrlsImg::O1());
	CtrlImg::Set(CtrlImg::I_MenuRadio0, CtrlsImg::S0());
	CtrlImg::Set(CtrlImg::I_MenuRadio1, CtrlsImg::S1());

	for(int i = 0; i < 6; i++)
		CtrlsImg::Set(CtrlsImg::I_DA + i, CtrlsImg::Get(CtrlsImg::I_kDA + i));
	
	{
		Gtk_New("button");
		Color ink;
		Color text[4];
		Image button[4];
		for(int pass = 0; pass < 2; pass++) {
			Button::Style& s = pass ? Button::StyleOk().Write() : Button::StyleNormal().Write();
			int roundness = DPI(3);
			for(int i = 0; i < 4; i++) {
				Gtk_State(i);
				s.look[i] = Hot3(CairoImage());
				s.monocolor[i] = s.textcolor[i] = GetInkColor();
				if(pass == 0) {
					button[i] = WithHotSpots(CairoImage(100, 100), DPI(4), DPI(4), 0, 0);
					text[i] = GetInkColor();
				}
			}
			s.ok = Gtk_Icon("gtk-ok", DPI(16));
			s.cancel = Gtk_Icon("gtk-cancel", DPI(16));
			s.exit = Gtk_Icon("gtk-quit", DPI(16));
		}
		
		ChSynthetic(button, text);

		{
			auto& s = ToolButton::StyleDefault().Write();
			s.look[CTRL_NORMAL] = Image();
			s.look[CTRL_HOT] = button[CTRL_HOT];
			s.look[CTRL_PRESSED] = button[CTRL_PRESSED];
			s.look[CTRL_DISABLED] = Image();
			s.look[CTRL_CHECKED] = button[CTRL_PRESSED];
			s.look[CTRL_HOTCHECKED] = button[CTRL_HOT];
		}
	}

	auto DialogIcon = [](int i, const char *s) { CtrlImg::Set(i, Gtk_Icon(s, DPI(48))); };
	DialogIcon(CtrlImg::I_information, "gtk-dialog-info");
	DialogIcon(CtrlImg::I_question, "gtk-dialog-question");
	DialogIcon(CtrlImg::I_exclamation, "gtk-dialog-warning");
	DialogIcon(CtrlImg::I_error, "gtk-dialog-error");
	
	YesButtonImage_Write(Gtk_Icon("gtk-yes", DPI(16)));
	NoButtonImage_Write(Gtk_Icon("gtk-no", DPI(16)));
	AbortButtonImage_Write(Gtk_Icon("gtk-stop", DPI(16)));
	RetryButtonImage_Write(Gtk_Icon("gtk-refresh", DPI(16)));

	{
		ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
		static gboolean stepper;
		static gint minslider;
		ONCELOCK {
			static GtkWidget *proto = (GtkWidget *)gtk_scrollbar_new(GTK_ORIENTATION_HORIZONTAL, NULL); // to get style params
			gtk_widget_style_get(proto, "has-backward-stepper", &stepper, "min-slider-length", &minslider, NULL);
		}
		if(!stepper)
			s.arrowsize = 0;
		Gtk_New("scrollbar.horizontal.bottom");
		Size sz = GtkSize();
		Gtk_New("scrollbar.horizontal.bottom contents");
		GtkSize(sz);
		Gtk_New("scrollbar.horizontal.bottom contents trough");
		GtkSize(sz);
		Gtk_New("scrollbar.horizontal.bottom contents trough slider");
		GtkSize(sz);
		
		s.barsize = s.thumbwidth = DPI(sz.cy);
		s.thumbmin = max(minslider, 2 * s.barsize);

		sz.cx = 4 * sz.cy;

		for(int status = CTRL_NORMAL; status <= CTRL_DISABLED; status++) {
			Gtk_New("scrollbar.horizontal.bottom", status);
			Image m = CairoImage(sz.cx, sz.cy);
			Gtk_New("scrollbar.horizontal.bottom contents", status);
			Over(m, CairoImage(sz.cx, sz.cy));
			Gtk_New("scrollbar.horizontal.bottom contents trough", status);
			Over(m, CairoImage(sz.cx, sz.cy));
			s.hupper[status] = s.hlower[status] = WithHotSpot(m, CH_SCROLLBAR_IMAGE, 0);;
			s.vupper[status] = s.vlower[status] = WithHotSpot(RotateAntiClockwise(m), CH_SCROLLBAR_IMAGE, 0); // we have problems getting this right for vertical
			Gtk_New("scrollbar.horizontal.bottom contents trough slider", status);
			Image thumb = CairoImage(sz.cx, sz.cy);
			s.hthumb[status] = WithHotSpot(thumb, CH_SCROLLBAR_IMAGE, 0);
			s.vthumb[status] = WithHotSpot(RotateAntiClockwise(thumb), CH_SCROLLBAR_IMAGE, 0);
		}
	}
	
	{
		MenuBar::Style& s = MenuBar::StyleDefault().Write();
		s.pullshift.y = 0;

		Gtk_New("menu");
		Image m = CairoImage(128, 64);
		s.pullshift.y = 0;
		int mg = DPI(2);
		s.popupframe = WithHotSpot(m, mg, mg);
		Size sz = m.GetSize();
		s.popupbody = Crop(m, mg, mg, sz.cx - 2 * mg, sz.cy - 2 * mg);
		s.leftgap = DPI(16) + Zx(6);
		SColorMenu_Write(GetBackgroundColor());
		SColorMenuText_Write(s.menutext);
		
		Gtk_New("menu menuitem");
		s.menutext = GetInkColor();
		Gtk_State(CTRL_HOT);
		s.itemtext = GetInkColor();
		Color c = AvgColor(m);
		if(Diff(c, s.menutext) < 100) // menutext color too close to background color, fix it
			s.menutext = IsDark(c) ? White() : Black();
		s.item = Hot3(CairoImage(32, 16));
		
		m = CreateImage(Size(DPI(32), DPI(16)), SColorFace());
		Gtk_New("frame");
		Over(m, CairoImage(DPI(32), DPI(16)));
		Gtk_New("frame border");
		Over(m, CairoImage(DPI(32), DPI(16)));
		Gtk_New("menubar");
		Over(m, CairoImage(DPI(32), DPI(16)));
		s.look = Hot3(m);
		Color dk = SColorText();
		Color wh = SColorPaper();
		if(IsDark(wh))
			Swap(dk, wh);
		s.topitemtext[0] = IsDark(AvgColor(m)) ? wh : dk;
		s.topitem[1] = s.topitem[0] = Null;
		s.topitemtext[1] = s.topitemtext[0];
		Gtk_New("menubar menuitem", CTRL_HOT);
		s.topitem[0] = Null;
		s.topitem[2] = Hot3(CairoImage(32, 16));
		s.topitemtext[2] = GetInkColor();
	}

	Gtk_Free();
}

Image GtkThemeIcon(const char *name, int rsz)
{
	return Gtk_Icon(name, rsz);
}

#else

Image Gtk_Icon(const char *icon_name, int size)
{
	GdkPixbuf *pixbuf = gtk_icon_theme_load_icon(gtk_icon_theme_get_default(), icon_name,
		                                         size, (GtkIconLookupFlags)0, NULL);
	if(pixbuf) {
		int cx = gdk_pixbuf_get_width(pixbuf);
		int cy = gdk_pixbuf_get_height(pixbuf);
	
		Image m = CairoImage(cx, cy, [&](cairo_t *cr) {
			gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
			cairo_paint(cr);
		});
		
		Size sz = m.GetSize();
		
		g_object_unref(pixbuf);
	
		return sz.cy > size && sz.cy ? Rescale(m, sz.cx * size / sz.cy, size) : m;
	}
	return Null;
}

Image GtkThemeIcon(const char *name, int rsz)
{
	return Gtk_Icon(name, rsz);
}

void ChHostSkin()
{
	SetupFont();
#if 0
	static Color paper;
	ONCELOCK {
		GtkStyleContext *ctx = gtk_widget_get_style_context((GtkWidget *)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));
		gtk_style_context_set_state(ctx, GTK_STATE_FLAG_NORMAL);
		paper = AvgColor(CairoImage(ctx));
		SetChameleonSample(CairoImage(ctx));
		DDUMP(paper);
	}
	if(IsDark(paper)) {
		SColorText_Write(White());
		SColorPaper_Write(Black());
		SColorMenuText_Write(White());
		SColorFace_Write(GrayColor(60));
		SColorMenu_Write(GrayColor(70));
		SColorHighlight_Write(GrayColor(120));
		SColorInfo_Write(GrayColor(79));
		SColorInfoText_Write(SColorText());
	}
	else
#endif
	{
		SColorFace_Write(Color(242, 241, 240));
		SColorMenu_Write(Color(242, 241, 240));
		SColorHighlight_Write(Color(50, 50, 250));
	}

	ChStdSkin();
}

#endif

};

#endif