#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	Array<int> h{1, 2, 3, 4, 5, 6, 7, 8};
	h.RemoveIf([](int i) { return i & 1; });
	DDUMP(h);
	for(int i = 0; i < 10; i++)
		h << Random(100);
	DDUMP(h);
	h.RemoveIf([&](int i) { return h[i] % 3 == 0; });
	DDUMP(h);
}
