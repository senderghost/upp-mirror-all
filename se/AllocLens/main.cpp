#include <Core/Core.h>
#include <cstddef>
#include <type_traits>

using namespace Upp;

struct alignas(64) Foo {
	int bar;
};

CONSOLE_APP_MAIN
{
	for(int N = 16; N < 4064; N += 16) {
	//	DLOG("------------");
	//	DDUMP(N);
		int usedi = 0;
		int n = 4096 - N;
		while(n >= 32) {
	//		DDUMP(n);
			if((n & 0xff) == 16) {
	//			DLOG("Skip " << n << " " << FormatIntHex(n));
				n -= 16;
			}
			else {
				++usedi;
	//			DDUMP(usedi);
				n -= N;
			}
		}
	//	DDUMP(usedi);
	//	DDUMP(4064 / N);
		int oldused = 4064 / N * N;
		int oldwasted = 4096 - oldused;
	//	DDUMP(oldused);
		int used = usedi * N;
		int wasted = 4096 - used;
	//	DDUMP(used);
		DLOG(N << " used " << used << "(" << usedi << "), wasted " << wasted << ", "
		       << 100.0*wasted/4096 << "%"
		       << ", was " << 100.0*oldwasted/4096 << "%");
	}
}
