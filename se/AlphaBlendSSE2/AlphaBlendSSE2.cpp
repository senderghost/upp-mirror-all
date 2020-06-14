#include <Core/Core.h>
#include <Painter/Painter.h>

using namespace Upp;

never_inline
String AsString(__m128 x)
{
	float f[4];
	memcpy(f, &x, 16);
	return Sprintf("(%f, %f, %f, %f)", f[0], f[1], f[2], f[3]);
}

#if 1
#define DUMPS(x) RLOG(#x << " = " << AsString(x));
#else
#define DUMPS(x)
#endif

/*
						t->a = alpha = Saturate255(alpha / w);
						t->r = clamp(red / w, 0, alpha);
						t->g = clamp(green / w, 0, alpha);
						t->b = clamp(blue / w, 0, alpha);
*/

__m128 ClampRGBAF(__m128 p)
{
	__m128 alpha = _mm_shuffle_ps(p, p, _MM_SHUFFLE(3, 3, 3, 3));
	alpha = _mm_min_ps(alpha, _mm_set1_ps(255.0));
	return _mm_min_ps(p, alpha);
}

force_inline
__m128 LoadRGBAF(const RGBA *s)
{
	return _mm_cvtepi32_ps(_mm_unpacklo_epi16(_mm_unpacklo_epi8(_mm_set_epi32(0, 0, 0, *(dword *)s), _mm_setzero_si128()), _mm_setzero_si128()));
}

/*
m128f
m128d
m128b
m128w
m128i

			for(int x = 0; x < sz.cx; x++) {
				__m128 rgbaf = _mm_setzero_ps();
				__m128 w = _mm_setzero_ps();
				yd = py;
				int hasalpha = 0;
				for(int yy = 2 * ay; yy-- > 0;) {
					__m128 ky = *yd++;
					const RGBA *l = img[*yd++];
					for(int xx = 2 * ax; xx-- > 0;) {
						__m128 s = LoadRGBAF(&l[*xd++]);
						__m128 weight = __mm_set1_ps(ky * *xd++);
						rgbaf = _mm_add_ps(rgbaf, _mm_mul_ps(weight, s));
						w = _mm_add_ps(w, weight);
					}
				}
				StoreRGBAF(ClampRGBAF(_mm_div_ps(rgbaf, w)));
				t++;
			}
*/

int x = 300;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	
	__m128 a = _mm_set1_ps(x);
	DUMPS(a);
	a = ClampRGBAF(a);
	DUMPS(a);

	RGBA x;
	x.r = 134;
	x.g = 222;
	x.b = 122;
	x.a = 130;
	__m128 v = LoadRGBAF(&x);
	DUMPS(v);
	DUMPS(ClampRGBAF(v));
	return;
}
