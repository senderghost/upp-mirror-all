#include <Core/Core.h>

using namespace Upp;

never_inline
void memmove_l(void *t, const void *s, size_t len)
{
	memmove(t, s, len);
}

inline
void memmove8(void *p, const void *q, size_t len)
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
			dword a = *(dword *)(s + 4);
			dword b = *(dword *)(s + len - 4);
			*(dword *)(t + 4) = a;
			*(dword *)(t + len - 4) = b;
			return;
		}
		uint64 a = *(uint64 *)s;
		uint64 b = *(uint64 *)(s + len - 8);
		*(uint64 *)t = a;
		*(uint64 *)(t + len - 8) = b;
		return;
	}
	memmove_l(p, q, len);
}
/*
never_inline
void memmove8(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(t < s) {
		while(len >= 16) {
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			t += 16;
			s += 16;
			len -= 16;
		}
		if(len & 8) {
			*(qword *)s = *(qword *)t;
			t += 8;
			s += 8;
		}
		if(len & 4) {
			*(dword *)s = *(dword *)t;
			t += 4;
			s += 4;
		}
		if(len & 2) {
			*(word *)s = *(word *)t;
			t += 2;
			s += 2;
		}
		if(len & 1)
			*s = *t;
	}
	else {
		t += len;
		s += len;
		while(len >= 16) {
			t -= 16;
			s -= 16;
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			len -= 16;
		}
		if(len & 8) {
			t -= 8;
			s -= 8;
			*(qword *)s = *(qword *)t;
		}
		if(len & 4) {
			t -= 4;
			s -= 4;
			*(dword *)s = *(dword *)t;
		}
		if(len & 2) {
			t -= 2;
			s -= 2;
			*(word *)s = *(word *)t;
		}
		if(len & 1)
			*--s = *--t;
	}
}
*/
never_inline
void memmove32(void *p, const void *q, size_t len)
{
	dword *t = (dword *)p;
	dword *s = (dword *)q;
	if(t < s) {
		while(len >= 4) {
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			t += 4;
			s += 4;
			len -= 4;
		}
		if(len & 2) {
			*(qword *)s = *(qword *)t;
			t += 2;
			s += 2;
		}
		if(len & 1)
			*(dword *)s = *(dword *)t;
	}
	else {
		t += len;
		s += len;
		while(len >= 4) {
			t -= 4;
			s -= 4;
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			len -= 4;
		}
		if(len & 2) {
			t -= 2;
			s -= 2;
			*(qword *)s = *(qword *)t;
		}
		if(len & 1)
			*(dword *)--s = *(dword *)--t;
	}
}

never_inline
void memmove64(void *p, const void *q, size_t len)
{
	qword *t = (qword *)p;
	qword *s = (qword *)q;
	if(t < s) {
		while(len >= 2) {
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			t += 2;
			s += 2;
			len -= 2;
		}
		if(len & 1)
			*(qword *)s = *(qword *)t;
	}
	else {
		t += len;
		s += len;
		while(len >= 2) {
			t -= 2;
			s -= 2;
			_mm_storeu_si128((__m128i *)t, _mm_loadu_si128((__m128i *)s));
			len -= 2;
		}
		if(len & 1)
			*(qword *)--s = *(qword *)--t;
	}
}

never_inline
void memmove128(void *p, const void *q, size_t len)
{
	dqword *t = (dqword *)p;
	dqword *s = (dqword *)q;
	if(t < s) {
		while(len) {
			_mm_storeu_si128((__m128i *)t++, _mm_loadu_si128((__m128i *)s++));
			len--;
		}
	}
	else {
		t += len;
		s += len;
		while(len) {
			_mm_storeu_si128((__m128i *)--t, _mm_loadu_si128((__m128i *)--s));
			len--;
		}
	}
}


byte b1[2000], b2[2000];

CONSOLE_APP_MAIN
{
	for(int i = 0; i < 1000000; i++) {
		for(int i = 0; i < 100; i++) {
			int pos = Random(2000);
			int val = Random(256);
			b1[pos] = b2[pos] = val;
		}
		Vector<int> n;
		for(int i = 0; i < 100; i++) {
			n.Add(Random(1000));
			n.Add(Random(1000));
			n.Add(Random(20));
		}
		{
			RTIMING("memmove");
			int q = 0;
			for(int j = 0; j < 100; j++) {
				int pos1 = n[q++];
				int pos2 = n[q++];
				int len = n[q++];
				memmove(b1 + pos1, b1 + pos2, len);
				memmove(b1 + pos2, b1 + pos1, len);
			}
		}
		{
			RTIMING("svo_memmove");
			int q = 0;
			for(int j = 0; j < 100; j++) {
				int pos1 = n[q++];
				int pos2 = n[q++];
				int len = n[q++];
				memmove8(b2 + pos1, b2 + pos2, len);
				memmove8(b2 + pos2, b2 + pos1, len);
			}
		}
	}
}
