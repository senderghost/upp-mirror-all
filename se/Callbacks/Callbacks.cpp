#include <Core/Core.h>

using namespace Upp;

void Foo(const String& h)
{
	DDUMP(h);
}

CONSOLE_APP_MAIN
{
	auto x = callback(Foo);
	x("AAA");
	
	auto y = callback1(x, "B");
	y();
	
	Callback h = [=] { LOG("FUN"); };
	h();
	h = [] { LOG("FUN2"); };
	h();
}
