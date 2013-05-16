#include "glyph.h"

bool IsUniform(const RGBA *s, RGBA c, int add, int n)
{
	while(n-- > 0) {
		if(*s != c)
			return false;
		s += add;
	}
	return true;
}

Image AutoCrop(const Image& m, RGBA c)
{
	Size isz = m.GetSize();
	Rect r = isz;
	for(r.top = 0; r.top < isz.cy && IsUniform(m[r.top], c, 1, isz.cx); r.top++)
		;
	for(r.bottom = isz.cy; r.bottom > r.top && IsUniform(m[r.bottom - 1], c, 1, isz.cx); r.bottom--)
		;
	if(r.bottom <= r.top)
		return Null;
	int h = r.GetHeight();
	const RGBA *p = m[r.top];
	for(r.left = 0; r.left < isz.cy && IsUniform(p + r.left, c, isz.cx, h); r.left++)
		;
	for(r.right = isz.cx; r.right > r.left && IsUniform(p + r.right - 1, c, isz.cx, h); r.right--)
		;
	Point p1 = m.GetHotSpot() - r.TopLeft();
	Point p2 = m.Get2ndSpot() - r.TopLeft();
	return WithHotSpots(Crop(m, r), p1.x, p1.y, p2.x, p2.y);
}

Image RenderGlyph(Font fnt, int chr, Color color, int angle)
{
	int cx = fnt[chr];
	int cy = fnt.GetLineHeight();
	ImageBuffer ib(2 * (cx + cy), 2 * (cx + cy));
	BufferPainter sw(ib, MODE_ANTIALIASED);
	sw.Clear(RGBAZero());
	sw.DrawText(cx + cy, cx + cy, angle, WString(chr, 1), fnt, color);
	ib.SetHotSpot(Point(cx + cy, cx + cy));
	return AutoCrop(ib, RGBAZero());
}

Image RenderGlyph(Font fnt, int chr, Color color, int angle, Size sz, Point offset)
{
	int cx = fnt[chr];
	int cy = fnt.GetLineHeight();
	ImageBuffer ib(sz);
	BufferPainter sw(ib, MODE_ANTIALIASED);
	sw.Offset(offset);
	sw.Clear(RGBAZero());
	sw.DrawText(cx + cy, cx + cy, angle, WString(chr, 1), fnt, color);
	ib.SetHotSpot(Point(cx + cy, cx + cy));
	return ib;
}

String CompressGlyph(const Image& m)
{
	const RGBA *s = m;
	const RGBA *e = s + m.GetLength();
	StringStream r;
	Size sz = m.GetSize();
	r / sz.cx / sz.cy;
	Point p = m.GetHotSpot();
	r / p.x / p.y;
	while(s < e) {
		const RGBA *b = s;
		if(s->a == 0 || s->a == 255) {
			byte a = s->a;
			s++;
			while(s < e && s - b < 63 && s->a == a)
				s++;
			if(a == 0 && s >= e)
				return r;
			r.Put((a & 0x40) | (s - b));
		}
		else {
			r.Put((s->a >> 1) | 0x80);
			s++;
		}
	}
	return r;
}

Image DecompressGlyph(const String& g, Color c)
{
	StringStream r(g);
	Size sz;
	r / sz.cx / sz.cy;
	ImageBuffer ib(sz);
	Point p;
	ib.SetHotSpot(p);
	r / p.x / p.y;
	RGBA *t = ib;
	RGBA *te = ib.End();
	RGBA full = c;
	while(!r.IsEof()) {
		byte b = r.Get();
		ASSERT(t < te);
		if(b & 0x80)
			*t++ = (((b & 0x7f) << 1) | ((b & 0x40) >> 6)) * c;
		else {
			int n = b & 63;
			ASSERT(t + n <= te);
			Fill(t, b & 0x40 ? full : RGBAZero(), n);
			t += n;
		}
	}
	Fill(t, RGBAZero(), te - t);
	return ib;
}
