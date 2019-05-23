void  OutOfMemoryPanic(size_t size);

void *SysAllocRaw(size_t size, size_t reqsize);
void  SysFreeRaw(void *ptr, size_t size);

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

struct HugeHeapDetail {
	static BlkHeader_<4096> freelist[2];
	
	static void LinkFree(BlkHeader_<4096> *h)     { Dbl_LinkAfter(h, &freelist[h->GetSize() >= 16]); }
	static void NewFreeSize(BlkHeader_<4096> *h)  {}
};

struct Heap : BlkHeap<HugeHeapDetail, 4096> {
	void *HugeAlloc(size_t count); // count in 4KB, client needs to not touch HugePrefix
	int   HugeFree(void *ptr);
	bool  HugeTryRealloc(void *ptr, size_t count);

	enum {
		NKLASS = 23, // number of small size classes
	};

	static int Ksz(int k) {
		static int sz[] = {
		//  0   1   2   3    4    5    6    7    8    9    10   11
			32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384,
			448, 576, 672, 800, 992, 8, 16, 24, 40, 48, 56
		//  12   13   14   15   16  17  18  19  20  21  22
		//  8 - 56 sizes are only available with TinyAlloc
		};
		static_assert(__countof(sz) == 23, "NKLASS mismatch");
		return sz[k];
	}
	
	struct FreeLink {
		FreeLink *next;
	};

	struct Page { // small block Page
		BlkPrefix    reserved; // this is reserved for huge block management
		Heap        *heap;     // pointer to Heap
		byte         klass;    // size class
		word         active;   // number of used (active) blocks in this page
		FreeLink    *freelist; // single linked list of free blocks in Page
		Page        *next;     // Pages are in work/full/empty lists
		Page        *prev;

		void         LinkSelf()            { Dbl_Self(this); }
		void         Unlink()              { Dbl_Unlink(this); }
		void         Link(Page *lnk)       { Dbl_LinkAfter(this, lnk);  }

		void         Format(int k);

		byte *Begin()                      { return (byte *)this + sizeof(Page); }
		byte *End()                        { return (byte *)this + 4096; }
		int   Count()                      { return (int)(uintptr_t)(End() - Begin()) / Ksz(klass); }
	};

	struct Header;

	struct DLink {
		BlkPrefix    reserved;   // this is reserved for huge block management, 0-0 for sys block
		DLink       *next;
		DLink       *prev;

		void         LinkSelf()            { Dbl_Self(this); }
		void         Unlink()              { Dbl_Unlink(this); }
		void         Link(DLink *lnk)      { Dbl_LinkAfter(this, lnk);  }

		Header      *GetHeader()           { return (Header *)this - 1; }
	};

	struct Header { // Large block header
		dword      size;
		dword      prev;
		uintptr_t  heap_ptr;
	#ifdef CPU_32
		dword      filler1; // sizeof(Header) == 16
	#endif

		Header     *Next()                   { return (Header *)((byte *)this + size) + 1; }
		Header     *Prev()                   { return (Header *)((byte *)this - prev) - 1; }
		
		void        SetFree(bool b)          { heap_ptr = (heap_ptr & ~1) | (int)b; }
		bool        IsFree()                 { return heap_ptr & 1; }

		void        SetHeap(Heap *h, bool f) { heap_ptr = (uintptr_t)h | (int)f; }
		Heap       *GetHeap()                { return (Heap *)(heap_ptr & ~1); }

		DLink      *GetBlock()               { return (DLink *)(this + 1); }
	};
	
	struct BigHdr : DLink {
		size_t       size;
	};

	enum {
		LARGEHDRSZ = 32, // size of large block header, + sizeof(Header) causes 16 byte disalignment
		BIGHDRSZ = 48, // size of huge block header
		REMOTE_OUT_SZ = 2000, // maximum size of remote frees to be buffered to flush at once

		MAXBLOCK = 65536 - 2 * sizeof(Header) - LARGEHDRSZ, // maximum size of large block
		LBINS = 77, // number of large size bins
	};

	static_assert(sizeof(Header) == 16, "Wrong sizeof(Header)");
	static_assert(sizeof(DLink) < 64, "Wrong sizeof(DLink)");
	static_assert(sizeof(BigHdr) + sizeof(Header) <= BIGHDRSZ, "Big header sizeof issue");

	static StaticMutex mutex;

	Page      work[NKLASS][1];   // circular list of pages that contain some empty blocks
	Page      full[NKLASS][1];   // circular list of pages that contain NO empty blocks
	Page     *empty[NKLASS];     // last fully freed page per klass (hot reserve) / shared global list of empty pages in aux
	FreeLink *cache[NKLASS];     // hot frontend cache of small blocks
	int       cachen[NKLASS];    // counter of small blocks that are allowed to be stored in cache

	bool      initialized;

	static word  BinSz[LBINS];   // block size for bin
	static byte  SzBin[MAXBLOCK / 8 + 1]; // maps size/8 to bin
	static byte  BlBin[MAXBLOCK / 8 + 1]; // Largest bin less or equal to size/8 (free -> bin)

	DLink  large[1]; // all large chunks that belong to this heap
	DLink  freebin[LBINS][1]; // all free blocks by bin
	
	void     *out[REMOTE_OUT_SZ / 8 + 1];
	void    **out_ptr;
	int       out_size;

	byte      filler1[64]; // make sure the next variable is in distinct cacheline

	FreeLink *small_remote_list; // list of remotely freed small blocks for lazy reclamation
	FreeLink *large_remote_list; // list of remotely freed large blocks for lazy reclamation

