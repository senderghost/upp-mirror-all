#include "Core.h"

NAMESPACE_UPP

void RGBtoHSV(double r, double g, double b, double& h, double& s, double& v)
{
	double delta;
	if((v = max(r, max(g, b))) == 0 || (delta = v - min(r, min(g, b))) == 0)
	{
		h = s = 0;
		return;
	}
	s = delta / v;
	delta *= 6;
	if(g == v)
		h = 1 / 3.0 + (b - r) / delta;
	else if(b == v)
		h = 2 / 3.0 + (r - g) / delta;
	else
		if((h = (g - b) / delta) < 0)
			h += 1;
}

void HSVtoRGB(double h, double s, double v, double& r, double& g, double& b)
{
	if(s == 0)
	{
		r = g = b = v;
		return;
	}
	double rem = fmod(h *= 6, 1);
	double p = v * (1 - s);
	double q = v * (1 - s * rem);
	double t = v * (1 - s * (1 - rem));
	switch(ffloor(h))
	{
	default: NEVER(); // invalid color!
	case 6:
	case 0: r = v; g = t; b = p; break;
	case 1: r = q; g = v; b = p; break;
	case 2: r = p; g = v; b = t; break;
	case 3: r = p; g = q; b = v; break;
	case 4: r = t; g = p; b = v; break;
	case -1:
	case 5: r = v; g = p; b = q; break;
	}
}

Color HsvColorf(double h, double s, double v)
{
	double r, g, b;
	HSVtoRGB(h, s, v, r, g, b);
	return Color(min(int(r * 255), 255), min(int(g * 255), 255), min(int(b * 255), 255));
}

static GLOBAL_VAR(Vector<dword>, sStdColor);

void Color::SetStdColor(int i, dword color) {
	sStdColor().At(i) = color;
}

dword Color::Get() const
{
	if(IsNullInstance()) return 0;
	dword c = color;
	if(color & 0x80000000) {
		int palix(color & 0xffffff);
		const Vector<dword>& stdclr = sStdColor();
		if(palix < stdclr.GetCount())
			c = stdclr[palix];
	}
	return c & 0xffffff;
}

Color::operator RGBA() const
{
	RGBA color;
	if(IsNullInstance())
		Zero(color);
	else {
		color.r = GetR();
		color.g = GetG();
		color.b = GetB();
		color.a = 255;
	}
	return color;
}

Color::Color(RGBA rgba)
{
	if(rgba.a == 0)
		color = 0xffffffff;
	else
		color = RGB(rgba.r, rgba.g, rgba.b);
}

template<>
String AsString(const Color& c) {
	if(IsNull(c))
		return "Color(Null)";
	return Format("Color(%d, %d, %d)", c.GetR(), c.GetG(), c.GetB());
}

String ColorToHtml(Color color)
{
	return Format("#%02X%02X%02X",  color.GetR(), color.GetG(), color.GetB());
}

Color Blend(Color c1, Color c2, int alpha)
{
	int a = (alpha >> 7) + alpha;
	return Color(min(((a * (c2.GetR() - c1.GetR())) >> 8) + c1.GetR(), 255),
	             min(((a * (c2.GetG() - c1.GetG())) >> 8) + c1.GetG(), 255),
	             min(((a * (c2.GetB() - c1.GetB())) >> 8) + c1.GetB(), 255));
}


INITBLOCK {
	RichValue<Color>::Register();
}

END_UPP_NAMESPACE
