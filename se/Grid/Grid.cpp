#include <Core/Core.h>

using namespace Upp;

#include "DataArray.h"
#include "Grid.h"

cu * (cz * (x * cy + y) + z) + u

(cu * cz * (x * cy + y) + cu * z) + u

cu * cz * cy * x + cu * cz * y + cu * z + u



CONSOLE_APP_MAIN
{
	Grid<int> test;
	test.Create(3, 4, 5);
	
	int i = 0;

	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 4; y++)
			for(int z = 0; z < 5; z++) {
				DDUMP(x);
				DDUMP(y);
				DDUMP(z);
				test[x][y][z] = i++;
				DDUMP((int)test[x][y][z]);
			}
			
	i = 0;
	LOG("====================");

	for(int x = 0; x < 3; x++)
		for(int y = 0; y < 4; y++)
			for(int z = 0; z < 5; z++) {
				DDUMP((int)test[x][y][z]);
//				ASSERT(test[x][y][z] == i++);
			}
	return;

#if 0	
	DataArray<double> h;
	h.Create(20000000);
	{
		RTIMING("Set");
		for(int i = 0; i < h.GetCount(); i++)
			h.Set(i, 2.33 * i);
	}
	{
		RTIMING("SetFast");
		double *v = h.BeginWrite();
		for(int i = 0; i < h.GetCount(); i++)
			v[i] = 2.33 * i;
		h.EndWrite();
	}
	
#ifdef _DEBUG
	DataArray<int> a;
	a.Create(3);
	
	a.Set(0, 1);
	a.Set(1, 2);
	a.Set(2, 3);

	DDUMP(a);
	
	DataArray<int> b = a;

	DDUMP(b);
	DDUMP(a);
	
	b.Set(2, 12);

	DDUMP(b);
	DDUMP(a);
	
	a = b;
	
	DDUMP(a);
	
	Value v = a;
	DDUMP(v);
	DataArray<int> x = v;
	DDUMP(x);
	DDUMP(v);
	
	String ss = StoreAsString(x);
	DUMPHEX(ss);
	LoadFromString(x, ss);
	DDUMP(x);
	
	StringStreamVals vs;
	x.Serialize(vs);
	ss = vs.GetResult();
	DUMPHEX(ss);
	DDUMP(vs.va.GetCount());
	DDUMP(vs.va[0]);
	
#endif
#endif
}
