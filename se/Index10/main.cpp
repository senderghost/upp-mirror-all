#include "Index.h"

#include <set>


int nnn = 200;
int val = 0;
int sum = 0;

#define N 500

void Benchmark()
{
	Vector<String> data;
	for(int i = 0; i < N; i++)
		data.Add(AsString(i)/* + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa"*/);
	int rep = max(100000000 / N, 1);
	for(int n = 0; n < rep; n++) {
		{
			New::Index<int> test;
			{
				RTIMING("New int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("New int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
			{
				RTIMING("New int findadd");
				test.Clear();
				for(int i = 0; i < N; i++) {
					if(test.FindAdd(i >> 2) == i)
						sum++;
				}
			}
		}
		{
			Index<int> test;
			{
				RTIMING("Old int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("Old int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
			{
				RTIMING("Old int findadd");
				test.Clear();
				for(int i = 0; i < N; i++) {
					if(test.FindAdd(i >> 2) == i)
						sum++;
				}
			}
		}
		{
			New::Index<String> test;
			{
				RTIMING("New string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("New string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
			test.Clear();
			{
				RTIMING("New string findadd");
				for(int i = 0; i < N; i++) {
					if(test.FindAdd(data[i >> 2]) == i)
						sum++;
				}
			}
		}
		{
			Index<String> test;
			{
				RTIMING("Old string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("Old string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
			test.Clear();
			{
				RTIMING("Old string findadd");
				for(int i = 0; i < N; i++) {
					if(test.FindAdd(data[i >> 2]) == i)
						sum++;
				}
			}
		}
	}
	RDUMP(sum);
}

void Check(const New::Index<int>& x)
{
	bool un = false;
	for(int i = 0; i < x.GetCount(); i++) {
		if(!x.IsUnlinked(i)) {
			int q = x.Find(x[i]);
			ASSERT(x[i] == x[q]);
			while(q >= 0) {
				ASSERT(x[i] == x[q]);
				int qq = x.FindNext(q);
				if(qq < 0)
					break;
				if(qq <= q) {
					DUMP(qq);
					DUMP(q);
					DUMP(x);
				}
				ASSERT(qq > q);
				q = qq;
			}

			q = x.FindLast(x[i]);
			ASSERT(x[i] == x[q]);
			while(q >= 0) {
				ASSERT(x[i] == x[q]);
				int qq = x.FindPrev(q);
				if(qq < 0)
					break;
				if(qq >= q) {
					DUMP(qq);
					DUMP(q);
					DUMP(x);
				}
				ASSERT(qq < q);
				q = qq;
			}
		}
		else
			un = true;
	}
	
	ASSERT(un == x.HasUnlinked());
}

void RealBenchmark();

CONSOLE_APP_MAIN
{
	RealBenchmark();
	return;
	
	New::Index<int> x;
	
	RDUMP(sizeof(New::Index<int>));
	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(std::set<int>));
	
	SeedRandom(0);
	
	int rnd = Random(1000);

	x.Add(rnd);
	x.Add(rnd);
	x.Add(rnd);
	LOG(AsString(x));
	
	RDUMP(FoldHash(rnd) & 3);
	RDUMP(FoldHash(0) & 3);
	
	RDUMP(x.Find(0));
	RDUMP(x.Find(rnd));
	RDUMP(x.FindNext(1));
	
	RDUMP(x.FindAdd(7));
	RDUMP(x.FindAdd(rnd));

#ifndef _DEBUG
	Benchmark();
#endif

	return;


	x.Add(1);
	x.Add(1);
	x.Add(1);
	DUMP(x);

	x.Unlink(0);
	DUMP(x);
	x.Unlink(1);
	DUMP(x);
	x.Unlink(2);
	DUMP(x);
	
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	
	x.UnlinkKey(1);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	
	x.Set(1, 5);
	DUMP(x);
	x.Set(2, 5);
	DUMP(x);
	
/*
	LOG(AsString(x));
	x.Set(1, 2);
	LOG(AsString(x));
	LOG(x.Dump());
	x.UnlinkKey(1);
//	x.Unlink(0);
//	x.Unlink(2);
	LOG(AsString(x));
	LOG(x.Dump());
	x.Trim(1);
	LOG(AsString(x));
*/
#ifdef _DEBUG
	int Q = 20;
	int COUNT = 100000;
#else
	int Q = 50;
	int COUNT = 100000000;
#endif

	#define CLOG(x)

	for(int i = 0; i < COUNT; i++)
	{
		int v = Random(Q);
		{
			RTIMING("UnlinkKey");
			x.UnlinkKey(v);
		}
		Check(x);
		CLOG("Removed " << v << ": " << AsString(x));
		v = Random(Q);
		{
//			RTIMING("Push");
//			x.Push(v);
			RTIMING("Put");
			x.Put(v);
		}
		CLOG("Pushed  " << v << ": " << AsString(x));
		Check(x);
	}

	for(int i = 0; i < COUNT; i++)
	{
		int v = Random(Q);
		int ii;
		{
			RTIMING("FindAdd");
			ii = x.FindAdd(v);
		}
		ASSERT(x[ii] == v);
		CLOG("FindAdd " << v << ": " << ii << ": " << AsString(x));
		if(Random(Q) == 0) {
			x.Clear();
			LOG("Clear " << AsString(x));
		}
		Check(x);
	}
	for(int i = 0; i < COUNT; i++) {
		int ii = Random(x.GetCount());
		int v = Random(Q);
		x.Set(ii, v);
		ASSERT(x[ii] == v);
		CLOG("Set " << ii << ", " << v << ": " << AsString(x));
		Check(x);
	}
	return;
	for(int i = 0; i < COUNT; i++) {
		int v = Random(Q);
		{
			RTIMING("Add");
			x.Add(v);
		}
		CLOG("Add " << v << ": " << AsString(x));
		Check(x);
		if(x.GetCount() > 100) {
		#if 0
			x.Clear();
		#else
			int n = Random(x.GetCount());
			x.Trim(n);
			LOG("Trim " << n << ": " << AsString(x));
		#endif
			Check(x);
		}
	}

	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(New::Index<int>));
	return;

	New::Index<int> test;
	for(int i = 0; i < 10000; i++) {
		test.Add(i);
		if(test.Find(i) == i)
			sum++;
		ASSERT(test.Find(i) == i);
	}

	DUMP(sum);

#if 0
	New::HashBase h;
	for(int i = 0; i < nnn; i++) {
		val = Random(20);
		RLOG("--- " << val);
		h.Add(val);
		h.Find(val, [&](int i) { LOG(i << " " << h[i]); sum += i; return false; });
	}
#endif
}
