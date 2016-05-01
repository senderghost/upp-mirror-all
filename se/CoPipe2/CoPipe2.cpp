#include <Core/Core.h>

using namespace Upp;

Vector<String> result;

void Process(CoWork& co, String h, int n)
{
	int x = atoi(h);
	x++;
	if(n < 100)
		co.Step(n + 1, [=, &co] { Process(co, AsString(atoi(h) + 1), n + 1); });
	else
		result.Add(h);
}

CONSOLE_APP_MAIN
{
	CoWork co;
	for(int i = 0; i < 1000; i++)
		co.Step(0, [=, &co] { Process(co, AsString(i), 0); });
	co.Finish();
	DDUMPC(result);

	Thread::ShutdownThreads();
}
