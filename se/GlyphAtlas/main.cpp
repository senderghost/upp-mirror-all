#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

Image RenderGlyphByPainter2(Point at, double angle, int chr, Font font, Color color, Size sz)
{
	ImageBuffer ib(sz);
	BufferPainter sw(ib);
	sw.Clear(RGBAZero());
	sw.EvenOdd(true);
	sw.Translate(at.x, at.y);
	if(angle)
		sw.Rotate(angle);
	wchar text = chr;
	sw.Text(0, 0, &text, font, 1);
	sw.Fill(color);
	Image h = ib;
	return Premultiply(h);
}

Image RenderGlyph(double angle, int chr, Font font, Color color)
{
	Point at(font[chr], font.GetLineHeight());
	int n = 2 * (at.x + at.y);
	if(n < 0)
		return Null;
	at.x = max(at.x, at.y);
	at.y = max(at.x, at.y);
	return AutoCrop(WithHotSpot(RenderGlyphByPainter2(at, angle, chr, font, color, Size(n, n)), at.x, at.y), RGBAZero());
}

Image CreateGlyphAtlas(double angle, Font font, Color color, int max_glyphs, int atlas_width, int atlas_max_height)
{
	Array<Image> m;
	ImageBuffer b;
	for(int pass = 0; pass < 2; pass++) {
		int linecy = 0;
		int cx = 0;
		Point pos(0, 0);
		for(int i = 0; i < max_glyphs; i++) {
			Image h;
			if(pass == 0) {
				h = RenderGlyph(0, i + 32, font, color);
				m.Add(h);
			}
			else
				h = m[i];
			Size isz = h.GetSize();
			if(pos.y + isz.cy > atlas_max_height)
				break;
			if(isz.cx && isz.cy) {
				if(pos.x + isz.cx > atlas_width) {
					cx = max(cx, pos.x);
					pos.y += linecy;
					pos.x = linecy = 0;
				}
				if(pass)
					Copy(b, pos, h, isz);
			}
			pos.x += isz.cx;
			linecy = max(linecy, isz.cy);
		}
		if(pass == 0) {
			b.Create(cx, min(atlas_max_height, pos.y + linecy));
			Fill(~b, RGBAZero(), b.GetLength());
		}
	}
	return b;
}

Image atlas;

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) {
		w.DrawRect(GetSize(), White());
		w.DrawImage(0, 0, atlas);
//		w.DrawImage(0, 0, RenderGlyph(0, 'A', Arial(200), Black()));
	}
};

GUI_APP_MAIN
{
	for(int i = 0; i < 10; i++) {
		RTIMING("Atlas");
		atlas = CreateGlyphAtlas(0, StdFont(), Black(), 2048, 1024, 1024);
	}
	
	MyApp().Run();
}
