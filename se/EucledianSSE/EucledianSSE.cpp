#include <Core/Core.h>
#include <xmmintrin.h>

static float distance(const int n, const float* x, const float* y){
	float result = 0.f;
	for(int i = 0; i < n; ++i) {
		const float num = x[i] - y[i];
		result += num * num;
	}
	return result;
}

static float sse_distance(int n, const float* x, const float* y){
	float result=0;
	__m128 euclidean = _mm_setzero_ps();
	for (; n>3; n-=4) {
		__m128 a = _mm_loadu_ps(x);
		__m128 b = _mm_loadu_ps(y);
		__m128 a_minus_b = _mm_sub_ps(a,b);
		__m128 a_minus_b_sq = _mm_mul_ps(a_minus_b, a_minus_b);
		euclidean = _mm_add_ps(euclidean, a_minus_b_sq);
		x+=4;
		y+=4;
	}
	__m128 shuffle1 = _mm_shuffle_ps(euclidean, euclidean, _MM_SHUFFLE(1,0,3,2));
	__m128 sum1 = _mm_add_ps(euclidean, shuffle1);
	__m128 shuffle2 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2,3,0,1));
	__m128 sum2 = _mm_add_ps(sum1, shuffle2);

	_mm_store_ss(&result, sum2);

	if (n)
		result += distance(n, x, y);	// remaining 1-3 entries
	return result;
}

struct Float4 {
	__m128 val;
	
	void SetZero() { _mm_setzero_ps(); }
	
	Float4(const float *d)            { val = _mm_loadu_ps(d); }
	Float4& operator=(const float *d) { val = _mm_loadu_ps(d); return *this; }
	Float4()                          { SetZero(); }
};

inline Float4 operator-(const Float4& a, const Float4& b) { Float4 r; r.val = _mm_sub_ps(a.val, b.val); return r; }
inline Float4 operator+(const Float4& a, const Float4& b) { Float4 r; r.val = _mm_add_ps(a.val, b.val); return r; }
inline Float4 operator*(const Float4& a, const Float4& b) { Float4 r; r.val = _mm_mul_ps(a.val, b.val); return r; }
inline Float4 sqr(const Float4& x) { return x * x; }

inline float  sum(const Float4& x) {
	__m128 shuffle1 = _mm_shuffle_ps(x.val, x.val, _MM_SHUFFLE(1,0,3,2));
	__m128 sum1 = _mm_add_ps(x.val, shuffle1);
	__m128 shuffle2 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2,3,0,1));
	__m128 sum2 = _mm_add_ps(sum1, shuffle2);
	float result;
	_mm_store_ss(&result, sum2);
	return result;
}

static float sse_distance2(int n, const float* x, const float* y){
	float result=0;
	Float4 euclidean;
	for (; n>3; n-=4) {
		euclidean = euclidean + sqr(Float4(x) - Float4(y));
		x+=4;
		y+=4;
	}
	
	result = sum(euclidean);

	if (n)
		result += distance(n, x, y);	// remaining 1-3 entries
	return result;
}


float x[15], y[15];

void main()
{
	printf("%f", sse_distance2(15, x, y));
}
