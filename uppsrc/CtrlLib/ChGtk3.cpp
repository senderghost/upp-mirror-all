#include "CtrlLib.h"

#ifdef GUI_GTK

namespace Upp {

int GtkStyleInt(const char *name)
{
	int h = Null;
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
	DDUMP(gui_font);
	Font::SetDefaultFont(gui_font);
}

void ChHostSkin()
{
	SetupFont();
}

Image GtkThemeIcon(const char *name, int rsz)
{
	return CtrlImg::smallreporticon();
}

};

#endif