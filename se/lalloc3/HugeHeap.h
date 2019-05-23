struct HugeHeapDetail {
	static BlkHeader_<4096> freelist[2];
	
	static void LinkFree(BlkHeader_<4096> *h)     { Dbl_LinkAfter(h, &freelist[h->GetSize() >= 16]); }
	static void NewFreeSize(BlkHeader_<4096> *h)  {}
};

BlkHeader_<4096> HugeHeapDetail::freelist[2];

struct HugeHeap : BlkHeap<HugeHeapDetail, 4096> {
	void *Alloc(size_t count);
	void  Free(void *ptr);
	bool  FreeSmallEmpty(int) { return false; }
	
	static size_t huge_4KB_count; // total number of 4KB pages in small/large/huge blocks
	static size_t free_4KB; // empty 4KB pages
	static size_t big_size; // blocks >~64KB
	static size_t big_count;
	static size_t sys_size;  // blocks allocated directly from system (included in big too)
	static size_t sys_count;
	static size_t huge_chunks; // 32MB master pages
};

size_t HugeHeap::huge_4KB_count;
size_t HugeHeap::free_4KB;
size_t HugeHeap::big_size;
size_t HugeHeap::big_count;
size_t HugeHeap::sys_size;
size_t HugeHeap::sys_count;
size_t HugeHeap::huge_chunks;

void *HugeHeap::Alloc(size_t count) // count in 4kb pages
{
	ASSERT(count);

	huge_4KB_count += count;
	
	if(!D::freelist[0].next) { // initialization
		for(int i = 0; i < 2; i++)
			Dbl_Self(&D::freelist[i]);
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
			BlkHeader *l = &D::freelist[i];
			BlkHeader *h = l->next;
			while(h != l) {
				word sz = h->GetSize();
				if(sz >= count)
					return MakeAlloc(h, wcount);
				h = h->next;
			}
		}

		if(!FreeSmallEmpty(wcount)) { // try to coalesce 4KB small free blocks back to huge storage
			AddChunk((BlkHeader *)SysAllocRaw(8192 * 4096, 0), 8192); // failed, add 32MB from the system
			huge_chunks++;
		}
	}
	Panic("Out of memory");
	return NULL;
}

void HugeHeap::Free(void *ptr)
{
	BlkHeader *h = (BlkHeader *)ptr;
	if(h->size == 0) {
		byte *sysblk = (byte *)h - 4096;
		size_t count = *((size_t *)sysblk);
		SysFreeRaw(sysblk, count);
		huge_4KB_count -= count;
		sys_count--;
		sys_size -= 4096 * count;
		return;
	}
	huge_4KB_count -= h->GetSize();
	BlkHeap::Free(h);
}