	static DLink big[1]; // List of all big blocks
	static Heap  aux;    // Single global auxiliary heap to store orphans and global list of free pages

	static size_t huge_4KB_count; // total number of 4KB pages in small/large/huge blocks
	static size_t free_4KB; // empty 4KB pages
	static size_t big_size; // blocks >~64KB
	static size_t big_count;
	static size_t sys_size;  // blocks allocated directly from system (included in big too)
	static size_t sys_count;
	static size_t huge_chunks; // 32MB master pages

#ifdef HEAPDBG
	static void  DbgFreeFill(void *ptr, size_t size);
	static void  DbgFreeCheck(void *ptr, size_t size);
	static void  DbgFreeFillK(void *ptr, int k);
	static void *DbgFreeCheckK(void *p, int k);
#else
	static void  DbgFreeFill(void *ptr, size_t size) {}
	static void  DbgFreeCheck(void *ptr, size_t size) {}
	static void  DbgFreeFillK(void *ptr, int k) {}
	static void *DbgFreeCheckK(void *p, int k) { return p; }
#endif

#ifdef flagHEAPSTAT
	static void  Stat(size_t sz);
#else
	static void  Stat(size_t sz) {}
#endif

	void  Init();

	static int   CheckFree(FreeLink *l, int k);
	void  Check();
	static void  Assert(bool b);
	static void  DblCheck(Page *p);
	static void  AssertLeaks(bool b);
	
	static bool  IsSmall(void *ptr) { return (((dword)(uintptr_t)ptr) & 16) == 0; }
	static Page *GetPage(void *ptr) { return (Page *)((uintptr_t)ptr & ~(uintptr_t)4095); }

	Page *WorkPage(int k);
	void *AllocK(int k);
	void  FreeK(void *ptr, Page *page, int k);
	void *Allok(int k);
	void  Free(void *ptr, Page *page, int k);
	void  Free(void *ptr, int k);

	static bool FreeSmallEmpty(int count4KB);

	static void GlobalLInit();
	static int  SizeToBin(int n) { return SzBin[(n - 1) >> 3]; }

	static void MoveLarge(Heap *dest, DLink *l);
	DLink *Add64KB();
	void   Free64KB(DLink *l, Header *bh);
	void   LinkFree(DLink *b, int size);
	void  *DivideBlock(DLink *b, int size);
	void  *TryLAlloc(int ii, size_t size);
	void  *LAlloc(size_t& size);
	void   LFree(void *ptr);
	size_t LGetBlockSize(void *ptr);
	bool   LTryRealloc(void *ptr, size_t newsize);
	void   Make(MemoryProfile& f);

	static void Shrink();

	void SmallFreeDirect(void *ptr);

	void RemoteFlushRaw();
	void RemoteFlush();
	void RemoteFree(void *ptr, int size);
	void SmallFreeRemoteRaw(FreeLink *list);
	void SmallFreeRemoteRaw() { SmallFreeRemoteRaw(small_remote_list); small_remote_list = NULL; }
	void SmallFreeRemote();
	void LargeFreeRemoteRaw(FreeLink *list);
	void LargeFreeRemoteRaw() { LargeFreeRemoteRaw(large_remote_list); large_remote_list = NULL; }
	void LargeFreeRemote();
	void FreeRemoteRaw();

	void Shutdown();
	static void AuxFinalCheck();

	void  *AllocSz(size_t& sz);
	void   Free(void *ptr);
	size_t GetBlockSize(void *ptr);
	void  *Alloc32();
	void   Free32(void *ptr);
	void  *Alloc48();
	void   Free48(void *ptr);

	bool   TryRealloc(void *ptr, size_t newsize);
};

force_inline
void Heap::RemoteFlushRaw()
{ // transfer all buffered freed remote blocks to target heaps, no locking
	if(!initialized)
		Init();
	for(void **o = out; o < out_ptr; o++) {
		FreeLink *f = (FreeLink *)*o;
		Heap *heap = GetPage(f)->heap;
		f->next = heap->small_remote_list;
		heap->small_remote_list = f;
	}
	out_ptr = out;
	out_size = 0;
}

force_inline
void Heap::RemoteFree(void *ptr, int size)
{ // buffer freed remote block until REMOTE_OUT_SZ is reached
	if(!initialized)
		Init();
	ASSERT(out_ptr <= out + REMOTE_OUT_SZ / 8 + 1);
	*out_ptr++ = ptr;
	out_size += size;
	if(out_size >= REMOTE_OUT_SZ) {
		Mutex::Lock __(mutex);
		RemoteFlushRaw();
	}
}

force_inline
void Heap::SmallFreeRemoteRaw(FreeLink *list)
{
	while(list) {
		FreeLink *f = list;
		list = list->next;
		SmallFreeDirect(f);
	}
}

force_inline
void Heap::SmallFreeRemote()
{
	while(small_remote_list) { // avoid mutex if likely nothing to free
		FreeLink *list;
		{ // only pick values in mutex, resolve later
			Mutex::Lock __(mutex);
			list = small_remote_list;
			small_remote_list = NULL;
		}
		SmallFreeRemoteRaw(list);
	}
}

force_inline
void Heap::LargeFreeRemoteRaw(FreeLink *list)
{
	while(list) {
		FreeLink *f = list;
		list = list->next;
		LFree(f);
	}
}

force_inline
void Heap::LargeFreeRemote()
{
	while(large_remote_list) { // avoid mutex if likely nothing to free
		FreeLink *list;
		{ // only pick values in mutex, resolve later
			Mutex::Lock __(mutex);
			list = large_remote_list;
			large_remote_list = NULL;
		}
		LargeFreeRemoteRaw(list);
	}
}
