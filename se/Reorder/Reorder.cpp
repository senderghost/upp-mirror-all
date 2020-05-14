#include <Core/Core.h>

using namespace Upp;

void Merge(Vector<int>& a, int l, int m, int h)
{
	BiVector<int> x;
	int r = m;
	while(r < h) {
		if(x.GetCount()) {
			int q = x.Head();
			if(a[q] < a[r]) {
				
			}
				l++;
			else {
				Swap(a[q], a
			}
				
		}
		else
		if(l < m) {
			if(a[l] < a[r])
				l++;
			else {
				Swap(a[l], a[r]);
				x.AddTail(r);
				r++;
			}
		}
	}
}

CONSOLE_APP_MAIN
{
	
}
