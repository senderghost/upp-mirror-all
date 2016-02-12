#include <Core/Core.h>

using namespace Upp;

void Foo(const String& h)
{
	DDUMP(h);
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
	
	DDUMP(Sum(v));
	
	DDUMP(FindMin(v));
	DDUMP(FindMax(v));
	
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

//	h = [] { LOG("FUN2"); };

	
//	Execute([=] { LOG("Execute"); });
/*	
	h();
	h();
*/
}
