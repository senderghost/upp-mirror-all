#include "NNSearch.h"

const int M = 100000;
const int R = 1000;
const int Q = 10;

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
//	SeedRandom(0);

	NNSearch sp;
	sp.Dimensions(20);

	FVecReader in;
	in.Open("C:/xxx/sift/sift/sift_base.fvecs");
	for(int i = 0; i < M && !in.IsEof(); i++)
		sp.Add(in.Get());

	sp.PrepareForSearch();
	
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
