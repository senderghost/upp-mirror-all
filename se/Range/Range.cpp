#include <Core/Core.h>

using namespace Upp;

template <class I>
class RangeRef {
	I   l;
	int count;

public:
	typedef decltype(*l) ValueType;

	int GetCount() const { return count; }
	decltype(*l)& operator[](int i) const { ASSERT(i >= 0 && i < count); return l[i]; }
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

CONSOLE_APP_MAIN
{
	Vector<int> h = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Sort(Range(h, 2, 5));
	DDUMP(h);
}
