#include "Core.h"
#include "Core.h"

namespace Upp {

#ifdef UPP_HEAP

#define LLOG(x) //  LOG((void *)this << ' ' << x)

#include "HeapImp.h"

void Heap::LInit()
{
	for(int i = 0; i < 65; i++)
		Dbl_Self(lheap.freelist[i]);
	lheap.mini = 64;
	big->LinkSelf();
}

void *Heap::TryLAlloc(int i0, word wcount)
{
	LOG("i0: " << asString(i0) << ", mini: " << lheap.mini);
	for(int i = max(i0, lheap.mini); i < 65; i++) {
		LBlkHeader *l = lheap.freelist[i];
		LBlkHeader *h = l->next;
		while(h != l) {
			word sz = h->GetSize();
			if(sz >= wcount) {
				LOG("found: " << i);
				
				if(lheap.mini >= i0) {
					LOG("New " << i);
					lheap.mini = i;
				}
				lheap.MakeAlloc(h, wcount);
				h->heap = this;
				return (BlkPrefix *)h + 1;
			}
			h = h->next;
		}
	}
	return NULL;
}

void *Heap::LAlloc(size_t& size)
{
	if(!initialized)
		Init();

	if(size > LUNIT * LPAGE - sizeof(BlkPrefix)) { // big block allocation
		Mutex::Lock __(mutex);
		size_t count = (size + sizeof(DLink) + sizeof(BlkPrefix) + 4095) >> 12;
		DLink *d = (DLink *)HugeAlloc(count);
		d->Link(big);
		d->size = size = (count << 12) - sizeof(DLink) - sizeof(BlkPrefix);
		BlkPrefix *h = (BlkPrefix *)(d + 1);
		h->heap = NULL; // mark this as huge block
		big_size += size;
		big_count++;
		LLOG("Big alloc " << size << ": " << h + 1);
		return h + 1;
	}
	
	word wcount = word((size + sizeof(BlkPrefix) + 255) >> 8);
	size = ((int)wcount << 8) - sizeof(BlkPrefix);
	int i0 = min((int)wcount, 64);

	if(large_remote_list)  // there might be blocks of this heap freed in other threads
		LargeFreeRemote(); // free them first

	void *ptr = TryLAlloc(i0, wcount);
	if(ptr)
		return ptr;

	Mutex::Lock __(mutex);
	aux.LargeFreeRemoteRaw();
	if(aux.large->next != aux.large) {
		while(aux.large->next != aux.large) { // adopt all abandoned large blocks
			DLink *ml = aux.large->next;
			ml->Unlink();
			ml->Link(large);
		}
		ptr = TryLAlloc(i0, wcount);
		if(ptr)
			return ptr;
	}

	DLink *ml = (DLink *)HugeAlloc(16); // 16 x 4KB = 64KB
	ml->Link(large);
	LBlkHeader *h = ml->GetFirst();
	lheap.AddChunk(h, 255);
	lheap.MakeAlloc(h, wcount);
	h->heap = this;
	return (BlkPrefix *)h + 1;
}

void Heap::FreeLargePage(DLink *l)
{
	LLOG("Moving empty large " << (void *)l << " to global storage, lcount " << lcount);
	l->Unlink();
	Mutex::Lock __(mutex);
	HugeFree(l);
}

void Heap::LFree(void *ptr)
{
	BlkPrefix *h = (BlkPrefix *)ptr - 1;

	if(h->heap == this) {
		LBlkHeader *fh = lheap.Free((LBlkHeader *)h);
		if(fh->GetSize() == 255) {
			fh->UnlinkFree();
			FreeLargePage((DLink *)((byte *)fh - LOFFSET));
		}
		return;
	}

	Mutex::Lock __(mutex);
	if(h->heap == NULL) { // this is huge block
		Mutex::Lock __(mutex);
		DLink *d = (DLink *)h - 1;
		big_size -= h->size;
		big_count--;
		d->Unlink();
		LLOG("Big free " << (void *) ptr << " size " << h->size);
		HugeFree(d);
		return;
	}

	// this is remote heap
	FreeLink *f = (FreeLink *)ptr;
	f->next = h->heap->large_remote_list;
	h->heap->large_remote_list = f;
}

bool   Heap::LTryRealloc(void *ptr, size_t newsize)
{
	return false;
}

size_t Heap::LGetBlockSize(void *ptr) {
	LBlkHeader *h = (LBlkHeader *)ptr - 1;

	if(h->heap == NULL) { // huge block
		Mutex::Lock __(mutex);
		DLink *h = (DLink *)ptr - 1;
		return h->size;
	}
	
	return h->GetSize();
}

#endif

}
