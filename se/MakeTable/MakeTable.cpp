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

static double exp_tab_h[EXP_COUNT_H + 1], exp_tab_l[EXP_COUNT_L + 1];

INITBLOCK {
	for(int i = 0; i <= EXP_COUNT_H; i++)
		exp_tab_h[i] = exp2((double)i / EXP_COUNT_H);
	for(int i = 0; i <= EXP_COUNT_L; i++)
		exp_tab_l[i] = exp2((double)i / (EXP_COUNT_H * EXP_COUNT_L));
}

force_inline double fast_exp2(double arg) {
	const double EXP_LSTEP = 0.000000165259179674138; // H:11
//	const double EXP_LSTEP = 0.00000066103688212138; // H:10
	arg += IEEE_EXPONENT_ZERO + 1;
	if(arg < 0)
		return 0;
	if(arg > 2046)
		return HUGE_VAL;
	int exponent = (int)arg;
	double f = (1 << (EXP_BITS_H + EXP_BITS_L)) * (arg - exponent);
	int ii = (int)f;
	f -= ii;
	return exp2i(exponent) * exp_tab_h[ii >> EXP_BITS_L] * exp_tab_l[ii & EXP_MASK_L] * (1 + f * EXP_LSTEP);
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
