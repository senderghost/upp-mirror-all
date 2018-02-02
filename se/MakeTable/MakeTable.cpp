#include "fast_math.h"

using namespace Upp;

#define CE e1

void Test(double arg)
{
	LOG("=============");
	DUMP(arg);
	
	double ee = ::exp(arg);
	RDUMP(ee);
	
	uint64 h = dbl_to_raw(arg + 1023);
	
	DUMP(arg + 1024);
	
	DUMPHEX(h);
	
	uint64 exponent = h >> 52;
	DUMP(exponent - 1023);
	DUMPHEX(DBL_SGNEXP_MASK);
	DUMPHEX(~DBL_SGNEXP_MASK);
	DUMPHEX(h & ~DBL_SGNEXP_MASK);
	h = ((h & ~DBL_SGNEXP_MASK) | DBL_ONE_BIT) << (exponent - 1023);
	DUMPHEX(h);
	DUMPHEX(h >> 52);
	DUMP(h >> 52);
	DUMP(raw_to_dbl(h & DBL_SGNEXP_MASK));
	
	RLOG("----");
	double e = e5::exp2(arg);
	RDUMP(e);
	RDUMP(exp2(arg));
	LOG(Format("ERROR: %g", abs(e - exp2(arg)) / exp2(arg)));
	return;
	

#if 0

	DUMP(CE::exp2(arg));
	
	DUMP(exp2i((int)arg));
	DUMP(exp2i(1 + (int)arg) * exp2(arg - (int)arg));
	DUMP(exp2(arg - (int)arg));

	double f = (1 << 22) * (arg - (int)arg);
	
	int ii = (int)f;
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
	DUMP(e1::exp2(arg));
	
	DUMP(exp(arg));
	DUMP(CE::exp(arg));
}

CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);

	int i = 0;
	
	Test(0.255758254242763);
	Test(1.2345678);
	Test(234.5678);
	Test(0);
	Test(0.00001);
	Test(0.78);
	Test(20.3);
	Test(50);
	Test(50.5);
	Test(-20.3);
	Test(-1025);
	Test(-1024);
	Test(-1023);
	Test(1024);
	Test(1025);

	RLOG("-------------------");
	double x = Randomf();
	
	uint64 xx = dbl_to_raw(x);
	
	RDUMPHEX(xx);
	
	RDUMP(CE::exp2(x));
	
	
	Test(1.23);
	Test(34.98);
	Test(-34.98);

#ifdef _DEBUG
	return;
#endif

	Vector<double> data;
	for(int i = 0; i < 30000000; i++)
		data.Add(Randomf() * 300 + 0.1);
	
	float a = (float)data[0];
	float b = (float)data[1];
	
	RDUMP(a * b);

	RLOG("--- Benchmarks");
//	Benchmark(data, [](double x) { return log(x); }, "std::log");
	Benchmark(data, [](double x) { return sin(x); }, "std::sin");
	Benchmark(data, [](double x) { return sinf((float)x); }, "std::sinf");
	Benchmark(data, [](double x) { return exp(x); }, "std::exp");
	Benchmark(data, [](double x) { return expf(x); }, "std::expf");
//	Benchmark(data, [](double x) { return exp2(x); }, "std::exp2");
//	Benchmark(data, e1::exp2, "e1::exp2");
	Benchmark(data, e2::exp2, "e2::exp2");

	Benchmark(data, e5::exp2, "e5::exp2");
//	Benchmark(data, e3::exp2, "e3::exp2");
//	Benchmark(data, e4::exp2, "e4::exp2");
//	Benchmark(data, expd::exp, "expd::exp");
	
	double maxerror = 0;
	double maxerrval;
	for(int qq = -10000; qq < 10000; qq++) {
		double q = qq / 9;
		double val = exp2(q);
		double fval = CE::exp2(q);
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

