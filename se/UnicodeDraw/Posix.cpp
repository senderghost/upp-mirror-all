#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#ifdef PLATFORM_POSIX

#include <cairo/cairo-ft.h>

namespace Upp {
FT_Face FTFace(Font fnt, String *rpath = NULL);
GlyphInfo  GetGlyphInfoSys(Font font, int chr);
FcPattern *CreateFcPattern(Font font);
};

int GlyphIndex(Font fnt, int ch)
{
	return FT_Get_Char_Index(FTFace(fnt), ch);
}

bool HasCodepoint(Font fnt, int ch)
{
	static Vector<int> tofu;
	int& q = tofu.At(fnt.GetFace(), Null);
	if(IsNull(q))
		q = GlyphIndex(fnt, 1); // this is 99.99% to produce tofu
	return ch == ' ' || GlyphIndex(fnt, ch) != q;
}

int GetAdvanceWidth(Font fnt, int ch)
{
	return GetGlyphInfoSys(fnt, ch).width;
}

void RenderCodepoint(FontGlyphConsumer& sw, double x, double y, int ch, Font fnt)
{
	RenderCharacterSys(sw, x, y, ch, fnt);
}

void DrawCodepoint(Draw& w, int x, int y, int ch, Font font)
{
	FcPattern *p = CreateFcPattern(font);
	cairo_font_face_t *font_face = cairo_ft_font_face_create_for_pattern(p);
	FcPatternDestroy(p);
		
	cairo_matrix_t font_matrix[1], ctm[1];
	cairo_matrix_init_identity(ctm);
	cairo_matrix_init_scale(font_matrix, font.GetHeight(), font.GetHeight());
	
	if(font.IsItalic() && !(FTFace(font)->style_flags & FT_STYLE_FLAG_ITALIC)) {
		cairo_matrix_t sheer[1];
		cairo_matrix_init_identity(sheer);
		sheer->xy = -0.2;
		cairo_matrix_multiply(font_matrix, font_matrix, sheer);
	}
	
	int angle = 0;
	if(angle)
		cairo_matrix_rotate(font_matrix, -angle * M_2PI / 3600);
	cairo_font_options_t *opt = cairo_font_options_create();
	cairo_scaled_font_t *scaled_font = cairo_scaled_font_create(font_face, font_matrix, ctm, opt);

	cairo_font_options_destroy(opt);
	cairo_font_face_destroy(font_face);

	cairo_glyph_t gs[1];
	cairo_glyph_t& g = gs[0];
	g.index = GlyphIndex(font, ch);
	g.x = x;
	g.y = y;

	SystemDraw *sw = dynamic_cast<SystemDraw *>(&w);
	if(sw) {
		cairo_t *cr = *sw;
		cairo_set_scaled_font(cr, scaled_font);
	
		Color c = Black();
		cairo_set_source_rgb(cr, c.GetR() / 255.0, c.GetG() / 255.0, c.GetB() / 255.0);
		cairo_show_glyphs(cr, gs, 1);
	}

	cairo_scaled_font_destroy(scaled_font);
}

#endif