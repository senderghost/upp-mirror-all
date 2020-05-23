#include <CtrlLib/CtrlLib.h>
#include <smmintrin.h>

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

void Fill3(RGBA *t, RGBA c, int len)
{
	__m128i val4 = _mm_set1_epi32(*(int*)&c);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	auto Set4S = [&](int at) { _mm_stream_si128((__m128i *)(t + at), val4); };
	if(len >= 16) {
		if(len > 1024*1024 / 16 && ((uintptr_t)t & 3) == 0) { // for really huge data, bypass the cache
			while((uintptr_t)t & 15) { // align to 16 bytes for SSE
				*t++ = c;
				len--;
			}
			do {
				Set4S(0);
				Set4S(4);
				Set4S(8);
				Set4S(12);
				t += 16;
				len -= 16;
			}
			while(len >= 16);
			_mm_sfence();
		}
		else
			do {
				Set4(0);
				Set4(4);
				Set4(8);
				Set4(12);
				t += 16;
				len -= 16;
			}
			while(len >= 16);
	}
	if(len & 8) {
		Set4(0);
		Set4(4);
		t += 8;
	}
	if(len & 4) {
		Set4(0);
		t += 4;
	}
	if(len & 2) {
		t[0] = t[1] = c;
		t += 2;
	}
	if(len & 1)
		t[0] = c;
}

void Fill3c(RGBA *t, RGBA c, int len)
{
	__m128i val4 = _mm_set1_epi32(*(int*)&c);
	auto Set2 = [&](int at) { t[0] = t[1] = c; };
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	auto Set4S = [&](int at) { _mm_stream_si128((__m128i *)(t + at), val4); };
	if(len >= 16) {
		if(len > 1024*1024 / 16 && ((uintptr_t)t & 3) == 0) { // for really huge data, bypass the cache
			while((uintptr_t)t & 15) { // align to 16 bytes for SSE
				*t++ = c;
				len--;
			}
			do {
				Set4S(0);
				Set4S(4);
				Set4S(8);
				Set4S(12);
				t += 16;
				len -= 16;
			}
			while(len >= 16);
			_mm_sfence();
		}
		else
			do {
				Set4(0);
				Set4(4);
				Set4(8);
				Set4(12);
				t += 16;
				len -= 16;
			}
			while(len >= 16);
	}
	int l1 = len & 1;
	if(len & 8) {
		Set4(0);
		Set4(4);
		if(len & 4) {
			Set4(8);
			if(len & 2) {
				Set2(12);
				t[13 + l1] = c;
				return;
			}
			t[11 + l1] = c;
			return;
		}
		if(len & 2) {
			Set2(8);
			t[9 + l1] = c;
			return;
		}
		t[7 + l1] = c;
		return;
	}
	if(len & 4) {
		Set4(0);
		if(len & 2) {
			Set2(4);
			t[7 + l1] = c;
			return;
		}
		t[3 + l1] = c;
		return;
	}
	if(len & 2) {
		Set2(0);
		t[1 + l1] = c;
		return;
	}
	if(len & 1) {
		t[0] = c;
	}
}

never_inline
void HugeFill(dword *t, dword c, int len)
{
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
	while(len--)
		*t++ = c;
	_mm_sfence();
}

void Fill6(dword *t, dword c, int len)
{
	if(len >= 4) {
		__m128i val4 = _mm_set1_epi32(*(int*)&c);
		auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
		if(len > 4*1024*1024 / 4) {
			HugeFill(t, c, len);
			return;
		}
		while(len >= 16) {
			Set4(0);
			Set4(4);
			Set4(8);
			Set4(12);
			t += 16;
			len -= 16;
		}
		if(len & 8) {
			Set4(0);
			Set4(8);
			t += 8;
		}
		if(len & 4) {
			Set4(0);
			t += 4;
		}
	}
	if(len)
		t[0] = t[(len & 2) >> 1] = t[(len & 2) & ((len & 1) << 1)] = c;
}

