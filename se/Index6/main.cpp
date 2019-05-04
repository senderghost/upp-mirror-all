#include "Index.h"


int nnn = 200;
int val = 0;
int sum = 0;

#define N 1000

void Benchmark()
{
	Vector<String> data;
	for(int i = 0; i < N; i++)
		data.Add(AsString(i) + "aaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	int rep = max(100000000 / N, 1);
	for(int n = 0; n < rep; n++) {
		{
			New::Index<int> test;
			{
				RTIMING("New int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("New int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
		}
		{
			Index<int> test;
			{
				RTIMING("Old int add");
				for(int i = 0; i < N; i++) {
					test.Add(i);
				}
			}
			{
				RTIMING("Old int find");
				for(int i = 0; i < N; i++) {
					if(test.Find(i) == i)
						sum++;
				}
			}
		}
		{
			New::Index<String> test;
			{
				RTIMING("New string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("New string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
		}
		{
			Index<String> test;
			{
				RTIMING("Old string add");
				for(int i = 0; i < N; i++) {
					test.Add(data[i]);
				}
			}
			{
				RTIMING("Old string find");
				for(int i = 0; i < N; i++) {
					sum += test.Find(data[i]);
				}
			}
		}
	}
	RDUMP(sum);
}

void Check(const New::Index<int>& x)
{
	for(int i = 0; i < x.GetCount(); i++) {
		if(!x.IsUnlinked(i)) {
			int q = x.Find(x[i]);
			ASSERT(x[i] == x[q]);
			while(q >= 0) {
				ASSERT(x[i] == x[q]);
				q = x.FindNext(i);
			}
		}
	}
}

String AsString(const New::Index<int>& x)
{
	String r;
	int n = 0;
	for(int i = 0; i < x.GetCount(); i++) {
		if(i)
			r << ", ";
		if(x.IsUnlinked(i)) {
			r << "#";
			n++;
		}
		r << x[i];
	}
	return String() << "(" << x.GetCount() << "/#" << n << "): " << r;
}

CONSOLE_APP_MAIN
{
	New::Index<int> x;
	
	SeedRandom(0);
	
	x.Add(1);
	x.Add(1);
	LOG(AsString(x));
	x.UnlinkKey(1);
	LOG(AsString(x));

	int Q = 20;
	for(int i = 0; i < 1000; i++) {
		int v = Random(Q);
		x.UnlinkKey(v);
		Check(x);
		LOG("Removed " << v << ": " << AsString(x));
		v = Random(Q);
		{
			RTIMING("Push");
			x.Push(v);
		}
		LOG("Pushed  " << v << ": " << AsString(x));
		Check(x);
	}
	
	RDUMP(sizeof(Index<int>));
	RDUMP(sizeof(New::Index<int>));
	return;

#ifndef _DEBUG
	Benchmark();
#endif

	New::Index<int> test;
	for(int i = 0; i < 10000; i++) {
		test.Add(i);
		if(test.Find(i) == i)
			sum++;
		ASSERT(test.Find(i) == i);
	}

	DUMP(sum);

#if 0
	New::HashBase h;
	for(int i = 0; i < nnn; i++) {
		val = Random(20);
		RLOG("--- " << val);
		h.Add(val);
		h.Find(val, [&](int i) { LOG(i << " " << h[i]); sum += i; return false; });
	}
#endif
}
