#include <Core/Core.h>

using namespace Upp;

class SearchPoints {
	int            dims;
	int            count;
	Vector<double> point;
	Buffer<double> projector[10];

	struct PI : Moveable<PI> { // point & distance
		int    index;
		double distance;
		
		bool   operator<(const PI& b) const            { return distance < b.distance; }
	};
	
	struct Ball : Moveable<Ball> { // hypersphere with its points
		int         center;
		double      radius;
		double      projected_min;
		double      projected_max;
		Vector<PI>  point;
		Vector<int> closest; // closest point to ball i center
		Vector<double> closest_distance; // distance of closest point to ball i center
	};
	
	Vector<Ball> ball;

	const double *At(int i) const                      { return (const double *)point + dims * i; }
	double  SquaredDistance(const double *a, const double *b);
	double  SquaredDistance(int ai, int bi)            { return SquaredDistance(At(ai), At(bi)); }
	double  Distance(int ai, int bi)                   { return Distance(At(ai), At(bi)); }
	bool    FindCloserPoint(const Ball& b, const double *p, int fromi, int& besti, double& qbest);
	double  Project(const double *p, int pi = 0) const;
	double  Project(int i, int pi = 0) const           { return Project(At(i), pi); }

public:
	void   MakeV(Buffer<double>& v);
	double Distance(const double *a, const double *b) { return sqrt(SquaredDistance(a, b)); }

	void Dimensions(int n);
	void Add(const double *p);
	void Finish();

	int  GetDimensions() const                    { return dims; }
	int  GetCount() const                         { return count; }
	const double *operator[](int i) const         { return At(i); }

	int  Search(const double *p);

// performance counters
	int distance_tests = 0; // performance counter
	int excluded_balls = 0;
	int balls_tested = 0;
	int best_count = 0;
	int best_maxi = 0;
	
	void ClearCounters() { distance_tests = excluded_balls = balls_tested = best_count = best_maxi = 0; }
	void DumpCounters();
	
// diagnostics only...
	int  SimpleSearch(const double *p);
	String AsString(const double *p);
	String AsString(int i)                        { return AsString(At(i)); }
	String AsString(const Ball& b);
	void   Dump(const Ball& b);
};
