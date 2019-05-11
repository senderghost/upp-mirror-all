#include "Index.h"

#define LLOG(x)

using namespace Upp;

namespace New {

int HashBase::empty[1] = { -1 };

HashBase::HashBase()
{
	hash = NULL;
	map = empty;
	mask = 0;
	unlinked = -1;
}

HashBase::~HashBase()
{
	Free();
}

void HashBase::FreeMap()
{
	if(map != empty)
		MemoryFree(map);
}

void HashBase::Free()
{
	if(hash)
		MemoryFree(hash);
	FreeMap();
}

void HashBase::Remap(int count)
{
	Fill(map, map + mask + 1, -1);
	for(int i = 0; i < count; i++) // todo: unlinked
		if(hash[i].hash)
			Link(i, hash[i].hash);
}

void HashBase::Reindex(int count)
{
	FreeMap();
	map = (int *)MemoryAlloc((mask + 1) * sizeof(int));
	Remap(count);
}

void HashBase::Clear()
{
	Free();
	hash = NULL;
	map = empty;
	mask = 0;
	unlinked = -1;
}

void HashBase::GrowMap(int count)
{
	LLOG("== GrowMap");
	mask = (mask << 1) | 3;
	Reindex(count);
}

Vector<int> HashBase::GetUnlinked() const
{
	Vector<int> r;
	int i = unlinked;
	if(i >= 0) {
		do {
			i = hash[i].prev;
			r.Add(i);
		}
		while(i != unlinked);
	}
	return r;
}

void HashBase::AdjustMap(int count, int alloc)
{
	dword msk = 0;
	while(msk < (dword)alloc)
		msk = (msk << 1) | 3;
	if(msk != mask) {
		mask = msk;
		Reindex(count);
	}
}

void HashBase::Trim(int n, int count)
{
	if(n == 0) {
		int n = (int)(mask + 1);
		for(int i = 0; i < n; i++)
			map[i] = -1;
		unlinked = -1;
		return;
	}
	
	for(int i = n; i < count; i++) { // remove items in trimmed area from buckets / unlinked
		Hash& hh = hash[i];
		if(hh.hash)
			Del(map[hh.hash & mask], hh, i);
		else
			Del(unlinked, hh, i);
	}
}

void HashBase::Sweep(int n)
{
	int ti = 0;
	for(int i = 0; i < n; i++)
		if(hash[i].hash)
			hash[ti++].hash = hash[i].hash;
	Remap(ti);
	unlinked = -1;
}

};
