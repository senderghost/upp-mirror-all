#include <Core/Core.h>

using namespace Upp;

template <class I, class Accumulator>
void CoAccumulate(I begin, I end, Accumulator& result)
{
	const size_t chunk = (end - begin) / CPU_Cores();
	CoWork co;
	while(begin < end) {
		co & [=, &result] {
			Accumulator h;
			I i = begin;
			I e = i + min(chunk, size_t(end - begin));
			while(i < e)
				h(*i++);
			INTERLOCKED
				result(h);
		};
		begin += chunk;
	}
}

template <class T>
struct Summer {
	T value;
	
	void operator()(const T& x) { value += x; }
	void operator()(const Summer& s) { value += s.value; }
	Summer() { value = 0; }
};

#ifdef _DEBUG
#define N 20005
#else
#define N 500000
#endif

CONSOLE_APP_MAIN
{
	Vector<int> a;
	for(int i = 0; i < N; i++)
		a.Add(Random());
	
	int sum1;
	int sum2;
	
	for(int i = 0; i < 10000; i++) {
		{
			RTIMING("Parallel");
			Summer<int> x;
			CoAccumulate(a.Begin(), a.End(), x);
			sum1 = x.value;
		}
		{
			RTIMING("Serial");
			sum2 = Sum0(a);
		}
	}
	
	RLOG(sum1);
	RLOG(sum2);
	
	ASSERT(sum1 == sum2);
}
