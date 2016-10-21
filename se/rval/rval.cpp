#include <Core/Core.h>

using namespace Upp;

struct Foo : DeepCopyOption<Foo> {
	Foo() {}
	Foo(Foo&&) { LOG("Foo move constructor"); }
	Foo& operator=(Foo&&) { LOG("Foo move assignment"); return *this; }
	Foo(const Foo& x, int) {
		LOG("Foo clone");
	}
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
	Bar a, b;
	
//	a = b;
	
	LOG("==== Clone");
	a = Upp::cloneit(b);
	
	LOG("==== Pick");
	a = pick(b);
	
	
	{
		Vector<int> a, b;
	
		a = clone(b);
		
		a = Upp::cloneit(b);
	}
}
