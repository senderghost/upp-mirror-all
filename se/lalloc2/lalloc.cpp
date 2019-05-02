#include <Core/Core.h>

using namespace Upp;

namespace Upp {
void *SysAllocRaw(size_t size, size_t reqsize);
};

#define LLOG(x)  // LOG(x)
#define LDUMP(x) // DUMP(x)

#ifdef COMPILER_MSC
inline int BSR(dword x) { dword r; _BitScanReverse(&r, x); return r; }
#else
inline int BSR(dword x) { return 31 - __builtin_clz(x); }
#endif

//	xT = 1 << (31 - __builtin_clz(xT));

struct HugePrefix { // this part is at the start of allocated block
	word        prev_size; // top bit: free, size of previous block in 4KB blocks
	word        size; // top bit: last block, size in 4KB blocks
};

struct HugeHeader : HugePrefix {
	HugeHeader *prev; // linked list of free blocks
	HugeHeader *next; // linked list of free blocks

	void  SetSize(word sz)      { size = (size & 0x8000) | sz; }
	void  SetPrevSize(word sz)  { prev_size = (prev_size & 0x8000) | sz; }
	void  SetFree(bool b)       { prev_size = b ? prev_size | 0x8000 : prev_size & ~0x8000; }
	void  SetLast(bool b)       { size = b ? size | 0x8000 : size & ~0x8000; }

	word  GetSize()                  { return size & 0x7fff; }
	word  GetPrevSize()              { return prev_size & 0x7fff; }
	bool  IsFirst()                  { return GetPrevSize() == 0; }
	bool  IsFree()                   { return prev_size & 0x8000; }
	bool  IsLast()                   { return size & 0x8000; }

	HugeHeader *GetPrevHeader()      { return (HugeHeader *)((byte *)this - 4096 * GetPrevSize()); }
	HugeHeader *GetNextHeader()      { return (HugeHeader *)((byte *)this + 4096 * GetSize()); }

	void  UnlinkFree();
	void  LinkFree();

	void  SetNextPrev()              { if(!IsLast()) GetNextHeader()->SetPrevSize(GetSize()); }
};

static HugeHeader freelist[8193];
int freecount;

inline
void HugeHeader::LinkFree()
{
	Dbl_LinkAfter(this, &freelist[GetSize()]);
	freecount++;
}

inline
void HugeHeader::UnlinkFree()
{
	Dbl_Unlink(this);
	freecount--;
}
               
void HugeMore()
{
	RTIMING("HugeMore");

	HugeHeader *h = (HugeHeader *)SysAllocRaw(8192 * 4096, 0); // 8192 pages
	h->SetSize(8192);
	h->SetPrevSize(0); // is first
	h->SetLast(true);
	h->SetFree(true);
	h->LinkFree();

	LLOG("HugeMore " << h);
}

void *HugeAlloc(int count) // count in 4kb pages
{
	ASSERT(count);
	if(!freelist[0].next) { // initialization
		for(int i = 0; i < 16; i++)
			freelist[i].next = freelist[i].prev = &freelist[i];
	}
	for(int pass = 0; pass < 2; pass++) {
		for(int q = count; q < 8193; q++) {
			HugeHeader *l = &freelist[q];
			HugeHeader *h = l->next;
			if(h != l) {
	//			RTIMING("Scan");
				word sz = h->GetSize();
				LDUMP(sz);
				h->UnlinkFree();
				h->SetFree(false);
				if(sz > count) { // split the block
					HugeHeader *h2 = (HugeHeader *)((byte *)h + 4096 * count);
					LDUMP(h);
					LDUMP(h2);
					LDUMP(sz - count);
					word nsz = sz - count;
					h2->SetFree(true);
					h2->SetLast(h->IsLast());
					h2->SetSize(nsz);
					h2->SetPrevSize(count);
					h2->SetNextPrev();
					h2->LinkFree();

					h->SetSize(count);
					h->SetLast(false);
				}
				return h;
			}
		}
		HugeMore();
	}
	Panic("Out of memory");
	return NULL;
}

void HugeFree(void *ptr)
{
	LLOG("Free ---------------");
	HugeHeader *h = (HugeHeader *)ptr;
	LDUMP(h);
	LDUMP(h->GetPrevSize());
	LDUMP(h->GetSize());
	if(!h->IsLast()) { // try to join with next header if it is free
		HugeHeader *nh = h->GetNextHeader();
		LDUMP(nh);
		LDUMP(nh->IsFree());
		if(nh->IsFree()) {
			LDUMP(h->GetSize());
			LDUMP(nh->GetSize());
			LDUMP(h->GetSize() + nh->GetSize());
			h->SetLast(nh->IsLast());
			nh->UnlinkFree();
			word nsz = h->GetSize() + nh->GetSize();
			LDUMP(nsz);
			ASSERT(nsz <= 8192);
			h->SetSize(nsz);
			h->SetNextPrev();
		}
	}
	if(!h->IsFirst()) { // try to join with previous header if it is free
		HugeHeader *ph = h->GetPrevHeader();
		LDUMP(ph);
		LDUMP(ph->IsFree());
		if(ph->IsFree()) {
			LDUMP(ph->GetSize());
			LDUMP(h->GetSize());
			LDUMP(ph->GetSize() + h->GetSize());
			word nsz = ph->GetSize() + h->GetSize();
			LDUMP(nsz);
			ASSERT(nsz <= 8192);
			ph->SetSize(nsz);
			ph->SetLast(h->IsLast());
			ph->SetNextPrev();
			return;
		}
	}
	LDUMP(h->GetSize());
	h->SetFree(true);
	LDUMP(h->IsFree());
	h->LinkFree(); // was not joined with previous header
}

void DumpFreeList(bool check = false)
{
	LOG("FreeList ------------");
	HugeHeader *h = freelist->next;
	while(h != freelist) {
		LOG(h << " " << h->GetSize());
		if(check)
			ASSERT(h->GetSize() == 8192);
		h = h->next;
	}
}

int xT = 123;

CONSOLE_APP_MAIN
{
	/*
	for(int i = 1; i < 512; i++)
		DLOG(i << " " << Bsr(i));
	return;*/

	void *ptr = HugeAlloc(16);
	DumpFreeList();
	HugeFree(ptr);
	DumpFreeList();
	ptr = HugeAlloc(8192);
	DumpFreeList();
	HugeFree(ptr);
	DumpFreeList();

	LOG("-- TEST ----------------------");
	{
		SeedRandom(0);

		static void *ptr[1000];
		
		for(int i = 0; i < 5000000; i++) {
			int ii = Random(1000);
			if(ptr[ii]) {
				RTIMING("HugeFree");
				HugeFree(ptr[ii]);
				ptr[ii] = NULL;
			}
			if(Random(2)) {
				RTIMING("HugeAlloc");
//				ptr[ii] = HugeAlloc(Random(1000) + 100);
				ptr[ii] = HugeAlloc(Random(8192) + 1);
			}
		}

		for(int i = 0; i < 1000; i++)
			if(ptr[i])
				HugeFree(ptr[i]);

		DumpFreeList(true);
	}
}
