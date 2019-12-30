#include "CtrlLib.h"

#ifdef GUI_GTK

/*

TODO: overpaint

*/

namespace Upp {

int GtkStyleInt(const char *name)
{
	gint h = Null;
	g_object_get(gtk_settings_get_default(), name, &h, NULL);
	return h;
}

int GtkStyleBool(const char *name)
{
	gboolean h = false;
	g_object_get(gtk_settings_get_default(), name, &h, NULL);
	return h;
}

String GtkStyleString(const char *name)
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

	String font_name = GtkStyleString("gtk-font-name");
	int xdpi = Nvl(GtkStyleInt("gtk-xft-dpi"), 72 * 1024);
	
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
	
	Font gui_font = Font(fontface, fround(DPI(fontheight) * xdpi + 512*72.0) / (1024*72)).Bold(bold).Italic(italic);
	Font::SetDefaultFont(gui_font);
}

static GtkStyleContext *sCtx = NULL;
static GtkStateFlags sFlags;

void Gtk_Free()
{
	if(sCtx)
		g_object_unref(sCtx);
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
			gtk_widget_path_append_type (path, G_TYPE_NONE);
			gtk_widget_path_iter_set_object_name (path, -1, s[0]);
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
	DLOG("Current style " << gtk_widget_path_to_string(gtk_style_context_get_path(sCtx)));
	
	GtkBorder margin, border, padding;
	int min_width, min_height;
	
	GtkStateFlags f = gtk_style_context_get_state(sCtx);
	gtk_style_context_get_margin (sCtx, f, &margin);
	gtk_style_context_get_border (sCtx, f, &border);
	gtk_style_context_get_padding (sCtx, f, &padding);

	gtk_style_context_get (sCtx, f, "min-width", &min_width, "min-height", &min_height, NULL);
	DDUMP(min_width);
	DDUMP(min_height);
	
	min_width += margin.left + margin.right + border.left + border.right + padding.left + padding.right;
	min_height += margin.top + margin.bottom + border.top + border.bottom + padding.top + padding.bottom;
	
	sCurrentSize.cx = min_width;
	sCurrentSize.cy = min_height;
}

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
	GdkRGBA color;
	gtk_style_context_get_color(sCtx, sFlags, &color);
	return Color(int(255 * color.red), int(255 * color.green), int(255 * color.blue));
}

Color GetBackgroundColor()
{
    ImageDraw iw(16, 16);
    gtk_render_background(sCtx, iw, 0, 0, 16, 16);
	return AvgColor(iw);
}

static Image sCurrentImage;

Image CairoImage(int cx, int cy, Event<cairo_t *> draw)
{
	Image m[2];
	for(int i = 0; i < 2; i++) {
		ImageDraw iw(DPI(cx), DPI(cy));
		iw.DrawRect(0, 0, DPI(cx), DPI(cy), i ? Black() : White());
		cairo_t *cr = iw;
		cairo_surface_set_device_scale(cairo_get_target(cr), DPI(1), DPI(1));
		draw(cr);
		m[i] = iw;
	}
	sCurrentImage = RecreateAlpha(m[0], m[1]);
	return sCurrentImage;
}

void SOImages(int imli, dword flags)
{
	for(int st = 0; st < 4; st++) {
		Gtk_State(st, flags);
		CtrlsImg::Set(imli++, CairoImage(16, 16, [&](cairo_t *cr) {
			gtk_render_check(sCtx, cr, 0, 0, 16, 16);
		}));
	}
}

Image CairoImage(int cx = 40, int cy = 32)
{
	return CairoImage(cx, cy, [&](cairo_t *cr) {
		gtk_render_background(sCtx, cr, 0, 0, cx, cy);
		gtk_render_frame(sCtx, cr,  0, 0, cx, cy);
	});
}

Image Gtk_Icon(const char *icon_name, int size)
{
	GdkPixbuf *pixbuf = gtk_icon_theme_load_icon_for_scale(gtk_icon_theme_get_default(), icon_name,
		                                                   size, 2, (GtkIconLookupFlags)0, NULL);
	int cx = gdk_pixbuf_get_width(pixbuf);
	int cy = gdk_pixbuf_get_height(pixbuf);

	Image m = CairoImage(cx, cy, [&](cairo_t *cr) {
		gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
		cairo_paint(cr);
	});
	
	Size sz = m.GetSize();

	return sz.cy > size && sz.cy ? Rescale(m, sz.cx * size / sz.cy, size) : m;
}

