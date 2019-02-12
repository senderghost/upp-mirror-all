#include <CtrlLib/CtrlLib.h>

using namespace Upp;

Color DarkTheme2(Color c)
{
	int h = 255 - Grayscale(c);

	int v[3], t[3];
	v[0] = c.GetR();
	v[1] = c.GetG();
	v[2] = c.GetB();
	
	t[0] = h;
	t[1] = h;
	t[2] = h;
	
	int i0 = 0;
	int i1 = 1;
	int i2 = 2;
	
	if(v[i0] > v[i1])
		Swap(i0, i1);
	if(v[i1] > v[i2])
		Swap(i1, i2);
	if(v[i0] > v[i1])
		Swap(i0, i1);

	t[i0] = clamp(h - (v[1] - v[0]), 0, 255);
	int h2 = h + (v[2] - v[1]);
	t[i2] = clamp(h2, 0, 255);
	h2 -= t[i2];
	t[i0] -= h2;
	t[i1] -= h2;
	
	return Color(t[i0], t[i1], t[i2]);
}

Image DarkTheme(const Image& img)
{
	Image simg = Unmultiply(img);
	const RGBA *s = simg.begin();
	const RGBA *e = simg.end();

	ImageBuffer ib(img.GetSize());
	RGBA *t = ~ib;
	
	while(s < e) {
		RGBA h = *s++;
		byte a = h.a;
		h.a = 255;
	//	DLOG(h << " -> " << DarkTheme(Color(h)));
		h = DarkTheme2(Color(h));
		h.a = a;
		*t++ = h;
	}
	
	Premultiply(ib);

	return ib;
}

void PaintImages(Draw& w, Rect r, Iml& iml, bool dark)
{
	// DDUMP(dark);
	w.DrawRect(r, dark ? Black() : White());
	int x = r.left + 8;
	int y = r.top + 8;
	int cy = 0;
	for(int i = 0; i < iml.GetCount(); i++) {
		Image m = iml.Get(i);
		if(dark)
			m = DarkTheme(m);
		Size sz = m.GetSize();
		if(x + sz.cx + 16 > r.right) {
			y += cy + 16;
			x = r.left + 8;
		}
		w.DrawImage(x, y, m);
		x += sz.cx + 16;
		cy = max(cy, sz.cy);
	}
}

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		w.DrawRect(sz, White());
		PaintImages(w, RectC(0, 0, sz.cx, sz.cy / 2), CtrlImg::Iml(), false);
		PaintImages(w, RectC(0, sz.cy / 2, sz.cx, sz.cy / 2), CtrlImg::Iml(), true);
	}
};

GUI_APP_MAIN
{
#if 0
	DDUMP(DarkTheme2(Color(0,0,255)));
	return;

	RGBA h;
	h.a = 230;
	h.r = 168;
	h.g = 54;
	h.b = 255;
	
	DDUMP(h);
	
	Unmultiply(&h, &h, 1);

	h.a = 255;
	DDUMP(h);
	
	Color c = h;
	DDUMP(c);
	
	DDUMP(DarkTheme(c));

	DLOG("====");
	PNGEncoder().SaveFile("c:/xxx/reporticon.png", DarkTheme(CtrlImg::reporticon()));
	
	
	
	return;
#endif
	
	MyApp().Sizeable().Run();
}
