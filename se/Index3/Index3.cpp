#include <Core/Core.h>

using namespace Upp;

namespace New {
	
inline
dword Smear(dword h)
{
	return FoldHash(h);
//	h = SwapEndian32(0xa3613c16 * h);
//	return SwapEndian32(0xa3613c16 * h);
}

struct HashBase {
	enum {
		OBLK = 3
	};
	
	struct Overflow : Moveable<Overflow> {
		int index[OBLK];
		int next; // next item or count of index in the last item
	};

	struct Slot {
		int a = -1; // first index or first slot
		int b = -1; // last index or last slot
	};
	
	Buffer<Slot>     map;
	Vector<dword>    hash;
	Vector<Overflow> overflow;
	dword            mask;
	int              unlinked;
	
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
		Overflow& o = overflow.Add();
		o.index[0] = m.a;
		o.index[1] = m.b;
		o.index[2] = ii;
		o.next = 3;
		m.a = m.b = UNSIGNED_HIBIT | oi;
	}
	else {
		next_overflow++;
		DLOG("Next overflow " << ii);
		int last = m.b & ~UNSIGNED_HIBIT;
		Overflow& l = overflow[last];
		if(l.next < OBLK)
			l.index[l.next++] = ii;
		else {
			l.next = overflow.GetCount();
			m.b = l.next | UNSIGNED_HIBIT;
			Overflow& nl = overflow.Add();
			nl.index[0] = ii;
			nl.next = 1;
		}
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
		LOG("Overflow " << ii << ", count: " << hash.GetCount() << ", mask: " << FormatIntHex(mask));
		AddOverflow(m, ii);
	}
}

void HashBase::Reindex()
{
	DLOG("Reindex");
	DDUMP(first_overflow);
	DDUMP(next_overflow);
	DDUMP(second);
	second = first_overflow = next_overflow = 0;

	overflow.Trim(0);
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
	if(ii + (ii) > (int)mask)
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
	int oi = m.a & ~UNSIGNED_HIBIT;
	int last = m.b & ~UNSIGNED_HIBIT;
	while(oi < last) {
		const Overflow& o = overflow[oi];
		if(pred(o.index[0])) return o.index[0];
		if(pred(o.index[1])) return o.index[1];
		if(pred(o.index[2])) return o.index[2];
		oi = o.next;
	}
	const Overflow& o = overflow[oi];
	for(int i = 0; i < o.next; i++)
		if(pred(o.index[i])) return o.index[i];
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

CONSOLE_APP_MAIN
{
	New::Index<String> test;
	
	for(int i = 0; i < 10000; i++) {
		DLOG("===========");
		DDUMP(i);
		String k = AsString(i);
		test.Add(k);
		int q = test.Find(k);
		DDUMP(q);
	}
	
	DDUMP(New::second);
	DDUMP(New::first_overflow);
	DDUMP(New::next_overflow);

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
