#include <Core/Core.h>

using namespace Upp;

template <class T>
void Check(const Index<T>& x, bool ordered = false)
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

void CheckIn(const Index<int>& x, int v, int ii)
{
	for(int q = x.Find(v); q >= 0; q = x.FindNext(q))
		if(q == ii)
			return;
	NEVER();
}

void RealBenchmark();
void RealBenchmarkCollisions();

#ifdef _DEBUG
#define TEST(op, result) { op; String s = x.Dump(); LOG("TEST(" << #op << ", " << AsCString(s) << ");"); if(*result) ASSERT(s == result); Check(x); }
#define UTST(result)     { String s = AsString(x.GetUnlinked()); LOG("UTST(" << AsCString(s) << ");"); if(*result) ASSERT(s == result); }
#else
#define TEST(op, result)
#define UTST(result)
#endif

void PickTests()
{
	Index<String> x;
	LOG("------------- PICK TESTS");
	String h = "Hello!";
	x.Add(h);
	x.Add(h);
	ASSERT(h.GetCount());
	x.Add(pick(h));
	ASSERT(IsNull(h));
	h = "1";
	x.Add(pick(h));
	ASSERT(IsNull(h));
	h = "2";
	int hi = x.FindAdd(pick(h));
	ASSERT(IsNull(h));
	h = "2";
	ASSERT(x.FindAdd(pick(h)) == hi);
	ASSERT(h == "2");
	
	h = "3";
	x.Unlink(0);
	TEST(x.Put(pick(h)), "0: 3/4 -> 0:0; 1: Hello!/3 -> 2:2; 2: Hello!/3 -> 1:1; 3: 1/7 -> 3:3; 4: 2/1 -> 4:4");
	ASSERT(IsNull(h));
	h = "31";
	TEST(x.Put(pick(h)), "0: 3/4 -> 0:0; 1: Hello!/3 -> 2:2; 2: Hello!/3 -> 1:1; 3: 1/7 -> 5:5; 4: 2/1 -> 4:4; 5: 31/7 -> 3:3");
	ASSERT(IsNull(h));
	
	h = "X";
	TEST(x.FindPut(pick(h)), "0: 3/4 -> 0:0; 1: Hello!/3 -> 2:2; 2: Hello!/3 -> 1:1; 3: 1/7 -> 5:5; 4: 2/1 -> 6:6; 5: 31/7 -> 3:3; 6: X/1 -> 4:4");
	ASSERT(IsNull(h));
	h = "X";
	TEST(x.FindPut(pick(h)), "0: 3/4 -> 0:0; 1: Hello!/3 -> 2:2; 2: Hello!/3 -> 1:1; 3: 1/7 -> 5:5; 4: 2/1 -> 6:6; 5: 31/7 -> 3:3; 6: X/1 -> 4:4");
	ASSERT(!IsNull(h));
	h = "Y";
	TEST(x.FindPut(h), "0: 3/4 -> 0:0; 1: Hello!/3 -> 2:2; 2: Hello!/3 -> 1:1; 3: 1/15 -> 5:5; 4: 2/9 -> 4:4; 5: 31/15 -> 3:3; 6: X/1 -> 6:6; 7: Y/12 -> 7:7");
	ASSERT(!IsNull(h));
	
	h = "SET";
	TEST(x.Set(0, pick(h)), "");
	ASSERT(IsNull(h));
}

