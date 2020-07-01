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

force_inline f32x4  operator==(f32x4 a, f32x4 b)   { return _mm_cmpeq_ps(a.data, b.data); }
force_inline f32x4  operator!=(f32x4 a, f32x4 b)   { return _mm_cmpneq_ps(a.data, b.data); }
force_inline f32x4  operator<(f32x4 a, f32x4 b)    { return _mm_cmplt_ps(a.data, b.data); }
force_inline f32x4  operator>(f32x4 a, f32x4 b)    { return _mm_cmpgt_ps(a.data, b.data); }
force_inline f32x4  operator<=(f32x4 a, f32x4 b)   { return _mm_cmple_ps(a.data, b.data); }
force_inline f32x4  operator>=(f32x4 a, f32x4 b)   { return _mm_cmpge_ps(a.data, b.data); }
force_inline bool   Test(f32x4 a)                  { return _mm_movemask_ps(a.data) == 0xf; }

force_inline f32x4 min(f32x4 a, f32x4 b)          { return _mm_min_ps(a.data, b.data); }
force_inline f32x4 max(f32x4 a, f32x4 b)          { return _mm_max_ps(a.data, b.data); }

#define _MM_BCAST(a)                              _MM_SHUFFLE(a,a,a,a)

force_inline f32x4 Broadcast0(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(0)); }
force_inline f32x4 Broadcast1(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(1)); }
force_inline f32x4 Broadcast2(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(2)); }
force_inline f32x4 Broadcast3(f32x4 a)            { return _mm_shuffle_ps(a.data, a.data, _MM_BCAST(3)); }

struct i16x8 { // 8xint16
	__m128i data;

	const void   Load(const void *ptr)       { data = _mm_loadu_si128((__m128i *)ptr); }
	const void   Load64(const void *ptr)     { data = _mm_castpd_si128(_mm_load_sd((double *)ptr)); }
	const void   Load32(const void *ptr)     { data = _mm_castps_si128(_mm_load_ss((float *)ptr)); }

	const void   Store(const void *ptr)      { _mm_storeu_si128((__m128i *)ptr, data); }
	const void   Store64(const void *ptr)    { _mm_store_sd((double *)ptr, _mm_castsi128_pd(data)); }
	const void   Store32(const void *ptr)    { _mm_store_ss((float *)ptr, _mm_castsi128_ps(data)); }
	
	i16x8()                      {}
	i16x8(const void *ptr)       { Load(ptr); }
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

force_inline i16x8  operator==(i16x8 a, i16x8 b)   { return _mm_cmpeq_epi16(a.data, b.data); }
force_inline i16x8  operator<(i16x8 a, i16x8 b)    { return _mm_cmplt_epi16(a.data, b.data); }
force_inline i16x8  operator>(i16x8 a, i16x8 b)    { return _mm_cmpgt_epi16(a.data, b.data); }
force_inline bool   Test(i16x8 a)                  { return _mm_movemask_epi8(a.data) == 0xffff; }

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

force_inline i32x4  operator==(i32x4 a, i32x4 b)   { return _mm_cmpeq_epi32(a.data, b.data); }
force_inline i32x4  operator<(i32x4 a, i32x4 b)    { return _mm_cmplt_epi32(a.data, b.data); }
force_inline i32x4  operator>(i32x4 a, i32x4 b)    { return _mm_cmpgt_epi32(a.data, b.data); }
force_inline bool   Test(i32x4 a)                  { return _mm_movemask_epi8(a.data) == 0xffff; }

struct i8x16 : i16x8 { // 16xint8
	i8x16()                      {}
	i8x16(void *ptr)             { Load(ptr); }
	i8x16(__m128i d)             { data = d; }
	i8x16(int v)                 { data = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,v); }
	i8x16(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p)
	                             { data = _mm_set_epi8(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p); }

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

i16x8 Unpack8L(i16x8 a)                           { return _mm_unpacklo_epi8(a.data, _mm_setzero_si128()); }
i16x8 Unpack8H(i16x8 a)                           { return _mm_unpackhi_epi8(a.data, _mm_setzero_si128()); }
i32x4 Unpack16L(i16x8 a)                          { return _mm_unpacklo_epi16(a.data, _mm_setzero_si128()); }
i32x4 Unpack16H(i16x8 a)                          { return _mm_unpackhi_epi16(a.data, _mm_setzero_si128()); }

i8x16 Pack16(i16x8 l, i16x8 h)                    { return _mm_packus_epi16(l.data, h.data); }

i16x8 BroadcastLH0(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(0)), _MM_BCAST(0)); }
i16x8 BroadcastLH1(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(1)), _MM_BCAST(1)); }
i16x8 BroadcastLH2(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(2)), _MM_BCAST(2)); }
i16x8 BroadcastLH3(i16x8 a)                       { return _mm_shufflelo_epi16(_mm_shufflehi_epi16(a.data, _MM_BCAST(3)), _MM_BCAST(3)); }

