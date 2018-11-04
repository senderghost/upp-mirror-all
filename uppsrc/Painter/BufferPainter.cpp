#include "Painter.h"

namespace Upp {

void BufferPainter::EndOp()
{
	PainterFrontend::EndOp();

#ifdef PAINTER_CLIPS
	clip.SetCount(attr.cliplevel);
	if(attr.mask)
		FinishMask();
	if(attr.onpath) {
		attr.onpath = false;
		onpath = pick(onpathstack.Top());
		onpathstack.Drop();
		pathlen = pathlenstack.Pop();
	}
#endif
}


BufferPainter::BufferPainter(RGBA *pixels, Size sz, int mode, int offsety)
:	size(sz)
{
	RTIMING("INIT");
	backend.Init(pixels, size, mode, offsety);
	
	gradientn = Null;
	
	dopreclip = false;
}

BufferPainter::BufferPainter(ImageBuffer& ib, int mode)
:	BufferPainter(~ib, ib.GetSize(), mode)
{}

static RGBA sPixelDummy[1];

BufferPainter::BufferPainter(LinearPathConsumer& t, double tolerance)
:	BufferPainter(sPixelDummy, Size(1, 1), MODE_ANTIALIASED)
{
	alt = &t;
	alt_tolerance = tolerance;
}

};