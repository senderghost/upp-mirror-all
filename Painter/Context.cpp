#include "Painter.h"

namespace Upp {

void BufferPainter::BeginOp()
{
	attr.onpath = false;
	attrstack.Add(attr);
	attr.hasclip = false;
}

void BufferPainter::EndOp()
{
	if(attrstack.GetCount() == 0) {
		NEVER_("Painter::End: attribute stack is empty");
		return;
	}
	DoPath();
	path_info->attr = attr = attrstack.Top();
	attrstack.Drop();
	if(clip.GetCount() != attr.cliplevel || attr.mask || attr.onpath)
		Finish();
	clip.SetCount(attr.cliplevel);
	if(attr.mask)
		FinishMask();
	if(attr.onpath) {
		attr.onpath = false;
		onpath = pick(onpathstack.Top());
		onpathstack.Drop();
		pathlen = pathlenstack.Pop();
	}
}

void   BufferPainter::TransformOp(const Xform2D& m)
{
	DoPath();
	ASSERT_(path_info->path.Top().IsEmpty(), "Cannot change transformation during path definition");
	path_info->attr.mtx = attr.mtx = m * attr.mtx;
//	path_info->attr.mtx_serial = ++mtx_serial;
}

void BufferPainter::OpacityOp(double o)
{
	DoPath();
	path_info->attr.opacity *= o;
	if(path_info->path.Top().IsEmpty())
		attr.opacity *= o;
}

void BufferPainter::LineCapOp(int linecap)
{
	DoPath();
	path_info->attr.cap = linecap;
	if(path_info->path.Top().IsEmpty())
		attr.cap = linecap;
}

void BufferPainter::LineJoinOp(int linejoin)
{
	DoPath();
	path_info->attr.join = linejoin;
	if(path_info->path.Top().IsEmpty())
		attr.join = linejoin;
}

void BufferPainter::MiterLimitOp(double l)
{
	DoPath();
	path_info->attr.miter_limit = l;
	if(path_info->path.Top().IsEmpty())
		attr.miter_limit = l;
}

void BufferPainter::EvenOddOp(bool evenodd)
{
	DoPath();
	path_info->attr.evenodd = evenodd;
	if(path_info->path.Top().IsEmpty())
		attr.evenodd = evenodd;
}

void BufferPainter::InvertOp(bool invert)
{
	DoPath();
	path_info->attr.invert = invert;
	if(path_info->path.Top().IsEmpty())
		attr.invert = invert;
}

void BufferPainter::DashOp(const Vector<double>& dash, double start)
{
	DoPath();
	auto& pa = path_info->attr;
	pa.dash = clone(dash);
	pa.dash_start = start;
	if(path_info->path.Top().IsEmpty()) {
		attr.dash = pa.dash;
		attr.dash_start = start;
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
	DoPath();
	ColorStop0(path_info->attr, pos, color);
	if(path_info->path.Top().IsEmpty())
		ColorStop0(attr, pos, color);
}

void BufferPainter::ClearStopsOp()
{
	DoPath();
	auto& pa = path_info->attr;
	pa.stop.Clear();
	pa.stop_color.Clear();
	if(path_info->path.Top().IsEmpty()) {
		auto& a = attr;
		a.stop.Clear();
		a.stop_color.Clear();
	}
}

BufferPainter::BufferPainter(ImageBuffer& ib, int mode)
:	ib(ib),
	mode(mode),
	rasterizer(ib.GetWidth(), ib.GetHeight(), mode == MODE_SUBPIXEL)
{
	paths.Alloc(BATCH_SIZE);
	path_info = paths;

	ClearPath();

	render_cx = ib.GetWidth();
	if(mode == MODE_SUBPIXEL) {
		render_cx *= 3;
		subpixel.Alloc(render_cx + 30);
	}
	auto& a = attr;
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
	path_info->attr = attr;
	
	gradientn = Null;
	
	dopreclip = false;
	jobcount = 0;
	
	size = ib.GetSize();
}

BufferPainter::BufferPainter(PainterTarget& t, double tolerance)
:	BufferPainter(dummy, MODE_ANTIALIASED)
{
	alt = &t;
	alt_tolerance = tolerance;
	dummy.Create(1, 1);
}

}
