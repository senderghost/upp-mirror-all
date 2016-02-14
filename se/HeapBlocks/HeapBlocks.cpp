#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	for(int sz = 32; sz < 2048; sz += 32) {
		int blocks = (4096 - 32) / sz;
		int overhead = 4096 - blocks * sz;
		DLOG(sz << ", blocks " << blocks << ", overhead " << overhead << " "
		        << overhead / 4096.0 * 100 << "%, " << (double)overhead / blocks << " bytes/block");
	}
}
