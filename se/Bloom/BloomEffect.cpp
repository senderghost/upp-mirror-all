#include "BloomEffect.h"

BloomEffectSSE2::BloomEffectSSE2(float bloomIntensity, float bloomSaturation, float baseIntensity, float baseSaturation)
	: BloomIntensity(bloomIntensity)
	, BloomSaturation(bloomSaturation)
	, BaseIntensity(baseIntensity)
	, BaseSaturation(baseSaturation)
{
}

BloomEffectSSE2::~BloomEffectSSE2(void)
{
}

float BloomEffectSSE2::dot(const F32vec4& a, const F32vec4& b)
{
	F32vec4 c = a * b;
	return c[1] + c[2] + c[3];
}

void BloomEffectSSE2::AdjustSaturation(F32vec4& color, const F32vec4& saturation)
{
	F32vec4 greyweight( 0.11f, 0.59f, 0.3f, 0.0f );
	F32vec4 grey(dot(color, greyweight));
	F32vec4 dest(0.0f);
	lerp(grey, color, saturation, dest);

	color = dest;
}

void BloomEffectSSE2::lerp(const F32vec4& grey, const F32vec4& color, const F32vec4& saturation, F32vec4& dest)
{
	dest = grey + saturation * (color - grey);
}

F32vec4 BloomEffectSSE2::saturate(F32vec4& v)
{
	static const F32vec4 kMax(1.0f);
	static const F32vec4 kMin(0.0f);

	F32vec4 res = v;

	res = simd_max(res, kMin);
	res = simd_min(res, kMax);

	return res;
}

void BloomEffectSSE2::ComputeBloom(F32vec4& color, F32vec4& dest)
{
	static const F32vec4 kMax(1.0f);
	static const F32vec4 BloomThreshold(0.25f);

	F32vec4 alpha(color[0]);
	F32vec4 base = color / alpha; // color[0] is alpha

	F32vec4 bloom = saturate((base - BloomThreshold) / (kMax - BloomThreshold));

	// Adjust color saturation and intensity.
	AdjustSaturation(bloom, BloomSaturation);
	AdjustSaturation(base, BaseSaturation);

	bloom = bloom * BloomIntensity;

	base = base * BaseIntensity;

	// Darken down the base image in areas where there is a lot of bloom,
	// to prevent things looking excessively burned-out.
	base *= (kMax - saturate(bloom));

	// Combine the two images.
	dest = (base + bloom) * alpha;
	dest[0] = alpha[0];
}

void BloomEffectSSE2::ComputeBloom(RGBA& color)
{
	F32vec4 colorf;
	F32vec4 destf(0.0f);

	colorf[0] = color.a;
	colorf[1] = color.r;
	colorf[2] = color.g;
	colorf[3] = color.b;

	colorf /= F32vec4(255.0f);

	ComputeBloom(colorf, destf);
	destf = saturate(destf);
	
	color.a = byte(destf[0] * 255);
	color.r = byte(destf[1] * 255);
	color.g = byte(destf[2] * 255);
	color.b = byte(destf[3] * 255);
}

Image BloomEffect(const Image& img, float bloomIntensity, float bloomSaturation, float baseIntensity, float baseSaturation)
{
	ImageBuffer r(img.GetSize());

	BloomEffectSSE2 effect(bloomIntensity, bloomSaturation, baseIntensity, baseSaturation);
	RGBA *t = ~r;
	for(const RGBA& s : img) {
		*t = s;
		effect.ComputeBloom(*t++);
	}

	return r;
}

Image CoBloomEffect(const Image& img, float bloomIntensity, float bloomSaturation, float baseIntensity, float baseSaturation)
{
	Size isz = img.GetSize();
	ImageBuffer r(isz);
	std::atomic<int> yy(0);
	CoDo([&] {
		BloomEffectSSE2 effect(bloomIntensity, bloomSaturation, baseIntensity, baseSaturation);
		for(int y = yy++; y < isz.cy; y = yy++) {
			RGBA *t = r[y];
			const RGBA *s = img[y];
			const RGBA *e = s + isz.cx;
			while(s < e) {
				*t = *s;
				effect.ComputeBloom(*t++);
				s++;
			}
		}
	});

	return r;
}

Image PPLBloomEffect(const Image& img, float bloomIntensity, float bloomSaturation, float baseIntensity, float baseSaturation)
{
	Size isz = img.GetSize();
	ImageBuffer r(isz);
	std::atomic<int> yy(0);
	using namespace Concurrency;
	parallel_for(0, isz.cy, [&](UINT y) {
		BloomEffectSSE2 effect(bloomIntensity, bloomSaturation, baseIntensity, baseSaturation);
		RGBA *t = r[y];
		const RGBA *s = img[y];
		const RGBA *e = s + isz.cx;
		while(s < e) {
			*t = *s;
			effect.ComputeBloom(*t++);
			s++;
		}
	});
	return r;
}