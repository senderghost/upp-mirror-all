#include <Core/Core.h>

using namespace Upp;

struct Foo : WithClone<Foo> {
	Foo() {}
	Foo(Foo&&) { LOG("Foo move constructor"); }
	Foo& operator=(Foo&&) { LOG("Foo move assignment"); return *this; }
	Foo(const Foo& x, int) {
		LOG("Foo clone");
	}
};

struct Bar1 {
	String a;
	Foo b;
};

struct Bar2 {
	String a;
	WithDeepCopy<Foo> b;
};

struct Bar : WithClone<Bar> {
	String            a;
	WithDeepCopy<Foo> b;
	
	Bar() {}

	Bar(Bar&&) = default;
	Bar& operator=(Bar&&) = default;
	Bar(const Bar& x, int) : Bar(x) {}

private:
	Bar(const Bar&) = default;
};

namespace Upp {
	template <class T>
	T cloneit(const T& x) { return clone(x); }
};

CONSOLE_APP_MAIN
{
	{
		Bar1 a, b;
		
	//	a = b;
		
	//	LOG("==== Clone");
	//	a = clone(b);
		
		LOG("==== Pick");
		a = pick(b);
	}
	
	{
		Bar2 a, b;
	
		LOG("==== Copy");
		a = b;
		
		LOG("==== Clone");
		a = clone(b);
		
		LOG("==== Pick");
		a = pick(b);
	}
	
	{
		Bar a, b;
		
	//	a = b;
		
		LOG("==== Clone");
		a = clone(b);
		
		LOG("==== Pick");
		a = pick(b);
	}
	
	
	{
		Vector<int> a, b;
	
		a = clone(b);
		
		a = Upp::cloneit(b);
	}
}
