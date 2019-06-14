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
	chunk = clamp((end - begin) / CPU_Cores(), 1, 200);
}

template <class Range, class Predicate>
Vector<int> CoFindAll2(const Range& r, Predicate match, int from = 0)
{
	Vector<Vector<int>> rs;
	int total = 0;
	
	CoPartitioner p(from, r.GetCount());
	
	CoDo([&] {
		Vector<Vector<int>> r;
		for(size_t b = p++; b < r.GetCount(); b = p++)
			r.Add(pick(FindAll(SubRange(0, p.End(b), match, b))));
		CoWork::FinLock();
		rs.Append(pick(r));
	});
	CoSort(rs, [](const Vector<int>& a, const Vector<int>& b) { return a[0] < b[0]; });
	Vector<int> result;
	for(const auto& s : rs)
		result.Append(s);
	return result;
}

CONSOLE_APP_MAIN
{
}
