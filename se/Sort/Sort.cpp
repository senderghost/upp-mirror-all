#include <Core/Core.h>
#include <vector>

using namespace Upp;

int64 part_count;
int64 retry_count;
int64 mid_count;
int64 misbalance;

#ifdef _DEBUG
#define TEST(x) x
#else
#define TEST(x)
#endif

template <class I, class Less>
force_inline
I Median__(I l, int count, const Less& less)
{
	I middle = l + (int)Random(count);
	I h = l + (int)Random(count);
	if(less(*middle, *l))
		Swap(middle, l);
	if(less(*h, *middle))
		Swap(middle, h);
	if(less(*middle, *l))
		Swap(middle, l);
	return middle;
}

template <class I, class Less>
void NewSort(I l, I h, const Less& less)
{
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
			TEST(part_count += count);
			I middle = l + (count >> 1);        // get the middle element
			if(count > 500) {
//				RTIMING("Extended middle");
				IterSwap(l, Median__(l, count, less));
				IterSwap(middle, Median__(l, count, less));
				IterSwap(h - 1, Median__(l, count, less));
			}
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
				TEST(misbalance += abs((ii - l) - (h - iih - 1)));
				if(ii - l < h - iih - 1) {       // recurse on smaller partition, tail on larger
					NewSort(l, ii, less);
					l = iih + 1;
				}
				else {
					NewSort(iih + 1, h, less);
					h = ii;
				}
				break;
			}
			TEST(retry_count += count);
			IterSwap(l, l + (int)Random(count));     // try some other random elements for median pivot
			IterSwap(middle, l + (int)Random(count));
			IterSwap(h - 1, l + (int)Random(count));
			pass++;
		}
	}
}

template <class T, class Less>
void NewSort(T& c, const Less& less)
{
	NewSort(c.Begin(), c.End(), less);
}

template <class T>
void NewSort(T& c)
{
	typedef typename T::ValueType VT;
	NewSort(c.Begin(), c.End(), StdLess<VT>());
}

#ifdef _DEBUG
#define N 100000
#else
//#define N 10000000
#define N 5000000
//#define N 1000
#endif


int Partition3(I l, I h)
{
	I ii = l;
	I jj = h - 1;
	I i = l + 1;
	for(;;) {
		if(i >= jj)
			break;
		if(*i < *l)
			IterSwap(++ii, i);
		else
		if(*i > *(h - 1))
			IterSwap(--jj, i);
	}
}

CONSOLE_APP_MAIN
{
	Vector<String> a;
	SeedRandom();
	
	Vector<int> x

	std::vector<std::string> c;
	for(int i = 0; i < N; i++) {
		String s = AsString(Random());
		a.Add(s);
		c.push_back(s.ToStd());
	}

#ifdef _DEBUG
	Vector<String> b = clone(a);
	Sort(a);
	NewSort(b);
	DDUMP(b.GetCount());
	DDUMP(part_count);
	DDUMP(retry_count);
	DDUMP(mid_count);
	DDUMP(misbalance);
	ASSERT(a == b);
#else
	RDUMP(N);
	for(int i = 0; i < 10000000 / N; i++) {
		{
			Vector<String> b = clone(a);
			RTIMING("Sort");
			Sort(b);
		}
		{
			Vector<String> b = clone(a);
			RTIMING("NewSort");
			NewSort(b);
		}
		if(0) {
			std::vector<std::string> d = c;
			RTIMING("std::sort");
			std::sort(d.begin(), d.end());
		}
	}
#endif
}
