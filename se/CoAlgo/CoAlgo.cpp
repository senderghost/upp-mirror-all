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

template <class I, class Eq>
int CoFind(I begin, int count, const Eq& eq)
{
	int found = count;
	CoLoop(0, count,
		[=, &found](int i, int e) {
			while(i < e) {
				if(found < i)
					break;
				if(eq(begin[i])) {
					CoWork::FinLock();
					found = i;
					return;
				}
				i++;
			}
		}
	);
	return found < count ? found : -1;
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
#define N 5000000
#endif

CONSOLE_APP_MAIN
{
	RDUMP(CPU_Cores());

	Vector<String> data;
	for(int i = 0; i < N; i++)
		data.Add(AsString(Random()));
	
	for(int i = 0; i < 1000; i++) {
		String f = data[Random(data.GetCount())];
		int a;
		int b;
		{
			RTIMING("Serial");
			a = FindIndex(data, f);
		}
		{
			RTIMING("Parallel");
			b = CoFind(data.Begin(), data.GetCount(), [=](const String& s) { return s == f; });
		}
		
		if(a != b)
			Panic("!!!");
	}

	return;
	
	int samples = 100000000;
	{
		RTIMING("Parallel");
		int count = 0;
		CoLoop(0, samples,
			[=, &count](int a, int b) {
				int lcount = 0;
				while(a < b) {
					double x = Randomf();
					double y = Randomf();
					if(sqrt(x*x + y*y) < 1)
						lcount++;
					a++;
				}
				CoWork::FinLock();
				count += lcount;
			}
		);
		RDUMP(4.0 * count / samples);
	}
	{
		RTIMING("Serial");
		int count = 0;
		for(int i = 0; i < samples; i++) {
			double x = Randomf();
			double y = Randomf();
			if(sqrt(x*x + y*y) < 1)
				count++;
		}
		RDUMP(4.0 * count / samples);
	}
	return;

#if 0
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
#endif
}
