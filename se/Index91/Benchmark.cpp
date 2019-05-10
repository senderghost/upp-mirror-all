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

int PopCnt(dword n)
{
	int cnt = 0;
	for(dword b = 0x80000000; b; b >>= 1)
		cnt += !!(b & n);
	return cnt;
}

void NumberInfo(dword n)
{
	RLOG("====================================");
	RLOG("0x" << FormatIntHex(n));
	RLOG(FormatIntBase(n, 2));
	RLOG("Bit count: " << PopCnt(n));
}

dword MakeHashNumber()
{
	dword w = 0x80000001;
	while(PopCnt(w) < 16)
		w |= 1 << Random(32);
	return w;
}

void RealBenchmark()
{
	RealBenchmarkT<New::VectorMap<String, int>>();
#ifndef _DEBUG
	StdLogSetup(LOG_FILE|LOG_COUT);

	const int N = 10000;
	int bh = hash_const1;

#if 0
	for(;;) {
		dword th = Random();
		NumberInfo(th);
#else
	int th = 0;
	{
#endif
		{
			TimeStop tm;
			hash_const1 = th;
			for(int i = 0; i < N; i++)
				RealBenchmarkT<New::VectorMap<String, int>>();
			hash_const1 = bh;
			RLOG("New " << tm);
		}
		{
			TimeStop tm;
			hash_const1 = th;
			for(int i = 0; i < N; i++)
				RealBenchmarkT<VectorMap<String, int>>();
			hash_const1 = bh;
			RLOG("Old " << tm);
		}
	}
#endif
}
