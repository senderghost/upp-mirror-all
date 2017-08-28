#include <CtrlLib/CtrlLib.h>

#define IMAGECLASS FontImg
#define IMAGEFILE <MakeFont/font.iml>
#include <Draw/iml.h>

using namespace Upp;

GUI_APP_MAIN
{
	for(int i = 0; i < FontImg::GetCount(); i++) {
		Image m = FontImg::Get(i);
		String ln;
		for(int y = 0; y < 8; y++) {
			byte b = 0;
			for(int x = 0; x < 8; x++) {
				b = (b << 1) | (m[y][x].r < 128 ? 1 : 0);
			}
			ln << Format("0x%02x,", b);
		}
		LOG(ln);
	}
}

void PNGtoIML()
{
	Image img = StreamRaster::LoadFileAny("C:/u/exsrc/Potash_8x8.png");
	int ch = 0;
	for(int y = 0; y < 128; y += 8)
		for(int x = 0; x < 128; x += 8) {
			ImageBuffer ib(8, 8);
			for(int i = 0; i < 8; i++)
				for(int j = 0; j < 8; j++)
					ib[i][j] = img[y + i][x + j].g == 255 ? Black() : White();
			PNGEncoder().SaveFile("d:/xxx/font/c" + Format("%03d", ch++) + ".png", ib);
		}
}