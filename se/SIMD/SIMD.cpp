#include <Core/Core.h>

using namespace Upp;

struct m128 {
	union {
		__m128i m128i;
		__m128d m128d;
		__m128  m128s;
		int8    i8[16];
		int16   i16[8];
		int     i32[4];
		int64   i64[2];
		float   f[4];
		double  d[2];
	};
	
	m128& Zero()           { m128i = _mm_setzero_si128(); return *this; }
	m128& Load(void *ptr)  { m128i = _mm_loadu_si128((__m128i *)ptr); return *this; }
	void  Store(void *ptr) { _mm_storeu_si128((__m128i *)ptr, m128i); }
};

struct m128f : m128 {
	m128f()                      {}
	m128f(const m128& x)         { m128s = x.m128s; }
	m128f(const __m128 x)        { m128s = x; }
	m128f(void *ptr)             { Load(ptr); }
	m128f(float f)               { m128s = _mm_set_ss(f); }
	m128f(float a, float b, float c, float d) { m128s = _mm_set_ps(a, b, c, d); }

	m128f(int i) : m128f((float)i)    {}
	m128f(double f) : m128f((float)f) {}

	static m128f   All(float f)  { m128f x; x.m128s = _mm_set1_ps(f); return x; }
};

force_inline m128f  operator+(m128f a, m128f b)   { return _mm_add_ps(a.m128s, b.m128s); }
force_inline m128f& operator+=(m128f& a, m128f b) { return a = a + b; }
force_inline m128f  operator-(m128f a, m128f b)   { return _mm_sub_ps(a.m128s, b.m128s); }
force_inline m128f& operator-=(m128f& a, m128f b) { return a = a - b; }
force_inline m128f  operator*(m128f a, m128f b)   { return _mm_mul_ps(a.m128s, b.m128s); }
force_inline m128f& operator*=(m128f& a, m128f b) { return a = a * b; }
force_inline m128f  operator/(m128f a, m128f b)   { return _mm_div_ps(a.m128s, b.m128s); }
force_inline m128f& operator/=(m128f& a, m128f b) { return a = a + b; }


struct m128f;
struct m128d;
struct m128i;
struct m128i16;
struct m128i8;

struct m128i8 {
	m128i16 UnpackL() { 
	m128i16 UnpackH() { 
}

	auto do_line = [&](int ty, __m128 *b, __m128 *div) {
		memset(b, 0, tsz.cx * sizeof(__m128));
		memset(div, 0, tsz.cx * sizeof(__m128));
		m128f v1 = m128f::All(1);
		int yy = ny * ty;
		for(int yi = 0; yi < ny; yi++) {
			int y = yy + yi;
			if(y < ssz.cy) {
				const RGBA *s = img[yy + yi];
				const RGBA *e = s + scx0;
				const RGBA *e2 = s + ssz.cx;
				m128f *t = b;
				m128f *d = div;
				while(s < e) {
					m128f px = 0;
					m128f dv = 0;
					for(int n = nx; n--;) {
						px += LoadRGBAF(s++);
						dv += v1;
					}
					*t++ = px;
					*d++ = dv;
				}
				__m128f px = 0;
				__m128f dv = 0;
				while(s < e2) {
					px += LoadRGBAF(s++);
					dv += m128f::all(1);
				}
				*t++ = px;
				*d++ = dv;
			}
		}
		__m128 *s = b;
		__m128 *d = div;
		RGBA *t = ~ib + ty * tsz.cx;
		RGBA *e = t + tsz.cx;
		while(t < e)
			StoreRGBAF(t++, *s++ / *d++);
	};

force_inline
m128i16 LoadRGBA2(const RGBA& c)
{
	return ((m128i8)m128i32(0, 0, *(dword *)&c, *(dword *)&c)).UnpackL();
}


/*
force_inline
m128i16 AlphaBlendSSE2(m128i16 t, m128i16 s, m128i16 alpha)
{
	return s + (t * alpha >> 8); 
}

force_inline
m128i16 Mul8(m128i16 x, int alpha)
{
	return x * alpha >> 8;
}

force_inline
m128i16 MakeAlpha(m128i16 x)
{
	x = BroadcastAlpha(x);
	x = m128i16::All(256) - (m128i16(128, 129, 129, 129, 128, 129, 129, 129) * x >> 7);
	return x;
}

force_inline
__m128i LoadRGBA2(const RGBA& c)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, *(dword *)&c, *(dword *)&c), _mm_setzero_si128());
}


*/

String AsString(const m128& x)
{
	return Format("%d %d %d %d", x.i32[0], x.i32[1], x.i32[2], x.i32[3]);
}

float x[256];

CONSOLE_APP_MAIN
{
	for(int i = 0; i < 256; i++)
		x[i] = (float)i;
	
	for(int i = 0; i < 256; i += 4) {
		(0 - m128f(x + i) + m128f::All(1) + 35.2).Store(x + i);
	}
	__BREAK__;
}
