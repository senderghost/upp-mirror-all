#include "fast_math.h"

namespace e3 {

uint64 tab_h[COUNT_H];

INITBLOCK {
	for(int i = 0; i < COUNT_H; i++)
		tab_h[i] = dbl_to_raw(::exp2((double)i / COUNT_H)) - (1023ull << MANTISSA_BITS);
}

}
