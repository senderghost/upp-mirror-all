namespace expd {

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
//			tbl[i] = di.i & mask64(52);
		}
	}
};


inline unsigned int mask(int x)
{
	return (1U << x) - 1;
}

inline uint64_t mask64(int x)
{
	return (1ULL << x) - 1;
}

static const ExpdVar<> c;

inline double exp(double x)
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

};

