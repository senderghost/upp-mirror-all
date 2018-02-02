#ifndef _MakeTable_exp2_2_h_
#define _MakeTable_exp2_2_h_

namespace e2 {

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
	uint64 val_h = tab_h[(h >> (MANTISSA_BITS - BITS_H)) & MASK_H];
	
	DUMP((val_h & DBL_SGNEXP_MASK) >> MANTISSA_BITS);


//	double r = REMK * (double)(h & REMAINDER_MASK);
	
	double r = REMK * (h & REMAINDER_MASK);
	
	
	double e = raw_to_dbl((h & DBL_SGNEXP_MASK) + val_h);
	DUMP(e);
	DUMP(tab_l[(h >> (MANTISSA_BITS - BITS_H - BITS_L) & MASK_L)]);
	
	double val_l = tab_l[(h >> (MANTISSA_BITS - BITS_H - BITS_L) & MASK_L)];
	
	
	e = e + e * val_l;
	DUMP(e);
	
	DUMP(::exp2(r));
	DUMP(::exp2m1((double)(h & REMAINDER_MASK) / COUNT_H / COUNT_L));
	DUMP(r);
	DUMP(r + 0.5 * r*r + r*r*r / 6);
	DUMP(r + 0.5 * r*r + r*r*r / 6 + r*r*r*r / 24);

	DUMP(e + e * r);
	DUMP(e + e * (r + 0.5 * r*r + r*r*r / 6));
	DUMP(e + e * (r + 0.5 * r*r + r*r*r / 6 + r*r*r*r / 24));

	e += e * r;
//	e += e * r * (1 + 0.5 * r * (1 + 0.333333333333333333 * r));
	DUMP(e);

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
