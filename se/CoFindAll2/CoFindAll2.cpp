#include <Core/Core.h>

using namespace Upp;

class CoPartitioner {
	std::atomic<int> ii = 0;
	int begin;
	int end;
	int chunk;

public:
	int operator++(int) { return chunk * ii++; }
	int End(int b)      { return min(b + chunk, end); }

	CoPartitioner(int begin, int end);
};

CoPartitioner::CoPartitioner(int begin, int end)
:	begin(begin), end(end)
{
	chunk = clamp((end - begin) / CPU_Cores(), 1, 20000);
}

template <class Range, class Predicate>
Vector<int> CoFindAll2(const Range& r, Predicate match, int from = 0)
{
	Vector<Vector<int>> rs;
	int total = 0;
	
	CoPartitioner p(from, r.GetCount());
	CoDo([&] {
		Vector<Vector<int>> sr;
		for(int b = p++; b < r.GetCount(); b = p++) {
			Vector<int> f = pick(FindAll(SubRange(r, 0, p.End(b)), match, b));
			if(f.GetCount())
				sr.Add(pick(f));
		}
		CoWork::FinLock();
		rs.Append(pick(sr));
	});
	CoSort(rs, [](const Vector<int>& a, const Vector<int>& b) { return a[0] < b[0]; });
	Vector<int> result;
	for(const auto& s : rs)
		result.Append(s);
	return result;
}


CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	Vector<int> data;
	for(int i = 0; i < 100000000; i++)
		data.Add(Random());
#if 0	
	{
		RTIMING("FindAll");
		RDUMP(FindAll(data, [=](int c) { return c % 177777 == 0; }).GetCount());
	}
	{
		RTIMING("CoFindAll");
		RDUMP(CoFindAll(data, [=](int c) { return c % 177777 == 0; }).GetCount());
	}
	{
		RTIMING("CoFindAll2");
		RDUMP(CoFindAll2(data, [=](int c) { return c % 177777 == 0; }).GetCount());
	}
#endif
	data.Trim(200000);
	
	for(int i = 0; i < 1000; i++) {
		{
			RTIMING("FindAll 1000");
			int ii = FindAll(data, [=](int c) { return c % 17 == 0; }).GetCount();
			ONCELOCK { RDUMP(ii); }
		}
		{
			RTIMING("CoFindAll 1000");
			int ii = CoFindAll(data, [=](int c) { return c % 17 == 0; }).GetCount();
			ONCELOCK { RDUMP(ii); }
		}
		{
			RTIMING("CoFindAll2 1000");
			int ii = CoFindAll2(data, [=](int c) { return c % 17 == 0; }).GetCount();
			ONCELOCK { RDUMP(ii); }
		}
	}

	LOG("===================== OK");
}
