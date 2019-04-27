#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	for(int i = 0; i < 10; i++) {
		Vector<Value> v;
		Vector<int> iv;
		for(int i = 0; i < 100000; i++) {
			int n = Random(10000);
			v.Add(n);
			iv.Add(n);
		}

		{
			auto h = clone(v);
			RTIMING("StableSort");
			StableSort(h);
		}

		{
			auto h = clone(iv);
			RTIMING("StableSort int");
			StableSort(h);
		}

		{
			RTIMING("Sort");
			Sort(v);
		}

		{
			RTIMING("Sort int");
			Sort(iv);
		}
	}
}
