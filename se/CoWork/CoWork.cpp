#include <Core/Core.h>

using namespace Upp;

void Do() {
	DDUMP(CoWork::IsWorker());
//	CoWork::StartPool(20);
	Vector<int> h;
	for(int i = 0; i < 1000000; i++)
		h.Add(Random());
	CoSort(h);
	DLOG("Exit Do");
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
	
	Thread::ShutdownThreads();
	DLOG("Exit main 2");
	Thread::ShutdownThreads();
}
