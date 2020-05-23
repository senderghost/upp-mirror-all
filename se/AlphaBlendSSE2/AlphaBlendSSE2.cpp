#include <Core/Core.h>
#include <Painter/Painter.h>

using namespace Upp;

#if 0
void AlphaBlendOpaque(RGBA *t, RGBA c, int alpha, int len)
{
	const RGBA *e = s + len;
	while(s < e) {
		int alpha = 256 - (s->a + (s->a >> 7));
		t->r = c.r + (alpha * t->r >> 8);
		t->g = c.g + (alpha * t->g >> 8);
		t->b = c.b + (alpha * t->b >> 8);
		t->a = 255;
		t++;
	}
}

inline void AlphaBlend(RGBA& t, const RGBA& c)
{
	int alpha = 256 - (c.a + (c.a >> 7));
	t.r = c.r + (alpha * t.r >> 8);
	t.g = c.g + (alpha * t.g >> 8);
	t.b = c.b + (alpha * t.b >> 8);
	t.a = c.a + ((256 - c.a) * t.a >> 8);
}

inline void AlphaBlendOpaqueCover8(RGBA& t, const RGBA& c, int cover)
{
	int a = c.a * cover >> 8;
	int alpha = 256 - a - (a >> 7);

	t.r = (c.r * cover >> 8) + (alpha * t.r >> 8);
	t.g = (c.g * cover >> 8) + (alpha * t.g >> 8);
	t.b = (c.b * cover >> 8) + (alpha * t.b >> 8);
	t.a = a + (alpha * t.a >> 8);
}

inline void AlphaBlendCover8(RGBA& t, const RGBA& c, int cover)
{
	int a = c.a * cover >> 8;
	int alpha = 256 - a - (a >> 7);

	t.r = (c.r * cover >> 8) + (alpha * t.r >> 8);
	t.g = (c.g * cover >> 8) + (alpha * t.g >> 8);
	t.b = (c.b * cover >> 8) + (alpha * t.b >> 8);
	t.a = a + (alpha * t.a >> 8);
}
#endif

never_inline
String AsString(__m128i x)
{
	dword h[4];
	memcpy(h, &x, 16);
	return Sprintf("_%08x_%08x_%08x_%08x", h[3], h[2], h[1], h[0]);
}

#ifdef _DEBUG
#define DUMPS(x) RLOG(#x << " = " << AsString(x));
#else
#define DUMPS(x)
#endif

__m128i LoadRGBA(RGBA *s)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, *(dword *)s, *(dword *)s), _mm_setzero_si128());
}

__m128i LoadRGBA2(RGBA *s)
{
	return _mm_unpacklo_epi8(_mm_set_epi32(0, 0, *(dword *)(s + 1), *(dword *)s), _mm_setzero_si128());
}

__m128i LoadRGBAL(__m128i x)
{
	return _mm_unpacklo_epi8(x, _mm_setzero_si128());
}

__m128i LoadRGBAH(__m128i x)
{
	return _mm_unpackhi_epi8(x, _mm_setzero_si128());
}

__m128i PackRGBA(__m128i l, __m128i h)
{
	return _mm_packus_epi16(l, h);
}

void StoreRGBA(RGBA *rgba, __m128i x)
{
	_mm_storeu_si32(rgba, PackRGBA(x, _mm_setzero_si128()));
}

void StoreRGBA2(RGBA *rgba, __m128i x)
{
	_mm_storeu_si64(rgba, PackRGBA(x, _mm_setzero_si128()));
}

__m128i BroadcastAlpha(__m128i x)
{
	return _mm_shufflelo_epi16(_mm_shufflehi_epi16(x, 0xff), 0xff);
}

__m128i ApplyCover(__m128i x, __m128i cover)  // cover is 0 - 256
{
	return _mm_srli_epi16(_mm_mullo_epi16(cover, x), 8); // int a = c.a * cover >> 8;
}

__m128i MakeAlpha(__m128i x)
{
	x = BroadcastAlpha(x);
	x = _mm_add_epi16(x, _mm_srli_epi16(x, 7)); // int alpha = 256 - a - (a >> 7);
	x = _mm_sub_epi16(_mm_set1_epi16(256), x);
	return x;
}

