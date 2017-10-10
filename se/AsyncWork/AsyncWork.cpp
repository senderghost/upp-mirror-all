#include <Core/Core.h>

using namespace Upp;

template <class Range>
ValueTypeOf<Range> ASum(const Range& rng, const ValueTypeOf<Range>& zero)
{
	int n = rng.GetCount();
	if(n == 1)
		return rng[0];
	if(n == 0)
		return 0;
	auto l = Async([&] { return ASum(SubRange(rng, 0, n / 2)); });
	auto r = Async([&] { return ASum(SubRange(rng, n / 2, n - n / 2)); });
	while(!l.IsFinished() || !r.IsFinished())
		Sleep(1);
	return l.Get() + r.Get();
}

template <class T>
ValueTypeOf<T> ASum(const T& c)
{
	return ASum(c, (ValueTypeOf<T>)0);
}


CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	{
		Vector<int> h;
		for(int i = 0; i < 100; i++)
			h.Add(Random());
		
		DDUMP(CoSum(h));
		DDUMP(Sum(h));
		DDUMP(ASum(h));
	}
	return;

	
	auto h = Async([] { return "Hello world"; });
	DDUMP(h.Get());
	
	AsyncWork<const char *> xx;
	xx = pick(h);
	
	DDUMP(~Async([](int x) { return x * x; }, 9));
	
	auto x = Async([] { throw "error"; });
	try {
		x.Get();
	}
	catch(...) {
		DLOG("Exception caught");
	}
}
