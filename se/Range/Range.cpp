#include <Core/Core.h>

using namespace Upp;

template <class I>
class RangeRef {
	I   l;
	int count;

public:
	typedef decltype(*l) value_type;
	
	typedef value_type ValueType;

	typedef ptrdiff_t                        difference_type;
    typedef std::random_access_iterator_tag  iterator_category;
//    typedef T                                value_type;
  //  typedef T                                pointer;
    // typedef T                                reference;
//	typedef ConstIterator const_iterator; \
//	typedef const T&      const_reference; \
//	typedef int           size_type; \
//	typedef int           difference_type; \

	int GetCount() const { return count; }

	value_type& operator[](int i) const { ASSERT(i >= 0 && i < count); return l[i]; }
	I  begin() const { return l; }
	I  end() const { return l + count; }
	I  Begin() const { return l; }
	I  End() const { return l + count; }

	RangeRef(I begin, int count) : l(begin), count(count) {}
	RangeRef(I begin, I end)                              { l = begin; count = end - begin; }
};

template <class I>
RangeRef<I> Range(I l, I h)
{
	return RangeRef<I>(l, h);
}

template <class I>
RangeRef<I> Range(I l, int count)
{
	return RangeRef<I>(l, count);
}

template <class C>
auto Range(C& c, int pos, int count)
{
	return Range(c.begin() + pos, count);
}

template <class F>
struct FunctionRangeClass {
	F   f;
	int count;
	
	typedef decltype(f(1)) value_type;
	typedef value_type ValueType;
	
	value_type operator[](int i) const { return f(i); }
	int GetCount() const { return count; }
	
	typedef ConstIIterator<FunctionRangeClass> Iterator;
	
	Iterator begin() const { return Iterator(*this, 0); }
	Iterator end() const { return Iterator(*this, count); }

	Iterator Begin() const { return Iterator(*this, 0); }
	Iterator End() const { return Iterator(*this, count); }

	FunctionRangeClass(F f, int count) : f(f) {}
};

template <class F>
FunctionRangeClass<F> FunctionRange(F f, int count)
{
	return FunctionRangeClass<F>(f, count);
}

CONSOLE_APP_MAIN
{
	Vector<int> h = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Sort(Range(h, 2, 5));
	DDUMP(h);
	Sort(Range(h.begin() + 1, h.end()));
	DDUMP(h);
	Sort(Range(h.begin(), 5), std::greater<int>());
	DDUMP(h);

	DDUMPC(FunctionRange([](int i) { return i * i; }, 200));
}
