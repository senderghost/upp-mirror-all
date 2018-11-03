#include "Painter.h"

namespace Upp {

void PainterFrontend::BeginOp()
{
	attr.onpath = false;
	attrstack.Add(attr);
	attr.hasclip = false;
}

void PainterFrontend::EndOp()
{
	if(attrstack.GetCount() == 0) {
		NEVER_("Painter::End: attribute stack is empty");
		return;
	}
	pathattr = attr = attrstack.Top();
	attrstack.Drop();
}

void   PainterFrontend::TransformOp(const Xform2D& m)
{
	ASSERT_(IsNull(current), "Cannot change transformation during path definition");
	pathattr.mtx = attr.mtx = m * attr.mtx;
}

void PainterFrontend::OpacityOp(double o)
{
	pathattr.opacity *= o;
	if(IsNull(current))
		attr.opacity *= o;
}

void PainterFrontend::LineCapOp(int linecap)
{
	pathattr.cap = linecap;
	if(IsNull(current))
		attr.cap = linecap;
}

void PainterFrontend::LineJoinOp(int linejoin)
{
	pathattr.join = linejoin;
	if(IsNull(current))
		attr.join = linejoin;
}

void PainterFrontend::MiterLimitOp(double l)
{
	pathattr.miter_limit = l;
	if(IsNull(current))
		attr.miter_limit = l;
}

void PainterFrontend::EvenOddOp(bool evenodd)
{
	pathattr.evenodd = evenodd;
	if(IsNull(current))
		attr.evenodd = evenodd;
}

void PainterFrontend::InvertOp(bool invert)
{
	pathattr.invert = invert;
	if(IsNull(current))
		attr.invert = invert;
}

void PainterFrontend::DashOp(const Vector<double>& dash, double start)
{
	pathattr.dash <<= dash;
	pathattr.dash_start = start;
	if(IsNull(current)) {
		attr.dash <<= dash;
		attr.dash_start = start;
	}
}

void PainterFrontend::ColorStop0(Attr& a, double pos, const RGBA& color)
{
	pos = minmax(pos, 0.0, 1.0);
	int i = FindLowerBound(a.stop, pos);
	a.stop.Insert(i, pos);
	a.stop_color.Insert(i, color);
}

void PainterFrontend::ColorStopOp(double pos, const RGBA& color)
{
	ColorStop0(pathattr, pos, color);
	if(IsNull(current))
		ColorStop0(attr, pos, color);
}

void PainterFrontend::ClearStopsOp()
{
	pathattr.stop.Clear();
	pathattr.stop_color.Clear();
	if(IsNull(current)) {
		attr.stop.Clear();
		attr.stop_color.Clear();
	}
}

PainterFrontend::PainterFrontend()
{
	ClearPath();
	attr.cap = LINECAP_BUTT;
	attr.join = LINEJOIN_MITER;
	attr.miter_limit = 4;
	attr.evenodd = false;
	attr.hasclip = false;
	attr.cliplevel = 0;
	attr.dash_start = 0.0;
	attr.opacity = 1.0;
	attr.mask = false;
	attr.invert = false;
	pathattr = attr;
}

}
