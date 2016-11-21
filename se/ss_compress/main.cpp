#include <CtrlLib/CtrlLib.h>
#include <plugin/lzma/lzma.h>

using namespace Upp;

GUI_APP_MAIN
{
	String fn = "c:/xxx/ide.png";
	
	DDUMP(GetFileLength(fn));
	
	Image m = StreamRaster::LoadFileAny(fn);
	
	DDUMP(m.GetSize());
	
	String bin((byte *)~m, m.GetLength() * 4);
	
	DDUMP(bin.GetCount());
	
	DDUMP(ZCompress(bin).GetCount());
	DDUMP(LZMACompress(bin).GetCount());
	
	VectorMap<Color, int> histogram;
	
	for(Color c : m) {
		histogram.GetAdd(c, 0)++;
	}
	
	SortByValue(histogram, std::greater<int>());
	
	DDUMPM(histogram);
}
