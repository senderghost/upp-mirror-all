#include <Core/Core.h>

using namespace Upp;

inline
uint64 memhash2(const void *ptr, int len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	while(len >= 8) {
		val = HASH64_CONST2 * val + Peek64(s);
		s += 8;
		len -= 8;
	}
	if(len & 4) {
		val = HASH64_CONST2 * val + Peek32(s);
		s += 4;
	}
	if(len & 2) {
		val = HASH64_CONST2 * val + Peek16(s);
		s += 4;
	}
	if(len & 1)
		val = HASH64_CONST2 * val + *s;
	return val;
}

inline
uint64 memhash3(const void *ptr, int len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	if(len >= 8) {
		const byte *e = s + len - 8;
		do {
			val = HASH64_CONST2 * val + Peek64(s);
			s += 8;
		}
		while(s <= e);
	}
	if(len & 4) {
		val = HASH64_CONST2 * val + Peek32(s);
		s += 4;
	}
	if(len & 2) {
		val = HASH64_CONST2 * val + Peek16(s);
		s += 2;
	}
	if(len & 1)
		val = HASH64_CONST2 * val + *s;
	return val;
}

never_inline
uint64 memhash3a(const void *ptr, int len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	if(len >= 8) {
		const byte *e = s + len - 8;
		while(s < e) {
			val = HASH64_CONST2 * val + *(qword *)(s);
			s += 8;
		}
		return HASH64_CONST2 * val + *(qword *)(e);
	}
	if(len > 4) {
		val = HASH64_CONST2 * val + *(dword *)(s);
		val = HASH64_CONST2 * val + *(dword *)(s + len - 4);
		return val;
	}
	if(len >= 2) {
		val = HASH64_CONST2 * val + *(word *)(s);
		val = HASH64_CONST2 * val + *(word *)(s + len - 2);
		return val;
	}
	return len ? HASH64_CONST2 * val + *s : val;
}

never_inline
uint64 memhash3b(const void *ptr, int len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	if(len >= 8) {
		if(len >= 64) {
			uint64 val1, val2, val3, val4;
			val1 = val2 = val3 = val4 = HASH64_CONST1;
			while(len >= 32) {
				val1 = HASH64_CONST2 * val2 + *(qword *)(s);
				val2 = HASH64_CONST2 * val2 + *(qword *)(s + 8);
				val3 = HASH64_CONST2 * val2 + *(qword *)(s + 16);
				val4 = HASH64_CONST2 * val2 + *(qword *)(s + 24);
				s += 32;
				len -= 32;
			}
			val = HASH64_CONST2 * val + val1;
			val = HASH64_CONST2 * val + val2;
			val = HASH64_CONST2 * val + val3;
			val = HASH64_CONST2 * val + val4;
		}
		const byte *e = s + len - 8;
		while(s < e) {
			val = HASH64_CONST2 * val + *(qword *)(s);
			s += 8;
		}
		return HASH64_CONST2 * val + *(qword *)(e);
	}
	if(len > 4) {
		val = HASH64_CONST2 * val + *(dword *)(s);
		val = HASH64_CONST2 * val + *(dword *)(s + len - 4);
		return val;
	}
	if(len >= 2) {
		val = HASH64_CONST2 * val + *(word *)(s);
		val = HASH64_CONST2 * val + *(word *)(s + len - 2);
		return val;
	}
	return len ? HASH64_CONST2 * val + *s : val;
}


inline
uint64 memhash3c(const void *ptr, int len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	if(len >= 8) {
		const byte *e = s + len - 8;
		while(s < e) {
			val = HASH64_CONST2 * val + Peek64(s);
			s += 8;
		}
		return HASH64_CONST2 * val + Peek64(e);
	}
	if(len > 4) {
		val = HASH64_CONST2 * val + Peek32(s);
		val = HASH64_CONST2 * val + Peek32(s + len - 4);
		return val;
	}
	if(len >= 2) {
		val = HASH64_CONST2 * val + Peek16(s);
		val = HASH64_CONST2 * val + Peek16(s + len - 2);
		return val;
	}
	return len ? HASH64_CONST2 * val + *s : val;
}


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

uint64 cw = 123;
size_t len = 5;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	int bsize=8*1024*1024;
	Buffer<byte> b(bsize, 0);
	for(int i = 0; i < bsize; i++)
		b[i] = Random() & 255;
	
	cw += memhash3a(&b, len);

	String result="\"N\",\"memsetd()\",\"FillX()\"\r\n";
	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			cw += memhash3a(~b, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			cw += memhash3b(~b, len);
		int64 t2=usecs();
		String r = Format("%d,%f,%f",len,1000.0*(t1-t0)/maximum,1000.0*(t2-t1)/maximum);
		RLOG(r);
		result.Cat(r + "\r\n");
		if(len<64) len++;
		else len*=2;
	}
	return;
}
