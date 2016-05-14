#include <Core/Core.h>

#include <atomic>
#include <thread>
#include <mutex>

using namespace Upp;

CONSOLE_APP_MAIN
{
	Vector<int> h = { 6, 1, 3, 56, 8, 223, 12, 2, 6, 3 };
	Sort(SubRange(h, 1, 5));
	DUMP(h);
	Reverse(SubRange(h, 0, 4));
	DUMP(h);
}
