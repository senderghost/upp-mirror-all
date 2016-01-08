#include <Core/Core.h>
#include <vector>

using namespace Upp;

template <class I, class Less>
void CoSort(CoWork& cw, I l, I h, const Less& less)
{
	enum { PARALLEL_THRESHOLD = 80 };

	for(;;) {
		int count = int(h - l);
		if(count < 2)
			return;
		if(count < 8) {                         // Final optimized SelectSort
			ForwardSort(l, h, less);
			return;
		}
		int pass = 4;
		for(;;) {
			I middle = l + (count >> 1);        // get the middle element
			OrderIter2__(l, middle, less);      // sort l, middle, h-1 to find median of 3
			OrderIter2__(middle, h - 1, less);
			OrderIter2__(l, middle, less);      // median is now in middle
			IterSwap(l + 1, middle);            // move median pivot to l + 1
			I ii = l + 1;
			for(I i = l + 2; i != h - 1; ++i)   // do partitioning; already l <= pivot <= h - 1
				if(less(*i, *(l + 1)))
					IterSwap(++ii, i);
			IterSwap(ii, l + 1);                // put pivot back in between partitions
			I iih = ii;
			while(iih + 1 != h && !less(*ii, *(iih + 1))) // Find middle range of elements equal to pivot
				++iih;
			if(pass > 5 || min(ii - l, h - iih) > (max(ii - l, h - iih) >> pass)) { // partition sizes ok or we have done max attempts
				if(ii - l < h - iih - 1) {       // schedule or recurse on smaller partition, tail on larger
					if(ii - l < PARALLEL_THRESHOLD) // too small to run in parallel?
						Sort(l, ii, less); // resolve in this thread
					else
						cw & [=, &cw] { CoSort(cw, l, ii, less); }; // schedule for parallel execution
					l = iih + 1;
				}
				else {
					if(h - iih - 1 < PARALLEL_THRESHOLD) // too small to run in parallel?
						Sort(iih + 1, h, less); // resolve in this thread
					else
						cw & [=, &cw] { CoSort(cw, iih + 1, h, less); }; // schedule for parallel execution
					h = ii;
				}
				break;
			}
			IterSwap(l, l + (int)Random(count));     // try some other random elements for median pivot
			IterSwap(middle, l + (int)Random(count));
			IterSwap(h - 1, l + (int)Random(count));
			pass++;
		}
	}
}

template <class I, class Less>
void CoSort(I l, I h, const Less& less)
{
	CoWork cw;
	CoSort(cw, l, h, less);
}

template <class T, class Less>
void CoSort(T& c, const Less& less)
{
	CoSort(c.Begin(), c.End(), less);
}

template <class T>
void CoSort(T& c)
{
	typedef typename T::ValueType VT;
	CoSort(c.Begin(), c.End(), StdLess<VT>());
}

#ifdef _DEBUG
#define N 100000
#else
#define N 10000000
#endif

CONSOLE_APP_MAIN
{
	Vector<String> a, b;
	std::vector<std::string> c;
	std::vector<std::string> d;
	for(int i = 0; i < N; i++) {
		String s = AsString(Random());
		a.Add(s);
		b.Add(s);
		c.push_back(s.ToStd());
		d.push_back(s.ToStd());
	}

	{
		RTIMING("Sort");
		Sort(a);
	}
	{
		RTIMING("CoSort");
		CoSort(b);
	}
	{
		RTIMING("std::sort");
		std::sort(c.begin(), c.end());
	}
#if 0
	{
		RTIMING("parallel_sort");
		concurrency::parallel_sort(d.begin(), d.end());
	}
#endif
	ASSERT(a == b);
}
