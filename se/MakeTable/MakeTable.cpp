#include <Core/Core.h>

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
static double fast_exp2(double x) {
	int exponent = (int)(x + 1);
	
	double f = EXPTAB20 * (exponent - x);
	int ti = (int)f;
	
	union { uint64 raw; double dbl; } r;
	r.raw = uint64(exponent + 1022) << 52;
	return r.dbl * exptab20[ti] + (f - ti) * (exptab20[ti + 1] - exptab20[ti]);
}

const size_t EXPD_TABLE_SIZE = 11;


typedef unsigned long long uint64_t;

union fi {
	float f;
	unsigned int i;
};

union di {
	double d;
	uint64_t i;
};

template<size_t sbit_ = EXPD_TABLE_SIZE>
struct ExpdVar {
	enum {
		sbit = sbit_,
		s = 1UL << sbit,
		adj = (1UL << (sbit + 10)) - (1UL << sbit)
	};
	// A = 1, B = 1, C = 1/2, D = 1/6
	double C1[2]; // A
	double C2[2]; // D
	double C3[2]; // C/D
	uint64_t tbl[s];
	double a;
	double ra;
	ExpdVar()
		: a(s / ::log(2.0))
		, ra(1 / a)
	{
		for (int i = 0; i < 2; i++) {
#if 0
			C1[i] = 1.0;
			C2[i] = 0.16667794882310216;
			C3[i] = 2.9997969303278795;
#else
			C1[i] = 1.0;
			C2[i] = 0.16666666685227835064;
			C3[i] = 3.0000000027955394;
#endif
		}
		for (int i = 0; i < s; i++) {
			di di;
			di.d = ::pow(2.0, i * (1.0 / s));
			tbl[i] = di.i & mask64(52);
		}
	}
};


static const ExpdVar<> c;


inline unsigned int mask(int x)
{
	return (1U << x) - 1;
}

inline uint64_t mask64(int x)
{
	return (1ULL << x) - 1;
}

inline double expd(double x)
{
	if (x <= -708.39641853226408) return 0;
	if (x >= 709.78271289338397) return std::numeric_limits<double>::infinity();

	const double _b = double(uint64_t(3) << 51);
	__m128d b = _mm_load_sd(&_b);
	__m128d xx = _mm_load_sd(&x);
	__m128d d = _mm_add_sd(_mm_mul_sd(xx, _mm_load_sd(&c.a)), b);
	uint64_t di = _mm_cvtsi128_si32(_mm_castpd_si128(d));
	uint64_t iax = c.tbl[di & mask(c.sbit)];
	__m128d _t = _mm_sub_sd(_mm_mul_sd(_mm_sub_sd(d, b), _mm_load_sd(&c.ra)), xx);
	uint64_t u = ((di + c.adj) >> c.sbit) << 52;
	double t;
	_mm_store_sd(&t, _t);
	double y = (c.C3[0] - t) * (t * t) * c.C2[0] - t + c.C1[0];
	double did;
	u |= iax;
	memcpy(&did, &u, sizeof(did));
	return y * did;
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
			s3 += expd(i);
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
		if(q <= 1) {
			if(err > maxerror) {
				maxerror = err;
				maxerrval = q;
			}
		}
	}
	RLOG(maxerror << "% at " << maxerrval);
}
