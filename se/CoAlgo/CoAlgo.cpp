#include <Core/Core.h>

using namespace Upp;

template <typename I, typename Lambda>
void CoLoop(I begin, I end, const Lambda& lambda)
{
	size_t chunk = max(size_t((end - begin) / CPU_Cores()), (size_t)1);
	CoWork co;
	while(begin < end) {
		co & [=] {
			lambda(begin, begin + min(chunk, size_t(end - begin)));
		};
		begin += chunk;
	}
}

template <class I, class Accumulator>
void CoAccumulate(I begin, I end, Accumulator& result)
{
	CoLoop(begin, end,
		[=, &result](I i, I e) {
			Accumulator h;
			while(i < e)
				h(*i++);
			CoWork::FinLock();
			result(h);
		}
	);
}

template <class I, class Better>
I CoBest(I begin, I end, const Better& better)
{
	I best = begin++;
	CoLoop(begin, end,
		[=, &best](I i, I e) {
			I b = i++;
			while(i < e) {
				if(better(*i, *b))
					b = i;
				i++;
			}
			CoWork::FinLock();
			if(better(*b, *best))
				best = b;
		}
	);
	return best;
}

struct Summer {
	int value;
	
	void operator()(const String& x) { value += atoi(x); }
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
	RDUMP(CPU_Cores());

	Vector<String> a;
	for(int i = 0; i < N; i++)
		a.Add(AsString(Random()));
	

	if(1) {
		int sum1;
		int sum2;
		for(int i = 0; i < 100; i++) {
			{
				RTIMING("Parallel");
				Summer x;
				CoAccumulate(a.Begin(), a.End(), x);
				sum1 = x.value;
			}
			{
				RTIMING("Serial");
				sum2 = 0;
				for(int i = 0; i < a.GetCount(); i++)
					sum2 += atoi(a[i]);
			}
		}
		RLOG(sum1);
		RLOG(sum2);
		ASSERT(sum1 == sum2);
	}

	int pos1, pos2;
#ifdef _DEBUG
	for(int i = 0; i < 1; i++)
#else
	for(int i = 0; i < 100; i++)
#endif
	{
		{
			RTIMING("Parallel CoBest");
			pos1 = CoBest(a.Begin(), a.End(), [=](const String& a, const String& b) { return atoi(a) < atoi(b); })
			       - a.Begin();
		}
		{
			RTIMING("Serial CoBest");
			pos2 = 0;
			for(int i = 1; i < a.GetCount(); i++)
				if(atoi(a[i]) < atoi(a[pos2]))
					pos2 = i;
		}
	}
	RLOG(pos1);
	RLOG(pos2);
	
	{
		Vector<double> a;
		for(int i = 0; i < 10000000; i++)
			a.Add(Randomf());
		for(int i = 0; i < 100; i++)
		{
			{
				RTIMING("Parallel CoBest F");
				pos1 = CoBest(a.Begin(), a.End(), [=](double a, double b) { return a < b; })
				       - a.Begin();
			}
			{
				RTIMING("Serial CoBest F");
				pos2 = 0;
				for(int i = 1; i < a.GetCount(); i++)
					if(a[i] < a[pos2])
						pos2 = i;
			}
		}
		RLOG(pos1);
		RLOG(pos2);
	}
}
