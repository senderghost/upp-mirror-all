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
	uint64 val = HASH32_CONST1;
	if(len >= 8) {
		const byte *e = s + len - 8;
		while(s < e) {
			val = HASH32_CONST2 * val + *(qword *)(s);
			s += 8;
		}
		return HASH32_CONST2 * val + *(qword *)(e);
	}
	if(len > 4) {
		val = HASH32_CONST2 * val + *(dword *)(s);
		val = HASH32_CONST2 * val + *(dword *)(s + len - 4);
		return val;
	}
	if(len >= 2) {
		val = HASH32_CONST2 * val + *(word *)(s);
		val = HASH32_CONST2 * val + *(word *)(s + len - 2);
		return val;
	}
	return len ? HASH32_CONST2 * val + *s : val;
}

never_inline
hash_t memhash64(const void *ptr, size_t len)
{
	const byte *s = (byte *)ptr;
	uint64 val = HASH64_CONST1;
	if(len >= 8) {
		if(len >= 32) {
			uint64 val1, val2, val3, val4;
			val1 = val2 = val3 = val4 = HASH64_CONST1;
			while(len >= 32) {
				val1 = HASH64_CONST2 * val1 + *(qword *)(s);
				val2 = HASH64_CONST2 * val2 + *(qword *)(s + 8);
				val3 = HASH64_CONST2 * val3 + *(qword *)(s + 16);
				val4 = HASH64_CONST2 * val4 + *(qword *)(s + 24);
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

never_inline
hash_t memhash32(const void *ptr, size_t len)
{
	const byte *s = (byte *)ptr;
	dword val = HASH32_CONST1;
	if(len >= 4) {
		if(len >= 16) {
			dword val1, val2;
			val1 = val2 = HASH32_CONST1;
			while(len >= 8) {
				val1 = HASH32_CONST2 * val1 + *(dword *)(s);
				val2 = HASH32_CONST2 * val2 + *(dword *)(s + 4);
				s += 8;
				len -= 8;
			}
			val = HASH32_CONST2 * val + val1;
			val = HASH32_CONST2 * val + val2;
		}
		const byte *e = s + len - 4;
		while(s < e) {
			val = HASH32_CONST2 * val + *(dword *)(s);
			s += 4;
		}
		return HASH32_CONST2 * val + *(dword *)(e);
	}
	if(len >= 2) {
		val = HASH32_CONST2 * val + *(word *)(s);
		val = HASH32_CONST2 * val + *(word *)(s + len - 2);
		return val;
	}
	return len ? HASH32_CONST2 * val + *s : val;
}


never_inline
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


never_inline
hash_t memhash0(const void *ptr, size_t count)
{
	unsigned hash = 1234567890U;

	const unsigned *ds = (unsigned *)ptr;
	const unsigned *de = ds + (count >> 2);
	while(ds < de)
		hash = ((hash << 5) - hash) ^ *ds++;

	const byte *s = (byte *)ds;
	const byte *e = s + (count & 3);
	while(s < e)
		hash = ((hash << 5) - hash) ^ *s++;

	return hash;
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

	byte p1[] = { 0x5A, 0x23, 0xBF, 0x73, 0xFF, 0x1F, 0xD5, 0xC0 };
	byte p2[] = { 0x5A, 0x23, 0xBF, 0x73, 0xB4, 0x1F, 0xD5, 0xC0 };
	
	RDUMP(memhash64(p1, 8));
	RDUMP(memhash64(p2, 8));
	return;

	int bsize=8*1024*1024;
	Buffer<byte> b(bsize, 0);
	for(int i = 0; i < bsize; i++)
		b[i] = Random() & 255;
	
	cw += memhash3a(&b, len);

	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			cw += memhash(~b, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			cw += memhash32(~b, len);
		int64 t2=usecs();
		for(int i = 0; i < maximum; i++)
			cw += memhash64(~b, len);
		int64 t3=usecs();
		String r = Format("%d,%f,%f,%f", len, 1000.0*(t1-t0)/maximum, 1000.0*(t2-t1)/maximum, 1000.0*(t3-t2)/maximum);
		RLOG(r);
		if(len<64) len++;
		else len*=2;
	}
	return;
}
