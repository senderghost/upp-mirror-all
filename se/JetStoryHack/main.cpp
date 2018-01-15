#include <CtrlLib/CtrlLib.h>

using namespace Upp;

String data;

struct MyApp : TopWindow {
	int base = 0;
	int width = 2;
	bool be = false;
	bool stride = TRUE;
	
	void Sync() {
		Title(String() << base << ", width: " << 8 * width << ", endian: " << (be ? "BE" : "LE") << ", stride: " << (stride ? "TD" : "LR"));
	}
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		w.DrawRect(sz, White());
		int n = base;
		ImageBuffer ib(sz);
		if(stride) {
			for(int xx = 0; xx < sz.cx; xx += 32)
				for(int yy = 0; yy < sz.cy - 32; yy += 32) {
					for(int x = 0; x < 2; x++) {
						for(int y = 0; y < 16; y++) {
							if(n + 16 >= data.GetCount())
								goto end;
							dword h = MAKEWORD(data[n + 16], data[n]);
							RGBA *h1 = ib[yy + 2 * y] + xx;
							RGBA *h2 = ib[yy + 2 * y + 1] + xx;
							for(int bit = 32768; bit; bit >>= 1) {
								RGBA c = h & bit ? Black() : White();
								*h1++ = c;
								*h1++ = c;
								*h2++ = c;
								*h2++ = c;
							}
							n++;
						}
					}
				}
		}
		else
			for(int x = 0; x < sz.cx; x += 8 * width * 2 + 2)
				for(int y = 0; y < sz.cy / 2 - 1; y++) {
					if(n >= data.GetCount())
						goto end;
					dword h = MAKEWORD(data[n + 1], data[n]);
					RGBA *h1 = ib[2 * y] + x;
					RGBA *h2 = ib[2 * y + 1] + x;
					for(int bit = 1 << (8 * width); bit; bit >>= 1) {
						RGBA c = h & bit ? Black() : White();
						*h1++ = c;
						*h1++ = c;
						*h2++ = c;
						*h2++ = c;
					}
					n += width;
				}
	end:
		w.DrawImage(0, 0, ib);
	}
	
	virtual bool Key(dword key, int count)
	{
		switch(key) {
		case K_DOWN: base++; break;
		case K_UP: base = max(base - 1, 0); break;
		case K_PAGEDOWN: base += 64; break;
		case K_PAGEUP: base = max(base - 64, 0); break;
		case K_LEFT: width = max(width - 1, 1); break;
		case K_RIGHT: width++; break;
		case K_F1: be = !be; break;
		case K_F2: stride = !stride; break;
		}
		Sync();
		Refresh();
		return false;
	}

	MyApp() { Sync(); }
};

GUI_APP_MAIN
{
	data = LoadFile("C:/xxx/GG.sna");
	DDUMP(data.GetCount());
//	data = LoadFile("C:/xxx/shades.sna");
	MyApp().Run();
}
