struct LargeHeapDetail {
	BlkHeader_<256> freelist[65]; // all blocks >16KB are in freelist[64]
	
	void LinkFree(BlkHeader_<256> *h) { Dbl_LinkAfter(h, freelist + min((int)h->GetSize(), 64)); }
	void NewFreeSize(BlkHeader_<256> *h)  {
		// TODO: free block to Huge
	}
};

struct LargeHeap : BlkHeap<LargeHeapDetail, 256> {
	void *Alloc(int count);
	void  Free(void *ptr) { BlkHeap::Free((BlkHeader *)ptr); }
	void  Init();
};

void LargeHeap::Init()
{
	for(int i = 0; i < 65; i++)
		Dbl_Self(&D::freelist[i]);
}

void *LargeHeap::Alloc(int count)
{
	word wcount = (word)count;
	
	int i0 = min(count, 64);
	for(int pass = 0; pass < 2; pass++) {
		for(int i = i0; i < 65; i++) {
			BlkHeader *l = &D::freelist[i];
			BlkHeader *h = l->next;
			while(h != l) {
				word sz = h->GetSize();
				if(sz >= count)
					return MakeAlloc(h, count);
				h = h->next;
			}
		}
		// TODO: Mutex, Alloc from the Huge
		byte *b = (byte *)SysAllocRaw(256 * 256, 0);
		AddChunk((BlkHeader *)(b + 256), 255);
		i0 = 64; // because the new block is there
		// TODO: Large header
	}
	Panic("Out of memory");
	return NULL;
}
