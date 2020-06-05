#include <Core/Core.h>

using namespace Upp;

never_inline
hash_t memhash32(const void *ptr, size_t len)
{
	const byte *s = (byte *)ptr;
	dword val = HASH_CONST1;
	if(len >= 4) {
		if(len >= 48) {
			dword val1, val2, val3, val4;
			val1 = val2 = val3 = val4 = HASH_CONST1;
			while(len >= 16) {
				val1 = HASH_CONST2 * val1 + *(dword *)(s);
				val2 = HASH_CONST2 * val2 + *(dword *)(s + 4);
				val3 = HASH_CONST2 * val3 + *(dword *)(s + 8);
				val4 = HASH_CONST2 * val4 + *(dword *)(s + 12);
				s += 16;
				len -= 16;
			}
			val = HASH_CONST2 * val + val1;
			val = HASH_CONST2 * val + val2;
			val = HASH_CONST2 * val + val3;
			val = HASH_CONST2 * val + val4;
		}
		const byte *e = s + len - 4;
		while(s < e) {
			val = HASH_CONST2 * val + *(dword *)(s);
			s += 4;
		}
		return HASH_CONST2 * val + *(dword *)(e);
	}
	if(len >= 2) {
		val = HASH_CONST2 * val + *(word *)(s);
		val = HASH_CONST2 * val + *(word *)(s + len - 2);
		return val;
	}
	return len ? HASH_CONST2 * val + *s : val;
}

hash_t cw;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	byte p1[] = { 0x5A, 0x23, 0xBF, 0x73, 0xFF, 0x1F, 0xD5, 0xC0 };
	byte p2[] = { 0x5A, 0x23, 0xBF, 0x73, 0xB4, 0x1F, 0xD5, 0xC0 };

	int bsize=8*1024*1024;
	Buffer<byte> b(bsize, 0);
	for(int i = 0; i < bsize; i++)
		b[i] = Random() & 255;
	
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
			cw += memhash(~b, len);
		int64 t3=usecs();
		String r = Format("%d,%f,%f,%f", len, 1000.0*(t1-t0)/maximum, 1000.0*(t2-t1)/maximum, 1000.0*(t3-t2)/maximum);
		RLOG(r);
		if(len<64) len++;
		else len*=2;
	}
	return;
}
