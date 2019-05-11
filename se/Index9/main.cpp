#include "Index.h"

#include <set>


void Check(const New::Index<int>& x, bool ordered = false)
{
	int un = 0;
	Vector<int> uns = x.GetUnlinked();
	for(int i = 0; i < x.GetCount(); i++) {
		if(x.IsUnlinked(i)) {
			ASSERT(FindIndex(uns, i) >= 0);
			un++;
		}
		else {
			int q = x.Find(x[i]);
			bool f = false;
			ASSERT(x[i] == x[q]);
			while(q >= 0) {
				if(q == i)
					f = true;
				ASSERT(x[i] == x[q]);
				int qq = x.FindNext(q);
				if(qq < 0)
					break;
				ASSERT(!ordered || qq > q);
				q = qq;
			}
			ASSERT(f);

			q = x.FindLast(x[i]);
			ASSERT(x[i] == x[q]);
			while(q >= 0) {
				ASSERT(x[i] == x[q]);
				int qq = x.FindPrev(q);
				if(qq < 0)
					break;
				ASSERT(!ordered || qq < q);
				q = qq;
			}
		}
	}
	
	ASSERT(un == uns.GetCount());
}

void RealBenchmark();
void RealBenchmarkCollisions();

void PickTests()
{
	New::Index<String> s;
	String h = "Hello!";
	s.Add(h);
	s.Add(h);
	ASSERT(h.GetCount());
	s.Add(pick(h));
	ASSERT(IsNull(h));
	h = "1";
	s.Add(pick(h));
	ASSERT(IsNull(h));
	h = "2";
	int hi = s.FindAdd(pick(h));
	ASSERT(IsNull(h));
	h = "2";
	ASSERT(s.FindAdd(pick(h)) == hi);
	ASSERT(h == "2");
}

#define TEST(op, result) { op; String s = AsString(x); LOG("TEST(" << #op << ", " << AsCString(s) << ")"); if(strlen(result)) ASSERT(s == result); Check(x);; }

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	RDUMP(sizeof(New::Index<int>));
	RDUMP(sizeof(New::VectorMap<String, int>));
	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(VectorMap<String, int>));
	RDUMP(sizeof(std::set<int>));

#ifndef _DEBUG
	RealBenchmark();
	Benchmark();
	return;
#endif

//	RealBenchmarkCollisions();

	PickTests();

	New::Index<int> x;

	SeedRandom(0);
	
	int rnd = Random(100);

	TEST(x.Add(0), "");
	TEST(x.Add(0), "");
	TEST(x.Add(0), "");

	TEST(x.Add(1), "");
	TEST(x.Add(1), "");
	TEST(x.Add(1), "");

	ASSERT(x.Find(10) < 0);
	ASSERT(x.Find(1) == 3);

	ASSERT(x.FindNext(3) == 4);
	ASSERT(x.FindNext(4) == 5);
	ASSERT(x.FindNext(5) == -1);

	ASSERT(x.FindLast(1) == 5);
	ASSERT(x.FindPrev(5) == 4);
	DDUMP(x.FindPrev(4));
	ASSERT(x.FindPrev(4) == 3);
	ASSERT(x.FindPrev(3) == -1);

	TEST(x.Unlink(0), "");
	DUMP(x);
	DUMP(x.GetUnlinked());
	x.Unlink(1);
	DUMP(x);
	DUMP(x.GetUnlinked());
	x.Unlink(2);
	DUMP(x);
	DUMP(x.GetUnlinked());
	
	DUMP(x.Put(2));
	DUMP(x);
	DUMP(x.GetUnlinked());
	DUMP(x.Put(2));
	DUMP(x);
	DUMP(x.GetUnlinked());
	DUMP(x.Put(2));
	DUMP(x);
	DUMP(x.GetUnlinked());
	
	x.UnlinkKey(1);
	DUMP(x);
	DUMP(x.GetUnlinked());

	DLOG("----- Put(2)");
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	x.Put(2);
	DUMP(x);
	
	DLOG("----- Set");
	TEST(x.Set(1, 5), "");
	TEST(x.Set(2, 5), "");
	
	DLOG("----- Unlink");
	TEST(x.Unlink(5), "");
	TEST(x.Trim(4), "");
	
	DLOG("----- Sweep");
	TEST(x.Unlink(1), "");
	TEST(x.Sweep(), "");

	DLOG("----- Reserve");
	TEST(x.Reserve(1000), "");
	TEST(x.Shrink(), "");
	
	return;
	
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

}
