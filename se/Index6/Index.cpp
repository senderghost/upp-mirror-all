#include <Core/Core.h>

using namespace Upp;

namespace New {
	
class HashBase {
	enum { HIBIT = 0x80000000 };

	struct Bucket {
		int first = -1;
		int last = -1;
	};
	
	struct Hash : Moveable<Hash> {
		dword hash;
		int   next;
	};
	
	Buffer<Bucket> map;
	Vector<Hash> hash;
	dword        mask;
	int          unlinked = -1;

	static dword Smear(dword h)          { return FoldHash(h) | HIBIT; }

	void AddOverflow(Bucket& m, int ii);
	void Reindex();
	void GrowMap();
	void Link(int ii, dword h);
	void Del(int ii);
	void Ins(int ii, dword sh);
	void AddS(dword sh);
	
public:
	dword operator[](int i) const        { return hash[i].hash; }

	void Add(dword h);
	
	template <typename P>
	int FindFrom(int ii, dword sh, P pred) const;

	template <typename P>
	int Find(dword h, P x) const;
	
	void Unlink(int i);
	bool IsUnlinked(int i)               { return hash[i].hash == 0; }
	int  Put(dword h);

	void Set(int ii, dword h);
	
	HashBase()                           { mask = 0; }
};

void HashBase::Unlink(int ii)
{
	hash[ii].hash = 0;
	hash[ii].next = unlinked;
	unlinked = ii;
}

force_inline
void HashBase::Del(int ii)
{
	Hash& h = hash[ii];
	Bucket& m = map[h.hash & mask];
	int i = m.first;
	if(i == ii)
		m.first = h.next;
	else // need to find the item before ii
		while(i >= 0) {
			Hash& p = hash[i];
			if(p.next == ii) { // item before ii
				p.next = h.next; // point to item after ii
				if(m.last == ii) // if last item is ii
					m.last = i; // set it to item before ii
				break;
			}
			i = p.next;
		}
}

force_inline
void HashBase::Ins(int ii, dword sh)
{
	Hash& h = hash[ii];
	h.hash = sh;
	h.next = -1;
	Bucket& m = map[sh & mask];
	int i = m.first;
	if(ii < i) { // before first
		h.next = i;
		m.first = ii;
	}
	else
	if(ii > m.last) { // after last
		hash[m.last].next = ii;
		m.last = ii;
	}
	else
		while(i >= 0) {
			Hash& p = hash[i];
			if(ii < p.next) {
				h.next = p.next;
				p.next = ii;
				break;
			}
			i = p.next;
		}
}

int HashBase::Put(dword h)
{
	int ii = unlinked;
	h = Smear(h);
	if(ii < 0) {
		ii = hash.GetCount();
		AddS(h);
	}
	else {
		unlinked = hash[ii].next;
		Del(ii); // remove from original bucket list
		Ins(ii, Smear(h)); // put to new bucket list
	}
	return ii;
}

void HashBase::Set(int ii, dword h)
{
	Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
}

force_inline
void HashBase::Link(int ii, dword sh)
{
	Bucket& m = map[sh & mask];
	if(m.first == -1)
		m.first = m.last = ii;
	else {
		hash[m.last].next = ii;
		m.last = ii;
	}
}

void HashBase::Reindex()
{
	map.Alloc(mask + 1);
	for(int i = 0; i < hash.GetCount(); i++) {
		hash[i].next = -1;
		Link(i, hash[i].hash);
	}
}

void HashBase::GrowMap()
{
	mask = (mask << 1) | 1;
	Reindex();
}

force_inline
void HashBase::AddS(dword sh)
{
	int ii = hash.GetCount();
	Hash& hh = hash.Add();
	hh.hash = sh;
	hh.next = -1;
	if(ii >= (int)mask)
		GrowMap();
	else
		Link(ii, sh);
}

force_inline
void HashBase::Add(dword h)
{
	AddS(Smear(h));
}

template <typename P>
force_inline
int HashBase::FindFrom(int i, dword sh, P pred) const
{
	do {
		const Hash& ih = hash[i];
		if(sh == ih.hash && pred(i))
			break;
		i = ih.next;
	}
	while(i >= 0);
	return i;
}

template <typename P>
force_inline
int HashBase::Find(dword h, P pred) const
{
	h = Smear(h);
	return FindFrom(map[h & mask].first, h, pred);
}

template <class T>
class Index {
	Vector<T> key;
	HashBase  hash;

public:
	void Add(const T& k)        { key.Add(k); hash.Add(GetHashValue(k)); }
	int  Find(const T& k) const { return hash.Find(GetHashValue(k), [&](int i) { return key[i] == k; }); }
};

};

int nnn = 200;
int val = 0;
int sum = 0;

#define N 1000

void Benchmark()
{
	Vector<String> data;
	for(int i = 0; i < N; i++)
		data.Add(AsString(i));
	int rep = max(100000000 / N, 1);
	for(int n = 0; n < rep; n++) {
		{
			New::Index<int> test;
			{
				RTIMING("New int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("New int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
		}
		{
			Index<int> test;
			{
				RTIMING("Old int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("Old int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
		}
		{
			New::Index<String> test;
			{
				RTIMING("New string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("New string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
		}
		{
			Index<String> test;
			{
				RTIMING("Old string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("Old string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
		}
	}
	RDUMP(sum);
}

CONSOLE_APP_MAIN
{
	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(New::Index<int>));

#ifndef _DEBUG
	Benchmark();
#endif

	New::Index<int> test;
	for(int i = 0; i < 10000; i++) {
		test.Add(i);
		if(test.Find(i) == i)
			sum++;
		ASSERT(test.Find(i) == i);
	}

	DUMP(sum);
	DUMP(New::second);
	DUMP(New::first_overflow);
	DUMP(New::next_overflow);

#if 0
	New::HashBase h;
	for(int i = 0; i < nnn; i++) {
		val = Random(20);
		RLOG("--- " << val);
		h.Add(val);
		h.Find(val, [&](int i) { LOG(i << " " << h[i]); sum += i; return false; });
	}
#endif
}
