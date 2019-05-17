#include <Core/Core.h>

namespace Upp {

#ifdef UPP_HEAP

#include "HeapImp.h"

// this part reserves 32 MB chunks form the system and then serves as 4KB rounded allocator
// used as manager of large memory blocks. 4KB and 64KB blocks are allocated from here too
// also able to deal with blocks >32MB, those are directly allocated / freed from system

Heap::HugeHeader Heap::hsmall[1]; // blocks smaller than 64KB (16 * 4KB)
Heap::HugeHeader Heap::hlarge[1]; // blocks >= 16 * 4 KB

inline
void Heap::HugeHeader::UnlinkFree()
{
	Dbl_Unlink(this);
}

inline
void Heap::HugeHeader::LinkFree()
{
	Dbl_LinkAfter(this, GetSize() < 16 ? hsmall : hlarge);
}

void *Heap::HugeAlloc(size_t count) // count in 4kb pages
{
	ASSERT(count);

	huge_4KB_count += count;
	
	if(!hsmall->next) { // initialization
		hsmall->next = hsmall->prev = hsmall;
		hlarge->next = hlarge->next = hlarge;
	}
		
	if(count > 8192) { // we are wasting whole 4KB page to store just 4 bytes, but this is >32MB after all..
		byte *sysblk = (byte *)SysAllocRaw((count + 1) * 4096, 0);
		HugeHeader *h = (HugeHeader *)(sysblk + 4096);
		h->size = 0;
		*((size_t *)sysblk) = count;
		sys_count++;
		sys_size += 4096 * count;
		return h;
	}
	
	word wcount = (word)count;
	
	for(int pass = 0; pass < 2; pass++) {
		HugeHeader *l = count < 16 ? hsmall : hlarge;
		for(;;) {
			HugeHeader *h = l->next;
			while(h != l) {
				word sz = h->GetSize();
				if(sz >= count) {
					h->UnlinkFree();
					h->SetFree(false);
					if(sz > count) { // split the block
						HugeHeader *h2 = (HugeHeader *)((byte *)h + 4096 * count);
						word nsz = sz - wcount;
						h2->SetFree(true);
						h2->SetLast(h->IsLast());
						h2->SetSize(nsz);
						h2->SetPrevSize(wcount);
						h2->SetNextPrevSz();
						h2->LinkFree();
	
						h->SetSize(wcount);
						h->SetLast(false);
					}
					return h;
				}
				h = h->next;
			}
			if(l == hlarge)
				break;
			l = hlarge;
		}

		if(!FreeSmallEmpty(wcount)) { // try to coalesce 4KB small free blocks back to huge storage
			HugeHeader *h = (HugeHeader *)SysAllocRaw(8192 * 4096, 0); // failed, get 32MB from the system
			h->SetSize(8192);
			h->SetPrevSize(0); // is first
			h->SetLast(true);
			h->SetFree(true);
			h->LinkFree();
			huge_chunks++;
		}
	}
	Panic("Out of memory");
	return NULL;
}

int Heap::HugeFree(void *ptr)
{
	HugeHeader *h = (HugeHeader *)ptr;
	if(h->size == 0) {
		byte *sysblk = (byte *)h - 4096;
		size_t count = *((size_t *)sysblk);
		SysFreeRaw(sysblk, count);
		huge_4KB_count -= count;
		sys_count--;
		sys_size -= 4096 * count;
		return 0;
	}
	huge_4KB_count -= h->GetSize();
	if(!h->IsLast()) { // try to join with next header if it is free
		HugeHeader *nh = h->GetNextHeader();
		if(nh->IsFree()) {
			h->SetLast(nh->IsLast());
			nh->UnlinkFree();
			word nsz = h->GetSize() + nh->GetSize();
			ASSERT(nsz <= 8192);
			h->SetSize(nsz);
			h->SetNextPrevSz();
		}
	}
	if(!h->IsFirst()) { // try to join with previous header if it is free
		HugeHeader *ph = h->GetPrevHeader();
		if(ph->IsFree()) {
			word nsz = ph->GetSize() + h->GetSize();
			ASSERT(nsz <= 8192);
			ph->SetSize(nsz);
			ph->SetLast(h->IsLast());
			ph->SetNextPrevSz();
			return nsz;
		}
	}
	h->SetFree(true);
	h->LinkFree(); // was not joined with previous header
	return h->GetSize();
}

#endif

}