void Fill7(dword *t, dword data, int len){
	switch(len) {
		case 3: t[2] = data;
		case 2: t[1] = data;
		case 1: t[0] = data;
		case 0: return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	Set4(len - 4); // fill tail
	if(len >= 32) {
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			HugeFill(t, data, len);
			return;
		}
		const dword *e = t + len - 32;
		do {
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

void Fill7a(dword *t, dword data, int len){
	if(len < 4) {
		if(len & 2) {
			t[0] = t[1] = data;
			t += 2;
		}
		if(len & 1)
			t[0] = data;
		return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	Set4(len - 4); // fill tail
	if(len >= 32) {
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			HugeFill(t, data, len);
			return;
		}
		const dword *e = t + len - 32;
		do {
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

void Fill8(dword *t, dword data, int len){
	switch(len) {
		case 3: t[2] = data;
		case 2: t[1] = data;
		case 1: t[0] = data;
		case 0: return;
	}

	__m128i val4 = _mm_set1_epi32(data);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };

	Set4(len - 4); // fill tail
	if(len >= 32) {
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			HugeFill(t, data, len);
			return;
		}
		int cnt = len >> 5;
		do {
			Set4(0); Set4(4); Set4(8); Set4(12);
			len -= 32;
			Set4(16); Set4(20); Set4(24); Set4(28);
			t += 32;
		}
		while(len >= 32);
	}
	switch((len >> 2) & 7) {
	case 7: Set4(24);
	case 6: Set4(20);
	case 5: Set4(16);
	case 4: Set4(12);
	case 3: Set4(8);
	case 2: Set4(4);
	case 1: Set4(0);
	}
}

void Fill3a(RGBA *t, RGBA c, int len)
{
	__m128i val4 = _mm_set1_epi32(*(int*)&c);
	auto Set4A = [&](int at) { _mm_store_si128((__m128i *)(t + at), val4); }; // aligned
	auto Set4U = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); }; // unaligned
	auto Set4S = [&](int at) { _mm_stream_si128((__m128i *)(t + at), val4); }; // cache bypass
	if(len >= 32) {
		Set4U(0); // head alignment
		RGBA *t0 = t;
		t = (RGBA *)(((uintptr_t)t | 0xf) + 1);
		len += t - t0;
		if(len > 1024*1024 / 16) { // for really huge data, bypass the cache
			while(len >= 32) {
				Set4S(0); Set4S(4); Set4S(8); Set4S(12);
				Set4S(16); Set4S(20); Set4S(24); Set4S(28);
				t += 32;
				len -= 32;
			}
			_mm_sfence();
		}
		else
			while(len >= 32) {
				Set4A(0); Set4A(4); Set4A(8); Set4A(12);
				len -= 32;
				Set4A(16); Set4A(20); Set4A(24); Set4A(28);
				t += 32;
			}
	}
	if(len & 16) {
		Set4U(0); Set4U(4); Set4U(8); Set4U(12);
		t += 16;
	}
	if(len & 8) {
		Set4U(0); Set4U(4);
		t += 8;
	}
	if(len & 4) {
		Set4U(0);
		t += 4;
	}
	if(len & 2) {
		t[0] = t[1] = c;
		t += 2;
	}
	if(len & 1)
		t[0] = c;
}

void Fill4(RGBA *t, RGBA c, int len)
{
	__m128i val4 = _mm_set1_epi32(*(int*)&c);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	if(len >= 16) {
		RGBA *e = t + len;
		do {
			Set4(0);
			Set4(4);
			Set4(8);
			Set4(12);
			t += 16;
		}
		while(t < e);
	}
	auto Set2 = [&](int at) { t[at] = c; t[at + 1] = c; };
	auto Set1 = [&](int at) { t[at] = c; };
	switch(len & 15) {
	case 15: Set1(14);
	case 14: Set4(0); Set4(4); Set4(8); Set2(12); break;
	case 13: Set1(12);
	case 12: Set4(0); Set4(4); Set4(8); break;
	case 11: Set1(10);
	case 10: Set4(0); Set4(4); Set2(8); break;
	case 9: Set1(8);
	case 8: Set4(0); Set4(4); break;
	case 7: Set1(6);
	case 6: Set4(0); Set2(4); break;
	case 5: Set1(4);
	case 4: Set4(0); break;
	case 3: Set1(2);
	case 2: Set2(0); break;
	case 1: Set1(0);
	case 0: break;
	}
}

void Fill5(RGBA *t, RGBA c, int len)
{
	__m128i val4 = _mm_set1_epi32(*(int*)&c);
	auto Set4 = [&](int at) { _mm_storeu_si128((__m128i *)(t + at), val4); };
	auto Set1 = [&](int at) { t[at] = c; };
	while(len >= 16) {
		Set4(0);
		Set4(4);
		Set4(8);
		Set4(12);
		t += 16;
		len -= 16;
	}
	while(len >= 4) {
		Set4(0);
		t += 4;
		len -= 4;
	}
	while(len >= 0) {
		Set1(0);
		t++;
		len--;
	}
}

void Fill3T(void *b, dword data, int len){
	switch(len){
		case 3: ((dword *)b)[2] = data;
		case 2: ((dword *)b)[1] = data;
		case 1: ((dword *)b)[0] = data;
		case 0: return;
	}
	__m128i q = _mm_set1_epi32(*(int*)&data);
	__m128i *w = (__m128i*)b;
	
	if(len >= 32) {
		__m128i *e = (__m128i*)b + (len>>2) - 8;
		if(len >= 1024*1024) { // for really huge data, bypass the cache
			_mm_storeu_si128(w, q); // Head align
			int s=(-((int)((uintptr_t)b)>>2))&0x3;
			w = (__m128i*) ((dword*)b) + s;
			do {
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
				_mm_stream_si128(w++, q);
			}while(w<=e);
			_mm_sfence();
		}
		else
			do {
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
				_mm_storeu_si128(w++, q);
			}while(w<=e);
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
		_mm_storeu_si128(w, q);
	}
	_mm_storeu_si128((__m128i*) (((dword*)b) + len - 4), q); // Tail align
}

int len = 2000 * 4000;
int len2 = 7;

void CheckFill(void (*fill)(dword *t, dword val, int len))
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
	RGBA c = Red();
	dword cw = *((dword *)&c);
	
	CheckFill(Fill7);
	CheckFill(Fill7a);
	CheckFill(Fill8);
	
	Buffer<RGBA> b(2000);
	
	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(10);
	
//	Fill7a((dword *)~b, 7, len2);
	
	RDUMP(rnd);

	for(int i = 0; i < 1000000; i++) {
		{
			RTIMING("memsetd");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memsetd(b + rnd[i], *(dword*)&(c), rnd[i + 1]);
		}
		{
			RTIMING("Fill");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill0");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill0(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill2");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill2(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill3");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill3(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill3T");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill3T(b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("Fill6");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill6((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("Fill7");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill7((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("Fill7a");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill7a((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("Fill8");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill8((dword *)~b + rnd[i], cw, rnd[i + 1]);
		}
		{
			RTIMING("memset");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memset(b + 4 * rnd[i], c.r, 4 * rnd[i + 1]);
		}
	}
	
	return;

	b.Alloc(len);

	for(int i = 0; i < 20; i++) {
		memsetd(b, *(dword*)&(c), len);
		{
			RTIMING("HUGE memsetd");
			memsetd(b, *(dword*)&(c), len);
		}
		{
			RTIMING("HUGE Fill");
			Fill(b, c, len);
		}
		{
			RTIMING("HUGE Fill3");
			Fill3(b, c, len);
		}
		{
			RTIMING("HUGE memset");
			memset(b, c.r, len * 4);
		}
	}

	BeepExclamation();
}
