#include <Core/Core.h>

using namespace Upp;

namespace Upp {
void *SysAllocRaw(size_t size, size_t reqsize);
void  SysFreeRaw(void *ptr, size_t size);
};

#define LLOG(x)  // LOG(x)
#define LDUMP(x) // DUMP(x)

struct HugePrefix { // this part is at the start of allocated block, client must not touch it
	word        prev_size; // top bit: free, rest: size of previous block in 4KB blocks
	word        size; // top bit: last block, rest: size of this block in 4KB blocks, 0 - sys
};

struct HugeHeader : HugePrefix {
	HugeHeader *prev; // linked list of free blocks
	HugeHeader *next; // linked list of free blocks

	void  SetSize(word sz)           { size = (size & 0x8000) | sz; }
	void  SetPrevSize(word sz)       { prev_size = (prev_size & 0x8000) | sz; }
	void  SetFree(bool b)            { prev_size = b ? prev_size | 0x8000 : prev_size & ~0x8000; }
	void  SetLast(bool b)            { size = b ? size | 0x8000 : size & ~0x8000; }

	word  GetSize()                  { return size & 0x7fff; }
	word  GetPrevSize()              { return prev_size & 0x7fff; }
	bool  IsFirst()                  { return GetPrevSize() == 0; }
	bool  IsFree()                   { return prev_size & 0x8000; }
	bool  IsLast()                   { return size & 0x8000; }

	HugeHeader *GetPrevHeader()      { return (HugeHeader *)((byte *)this - 4096 * GetPrevSize()); }
	HugeHeader *GetNextHeader()      { return (HugeHeader *)((byte *)this + 4096 * GetSize()); }

	void  UnlinkFree();
	void  LinkFree();

	void  SetNextPrevSz()            { if(!IsLast()) GetNextHeader()->SetPrevSize(GetSize()); }
};

static HugeHeader hsmall[4], hlarge[4];
int freecount;

inline
void HugeHeader::LinkFree()
{
	Dbl_LinkAfter(this, GetSize() < 16 ? hsmall : hlarge);
	freecount++;
}

inline
void HugeHeader::UnlinkFree()
{
	Dbl_Unlink(this);
	freecount--;
}

void *HugeAlloc(size_t count) // count in 4kb pages
{
	ASSERT(count);
	
	if(!hsmall->next) { // initialization
		hsmall->next = hsmall->prev = hsmall;
		hlarge->next = hlarge->next = hlarge;
	}
		
	if(count > 8192) { // we are wasting whole 4KB page to store just 4 bytes, but this is >32MB after all..
		byte *sysblk = (byte *)SysAllocRaw((count + 1) * 4096, 0);
		HugeHeader *h = (HugeHeader *)(sysblk + 4096);
		h->size = 0;
		*((size_t *)sysblk) = count;
		return h;
	}
	
	word wcount = (word)count;
	
	for(int pass = 0; pass < 2; pass++) {
		HugeHeader *l = count < 16 ? hsmall : hlarge;
		for(;;) {
			HugeHeader *h = l->next;
			if(h != l) {
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
	
						h->SetSize(count);
						h->SetLast(false);
					}
					return h;
				}
			}
			if(l == hlarge)
				break;
			l = hlarge;
		}

		HugeHeader *h = (HugeHeader *)SysAllocRaw(8192 * 4096, 0); // 8192 pages
		h->SetSize(8192);
		h->SetPrevSize(0); // is first
		h->SetLast(true);
		h->SetFree(true);
		h->LinkFree();
	}
	Panic("Out of memory");
	return NULL;
}

int HugeFree(void *ptr)
{
	LLOG("Free ---------------");
	HugeHeader *h = (HugeHeader *)ptr;
	if(h->size == 0) {
		byte *sysblk = (byte *)h - 4096;
		SysFreeRaw(sysblk, *((size_t *)sysblk));
		return 0;
	}
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

void DumpFreeList(bool check = false)
{
	#if 0
	LOG("FreeList ------------");
	HugeHeader *h = freelist->next;
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
	/*
	for(int i = 1; i < 512; i++)
		DLOG(i << " " << Bsr(i));
	return;*/
	void *ptr = HugeAlloc(10000);
	HugeFree(ptr);
	
	ptr = HugeAlloc(16);
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
				RTIMING("HugeFree 4KB");
				HugeFree(ptr[ii]);
				ptr[ii] = NULL;
			}
			if(Random(2)) {
				RTIMING("HugeAlloc 4KB");
				ptr[ii] = HugeAlloc(1);
			}
		}
	}

#if 0
		for(int i = 0; i < 1000; i++)
			if(ptr[i]) {
				HugeFree(ptr[i]);
				ptr[i] = NULL;
			}
		RLOG("4KB failed pass: " << failed_pass << ", failed list: " << failed_list); failed_pass = failed_list = 0;

		for(int i = 0; i < 5000000; i++) {
			int ii = Random(1000);
			if(ptr[ii]) {
				RTIMING("HugeFree 64KB");
				HugeFree(ptr[ii]);
				ptr[ii] = NULL;
			}
			if(Random(2)) {
				RTIMING("HugeAlloc 64KB");
				ptr[ii] = HugeAlloc(16);
			}
		}
		for(int i = 0; i < 1000; i++)
			if(ptr[i]) {
				HugeFree(ptr[i]);
				ptr[i] = NULL;
			}
		RLOG("64KB failed pass: " << failed_pass << ", failed list: " << failed_list); failed_pass = failed_list = 0;

		for(int i = 0; i < 5000000; i++) {
			int ii = Random(1000);
			if(ptr[ii]) {
				RTIMING("HugeFree <300KB");
				HugeFree(ptr[ii]);
				ptr[ii] = NULL;
			}
			if(Random(2)) {
				RTIMING("HugeAlloc <300KB");
				ptr[ii] = HugeAlloc(Random(300) + 1);
			}
		}
		for(int i = 0; i < 1000; i++)
			if(ptr[i]) {
				HugeFree(ptr[i]);
				ptr[i] = NULL;
			}
		RLOG("<300KB failed pass: " << failed_pass << ", failed list: " << failed_list); failed_pass = failed_list = 0;

		for(int i = 0; i < 5000000; i++) {
			if(ptr[i & 255]) {
				RTIMING("HugeFree 1MB");
				HugeFree(ptr[i & 255]);
				ptr[i & 255] = NULL;
			}
			RTIMING("HugeAlloc 1MB");
			ptr[i & 255] = HugeAlloc(i & 1 ? 100 : 256);
		}
		for(int i = 0; i < 1000; i++)
			if(ptr[i]) {
				HugeFree(ptr[i]);
				ptr[i] = NULL;
			}
		RLOG("1MB failed pass: " << failed_pass << ", failed list: " << failed_list); failed_pass = failed_list = 0;

		for(int i = 0; i < 5000000; i++) {
			int ii = Random(1000);
			if(ptr[ii]) {
				RTIMING("HugeFree");
				HugeFree(ptr[ii]);
				ptr[ii] = NULL;
			}
			if(Random(2)) {
				RTIMING("HugeAlloc");
				ptr[ii] = HugeAlloc(Random(8192) + 1);
			}
		}
		for(int i = 0; i < 1000; i++)
			if(ptr[i]) {
				HugeFree(ptr[i]);
				ptr[i] = NULL;
			}
		RLOG("Failed pass: " << failed_pass << ", failed list: " << failed_list); failed_pass = failed_list = 0;

		DumpFreeList(true);
	}
#endif
}
