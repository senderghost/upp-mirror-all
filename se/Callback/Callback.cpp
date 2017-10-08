#include <Core/Core.h>

#include <vector>

using namespace Upp;

int test(int x) { return 123 * x; }

CONSOLE_APP_MAIN
{
	Function<int (int)> fn = test;
	fn = test;
	
	DDUMP(fn(2));
}


