#include <CtrlLib/CtrlLib.h>
#include <smmintrin.h>
#include <immintrin.h>

using namespace Upp;

void Fill0(RGBA *t, RGBA c, int len)
{
	while(len >= 16) {
		t[0] = c; t[1] = c; t[2] = c; t[3] = c;
		t[4] = c; t[5] = c; t[6] = c; t[7] = c;
		t[8] = c; t[9] = c; t[10] = c; t[11] = c;
		t[12] = c; t[13] = c; t[14] = c; t[15] = c;
		t += 16;
		len -= 16;
	}
	switch(len & 15) {
	case 15: t[14] = c;
	case 14: t[13] = c;
	case 13: t[12] = c;
	case 12: t[11] = c;
	case 11: t[10] = c;
	case 10: t[9] = c;
	case 9: t[8] = c;
	case 8: t[7] = c;
	case 7: t[6] = c;
	case 6: t[5] = c;
	case 5: t[4] = c;
	case 4: t[3] = c;
	case 3: t[2] = c;
	case 2: t[1] = c;
	case 1: t[0] = c;
	}
}

void Fill2(RGBA *t, RGBA c, int len)
{
	while(len >= 16) {
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

never_inline
void HugeFill(dword *t, dword c, int len)
{
	if(((uintptr_t)t & 3) == 0) {
		__m128i val4 = _mm_set1_epi32(*(int*)&c);
		auto Set4S = [&](int at) { _mm_stream_si128((__m128i *)(t + at), val4); };
		while((uintptr_t)t & 15) { // align to 16 bytes for SSE
			*t++ = c;
			len--;
		}
		while(len >= 16) {
			Set4S(0);
			Set4S(4);
			Set4S(8);
			Set4S(12);
			t += 16;
			len -= 16;
		}
		_mm_sfence();
	}
	while(len--)
		*t++ = c;
}

/*
inline
void FillX(dword *t, dword data, int len){
	if(len <= 4) {
		if(len) {
			if(len > 1) {
				uint64 val2 = (int64)I64(0x100000001) * (int)data;
				*(int64 *)t = val2;
				*(int64 *)(t + len - 2) = val2;
				return;
			}
			t[0] = data;
		}
		return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	for(;;) {
		Set4(0);
		Set4(len - 4);
		if(len <= 8)
			return;
		Set4(4);
		Set4(len - 8);
		if(len <= 16)
			return;
		Set4(8);
		Set4(len - 12);
		if(len <= 24)
			return;
		len -= 24;
		t += 12;
		if(len >= 32) {
			if(len >= 1024*1024) { // for really huge data, bypass the cache
				huge_memsetd(t, data, len);
				return;
			}
			
		}
	}
}
*/

never_inline
void large_fill(dword *t, dword data, int len)
{
	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	Set4(len - 4); // fill tail
	if(len >= 1024*1024) { // for really huge data, bypass the cache
		huge_memsetd(t, data, len);
		return;
	}
	const dword *e = t + len - 32;
	do {
		Set4(0); Set4(4); Set4(8); Set4(12);
		Set4(16); Set4(20); Set4(24); Set4(28);
		t += 32;
	}
	while(t <= e);
	if(len & 16) {
		Set4(0); Set4(4); Set4(8); Set4(12);
		t += 16;
	}
	if(len & 8) {
		Set4(0); Set4(4);
		t += 8;
	}
	if(len & 4)
		Set4(0);
}

inline
void FillX0(void *p, dword data, int len)
{
	dword *t = (dword *)p;
	if(len < 4) {
		if(len & 2) {
			t[0] = t[1] = t[len - 1] = data;
			return;
		}
		if(len & 1)
			t[0] = data;
		return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	Set4(len - 4); // fill tail
	if(len >= 32) {
		Set4(0);
		const dword *e = t + len;
		t = (dword *)(((uintptr_t)t | 15) + 1);
		len = e - t;
		e -= 32;
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			huge_memsetd(t, data, len);
			return;
		}
		while(t <= e) {
			Set4(0); Set4(4); Set4(8); Set4(12);
			Set4(16); Set4(20); Set4(24); Set4(28);
			t += 32;
		}
		while(t <= e);
	}
	if(len & 16) {
		Set4(0); Set4(4); Set4(8); Set4(12);
		t += 16;
	}
	if(len & 8) {
		Set4(0); Set4(4);
		t += 8;
	}
	if(len & 4)
		Set4(0);
}

__attribute__((target ("avx")))
never_inline
void memsetd_l2(dword *t, dword data, size_t len)
{
	__m128i val4 = _mm_set1_epi32(data);
	__m256i val8 = _mm256_set1_epi32(data);
	auto Set4 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	#define Set8(at) _mm256_storeu_si256((__m256i *)(t + at), val8);
	Set4(len - 4); // fill tail
	if(len >= 32) {
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			huge_memsetd(t, data, len);
			return;
		}
		Set8(0); // align up on 16 bytes boundary
		const dword *e = t + len;
		t = (dword *)(((uintptr_t)t | 31) + 1);
		len = e - t;
		e -= 32;
		while(t <= e) {
			Set8(0); Set8(8); Set8(16); Set8(24);
			t += 32;
		}
	}
	if(len & 16) {
		Set8(0); Set8(8);
		t += 16;
	}
	if(len & 8) {
		Set8(0);
		t += 8;
	}
	if(len & 4)
		Set4(0);
}

inline
void FillX(void *p, dword data, size_t len)
{
	dword *t = (dword *)p;
	if(len < 4) {
		if(len & 2) {
			t[0] = t[1] = t[len - 1] = data;
			return;
		}
		if(len & 1)
			t[0] = data;
		return;
	}

	if(len >= 16) {
		memsetd_l2(t, data, len);
		return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](size_t at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	Set4(len - 4); // fill tail
	if(len & 8) {
		Set4(0); Set4(4);
		t += 8;
	}
	if(len & 4)
		Set4(0);
}

inline
void Fill3T3(dword *b, dword data, int len){
	if(len<4){
		if(len&1) *b++ = data;
		if(len&2){ *b++ = data; *b++ = data; }
		return;
	}

	__m128i *w = (__m128i *)b;
	__m128i q = _mm_set1_epi32((int)data);

	if(len >= 32) {
		if(len>1024*1024 && (((uintptr_t)b & 3)==0)){
			HugeFill(b,data,len);
			return;
		}
		
		__m128i *e = w + (len>>2) - 7;
		do{
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
			_mm_storeu_si128(w++, q);
		}while(w<e);
	}
	if(len & 16) {
		_mm_storeu_si128(w++, q);
		_mm_storeu_si128(w++, q);
		_mm_storeu_si128(w++, q);
		_mm_storeu_si128(w++, q);
	}
	if(len & 8) {
		_mm_storeu_si128(w++, q);
		_mm_storeu_si128(w++, q);
	}
	if(len & 4) {
		_mm_storeu_si128(w++, q);
	}
	_mm_storeu_si128((__m128i*)(b + len - 4), q); // Tail align

}

int len = 2000 * 4000;
int len2 = 7;
int len3 = 3;
int val3 = 12;

void CheckFill(void (*fill)(void *t, dword val, size_t len))
{
	RTIMING("CheckFill");
	Buffer<dword> b1(2000, 0), b2(2000, 0);
	for(int i = 0; i < 500000; i++) {
		int pos = Random(200);
		int len = Random(200);
		memsetd(~b1 + pos, i, len);
		fill(~b2 + pos, i, len);
		if(memcmp(b1, b2, 2000 * sizeof(dword)))
			Panic("Failed");
	}
}


GUI_APP_MAIN
{
	{
		Buffer<dword> b(2000, 0);
		FillX(~b + 41, 123, 33);
		LOGHEXDUMP(b, 8000);
	}
	CheckFill(FillX);

#if 0
	RGBA c = Red();
	dword cw = *((dword *)&c);
	Buffer<RGBA> b(2000);

	FillX((dword *)~b, val3, len3);
	
//	CheckFill(memsetd);
//	CheckFill(Fill3T3);

	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(12);
	
	
//	Fill7a((dword *)~b, 7, len2);
	
	RDUMP(rnd);

	for(int i = 0; i < 1000000; i++) {
		{
			RTIMING("memsetd");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memsetd((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("FillX");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				FillX((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("Fill3T3");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill3T3((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
	}
#else

	int bsize=8*1024*1024;
	Buffer<dword> b(bsize, 0);
	dword cw = 123;

	String result="\"N\",\"memsetd()\",\"FillX()\"\r\n";
	for(int len=1;len<=bsize;){
		int maximum=100000000/len;
		int64 t0=usecs();
		for(int i = 0; i < maximum; i++)
			memsetd(~b + 1, cw, len);
		int64 t1=usecs();
		for(int i = 0; i < maximum; i++)
			FillX(~b + 1, cw, len);
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
