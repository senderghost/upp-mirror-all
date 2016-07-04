#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	const char *path = "C:/xxx/log/local5.info";
	path = "C:/xxx/fav.xml";
	Huge h;
	FileIn in(path);
	for(;;) {
		int len = in.Get(h.AddChunk(), h.CHUNK);
		if(len < h.CHUNK) {
			h.Finish(len);
			break;
		}
	}
	
	DDUMP(h.GetSize());
	
	ASSERT(h.Get() == LoadFile(path));
}
