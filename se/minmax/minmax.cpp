#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	DDUMP(min(5, 3, 7, 8, 9, 2, 4, 7));
	DDUMP(min(5, 3));

	DDUMP(max(5, 3, 7, 8, 9, 2, 4, 7));
	DDUMP(max(5, 3));
}
