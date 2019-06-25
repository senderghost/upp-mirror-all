#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	SeedRandom(0);
	
	
	MemoryOptions h;
	h.master_reserve = 0;
	MemorySetOptions(h);

	for(int pass = 0; pass < 4; pass++) {
	
		Vector<byte *> p;
		Array<String> h;
		for(int i = 0; i < 500; i++) {
			p.Add(new byte[1000000]);
			h.Add();
	//		h.Add().Cat(0, 2000);
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
}
