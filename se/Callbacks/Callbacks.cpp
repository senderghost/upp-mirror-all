#include <Core/Core.h>

using namespace Upp;

void Foo(const String& h)
{
	DUMP(h);
}

void Execute(Callback cb)
{
	cb();
}

/*
template <class A, class B>
struct Tuple {
	A a;
	B b;
};

template <class A, class B, class C>
struct Tuple {
	A a;
	B b;
	C c;
};
*/
/*
template <size_t N, typename... T>
struct Choose;

template <size_t N, typename H, typename... T>
struct Choose <N, H, T...> : Choose <N-1, T...> { };


template <Args... args>
struct Tuple : TupleN< sizeof(args...) >
{
	
};
*/

template <int N, typename... T>
struct TupleN;

template <typename A>
struct TupleN<1, A>
{
	typedef A type;

	A a;
};

template <typename B, typename... T>
struct TupleN<2, B, T...> : TupleN<1, T...>
{
	B b;
};

template <typename... T>
struct Tuple : TupleN<sizeof...(T), T...>
{
};

/*
template <int N, typename C, typename... T>
struct TupleN<3, C, T...> : TupleN<2, T...>
{
	C c;
};

template <int N, typename D, typename... T>
struct TupleN<4, D, T...> : TupleN<3, T...>
{
	D d;
};
*/

namespace Upp {
void *MemoryAlloc_(size_t sz);
};

CONSOLE_APP_MAIN
{
	for(int i : { 16, 23, 32, 200, 1000, 100000 }) {
		DDUMP(i);
		void *ptr1 = MemoryAlloc(i);
		DDUMP(ptr1);
	}

	struct Prec {
		Prec   *ptr;
		Atomic  n;
	};
	
	DDUMP(sizeof(Prec));

	DDUMP(sizeof(Atomic));

	{
		Vector<int> a{1, 2}, b;
		
		a << 1 << 2 << 3;
		
		b = clone(a);
		DUMP(a);
		DUMP(b);
		a = pick(b);
		DUMP(a);
		DUMP(b);
	}
	
	
	TupleN<2, int, String> tpl;
/*	
	Tuple<int, String> tpl2;
	tpl2.a = 10;
	tpl2.b = 20;
	
*/	Cout() << String("Hello!") << 1;

	auto x = callback(Foo);
	x("AAA");
	
	auto y = callback1(x, "B");
	y();

	Callback h([=] { LOG("FUN"); });
	Callback h1([=] { LOG("FUN"); });
	
	
	Vector<int> v { 1, 2, 3, 2, 1 };
	
	DUMP(Sum(v));
	
	DUMP(FindMin(v));
	DUMP(FindMax(v));
	
	v.Add(123);
	v.Add(pick(123));

	{
		Vector<String> vs;
		String h;
		vs.Add(h);
		vs.Add(pick(h));
		vs.Add(h + "123");
		vs.Add("aaa");
	}
	
	String a = AsString(123) + "123";
	
	RDUMP(a);

	WString ws;
	ws = a.ToWString();

	RDUMP(ws);
//	h = [] { LOG("FUN2"); };

	
//	Execute([=] { LOG("Execute"); });
/*	
	h();
	h();
*/
}
