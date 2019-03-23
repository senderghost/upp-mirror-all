#include "Cutlass.h"

#include "Cutlass.h"

#include <Core/Core.h>

using namespace Upp;

Vector<Vector<Pointf>> TestDataSaw()
{
	Vector<Vector<Pointf>> data;
	
	Vector<Pointf>& saw = data.Add();
	
	for(int x = 100; x < 500; x += 50) {
		saw.Add(Pointf(x, 200 + x / 3));
		saw.Add(Pointf(x + 25, 200 - x / 3));
	}
	saw.Add(Pointf(525, 420));
	
	RDUMP(saw.GetCount());
	
	return data;
}