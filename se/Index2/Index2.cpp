#include <Core/Core.h>

using namespace Upp;

namespace New {
	
struct HashBase {
	struct Item : Moveable<Item> {
		dword hash; // folded hash value
		int   next; // link to next value in the bucket / previous unlinked item
	};
	
	Vector<Item> item;
	Buffer<int>  map;
	dword        mask = 0;
	int          unlinked = -1;

	static void Fold(dword hash)    { hash = FoldHash(hash) | 0x80000000; }
	void Del(int ii);
	void Ins(int ii, dword hash);

public:
	void Link(int ii, Item& e, dword hash);
	void Reindex();
	void GrowMap();
	void Add(dword hash)            { AddFolded(Fold(hash)); }
	int  Find(dword hash);
	int  FindNext(int ii);
	
	void Unlink(int ii);
	bool IsUnlinked(int ii)         { return item[ii].hash == 0; }
	int  Put(dword hash);
	void Set(int ii, dword hash);
};

void HashBase::Del(int ii)
{ // remove hash from the bucket - need to correct the link chain
	dword& hash = item[ii].hash;
	int& m = map[hash & mask];
	hash = 0;
	if(item[ii].next == ii) // unlinking the last item in this bucket
		m = -1;
	else {
		int i = m;
		for(;;) { // find item before unlinked one
			int& next = item[i].next;
			if(next == ii) {
				next = item[ii].next;
				break;
			}
			i = next;
		}
		if(m == ii) // ii was the last item in the bucket, map was pointing to it
			m = i; // now pointing to the new last item (one before ii)
	}
}

void HashBase::Ins(int ii, dword hash)
{ // put folded hash to the bucket
	int& m = map[hash & mask]; // index of last item in the bucket
	item[ii].hash = hash;
	if(m < 0) // putting the first element into the bucket
		m = item[ii].next = ii;
	else
	if(ii > m) { // ii is after the last item in the bucket
		item[ii].next = item[m].next; // point to the first item
		m = item[m].next = ii; // new last item in the bucket
	}
	else { // need to find a place where to insert ii
		int i = m;
		for(;;) {
			int& next = item[i].next;
			if(ii < next) { // ii is before the next item
				item[ii].next = next;
				next = ii;
				break;
			}
			i = next;
		}
	}
}

void HashBase::Unlink(int ii)
{
	Del(ii);
	item[ii].next = unlinked; // add to list of unlinked items
	unlinked = ii;
}

int HashBase::Put(dword hash)
{
	hash = Fold(hash);
	int ii;
	if(unlinked < 0) { // no unlinked items, need to add normally
		ii = GetCount();
		AddFolded(hash);
	}
	else { // pop unlinked item index and put the hash there
		ii = unlinked;
		unlinked = item[unlinked].next;
		Ins(ii, hash);
	}
	return ii;
}

void HashBase::Set(int ii, dword hash)
{
	Del(ii);
	Ins(ii, Fold(hash));
}

force_inline
void HashBase::Link(int ii, Item& e, dword hash)
{
	int& m = map[hash & mask];
	if(m < 0)
		m = e.next = ii; // this is the first item in this bucket
	else {
		Item& ee = item[m]; // previous last item in this bucket
		e.next = ee.next; // last item points to first item
		m = ee.next = ii; // new is now next, map points to the last one
	}
}

void HashBase::Reindex()
{
	map.Alloc(mask + 1, -1);
	for(int i = 0; i < item.GetCount(); i++)
		Link(i, item[i], item[i].hash);
}

void HashBase::GrowMap()
{
	mask = max((dword)7, mask << 1 | 1);
	Reindex();
}

void HashBase::AddFolded(dword hash)
{
	int ii = item.GetCount();
	Item& e = item.Add();
	e.hash = hash;
	if(item.GetCount() <= (int)mask)
		Link(ii, e, hash);
	else
		GrowMap();
}


int HashBase::Find(dword hash)
{
	int m = map[Fold(hash) & mask];
	return m < 0 ? -1 : item[m].next; // map points to the last element
}

int HashBase::FindNext(int ii)
{
	const Item& e = item[ii];
	return e.next > ii ? e.next : -1;
}

};

CONSOLE_APP_MAIN
{
	New::HashBase b;
	
	b.Add(123);
	b.Add(13);
	
	RDUMP(b.Find(123));
	RDUMP(b.Find(124));
	RDUMP(b.Find(127));
	RDUMP(b.Find(13));
}
