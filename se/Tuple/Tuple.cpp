#include <Core/Core.h>

using namespace Upp;

template <int N, typename... T>
struct TupleN;

template <int I>
struct IndexI__ {};

template <typename V, typename T, typename I>
const V& GetFromTuple(const T& t, const I&);

template <typename... T>
struct Tup;

template <typename A>
struct TupleN<1, A>
{
	A a;

	Value Get(int i) const   { ASSERT(i == 0); return a; }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<0>&) -> decltype(t.a)
{
	return t.a;
}

template <typename A, typename B>
struct TupleN<2, A, B> : TupleN<1, A>
{
	B b;

	Value Get(int i) const { return i == 1 ? (Value)b : TupleN<1, A>::Get(i); }
	
	template <typename AA, typename BB>
	operator Tup<AA, BB>() const           { Tup<AA, BB> t; t.a = (AA)a; t.b = (BB)b; return t; }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<1>&) -> decltype(t.b)
{
	return t.b;
}

template <typename A, typename B, typename C>
struct TupleN<3, A, B, C> : TupleN<2, A, B>
{
	C c;
	
	Value Get(int i) const { return i == 2 ? (Value)c : TupleN<2, A, B>::Get(i); }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<2>&) -> decltype(t.c)
{
	return t.c;
}

template <typename... T>
struct Tup : TupleN<sizeof...(T), T...> {
	typedef TupleN<sizeof...(T), T...> BaseClass;
	
	Value Get(int i) const { return BaseClass::Get(i); }

	template <int I>
	auto Get() const -> decltype(GetFromTuple(*this, IndexI__<I>())) { return GetFromTuple(*this, IndexI__<I>()); }
};

struct NonVal {
	Tup<int, double> h;

	int x;
	int y;
};

CONSOLE_APP_MAIN
{
	Tup<int, String> x;
	x.a = 1;
	x.b = "HHH";
	
	Tup<int, Point, String> z;
	z.a = 0;
	z.b = Point(1, 2);
	z.c = "HHH";
	
	DDUMP(z.c);
	
	DDUMP(z.Get(0));
	DDUMP(z.Get(1));
	DDUMP(z.Get(2));
	
	DDUMP(z.Get<0>());
	DDUMP(z.Get<1>());
	DDUMP(z.Get<2>());
	
	Tup<NonVal, int> y;
	y.a.x = 5;
	
	Tup<int, int> it;
	it.a = 10;
	it.b = 11;
	Tup<float, float> ft = it;
	DDUMP(ft.a / 7);
	DDUMP(ft.b);
}
