#include "InVector.h"

#define N 10000000

void InVectorBenchmark()
{
/*
	std::multiset<int> s;
	SeedRandom();
	{
		RTIMING("std::set INSERT");
		for(int i = 0; i < N; i++)
			s.insert(Random());
	}

	SeedRandom();
	{
		RTIMING("InVector INSERT UB");
		for(int i = 0; i < N; i++) {
			int x = Random();
			a.Insert(FindUpperBound(a, x)) = x;
		}
	}
	return;
*/
	InVector<int> a;
	{
		RTIMING("InVector INSERT");
		a.Insert(0) = 0;
		for(int i = 0; i < N; i++) {
			a.Insert(Random(a.GetCount())) = Random(100);
		}
	}
	{
		RTIMING("InVector SCAN");
		int sum = 0;
		for(int i = 0; i < a.GetCount(); i++)
			sum += a[i];
		RDUMP(sum);
	}
	{
		RTIMING("InVector iterator SCAN");
		int sum = 0;
		for(InVector<int>::Iterator i = a.Begin(); i != a.End(); i++)
			sum += *i;
		RDUMP(sum);
	}
	{
		RTIMING("InVector Sort");
		Sort(a);
	}
	RDUMP(a.GetCount());

	SeedRandom();
	Vector<int> b;
	{
		RTIMING("Vector INSERT");
		b.Insert(0) = 0;
		for(int i = 0; i < N; i++) {
			b.Add(Random());
//			b.Insert(Random(b.GetCount())) = Random(100);
		}
	}
	{
		RTIMING("Vector SCAN");
		int sum = 0;
		for(int i = 0; i < b.GetCount(); i++)
			sum += b[i];
		RDUMP(sum);
	}
	{
		RTIMING("Vector iterator SCAN");
		int sum = 0;
		for(Vector<int>::Iterator i = b.Begin(); i != b.End(); i++)
			sum += *i;
		RDUMP(sum);
	}
	{
		RTIMING("Vector Sort");
		Sort(b);
	}
	return;
	SeedRandom();
	Array<int> c;
	{
		RTIMING("Array INSERT");
		c.Insert(0) = 0;
		for(int i = 0; i < N; i++) {
			c.Add(Random(100));
//			c.Insert(Random(c.GetCount())) = Random(100);
		}
	}
	{
		RTIMING("Array SCAN");
		int sum = 0;
		for(int i = 0; i < c.GetCount(); i++)
			sum += c[i];
		RDUMP(sum);
	}
	{
		RTIMING("Array Sort");
		Sort(c);
	}

	SeedRandom();
	BiVector<int> d;
	{
		RTIMING("BiVector INSERT");
		d.AddTail() = 0;
		for(int i = 0; i < N; i++) {
			d.AddTail(Random(100));
//			d.Insert(Random(d.GetCount())) = Random(100);
		}
	}
	{
		RTIMING("BiVector SCAN");
		int sum = 0;
		for(int i = 0; i < d.GetCount(); i++)
			sum += d[i];
		RDUMP(sum);
	}
	{
		RTIMING("BiVector Sort");
		Sort(d);
	}
}

template <class C1, class C2>
void Compare(C1& a, C2& b)
{
	ASSERT(a.GetCount() == b.GetCount());

	for(int i = 0; i < a.GetCount(); i++)
		ASSERT(a[i] == b[i]);
	
	C1::Iterator ia = a.Begin();
	C2::Iterator ib = b.Begin();
	while(ib != b.End()) {
		ASSERT(*ia == *ib);
		ia++;
		ib++;
	}
}

void InVectorTest()
{
	SeedRandom();
	Vector<int> q;
	InVector<int> iv;
	Compare(q, iv);
	iv.Insert(0) = 0;
	q.Insert(0) = 0;
	iv.Insert(1) = -1;
	q.Insert(1) = -1;
	for(int j = 0; j < 10000; j++) {
		if(j % 1000 == 0)
			LOG(j);
		int i = Random(iv.GetCount());
		iv.Insert(i) = i;
		q.Insert(i) = i;
		Compare(q, iv);
		ASSERT(iv.End() - iv.Begin() == iv.GetCount());
	}

	for(int i = 0; i < 100; i++) {
		int n = Random(100) + 20;
		InVector<int>::Iterator it2, it = iv.Begin();
		it += n;
		ASSERT(it - iv.Begin() == n);
		it2 = it;
		for(int j = 0; j < 10; j++) {
			ASSERT(it2 - iv.Begin() == n + j);
			++it2;
		}
		it2 = it;
		for(int j = 0; j < 10; j++) {
			ASSERT(it2 - iv.Begin() == n - j);
			--it2;
		}
	}

	StableSort(q);
	StableSort(iv);
	Compare(q, iv);
}
	
CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);
#ifdef _DEBUG
	InVectorTest();
#else
	InVectorBenchmark();
#endif
}
