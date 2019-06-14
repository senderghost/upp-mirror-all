#include <Core/Core.h>

using namespace Upp;

namespace Upp {
void *SysAllocRaw(size_t size, size_t reqsize);
void  SysFreeRaw(void *ptr, size_t size);
};

#include "BlkHeap.h"
#include "HugeHeap.h"
#include "LargeHeap.h"

void DumpFreeList(bool check = false)
{
#if 0
	LOG("FreeList ------------");
	BlkHeader *h = freelist->next;
	while(h != freelist) {
		LOG(h << " " << h->GetSize());
		if(check)
			ASSERT(h->GetSize() == 8192);
		h = h->next;
	}
#endif
}

int xT = 123;

CONSOLE_APP_MAIN
{
	for(size_t isz : { 10, 4000, 100000 }) {
		RLOG("=============================================");
		RDUMP(isz);
		void *ptr = MemoryAlloc(isz);
		for(size_t sz : { 10, 5000, 10000, 2000, 40000 }) {
			RDUMP(sz);
			RDUMP(MemoryTryRealloc(ptr, sz));
			RDUMP(sz);
			RLOG("--------");
		}
		MemoryFree(ptr);
	}
}