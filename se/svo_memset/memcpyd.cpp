#include <Core/Core.h>

using namespace Upp;

never_inline
void svo_memset_l(byte *t, dword val4, int len)
{
	const byte *e = t + len;
	t = (byte *)(((uintptr_t)t | 3) + 1);
	len = e - t;
	memsetd(t, val4, len >> 2);
}

inline
void svo_memset(void *p, byte val, int len)
{
	byte *t = (byte *)p;
	if(len < 2) {
		if(len)
			t[0] = val;
		return;
	}
	dword val4 = 0x1010101 * val;
	if(len <= 4) {
		*(word *)t = *(word *)(t + len - 2) = val4;
		return;
	}
	*(dword *)t = *(dword *)(t + len - 4) = val4; // alignment & fill tail
	if(len > 16) {
		svo_memset_l(t, val4, len);
		return;
	}
	if(len > 8)
		*(dword *)(t + 4) = *(dword *)(t + len - 8) = val4;
}

inline
void svo_memsetxx(void *p, byte val, int len)
{
	byte *t = (byte *)p;
	if(len <= 4) {
		if(len > 1) {
			*(word *)t = *(word *)(t + len - 2) = MAKEWORD(val, val);
			return;
		}
		if(len)
			t[0] = val;
		return;
	}
	dword val4 = 0x1010101 * val;
	*(dword *)t = *(dword *)(t + len - 4) = val4; // alignment & fill tail
	if(len > 16) {
		svo_memset_l(t, val4, len);
		return;
	}
	if(len > 8)
		*(dword *)(t + 4) = *(dword *)(t + len - 8) = val4;
}

inline
void svo_memseta(void *p, byte val, int len)
{
	if(len >= 32) {
		memset(p, val, len);
		return;
	}
	byte *t = (byte *)p;
	while(len & 16) {
		t[0] = c; t[1] = c; t[2] = c; t[3] = c;
		t[4] = c; t[5] = c; t[6] = c; t[7] = c;
		t[8] = c; t[9] = c; t[10] = c; t[11] = c;
		t[12] = c; t[13] = c; t[14] = c; t[15] = c;
		t += 16;
		len -= 16;
	}
	if(len & 8) {
		t[0] = t[1] = t[2] = t[3] = t[4] = t[5] = t[6] = t[7] = c;
		t += 8;
	}
	if(len & 4) {
		t[0] = t[1] = t[2] = t[3] = c;
		t += 4;
	}
	if(len & 2) {
		t[0] = t[1] = c;
		t += 2;
	}
	if(len & 1)
		t[0] = c;
}

void svo_memset1(void *p, byte val, int len)
{
	SVO_MEMSET(p, val, len);
/*	byte *t = (byte *)p;
	if(len < 4) {
		if(len > 1) {
			t[0] = t[1] = t[len - 1] = val;
		}
		if(len)
			t[0] = val;
		return;
	}
	
	dword val4 = 0x1010101 * (byte)val;
	*(dword *)t = *(dword *)(t + len - 4) = val4; // alignment & fill tail
	if(len < 8)
		return;
	const byte *e = t + len;
	t = (byte *)(((uintptr_t)t | 3) + 1);
	len = e - t;
	memsetd(t, val4, len >> 2);*/
}

int len = 2000 * 4000;
int len2 = 7;
int len3 = 3;
int val3 = 12;

void CheckFill(void (*fill)(void *t, byte val, int len))
{
	RTIMING("CheckFill");
	Buffer<byte> b1(2000, 0), b2(2000, 0);
	for(int i = 0; i < 500000; i++) {
		int pos = Random(200);
		int len = Random(200);
		memset(~b1 + pos, i, len);
		fill(~b2 + pos, i, len);
		if(memcmp(b1, b2, 2000)) {
			RDUMPHEX(i);
			RDUMP(pos);
			RDUMP(len);
			RLOGHEXDUMP(b1, 500);
			RLOGHEXDUMP(b2, 500);
			Panic("Failed");
		}
	}
}

int cw = 123;

CONSOLE_APP_MAIN
{
	char h[50] = {0};

	cw++;
	
	svo_memset(h, '0', 10);

	RDUMP(h);
	
#if 0
	
	svo_memset(~b + 128, 123, 168);
	
	for(int i = 0; i < 500; i++)
		LOG(i << " " << b[i]);
#endif
	CheckFill(svo_memset);
	CheckFill(svo_memseta);

#if 1

	Buffer<byte> b(2000, 0);

	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(80);
	
	for(int i = 0; i < 1000000; i++) {
		{
			RTIMING("memset");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memset(~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("svo_memset");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memset(~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("svo_memseta");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memseta(~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("svo_memset1");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				svo_memset1(~b + rnd[i], cw, rnd[i + 1]);
		}
	}
#else

	int bsize=8*1024*1024;
	Buffer<byte> b(bsize, 0);

	String result="\"N\",\"memsetd()\",\"FillX()\"\r\n";
	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			memset(~b + 1, cw, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			svo_memseta(~b + 1, cw, len);
		int64 t2=usecs();
		String r = Format("%d,%f,%f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
		RLOG(r);
		result.Cat(r + "\r\n");
		if(len<64) len++;
		else len*=2;
	}
	
	SaveFile(GetHomeDirFile("memset.csv"),result);
#endif
	BeepExclamation();
	return;
}
