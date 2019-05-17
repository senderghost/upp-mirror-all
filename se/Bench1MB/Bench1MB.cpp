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
	for(int i = 0; i < 1000000; i++) {
		RTIMING("Alloc/free 50000");
		byte *h = new byte[50000];
		delete[] h;
	}
	for(int i = 0; i < 1000000; i++) {
		RTIMING("Alloc/free 10000");
		byte *h = new byte[10000];
		delete[] h;
	}
	for(int i = 0; i < 1000000; i++) {
		RTIMING("Alloc/free 700");
		byte *h = new byte[700];
		delete[] h;
	}
	for(int i = 0; i < 1000000; i++) {
		RTIMING("malloc/free 1MB");
		void *h = malloc(N);
		free(h);
	}
	for(int i = 0; i < 1000000; i++) {
		RTIMING("Alloc/free 1MB");
		byte *h = new byte[N];
		delete[] h;
	}
	for(int i = 0; i < 1000; i++) {
		RTIMING("Alloc/free memset");
		byte *h = new byte[N];
		memset(h, 123, N);
		delete[] h;
	}
}
