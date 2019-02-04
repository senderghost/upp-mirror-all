#include <Core/Core.h>

using namespace Upp;

Vector<Tuple2<String, double>> data;

int N = 10000000;

struct Bench {
	String name;
	double count;
	int    time0;
	
	Bench(const char *nm, double n = N * 256) {
		name = nm;
		time0 = msecs();
		count = n;
	}
	
	~Bench() {
		RDUMP(msecs());
		RDUMP(time0);
		int t = msecs() - time0;
		RDUMP(t);
		data.Add(MakeTuple(name, t / count));
	}
};

static int array[256];
int an = 256;

CONSOLE_APP_MAIN
{
	int n = Random(128) + 1;
	const int *end = array + an;
	{
		Bench("Add", 1);
		RTIMING("Add");
		Sleep(200);
		for(int i = 0; i < N; i++)
			for(int *d = array; d != end; d++)
				*d += n;
	}
	
	RDUMP(n);
	RDUMP(array[0]);
	RDUMP(array[1]);
	RDUMP(data);
}
