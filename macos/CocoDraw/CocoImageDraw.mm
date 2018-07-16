#include "MMDraw.h"

namespace Upp {

void ImageDraw::Init(int cx, int cy)
{
	ib.Create(cx, cy);

	static CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); // TODO: This is probably wrong...

	SystemDraw::Init(CGBitmapContextCreateWithData(~ib, cx, cy, 8, cx * sizeof(RGBA),
	                                               colorSpace, kCGImageAlphaPremultipliedFirst,
	                                               NULL, NULL), cy);
}

ImageDraw::ImageDraw(Size sz)
{
	Init(sz.cx, sz.cy);
}

ImageDraw::ImageDraw(int cx, int cy)
{
	Init(cx, cy);
}

Draw& ImageDraw::Alpha()
{
	if(!alpha)
		alpha.Create(ib.GetSize());
	return *alpha;
}

ImageDraw::~ImageDraw()
{
	CGContextRelease(cgHandle);
}

Image ImageDraw::GetStraight()
{
	if(alpha) {
		RGBA *e = ib.End();
		RGBA *t = ib;
		RGBA *s = alpha->ib;
		while(t < e) {
			t->a = s->r;
			s++;
			t++;
		}
	}
	return Image(ib);
}

ImageDraw::operator Image()
{
	if(alpha)
		return Premultiply(GetStraight());
	return Image(ib);
}

};

