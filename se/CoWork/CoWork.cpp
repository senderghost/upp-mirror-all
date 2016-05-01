#include <Core/Core.h>

using namespace Upp;

void Do(Vector<int>& h) {
	DUMP(CoWork::IsWorker());
	for(int i = 0; i < 1000000; i++)
		h.Add(Random());
	CoSort(h);
	LOG("Do finished");
}

bool IsSorted(const Vector<int>& h)
{
	for(int i = 1; i < h.GetCount(); i++)
		if(h[i - 1] > h[i])
			return false;
	return true;
}

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	Vector<int> h1, h2, h3;

	Thread a;
	{
		a.Run([&] { Do(h1); });
	
		CoWork co;
		co & [&] { Do(h2); };
	
		Do(h3);
	}
	a.Wait();

	
	ASSERT(IsSorted(h1));
	ASSERT(IsSorted(h2));
	ASSERT(IsSorted(h3));

	LOG("Exit main");
	
	Thread::ShutdownThreads();

	LOG("Exit main 2 (checking that ShutdownThreads can be called twice)");
	Thread::ShutdownThreads();
	
	LOG("============== OK");
}
