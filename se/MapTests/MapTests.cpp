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

#ifdef _DEBUG
#define TEST(op, result) { op; String s = AsString(x); LOG("TEST(" << #op << ", " << AsCString(s) << ");"); if(*result) ASSERT(s == result); Check(x.GetIndex()); }
#define UTST(result)     { String s = AsString(x.GetUnlinked()); LOG("UTST(" << AsCString(s) << ");"); if(*result) ASSERT(s == result); }
#else
#define TEST(op, result)
#define UTST(result)
#endif

void PickTests()
{
	LOG("=============== Add");
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(k, v), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(k, pick(v)), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(k), "{A: }");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(pick(k)), "{A: }");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(pick(k), v), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add(pick(k), pick(v)), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
	}
	
	LOG("================= FIND");
	{
		VectorMap<String, String> x;
		TEST(x.Add("A", "1"), "{A: 1}");
		TEST(x.Add("A", "2"), "{A: 1, A: 2}");
		
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
		ASSERT(x.FindLast("A") == 1);
		ASSERT(x.FindPrev(1) == 0);
		ASSERT(x.FindPrev(0) == -1);
	}
	
	LOG("================= FINDADD");
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(k) == 0), "{A: }");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(k, v) == 0), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(k, pick(v)) == 0), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(pick(k)) == 0), "{A: }");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(pick(k), v) == 0), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindAdd(pick(k), pick(v)) == 0), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
	}
	
	LOG("================= PUT");
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add("", ""), "{: }");
		TEST(x.Unlink(0), "{UNLINKED : }");
		TEST(x.Put(k), "{A: }");
		TEST(x.Put(k), "{A: , A: }");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		x.Add("", "");
		x.Unlink(0);
		TEST(x.Put(k, v), "{A: B}");
		TEST(x.Put(k, v), "{A: B, A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		x.Add("", "");
		x.Unlink(0);
		TEST(x.Put(k, pick(v)), "{A: B}");
		ASSERT(IsNull(v));
		v = "C";
		TEST(x.Put(k, pick(v)), "{A: B, A: C}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.Add("", ""), "{: }");
		TEST(x.Unlink(0), "{UNLINKED : }");
		TEST(x.Put(pick(k)), "{A: }");
		ASSERT(IsNull(k));
		k = "A";
		TEST(x.Put(pick(k)), "{A: , A: }");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		x.Add("", "");
		x.Unlink(0);
		TEST(x.Put(pick(k), v), "{A: B}");
		ASSERT(IsNull(k));
		k = "A";
		TEST(x.Put(pick(k), v), "{A: B, A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		x.Add("", "");
		x.Unlink(0);
		TEST(x.Put(pick(k), pick(v)), "{A: B}");
		ASSERT(IsNull(k));
		k = "A";
		ASSERT(IsNull(v));
		v = "C";
		TEST(x.Put(pick(k), pick(v)), "{A: B, A: C}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
		ASSERT(x.Find("A") == 0);
		ASSERT(x.FindNext(0) == 1);
		ASSERT(x.FindNext(1) == -1);
	}


	
#if 0
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
CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(VectorMap<String, int>));

//	RealBenchmarkCollisions();
	PickTests();

	LOG("================= OK");
}
