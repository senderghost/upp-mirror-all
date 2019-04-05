#include <Core/Core.h>

using namespace Upp;

class SearchPoints {
	int            dims;
	int            count;
	Vector<double> point;

	struct Ball : Moveable<Ball> { // hypersphere with its points
		double         radius;
		Buffer<double> center;
		Vector<int>    point;
		Vector<double> point_distance;
	};
	
	Vector<Ball> ball;

	const double *At(int i) const                      { return (const double *)point + dims * i; }

public:
	double  SquaredDistance(const double *a, const double *b) const;
	double  SquaredDistance(int ai, int bi) const            { return SquaredDistance(At(ai), At(bi)); }
	double  Distance(int ai, int bi) const                   { return Distance(At(ai), At(bi)); }
	double  Distance(const double *a, const double *b) const { return sqrt(SquaredDistance(a, b)); }
	void    Copy(Vector<double>& t, const double *s) const;
	void    Copy(Buffer<double>& t, const double *s) const;
	Buffer<double> Copy(const double *s) const               { Buffer<double> h; Copy(h, s); return h; }
	double *Add(double *t, const double *s) const;
	double *Sub(double *t, const double *s) const;
	double *Mul(double *t, double a) const;
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
	int excluded_points = 0;
	int first_count = 0;
	
	void ClearCounters()                          { distance_tests = excluded_points = first_count = 0; }
	void DumpCounters();
	
// diagnostics only...
	int  SimpleSearch(const double *p);
	String AsString(const double *p) const;
	String AsString(int i) const                  { return AsString(At(i)); }
	String AsString(const Ball& b) const;
};
