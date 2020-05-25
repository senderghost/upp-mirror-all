#include <Core/Core.h>
#include <Painter/Painter.h>

using namespace Upp;

never_inline
String AsString(__m128i x)
{
	dword h[4];
	memcpy(h, &x, 16);
	word w[8];
	memcpy(w, &x, 16);
	return Sprintf("_%08x_%08x_%08x_%08x (%d, %d, %d, %d) : (%d, %d, %d, %d)",
	               h[3], h[2], h[1], h[0], w[6], w[5], w[4], w[7], w[2], w[1], w[0], w[3]);
}

#ifdef _DEBUG
#define DUMPS(x) RLOG(#x << " = " << AsString(x));
#else
#define DUMPS(x)
#endif

force_inline
__m128i LoadRGBA(const RGBA *s)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, 0, *(dword *)s), _mm_setzero_si128());
}

force_inline
__m128i LoadRGBA2(const RGBA& c)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, *(dword *)&c, *(dword *)&c), _mm_setzero_si128());
}

force_inline
__m128i LoadRGBA2(const RGBA *s)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, *(dword *)(s + 1), *(dword *)s), _mm_setzero_si128());
}

force_inline
__m128i LoadRGBAL(__m128i x)
{
	return _mm_unpacklo_epi8(x, _mm_setzero_si128());
}

force_inline
__m128i LoadRGBAH(__m128i x)
{
	return _mm_unpackhi_epi8(x, _mm_setzero_si128());
}

force_inline
__m128i PackRGBA(__m128i l, __m128i h)
{
	return _mm_packus_epi16(l, h);
}

force_inline
void StoreRGBA(RGBA *rgba, __m128i x)
{
	_mm_store_ss((float *)rgba, _mm_castsi128_ps(PackRGBA(x, _mm_setzero_si128())));
}

force_inline
void StoreRGBA2(RGBA *rgba, __m128i x)
{
	_mm_storeu_si64(rgba, PackRGBA(x, _mm_setzero_si128()));
}

force_inline
__m128i BroadcastAlpha(__m128i x)
{
	return _mm_shufflelo_epi16(_mm_shufflehi_epi16(x, 0xff), 0xff);
}

force_inline
__m128i Mul8(__m128i x, int alpha)  // cover is 0 - 256
{
	return _mm_srli_epi16(_mm_mullo_epi16(_mm_set1_epi16(alpha), x), 8); // int a = c.a * cover >> 8;
}

/*
force_inline
__m128i MakeAlpha(__m128i x)
{
	x = BroadcastAlpha(x);
	x = _mm_add_epi16(x, _mm_srli_epi16(x, 7)); // (a + (a >> 7))
	x = _mm_sub_epi16(_mm_set1_epi16(256), x); // 256 - (a + (a >> 7));
	return x;
}
*/
force_inline
__m128i MakeAlpha(__m128i x)
{
	x = BroadcastAlpha(x);
	x = _mm_srli_epi16(_mm_mullo_epi16(_mm_set_epi16(256, 258, 258, 258, 256, 258, 258, 258), x), 8); // a for alpha, 256*a/255 for color
	x = _mm_sub_epi16(_mm_set1_epi16(256), x); // 256 - a for alpha, 256 - (a + (a >> 7)) for color;
	return x;
}

force_inline
__m128i AlphaBlendSSE2(__m128i t, __m128i s, __m128i alpha)
{
	LOG("---- AlphaBlendSSE2");
	DUMPS(t);
	DUMPS(s);
	DUMPS(alpha);
	return _mm_adds_epi16(s, _mm_srli_epi16(_mm_mullo_epi16(t, alpha), 8)); // t = c + (t * alpha >> 8);
}

force_inline
void AlphaBlend1(RGBA *t, __m128i s, __m128i alpha)
{
	StoreRGBA(t, AlphaBlendSSE2(LoadRGBA(t), s, alpha));
}

force_inline
void AlphaBlend1(RGBA *t, const RGBA *q)
{
	__m128i s = LoadRGBA(q);
	StoreRGBA(t, AlphaBlendSSE2(LoadRGBA(t), s, MakeAlpha(s)));
}

force_inline
void AlphaBlend1(RGBA *t, const RGBA *q, int alpha)
{
	__m128i s = Mul8(LoadRGBA(q), alpha);
	StoreRGBA(t, AlphaBlendSSE2(LoadRGBA(t), s, MakeAlpha(s)));
}

force_inline
void AlphaBlend1(RGBA *t, const RGBA& c, int alpha)
{
	__m128i s = Mul8(LoadRGBA(&c), alpha);
	AlphaBlend1(t, &c, alpha);
}

force_inline
void AlphaBlend2(RGBA *t, __m128i s, __m128i alpha)
{
	StoreRGBA2(t, AlphaBlendSSE2(LoadRGBA2(t), s, alpha));
}


force_inline
void AlphaBlend4(RGBA *t, __m128i sl, __m128i al, __m128i sh, __m128i ah)
{
	__m128i t4 = _mm_loadu_si128((__m128i *)t);
	_mm_storeu_si128((__m128i *)t,
		PackRGBA(
			AlphaBlendSSE2(LoadRGBAL(t4), sl, al),
			AlphaBlendSSE2(LoadRGBAH(t4), sh, ah)));
}

void AlphaBlendSSE2(RGBA *t, const RGBA& c, int alpha, int len)
{
	__m128i s = LoadRGBA2(c);
	DUMPS(s);
	s = Mul8(s, alpha);
	DUMPS(s);
	__m128i a = MakeAlpha(s);
	DUMPS(a);
	while(len >= 4) {
		AlphaBlend4(t, s, a, s, a);
		t += 4;
		len -= 4;
	}
	if(len & 2) {
		AlphaBlend2(t, s, a);
		t += 2;
	}
	if(len & 1)
		AlphaBlend1(t, s, a);
}

RGBA RandomRGBA()
{
	return (int)Random(256) * Color(Random(256), Random(256), Random(256));
}

int axx = 123;

RGBA gt[1];
RGBA gs[1];

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	for(int i = 0; i < 1000000; i++) {
		int len = 1; // Random(100) + 1;
		Vector<RGBA> t;
//		Vector<RGBA> s;
		
		for(int i = 0; i < len; i++) {
			t.Add(RandomRGBA());
//			s.Add(RandomRGBA());
		}

		Vector<RGBA> t1 = clone(t);

		RGBA c = RandomRGBA();
		int alpha = Random(257);
		DUMP(t[0]);
		DUMP(c);
		DUMP(alpha);
		{
			RTIMING("Non SSE");
			RGBA c2 = Mul8(c, alpha);
			DUMP(c2);
			RGBA *q = t1.begin();
			const RGBA *e = t1.end();
			while(q < e)
				AlphaBlend(*q++, c2);
		}
		LOG("===============");
		{
			RTIMING("SSE");
			AlphaBlendSSE2(t, c, alpha, len);
		}

		if(t != t1) {
			RDUMP(t);
			RDUMP(t1);
			RDUMP(i);
			RDUMP(len);
			Panic("Failed");
		}
		LOG("===================================================");
	}
	for(int i = 0; i < 20000000; i++) {
		{
			RTIMING("1 Non SSE");
			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);

			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);
			AlphaBlendCover8(gt[0], gs[0], axx);
		}
		{
			RTIMING("1 SSE");
			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);

			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);
			AlphaBlend1(gt, gs[0], axx);
		}
	}
	return;
}
