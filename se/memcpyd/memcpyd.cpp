#include <Core/Core.h>

using namespace Upp;

never_inline
void memcpyd_l2(dword *t, dword *s, size_t len)
{
	auto Copy4 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };

	Copy4(0); // align target data up on next 16 bytes boundary
	const dword *e = t + len;
	dword *t1 = (dword *)(((uintptr_t)t | 15) + 1);
	s += t1 - t;
	t = t1;
	len = e - t;
	e -= 16;
	if(len >= 1024*1024) { // for really huge data, call memcpy to bypass the cache
		memcpy(t, s, 4 * len);
		return;
	}
	while(t <= e) {
		Copy4(0); Copy4(4); Copy4(8); Copy4(12);
		t += 16;
		s += 16;
	}
	if(len & 8) {
		Copy4(0); Copy4(4);
		t += 8;
		s += 8;
	}
	if(len & 4)
		Copy4(0);
}

inline
void svo_memcpyd(dword *t, dword *s, size_t len)
{
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

	auto Copy4 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), _mm_loadu_si128((__m128i *)(s + at))); };

	Copy4(len - 4); // copy tail
	if(len >= 16) {
		memcpyd_l2(t, s, len);
		return;
	}
	if(len & 8) {
		Copy4(0); Copy4(4);
		t += 8;
		s += 8;
	}
	if(len & 4)
		Copy4(0);
}

inline
void svo_memcpyd2(dword *t, dword *s, int len)
{ // for non-x86 CPUs
	if(len >= 16) {
		memcpy(t, s, 4 * len);
		return;
	}
	if(len & 8) {
		t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = s[3];
		t[4] = s[4]; t[5] = s[5]; t[6] = s[6]; t[7] = s[7];
		t += 8;
		s += 8;
		len -= 8;
	}
	if(len & 4) {
		t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = s[3];
		s += 4;
		t += 4;
	}
	if(len & 2) {
		t[0] = s[0]; t[1] = s[1];
		s += 2;
		t += 2;
	}
	if(len & 1)
		t[0] = s[0];
}

void Check(void (*copy)(dword *t, dword *s, size_t len))
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
		if(memcmp(b1, b2, 2000 * sizeof(dword)))
			Panic("Failed");
	}
}

CONSOLE_APP_MAIN
{
	Check(svo_memcpyd);

#if 0
	Buffer<dword> b1(200000);
	Buffer<dword> b2(200000);
	
	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(8000);
	

	for(int i = 0; i < 10000; i++) {
		{
			RTIMING("memcpy");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], 4 * rnd[i + 1]);
		}
		{
			RTIMING("memcpyd");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memcpyd((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("memcpyd2");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memcpyd2((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
	}
#else
	int bsize=8*1024*1024;
	Buffer<dword> b1(bsize, 0), b2(bsize, 0);
	dword cw = 123;

	String result="\"N\",\"memcpy()\",\"memcpyd\"\r\n";
	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			memcpyd(~b1 + 1, ~b2 + 1, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			svo_memcpyd(~b1 + 1, ~b2 + 1, len);
		int64 t2=usecs();
		String r = Format("%d,%f,%f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
		RLOG(r);
		result.Cat(r + "\r\n");
		if(len<64) len++;
		else len*=2;
	}
#endif
	SaveFile(GetHomeDirFile("memset.csv"),result);
}
