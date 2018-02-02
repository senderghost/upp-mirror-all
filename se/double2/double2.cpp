#include <Core/Core.h>

#include "emmintrin.h"
#include "pmmintrin.h"

using namespace Upp;

struct double2 {
	__m128d value;
	
	void SetL(double x)                   { value = _mm_loadl_pd(value, &x); }
	void SetH(double x)                   { value = _mm_loadh_pd(value, &x); }
	void SetLH(double x)                  { value = _mm_loaddup_pd(&x); }
	
	double GetL() const                   { double x; _mm_storel_pd(&x, value); return x; }
	double GetH() const                   { double x; _mm_storeh_pd(&x, value); return x; }
	
	String ToString() const               { return String() << GetL() << ", " << GetH(); }

	double2  operator+(const double2& h) const { return _mm_add_pd(value, h.value); }
	double2  operator-(const double2& h) const  { return _mm_sub_pd(value, h.value); }
	double2  operator*(const double2& h) const { return _mm_mul_pd(value, h.value); }
	double2  operator/(const double2& h) const { return _mm_div_pd(value, h.value); }

	double2  operator-() const             { return _mm_sub_pd(_mm_setzero_pd(), value); }
	
	double2& operator+=(const double2& h) { value = _mm_add_pd(value, h.value); return *this; }
	double2& operator-=(const double2& h) { value = _mm_sub_pd(value, h.value); return *this; }
	double2& operator*=(const double2& h) { value = _mm_mul_pd(value, h.value); return *this; }
	double2& operator/=(const double2& h) { value = _mm_div_pd(value, h.value); return *this; }
	
	double2 sqrt() const                  { return _mm_sqrt_pd(value); }
	
	double2(double *d2)                   { value = _mm_loadu_pd(d2); }
	double2(double l, double h)           { SetL(l); SetH(h); }
	double2(double lh)                    { SetLH(lh); }
	double2(__m128d v)                    { value = v; }
	double2()                             {}
};

CONSOLE_APP_MAIN
{
	double2 x(1, 2);
	x += 1;
	for(int i = 0; i < 10; i++)
		x *= 1.23;
	RDUMP(x);
	
	x += { 12.0, 23.1 };

	RDUMP(-x);
	
	x *= 1.23;
	RDUMP(x);
	
	x /= 2;
	RDUMP(x);
	
	RDUMP(x.sqrt());
	
	x = x * 4 - 1;
	
	RDUMP(x * 4 - 1);
}
