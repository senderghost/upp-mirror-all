#include "NNSearch.h"

String NNSearch::AsString(const Ball& b) const
{
	return String() << "Ball radius " << b.radius << ", points " << b.point.GetCount() << ", center " << AsString(b.center);
}

String NNSearch::AsString(const double *p) const
{
	String s = "[";
	for(int i = 0; i < dims; i++) {
		if(i)
			s << ", ";
		s << Format("%.1f", p[i]);
	}
	return s + "]";
}

double NNSearch::SquaredDistance(const double *a, const double *b) const
{
	double d = 0;
	for(int i = 0; i < dims; i++)
		d += sqr(a[i] - b[i]);
	return d;
}

void NNSearch::Copy(Vector<double>& t, const double *s) const
{
	t.SetCount(dims);
	for(int i = 0; i < dims; i++)
		t[i] = s[i];
}

void NNSearch::Copy(Buffer<double>& t, const double *s) const
{
	t.Alloc(dims);
	for(int i = 0; i < dims; i++)
		t[i] = s[i];
}

double *NNSearch::Sub(double *t, const double *s) const
{
	for(int i = 0; i < dims; i++)
		t[i] -= s[i];
	return t;
}

double *NNSearch::Add(double *t, const double *s) const
{
	for(int i = 0; i < dims; i++)
		t[i] += s[i];
	return t;
}

double *NNSearch::Mul(double *t, double a) const
{
	for(int i = 0; i < dims; i++)
		t[i] *= a;
	return t;
}

void NNSearch::Unit(double *v) const
{
	double l = 0;
	for(int i = 0; i < dims; i++)
		l += sqr(v[i]);
	l = sqrt(l);
	for(int i = 0; i < dims; i++)
		v[i] /= l;
}

double NNSearch::Scalar(const double *a, const double *b) const
{
	double r = 0;
	for(int i = 0; i < dims; i++)
		r += a[i] * b[i];
	return r;
}

double NNSearch::Length(const double *s) const
{
	double r = 0;
	for(int i = 0; i < dims; i++)
		r += sqr(s[i]);
	return sqrt(r);
}
