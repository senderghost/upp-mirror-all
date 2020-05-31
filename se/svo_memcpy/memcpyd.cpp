#include <Core/Core.h>

using namespace Upp;

never_inline
void svo_memcpy_l(byte *t, byte *s, size_t len)
{
	const byte *e = t + len;
	byte *t2 = (byte *)(((uintptr_t)t | 3) + 1);
	s += t2 - t;
	t = t2;
	len = e - t;
	memcpyd((dword *)t, (dword *)s, len >> 2);
}

never_inline
void memcpy8_l(byte *t, const byte *s, size_t len)
{
	ASSERT(len >= 16);

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
		Copy128(0); Copy128(16); Copy128(32); Copy128(48);
		t += 64;
		s += 64;
	}
	if(len & 32) {
		Copy128(0); Copy128(16);
		t += 32;
		s += 32;
	}
	if(len & 16)
		Copy128(0);
}

inline
void memcpy8(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(len <= 4) {
		if(len < 2) {
			if(len)
				t[0] = s[0];
			return;
		}
		word a = *(word *)s;
		word b = *(word *)(s + len - 2);
		*(word *)t = a;
		*(word *)(t + len - 2) = b;
		return;
	}
	if(len <= 16) {
		if(len <= 8) {
			dword a = *(dword *)(s);
			dword b = *(dword *)(s + len - 4);
			*(dword *)(t) = a;
			*(dword *)(t + len - 4) = b;
			return;
		}
		uint64 a = *(uint64 *)s;
		uint64 b = *(uint64 *)(s + len - 8);
		*(uint64 *)t = a;
		*(uint64 *)(t + len - 8) = b;
		return;
	}
	memcpy8_l(t, s, len);
}

inline
void memcpy8a(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(len < 4) {
		if(len < 2) {
			if(len)
				t[0] = s[0];
			return;
		}
		*(word *)t = *(word *)s;
		*(word *)(t + len - 2) = *(word *)(s + len - 2);
		return;
	}
	if(len >= 16) {
		memcpy8_l(t, s, len);
		return;
	}
	*(dword *)(t + len - 4) = *(dword *)(s + len - 4);
	if(len & 8) {
		*(uint64 *)t = *(uint64 *)s;
		s += 8;
		t += 8;
	}
	if(len & 4)
		*(dword *)t = *(dword *)s;
}

inline
void svo_memcpya(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(len >= 16) {
		memcpy(t, s, len);
		return;
	}
	if(len & 8) {
		t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = s[3];
		t[4] = s[4]; t[5] = s[5]; t[6] = s[6]; t[7] = s[7];
		t += 8;
		s += 8;
	}
	if(len & 4) {
		t[0] = s[0]; t[1] = s[1]; t[2] = s[2]; t[3] = s[3];
		t += 4;
		s += 4;
	}
	if(len & 2) {
		t[0] = s[0]; t[1] = s[1];
		t += 2;
		s += 2;
	}
	if(len & 1)
		t[0] = s[0];
}

void Check(void (*copy)(void *t, const void *s, size_t len))
{
	RTIMING("Check");
	Buffer<byte> b0(2000, 0), b1(2000, 0), b2(2000, 0);
	for(int i = 0; i < 500000; i++) {
		int pos = Random(200);
		int len = Random(200);
		memset(~b0 + pos, i, len);
		pos = Random(200);
		len = Random(200);
		copy(~b1 + pos, ~b0 + pos, len);
		memcpy(~b2 + pos, ~b0 + pos, len);
		if(memcmp(b1, b2, 2000)) {
			RDUMP(i);
			RDUMP(pos);
			RDUMP(len);
			Panic("Failed");
		}
	}
}

byte h[20000];

CONSOLE_APP_MAIN
{
	svo_memcpya(h + 20, h + 40, 14);
	
	Check(memcpy8);

	Buffer<byte> b1(200000);
	Buffer<byte> b2(200000);
	
	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(150);

	for(int i = 0; i < 100000; i++) {
		{
			RTIMING("memcpy");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("svo_memcpy");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memcpy((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("memcpy8");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy8((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("memcpy8a");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memcpy8a((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
	}
	{
		int bsize=8*1024*1024;
		Buffer<byte> b1(bsize, 0), b2(bsize, 0);
		dword cw = 123;
	
		String result="\"N\",\"memcpy8()\",\"memcpyd\"\r\n";
		for(int len=1;len<=bsize;){
			int maximum=100000000/len;
			int64 t0=usecs();
			for(int i = 0; i < maximum; i++)
				memcpy8(~b1, ~b2, len);
			int64 t1=usecs();
			for(int i = 0; i < maximum; i++)
				memcpy8a(~b1, ~b2, len);
			int64 t2=usecs();
			String r = Format("%d,%f,%f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
			RLOG(r);
			result.Cat(r + "\r\n");
			if(len<64) len++;
			else len*=2;
		}
		SaveFile(GetHomeDirFile("memset.csv"),result);
	}
}
