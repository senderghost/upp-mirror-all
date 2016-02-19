#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	const int MAXBLOCK = 65536 - 64;
	int p = 256;
	int bi = 0;
	while(p < MAXBLOCK) {
		DLOG(bi++ << " " << p - 16 << " " << p / 64.0);
		int add = minmax(16 * p / 100 / 256 * 256, 256, INT_MAX);
		p += add;
	}

	return;
	for(int sz = 32; sz < 2048; sz += 32) {
		int blocks = (4096 - 32) / sz;
		int overhead = 4096 - blocks * sz;
		DLOG(sz << ", blocks " << blocks << ", overhead " << overhead << " "
		        << overhead / 4096.0 * 100 << "%, " << (double)overhead / blocks << " bytes/block");
	}
}
