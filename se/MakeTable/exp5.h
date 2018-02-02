#ifndef _MakeTable_exp5_2_h_
#define _MakeTable_exp5_2_h_

namespace e5 {

enum {
	BITS_H = 11,
	BITS_L = 11,
	
	COUNT_H = (1 << BITS_H),
	MASK_H = COUNT_H - 1,
	
	COUNT_L = (1 << BITS_L),
	MASK_L = COUNT_L - 1,
	
	REMAINDER_BITS = MANTISSA_BITS - BITS_H - BITS_L,
};

const uint64 REMAINDER_COUNT = (1ull << REMAINDER_BITS);
const uint64 REMAINDER_MASK = REMAINDER_COUNT - 1;

extern uint64 tab_h[COUNT_H];
extern double tab_l[COUNT_L];

const double REMK = log(2) / REMAINDER_COUNT / COUNT_H / COUNT_L;

const double MAXERROR = (1.0 - 100.0 / REMAINDER_COUNT) / COUNT_H / COUNT_L;

inline double exp2(double arg)
{
	uint64 h = dbl_to_raw(arg + 1023);
	DUMPHEX(h);
	DUMPHEX(h >> MANTISSA_BITS);
	DUMPHEX((h >> MANTISSA_BITS) - 1023);
	h = ((h & ~DBL_SGNEXP_MASK) | DBL_ONE_BIT) << ((h >> MANTISSA_BITS) - 1023);
	DUMPHEX(h);
	DUMP((h >> (MANTISSA_BITS - BITS_H)) & MASK_H);
	DUMP((h >> (MANTISSA_BITS - BITS_H - BITS_L) & MASK_L));
	DUMPHEX(REMAINDER_MASK);
	DUMPHEX(h & REMAINDER_MASK);
	
	uint64 exp = h & DBL_SGNEXP_MASK;

	double rem = REMK * (h & REMAINDER_MASK);
	h >>= REMAINDER_BITS;

	double val_l = tab_l[h & MASK_L];
	h >>= BITS_L;
	
	double e = raw_to_dbl(tab_h[h & BITS_H] + exp);
	e = e + e * val_l;
	e = e + e * rem;

	return e;
}
	
};

#if 0

e2::exp2(arg) = 2.35310506048042
exp2(arg) = 2.35310842882023

e2::exp2(arg) = 2.35310991996892
exp2(arg) = 2.35310842882023

#endif

#endif
