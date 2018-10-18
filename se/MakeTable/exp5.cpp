#include "fast_math.h"

namespace e5 {

uint64 tab_h[COUNT_H];
double tab_l[COUNT_L];

INITBLOCK {
	for(int i = 0; i < COUNT_H; i++)
		tab_h[i] = dbl_to_raw(::exp2((double)i / COUNT_H)) - (1023ull << MANTISSA_BITS);
	for(int i = 0; i < COUNT_L; i++)
		tab_l[i] = ::exp2m1((double)i / (COUNT_H * COUNT_L));
}

};