void BasicTests()
{
	Index<int> x;
	LOG("=========== ADD");
	TEST(x.Add(0), "0: 0/0 -> 0:0");
	TEST(x.Add(0), "0: 0/0 -> 1:1; 1: 0/0 -> 0:0");
	TEST(x.Add(0), "0: 0/0 -> 2:1; 1: 0/0 -> 0:2; 2: 0/0 -> 1:0");

	TEST(x.Add(1), "0: 0/0 -> 2:1; 1: 0/0 -> 0:2; 2: 0/0 -> 1:0; 3: 1/3 -> 3:3");
	TEST(x.Add(1), "0: 0/0 -> 2:1; 1: 0/0 -> 0:2; 2: 0/0 -> 1:0; 3: 1/3 -> 4:4; 4: 1/3 -> 3:3");
	TEST(x.Add(1), "0: 0/0 -> 2:1; 1: 0/0 -> 0:2; 2: 0/0 -> 1:0; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");

	ASSERT(x.Find(10) < 0);
	ASSERT(x.Find(1) == 3);

	ASSERT(x.FindNext(3) == 4);
	ASSERT(x.FindNext(4) == 5);
	ASSERT(x.FindNext(5) == -1);

	ASSERT(x.FindLast(1) == 5);
	ASSERT(x.FindPrev(5) == 4);
	ASSERT(x.FindPrev(4) == 3);
	ASSERT(x.FindPrev(3) == -1);

	LOG("============= UNLINK");
	TEST(x.Unlink(0), "#0: 0/0 -> 0:0; 1: 0/0 -> 2:2; 2: 0/0 -> 1:1; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[0]");
	TEST(x.Unlink(1), "#0: 0/0 -> 1:1; #1: 0/0 -> 0:0; 2: 0/0 -> 2:2; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[1, 0]");
	TEST(x.Unlink(2), "#0: 0/0 -> 2:1; #1: 0/0 -> 0:2; #2: 0/0 -> 1:0; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[2, 1, 0]");
	
	LOG("============= PUT");
	TEST(x.Put(2), "#0: 0/0 -> 1:1; #1: 0/0 -> 0:0; 2: 2/6 -> 2:2; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[1, 0]");
	TEST(x.Put(2), "#0: 0/0 -> 0:0; 1: 2/6 -> 2:2; 2: 2/6 -> 1:1; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[0]");
	TEST(x.Put(2), "0: 2/6 -> 1:2; 1: 2/6 -> 2:0; 2: 2/6 -> 0:1; 3: 1/3 -> 5:4; 4: 1/3 -> 3:5; 5: 1/3 -> 4:3");
	UTST("[]");
	
	TEST(x.UnlinkKey(1), "0: 2/6 -> 1:2; 1: 2/6 -> 2:0; 2: 2/6 -> 0:1; #3: 1/0 -> 5:4; #4: 1/0 -> 3:5; #5: 1/0 -> 4:3");
	UTST("[5, 4, 3]");
	
	TEST(x.Put(2), "0: 2/6 -> 1:5; 1: 2/6 -> 2:0; 2: 2/6 -> 5:1; #3: 1/0 -> 4:4; #4: 1/0 -> 3:3; 5: 2/6 -> 0:2");
	UTST("[4, 3]");
	TEST(x.Put(2), "0: 2/6 -> 1:5; 1: 2/6 -> 2:0; 2: 2/6 -> 4:1; #3: 1/0 -> 3:3; 4: 2/6 -> 5:2; 5: 2/6 -> 0:4");
	UTST("[3]");
	TEST(x.Put(2), "0: 2/6 -> 1:5; 1: 2/6 -> 2:0; 2: 2/6 -> 3:1; 3: 2/6 -> 4:2; 4: 2/6 -> 5:3; 5: 2/6 -> 0:4");
	UTST("[]");
	TEST(x.Put(2), "0: 2/6 -> 1:5; 1: 2/6 -> 2:0; 2: 2/6 -> 6:1; 3: 2/6 -> 4:6; 4: 2/6 -> 5:3; 5: 2/6 -> 0:4; 6: 2/6 -> 3:2");
	UTST("[]");
	
	LOG("============= SET");
	TEST(x.Set(1, 5), "0: 2/6 -> 2:5; 1: 5/0 -> 1:1; 2: 2/6 -> 6:0; 3: 2/6 -> 4:6; 4: 2/6 -> 5:3; 5: 2/6 -> 0:4; 6: 2/6 -> 3:2");
	TEST(x.Set(2, 5), "0: 2/6 -> 6:5; 1: 5/0 -> 2:2; 2: 5/0 -> 1:1; 3: 2/6 -> 4:6; 4: 2/6 -> 5:3; 5: 2/6 -> 0:4; 6: 2/6 -> 3:0");
	
	LOG("============= TRIM");
	TEST(x.Unlink(5), "0: 2/6 -> 6:4; 1: 5/0 -> 2:2; 2: 5/0 -> 1:1; 3: 2/6 -> 4:6; 4: 2/6 -> 0:3; #5: 2/0 -> 5:5; 6: 2/6 -> 3:0");
	TEST(x.Trim(4), "0: 2/6 -> 3:3; 1: 5/0 -> 2:2; 2: 5/0 -> 1:1; 3: 2/6 -> 0:0");
	
	LOG("============= SWEEP");
	TEST(x.Unlink(1), "0: 2/6 -> 3:3; #1: 5/0 -> 1:1; 2: 5/0 -> 2:2; 3: 2/6 -> 0:0");
	TEST(x.Sweep(), "0: 2/6 -> 2:2; 1: 5/0 -> 1:1; 2: 2/6 -> 0:0");

	LOG("============= RESERVE");
	TEST(x.Reserve(1000), "0: 2/582 -> 2:2; 1: 5/560 -> 1:1; 2: 2/582 -> 0:0");
	TEST(x.Shrink(), "0: 2/2 -> 2:2; 1: 5/0 -> 1:1; 2: 2/2 -> 0:0");
	
	LOG("============= POP");
	ASSERT(x.Top() == 2);
	TEST(ASSERT(x.Pop() == 2), "0: 2/2 -> 0:0; 1: 5/0 -> 1:1");
	
	LOG("============= Serialize");
	static byte data_[] = { 100,97,116,97,5,1,0,0,0,2,0,0,0,3,0,0,0,4,0,0,0,1,5,1,0,0,0,2,0,0,128,3,0,0,0,4,0,0,0,101,110,100,0,43,0,0,0, };
	String data(data_, __countof(data_));
	DUMP(data.GetCount());
	TEST(LoadFromString(x, data), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
	
	data = StoreAsString(x);
	DUMP(data.GetCount());
	x.Clear();

	TEST(LoadFromString(x, data), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
	
	LOG("============== Json & XML");
	
	String s = StoreAsXML(x);
	LOG(s);
	{
		Index<int> x;
		TEST(LoadFromXML(x, s), "0: 1/3 -> 0:0; 1: 3/2 -> 1:1; 2: 4/1 -> 2:2");
	}

	s = StoreAsJson(x);
	LOG(s);
	{
		Index<int> x;
		TEST(LoadFromJson(x, s), "0: 1/3 -> 0:0; 1: 3/2 -> 1:1; 2: 4/1 -> 2:2");
	}
	
	LOG("============== Pick & Clone");

	{
		Index<int> x2(clone(x));
		TEST(Index<int> x(clone(x2)), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
		TEST(Index<int> x(pick(x2)), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
		ASSERT(x2.GetCount() == 0);
	}

	{
		Index<int> x2(clone(x));
		TEST(x = clone(x2), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
		TEST(x = pick(x2), "0: 1/3 -> 0:0; #1: 2/0 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
		ASSERT(x2.GetCount() == 0);
	}

	Vector<int> h{ 12, 13, 14 };
	
	TEST(x = clone(h), "0: 12/0 -> 0:0; 1: 13/3 -> 2:2; 2: 14/3 -> 1:1");
	h << 15;
	TEST(x = pick(h), "0: 12/0 -> 0:0; 1: 13/3 -> 1:1; 2: 14/7 -> 2:2; 3: 15/2 -> 3:3");
	ASSERT(h.GetCount() == 0);

	Vector<int> h2{ 21, 22, 23 };
	TEST(Index<int> x(clone(h2)), "0: 21/2 -> 1:1; 1: 22/2 -> 0:0; 2: 23/1 -> 2:2");
	TEST(Index<int> x(pick(h2)), "0: 21/2 -> 1:1; 1: 22/2 -> 0:0; 2: 23/1 -> 2:2");
	ASSERT(h2.GetCount() == 0);

	{
		Index<int> x{1, 2, 3};
		TEST(x, "0: 1/3 -> 0:0; 1: 2/2 -> 2:2; 2: 3/2 -> 1:1");
	}
	
	LOG("============== AsString");
	LOG(x.ToString());
	ASSERT(x.ToString() == "[12, 13, 14, 15]");

	LOG("============== SWAP");
	Index<int> x2{ 1, 2, 3, 4 };
	TEST(Swap(x, x2), "0: 1/3 -> 0:0; 1: 2/6 -> 1:1; 2: 3/2 -> 2:2; 3: 4/5 -> 3:3");
	TEST(Swap(x, x2), "0: 12/0 -> 0:0; 1: 13/3 -> 1:1; 2: 14/7 -> 2:2; 3: 15/2 -> 3:3");
	
	LOG("============== Deprecated");
	TEST(x.Insert(1, 999), "0: 12/0 -> 1:1; 1: 999/0 -> 0:0; 2: 13/3 -> 2:2; 3: 14/7 -> 3:3; 4: 15/2 -> 4:4");
	TEST(x.Remove(1, 2), "0: 12/0 -> 0:0; 1: 14/3 -> 1:1; 2: 15/2 -> 2:2");
}

#ifdef _DEBUG
#define TEST(op, result) { op; String s = x.; LOG("TEST(" << #op << ", " << AsCString(s) << ");"); if(*result) ASSERT(s == result); Check(x); }
#define UTST(result)     { String s = AsString(x.GetUnlinked()); LOG("UTST(" << AsCString(s) << ");"); if(*result) ASSERT(s == result); }
#else
#define TEST(op, result)
#define UTST(result)
#endif

void MapTests()
{
	LOG("=============== MAP TESTS
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> map;
		map.Add(k, v);
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> map;
		map.Add(k, pick(v));
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	
#if 0
	T&       Add(const K& k, const T& x)            { key.Add(k); return value.Add(x); }
	T&       Add(const K& k, T&& x)                 { key.Add(k); return value.Add(pick(x)); }
	T&       Add(const K& k)                        { key.Add(k); return value.Add(); }
	T&       Add(K&& k, const T& x)                 { key.Add(pick(k)); return value.Add(x); }
	T&       Add(K&& k, T&& x)                      { key.Add(pick(k)); return value.Add(pick(x)); }
	T&       Add(K&& k)                             { key.Add(pick(k)); return value.Add(); }

	int      Find(const K& k, unsigned h) const     { return key.Find(k, h); }
	int      Find(const K& k) const                 { return key.Find(k); }
	int      FindNext(int i) const                  { return key.FindNext(i); }
	int      FindLast(const K& k, unsigned h) const { return key.FindLast(k, h); }
	int      FindLast(const K& k) const             { return key.FindLast(k); }
	int      FindPrev(int i) const                  { return key.FindPrev(i); }

	int      FindAdd(const K& k)                    { return FindAdd_(k); }
	int      FindAdd(const K& k, const T& init)     { return FindAdd_(k, init); }
	int      FindAdd(const K& k, T&& init)          { return FindAdd_(k, pick(init)); }
	int      FindAdd(K&& k)                         { return FindAdd_(pick(k)); }
	int      FindAdd(K&& k, const T& init)          { return FindAdd_(pick(k), init); }
	int      FindAdd(K&& k, T&& init)               { return FindAdd_(pick(k), pick(init)); }

	T&       Put(const K& k)                        { return Put_(k); }
	int      Put(const K& k, const T& x)            { return Put_(k, x); }
	int      Put(const K& k, T&& x)                 { return Put_(k, pick(x)); }
	T&       Put(K&& k)                             { return Put_(pick(k)); }
	int      Put(K&& k, const T& x)                 { return Put_(pick(k), x); }
	int      Put(K&& k, T&& x)                      { return Put_(pick(k), pick(x)); }

	int      PutDefault(const K& k)                 { return PutDefault_(k); }
	int      PutDefault(K&& k)                      { return PutDefault_(pick(k)); }

	int      FindPut(const K& k)                    { return FindPut_(k); }
	int      FindPut(const K& k, const T& init)     { return FindPut_(k, init); }
	int      FindPut(const K& k, T&& init)          { return FindPut_(k, pick(init)); }
	int      FindPut(K&& k)                         { return FindPut_(pick(k)); }
	int      FindPut(K&& k, const T& init)          { return FindPut_(pick(k), init); }
	int      FindPut(K&& k, T&& init)               { return FindPut_(pick(k), pick(init)); }

	T&       Get(const K& k)                        { return value[Find(k)]; }
	const T& Get(const K& k) const                  { return value[Find(k)]; }
	const T& Get(const K& k, const T& d) const      { int i = Find(k); return i >= 0 ? value[i] : d; }

	T&       GetAdd(const K& k)                     { return GetAdd_(k); }
	T&       GetAdd(const K& k, const T& x)         { return GetAdd_(k, x); }
	T&       GetAdd(const K& k, T&& x)              { return GetAdd_(k, pick(x)); }
	T&       GetAdd(K&& k)                          { return GetAdd_(pick(k)); }
	T&       GetAdd(K&& k, const T& x)              { return GetAdd_(pick(k), x); }
	T&       GetAdd(K&& k, T&& x)                   { return GetAdd_(pick(k), pick(x)); }

	T&       GetPut(const K& k)                     { return GetPut_(k); }
	T&       GetPut(const K& k, const T& x)         { return GetPut_(k, x); }
	T&       GetPut(const K& k, T&& x)              { return GetPut_(k, pick(x)); }
	T&       GetPut(K&& k)                          { return GetPut_(pick(k)); }
	T&       GetPut(K&& k, const T& x)              { return GetPut_(pick(k), x); }
	T&       GetPut(K&& k, T&& x)                   { return GetPut_(pick(k), pick(x)); }

	void     SetKey(int i, const K& k)              { key.Set(i, k); }
	void     SetKey(int i, K&& k)                   { key.Set(i, pick(k)); }
#endif
}

void CarpetBombing()
{
	SeedRandom(0);
	Index<int> x;

	int Q = 20;
	int COUNT = 10000000;

	for(int i = 0; i < COUNT; i++)
	{
		if(i % 100000 == 0)
			LOG("UnlinkKey Put " << i);
		int v = Random(Q);
		x.UnlinkKey(v);
		ASSERT(x.Find(v) < 0);
		Check(x);
		v = Random(Q);
		int q = x.Put(v);
		CheckIn(x, v, q);
		Check(x);
	}

	x.Clear();
	for(int i = 0; i < COUNT; i++)
	{
		if(i % 100000 == 0)
			LOG("FindAdd Clear " << i);
		int v = Random(Q);
		int ii = x.FindAdd(v);
		ASSERT(x[ii] == v);
		ASSERT(x.Find(v) == ii);
		if(Random(Q) == 0)
			x.Clear();
		Check(x);
	}

	for(int i = 0; i < COUNT; i++) {
		if(i % 100000 == 0)
			LOG("Set " << i);
		int ii = Random(x.GetCount());
		int v = Random(Q);
		x.Set(ii, v);
		ASSERT(x[ii] == v);
		CheckIn(x, v, ii);
		Check(x);
	}
	for(int i = 0; i < COUNT; i++) {
		if(i % 100000 == 0)
			LOG("Add Trim " << i);
		int v = Random(Q);
		x.Add(v);
		Check(x);
		if(x.GetCount() > 100) {
			int n = Random(x.GetCount());
			x.Trim(n);
			Check(x);
		}
	}
}

void Benchmark();

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(VectorMap<String, int>));
	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(VectorMap<String, int>));

#ifndef _DEBUG
	RealBenchmark();
	Benchmark();
	return;
#endif

//	RealBenchmarkCollisions();
	BasicTests();

	PickTests();

	CarpetBombing();

	LOG("================= OK");
}
