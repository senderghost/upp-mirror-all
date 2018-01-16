#include <Core/Core.h>

using namespace Upp;

double FF(double x)
{
	return log(x);
}

const double TABL = 0.5;
const double TABH = 1;
const int    TABN = 2000000;

static double table[TABN + 1];

INITBLOCK {
	for(int i = 0; i <= TABN; i++) {
		double q = (double)i / TABN * (TABH - TABL) + TABL;
		table[i] = FF(q);
	}
}

force_inline
double ff(double x)
{
	const double h = (double)TABN / (TABH - TABL);
	double id = h * (x - TABL);
	if(id >= 0 && id < TABN) {
		int ii = (int)id;
		double f = id - ii;
		return (1 - f) * table[ii] + f * table[ii + 1];
	}
	return FF(x);
}

force_inline double fp_mantisa(double h)
{
	int64& x = *(int64 *)&h;
	x = (x & ~((int64)2047 << 52)) | ((int64)1022 << 52);
	return h;
}

force_inline int fp_mantisa_high(double h)
{
	dword *x = (dword *)&h;
	return int((*(int64 *)&h >> 52) & 2047) - 1022;
}

force_inline int fp_exponent(double h)
{
	return int((*(int64 *)&h >> 52) & 2047) - 1022;
}

force_inline
double fast_log0(double x) {
#if 1
	return 0.693147180559945 * fp_exponent(x) + ff(fp_mantisa(x));
#else
	double m = fp_mantisa(x) - 1;
	return 0.693147180559945 * fp_exponent(x) + m - m*m / 2 + m*m*m / 3 - m*m*m*m / 4 + m*m*m*m*m/5;
#endif
}

const int TAB20 = 16 * 65536;
static double log_table[TAB20 + 1];

INITBLOCK {
	for(int i = 0; i <= TAB20; i++)
		log_table[i] = log(0.5 * (double)i / TAB20 + 0.5);
}

force_inline
static double fast_log(double x) {
	dword *ix = (dword *)&x;
	int exponent = int((ix[1] >> 20) & 2047) - 1022;
	
	dword ti = (ix[1] & (TAB20 - 1));
	double f = 0.00000000023283064370808 * ix[0];
	
	f = (1 - f) * log_table[ti] + f * log_table[ti + 1];
	
	return 0.693147180559945 * exponent + f;
}

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	RDUMP(FF(0.33234));
	RDUMP(ff(0.33234));
	RDUMP(log(2));

	double s0 = 0;
	{
		RTIMING("placebo");
		for(double i = 0; i < 100; i += 0.00001) {
			s0 += i;;
		}
	}
	RDUMP(s0);

	double s1 = 0;
	{
		RTIMING("log");
		for(double i = 0; i < 100; i += 0.00001) {
			s1 += log(i);;
		}
	}
	RDUMP(s1);

	double s2 = 0;
	{
		RTIMING("fast_log");
		for(double i = 0; i < 100; i += 0.00001) {
			s2 += fast_log(i);;
		}
	}
	RDUMP(s2);

	double s3 = 0;
	{
		RTIMING("fast_log0");
		for(double i = 0; i < 100; i += 0.00001) {
			s2 += fast_log0(i);;
		}
	}
	RDUMP(s3);

	for(int i = 0; i < 10; i++) {
		double h = pow(1 + Randomf(), Random(100) - 10);
		RLOG("===========================");
		RDUMP(h);
		int e;
		double m = frexp(h, &e);
		RDUMP(m);
		RDUMP(e);
		
		double mm = fp_mantisa(h);
		double ee = fp_exponent(h);
		RDUMP(mm);
		RDUMP(ee);
		
		double hh = h;
		int64& x = *(int64 *)&hh;
		RDUMP(((x >> 52) & 2047) - 1022);
		x = (x & ~((int64)2047 << 52)) | ((int64)1022 << 52);
		RDUMP(hh);
		
		
		RDUMP(0.69314718 * e);
		RDUMP(log(m));
		RDUMP(log(2) * e + ff(m));
		RDUMP(log(2) * e + -0.69314718 * 2 * (1 - m));
		RDUMP(log(2) * e + (m-1)-1.4*sqr(m-1) / 2);
		RDUMP(log(h));
		RDUMP(fast_log(h));
	}
	
	double maxerror = 0;
	double maxerrval = 0;
	for(double q = 1e-100; q < 1e100; q *= 1.1) {
		double val = log(q);
		double fval = fast_log(q);
		double err = 100 * abs(val - fval) / val;
		RLOG(q << ", " << val << ", " << fval << ", " << val - fval << ", " << err << "%");
		if(err > maxerror) {
			maxerror = err;
			maxerrval = q;
		}
	}
	
	RLOG(maxerror << "% at " << maxerrval);
}
