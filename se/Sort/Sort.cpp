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

template <class I>
String Range(I l, int n)
{
	String r;
	for(int i = 0; i < n; i++)
		MergeWith(r, ", ", l[i]);
	return r;
}

#define LTIMING(x) RTIMING(x)

template <class I, class Less>
void NewSort(I l, I h, const Less& less, int nth_element = -1)
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
			if(count > 1000) {
//				RTIMING("Extended middle");
				LOG("-------------");
			//	int n = 5;
			//	while(2 * (1 << n) < count)
			//		n++;
				int n = count >> 7;
				DUMP(count);
				DUMP(n);
				{
					LTIMING("Random");
					for(int i = 0; i < n; i++)
						IterSwap(l + i, l + (int)Random(count));
				}
				LTIMING("Median");
				NewSort(l, l + n, less, n / 2);
				DUMP(l[0]);
				DUMP(l[n / 2]);
				DUMP(l[n - 1]);
				IterSwap(h - 1, l + n - 1);
				IterSwap(l + 1, l + n / 2);
			}
			else {
				LTIMING("Median2");
//				I middle = l + (count >> 1);        // get the middle element
				I middle = l + 1;
//				IterSwap(middle, l + (int)Random(count));
				OrderIter2__(l, middle, less);      // sort l, middle, h-1 to find median of 3
				OrderIter2__(middle, h - 1, less);
				OrderIter2__(l, middle, less);      // median is now in middle
//				IterSwap(l + 1, middle);            // move median pivot to l + 1
			}
			I ii = l + 1;
			for(I i = l + 2; i != h - 1; ++i)   // do partitioning; already l <= pivot <= h - 1
				if(less(*i, *(l + 1)))
					IterSwap(++ii, i);
			IterSwap(ii, l + 1);                // put pivot back in between partitions
			I iih = ii;
			while(iih + 1 != h && !less(*ii, *(iih + 1))) // Find middle range of elements equal to pivot
				++iih;
			if(true || pass > 5 || min(ii - l, h - iih) > (max(ii - l, h - iih) >> pass)) { // partition sizes ok or we have done max attempts
				TEST(misbalance += abs((ii - l) - (h - iih - 1)));
				LOG("=== " << count << " " << ii - l << ":" << h - iih - 1);
				if(nth_element >= 0) {
					int lh = ii - l; // end of left partition
					int hl = iih + 1 - l; // begin of right partition
					if(nth_element < lh) // nth_element is in the left partition
						h = ii;
					else
					if(nth_element >= hl) {
						l = iih + 1;
						nth_element -= hl;
					}
					else
						return;
				}
				else {
					if(ii - l < h - iih - 1) {       // recurse on smaller partition, tail on larger
						if(ii - l > 2)
							if(ii - l < 8)
								ForwardSort(l, ii, less);
							else
								NewSort(l, ii, less);
						l = iih + 1;
					}
					else {
						int n = h - iih - 1;
						if(n >= 2)
							if(n < 8)
								ForwardSort(iih + 1, h, less);
							else
								NewSort(iih + 1, h, less);
						h = ii;
					}
				}
				break;
			}
			LOG("Retry " << ii - l << " : " << h - iih);
			TEST(retry_count += count);
/*			IterSwap(l, l + (int)Random(count));     // try some other random elements for median pivot
			IterSwap(middle, l + (int)Random(count));
			IterSwap(h - 1, l + (int)Random(count));*/
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

template <class T>
void NthElement(T& c, int nth_element)
{
	typedef typename T::ValueType VT;
	NewSort(c.Begin(), c.End(), StdLess<VT>(), nth_element);
}

void TestNthElement()
{
	Vector<int> data;
	for(int i = 0; i < 10000; i++)
		data.Add(Random());
	Vector<int> sorted = clone(data);
	Sort(sorted);
	for(int i = 0; i < 1000; i++) {
		DUMP(i);
		int nth_element = Random(10000);
		Vector<int> nth = clone(data);
		NthElement(nth, nth_element);
		ASSERT(sorted[nth_element] == nth[nth_element]);
	}
}

#ifdef _DEBUG
#define N 100000
#else
//#define N 10000000
#define N 5000000
//#define N 1000
#endif


CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	Vector<String> a;
	SeedRandom();
	
	std::vector<std::string> c;
	for(int i = 0; i < N; i++) {
		String s = AsString(Random(1000000));
		a.Add(s);
		c.push_back(s.ToStd());
	}

#ifdef _DEBUG
//	TestNthElement();

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
