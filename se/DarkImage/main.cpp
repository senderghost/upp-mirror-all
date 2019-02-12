#include <CtrlLib/CtrlLib.h>

using namespace Upp;

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
		h = DarkTheme(Color(h));
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
	int x = r.left;
	int y = r.top;
	int cy = 0;
	for(int i = 0; i < iml.GetCount(); i++) {
		Image m = iml.Get(i);
		if(dark)
			m = DarkTheme(m);
		Size sz = m.GetSize();
		if(x + sz.cx + 16 > r.right) {
			y += cy + 16;
			x = r.left;
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
	DDUMP(DarkTheme(Color(230, 168, 54)));
	//return;

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
	
	MyApp().Run();
}