void StandardLook()
{
	for(int i = 0; i < 6; i++)
		CtrlsImg::Set(CtrlsImg::I_DA + i, CtrlsImg::Get(CtrlsImg::I_kDA + i));
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
	Gtk_New("tooltip.background");
		SColorInfo_Write(GetBackgroundColor());
		SColorInfoText_Write(GetInkColor());

//	ChClassicSkin();

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
	
	StandardLook();
	
	{
		Gtk_New("button");
		for(int pass = 0; pass < 2; pass++) {
			Button::Style& s = pass ? Button::StyleOk().Write() : Button::StyleNormal().Write();
			for(int i = 0; i < 4; i++) {
				Gtk_State(i);
				s.look[i] = Hot3(CairoImage());
				s.monocolor[i] = s.textcolor[i] = GetInkColor();
				DDUMP(GetInk(s.look[i]));
				if(pass == 0) {
					Image m = CairoImage(100, 100);
					Color ink = GetInk(m);
					Size sz = m.GetSize();
					m = Crop(m, sz.cx / 8, sz.cy / 8, 6 * sz.cx / 8, 6 * sz.cy / 8);
					auto Set = [&](Button::Style& s, const Image& arrow = Null) {
						Value l = MakeButton(0, m, DPI(1), ink, 0);
						s.look[i] = IsNull(l) ? l : ChLookWith(l, arrow);
					};
					Set(Button::StyleScroll().Write());
					Set(Button::StyleEdge().Write());
					Set(Button::StyleLeftEdge().Write());
					ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
					
					Set(s.up, CtrlsImg::UA());
					Set(s.down, CtrlsImg::DA());
					Set(s.left, CtrlsImg::LA());
					Set(s.right, CtrlsImg::RA());
				}
			}
			s.ok = Gtk_Icon("gtk-ok", DPI(16));
			s.cancel = Gtk_Icon("gtk-cancel", DPI(16));
			s.exit = Gtk_Icon("gtk-quit", DPI(16));
		}
	}

	{
		ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
		s.through = true;
		Gtk_New("scrollbar.right.vertical");
		Size sz = GtkSize();
		Gtk_New("scrollbar.right.vertical contents");
		GtkSize(sz);
		Gtk_New("scrollbar.right.vertical contents trough");
		GtkSize(sz);
		Gtk_New("scrollbar.right.vertical contents trough slider");
		GtkSize(sz);
		
		s.barsize = s.thumbwidth = DPI(sz.cx);
		s.thumbmin = max(GtkStyleInt("min-slider-length"), s.barsize);
		
		if(!GtkStyleBool("has-backward-stepper"))
			s.arrowsize = 0;
		
		sz.cy = 2 * sz.cx;

		for(int status = CTRL_NORMAL; status <= CTRL_DISABLED; status++) {
			Gtk_New("scrollbar.right.vertical", status);
			Size sz = GtkSize();
			Image m = CairoImage(sz.cx, sz.cy);
			Gtk_New("scrollbar.right.vertical contents", status);
			GtkSize(sz);
			Over(m, CairoImage(sz.cx, sz.cy));
			Gtk_New("scrollbar.right.vertical contents trough", status);
			GtkSize(sz);
			Over(m, CairoImage(sz.cx, sz.cy));
			s.vupper[status] = s.vlower[status] = Hot3(m);
			Gtk_New("scrollbar.right.vertical contents trough slider", status);
			GtkSize(sz);
			s.vthumb[status] = Hot3(CairoImage(sz.cx, sz.cy));
			Gtk_New("scrollbar.horizontal.bottom", status);
			m = CairoImage(sz.cy, sz.cx);
			Gtk_New("scrollbar.horizontal.bottom contents", status);
			Over(m, CairoImage(sz.cy, sz.cx));
			Gtk_New("scrollbar.horizontal.bottom contents trough", status);
			Over(m, CairoImage(sz.cy, sz.cx));
			s.hupper[status] = s.hlower[status] = Hot3(m);
			Gtk_New("scrollbar.horizontal.bottom contents trough slider", status);
			s.hthumb[status] = Hot3(CairoImage(sz.cy, sz.cx));
		}
	}
	
	{
		MenuBar::Style& s = MenuBar::StyleDefault().Write();
		s.pullshift.y = 0;

		Gtk_New("menu");
		Image m = CairoImage(32, 32);
		s.pullshift.y = 0;
		int mg = DPI(2); // TODO: Use values from GTK
		s.popupframe = WithHotSpot(m, mg, mg);
		Size sz = m.GetSize();
		s.popupbody = Crop(m, mg, mg, sz.cx - 2 * mg, sz.cy - 2 * mg);
		s.leftgap = DPI(16) + Zx(6);
		
		Gtk_New("menu menuitem");
		s.menutext = GetInkColor();
		Gtk_State(CTRL_HOT);
		s.itemtext = GetInkColor();
		SColorMenuText_Write(s.menutext);
		Color c = AvgColor(m);
		if(Diff(c, s.menutext) < 100) // menutext color too close to background color, fix it
			s.menutext = IsDark(c) ? White() : Black();
		s.item = Hot3(CairoImage(32, 16));
		SColorMenu_Write(GetBackgroundColor());
		
		Gtk_New("menubar");
		s.look = Hot3(CairoImage(32, 16));
		Color dk = SColorText();
		Color wh = SColorPaper();
		if(IsDark(wh))
			Swap(dk, wh);
		s.topitemtext[0] = IsDark(AvgColor(sCurrentImage)) ? wh : dk; // TODO: Do this properly
		s.topitem[1] = s.topitem[0];
		s.topitemtext[1] = s.topitemtext[0];
		Gtk_New("menubar menuitem", CTRL_HOT);
		s.topitem[0] = Null;
		s.topitem[2] = Hot3(CairoImage(32, 16));
		s.topitemtext[2] = GetInkColor();
	}

	ColoredOverride(CtrlsImg::Iml(), CtrlsImg::Iml());

	Gtk_Free();
}

Image GtkThemeIcon(const char *name, int rsz)
{
	return CtrlImg::smallreporticon();
}

};

#endif