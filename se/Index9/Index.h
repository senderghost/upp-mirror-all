#ifndef _Index6_Index_h_
#define _Index6_Index_h_

#include <Core/Core.h>

using namespace Upp;

extern int find_counter;
extern int loop_counter;

namespace New {

struct HashBase {
	enum { HIBIT = 0x80000000 };

	struct Hash : Moveable<Hash> {
		int   next; // also link for unlinked items...
		dword hash;
		int   prev;
	};
	
	int         *map;
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

	void Set(int ii, dword h);
	
	void Sweep();
	
	void Reserve(int n);
	void Shrink();
	
	Vector<int> GetUnlinked() const;
	
	void Clear();
	void Trim(int n = 0);
	
	HashBase();
	~HashBase();
};

template <class K, class T> class VectorMap;

template <class T>
class Index : HashBase {
	Vector<T> key;

	static dword Smear(const T& k)   { return HashBase::Smear(GetHashValue(k)); }

	int  FindFrom(int i, dword sh, const T& k, int end) const;
	int  FindBack(int i, dword sh, const T& k, int end) const;


	template <typename U> void GrowAdd(U&& k, dword sh);
	template <typename U> void AddS(int& m, U&& k, dword sh);
	template <typename U> void AddS(U&& k, dword sh);

	template <class OP, class U> int FindAdd(U&& k, OP add_op);

	template <typename, typename> friend class VectorMap;

public:
	void Add(const T& k)             { AddS(k, Smear(k)); }
	void Add(T&& k)                  { AddS(pick(k), Smear(k)); }

	int  Find(const T& k) const;
	int  FindNext(int i) const;
	int  FindLast(const T& k) const;
	int  FindPrev(int i) const;
	
	int  FindAdd(const T& k)         { return FindAdd(k, []{}); }
	int  FindAdd(T&& k)              { return FindAdd(pick(k), []{}); }

	int  Put(const T& k);

	void Unlink(int i);
	bool IsUnlinked(int i) const     { return hash[i].hash == 0; }
	void UnlinkKey(const T& k);
	bool HasUnlinked() const         { return unlinked >= 0; }
	Vector<int> GetUnlinked() const  { return HashBase::GetUnlinked(); }

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
