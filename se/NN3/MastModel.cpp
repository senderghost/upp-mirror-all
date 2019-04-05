#include "SearchPoints.h"

const int M = 100000;
const int R = 1000;
const int Q = 10;

double *RandomPoint()
{
	static double x[20];
	for(int i = 0; i < 20; i++)
		x[i] = Random(R);
	return x;
}

double *Zero()
{
	static double x[20];
	return x;
}

double *MaxR()
{
	static double x[20];
	for(int i = 0; i < 20; i++)
		x[i] = R;
	return x;
}

struct FVecReader {
	FileIn in;
	int    in_dim;
	Buffer<float> vec;
	Buffer<double> dvec;
	
	bool Open(const char *path);
	bool IsEof();
	const double *Get();
};

bool FVecReader::Open(const char *path)
{
	if(!in.Open(path))
		return false;
	in_dim = in.Get32le();
	vec.Alloc(in_dim);
	dvec.Alloc(in_dim);
	return true;
}

bool FVecReader::IsEof()
{
	return in.IsEof();
}

const double *FVecReader::Get()
{
	if(!in.GetAll(~vec, in_dim * sizeof(float)))
		return NULL;
	in.Get32le();
	for(int i = 0; i < in_dim; i++)
		dvec[i] = vec[i];
	return dvec;
}

CONSOLE_APP_MAIN {
	SeedRandom(0);

	SearchPoints sp;
	sp.Dimensions(80);

	FVecReader in;
	in.Open("C:/xxx/sift/sift/sift_base.fvecs");
	for(int i = 0; i < M && !in.IsEof(); i++)
		sp.Add(in.Get());

	sp.Finish();
	
	in.Open("C:/xxx/sift/sift/sift_query.fvecs");
	for(int i = 0; i < Q; i++) {
		const double *p = in.Get();
//		RLOG("==========================");
//		RLOG(sp.AsString(p));
		int fi = sp.Search(p);
	}

	RDUMP(sp.GetCount());
	RDUMP(sp.GetDimensions());
	sp.DumpCounters();
	
	if(sp.distance_tests)
		RLOG("Speedup " << Q * M / sp.distance_tests);
}
