#include <Core/Core.h>

using namespace Upp;

double FF(double x)
{
	return exp(x);
}

const double TABL = -709;
const double TABH = 709;
const int    TABN = 2000000;

static double table[TABN + 1];

INITBLOCK {
	for(int i = 0; i <= TABN; i++) {
		double q = (double)i / TABN * (TABH - TABL) + TABL;
		table[i] = FF(q);
	}
}

force_inline
double fast_exp(double x)
{
	const double h = (double)TABN / (TABH - TABL);
	double id = h * (x - TABL);
	if(id < 0)
		return 0;
	if(id < TABN) {
		int ii = (int)id;
		double f = id - ii;
		return table[ii] + f * (table[ii + 1] - table[ii]);
//		return (1 - f) * table[ii] + f * table[ii + 1];
//		return table[ii] - (id - ii) * (table[ii + 1] - table[ii]);
	}
	return HUGE_VAL;
}

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	DUMP((double)1 / 0xffffffff);

	DUMP(FF(-0.33234));
	DUMP(ff(-0.33234));

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

	double s2 = 0;
	{
		RTIMING("exp");
		for(double i = 0; i < 100; i += 0.00001)
			s2 += fast_exp(i);
	}
	RDUMP(s2);

	double maxerror = 0;
	double maxerrval;
	for(double q = TABL - 10; q <= TABH + 10; q += 3.3) {
		double val = FF(q);
		double fval = fast_exp(q);
		double err = q > -705 ? 100 * abs(val - fval) / val : 0.0;
		RLOG(q << ", " << val << ", " << fval << ", " << val - fval << ", " << err << "%");
		if(q <= 1) {
			if(err > maxerror) {
				maxerror = err;
				maxerrval = q;
			}
		}
	}
	
	RLOG(maxerror << "% at " << maxerrval);
}
