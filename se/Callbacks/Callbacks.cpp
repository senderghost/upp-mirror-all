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
CONSOLE_APP_MAIN
{
	Cout() << String("Hello!") << 1;

	auto x = callback(Foo);
	x("AAA");
	
	auto y = callback1(x, "B");
	y();

	Callback h = [=] { LOG("FUN"); };
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
