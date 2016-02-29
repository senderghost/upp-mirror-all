#include <Core/Core.h>

using namespace Upp;

Vector<int> ih;
Vector<String> sh;
Vector<String> sh2;
Vector<String> sh3;

void Reset()
{
	ih.Clear();
	sh.Clear();
	sh2.Clear();
	sh3.Clear();
	for(int i = 0; i < 20; i++) {
		int x = Random(100);
		ih.Add(x);
		String h = Format("%03d", x);
		sh.Add(h);
		sh2.Add(h + "A");
		sh3.Add(h + "B");
	}
}

template <class Range>
void Check(const Range& r)
{
	for(int i = 1; i < r.GetCount(); i++)
		ASSERT(r[i] >= r[i - 1]);
}

template <class Range>
void Check2(const Range& r)
{
	for(int i = 1; i < r.GetCount(); i++)
		ASSERT(r[i] <= r[i - 1]);
}

template <class Range>
void Check(const Vector<int>& o, const Range& r)
{
	for(int i = 1; i < r.GetCount(); i++)
		ASSERT(r[o[i]] >= r[o[i - 1]]);
}


CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);

	SeedRandom(0);

	Reset();
	IndexSort(ih, sh);
	DUMP(ih);
	DUMP(sh);
	Check(ih);
	Check(sh);
	LOG("==============");
	Reset();
	IndexSort2(ih, sh, sh2);
	DUMP(ih);
	DUMP(sh);
	DUMP(sh2);
	Check(ih);
	Check(sh);
	Check(sh2);
	LOG("==============");
	Reset();
	IndexSort3(ih, sh, sh2, sh3);
	DUMP(ih);
	DUMP(sh);
	DUMP(sh2);
	Check(ih);
	Check(sh);
	Check(sh2);
	Check(sh3);
	LOG("==============");
	Reset();
	StableIndexSort(ih, sh);
	DUMP(ih);
	DUMP(sh);
	Check(ih);
	Check(sh);
	LOG("==============");
	Reset();
	StableIndexSort2(ih, sh, sh2);
	DUMP(ih);
	DUMP(sh);
	DUMP(sh2);
	Check(ih);
	Check(sh);
	Check(sh2);
	LOG("==============");
	Reset();
	StableIndexSort3(ih, sh, sh2, sh3);
	DUMP(ih);
	DUMP(sh);
	DUMP(sh2);
	Check(ih);
	Check(sh);
	Check(sh2);
	Check(sh3);
	LOG("==============");
	Reset();
	StableSort(ih, std::greater<int>());
	DUMP(ih);
	Check2(ih);
	Reset();
	StableSort(ih);
	DUMP(ih);
	Check(ih);
	LOG("===============");
	{
		Reset();
		Vector<int> o = GetSortOrder(ih);
		DDUMP(ih);
		DDUMP(o);
		Check(o, ih);
		DDUMP(ViewRange(ih, pick(o)));
	}
	LOG("===============");
	{
		Reset();
		Vector<int> o = GetStableSortOrder(ih);
		DDUMP(ih);
		DDUMP(o);
		Check(o, ih);
		DDUMP(ViewRange(ih, pick(o)));
	}
	LOG("========================= OK");
}
