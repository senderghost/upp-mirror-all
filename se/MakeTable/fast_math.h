#ifndef _MakeTable_fast_math_h_
#define _MakeTable_fast_math_h_

#include <Core/Core.h>

#include "emmintrin.h"

using namespace Upp;

force_inline double raw_to_dbl(uint64 val)
{
	return _mm_cvtsd_f64( _mm_castsi128_pd ( _mm_cvtsi64_si128 ( val )));
}

const int    MANTISSA_BITS = 52;
const uint64 DBL_SGNEXP_MASK = 0xfffull << MANTISSA_BITS;
const uint64 DBL_ONE_BIT = (1ull << MANTISSA_BITS);

force_inline uint64 dbl_to_raw(double val)
{
	union {
		double val;
		uint64 raw;
	} h;
	h.val = val;
	return h.raw;
//	return _mm_cvtsi128_si32(_mm_castpd_si128( _mm_load_sd(&val)));
}

force_inline
double exp2i(int64 exponent)
{
	return raw_to_dbl(uint64(exponent) << 52);
}

const int IEEE_EXPONENT_ZERO = 1022;


inline
double exp2m1(double h)
{
	return expm1(log(2) * h);
}

#include "exp2_1.h"
#include "exp2_2.h"
#include "exp2_3.h"
#include "exp2_4.h"
#include "expd.h"
#include "exp5.h"

#include "Benchmark.h"

#endif
