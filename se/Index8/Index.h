#ifndef _Index6_Index_h_
#define _Index6_Index_h_

#include <Core/Core.h>

using namespace Upp;

namespace New {

struct HashBase {
	enum { HIBIT = 0x80000000 };

	struct Hash : Moveable<Hash> {
		dword hash; // also link for unlinked items...
		int   next;
		int   prev;
	};
	
	int         *map;
	Vector<Hash> hash;
	dword        mask;
	int          unlinked;

	void MakeMap();
	
	static int empty[1];

	static dword Smear(dword h)          { return FoldHash(h) | HIBIT; }

	void Link(int& m, Hash& hh, int ii);
	void Link(int ii, dword sh);

	void Reindex();
	void GrowMap();
	void AddS(dword sh);
	void Free();

	void Del(int ii);
	void Ins(int ii, dword sh);
	
	dword operator[](int i) const        { return hash[i].hash; }
	int   GetCount() const               { return hash.GetCount(); }

	void Add(dword h);
	
	void Unlink(int i);
	template <typename P>
	void UnlinkKey(dword h, P pred);
	int  PutUnlinked(dword h);
	bool IsUnlinked(int i) const     { return hash[i].hash == 0; }

	void Set(int ii, dword h);
	
	void Sweep();
	
	void Reserve(int n);
	void Shrink();
	
	void Clear();
	void Trim(int n = 0);

	String Dump() const;
	void Check();
	
	HashBase();
	~HashBase();
};

template <class T>
class Index : HashBase {
	Vector<T> key;

	static dword Smear(const T& k)   { return HashBase::Smear(GetHashValue(k)); }
	int   FindFrom(int ii, dword sh, const T& k) const;

public:
	void Add(const T& k)             { key.Add(k); HashBase::Add(GetHashValue(k)); }

	int  Find(const T& k) const;
	int  FindNext(int i) const;
	
	int  FindAdd(const T& k);

	void Put(const T& k)             { dword h = GetHashValue(k); if(HasUnlinked()) key[PutUnlinked(h)] = k; else { key.Add(k); HashBase::Add(h); }}
	void Set(int i, const T& k)      { key[i] = k; HashBase::Set(i, GetHashValue(k)); }

	void Unlink(int i)               { HashBase::Unlink(i); }
	bool IsUnlinked(int i) const     { return hash[i].hash == 0; }
	void UnlinkKey(const T& k)       { HashBase::UnlinkKey(GetHashValue(k), [&](int i) { return key[i] == k; }); }
	bool HasUnlinked() const         { return unlinked >= 0; }

	const T& operator[](int i) const { return key[i]; }
	int  GetCount() const            { return key.GetCount(); }
	
	void  Clear()                    { key.Clear(); HashBase::Clear(); }
	
	void  Trim(int n)                { key.Trim(n); HashBase::Trim(n); }
	
	String Dump() const              { return HashBase::Dump(); }
};

};

#include "Index.hpp"

#endif
