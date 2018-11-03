#include "Painter.h"

namespace Upp {

void BufferPainter::EndOp()
{
	PainterFrontend::EndOp();

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


BufferPainter::BufferPainter(RGBA *pixels, Size sz, int mode)
:	pixels(pixels), size(sz), rasterizer(sz.cx, sz.cy, mode == MODE_SUBPIXEL)
{
	RTIMING("INIT");
	render_cx = sz.cx;
	if(mode == MODE_SUBPIXEL) {
		render_cx *= 3;
		subpixel.Alloc(render_cx + 30);
	}
	
	gradientn = Null;
	
	dopreclip = false;
}

BufferPainter::BufferPainter(ImageBuffer& ib, int mode)
:	BufferPainter(~ib, ib.GetSize(), mode)
{}

static RGBA sPixelDummy[1];

BufferPainter::BufferPainter(PainterTarget& t, double tolerance)
:	BufferPainter(sPixelDummy, Size(1, 1), MODE_ANTIALIASED)
{
	alt = &t;
	alt_tolerance = tolerance;
}

};