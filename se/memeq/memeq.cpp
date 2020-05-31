#include <Core/Core.h>

using namespace Upp;

inline
bool memeq8a(const void *p, const void *q, size_t len)
{
	const byte *t = (byte *)p;
	const byte *s = (byte *)q;
	if(len <= 4) {
		if(len < 2)
			return len ? t[0] == s[0] : true;
		return Peek16(s) == Peek16(t) && Peek16(s + len - 2) == Peek16(t + len - 2);
	}
	if(len <= 16) {
		if(len <= 8)
			return Peek32(s) == Peek32(t) && Peek32(s + len - 4) == Peek32(t + len - 4);
		return Peek64(s) == Peek64(t) && Peek64(s + len - 8) == Peek64(t + len - 8);
	}
	const byte *e = s + len - 8;
	if(Peek64(e) != Peek64(t + len - 8))
		return false;
	do {
		if(Peek64(s) != Peek64(t))
			return false;
		s += 8;
		t += 8;
	}
	while(s < e);
	return true;
}

bool memeq128a(const void *p, const void *q)
{
	auto Cmp128 = [&](int at) { return ; };
	return _mm_movemask_epi8(_mm_cmpeq_epi32(_mm_loadu_si128((__m128i *)p), _mm_loadu_si128((__m128i *)q))) == 0xffff;
}

bool memeq128b(const void *p, const void *q)
{
	const qword *t = (qword *)p;
	const qword *s = (qword *)q;
	return t[0] == s[0] && t[1] == s[1];
}

bool memeq128c(const void *p, const void *q)
{
	const qword *t = (qword *)p;
	const qword *s = (qword *)q;
	return ((t[0] ^ s[0]) | (t[1] ^ s[1])) == 0;
}

/*
inline
bool memeq8a(const void *p, const void *q, size_t l)
{
#ifdef CPU_64
	const qword *qa = (const qword *)p;
	const qword *qb = (const qword *)q;
	while(l >= 8) {
		if(*qa++ != *qb++) return false;
		l -= 8;
	}
	const dword *da = (const dword *)qa;
	const dword *db = (const dword *)qb;
	if((l & 4) && *da++ != *db++) return false;
#else
	const dword *da = (const dword *)p;
	const dword *db = (const dword *)q;
	while(l >= 4) {
		if(*da++ != *db++) return false;
		l -= 4;
	}
#endif
	const word *wa = (const word *)da;
	const word *wb = (const word *)db;
	if((l & 2) && *wa++ != *wb++) return false;
	return (l & 1) ? *(const char *)wa == *(const char *)wb : true;
}
*/

inline
bool memeq16(void *p, const void *q, size_t len)
{
	const word *t = (const word *)p;
	const word *s = (const word *)q;
	if(len < 2)
		return len ? t[0] == s[0] : true;
	if(len <= 4)
		return Peek32(s) == Peek32(t) && Peek32(s + len - 2) == Peek32(s + len - 2);
	if(len <= 8)
		return Peek64(s) == Peek64(t) && Peek64(s + len - 4) == Peek64(s + len - 4);
	return memeq8__(t, s, 2 * len);
}

inline
bool svo_memeq(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(len >= 8) {
		if(Peek64(s + len - 8) != Peek64(t + len - 8))
			return false;
		byte *e = s + len - 8;
		do {
			if(Peek64(s) != Peek64(t))
				return false;
			s += 8;
			t += 8;
		}
		while(s < e);
		return true;
	}
	if(len > 4)
		return ((Peek32(s) ^ Peek32(t)) | (Peek32(s + len - 4) ^ Peek32(t + len - 4))) == 0;
	if(len >= 2)
		return ((Peek16(s) ^ Peek16(t)) | (Peek16(s + len - 2) ^ Peek16(t + len - 2))) == 0;
	return len ? *s == *t : true;
}

inline
bool svo_memeq2(void *p, const void *q, size_t len)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	uint64 sum;
	while(len >= 8) {
		if(Peek64(s) != Peek64(t))
			return false;
		s += 8;
		t += 8;
		len -= 8;
	}
	if(len & 4) {
		if(Peek32(s) != Peek32(t))
			return false;
		s += 4;
		t += 4;
	}
	if(len & 2) {
		if(Peek16(s) != Peek16(t))
			return false;
		s += 2;
		t += 2;
	}
	return (len & 1) ? *s == *t : true;
}

int r1, r2, r3, r4, r5, rx;
byte a0[10000], b0[10000];

byte *a1 = a0;
byte *b1 = b0;

CONSOLE_APP_MAIN
{
	byte *a = a1;
	byte *b = b1;
	
	for(int i = 0; i < 10000; i++) {
		int q = Random(200);
		a[i] = b[i] = q;
//		if(Random(50))
//			b[i] = q;
	}
	for(int i = 0; i < 1000000; i++) {
		Vector<int> len;
		for(int j = 0; j < 100; j++)
			len.Add(Random(16) + 14);
		{
			RTIMING("svo_memeq");
			for(int i = 0; i < 100; i++)
				if(svo_memeq(a, b, len[i]))
					r1++;
		}
		{
			RTIMING("svo_memeq2");
			for(int i = 0; i < 100; i++)
				if(svo_memeq2(a, b, len[i]))
					r2++;
		}
		{
			RTIMING("memcmp");
			for(int i = 0; i < 100; i++)
				if(memcmp(a, b, len[i]) == 0)
					r3++;
		}
		{
			RTIMING("memeq8");
			for(int i = 0; i < 100; i++)
				if(memeq8(a, b, len[i]))
					r4++;
		}
		{
			RTIMING("memeq8a");
			for(int i = 0; i < 100; i++)
				if(memeq8a(a, b, len[i]))
					r5++;
		}
		{
			RTIMING("memeq128a");
			for(int i = 0; i < 1000; i++)
				if(memeq128a(a, b + i))
					rx++;
		}
		{
			RTIMING("memeq128b");
			for(int i = 0; i < 1000; i++)
				if(memeq128b(a, b + i))
					rx++;
		}
		{
			RTIMING("memeq128c");
			for(int i = 0; i < 1000; i++)
				if(memeq128c(a, b + i))
					rx++;
		}
		CHECK(r1 == r2);
		CHECK(r1 == r3);
		CHECK(r1 == r4);
		CHECK(r1 == r5);
	}
}
