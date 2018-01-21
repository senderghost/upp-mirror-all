namespace e1 {

enum {
	EXP_BITS_H = 11,
	EXP_BITS_L = 11,

	EXP_COUNT_H = (1 << EXP_BITS_H),
	EXP_MASK_H = EXP_COUNT_H - 1,
	EXP_COUNT_L = (1 << EXP_BITS_L),
	EXP_MASK_L = EXP_COUNT_L - 1,
};

extern double exp_tab_h[EXP_COUNT_H + 1], exp_tab_l[EXP_COUNT_L + 1];

force_inline double exp2(double arg) {
	const double EXP_LSTEP = 0.000000165259179674138; // H:11
	if(fabs(arg) < 700) {
		arg += IEEE_EXPONENT_ZERO + 1; // 44 ms
		int64 exponent = (int64)arg;
		double f = (1 << (EXP_BITS_H + EXP_BITS_L)) * (arg - exponent); // 69 ms
		dword ii = (dword)f;
		double fr = exp_tab_h[ii >> EXP_BITS_L] * exp_tab_l[ii & EXP_MASK_L]; // 132 ms
		double m = 1 + (f - (int)f) * EXP_LSTEP; // 230 ms
		return exp2i(exponent) * fr * m; // 240ms
	}
	return 0;
}


force_inline double exp(double arg)
{
	return exp2(1.44269504088896 * arg);
}

};