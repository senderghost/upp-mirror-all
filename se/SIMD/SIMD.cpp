#include <Core/Core.h>

using namespace Upp;

struct f32x4 {
	__m128 data;

	void   Load(void *ptr)       { data = _mm_loadu_ps((float *)ptr); }
	void   Load64(void *ptr)     { data = _mm_castpd_ps(_mm_load_sd((double *)ptr)); }
	void   Load32(void *ptr)     { data = _mm_load_ss((float *)ptr); }

	void   Store(void *ptr)      { _mm_storeu_ps((float *)ptr, data); }
	void   Store64(void *ptr)    { _mm_store_sd((double *)ptr, _mm_castps_pd(data)); }
	void   Store32(void *ptr)    { _mm_store_ss((float *)ptr, data); }
	
	f32x4()                      {}
	f32x4(void *ptr)             { Load(ptr); }
	f32x4(__m128 d)              { data = d; }
	f32x4(float f)               { data = _mm_set_ss(f); }
	f32x4(float a, float b, float c, float d) { data = _mm_set_ps(a, b, c, d); }

	f32x4(int i) : f32x4((float)i)    {}
	f32x4(double f) : f32x4((float)f) {}

	static f32x4   all(float f)  { f32x4 x; x.data = _mm_set1_ps(f); return x; }
	static f32x4   all(double f) { f32x4 x; x.data = _mm_set1_ps((float)f); return x; }
};

force_inline f32x4  operator+(f32x4 a, f32x4 b)   { return _mm_add_ps(a.data, b.data); }
force_inline f32x4& operator+=(f32x4& a, f32x4 b) { return a = a + b; }
force_inline f32x4  operator-(f32x4 a, f32x4 b)   { return _mm_sub_ps(a.data, b.data); }
force_inline f32x4& operator-=(f32x4& a, f32x4 b) { return a = a - b; }
force_inline f32x4  operator*(f32x4 a, f32x4 b)   { return _mm_mul_ps(a.data, b.data); }
force_inline f32x4& operator*=(f32x4& a, f32x4 b) { return a = a * b; }
force_inline f32x4  operator/(f32x4 a, f32x4 b)   { return _mm_div_ps(a.data, b.data); }
force_inline f32x4& operator/=(f32x4& a, f32x4 b) { return a = a + b; }

force_inline f32x4 min(f32x4 a, f32x4 b)          { return _mm_min_ps(a.data, b.data); }
force_inline f32x4 max(f32x4 a, f32x4 b)          { return _mm_max_ps(a.data, b.data); }

#define _MM_BCAST(a)                              _MM_SHUFFLE(a,a,a,a)

force_inline f32x4 Broadcast0(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(0)); }
force_inline f32x4 Broadcast1(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(1)); }
force_inline f32x4 Broadcast2(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(2)); }
force_inline f32x4 Broadcast3(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(3)); }

struct i16x8 { // 8xint16
	__m128i data;

	void   Load(void *ptr)       { data = _mm_loadu_si128((__m128i *)ptr); }
	void   Load64(void *ptr)     { data = _mm_castpd_si128(_mm_load_sd((double *)ptr)); }
	void   Load32(void *ptr)     { data = _mm_castps_si128(_mm_load_ss((float *)ptr)); }

	void   Store(void *ptr)      { _mm_storeu_si128((__m128i *)ptr, data); }
	void   Store64(void *ptr)    { _mm_store_sd((double *)ptr, _mm_castsi128_pd(data)); }
	void   Store32(void *ptr)    { _mm_store_ss((float *)ptr, _mm_castsi128_ps(data)); }
	
	i16x8()                      {}
	i16x8(void *ptr)             { Load(ptr); }
	i16x8(__m128i d)             { data = d; }
	i16x8(int v)                 { data = _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, v); }
	i16x8(int a, int b, int c, int d, int e, int f, int g, int h)  { data = _mm_set_epi16(a, b, c, d, e, f, g, h); }

	static i16x8   all(int v)    { i16x8 x; x.data = _mm_set1_epi16(v); return x; }
};

