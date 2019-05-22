#include <Core/Core.h>

using namespace Upp;

namespace Upp {
void *SysAllocRaw(size_t size, size_t reqsize);
void  SysFreeRaw(void *ptr, size_t size);
};

template <int BlkSize>
struct BlkHeap {
	struct BlkPrefix { // this part is at the start of Blk allocated block, client must not touch it
		word        prev_size; // top bit: free, rest: size of previous block in 4KB blocks
		word        size; // top bit: last block, rest: size of this block in 4KB blocks, 0 - sys
	};
	
	struct BlkHeader : BlkPrefix {
		BlkHeader *prev; // linked list of free blocks
		BlkHeader *next; // linked list of free blocks
	
		void  SetSize(word sz)           { size = (size & 0x8000) | sz; }
		void  SetPrevSize(word sz)       { prev_size = (prev_size & 0x8000) | sz; }
		void  SetFree(bool b)            { prev_size = b ? prev_size | 0x8000 : prev_size & ~0x8000; }
		void  SetLast(bool b)            { size = b ? size | 0x8000 : size & ~0x8000; }
	
		word  GetSize()                  { return size & 0x7fff; }
		word  GetPrevSize()              { return prev_size & 0x7fff; }
		bool  IsFirst()                  { return GetPrevSize() == 0; }
		bool  IsFree()                   { return prev_size & 0x8000; }
		bool  IsLast()                   { return size & 0x8000; }
	
		BlkHeader *GetPrevHeader()      { return (BlkHeader *)((byte *)this - BlkSize * GetPrevSize(); }
		BlkHeader *GetNextHeader()      { return (BlkHeader *)((byte *)this + BlkSize * GetSize(); }
	
		void  UnlinkFree();
		void  LinkFree();
	
		void  SetNextPrevSz()            { if(!IsLast()) GetNextHeader()->SetPrevSize(GetSize()); }
	};

	static BlkHeader hsmall[1], hlarge[1];

	static bool  BlkJoinNext(BlkHeader *h, word needs_count = 0);
	static void  BlkSplit(BlkHeader *h, word wcount);
	static void *BlkAlloc(size_t count); // count in 4KB, client needs to not touch BlkPrefix
	static int   BlkFree(void *ptr);
	static bool  BlkTryRealloc(void *ptr, size_t count);
}

inline
void Heap::BlkHeader::UnlinkFree()
{
	Dbl_Unlink(this);
}

inline
void Heap::BlkHeader::LinkFree()
{
	Dbl_LinkAfter(this, GetSize() < 16 ? hsmall : hlarge);
}

force_inline
bool Heap::BlkJoinNext(BlkHeader *h, word needs_count)
{ // try to join with next header if it is free, does not link to free
	if(h->IsLast())
		return false;
	BlkHeader *nh = h->GetNextHeader();
	if(!nh->IsFree() || h->GetSize() + nh->GetSize() < needs_count)
		return false;
	h->SetLast(nh->IsLast());
	nh->UnlinkFree();
	word nsz = h->GetSize() + nh->GetSize();
	ASSERT(nsz <= 8192);
	h->SetSize(nsz);
	h->SetNextPrevSz();
	return true;
}

force_inline
void Heap::BlkSplit(BlkHeader *h, word wcount)
{ // splits the block if bigger, links new block to free
	BlkHeader *h2 = (BlkHeader *)((byte *)h + 4096 * (int)wcount);
	word nsz = h->GetSize() - wcount;
	if(nsz == 0) // nothing to split
		return;

	h2->SetFree(true);
	h2->SetLast(h->IsLast());
	h2->SetSize(nsz);
	h2->SetPrevSize(wcount);
	h2->SetNextPrevSz();
	h2->LinkFree();

	h->SetSize(wcount);
	h->SetLast(false);
}

void *Heap::BlkAlloc(size_t count) // count in 4kb pages
{
	ASSERT(count);

	huge_4KB_count += count;
	
	if(!hsmall->next) { // initialization
		hsmall->next = hsmall->prev = hsmall;
		hlarge->next = hlarge->next = hlarge;
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
		BlkHeader *l = count < 16 ? hsmall : hlarge;
		for(;;) {
			BlkHeader *h = l->next;
			while(h != l) {
				word sz = h->GetSize();
				if(sz >= count) {
					h->UnlinkFree();
					h->SetFree(false);
					BlkSplit(h, wcount);
					return h;
				}
				h = h->next;
			}
			if(l == hlarge)
				break;
			l = hlarge;
		}

		if(!FreeSmallEmpty(wcount)) { // try to coalesce 4KB small free blocks back to huge storage
			BlkHeader *h = (BlkHeader *)SysAllocRaw(8192 * 4096, 0); // failed, get 32MB from the system
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

bool Heap::BlkTryRealloc(void *ptr, size_t count)
{
	ASSERT(count);
	
	if(count > 8192)
		return false;
	
	BlkHeader *h = (BlkHeader *)ptr;
	if(h->size == 0)
		return false;
	
	word sz = h->GetSize();
	if(sz != count) {
		if(!BlkJoinNext(h, count))
			return false;
		BlkSplit(h, count);
	}
	return true;
}

int Heap::BlkFree(void *ptr)
{
	BlkHeader *h = (BlkHeader *)ptr;
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
	BlkJoinNext(h);
	if(!h->IsFirst()) { // try to join with previous header if it is free
		BlkHeader *ph = h->GetPrevHeader();
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
	void *ptr[16];
	for(int i = 0; i < 16; i++)
		ptr[i] = new byte[50000];
	
	for(int i = 0; i < 16; i++)
		delete ptr[i];

	{
		void *ptr = new byte[100000];
		delete ptr;
	}
}
