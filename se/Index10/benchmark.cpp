#include "Index.h"

String data = LoadFile("C:/u/upp.src/benchmarks/idmapBench/alice30.txt");

template <class T>
void RealBenchmarkT() {
	StringStream in(data);

	T map;
	int line = 1;

	for(;;) {
		int c = in.Get();
		if(c < 0) break;
		if(IsAlpha(c) || c == '_') {
			String id;
			id.Cat(c);
			c = in.Get();
			while(c >= 0 && (IsAlNum(c) || c == '_')) {
				id.Cat(c);
				c = in.Get();
			}
			map.GetAdd(id, 0)++;
		}
		else
		if(IsDigit(c))
			do c = in.Get();
			while(c >= 0 && (IsAlNum(c) || c == '.'));
		if(c == '\n')
			++line;
	}

#ifdef _DEBUG
	DUMPM(map);
#endif
}


void RealBenchmark()
{
	RealBenchmarkT<New::VectorMap<String, int>>();
#ifndef _DEBUG
	const int N = 10000;
	{
		TimeStop tm;
		for(int i = 0; i < N; i++)
			RealBenchmarkT<New::VectorMap<String, int>>();
		RLOG("New " << tm);
	}
	{
		TimeStop tm;
		for(int i = 0; i < N; i++)
			RealBenchmarkT<VectorMap<String, int>>();
		RLOG("Old " << tm);
	}
#endif
}