force_inline i16x8  operator+(i16x8 a, i16x8 b)    { return _mm_add_epi16(a.data, b.data); }
force_inline i16x8& operator+=(i16x8& a, i16x8 b)  { return a = a + b; }
force_inline i16x8  operator-(i16x8 a, i16x8 b)    { return _mm_sub_epi16(a.data, b.data); }
force_inline i16x8& operator-=(i16x8& a, i16x8 b)  { return a = a - b; }
force_inline i16x8  operator*(i16x8 a, i16x8 b)    { return _mm_mullo_epi16(a.data, b.data); }
force_inline i16x8& operator*=(i16x8& a, i16x8 b)  { return a = a * b; }

force_inline i16x8  operator&(i16x8 a, i16x8 b)    { return _mm_and_si128(a.data, b.data); }
force_inline i16x8& operator&=(i16x8& a, i16x8 b)  { return a = a & b; }
force_inline i16x8  operator|(i16x8 a, i16x8 b)    { return _mm_or_si128(a.data, b.data); }
force_inline i16x8& operator|=(i16x8& a, i16x8 b)  { return a = a | b; }
force_inline i16x8  operator^(i16x8 a, i16x8 b)    { return _mm_xor_si128(a.data, b.data); }
force_inline i16x8& operator^=(i16x8& a, i16x8 b)  { return a = a ^ b; }
force_inline i16x8  operator~(i16x8 a)             { return _mm_xor_si128(a.data, i16x8::all(0xffff).data); }

force_inline i16x8  operator>>(i16x8 a, int b)     { return _mm_srli_epi16(a.data, b); }
force_inline i16x8& operator>>=(i16x8& a, int b)   { return a = a >> b; }
force_inline i16x8  operator<<(i16x8 a, int b)     { return _mm_slli_epi16(a.data, b); }
force_inline i16x8& operator<<=(i16x8& a, int b)   { return a = a << b; }

struct i32x4 : i16x8 { // 4xint32
	i32x4()                      {}
	i32x4(void *ptr)             { Load(ptr); }
	i32x4(__m128i d)             { data = d; }
	i32x4(int v)                 { data = _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, v); }
	i32x4(int a, int b, int c, int d)  { data = _mm_set_epi32(a, b, c, d); }

	static i32x4   all(int v)    { i32x4 x; x.data = _mm_set1_epi32(v); return x; }
};

force_inline i32x4  operator+(i32x4 a, i32x4 b)   { return _mm_add_epi32(a.data, b.data); }
force_inline i32x4& operator+=(i32x4& a, i32x4 b) { return a = a + b; }
force_inline i32x4  operator-(i32x4 a, i32x4 b)   { return _mm_sub_epi32(a.data, b.data); }
force_inline i32x4& operator-=(i32x4& a, i32x4 b) { return a = a - b; }

force_inline i32x4  operator&(i32x4 a, i32x4 b)   { return _mm_and_si128(a.data, b.data); }
force_inline i32x4& operator&=(i32x4& a, i32x4 b) { return a = a & b; }
force_inline i32x4  operator|(i32x4 a, i32x4 b)   { return _mm_or_si128(a.data, b.data); }
force_inline i32x4& operator|=(i32x4& a, i32x4 b) { return a = a | b; }
force_inline i32x4  operator^(i32x4 a, i32x4 b)   { return _mm_xor_si128(a.data, b.data); }
force_inline i32x4& operator^=(i32x4& a, i32x4 b) { return a = a ^ b; }
force_inline i32x4  operator~(i32x4 a)            { return _mm_xor_si128(a.data, i16x8::all(0xffffffff).data); }

force_inline i32x4  operator>>(i32x4 a, int b)    { return _mm_srli_epi32(a.data, b); }
force_inline i32x4& operator>>=(i32x4& a, int b)  { return a = a >> b; }
force_inline i32x4  operator<<(i32x4 a, int b)    { return _mm_slli_epi32(a.data, b); }
force_inline i32x4& operator<<=(i32x4& a, int b)  { return a = a << b; }

struct i8x16 : i16x8 { // 16xint8
	i8x16()                      {}
	i8x16(void *ptr)             { Load(ptr); }
	i8x16(__m128i d)             { data = d; }
	i8x16(int v)                 { data = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, v); }

	static i8x16   all(int v)    { i8x16 x; x.data = _mm_set1_epi8(v); return x; }
};

force_inline i8x16  operator+(i8x16 a, i8x16 b)   { return _mm_add_epi8(a.data, b.data); }
force_inline i8x16& operator+=(i8x16& a, i8x16 b) { return a = a + b; }
force_inline i8x16  operator-(i8x16 a, i8x16 b)   { return _mm_sub_epi8(a.data, b.data); }
force_inline i8x16& operator-=(i8x16& a, i8x16 b) { return a = a - b; }

