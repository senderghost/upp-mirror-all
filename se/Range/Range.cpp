#include <Core/Core.h>

using namespace Upp;
/*
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
*/
CONSOLE_APP_MAIN
{
	Array<Stream> file;
	file.Create<FileIn>("/home/centrum/1320.log");

	Vector<int> h = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	Sort(Range(h, 2, 5).Write());
	DDUMP(h);
	Sort(Range(h.begin() + 1, h.end()).Write());
	DDUMP(h);
//	Sort(Range(h.begin(), 5), std::greater<int>());
	DDUMP(h);
	
	DDUMPC(FilterRange(h, [=](int x) { return x & 1; }));
	
	for(int i = 0; i < 10; i++)
		h.Add(Random(25));

	DDUMP(FilterRange(h, [=](int x) { return x & 1; }));
	DDUMP(FilterRange(h, [=](int x) { return !(x & 1); }));

	Sort(FilterRange(h, [=](int x) { return x & 1; }).Write());
	Sort(FilterRange(h, [=](int x) { return !(x & 1); }).Write(), std::greater<int>());
	DDUMP(h);

	DDUMPC(ConstRange(12, 5));
	
	h.Set(5, ConstRange(123, 3));
	DDUMP(h);
	
	h.Insert(5, ConstRange(10, 5));
	DDUMP(h);
	
	String vs = String::GetVoid();
	DDUMP(vs.IsVoid());
	vs.Clear();
	DDUMP(vs.IsVoid());
	
	Array<int> ah;
	ah.Append(h);
	DDUMP(ah);
	ah.Insert(4, ConstRange(54321, 2));
	DDUMP(ah);
}
