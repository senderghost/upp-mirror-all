#include "fast_math.h"

namespace e1 {

double exp_tab_h[EXP_COUNT_H + 1], exp_tab_l[EXP_COUNT_L + 1];

INITBLOCK {
	for(int i = 0; i <= EXP_COUNT_H; i++)
		exp_tab_h[i] = exp2((double)i / EXP_COUNT_H);
	for(int i = 0; i <= EXP_COUNT_L; i++)
		exp_tab_l[i] = exp2((double)i / (EXP_COUNT_H * EXP_COUNT_L));
}

};