String AsString(const f32x4& x)
{
	float *f = (float *)&x;
	return Format("%g %g %g %g", f[3], f[2], f[1], f[0]);
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

float x[256];
f32x4 global;

int16 y[256];
i16x8 yg;

#define TEST(x, v) DDUMP(x); if(v) ASSERT(AsString(x) == v);

force_inline
bool memeq8__(const void *p, const void *q, size_t len)
{
	ASSERT(len >= 16);
	const byte *t = (byte *)p;
	const byte *s = (byte *)q;
	
	auto Cmp128 = [&](size_t at)    { return i16x8(s + at) == i16x8(t + at); };
	
	if(!Test(Cmp128(len - 16) & Cmp128(0))) // tail & alignment, also <= 32
		return false;
	
	if(len <= 32)
		return true;

	const byte *e = t + len; // align up

	byte *t1 = (byte *)(((uintptr_t)t | 15) + 1);
	s += t1 - t;
	t = t1;
	len = e - t;
	e -= 32;
	while(t <= e) {
		if(!Test(Cmp128(0*16) & Cmp128(1*16)))
			return false;
		s += 32;
		t += 32;
	}
	if(len & 16)
		if(!Test(Cmp128(0)))
			return false;
	return true;
}


CONSOLE_APP_MAIN
{
	for(int i = 0; i < 256; i++) {
		x[i] = (float)i;
		y[i] = i;
	}
	
	{
		f32x4 x(1, 2, 3, 4);
		TEST(Broadcast0(x), "4 4 4 4");
		TEST(Broadcast1(x), "3 3 3 3");
		DDUMP(Broadcast2(x));
		DDUMP(Broadcast3(x));
		
		f32x4 y(1, 3, 2, 4);
		DDUMP(min(x, y));
		DDUMP(max(x, y));
		DDUMP(x == y);
		DDUMP(x != y);
		DDUMP(x < y);
		DDUMP(x <= y);
		DDUMP(x > y);
		DDUMP(x >= y);
		DDUMP(Test(x == y));
		DDUMP(Test(x == x));
	}

	{
		i16x8 x(1, 2, 3, 4, 5, 6, 7, 8);
		DDUMP(BroadcastLH0(x));
		DDUMP(BroadcastLH1(x));
		DDUMP(BroadcastLH2(x));
		DDUMP(BroadcastLH3(x));
		
		i16x8 y(1, 4, 2, 3, 8, 7, 5, 6);
		DDUMP(x == y);
		DDUMP(x < y);
		DDUMP(x > y);
		
		DDUMP(Test(x == y));
		DDUMP(Test(x == x));
	}
	
	{
		i8x16 x(1,2,3,4, 11,12,13,14, 21,22,23,24, 31,32,33,34);
		DDUMP(x);
		DDUMP(Unpack8L(x));
		DDUMP(Unpack8H(x));
	}
	{
		i16x8 x(1,2,3,4, 11,12,13,14);
		DDUMP(Unpack16L(x));
		DDUMP(Unpack16H(x));
	}
	
	{
		i32x4 x(1, 2, 3, 4);
		DDUMP(ToFloat(x));

		i32x4 y(1, 4, 2, 3);
		DDUMP(x == y);
		DDUMP(x < y);
		DDUMP(x > y);
		
		DDUMP(Test(x == y));
		DDUMP(Test(x == x));
	}

	{
		f32x4 x(1.1, 2.8, 3.7, -4.2);
		DDUMP(x);
		DDUMP(Truncate(x));
		DDUMP(Round(x));
	}
}
