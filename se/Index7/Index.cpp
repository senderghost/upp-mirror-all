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
//	RTIMING("Reindex");
	LLOG("== Reindex " << mask);
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
	Free();
	hash.Clear();
	map = empty;
	mask = 0;
	unlinked = -1;
}
	
void HashBase::Set(int ii, dword h)
{
	Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
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
		h << i << ": " << hash[i].hash << " -> " << hash[i].next;
	}
	return h;
}

};
