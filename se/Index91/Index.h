#ifndef _Index6_Index_h_
#define _Index6_Index_h_

#include <Core/Core.h>

using namespace Upp;

namespace New {

struct HashBase {
	enum { HIBIT = 0x80000000 };

	struct Hash : Moveable<Hash> {
		dword hash;
		int   prev;
	};
	
	int         *map;
	int         *next;
	Hash        *hash;
	dword        mask;
	int          unlinked;

	void MakeMap();
	
	static int empty[1];

	static dword Smear(dword h)          { return FoldHash(h) | HIBIT; }

	void Link(int& m, Hash& hh, int ii);
	void Link(int ii, dword sh);
	void Del(int& m, Hash& hh, int ii);
	void Ins(int& m, Hash& hh, int ii);

	void Reindex(int count);
	void GrowMap(int count);
	void FreeMap();
	void Free();

	int  PutUnlinked(dword sh);
	void Set(int ii, dword h);
	
	void Sweep();
	
	void Reserve(int n);
	void Shrink();
	
	void Clear();
	void Trim(int n = 0);

	String Dump(int count) const;
	
	HashBase();
	~HashBase();
};

template <class K, class T>
class VectorMap;

template <class T>
class Index : HashBase {
	Vector<T> key;

	static dword Smear(const T& k)   { return HashBase::Smear(GetHashValue(k)); }

	int  FindFrom(int i, const T& k, int end) const;
	int  FindBack(int i, const T& k, int end) const;

	void GrowAdd(const T& key, dword sh);
	void FinishAdd(int& m, int ii, dword sh);
	void AddS(int& m, const T& k, dword sh);
	void AddS(const T& key, dword sh);

	template <class OP>
	int FindAdd(const T& k, OP op);

	template <typename, typename> friend class VectorMap;

public:
	void Add(const T& k)             { AddS(k, Smear(k)); }

	int  Find(const T& k) const;
	int  FindNext(int i) const;
	int  FindLast(const T& k) const;
	int  FindPrev(int i) const;
	
	int  FindAdd(const T& k)         { return FindAdd(k, []{}); }

	int  Put(const T& k);

	void Unlink(int i);
	bool IsUnlinked(int i) const     { return hash[i].hash == 0; }
	void UnlinkKey(const T& k);
	bool HasUnlinked() const         { return unlinked >= 0; }

	void Set(int i, const T& k);

	const T& operator[](int i) const { return key[i]; }
	int  GetCount() const            { return key.GetCount(); }
	
	void  Clear()                    { key.Clear(); HashBase::Clear(); }
	
	void  Trim(int n)                { key.Trim(n); HashBase::Trim(n); }
	
	String ToString() const;
};


template <class K, class T>
class VectorMap {
	Index<K>  key;
	Vector<T> value;

public:
	int GetCount() const             { return key.GetCount(); }
	const T& operator[](int i) const { return value[i]; }
	const K& GetKey(int i) const     { return key[i]; }
	
	T& GetAdd(const K& k, const T& x) { return value[key.FindAdd(k, [&] { value.Add(x); })]; }
};

};

#include "Index.hpp"

#endif
