#include "SearchPoints.h"

const int M = 100000;
const int R = 1000;
const int N = 100;

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
	if(!in.GetAll(~vec, in_dim * sizeof(float)) || in.Get32le() != in_dim)
		return NULL;
	for(int i = 0; i < in_dim; i++)
		dvec[i] = vec[i];
	return dvec;
}

CONSOLE_APP_MAIN {
	SeedRandom(0);

	SearchPoints sp;
	sp.Dimensions(20);

#if 1
	FVecReader in;
	ASSERT(in.Open("C:/xxx/sift/sift/sift_base.fvecs"));
	for(int i = 0; i < M && !in.IsEof(); i++)
		sp.Add(in.Get());
#else
	for(int i = 0; i < M; i++) {
		sp.Add(RandomPoint());
	}
#endif

	DDUMP(sp.Distance(Zero(), MaxR()));
	
	sp.Finish();
	
	
//	for(int i = 0; i < sp.GetCount(); i++)
//		RLOG(sp.AsString(i));
	
	int maxi_max = 0;

	in.Open("C:/xxx/sift/sift/sift_query.fvecs");
	for(int i = 0; i < 40; i++) {
		const double *p = in.Get();
		RLOG("==========================");
		RLOG(sp.AsString(p));
//		int ii = sp.SimpleSearch(p);
		sp.ClearCounters();
		int fi = sp.Search(p);
		sp.DumpCounters();
		maxi_max = max(maxi_max, sp.best_maxi);
//		double d1 = sqrt(sp.SquaredDistance(p, sp.At(ii)));
//		double d2 = sqrt(sp.SquaredDistance(p, sp.At(fi)));
//		RLOG(sp.AsString(p) << ", closest point " << ii << " " << sp.AsString(ii) << ", distance: " << d1
//		      << ", fast: " << fi << " " << sp.AsString(fi) << ", distance: " << d2);

//		ASSERT(d1 == d2);
	}
	
	DDUMP(maxi_max);

//	RLOG("Total steps " << 2 * gsteps << " vs " << ssteps);
}
