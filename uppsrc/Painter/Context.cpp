#include "Painter.h"

namespace Upp {

void BufferPainter::BeginOp()
{
	attr.Write().onpath = false;
	attrstack.Add(attr);
	attr.Write().hasclip = false;
}

void BufferPainter::EndOp()
{
	if(attrstack.GetCount() == 0) {
		NEVER_("Painter::End: attribute stack is empty");
		return;
	}
	path_info.Write().attr = attr = attrstack.Top();
	attrstack.Drop();
	const auto& a = ~attr;
	if(clip.GetCount() != a.cliplevel || a.mask || a.onpath)
		FinishPathJob();
	clip.SetCount(a.cliplevel);
	if(a.mask)
		FinishMask();
	if(a.onpath) {
		attr.Write().onpath = false;
		onpath = pick(onpathstack.Top());
		onpathstack.Drop();
		pathlen = pathlenstack.Pop();
	}
}

void   BufferPainter::TransformOp(const Xform2D& m)
{
	ASSERT_(IsNull(current), "Cannot change transformation during path definition");
	
	Xform2D mm = m * attr->mtx;
	PathAttr().mtx = attr.Write().mtx = mm;
}

void BufferPainter::OpacityOp(double o)
{
	PathAttr().opacity *= o;
	if(IsNull(current))
		attr.Write().opacity *= o;
}

void BufferPainter::LineCapOp(int linecap)
{
	PathAttr().cap = linecap;
	if(IsNull(current))
		attr.Write().cap = linecap;
}

void BufferPainter::LineJoinOp(int linejoin)
{
	PathAttr().join = linejoin;
	if(IsNull(current))
		attr.Write().join = linejoin;
}

void BufferPainter::MiterLimitOp(double l)
{
	PathAttr().miter_limit = l;
	if(IsNull(current))
		attr.Write().miter_limit = l;
}

void BufferPainter::EvenOddOp(bool evenodd)
{
	PathAttr().evenodd = evenodd;
	if(IsNull(current))
		attr.Write().evenodd = evenodd;
}

void BufferPainter::InvertOp(bool invert)
{
	PathAttr().invert = invert;
	if(IsNull(current))
		attr.Write().invert = invert;
}

void BufferPainter::DashOp(const Vector<double>& dash, double start)
{
	auto& pa = PathAttr();
	pa.dash <<= dash;
	pa.dash_start = start;
	if(IsNull(current)) {
		auto& a = attr.Write();
		a.dash <<= dash;
		a.dash_start = start;
	}
}

void BufferPainter::ColorStop0(Attr& a, double pos, const RGBA& color)
{
	pos = minmax(pos, 0.0, 1.0);
	int i = FindLowerBound(a.stop, pos);
	a.stop.Insert(i, pos);
	a.stop_color.Insert(i, color);
}

void BufferPainter::ColorStopOp(double pos, const RGBA& color)
{
	ColorStop0(PathAttr(), pos, color);
	if(IsNull(current))
		ColorStop0(attr.Write(), pos, color);
}

void BufferPainter::ClearStopsOp()
{
	auto& pa = PathAttr();
	pa.stop.Clear();
	pa.stop_color.Clear();
	if(IsNull(current)) {
		auto& a = attr.Write();
		a.stop.Clear();
		a.stop_color.Clear();
	}
}

BufferPainter::BufferPainter(ImageBuffer& ib, int mode)
:	ib(ib),
	mode(mode),
	rasterizer(ib.GetWidth(), ib.GetHeight(), mode == MODE_SUBPIXEL)
{
	ClearPath();

	render_cx = ib.GetWidth();
	if(mode == MODE_SUBPIXEL) {
		render_cx *= 3;
		subpixel.Alloc(render_cx + 30);
	}
	auto& a = attr.Write();
	a.cap = LINECAP_BUTT;
	a.join = LINEJOIN_MITER;
	a.miter_limit = 4;
	a.evenodd = false;
	a.hasclip = false;
	a.cliplevel = 0;
	a.dash_start = 0.0;
	a.opacity = 1.0;
	a.mask = false;
	a.invert = false;
	PathAttr() = attr;
	
	gradientn = Null;
	
	dopreclip = false;
	jobcount = 0;
}

BufferPainter::BufferPainter(PainterTarget& t, double tolerance)
:	BufferPainter(dummy, MODE_ANTIALIASED)
{
	alt = &t;
	alt_tolerance = tolerance;
	dummy.Create(1, 1);
}

}
