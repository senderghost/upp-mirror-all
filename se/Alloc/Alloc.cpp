#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	SeedRandom(0);
	Vector<byte *> p;
	Array<String> h;
	for(int i = 0; i < 10000; i++) {
		p.Add(new byte[100000]);
		h.Add();
		h.Add().Cat(0, 2000);
		if(i < 200) {
			MemoryDumpHuge();
			RLOG("=============================");
		}
	}
		
	
	RDUMP(MemoryProfile());
	MemoryDumpHuge();

	for(byte *q : p)
		delete[] q;

	RDUMP(MemoryProfile());
	MemoryDumpHuge();
}
