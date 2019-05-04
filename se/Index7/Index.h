#ifndef _Index6_Index_h_
#define _Index6_Index_h_

#include <Core/Core.h>

using namespace Upp;

namespace New {

struct HashBase {
	enum { HIBIT = 0x80000000 };

	struct Bucket {
		int first = -1;
		int last = -1;
	};
	
	struct Hash : Moveable<Hash> {
		dword hash; // also link for unlinked items...
		int   next;
	};
	
	Bucket      *map;
	Vector<Hash> hash;
	dword        mask;
	int          unlinked;
	
	static Bucket empty[1];

	static dword Smear(dword h)          { return FoldHash(h) | HIBIT; }

	void AddOverflow(Bucket& m, int ii);
	void Reindex();
	void GrowMap();
	void Link(int ii, dword h);
	void Del(int ii);
	void Ins(int ii, dword sh);
	void AddS(dword sh);
	void Free();
	
	dword operator[](int i) const        { return hash[i].hash; }

	void Add(dword h);
	
	template <typename P>
	int FindFrom(int ii, dword sh, P pred) const;

	template <typename P>
	int Find(dword h, P x) const;
	
	void Unlink(int i);
	template <typename P>
	void UnlinkKey(dword h, P pred);
	bool IsUnlinked(int i) const         { return hash[i].hash == 0; }
	bool HasUnlinked() const             { return unlinked >= 0; }
	int  PutUnlinked(dword h);

	void Set(int ii, dword h);
	
	void Clear();
	
	String Dump() const;
	
	HashBase();
	~HashBase();
};

template <class T>
class Index {
	Vector<T> key;
	HashBase  hash;

	void SweepGrow();

public:
	void Add(const T& k)             { key.Add(k); hash.Add(GetHashValue(k)); }

	int  Find(const T& k) const      { return hash.Find(GetHashValue(k), [&](int i) { return key[i] == k; }); }
	int  FindNext(int i) const       { const T& k = key[i]; return hash.FindFrom(hash.hash[i].next, hash[i], [&](int i) { return key[i] == k; }); }

//	void Push(const T& k)            { if(hash.WillGrow()) SweepGrow(); Add(k); }
	
	void Put(const T& k)             { dword h = GetHashValue(k); if(hash.HasUnlinked()) key[hash.PutUnlinked(h)] = k; else { key.Add(k); hash.Add(h); }}

	void Unlink(int i)               { hash.Unlink(i); }
	bool IsUnlinked(int i) const     { return hash.IsUnlinked(i); }
	void UnlinkKey(const T& k)       { hash.UnlinkKey(GetHashValue(k), [&](int i) { return key[i] == k; }); }

	const T& operator[](int i) const { return key[i]; }
	int  GetCount() const            { return key.GetCount(); }
	
	void  Clear()                    { key.Clear(); hash.Clear(); }
	
	String Dump() const              { return hash.Dump(); }
};

};

#include "Index.hpp"

#endif
