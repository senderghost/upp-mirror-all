#include "Index.h"

#define LLOG(x)

using namespace Upp;

namespace New {
	
void HashBase::SweepGrow()
{
	RTIMING("SweepGrow");
	int n0 = hash.GetCount();
	hash.RemoveIf([&](int i) { if(IsUnlinked(i)) { return true; } return false;});
	int n = hash.GetCount();
//	DLOG("== SweepGrow " << n0 << " -> " << n);
	if(3 * n < 2 * mask) {
		while(mask > 2 * n)
			mask >>= 1;
		Reindex();
	}
	else
		GrowMap();
}

void HashBase::Set(int ii, dword h)
{
	Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
}

void HashBase::Reindex()
{
	LLOG("== Reindex " << mask);
	map.Alloc(mask + 1);
	for(int i = 0; i < hash.GetCount(); i++) {
		hash[i].next = -1;
		if(hash[i].hash)
			Link(i, hash[i].hash);
	}
}

void HashBase::GrowMap()
{
	LLOG("== GrowMap");
	mask = (mask << 1) | 3;
	Reindex();
}


};
