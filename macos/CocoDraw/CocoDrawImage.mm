#include "CocoDraw.h"

#define LLOG(x)

namespace Upp {

CGImageRef createCGImage(const Image &img)
{
	CGDataProvider *dataProvider = CGDataProviderCreateWithData(NULL, ~img, img.GetLength() * sizeof(RGBA), NULL);
	static CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB(); // TODO: This is probably wrong...
	Upp::Size isz = img.GetSize();
    CGImageRef cg_img = CGImageCreate(isz.cx, isz.cy, 8, 32, isz.cx * sizeof(RGBA),
                                      colorSpace, kCGImageAlphaPremultipliedFirst,
                                      dataProvider, 0, false, kCGRenderingIntentDefault);
	CGDataProviderRelease(dataProvider);
	return cg_img;
}

struct ImageSysData {
	Image            img;
	CGImageRef       cgimg = NULL;
	
	void Init(const Image& img);
	~ImageSysData();
};

void ImageSysData::Init(const Image& m)
{
	img = m;
	cgimg = createCGImage(img);
	SysImageRealized(img);
}

ImageSysData::~ImageSysData()
{
	DLOG("destruct");
	SysImageReleased(img);
    CGImageRelease(cgimg);
}

struct ImageSysDataMaker : LRUCache<ImageSysData, int64>::Maker {
	Image img;

	virtual int64  Key() const                      { return img.GetSerialId(); }
	virtual int    Make(ImageSysData& object) const { object.Init(img); return img.GetLength(); }
};

void SystemDraw::SysDrawImageOp(int x, int y, const Image& img, Color color)
{
	GuiLock __;

	if(img.GetLength() == 0)
		return;

	ImageSysDataMaker m;
	static LRUCache<ImageSysData, int64> cache;
	LLOG("SysImage cache pixels " << cache.GetSize() << ", count " << cache.GetCount());
	m.img = IsNull(color) ? img : CachedSetColorKeepAlpha(img, color); // TODO: Can setcolor be optimized out? By masks e.g.?
	ImageSysData& sd = cache.Get(m);
	Size isz = img.GetSize();
	CGContextDrawImage(cgContext, Convert(x, y, isz.cx, isz.cy), sd.cgimg);
	cache.Shrink(4 * 1024 * 768, 1000); // Cache must be after Paint because of PaintOnly!
}

};