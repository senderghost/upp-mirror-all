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

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(VectorMap<String, int>));

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
	{
		String k = "A";
		VectorMap<String, String> x;
		x.Add("", "x");
		x.Unlink(0);
		TEST(x.PutDefault(k), "{A: }");
		ASSERT(!IsNull(k));
		TEST(x.PutDefault(pick(k)), "{A: , A: }");
		ASSERT(IsNull(k));
	}

	LOG("================= FINDPUT");
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		x.Add("1", "1");
		x.Unlink(0);
		TEST(ASSERT(x.FindPut(k) == 0), "{A: }");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
		TEST(ASSERT(x.FindPut(k) == 0), "{A: }");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
		TEST(ASSERT(x.FindPut("2") == 1), "{A: , 2: }");
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindPut(k, v) == 0), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindPut(k, pick(v)) == 0), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindPut(pick(k)) == 0), "{A: }");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindPut(pick(k), v) == 0), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.FindPut(pick(k), pick(v)) == 0), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
	}
	LOG("================= GET");
	{
		VectorMap<String, String> x{ { "A", "B" } };
		TEST(x, "{A: B}");
		ASSERT(x.Get("A") == "B");
		ASSERT(x.Get("x", "y") == "y");
	}
	LOG("================= GETADD");
	{
		VectorMap<String, String> x;
		TEST(x.GetAdd("A") = "1", "{A: 1}");
		TEST(x.GetAdd("A") == "1", "{A: 1}");
		TEST(x.GetAdd("B") = "2", "{A: 1, B: 2}");
		TEST(x.GetAdd("B") == "2", "{A: 1, B: 2}");
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.GetAdd(k) = "B", "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetAdd(k, v) == "B"), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetAdd(k, pick(v)) == "B"), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.GetAdd(pick(k)) = "B", "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetAdd(pick(k), v) == "B"), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetAdd(pick(k), pick(v)) == "B"), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
	}
	LOG("================= GETPUT");
	{
		VectorMap<String, String> x;
		x.Add("", "");
		x.Unlink(0);
		TEST(x.GetPut("A") = "1", "{A: 1}");
		TEST(x.GetPut("A") == "1", "{A: 1}");
		TEST(x.GetPut("B") = "2", "{A: 1, B: 2}");
		TEST(x.GetPut("B") == "2", "{A: 1, B: 2}");
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.GetPut(k) = "B", "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetPut(k, v) == "B"), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetPut(k, pick(v)) == "B"), "{A: B}");
		ASSERT(!IsNull(k));
		ASSERT(IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(x.GetPut(pick(k)) = "B", "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetPut(pick(k), v) == "B"), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(!IsNull(v));
	}
	{
		String k = "A"; String v = "B";
		VectorMap<String, String> x;
		TEST(ASSERT(x.GetPut(pick(k), pick(v)) == "B"), "{A: B}");
		ASSERT(IsNull(k));
		ASSERT(IsNull(v));
	}
	LOG("================= PICK(MAP)");
	{
		VectorMap<String, String> map, map2;
		map.Add("Test1", "Test2");
		map2 = pick(map);
		map.Add("Test3", "Test4");
		map2 = pick(map);
	}
	LOG("================= SETKEY");
	{
		VectorMap<String, String> x;
		x.Add("A", "1");
		x.Add("B", "2");
		x.Unlink(0);
		String k = "X";
		TEST(x.SetKey(0, k), "");
		ASSERT(!IsNull(k));
		TEST(x.SetKey(1, pick(k)), "");
		ASSERT(IsNull(k));
	}

	LOG("================= OK");
}
