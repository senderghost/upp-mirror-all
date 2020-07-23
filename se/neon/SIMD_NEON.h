#include "arm_neon.h"

using namespace Upp;

struct f32x4 {
	float32x4_t data;

	f32x4& Load(void *ptr)       { data = vld1q_f32((float *)ptr); return *this; }
	f32x4& Load64(void *ptr)     { data = vreinterpretq_f32_s64(vsetq_lane_s64(*(int64_t *)ptr, vdupq_n_s64(0), 0)); return *this; }
	f32x4& Load32(void *ptr)     { data = vsetq_lane_f32(*(float *)ptr, vdupq_n_f32(0), 0); return *this; }

	void   Store(void *ptr)      { vst1q_f32((float32_t *)ptr, data); }
	void   Store64(void *ptr)    { vst1q_lane_s64((int64_t *)ptr, vreinterpretq_s64_f32(data), 0); }
	void   Store32(void *ptr)    { vst1q_lane_f32((float32_t *)ptr, data, 0); }
	
	f32x4()                      {}
	f32x4(void *ptr)             { Load(ptr); }
	f32x4(float32x4_t d)         { data = d; }

	f32x4(double f)              { data = vsetq_lane_f32((float)f, vdupq_n_f32(0), 0); }
	f32x4(float f)               { data = vsetq_lane_f32((float)f, vdupq_n_f32(0), 0); }
	f32x4(int f)                 { data = vsetq_lane_f32((float)f, vdupq_n_f32(0), 0); }
	f32x4(double a, double b, double c, double d) {
		float __attribute__((aligned(16))) w[4] = { (float)d, (float)c, (float)b, (float)a };
		data = vld1q_f32(w);
	}
	
	operator float32x4_t()       { return data; }
};

force_inline f32x4  f32all(double f) { return vdupq_n_f32((float)f); }

force_inline f32x4  operator+(f32x4 a, f32x4 b)   { return vaddq_f32(a, b); }
force_inline f32x4& operator+=(f32x4& a, f32x4 b) { return a = a + b; }
force_inline f32x4  operator-(f32x4 a, f32x4 b)   { return vsubq_f32(a, b); }
force_inline f32x4& operator-=(f32x4& a, f32x4 b) { return a = a - b; }
force_inline f32x4  operator*(f32x4 a, f32x4 b)   { return vmulq_f32(a, b); }
force_inline f32x4& operator*=(f32x4& a, f32x4 b) { return a = a * b; }

force_inline f32x4  operator/(f32x4 a, f32x4 b)   {
	float32x4_t reciprocal = vrecpeq_f32(b);
	reciprocal = vmulq_f32(vrecpsq_f32(b, reciprocal), reciprocal);
	reciprocal = vmulq_f32(vrecpsq_f32(b, reciprocal), reciprocal);
	return vmulq_f32(a,reciprocal);
}

force_inline f32x4& operator/=(f32x4& a, f32x4 b) { return a = a / b; }

force_inline f32x4  operator==(f32x4 a, f32x4 b)  { return vreinterpretq_f32_u32(vceqq_f32(a, b)); }
force_inline f32x4  operator!=(f32x4 a, f32x4 b)  { return vreinterpretq_f32_u32(vmvnq_u32(vceqq_f32(a, b))); }
force_inline f32x4  operator<(f32x4 a, f32x4 b)   { return vreinterpretq_f32_u32(vcltq_f32(a, b)); }
force_inline f32x4  operator>(f32x4 a, f32x4 b)   { return vreinterpretq_f32_u32(vcgtq_f32(a, b)); }
force_inline f32x4  operator<=(f32x4 a, f32x4 b)  { return vreinterpretq_f32_u32(vcleq_f32(a, b)); }
force_inline f32x4  operator>=(f32x4 a, f32x4 b)  { return vreinterpretq_f32_u32(vcgeq_f32(a, b)); }

force_inline bool   AllTrue(f32x4 a) {
	uint32x4_t v = vreinterpretq_u32_f32(a);
    uint32x2_t tmp = vand_u32(vget_low_u32(v), vget_high_u32(v));
    return vget_lane_u32(vpmax_u32(tmp, tmp), 0);
}

force_inline f32x4 min(f32x4 a, f32x4 b)          { return vminq_f32(a, b); }
force_inline f32x4 max(f32x4 a, f32x4 b)          { return vmaxq_f32(a, b); }

