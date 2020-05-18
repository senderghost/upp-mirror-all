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

void Fill3d(RGBA *t, RGBA c, int len)
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
	if(len >= 4) {
		Set4(0);
		int off = (len & 8) >> 1;
		Set4(off);
		off += (len & 4) << 1;
		Set4(off);
		off += len & 2;
		Set2(off);
		t[off + (len & 1)] = c;
		return;
	}
	if(len) {
		t[0] = c;
		int off = (len & 2) >> 1;
		t[off] = c;
		t[off + (len & 1)] = c;
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

inline void new_memset128(RGBA *t, RGBA data, int len){
	switch(len){
		case 4: t[3] = data;
		case 3: t[2] = data;
		case 2: t[1] = data;
		case 1: t[0] = data;
		case 0: return;
	}
	__m128i q = _mm_set1_epi32(*(int*)&data);
	__m128i *w = (__m128i*)t;
	
	switch(len>>2){
		default:{
			__m128i *e = (__m128i*)t + (len>>2) - 4;
			if(len <= 2*1024*1024 / 16){
				while(w<e){
					_mm_storeu_si128(w++, q);
					_mm_storeu_si128(w++, q);
					_mm_storeu_si128(w++, q);
					_mm_storeu_si128(w++, q);
				}
			}
			else{
				while(w<e){
					_mm_stream_si128(w++, q);
					_mm_stream_si128(w++, q);
					_mm_stream_si128(w++, q);
					_mm_stream_si128(w++, q);
				}
			}
		}
		case 4: _mm_storeu_si128(w++, q);
		case 3: _mm_storeu_si128(w++, q);
		case 2: _mm_storeu_si128(w++, q);
		case 1: _mm_storeu_si128(w++, q);
	}
	switch(len&3){
		case 3: t[len-3] = data;
		case 2: t[len-2] = data;
		case 1: t[len-1] = data;
	}
}

int len = 2000 * 4000;

GUI_APP_MAIN
{
	RGBA c = Red();
	
	Buffer<RGBA> b(2000);
	
	Vector<int> rnd;
	for(int i = 0; i < 200; i++)
		rnd << Random(100);
	
	RDUMP(rnd);

	for(int i = 0; i < 1000000; i++) {
		{
			RTIMING("memsetd");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				memsetd(b + rnd[i], *(dword*)&(c), rnd[i + 1]);
		}
		{
			RTIMING("new_memset128");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				new_memset128(b + rnd[i], c, rnd[i + 1]);
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
			RTIMING("Fill3d");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill3d(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill4");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill4(b + rnd[i], c, rnd[i + 1]);
		}
		{
			RTIMING("Fill5");
			for(int i = 0; i < rnd.GetCount(); i += 2)
				Fill5(b + rnd[i], c, rnd[i + 1]);
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
			RTIMING("HUGE newmemset128");
			new_memset128(b, c, len);
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
