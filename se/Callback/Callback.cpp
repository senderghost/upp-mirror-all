#include <Core/Core.h>

#include <vector>

using namespace Upp;

CONSOLE_APP_MAIN
{
	Event<> a;
	Event<> b;
	a << b;
	a << pick(b);
	a << [] {};
	
	a = Null;
}


