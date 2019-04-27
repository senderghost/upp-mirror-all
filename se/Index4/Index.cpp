#include <Core/Core.h>

using namespace Upp;

namespace New {
	
inline
dword Smear(dword h)
{
	return FoldHash(h) ^ h;
//	h = SwapEndian32(0xa3613c16 * h);
//	return SwapEndian32(0xa3613c16 * h);
}

struct HashBase {
	struct Slot {
		int a = -1; // first index or first slot
		int b = -1; // last index or last slot
	};
	
	Buffer<Slot>        map;
	Vector<dword>       hash;
	Vector<Vector<int>> overflow;
	dword               mask;
	int                 unlinked;
	
	void AddOverflow(Slot& m, int ii);
	void Reindex();
	void GrowMap();
	void Add(int ii, dword h);
	
	void Add(dword h);
	dword operator[](int i) const { return hash[i]; }
	
	template <typename P>
	int  Find(dword h, P x) const;
	
	HashBase() { map.Alloc(8); mask = 7; }
};

int second;
int first_overflow;
int next_overflow;

void HashBase::AddOverflow(Slot& m, int ii)
{
	first_overflow++;
	if(m.a >= 0) { // need to convert to overflow
		int oi = overflow.GetCount();
		Vector<int>& o = overflow.Add();
		o.Add(m.a);
		o.Add(m.b);
		o.Add(ii);
		m.a = UNSIGNED_HIBIT | oi;
	}
	else {
		next_overflow++;
		overflow[m.a & ~UNSIGNED_HIBIT].Add(ii);
	}
}

force_inline
void HashBase::Add(int ii, dword h)
{
	Slot& m = map[h & mask];
	if(m.a == -1)
		m.a = ii;
	else
	if(m.b == -1) {
		m.b = ii;
		second++;
	}
	else {
		LOG("Overflow " << ii << ", count: " << hash.GetCount() << ", mask: " << mask);
		AddOverflow(m, ii);
	}
}

void HashBase::Reindex()
{
	DUMP(second);
	DUMP(first_overflow);
	DUMP(next_overflow);
	LOG("============= Reindex");
	DUMP(hash.GetCount());
	DUMP(mask);

	second = first_overflow = next_overflow = 0;

	overflow.Clear();
	map.Alloc(mask + 1);
	for(int i = 0; i < hash.GetCount(); i++)
		Add(i, hash[i]);
}

void HashBase::GrowMap()
{
	mask = (mask << 1) | 1;
	Reindex();
}

force_inline
void HashBase::Add(dword h)
{
	h = Smear(h);
	int ii = hash.GetCount();
	hash.Add(h);
	if(ii + (ii >> 2) > (int)mask)
		GrowMap();
	Add(ii, h);
}

template <typename P>
force_inline
int HashBase::Find(dword h, P pred) const
{
	h = Smear(h);
	const Slot& m = map[h & mask];
	if(m.a >= 0)
		return pred(m.a) ? m.a : m.b >= 0 && pred(m.b) ? m.b : -1;
	if(m.a == -1)
		return -1;
	for(int ii : overflow[m.a & ~UNSIGNED_HIBIT])
		if(pred(ii))
			return ii;
	return -1;
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

void Benchmark()
{
	for(int n = 0; n < 100; n++) {
		{
			RTIMING("New int");
			New::Index<int> test;
			for(int i = 0; i < 1000000; i++) {
				test.Add(i);
				if(test.Find(i) == i)
					sum++;
			}
		}
		{
			RTIMING("Old int");
			Index<int> test;
			for(int i = 0; i < 1000000; i++) {
				test.Add(i);
				if(test.Find(i) == i)
					sum++;
			}
		}
		{
			RTIMING("New String");
			New::Index<String> test;
			for(int i = 0; i < 1000000; i++) {
				String k = AsString(i);
				test.Add(k);
				if(test.Find(k) == i)
					sum++;
			}
		}
		{
			RTIMING("Old String");
			Index<String> test;
			for(int i = 0; i < 1000000; i++) {
				String k = AsString(i);
				test.Add(k);
				if(test.Find(k) == i)
					sum++;
			}
		}
	}
	RDUMP(sum);
}

CONSOLE_APP_MAIN
{
	New::Index<int> test;
	for(int i = 0; i < 1000000; i++) {
		test.Add(i);
		if(test.Find(i) == i)
			sum++;
	}
	
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
