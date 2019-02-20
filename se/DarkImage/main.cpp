#include <CtrlLib/CtrlLib.h>
#include <plugin/jpg/jpg.h>

using namespace Upp;

inline int  Gwwrayscale(int r, int g, int b) { return (77 * r + 151 * g + 28 * b) >> 8; }

Color DarkTheme20(Color c)
{
	int h = 255 - Grayscale(c);

	if(h > 128)
		while(Grayscale(c) < h)
			c = Color(min(c.GetR() + 1, 255), min(c.GetG() + 1, 255), min(c.GetB() + 1, 255));
	else
		while(Grayscale(c) > h)
			c = Color(max(c.GetR() - 1, 0), max(c.GetG() - 1, 0), max(c.GetB() - 1, 0));
	
	return c;
}

Color DarkTheme2(Color color)
{
	if(IsNull(color))
		return Null;
	
	int v[3];
	v[0] = color.GetR();
	v[1] = color.GetG();
	v[2] = color.GetB();
	
	double c[3];
	c[0] = 0.21;
	c[1] = 0.72;
	c[2] = 0.07;

	int m0 = Grayscale(color);
	int m = 256 - m0;
	
	int i0 = 0;
	int i1 = 1;
	int i2 = 2;
	
	if(v[i0] > v[i1])
		Swap(i0, i1);
	if(v[i1] > v[i2])
		Swap(i1, i2);
	if(v[i0] > v[i1])
		Swap(i0, i1);

	if(m0 < m) {
		m -= m0;
		int a = min(v[i2] + m, 255) - v[i2];
		v[i0] += a;
		v[i1] += a;
		v[i2] += a;
		m -= a;

		a = min(v[i1] + int(m / (c[i0] + c[i1])), 255) - v[i1];
		v[i0] += a;
		v[i1] += a;
		m -= (c[i0] + c[i1]) * a;

		v[i0] = min(v[i0] + int(m / c[i1]), 255);
	}
	else {
		m = m0 - m;
		int a = v[i0] - max(v[i0] - m, 0);
		v[i0] -= a;
		v[i1] -= a;
		v[i2] -= a;
		m -= a;

		a = v[i1] - max(v[i1] - int(m / (c[i1] + c[i2])), 0);
		v[i1] -= a;
		v[i2] -= a;
		m -= (c[i1] + c[i2]) * a;

		v[i2] = max(v[i2] - int(m / c[i2]), 0);
	}
	
	return Color(v[0], v[1], v[2]);
}

Color DarkTheme3(Color c)
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

Image photo;

struct MyApp : TopWindow {
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		w.DrawRect(sz, White());
	#if 0
		PaintImages(w, RectC(0, 0, sz.cx, sz.cy / 2), CtrlImg::Iml(), false);
		PaintImages(w, RectC(0, sz.cy / 2, sz.cx, sz.cy / 2), CtrlImg::Iml(), true);
	#else
		w.DrawImage(0, 0, photo);
		w.DrawImage(photo.GetSize().cx, 0, DarkTheme(photo));
	#endif
	}
};

GUI_APP_MAIN
{
#if 0
	DDUMP(DarkTheme2(Color(255,255,0)));
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
	PNGEncoder().SaveFile("c:/xxx/test.jpg", DarkTheme(CtrlImg::reporticon()));
	
	
	
	return;
#endif

//	photo = StreamRaster::LoadFileAny("C:/xxx/aukro.jpg");
	photo = StreamRaster::LoadFileAny("C:/Users/cxl/Documents/test.jpg");
	DDUMP(photo.GetSize());
	
	MyApp().Sizeable().Run();
}
