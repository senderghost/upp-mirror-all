#ifndef _Index6_Index_h_
#define _Index6_Index_h_

#include <Core/Core.h>

using namespace Upp;

extern int find_counter;
extern int loop_counter;

namespace New {


template <class K, class T>
class VectorMap {
	Index<K>  key;
	Vector<T> value;

public:
	int GetCount() const             { return key.GetCount(); }
	const T& operator[](int i) const { return value[i]; }
	const K& GetKey(int i) const     { return key[i]; }
	
	T& GetAdd(const K& k, const T& x) { return value[key.FindAdd(k, [&] { value.Add(x); })]; }
	T& GetPut(const K& k, const T& x) { int q = key.FindPut(k); return q < value.GetCount() ? value[q] : value.Add(x); }
};


};

#include "Index.hpp"

#endif
