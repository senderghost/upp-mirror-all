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
//	HugeHeap h;
//	void *ptr = h.Alloc(50);
//	h.Free(ptr);
	
	LargeHeap l;
	l.Init();
	void *lptr = l.Alloc(50);
	l.TryRealloc(lptr, 60);
	l.TryRealloc(lptr, 40);
	l.Free(lptr);
	lptr = l.Alloc(100);
	l.Free(lptr);
}