__m128i AlphaBlendSSE2(__m128i t, __m128i c, __m128i alpha)
{
	return _mm_adds_epi16(c, _mm_srli_epi16(_mm_mullo_epi16(t, alpha), 8)); // t = c + (t * alpha >> 8);
}

__m128i AlphaBlendSSE2(__m128i t, __m128i c)
{
	return AlphaBlendSSE2(t, c, MakeAlpha(c));
}

void AlphaBlend1(RGBA *t, const RGBA& c)
{
	StoreRGBA(t, AlphaBlendSSE2(LoadRGBA(t), LoadRGBA(c)));
}

void AlphaBlend1(RGBA *t, const RGBA *s)
{
	StoreRGBA(t, AlphaBlendSSE2(LoadRGBA(t), LoadRGBA(s)));
}

void AlphaBlend2(RGBA *t, const RGBA *s)
{
	StoreRGBA2(t, AlphaBlendSSE2(LoadRGBA2(t), LoadRGBA2(s)));
}

void AlphaBlend2(RGBA *t, const RGBA& c)
{
	StoreRGBA2(t, AlphaBlendSSE2(LoadRGBA2(t), LoadRGBA(s)));
}

void AlphaBlend4(RGBA *t, const RGBA *s)
{
	
}


RGBA c = Color(0x12, 0x34, 0x56);

RGBA c2[2];
RGBA c1[4];
dword c3[4] = { 0x1112131a, 0x2122232a, 0x3132333a, 0x4142434a };

RGBA RandomRGBA()
{
	return (int)Random(256) * Color(Random(256), Random(256), Random(256));
}

CONSOLE_APP_MAIN
{
	c1[0] = Color(0x12, 0x34, 0x56);
	c1[1] = Color(0x78, 0x9a, 0xbc);
	
	for(int i = 0; i < 10; i++) {
		RGBA t[2] = { RandomRGBA(), RandomRGBA() };
		RGBA s[2] = { RandomRGBA(), RandomRGBA() };

		RGBA t1[2] = { t[0], t[1] };
		DDUMP(t[1]);
		DDUMP(t1[1]);
		AlphaBlend(t1, s, 2);
		RLOG("NORMAL: " << t1[0] << ", " << t1[1]);

		
		AlphaBlend2(t, s);
		
		RLOG("SSE2: " << t[0] << ", " << t[1]);
		RLOG("===============");
	}
	return;
	
#if 0
	RGBA q = 255 * Red();
	DUMP(q);
	DUMP(255 * Red());
	DUMPS(LoadRGBA(q));
	DUMPS(BroadcastAlpha(LoadRGBA(q)));
	DUMPS(MakeAlpha(LoadRGBA(0 * Red())));
	DUMPS(MakeAlpha(LoadRGBA(127 * Red())));
	DUMPS(MakeAlpha(LoadRGBA(128 * Red())));
	DUMPS(MakeAlpha(LoadRGBA(255 * Red())));
	
	__m128i x = _mm_loadu_si128((__m128i *)c3);
	
	DUMPS(x);
	
	DUMPS(LoadRGBAL(x));
	DUMPS(LoadRGBAH(x));

	DUMPS(PackRGBA(LoadRGBAL(x), LoadRGBAH(x)));
	
	DUMPS(_mm_shufflehi_epi16(x, 0));
	DUMPS(_mm_shufflelo_epi16(x, 0));

	DUMPS(BroadcastAlpha(LoadRGBAL(x)));
	
	memset(c2, 255, sizeof(c2));

/*
	__m128i x = _mm_setzero_si128();
	DUMPS(x);
	x = LoadRGBA(c);
	DUMPS(x);
	x = LoadRGBA2(c1);
	DUMPS(x);
	
	int cover = 128;

	int a = c.a * cover >> 8;
	int alpha = 256 - a - (a >> 7);

	__m128i alpha2 = _mm_set1_epi16(alpha);
	__m128i cover2 = _mm_set1_epi16(cover);
	
	__m128i t = LoadRGBA2(c2);
	DUMPS(t);
	
	t = AlphaBlendCoverOpaqueSSE2(t, x, alpha2, cover2, alphamask);
	
	DUMPS(t);
*/
#endif
}