force_inline f32x4 Broadcast0(f32x4 a)            { return vdupq_n_f32(vgetq_lane_f32(a, 0)); }
force_inline f32x4 Broadcast1(f32x4 a)            { return vdupq_n_f32(vgetq_lane_f32(a, 1)); }
force_inline f32x4 Broadcast2(f32x4 a)            { return vdupq_n_f32(vgetq_lane_f32(a, 2)); }
force_inline f32x4 Broadcast3(f32x4 a)            { return vdupq_n_f32(vgetq_lane_f32(a, 3)); }


struct i16x8 { // 8xint16
	int16x8_t data;

	i16x8& Load(const void *ptr) { data = vld1q_s16((int16_t *)ptr); return *this; }
	i16x8& Load64(void *ptr)     { data = vreinterpretq_s16_s64(vsetq_lane_s64(*(int64_t *)ptr, vdupq_n_s64(0), 0)); return *this; }
	i16x8& Load32(void *ptr)     { data = vreinterpretq_s16_s32(vsetq_lane_s32(*(int32_t *)ptr, vdupq_n_s32(0), 0)); return *this; }


	void   Store(void *ptr)      { vst1q_s16((int16_t *)ptr, data); }
	void   Store64(void *ptr)    { vst1q_lane_s64((int64_t *)ptr, vreinterpretq_s64_s16(data), 0); }
	void   Store32(void *ptr)    { vst1q_lane_s32((int32_t *)ptr, vreinterpretq_s32_s16(data), 0); }

	i16x8()                      {}
	i16x8(const void *ptr)       { Load(ptr); }
	i16x8(int16x8_t d)           { data = d; }
	i16x8(int v)                 { data = vsetq_lane_s16(v, vdupq_n_s16(0), 0); }
	i16x8(int a, int b, int c, int d, int e, int f, int g, int h) {
		int16_t __attribute__((aligned(16))) val[8] = { (int16_t)h, (int16_t)g, (int16_t)f, (int16_t)e, (int16_t)d, (int16_t)c, (int16_t)b, (int16_t)a };
		data = vld1q_s16(val);
	}

	operator int16x8_t()         { return data; }
};


force_inline i16x8  i16all(int v)                  { return vdupq_n_s16(v); }

force_inline i16x8  operator+(i16x8 a, i16x8 b)    { return vaddq_s16(a, b); }
force_inline i16x8& operator+=(i16x8& a, i16x8 b)  { return a = a + b; }
force_inline i16x8  operator-(i16x8 a, i16x8 b)    { return vsubq_s16(a, b); }
force_inline i16x8& operator-=(i16x8& a, i16x8 b)  { return a = a - b; }
force_inline i16x8  operator*(i16x8 a, i16x8 b)    { return vmulq_s16(a, b); }
force_inline i16x8& operator*=(i16x8& a, i16x8 b)  { return a = a * b; }

force_inline i16x8  operator&(i16x8 a, i16x8 b)    { return vandq_s16(a, b); }
force_inline i16x8& operator&=(i16x8& a, i16x8 b)  { return a = a & b; }
force_inline i16x8  operator|(i16x8 a, i16x8 b)    { return vorrq_s16(a, b); }
force_inline i16x8& operator|=(i16x8& a, i16x8 b)  { return a = a | b; }
force_inline i16x8  operator^(i16x8 a, i16x8 b)    { return veorq_s16(a, b); }
force_inline i16x8& operator^=(i16x8& a, i16x8 b)  { return a = a ^ b; }
force_inline i16x8  operator~(i16x8 a)             { return vmvnq_s16(a); }

force_inline i16x8  operator>>(i16x8 a, int b)     { return vshlq_s16(a, vdupq_n_s16(-b)); }
force_inline i16x8& operator>>=(i16x8& a, int b)   { return a = a >> b; }
force_inline i16x8  operator<<(i16x8 a, int b)     { return vshlq_s16(a, vdupq_n_s16(b)); }
force_inline i16x8& operator<<=(i16x8& a, int b)   { return a = a << b; }

force_inline i16x8  operator==(i16x8 a, i16x8 b)  { return vreinterpretq_s16_u16(vceqq_s16(a, b)); }
force_inline i16x8  operator<(i16x8 a, i16x8 b)   { return vreinterpretq_s16_u16(vcltq_s16(a, b)); }
force_inline i16x8  operator>(i16x8 a, i16x8 b)   { return vreinterpretq_s16_u16(vcgtq_s16(a, b)); }

force_inline bool   AllTrue(i16x8 a) {
	uint32x4_t v = vreinterpretq_u32_s16(a);
    uint32x2_t tmp = vand_u32(vget_low_u32(v), vget_high_u32(v));
    return vget_lane_u32(vpmax_u32(tmp, tmp), 0) == 0xffffffff;
}
