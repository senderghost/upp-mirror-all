#include <Core/Core.h>

using namespace Upp;

never_inline
void memcpy8_l(void *p, const void *q, size_t len)
{
	ASSERT(len >= 16);
	
	byte *t = (byte *)p;
	const byte *s = (const byte *)q;

	auto Copy128 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };

	if(len > 4*1024*1024) { // for really huge data, call memcpy to bypass the cache
		memcpy(t, s, len);
		return;
	}
	Copy128(len - 16); // copy tail
	Copy128(0); // align target data up on the next 16 bytes boundary
	const byte *e = t + len;
	byte *t1 = (byte *)(((uintptr_t)t | 15) + 1);
	s += t1 - t;
	t = t1;
	len = e - t;
	e -= 64;
	while(t <= e) {
		Copy128(0*16); Copy128(1*16); Copy128(2*16), Copy128(3*16);
		t += 64;
		s += 64;
	}
	if(len & 32) {
		Copy128(0*16); Copy128(1*16);
		t += 32;
		s += 32;
	}
	if(len & 16)
		Copy128(0*16);
}

inline
void memcpy32(void *p, const void *q, size_t len)
{
	dword *t = (dword *)p;
	dword *s = (dword *)q;

#ifdef CPU_64
	if(len <= 4) {
		if(len) {
			if(len > 1) {
				*(int64 *)t = *(int64 *)s;
				*(int64 *)(t + len - 2) = *(int64 *)(s + len - 2);
				return;
			}
			*t = *s;
		}
		return;
	}
#else
	if(len < 4) {
		if(len) {
			if(len > 1) {
				t[0] = s[0];
				t[1] = s[1];
				t[len - 1] = s[len - 1];
				return;
			}
			*t = *s;
		}
		return;
	}
#endif

	auto Copy128 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };

	if(len >= 16) {
		memcpy8_l(t, s, 4 * len);
		return;
	}
	Copy128(len - 4); // copy tail
	if(len & 8) {
		Copy128(0); Copy128(4);
		t += 8;
		s += 8;
	}
	if(len & 4)
		Copy128(0);
}

inline
void memcpy32a(void *p, const void *q, size_t len)
{
	dword *t = (dword *)p;
	dword *s = (dword *)q;

	if(len <= 4) {
		if(len < 2) {
			if(len)
				t[0] = s[0];
			return;
		}
		*(qword *)t = *(qword *)s;
		*(qword *)(t + len - 2) = *(qword *)(s + len - 2);
		return;
	}

	if(len >= 16) {
		memcpy8_l(t, s, 4 * len);
		return;
	}
	auto Copy128 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };
	Copy128(len - 4); // copy tail
	if(len & 8) {
		Copy128(0); Copy128(4);
		t += 8;
		s += 8;
	}
	if(len & 4)
		Copy128(0);
/*
	if(len <= 8) {
		auto Copy128 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };
		Copy128(0);
		Copy128(len - 4);
		if(len > 8) {
			Copy128(4);
			Copy128(len - 8);
		}
		return;
	}
	memcpy8_l(t, s, 4 * len);
*/
}

void Check(void (*copy)(void *t, const void *s, size_t len))
{
	RTIMING("Check");
	Buffer<dword> b0(2000, 0), b1(2000, 0), b2(2000, 0);
	for(int i = 0; i < 500000; i++) {
		int pos = Random(200);
		int len = Random(200);
		memsetd(~b0 + pos, i, len);
		pos = Random(200);
		len = Random(200);
		copy(~b1 + pos, ~b0 + pos, len);
		memcpy(~b2 + pos, ~b0 + pos, len * 4);
		if(memcmp(b1, b2, 2000 * sizeof(dword))) {
			RDUMP(pos);
			RDUMP(len);
			Panic("Failed");
		}
	}
}

CONSOLE_APP_MAIN
{
	Check(memcpy32);
	
	Buffer<byte> x(100000000);
	memcpy(x, x + 100, 10000000);

	Buffer<dword> b1(200000);
	Buffer<dword> b2(200000);
	
	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(20);
	

	for(int i = 0; i < 10000; i++) {
		{
			RTIMING("memcpy");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], 4 * rnd[i + 1]);
		}
		{
			RTIMING("memcpyd");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpyd((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("memcpy32");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy32((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
	}

	{
		int bsize=8*1024*1024;
		Buffer<dword> b1(bsize, 0), b2(bsize, 0);
		dword cw = 123;
	
		for(int len=1;len<=bsize;){
			int maximum=100000000/len;
			int64 t0=usecs();
			for(int i = 0; i < maximum; i++)
				memcpyd(~b1 + 1, ~b2 + 1, len);
			int64 t1=usecs();
			for(int i = 0; i < maximum; i++)
				memcpy32(~b1 + 1, ~b2 + 1, len);
			int64 t2=usecs();
			String r = Format("%d: %f, %f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
			RLOG(r);
			if(len<64) len++;
			else len*=2;
		}
	}
}
