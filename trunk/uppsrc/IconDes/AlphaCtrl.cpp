#include "IconDes.h"

NAMESPACE_UPP

void AlphaCtrl::Layout()
{
	MakeImage();
}

void AlphaCtrl::Paint(Draw& w)
{
	Size sz = GetSize();
	Size isz = IconDesImg::Alpha().GetSize();
	w.DrawImage(0, isz.cy, img);
	DrawFrame(w, 0, isz.cy, sz.cx, sz.cy - isz.cy, SColorText());
	int h = sz.cy - isz.cy - 2;
	if(!mask) {
		w.DrawRect(15, isz.cy + 1, 1, h, SColorPaper());
		w.DrawRect(16, isz.cy + 1, 1, h, SColorText());
		w.DrawRect(17, isz.cy + 1, 1, h, SColorPaper());
		w.DrawRect(sz.cx - 17, isz.cy + 1, 1, h, SColorPaper());
		w.DrawRect(sz.cx - 16, isz.cy + 1, 1, h, SColorText());
		w.DrawRect(sz.cx - 15, isz.cy + 1, 1, h, SColorPaper());
	}
	int a = mask ? maskvalue : alpha;
	int x = a == 0   ? 8 - isz.cx / 2 :
	        a == 255 ? sz.cx - 8 - isz.cx / 2
	                 : 16 + a * (sz.cx - 32) / 255 - isz.cx / 2;
	w.DrawImage(x, 0, IconDesImg::Alpha());
}

void AlphaCtrl::DoPoint(Point p)
{
	Size sz = GetSize();
	if(mask)
		maskvalue = p.x < sz.cx / 2 ? 0 : 255;
	else
		if(p.x < 16 || sz.cx < 32)
			alpha = 0;
		else
		if(p.x > sz.cx - 16)
			alpha = 255;
		else
			alpha = 255 * (p.x - 16) / (sz.cx - 32);
	Refresh();
	UpdateActionRefresh();
}

void AlphaCtrl::LeftDown(Point p, dword keyflags)
{
	DoPoint(p);
	SetCapture();
}

void AlphaCtrl::MouseMove(Point p, dword keyflags)
{
	if(HasCapture())
		DoPoint(p);
}

static void sPaintCol(ImageBuffer& b, int x, int y, int h, RGBA c)
{
	RGBA *t = b[y] + x;
	while(h-- > 0) {
		*t = c;
		t += b.GetWidth();
	}
}

void AlphaCtrl::MakeImage()
{
	Size sz = GetSize();
	sz.cy -= IconDesImg::Alpha().GetHeight();
	if(sz.cx <= 32 || sz.cy < 0) {
		img = Null;
		return;
	}
	ImageBuffer b(GetSize());
	Color c = mask ? Black() : color;
	for(int i = 1; i < sz.cx; i++) {
		int a = mask ? i < sz.cx / 2 ? 0 : 255
		             : i < 16 ? 0 : i > sz.cx - 16 ? 255 : min(255, 255 * i / (sz.cx - 32) - 1);
		int h = sz.cy / 2;
		sPaintCol(b, i, 0, h, Blend((i & 8) ? White : Black, c, a));
		sPaintCol(b, i, h, h, Blend((i & 8) ? Black : White, c, a));
	}
	img = b;
	Refresh();
}

void AlphaCtrl::SetColor(Color c)
{
	color = c;
	MakeImage();
}

void AlphaCtrl::Mask(bool m)
{
	mask = m;
	MakeImage();
	Refresh();
}


void AlphaCtrl::Set(int a)
{
	(mask ? maskvalue : alpha) = a;
	UpdateRefresh();
}

int AlphaCtrl::Get() const
{
	return mask ? maskvalue : alpha;
}

AlphaCtrl::AlphaCtrl()
{
	BackPaint();
	Transparent();
	alpha = 255;
	mask = false;
	maskvalue = 255;
}

END_UPP_NAMESPACE
