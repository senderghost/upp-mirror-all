#include <Core/Core.h>

using namespace Upp;

void Do() {
	Vector<int> h;
	for(int i = 0; i < 10000000; i++)
		h.Add(Random());
	CoSort(h);
	DLOG("Exit thread");
}

CONSOLE_APP_MAIN
{
	Thread a, b;
	a.Run(callback(Do));
	b.Run(callback(Do));
	Do();

	a.Wait();
	b.Wait();

	DLOG("Exit main");
}