force_inline i8x16  operator&(i8x16 a, i8x16 b)   { return _mm_and_si128(a.data, b.data); }
force_inline i8x16& operator&=(i8x16& a, i8x16 b) { return a = a & b; }
force_inline i8x16  operator|(i8x16 a, i8x16 b)   { return _mm_or_si128(a.data, b.data); }
force_inline i8x16& operator|=(i8x16& a, i8x16 b) { return a = a | b; }
force_inline i8x16  operator^(i8x16 a, i8x16 b)   { return _mm_xor_si128(a.data, b.data); }
force_inline i8x16& operator^=(i8x16& a, i8x16 b) { return a = a ^ b; }
force_inline i8x16  operator~(i8x16 a)            { return _mm_xor_si128(a.data, i16x8::all(0xff).data); }

f32x4 ToFloat(i32x4 a)                            { return _mm_cvtepi32_ps(a.data); }
i32x4 Truncate(f32x4 a)                           { return _mm_cvttps_epi32(a.data); }
i32x4 Round(f32x4 a)                              { return _mm_cvtps_epi32(a.data); }

i16x8 Unpack8L(i8x16 a)                           { return _mm_unpacklo_epi8(a.data, _mm_setzero_si128()); }
i16x8 Unpack8H(i8x16 a)                           { return _mm_unpackhi_epi8(a.data, _mm_setzero_si128()); }
i32x4 Unpack16L(i16x8 a)                          { return _mm_unpacklo_epi16(a.data, _mm_setzero_si128()); }
i32x4 Unpack16H(i16x8 a)                          { return _mm_unpackhi_epi16(a.data, _mm_setzero_si128()); }

i8x16 Pack16(i16x8 l, i16x8 h)                    { return _mm_packus_epi16(l.data, h.data); }

i16x8 BroadcastLH0(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(0)), _MM_BCAST(0)); }
i16x8 BroadcastLH1(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(1)), _MM_BCAST(1)); }
i16x8 BroadcastLH2(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(2)), _MM_BCAST(2)); }
i16x8 BroadcastLH3(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(3)), _MM_BCAST(3)); }

#if 0
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

#endif

float x[256];
f32x4 global;

int16 y[256];
i16x8 yg;

String AsString(const f32x4& x)
{
	float *f = (float *)&x;
	return Format("%f %f %f %f", f[3], f[2], f[1], f[0]);
}

String AsString(const i32x4& x)
{
	int *f = (int *)&x;
	return Format("%d %d %d %d", f[3], f[2], f[1], f[0]);
}

String AsString(const i16x8& x)
{
	int16 *f = (int16 *)&x;
	return Format("%d %d %d %d  %d %d %d %d", f[7], f[6], f[5], f[4], f[3], f[2], f[1], f[0]);
}

String AsString(const i8x16& x)
{
	int8 *f = (int8 *)&x;
	return Format("%d %d %d %d . %d %d %d %d . %d %d %d %d . %d %d %d %d",
	              f[15], f[14], f[13], f[12], f[11], f[10], f[9], f[8],
	              f[7], f[6], f[5], f[4], f[3], f[2], f[1], f[0]);
}


CONSOLE_APP_MAIN
{
	for(int i = 0; i < 256; i++) {
		x[i] = (float)i;
		y[i] = i;
	}
	
	{
		f32x4 x(1, 2, 3, 4);
		DDUMP(Broadcast0(x));
		DDUMP(Broadcast1(x));
		DDUMP(Broadcast2(x));
		DDUMP(Broadcast3(x));
	}

	{
		i16x8 x(1, 2, 3, 4, 5, 6, 7, 8);
		DDUMP(BroadcastLH0(x));
		DDUMP(BroadcastLH1(x));
		DDUMP(BroadcastLH2(x));
		DDUMP(BroadcastLH3(x));
	}

	{
		f32x4 s = 0;
		for(int i = 0; i < 256; i += 4) {
			s += f32x4(x + i);
			DDUMP(s);
		}
		global = s;
		DDUMP(s);
	}

	{
		i16x8 s = 0;
		for(int i = 0; i < 256; i += 4) {
			s += i16x8(y + i);
			DDUMP(s);
		}
		yg = s;
	}
}
