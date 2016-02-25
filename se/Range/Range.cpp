#include <Core/Core.h>

using namespace Upp;

template <class Range>
void Sort(Range&& x)
{
	Sort(x);
}

template <class Range, class Predicate>
void Sort(Range&& x, Predicate order)
{
	Sort(x, order);
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

	DDUMPC(ConstRange(12, 5));
}
