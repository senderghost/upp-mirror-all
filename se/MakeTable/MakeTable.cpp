#include "fast_math.h"

using namespace Upp;

double FF(double x)
{
	return exp(x);
}

const double TABL = -709;
const double TABH = 709;
const int    TABN = 2000;

static double table[TABN + 1];

INITBLOCK {
	for(int i = 0; i <= TABN; i++) {
		double q = (double)i / TABN * (TABH - TABL) + TABL;
		table[i] = exp2(q);
	}
}

force_inline
double fast_exp2_(double x)
{
	const double h = (double)TABN / (TABH - TABL);
	double id = h * (x - TABL);
	if(id < 0)
		return 0;
	if(id < TABN) {
		int ii = (int)id;
		return table[ii] + (id - ii) * (table[ii + 1] - table[ii]);
	}
	return HUGE_VAL;
}

const int EXPTAB20 = 16 * 65536;
static double exptab20[EXPTAB20];

INITBLOCK {
	for(int i = 0; i <= EXPTAB20; i++)
		exptab20[i] = 2 * exp2(-(double)i / EXPTAB20);
}

force_inline
double fast_exp2(double x) {
	int exponent = (int)(x + 1);
	
	double f = EXPTAB20 * (exponent - x);
	int ti = (int)f;
	
	double val = exptab20[ti];
	return val * (1 + (f - ti) * (0.999999338963555 - 1)) * exp2i(exponent);
//	return exp2i(exponent) * (val + (f - ti) * (0.999999338963555 * val - val));
	
//	return exp2i(exponent) * (exptab20[ti] + (f - ti) * (exptab20[ti + 1] - exptab20[ti]));
}

void Test(double arg)
{
	LOG("=============");
	DUMP(arg);
	DUMP(exp2(arg));
	DUMP(fast_exp2(arg));
}

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	DUMP((double)1 / 0xffffffff);
	
	DUMP(exptab20[10] / exptab20[9]);
	DUMP(exptab20[20000] / exptab20[19999]);

	DUMP(FF(-0.33234));
//	DUMP(ff(-0.33234));
	
	double arg = 4.567;
	
	DUMP(exp2(arg));
	
	DUMP(exp2(5) * exp2(arg - 5));
	
	Test(arg);
	Test(-arg);
	Test(1.23);
	Test(34.98);
	//Test(-34.98);
	
	double s0 = 0;
	{
		RTIMING("void");
		for(double i = 0; i < 100; i += 0.00001)
			s0 += i;
	}
	RDUMP(s0);

	double s1 = 0;
	{
		RTIMING("exp");
		for(double i = 0; i < 100; i += 0.00001)
			s1 += exp(i);
	}
	RDUMP(s1);

	double s3 = 0;
	{
		RTIMING("expd");
		for(double i = 0; i < 100; i += 0.00001)
			s3 += exp(i);
	}
	RDUMP(s3);

	double s2 = 0;
	{
		RTIMING("fast_exp2");
		for(double i = 0; i < 100; i += 0.00001)
			s2 += fast_exp2(i);
	}
	RDUMP(s2);
	double maxerror = 0;
	double maxerrval;
	for(double q = 0.1; q <= TABH + 10; q += 3.3) {
		double val = exp2(q);
		double fval = fast_exp2(q);
		double err = q > -705 ? 100 * abs(val - fval) / val : 0.0;
		RLOG(q << ", " << val << ", " << fval << ", " << val - fval << ", " << err << "%");
		if(err > maxerror) {
			maxerror = err;
			maxerrval = q;
		}
	}
	RLOG(maxerror << "% at " << maxerrval);
}
