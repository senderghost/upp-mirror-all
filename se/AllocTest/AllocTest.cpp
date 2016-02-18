#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	for(int i = 0; i < 50000; i++) {
		size_t sz = i;
		void *ptr = MemoryAllocSz(sz);
		RLOG("requested " << i << ", ptr: " << ptr << ", ends: " << (byte *)ptr + sz << ", real size " << sz);
		void *ptr1 = ptr;
		ptr = MemoryAllocSz(sz);
		RLOG("requested " << i << ", ptr: " << ptr << ", ends: " << (byte *)ptr + sz << ", real size " << sz);
		MemoryFree(ptr);
		MemoryFree(ptr1);
	}
}
