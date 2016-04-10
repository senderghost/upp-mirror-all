#include <Core/Core.h>

using namespace Upp;

template <int N, typename... T>
struct TupleN;

template <int I>
struct IndexI__ {};

template <typename V, typename T, typename I>
const V& GetFromTuple(const T& t, const I&);

template <typename... T>
struct Tuple;

template <typename A>
struct TupleN<1, A>
{
	A a;

	Value Get(int i) const                 { ASSERT(i == 0); return a; }
	void  Set(int i, const Value& v) const { ASSERT(i == 0); a = v; }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<0>&) -> decltype(t.a)
{
	return t.a;
}

template <typename A, typename B>
struct TupleN<2, A, B> : TupleN<1, A>
{
	typedef TupleN<1, A> Base;
	B b;

	bool operator==(const TupleN& x) const    { return Base::operator==(x) && b == x.b; }
	int  Compare(const TupleN& x) const       { int q = Base::Compare(x); return q ? q : SgnCompare(b, x.b); }

	void ToHash(CombineHash& h)               { Base::ToHash(h); h(b); }
	void ToString(String& r)                  { Base::ToString(r); r << ", " << b; }
	
	void Serialize(Stream& s)                 { Base::Serialize(s); s % b; }
	
	int  GetCount() const                     { return 2; }

	Value Get(int i) const                    { return i == 1 ? (Value)b : Base::Get(i); }
	void  Set(int i, const Value& v) const    { if(i == 1) b = v; else Base::Set(i, v); }
	
	template <typename AA, typename BB>
	operator Tuple<AA, BB>()                  { Tuple<AA, BB> t; t.a = (AA)a; t.b = (BB)b; return t; }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<1>&) -> decltype(t.b)
{
	return t.b;
}

template <typename A, typename B, typename C>
struct TupleN<3, A, B, C> : TupleN<2, A, B>
{
	typedef TupleN<2, A, B> Base;
	C c;
	
	Value Get(int i) const                   { return i == 2 ? (Value)c : TupleN<2, A, B>::Get(i); }
	void  Set(int i, const Value& v)         { if(i == 2) c = v; else Base::Set(i, v); }
};

template <typename T>
auto GetFromTuple(const T& t, const IndexI__<2>&) -> decltype(t.c)
{
	return t.c;
}

template <typename... T>
struct Tuple : TupleN<sizeof...(T), T...> {
	typedef TupleN<sizeof...(T), T...> BaseClass;
	
	Value Get(int i) const { return BaseClass::Get(i); }

	template <int I>
	auto Get() const -> decltype(GetFromTuple(*this, IndexI__<I>())) { return GetFromTuple(*this, IndexI__<I>()); }
};

struct NonVal {
	Tuple<int, double> h;

	int x;
	int y;
};

CONSOLE_APP_MAIN
{
	Tuple<int, String> x;
	x.a = 1;
	x.b = "HHH";
	
	Tuple<int, Point, String> z;
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
	
	Tuple<NonVal, int> y;
	y.a.x = 5;
	
	Tuple<int, int> it;
	it.a = 10;
	it.b = 11;
	Tuple<float, float> ft = it;
	DDUMP(ft.a / 7);
	DDUMP(ft.b);
}
