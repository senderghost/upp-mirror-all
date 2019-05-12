#include "SearchPoints.h"

String SearchPoints::AsString(const Ball& b) const
{
	return String() << "Ball radius " << b.radius << ", points " << b.point.GetCount() << ", center " << AsString(b.center);
}

String SearchPoints::AsString(const double *p) const
{
	String s = "[";
	for(int i = 0; i < dims; i++) {
		if(i)
			s << ", ";
		s << Format("%.1f", p[i]);
	}
	return s + "]";
}

double SearchPoints::SquaredDistance(const double *a, const double *b) const
{
	double d = 0;
	for(int i = 0; i < dims; i++)
		d += sqr(a[i] - b[i]);
	return d;
}

void SearchPoints::Copy(Vector<double>& t, const double *s) const
{
	t.SetCount(dims);
	for(int i = 0; i < dims; i++)
		t[i] = s[i];
}

void SearchPoints::Copy(Buffer<double>& t, const double *s) const
{
	t.Alloc(dims);
	for(int i = 0; i < dims; i++)
		t[i] = s[i];
}

double *SearchPoints::Sub(double *t, const double *s) const
{
	for(int i = 0; i < dims; i++)
		t[i] -= s[i];
	return t;
}

double *SearchPoints::Add(double *t, const double *s) const
{
	for(int i = 0; i < dims; i++)
		t[i] += s[i];
	return t;
}

double *SearchPoints::Mul(double *t, double a) const
{
	for(int i = 0; i < dims; i++)
		t[i] *= a;
	return t;
}

void SearchPoints::Unit(double *v) const
{
	double l = 0;
	for(int i = 0; i < dims; i++)
		l += sqr(v[i]);
	l = sqrt(l);
	for(int i = 0; i < dims; i++)
		v[i] /= l;
}

double SearchPoints::Scalar(const double *a, const double *b) const
{
	double r = 0;
	for(int i = 0; i < dims; i++)
		r += a[i] * b[i];
	return r;
}

double SearchPoints::Length(const double *s) const
{
	double r = 0;
	for(int i = 0; i < dims; i++)
		r += sqr(s[i]);
	return sqrt(r);
}

void SearchPoints::DumpCounters()
{
	RDUMP(distance_tests);
	RDUMP(excluded_points);
}
