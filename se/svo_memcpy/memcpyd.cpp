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

inline
void svo_memcpy(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(len < 2) {
		if(len)
			t[0] = s[0];
		return;
	}
	if(len <= 4) {
		*(word *)t = *(word *)s;
		*(word *)(t + len - 2) = *(word *)(s + len - 2);
		return;
	}
	*(dword *)t = *(dword *)s;
	*(dword *)(t + len - 4) = *(dword *)(s + len - 4);
	if(len > 16) {
		svo_memcpy_l(t, s, len);
		return;
	}
	if(len > 8) {
		*(dword *)(t + 4) = *(dword *)(s + 4);
		*(dword *)(t + len - 8) = *(dword *)(s + len - 8);
	}
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

inline
void svo_memcpy0(void *p, void *q, size_t len)
{
	SVO_MEMCPY(p, q, len);
}

void Check(void (*copy)(void *t, void *s, size_t len))
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
	
	Check(svo_memcpy);
	Check(svo_memcpy0);
	Check(svo_memcpya);

#if 0
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
			RTIMING("svo_memcpya");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memcpya((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
		{
			RTIMING("svo_memcpy0");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memcpy0((dword *)~b1 + rnd[i], (dword *)~b2 + rnd[i], rnd[i + 1]);
		}
	}
#else
	int bsize=8*1024*1024;
	Buffer<byte> b1(bsize, 0), b2(bsize, 0);
	dword cw = 123;

	String result="\"N\",\"memcpy()\",\"memcpyd\"\r\n";
	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			svo_memcpya(~b1 + 1, ~b2 + 1, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			svo_memcpy(~b1 + 1, ~b2 + 1, len);
		int64 t2=usecs();
		String r = Format("%d,%f,%f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
		RLOG(r);
		result.Cat(r + "\r\n");
		if(len<64) len++;
		else len*=2;
	}
	SaveFile(GetHomeDirFile("memset.csv"),result);
#endif
	BeepInformation();
}
