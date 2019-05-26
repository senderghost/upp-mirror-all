#include <Core/Core.h>

namespace Upp {

#ifdef UPP_HEAP

#include "HeapImp.h"

// this part reserves 32 MB chunks form the system and then serves as 4KB rounded allocator
// used as manager of large memory blocks. 4KB and 64KB blocks are allocated from here too
// also able to deal with blocks >32MB, those are directly allocated / freed from system

BlkHeader_<4096> HugeHeapDetail::freelist[2][1]; // only single global Huge heap...
Heap::HugePage *Heap::huge_pages;

void *Heap::HugeAlloc(size_t count) // count in 4kb pages
{
	ASSERT(count);

	huge_4KB_count += count;
	
	if(!D::freelist[0]->next) { // initialization
		for(int i = 0; i < 2; i++)
			Dbl_Self(D::freelist[i]);
	}
		
	if(count > 8192) { // we are wasting whole 4KB page to store just 4 bytes, but this is >32MB after all..
		byte *sysblk = (byte *)SysAllocRaw((count + 1) * 4096, 0);
		BlkHeader *h = (BlkHeader *)(sysblk + 4096);
		h->size = 0;
		*((size_t *)sysblk) = count;
		sys_count++;
		sys_size += 4096 * count;
		return h;
	}
	
	word wcount = (word)count;
	
	for(int pass = 0; pass < 2; pass++) {
		for(int i = count >= 16; i < 2; i++) {
			BlkHeader *l = D::freelist[i];
			BlkHeader *h = l->next;
			while(h != l) {
				word sz = h->GetSize();
				if(sz >= count)
					return MakeAlloc(h, wcount);
				h = h->next;
			}
		}

// FIXME:
		if(!FreeSmallEmpty(wcount)) { // try to coalesce 4KB small free blocks back to huge storage
			void *ptr = SysAllocRaw(8192 * 4096, 0);
			HugePage *pg = (HugePage *)MemoryAllocPermanent(sizeof(HugePage));
			pg->page = ptr;
			pg->next = huge_pages;
			huge_pages = pg;
			AddChunk((BlkHeader *)ptr, 8192); // failed, add 32MB from the system
			huge_chunks++;
		}
	}
	Panic("Out of memory");
	return NULL;
}

int Heap::HugeFree(void *ptr)
{
	BlkHeader *h = (BlkHeader *)ptr;
	if(h->size == 0) {
		RTIMING("Sys Free");
		byte *sysblk = (byte *)h - 4096;
		size_t count = *((size_t *)sysblk);
		SysFreeRaw(sysblk, count);
		huge_4KB_count -= count;
		sys_count--;
		sys_size -= 4096 * count;
		RDUMP(4096 * count);
		return 0;
	}
	RTIMING("Blk Free");
	huge_4KB_count -= h->GetSize();
	return BlkHeap::Free(h)->GetSize();
}

bool Heap::HugeTryRealloc(void *ptr, size_t count)
{
	return BlkHeap::TryRealloc(ptr, count);
}

#endif

}