// This is used internally by U++ to manage large (64KB) and huge (32MB) blocks

struct BlkPrefix { // this part is at the start of Blk allocated block, client must not touch it
	word        prev_size; // top bit: free, rest: size of previous block in 4KB blocks
	word        size; // top bit: last block, rest: size of this block in 4KB blocks, 0 - sys
};

template <int BlkSize>
struct BlkHeader_ : BlkPrefix {
	BlkHeader_ *prev; // linked list of free blocks
	BlkHeader_ *next; // linked list of free blocks

	void  SetSize(word sz)           { size = (size & 0x8000) | sz; }
	void  SetPrevSize(word sz)       { prev_size = (prev_size & 0x8000) | sz; }
	void  SetFree(bool b)            { prev_size = b ? prev_size | 0x8000 : prev_size & ~0x8000; }
	void  SetLast(bool b)            { size = b ? size | 0x8000 : size & ~0x8000; }

	word  GetSize()                  { return size & 0x7fff; }
	word  GetPrevSize()              { return prev_size & 0x7fff; }
	bool  IsFirst()                  { return GetPrevSize() == 0; }
	bool  IsFree()                   { return prev_size & 0x8000; }
	bool  IsLast()                   { return size & 0x8000; }

	BlkHeader_ *GetPrevHeader()      { return (BlkHeader_ *)((byte *)this - BlkSize * GetPrevSize()); }
	BlkHeader_ *GetNextHeader()      { return (BlkHeader_ *)((byte *)this + BlkSize * GetSize()); }

	void  UnlinkFree()               { Dbl_Unlink(this); }

	void  SetNextPrevSz()            { if(!IsLast()) GetNextHeader()->SetPrevSize(GetSize()); }
};

template <typename Detail, int BlkSize>
struct BlkHeap : Detail {
	typedef BlkHeader_<BlkSize> BlkHeader;
	typedef Detail D;
	
	bool  JoinNext(BlkHeader *h, word needs_count = 0);
	void  Split(BlkHeader *h, word wcount);
	void  AddChunk(BlkHeader *h, int count);
	void *MakeAlloc(BlkHeader *h, word wcount);
	int   Free(BlkHeader *h);
	bool  TryRealloc(void *ptr, size_t count);
};

template <typename Detail, int BlkSize>
force_inline
bool BlkHeap<Detail, BlkSize>::JoinNext(BlkHeader *h, word needs_count)
{ // try to join with next header if it is free, does not link it to free
	if(h->IsLast())
		return false;
	BlkHeader *nh = h->GetNextHeader();
	if(!nh->IsFree() || h->GetSize() + nh->GetSize() < needs_count)
		return false;
	h->SetLast(nh->IsLast());
	nh->UnlinkFree();
	word nsz = h->GetSize() + nh->GetSize();
	h->SetSize(nsz);
	h->SetNextPrevSz();
	return true;
}

template <typename Detail, int BlkSize>
force_inline
void BlkHeap<Detail, BlkSize>::Split(BlkHeader *h, word wcount)
{ // splits the block if bigger, links new block to free
	BlkHeader *h2 = (BlkHeader *)((byte *)h + BlkSize * (int)wcount);
	word nsz = h->GetSize() - wcount;
	if(nsz == 0) // nothing to split
		return;

	h2->SetFree(true);
	h2->SetLast(h->IsLast());
	h2->SetSize(nsz);
	h2->SetPrevSize(wcount);
	h2->SetNextPrevSz();
	D::LinkFree(h2);

	h->SetSize(wcount);
	h->SetLast(false);
}

template <typename Detail, int BlkSize>
void BlkHeap<Detail, BlkSize>::AddChunk(BlkHeader *h, int count)
{
	h->SetSize(count);
	h->SetPrevSize(0); // is first
	h->SetLast(true);
	h->SetFree(true);
	D::LinkFree(h);
}

template <typename Detail, int BlkSize>
force_inline
void *BlkHeap<Detail, BlkSize>::MakeAlloc(BlkHeader *h, word wcount)
{
	h->UnlinkFree();
	h->SetFree(false);
	Split(h, wcount);
	return h;
}

template <typename Detail, int BlkSize>
bool BlkHeap<Detail, BlkSize>::TryRealloc(void *ptr, size_t count)
{
	ASSERT(count);
	
	BlkHeader *h = (BlkHeader *)ptr;
	if(h->size == 0)
		return false;
	
	word sz = h->GetSize();
	if(sz != count) {
		if(!JoinNext(h, (word)count))
			return false;
		Split(h, (word)count);
	}
	return true;
}

template <typename Detail, int BlkSize>
int BlkHeap<Detail, BlkSize>::Free(BlkHeader *h)
{
	JoinNext(h);
	if(!h->IsFirst()) { // try to join with previous header if it is free
		BlkHeader *ph = h->GetPrevHeader();
		if(ph->IsFree()) {
			word nsz = ph->GetSize() + h->GetSize();
			ph->SetSize(nsz);
			ph->SetLast(h->IsLast());
			ph->SetNextPrevSz();
			D::NewFreeSize(ph);
			return nsz;
		}
	}
	h->SetFree(true);
	D::LinkFree(h); // was not joined with previous header
	D::NewFreeSize(h);
	return h->GetSize();
}
