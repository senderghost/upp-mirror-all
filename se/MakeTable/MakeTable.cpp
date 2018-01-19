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
double fast_exp2_2(double x) {
	int exponent = (int)(x + 1);
	
	double f = EXPTAB20 * (exponent - x);
	int ti = (int)f;
	
	double val = exptab20[ti];
	return val * (1 + (f - ti) * (0.999999338963555 - 1)) * exp2i(exponent);
//	return exp2i(exponent) * (val + (f - ti) * (0.999999338963555 * val - val));
	
//	return exp2i(exponent) * (exptab20[ti] + (f - ti) * (exptab20[ti + 1] - exptab20[ti]));
}

/*
const int EXPTAB11 = (1 << 11);
static double exptab11[EXPTAB11 + 1], exptabl[EXPTAB11 + 1];

INITBLOCK {
	for(int i = 0; i <= EXPTAB11; i++) {
		exptab11[i] = exp2((double)i / EXPTAB11);
		exptabl[i] = exp2((double)i / sqr(EXPTAB11));
	}
}

force_inline double fast_exp2(double arg) {
	arg += IEEE_EXPONENT_ZERO + 1;
	if(arg < 0)
		return 0;
	if(arg > 2046)
		return HUGE_VAL;
	int exponent = (int)arg;
	double f = (1 << 22) * (arg - exponent);
	int ii = (int)f;
	f -= ii;
	return exp2i(exponent) * exptab11[ii >> 11] * exptabl[ii & 2047] * (1 + f * 0.000000165259179674138);
}
*/

enum {
	EXP_BITS_H = 11,
	EXP_BITS_L = 11,

	EXP_COUNT_H = (1 << EXP_BITS_H),
	EXP_MASK_H = EXP_COUNT_H - 1,
	EXP_COUNT_L = (1 << EXP_BITS_L),
	EXP_MASK_L = EXP_COUNT_L - 1,
};

double exp_tab_h[EXP_COUNT_H + 1], exp_tab_l[EXP_COUNT_L + 1];

INITBLOCK {
	for(int i = 0; i <= EXP_COUNT_H; i++)
		exp_tab_h[i] = exp2((double)i / EXP_COUNT_H);
	for(int i = 0; i <= EXP_COUNT_L; i++)
		exp_tab_l[i] = exp2((double)i / (EXP_COUNT_H * EXP_COUNT_L));
}

force_inline
double exp2i_(int64 exponent)
{
	return raw_to_dbl(uint64(exponent) << 52);
}

force_inline double fast_exp2_A(double arg) {
	const double EXP_LSTEP = 0.000000165259179674138; // H:11
	if(fabs(arg) < 700) {
		arg += IEEE_EXPONENT_ZERO + 1;
		int64 exponent = (int64)arg;
		double f = (1 << (EXP_BITS_H + EXP_BITS_L)) * (arg - exponent);
		dword ii = (dword)f;
		return exp2i_(exponent) * exp_tab_h[ii >> EXP_BITS_L] * exp_tab_l[ii & EXP_MASK_L]
		       * (1 + (f - (int)f) * EXP_LSTEP);
	}
	return 0;
}

// exp: 153ms total

// table fetch: 30ms
// exponent->double: 10ms
// double mul: 3ms
// double add: 5ms


force_inline double fast_exp2_B(double arg) {
	const double EXP_LSTEP = 0.000000165259179674138; // H:11
	if(fabs(arg) < 700) {
		arg += IEEE_EXPONENT_ZERO + 1; // 44 ms
		int64 exponent = (int64)arg;
		double f = (1 << (EXP_BITS_H + EXP_BITS_L)) * (arg - exponent); // 69 ms
		dword ii = (dword)f;
		double fr = exp_tab_h[ii >> EXP_BITS_L] * exp_tab_l[ii & EXP_MASK_L]; // 132 ms
		double m = 1 + (f - (int)f) * EXP_LSTEP; // 230 ms
		return exp2i_(exponent) * fr * m; // 240ms
	}
	return 0;
}


force_inline double fast_exp2(double arg) {
	const double EXP_LSTEP = 0.000000165259179674138; // H:11
	if(fabs(arg) < 700) {
		arg += IEEE_EXPONENT_ZERO + 1;
		int64 exponent = (int64)arg;
		double f = (1 << (EXP_BITS_H + EXP_BITS_L)) * (arg - exponent);
		dword ii = (dword)f;
		double fr = exp2i_(exponent) * exp_tab_h[ii >> EXP_BITS_L] * exp_tab_l[ii & EXP_MASK_L];
		double m = (f - (int)f) * EXP_LSTEP;
		return fr + fr * m;
	}
	return 0;
}


force_inline double fast_exp(double arg)
{
	return fast_exp2(1.44269504088896 * arg);
}





