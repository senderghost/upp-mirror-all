#include <Core/Core.h>

using namespace Upp;

int N = 1 * 1024*1024;

CONSOLE_APP_MAIN
{
	byte *h = new byte[N];
	for(int i = 0; i < 1000; i++) {
		RTIMING("memset");
		memset(h, 123, N);
	}
	delete[] h;
	for(int i = 0; i < 1000; i++) {
		RTIMING("Alloc/free");
		byte *h = new byte[N];
		memset(h, 123, N);
		delete[] h;
	}
}
