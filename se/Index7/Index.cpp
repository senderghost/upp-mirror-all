#include "Index.h"

#define LLOG(x)

using namespace Upp;

namespace New {

HashBase::Bucket HashBase::empty[1] = { -1, -1 };

HashBase::HashBase()
{
	map = empty;
	mask = 0;
	unlinked = -1;
}

HashBase::~HashBase()
{
	Free();
}

void HashBase::Free()
{
	if(map != empty)
		delete[] map;
}

void HashBase::Reindex()
{
	LOG("== Reindex " << mask);
	Free();
	map = new Bucket[mask + 1];
	for(int i = 0; i < hash.GetCount(); i++) {
		hash[i].next = -1;
		if(hash[i].hash)
			Link(i, hash[i].hash);
	}
}

void HashBase::Clear()
{
	hash.Clear();
	Free();
	map = empty;
	mask = 0;
	unlinked = -1;
}

void HashBase::GrowMap()
{
	LLOG("== GrowMap");
	mask = (mask << 1) | 3;
	Reindex();
}

String HashBase::Dump() const
{
	String h;
	for(int i = 0; i < hash.GetCount(); i++) {
		if(i)
			h << ", ";
		if(IsUnlinked(i))
			h << "#";
		h << i << ": " << hash[i].hash << " -> " << hash[i].next;
	}
	return h;
}

void HashBase::Sweep()
{
	
}

void HashBase::MakeMap()
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

void HashBase::Trim(int n)
{
	if(n == 0) { // trim everything
		hash.Trim(0);
		for(int i = 0; i < int(mask + 1); i++)
			map[i].first = map[i].last = -1;
		unlinked = -1;
		return;
	}
	
#if 1
	DLOG("Trim " << n);

//	for(int i = 0; i < mask + 1; i++)
//		DLOG(i << " first: " << map[i].first << ", last: " << map[i].last);
	DLOG(Dump());
#endif

	for(int i = n; i < GetCount(); i++) // remove items in trimmed area from buckets
		if(!IsUnlinked(i))
			Del(i);

	DLOG(Dump());

	int i = unlinked; // remove unlinked items in trimmed area
	unlinked = -1;
	while(i >= 0) {
		DDUMP(i);
		int ni = hash[i].next;
		if(i < n) {
			hash[i].next = unlinked;
			unlinked = i;
		}
		i = ni;
	}

	hash.Trim(n);

#if 1	
//	for(int i = 0; i < mask + 1; i++)
//		DLOG(i << " first: " << map[i].first << ", last: " << map[i].last);
	DLOG(Dump());
#endif

	Check();
}

void HashBase::Check() {
	for(int i = 0; i < mask + 1; i++)
		ASSERT(map[i].first < hash.GetCount() && map[i].last < hash.GetCount());
}

};
