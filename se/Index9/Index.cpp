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

void HashBase::Reindex(int count)
{
	FreeMap();
	map = (int *)MemoryAlloc((mask + 1) * sizeof(int));
	Fill(map, map + mask + 1, -1);
	for(int i = 0; i < count; i++) // todo: unlinked
		if(hash[i].hash)
			Link(i, hash[i].hash);
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

void HashBase::Sweep()
{
	
}

/*
void HashBase::MakeMap(int)
{
	while(mask <= (dword)hash.GetCount())
		mask = (mask << 1) | 3;
	Reindex();
}

void HashBase::Reserve(int n)
{
	hash.Reserve(n);
	MakeMap();
}

void HashBase::Shrink()
{
	hash.Shrink();
	mask = 0;
	MakeMap();
}
*/


void HashBase::Trim(int n)
{
#if 0
	if(n == 0) { // trim everything
		hash.Trim(0);
		for(int i = 0; i < int(mask + 1); i++)
			map[i].first = map[i].last = -1;
		unlinked = -1;
		return;
	}
	
	for(int i = n; i < GetCount(); i++) // remove items in trimmed area from buckets
		if(!IsUnlinked(i))
			Del(i);

	int i = unlinked; // remove unlinked items in trimmed area
	unlinked = -1;
	while(i >= 0) {
		int ni = hash[i].next;
		if(i < n) {
			hash[i].next = unlinked;
			unlinked = i;
		}
		i = ni;
	}

	hash.Trim(n);

	Check();
#endif
}

};
