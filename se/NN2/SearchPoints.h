#include <Core/Core.h>

using namespace Upp;

class SearchPoints {
	int            dims;
	int            count;
	Vector<double> point;

	struct Ball : Moveable<Ball> { // hypersphere with its points
		int          center;
		double       radius = 0;
		int          inner_points;
		Vector<int>  point;
		Vector<int>  closest; // closest point to ball i center
	};
	
	Vector<Ball> ball;

	const double *At(int i) const                      { return (const double *)point + dims * i; }
	bool    FindCloserPoint(const Ball& b, const double *p, int fromi, int& besti, double& qbest);

public:
	double  SquaredDistance(const double *a, const double *b) const;
	double  SquaredDistance(int ai, int bi) const            { return SquaredDistance(At(ai), At(bi)); }
	double  Distance(int ai, int bi) const                   { return Distance(At(ai), At(bi)); }
	double  Distance(const double *a, const double *b) const { return sqrt(SquaredDistance(a, b)); }
	void    Copy(Vector<double>& t, const double *s) const;
	void    Copy(Buffer<double>& t, const double *s) const;
	Buffer<double> Copy(const double *s) const               { Buffer<double> h; Copy(h, s); return h; }
	const double *Sub(double *t, const double *s) const;
	void    Unit(double *t) const;
	double  Scalar(const double *a, const double *b) const;
	double  Length(const double *s) const;

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
	String AsString(const double *p) const;
	String AsString(int i) const                  { return AsString(At(i)); }
	String AsString(const Ball& b) const;
};
