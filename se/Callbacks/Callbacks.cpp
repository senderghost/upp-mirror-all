#include <Core/Core.h>

#include <atomic>
#include <thread>
#include <mutex>

using namespace Upp;

template <class V>
class ValIIterator {
	typedef ValueTypeOfArray<V> T;

	const V       *cont;
	int            ii;

public:
	T        operator*() const             { return (*cont)[ii]; }
	T        operator[](int i) const       { return (*cont)[ii + i]; }

	ValIIterator& operator++()           { ++ii; return *this; }
	ValIIterator& operator--()           { --ii; return *this; }
	ValIIterator  operator++(int)        { ValIIterator t = *this; ++ii; return t; }
	ValIIterator  operator--(int)        { ValIIterator t = *this; --ii; return t; }

	ValIIterator& operator+=(int d)      { ii += d; return *this; }
	ValIIterator& operator-=(int d)      { ii -= d; return *this; }

	ValIIterator  operator+(int d) const { return ValIIterator(*cont, ii + d); }
	ValIIterator  operator-(int d) const { return ValIIterator(*cont, ii - d); }

	int  operator-(const ValIIterator& b) const   { return ii - b.ii; }

	bool operator==(const ValIIterator& b) const  { return ii == b.ii; }
	bool operator!=(const ValIIterator& b) const  { return ii != b.ii; }
	bool operator<(const ValIIterator& b) const   { return ii < b.ii; }
	bool operator>(const ValIIterator& b) const   { return ii > b.ii; }
	bool operator<=(const ValIIterator& b) const  { return ii <= b.ii; }
	bool operator>=(const ValIIterator& b) const  { return ii >= b.ii; }

	operator bool() const     { return ii < 0; }

	ValIIterator()          {}
	ValIIterator(const V& _cont, int ii) : cont(&_cont), ii(ii) {}

	STL_ITERATOR_COMPATIBILITY
};

struct IotaClass {
	int count;
	
	int operator[](int i) const               { return i; }
	int GetCount() const                      { return count; }
	
	typedef ValIIterator<IotaClass> Iterator;
	
	Iterator begin() const { return Iterator(*this, 0); }
	Iterator end() const { return Iterator(*this, count); }

	String   ToString() const                            { return AsStringArray(*this); }
	template <class B> bool operator==(const B& b) const { return IsEqualRange(*this, b); }
	template <class B> bool operator!=(const B& b) const { return !operator==(b); }
	template <class B> int  Compare(const B& b) const    { return CompareRanges(*this, b); }
	template <class B> bool operator<=(const B& x) const { return Compare(x) <= 0; }
	template <class B> bool operator>=(const B& x) const { return Compare(x) >= 0; }
	template <class B> bool operator<(const B& x) const  { return Compare(x) < 0; }
	template <class B> bool operator>(const B& x) const  { return Compare(x) > 0; }

	IotaClass(int count) : count(count) {}

// deprecated:
	typedef int        value_type;
	typedef value_type ValueType;
};

inline IotaClass Iota(int count) { return IotaClass(count); }

template <class C, class Fn>
class FnRangeClass {
	C   src;
	Fn  fn;

public:
	typedef typename std::remove_reference<decltype(fn(src[0]))>::type value_type;

	int GetCount() const                                 { return src.GetCount(); }
	value_type operator[](int i) const                   { return fn(src[i]); }

	typedef ValIIterator<FnRangeClass> Iterator;

	Iterator  begin() const                              { return Iterator(*this, 0); }
	Iterator  end() const                                { return Iterator(*this, GetCount()); }

	String   ToString() const                            { return AsStringArray(*this); }
	template <class B> bool operator==(const B& b) const { return IsEqualRange(*this, b); }
	template <class B> bool operator!=(const B& b) const { return !operator==(b); }
	template <class B> int  Compare(const B& b) const    { return CompareRanges(*this, b); }
	template <class B> bool operator<=(const B& x) const { return Compare(x) <= 0; }
	template <class B> bool operator>=(const B& x) const { return Compare(x) >= 0; }
	template <class B> bool operator<(const B& x) const  { return Compare(x) < 0; }
	template <class B> bool operator>(const B& x) const  { return Compare(x) > 0; }

	FnRangeClass(const C& src, Fn&& fn) : src(src), fn(pick(fn)) {}
};

template <class C, class Fn>
FnRangeClass<C, Fn> FnRange(const C& src, Fn&& fn)
{
	return FnRangeClass<C, Fn>(src, pick(fn));
}

CONSOLE_APP_MAIN
{
	DUMP(Iota(20));
	
	DDUMP(FnRange(Iota(20), [](int i) { return 7 * i; }));
	
	for(auto i: Iota(20))
		DDUMP(i);

	for(auto i: SubRange(FnRange(Iota(20), [](int i) { return -i; }), 4, 4))
		DDUMP(i);

	Vector<int> h = { 6, 1, 3, 56, 8, 223, 12, 2, 6, 3 };
	std::begin(h);
	Sort(SubRange(h, 1, 5));
	DUMP(h);
	Reverse(SubRange(h, 0, 4));
	DUMP(h);
}
