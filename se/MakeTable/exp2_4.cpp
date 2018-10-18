#include "fast_math.h"

namespace e4 {

double exp_tab_h[EXP_COUNT_H];

INITBLOCK {
	for(int i = 0; i < EXP_COUNT_H; i++)
		exp_tab_h[i] = exp2((double)i / EXP_COUNT_H);
}

};