#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	String h = LoadFile("C:/u/n-2016-137/uppsrc/ScatterCtrl/ScatterCtrl.cpp");
	DDUMP(h.GetCount());
	Index<String> dict;
	for(int i = 0; i + 4 < h.GetCount(); i += 4)
		dict.Add(h.Mid(i, 4));
	
	int found = 0;
	int notfound = 0;

	for(int i = 0; i + 4 < h.GetCount();) {
		String w = h.Mid(i, 4);
		int q = dict.Find(w);
		if(q >= 0 && 4 * q < i) {
			DLOG("Found " << AsCString(w) << " at " << q);
			i += 4;
			found++;
		}
		else {
			DLOG("Not found " << AsCString(w));
			i++;
			notfound++;
		}
	}
	
	DDUMP(found);
	DDUMP(notfound);
}
