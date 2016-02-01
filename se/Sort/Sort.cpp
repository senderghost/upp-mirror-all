#include <Core/Core.h>
#include <vector>

using namespace Upp;

int64 part_count;
int64 retry_count;
int64 mid_count;
int64 misbalance;

#define LLOG(x)

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

#define LTIMING(x) // RTIMING(x)

template <class I>
void RandomizePartition__(I l, I h)
{
	int count = h - l;
	if(h - l > 8) {
		I middle = l + (count >> 1);
		IterSwap(l, l + (int)Random(count));
		IterSwap(middle, l + (int)Random(count));
		IterSwap(h - 1, l + (int)Random(count));
	}
}

template <class I, class Less>
void NewSort3(I l, I h, const Less& less)
{
	for(;;) {
		int count = int(h - l);
		if(count < 2)
			return;
		if(count < 8) {                         // Final optimized SelectSort
			ForwardSort(l, h, less);
			return;
		}
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
		if(min(ii - l, h - iih) > (max(ii - l, h - iih) / 3)) { // Randomize partitions
			RandomizePartition__(l, ii);
			RandomizePartition__(iih + 1, h);
		}
		if(ii - l < h - iih - 1) {       // recurse on smaller partition, tail on larger
			if(ii - l > 2)
				if(ii - l < 8)
					ForwardSort(l, ii, less);
				else
					NewSort(l, ii, less);
			l = iih + 1;
		}
		else {
			int n = int(h - iih - 1);
			if(n >= 2)
				if(n < 8)
					ForwardSort(iih + 1, h, less);
				else
					NewSort(iih + 1, h, less);
			h = ii;
		}
	}
}

#include "Sampling.h"

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

/*
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
*/

#ifdef _DEBUG
#define N 10000
#else
//#define N 10000000
#define N 5000000
//#define N 1000
#endif

#include "SmallSort.h"

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);
	SeedRandom();

	Vector<String> a;

	std::vector<std::string> c;
	for(int i = 0; i < N; i++) {
		String s = AsString(Random(1000000));
		a.Add(s);
		c.push_back(s.ToStd());
	}
	
//	NewSort(a);

#ifdef _DEBUG
//	return;
//	TestNthElement();

	for(int i = 0; i < 1000; i++) {
		int n = Random(1000000);
		int lim = INT_MAX;
		if(i & 1)
			lim = Random(100) + 1;
		
		Cout() << n << "\r\n";

		Vector<int> a;
		for(int i = 0; i < n; i++)
			a.Add(Random(lim));
		auto b = clone(a);
		Sort(a);
		NewSort(b);
		ASSERT(a == b);
	}
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

#if 0
	for(int i = 0; i < 8; i++) {
		String s = AsString(Random(1000000));
		a.Add(s);
	}
	
#ifdef _DEBUG
	Vector<int> ar;

	for(int i = 0; i < 8; i++) {
		ar.Add(Random(100));
	}

	DUMP(ar);
	
	SmallSort(ar.begin(), ar.end(), StdLess<int>());
	
	DUMP(ar);
	return;
#else

	for(int i = 0; i < 10000000; i++) {
		{
			auto h = clone(a);
			RTIMING("ForwardSort");
			ForwardSort(h.begin(), h.end(), StdLess<String>());
		}
		{
			auto h = clone(a);
			RTIMING("SmallSort");
			SmallSort(h.begin(), h.end(), StdLess<String>());
		}
	}
#endif
	return;
#endif