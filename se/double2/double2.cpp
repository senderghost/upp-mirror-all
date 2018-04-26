#include <Core/Core.h>

#include "emmintrin.h"
#include "pmmintrin.h"

using namespace Upp;

struct double2 : Moveable<double2> {
	__m128d value;
	
	void SetL(double x)                   { value = _mm_loadl_pd(value, &x); }
	void SetH(double x)                   { value = _mm_loadh_pd(value, &x); }
	void SetLH(double x)                  { value = _mm_set1_pd(x); }
	
	double GetL() const                   { double x; _mm_storel_pd(&x, value); return x; }
	double GetH() const                   { double x; _mm_storeh_pd(&x, value); return x; }

	void   Swap()                         { value = _mm_shuffle_pd(value, value, 1); }
	
	String ToString() const               { return String() << GetH() << ", " << GetL(); }

	double2  operator+(const double2& h) const { return _mm_add_pd(value, h.value); }
	double2  operator-(const double2& h) const { return _mm_sub_pd(value, h.value); }
	double2  operator*(const double2& h) const { return _mm_mul_pd(value, h.value); }
	double2  operator/(const double2& h) const { return _mm_div_pd(value, h.value); }

	double2  operator-() const             { return _mm_sub_pd(_mm_setzero_pd(), value); } // OPTIMIZE!
	
	double2& operator+=(const double2& h) { value = _mm_add_pd(value, h.value); return *this; }
	double2& operator-=(const double2& h) { value = _mm_sub_pd(value, h.value); return *this; }
	double2& operator*=(const double2& h) { value = _mm_mul_pd(value, h.value); return *this; }
	double2& operator/=(const double2& h) { value = _mm_div_pd(value, h.value); return *this; }
	
	double2 sqrt() const                  { return _mm_sqrt_pd(value); }
	double2 abs() const                   { return _mm_max_pd(_mm_sub_pd(_mm_setzero_pd(), value), value); }
	double2 sgn() const;
	double2 swapped() const               { double2 h = *this; h.Swap(); return h; }
	
	double2(double *d2)                   { value = _mm_loadu_pd(d2); }
	double2(double h, double l)           { value = _mm_set_pd(h, l); }
	double2(double lh)                    { value = _mm_set1_pd(lh); }
	double2(__m128d v)                    { value = v; }
	double2()                             {}
};

double2 double2::sgn() const
{
    __m128d zero = _mm_setzero_pd();
    return _mm_or_pd(_mm_and_pd(_mm_cmpgt_pd(value, zero), _mm_set1_pd(1.0f)),
                     _mm_and_pd(_mm_cmplt_pd(value, zero), _mm_set1_pd(-1.0f)));
}

inline
double Distance(const double2& a, const double2& b)
{
	double2 c = a - b;
	c *= c;
	return sqrt(c.GetL() + c.GetH());
}

#define N 10000000
/*
x*A + x*x*B + x*x*x*C

x * (A + x*(B + x*C))
*/
CONSOLE_APP_MAIN
{
	double2 x(1, 2);
	RDUMP(x);
	RDUMP(x.GetL());
	x.Swap();
	RDUMP(x);

	RDUMP(double2(123, -123).swapped());
	RDUMP(double2(-23, 0).sgn());
	RDUMP(double2(123, -123).abs());
	RDUMP(double2(-23, 0).abs());
	RDUMP(double2(-23).abs());
	return;
	
	
	Vector<double2> a;
	Vector<double2> b;
	Vector<double> distance;

	Vector<Pointf> pa;
	Vector<Pointf> pb;
	
	double h = hypot(2, 4);
	
	for(int i = 0; i < N; i++) {
		Pointf p1(Randomf(), Randomf());
		Pointf p2(Randomf(), Randomf());
		double d = Randomf();
		a.Add(double2(p1.x, p1.y));
		b.Add(double2(p2.x, p2.y));
		distance.Add(d);
		pa.Add(p1);
		pb.Add(p2);
	}
	
	{
		RTIMING("SSE");
		for(int i = 0; i < a.GetCount(); i++)
			a[i] = (a[i] - b[i]) / distance[i];
	}
	
	{
		RTIMING("FP");
		for(int i = 0; i < a.GetCount(); i++)
			pa[i] = (pa[i] - pb[i]) / distance[i];
	}

}