void Test(double arg)
{
	LOG("=============");
	DUMP(arg);
	DUMP(exp2(arg));
	DUMP(fast_exp2(arg));
	
	DUMP(exp2i((int)arg));
	DUMP(exp2i(1 + (int)arg) * exp2(arg - (int)arg));
	DUMP(exp2(arg - (int)arg));

	double f = (1 << 22) * (arg - (int)arg);
	
	int ii = (int)f;
#if 0
	DUMP(exptab11[ii >> 11]);
	DUMP(exptabl[ii & 2047]);
	DUMP(exptab11[ii & 2047]);
	DUMP(exptab11[ii >> 11] * exptabl[ii & 2047]);
	DUMP(exptab11[ii >> 11] * exptab11[ii & 2047]);
	DUMP(exp2i((int)arg + 1) * exptab11[ii >> 11] * exptabl[ii & 2047]);
	
	f -= ii;
	double g = exptab11[ii >> 11] * exptabl[ii & 2047];
	DUMP(g);
	DUMP(f);
	DUMP((1 - f) * g + f * 1.00000016525918 * g);
	DUMP(exp2i((int)arg + 1) * ((1 - f) * g + f * 1.00000016525918 * g));

	DUMP(exp2i((int)arg + 1) * g * (1 + f * 0.00000016525918));
#endif
	DUMP(fast_exp2(arg));
	
	DUMP(exp(arg));
	DUMP(fast_exp(arg));
}

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	int i = 0;
	
	
	
	
	
	DUMP(exp2(208));
	DUMP(fast_exp2(208));
	DUMP(fast_exp2(-4.567));
	
	DUMP(exp2(sqr((double)i / EXP_COUNT_H)));

	DUMP((double)1 / 0xffffffff);
	
	DUMP(exp_tab_h[10] / exp_tab_h[9]);
	DUMP(exp2(1.0 / EXP_COUNT_H));
	DUMP(exp2(1.0 / (EXP_COUNT_H * EXP_COUNT_L)) - 1);

	DUMP(exp_tab_h[0]);

	DUMP(exp_tab_l[0]);
	DUMP(exp_tab_l[1]);
	DUMP(exp_tab_l[2047]);
	
	DUMP(exptab20[10] / exptab20[9]);
	DUMP(exptab20[20000] / exptab20[19999]);
	
	DUMP(exp2(45.0 / 2048));
	DUMP(exp_tab_h[45]);
	
	DUMP(exp2(45.0 / 2048 + 12.0 / 2048 / 2048));
	DUMP(exp_tab_h[45]);
	DUMP(exp2(12.0 / 2048 / 2048));
	DUMP(exp_tab_l[12]);
	DUMP(exp_tab_h[45] * exp_tab_l[12]);

	DUMP(exp2(45.0 / 2048 + 12.0 / 2048 / 2048) / exp2(45.0 / 2048 + 11.0 / 2048 / 2048));

	DUMP(exp2(49.0 / 2048 + 15.0 / 2048 / 2048) / exp2(49.0 / 2048 + 14.0 / 2048 / 2048));

	DUMP(log2(M_E));

	DUMP(FF(-0.33234));
//	DUMP(ff(-0.33234));
	
	double arg = 4.567;
	
	DUMP(exp2(arg));
	
	DUMP(exp2(5) * exp2(arg - 5));
	
	Test(arg);
	Test(-arg);
	Test(1.23);
	Test(34.98);
	Test(-34.98);

#ifdef _DEBUG
	return;
#endif

	Vector<double> data;
	for(int i = 0; i < 50000000; i++)
		data.Add(Randomf() * 100);
	
	double s0;
	{
		Vector<double> d = clone(data);
		{
			RTIMING("void");
			for(auto& h : d)
				h = h + 1;
		}
	}
	RDUMP(s0);

	{
		Vector<double> d = clone(data);
		{
			RTIMING("fast_exp");
			for(auto& h : d)
				h = fast_exp(h);
		}
		RDUMP(Sum(d));
	}

	{
		Vector<double> d = clone(data);
		{
			RTIMING("fast_exp_");
			for(auto& h : d)
				h = fast_exp2_(h);
		}
	}

	{
		Vector<double> d = clone(data);
		{
			RTIMING("fast_exp2");
			for(auto& h : d)
				h = fast_exp2(h);
		}
	}

	{
		Vector<double> d = clone(data);
		{
			RTIMING("exp");
			for(auto& h : d)
				h = exp(h);
		}
		RDUMP(Sum(d));
	}

	double maxerror = 0;
	double maxerrval;
	for(int qq = -10000; qq < 10000; qq++) {
		double q = qq / 9;
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

#if 0

TIMING exp            :  1.84 s  -  1.84 s  ( 1.84 s  / 1 ), min:  1.84 s , max:  1.84 s , nesting: 1 - 1
TIMING fast_exp2      : 200.00 ms - 200.00 ms (200.00 ms / 1 ), min: 200.00 ms, max: 200.00 ms, nesting: 1 - 1
TIMING fast_exp_      : 140.00 ms - 140.00 ms (140.00 ms / 1 ), min: 140.00 ms, max: 140.00 ms, nesting: 1 - 1
TIMING fast_exp       : 225.00 ms - 225.00 ms (225.00 ms / 1 ), min: 225.00 ms, max: 225.00 ms, nesting: 1 - 1
TIMING void           : 41.00 ms - 41.00 ms (41.00 ms / 1 ), min: 41.00 ms, max: 41.00 ms, nesting: 1 - 1


TIMING exp            : 163.00 ms - 163.00 ms (163.00 ms / 1 ), min: 163.00 ms, max: 163.00 ms, nesting: 1 - 1
TIMING fast_exp2      : 264.00 ms - 264.00 ms (264.00 ms / 1 ), min: 264.00 ms, max: 264.00 ms, nesting: 1 - 1
TIMING fast_exp_      : 149.00 ms - 149.00 ms (149.00 ms / 1 ), min: 149.00 ms, max: 149.00 ms, nesting: 1 - 1
TIMING fast_exp       : 277.00 ms - 277.00 ms (277.00 ms / 1 ), min: 277.00 ms, max: 277.00 ms, nesting: 1 - 1
TIMING void           : 40.00 ms - 40.00 ms (40.00 ms / 1 ), min: 40.00 ms, max: 40.00 ms, nesting: 1 - 1

#endif

