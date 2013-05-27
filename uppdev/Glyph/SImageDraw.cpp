#include "glyph.h"

void SImageDraw1::PutImage(Point p, const Image& m, const Rect& src)
{
	Over(ib, p, m, src);
}

void SImageDraw1::PutRect(const Rect& r, Color color)
{
	Upp::Fill(ib, r, color);
}

void SImageDraw1::Create(Size sz)
{
	ib.Create(sz);
	Init(sz);
}

Draw& SImageDraw::Alpha()
{
	if(!has_alpha) {
		Size sz = ib.GetSize();
		alpha.Create(sz);
		alpha.DrawRect(sz, GrayColor(0));
		has_alpha = true;
	}
	return alpha;
}

SImageDraw::operator Image() const
{
	ImageBuffer b(ib.GetSize());
	memcpy(b, ib.Begin(), sizeof(RGBA) * ib.GetLength());
	const RGBA *s = alpha.ib.Begin();
	RGBA *t = b;
	const RGBA *e = b.End();;
	if(has_alpha) {
		while(t < e) {
			t->a = s->r;
			t++;
			s++;
		}
		Premultiply(b);
		b.SetKind(IMAGE_ALPHA);
	}
	else {
		while(t < e) {
			t->a = 255;
			t++;
		}
		b.SetKind(IMAGE_OPAQUE);
	}
	return b;
}

SImageDraw::SImageDraw(Size sz)
{
	SImageDraw1::Create(sz);
}

SImageDraw::SImageDraw(int cx, int cy)
{
	SImageDraw1::Create(Size(cx, cy));
}
