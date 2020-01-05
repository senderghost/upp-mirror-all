#include "CtrlLib.h"

namespace Upp {

#define LLOG(x)  // RLOG(x)

#define IMAGECLASS CtrlsImg
#define IMAGEFILE <CtrlLib/Ctrls.iml>
#include <Draw/iml_source.h>

#define IMAGECLASS ClassicCtrlsImg
#define IMAGEFILE <CtrlLib/ClassicCtrls.iml>
#include <Draw/iml_source.h>

void ChSysInit();

void ChStdSkin()
{
	ChSysInit();
	GUI_GlobalStyle_Write(GUISTYLE_XP);
	GUI_PopUpEffect_Write(Ctrl::IsCompositedGui() ? GUIEFFECT_NONE : GUIEFFECT_SLIDE);
	ColoredOverride(CtrlsImg::Iml(), CtrlsImg::Iml());
}

void SbWc(Value *look)
{
	Color wc = Blend(SColorFace(), SColorPaper(), 170);
	look[CTRL_NORMAL] = wc;
	look[CTRL_HOT] = wc;
	look[CTRL_PRESSED] = SColorText();
	look[CTRL_DISABLED] = wc;
}

void ChClassicSkin()
{
	LLOG("ChInitWinClassic");

	ChSysInit();
	GUI_GlobalStyle_Write(GUISTYLE_CLASSIC);
	GUI_PopUpEffect_Write(Ctrl::IsCompositedGui() ? GUIEFFECT_NONE : GUIEFFECT_SLIDE);
	
	ColoredOverride(CtrlsImg::Iml(), ClassicCtrlsImg::Iml());
	for(int q = 0; q < 4; q++)
		CtrlsImg::Set(CtrlsImg::I_HTB + q, AdjustColors(CtrlsImg::Get(ClassicCtrlsImg::I_B + q)));

	{
		Button::Style& s = Button::StyleNormal().Write();
		s.monocolor[0] = s.monocolor[1] = s.monocolor[2] = s.monocolor[3] = SColorText();
		s.pressoffset.x = s.pressoffset.y = 1;
		s.transparent = false;
	}

	{
		ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
		SbWc(s.hupper);
		SbWc(s.hlower);
		SbWc(s.vupper);
		SbWc(s.vlower);
		for(int i = 0; i < 4; i++)
			s.vthumb[i] = s.hthumb[i] = Button::StyleNormal().look[i];
	}

	{
		MultiButton::Style& s = MultiButton::StyleDefault().Write();
		s.border = s.trivialborder = 2;
	}

	{
		SeparatorCtrl::Style& s = SeparatorCtrl::StyleDefault().Write();
		s.l1 = SColorShadow();
		s.l2 = SColorLight();
	}

	{
		MenuBar::Style& s = MenuBar::StyleDefault().Write();
		s.popupbody = SColorFace();
	}

//	LabelBoxTextColor_Write(SColorText());
}

#ifdef PLATFORM_X11

void ChSysInit()
{
	CtrlImg::Reset();
	CtrlsImg::Reset();
	ChReset();
}

#endif

void FillImage(Painter& p, const Rectf& r, const Image& m)
{
	Xform2D xform = Xform2D::Translation(r.left, r.top);
	Size isz = m.GetSize();
	xform = Xform2D::Scale(r.GetWidth() / isz.cx, r.GetHeight() / isz.cy) * xform;
	p.Fill(m, xform);
}

void RoundedRect(Painter& w, double x, double y, double cx, double cy, double rx, double ry, dword corners)
{
	if(corners & CORNER_TOP_LEFT)
		w.Move(x + rx, y).Arc(x + rx, y + ry, rx, ry, -M_PI / 2, -M_PI / 2);
	else
		w.Move(x, y);
	
	if(corners & CORNER_BOTTOM_LEFT)
		w.Line(x, y + cy - ry).Arc(x + rx, y + cy - ry, rx, ry, M_PI, -M_PI / 2);
	else
		w.Line(x, y + cy);

	if(corners & CORNER_BOTTOM_RIGHT)
		w.Line(x + cx - rx, y + cy).Arc(x + cx - rx, y + cy - ry, rx, ry, M_PI / 2, -M_PI / 2);
	else
		w.Line(x + cx, y + cy);
	
	if(corners & CORNER_TOP_RIGHT)
		w.Line(x + cx, y + ry).Arc(x + cx - rx, y + ry, rx, ry, 0, -M_PI / 2);
	else
		w.Line(x + cx, y);

	w.Close();
}

void RoundedRect(Painter& w, Rectf r, double rx, double ry, dword corner)
{
	RoundedRect(w, r.left, r.top, r.GetWidth(), r.GetHeight(), rx, ry, corner);
}

Image MakeButton(int radius, const Image& face, int border_width, Color border_color, dword corner)
{
	int q = radius + border_width + DPI(16);
	Rectf r(0, 0, q, q);
	ImagePainter w(r.GetSize());
	w.Clear(RGBAZero());
	RoundedRect(w, r.Deflated(border_width / 2.0), radius, radius, corner);
	FillImage(w, r.Deflated(border_width / 2.0 - 1), face);
	RoundedRect(w, r.Deflated(border_width / 2.0), radius, radius, corner);
	if(!IsNull(border_color))
		w.Stroke(border_width, border_color);
	Image m = w;
	Point p1(radius, radius);
	SetHotSpots(m, p1, (Point)r.BottomRight() - p1);
	return m;
}

Image MakeButton(int radius, Color face, int border_width, Color border_color, dword corner)
{
	return MakeButton(radius, CreateImage(Size(DPI(10), DPI(5)), face), border_width, border_color, corner);
}

Image Hot3(const Image& m)
{
	Size sz = m.GetSize();
	return WithHotSpots(m, sz.cx / 3, sz.cy / 3, sz.cx - sz.cx / 3, sz.cy - sz.cy / 3);
}

Image ChHot(const Image& m, int n)
{
	return WithHotSpots(m, DPI(n), DPI(n), 0, 0);
}

Color AvgColor(const Image& m, const Rect& rr)
{
	int r = 0;
	int g = 0;
	int b = 0;
	int n = 0;
	for(int y = rr.top; y < rr.bottom; y++)
		for(int x = rr.left; x < rr.right; x++) {
			RGBA c = m[y][x];
			Unmultiply(&c, &c, 1);
			if(c.a > 20) {
				r += c.r;
				g += c.g;
				b += c.b;
				n++;
			}
		}
	return n ? Color(r / n, g / n, b / n) : SWhite();
}

Color AvgColor(const Image& m, int margin)
{
	return AvgColor(m, Rect(m.GetSize()).Deflated(margin));
}



Color GetInk(const Image& m)
{
	RGBA avg = AvgColor(m);
	Color ink = SBlack();
	int   best = 0;
	for(RGBA c : m) {
		Unmultiply(&c, &c, 1);
		if(c.a > 100) {
			c.a = 255;
			int q = Grayscale(abs(c.r - avg.r), abs(c.g - avg.g), abs(c.b - avg.b));
			if(q > best) {
				best = q;
				ink = c;
			}
		}
	}
	return ink;
}

int GetRoundness(const Image& m)
{
	Size isz = m.GetSize();
	int bestd = 0, besth = 0;
	int di = 0, hi = 0;
	int hy = isz.cy / 2;
	RGBA avg = AvgColor(m);
	auto Chk = [&](int x, int y, int& best, int& besti) {
		if(x < isz.cx && y < isz.cy) {
			RGBA c = m[y][x];
			Unmultiply(&c, &c, 1);
			if(c.a > 100) {
				int q = Grayscale(abs(c.r - avg.r), abs(c.g - avg.g), abs(c.b - avg.b));
				if(q > best) {
					best = q;
					besti = x;
				}
			}
		}
	};
	for(int i = 0; i < 8; i++) {
		Chk(i, hy, besth, hi);
		Chk(i, i, bestd, di);
	}
	return max(di - hi, 0);
}

static Value sSample;

void SetChameleonSample(const Value& m, bool once)
{
	if(!once || IsNull(sSample))
		sSample = m;
}

Value GetChameleonSample()
{
	return sSample;
}

static Image sWithLine(Image m, Color c, int w, int at)
{
	ImageBuffer ib(m);
	for(int x = 0; x < w; x++)
		for(int y = 0; y < ib.GetHeight(); y++)
			ib[y][x + at] = c;
	return ib;
}

Image WithLeftLine(const Image& m, Color c, int w)
{
	return sWithLine(m, c, w, 0);
}

Image WithRightLine(const Image& m, Color c, int w)
{
	return sWithLine(m, c, w, m.GetWidth() - w);
}

void ChSynthetic(Image button100x100[4], Color text[4])
{
	int roundness = DPI(3);
	Color ink = SColorText();
	for(int i = 0; i < 4; i++) {
		Image m = button100x100[i];
		if(i == 0) {
			ink = GetInk(m);
			roundness = GetRoundness(m) ? DPI(3) : 0;
			DDUMP(GetRoundness(m));
			CtrlsImg::Set(CtrlsImg::I_EFE, WithHotSpots(MakeButton(roundness, SColorPaper(), DPI(1), ink), DPI(3), DPI(1), 0, 0));
			CtrlsImg::Set(CtrlsImg::I_VE, WithHotSpots(MakeButton(DPI(0), SColorPaper(), DPI(1), ink), DPI(2), DPI(2), 0, 0));
			EditField::StyleDefault().Write().edge[CTRL_DISABLED] = WithHotSpots(MakeButton(roundness, SColorFace(), DPI(1), ink), DPI(3), DPI(1), 0, 0);
			EditField::StyleDefault().Write().activeedge = true;
		}
		Size sz = m.GetSize();
		m = Crop(m, sz.cx / 8, sz.cy / 8, 6 * sz.cx / 8, 6 * sz.cy / 8);
		{
			auto Set = [&](Button::Style& s, const Image& arrow = Null) {
				Value l = MakeButton(0, m, DPI(1), ink, 0);
				s.look[i] = IsNull(l) ? l : ChLookWith(l, arrow);
			};
			Set(Button::StyleScroll().Write());
			Set(Button::StyleEdge().Write());
			Set(Button::StyleLeftEdge().Write());
			ScrollBar::Style& s = ScrollBar::StyleDefault().Write();
			
			Set(s.up, CtrlsImg::UA());
			Set(s.down, CtrlsImg::DA());
			Set(s.left, CtrlsImg::LA());
			Set(s.right, CtrlsImg::RA());
		}
		{
			MultiButton::Style& s = MultiButton::StyleDefault().Write();
			s.clipedge = true;
			s.border = s.trivialborder = 0;

			s.left[i] = MakeButton(roundness, m, DPI(1), ink, CORNER_TOP_LEFT|CORNER_BOTTOM_LEFT);
			s.trivial[i] = s.look[i] = s.right[i] = MakeButton(roundness, m, DPI(1), ink, CORNER_TOP_RIGHT|CORNER_BOTTOM_RIGHT);
			auto Middle = [&](Image m) {
				ImageBuffer ib(m);
				for(int y = 0; y < DPI(1); y++)
					for(int x = 0; x < ib.GetWidth(); x++) {
						ib[y][x] = ink;
						ib[ib.GetHeight() - y - 1][x] = ink;
					}
				return WithHotSpot(ib, DPI(1), DPI(1));
			};
			s.lmiddle[i] = Middle(WithRightLine(m, ink));
			s.rmiddle[i] = Middle(WithLeftLine(m, ink));
			s.monocolor[i] = s.fmonocolor[i] = text[i];
			for(int i = 0; i < 4; i++)
				s.edge[i] = EditField::StyleDefault().edge[i];
			s.margin = Rect(DPI(3), 2, DPI(1), 2);
			s.activeedge = true;
		}
		{
			SpinButtons::Style& sp = SpinButtons::StyleDefault().Write();
			if(i == 0)
				sp.dec = sp.inc = Button::StyleNormal();
			auto Spin = [&](dword corners, const Image& sm) {
				return ChLookWith(WithLeftLine(MakeButton(roundness, m, 0, Black(), corners), ink), sm, text[i]);
			};
			sp.inc.look[i] = Spin(CORNER_TOP_RIGHT, CtrlImg::spinup());
			sp.dec.look[i] = Spin(CORNER_BOTTOM_RIGHT, CtrlImg::spindown());
		}
		if(i == CTRL_DISABLED) {
			ProgressIndicator::Style& s = ProgressIndicator::StyleDefault().Write();
			s.hlook = MakeButton(roundness, m, DPI(1), ink);
			s.hchunk = MakeButton(roundness, SColorHighlight(), DPI(1), ink);
			s.bound = true;
			s.nomargins = true;
		}
	}
}

}
