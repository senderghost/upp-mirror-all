#include <Core/Core.h>

using namespace Upp;

#include <stdint.h>

/* The state must be seeded so that it is not everywhere zero. */
uint64_t s[16];
int p;

INITBLOCK {
	for(int i = 0; i < 16; i++)
		s[i] = Random64();
}

uint64_t xorshift1024star(void) {
   const uint64_t s0 = s[p];
   uint64_t s1 = s[p = (p + 1) & 15];
   s1 ^= s1 << 31; // a
   s[p] = s1 ^ s0 ^ (s1 >> 11) ^ (s0 >> 30); // b,c
   return s[p] * UINT64_C(1181783497276652981);
}

uint64_t xs128[2];

INITBLOCK {
	xs128[0] = Random();
	xs128[1] = Random();
}

uint64_t xorshift128plus(void) {
	uint64_t x = xs128[0];
	uint64_t const y = xs128[1];
	xs128[0] = y;
	x ^= x << 23; // a
	xs128[1] = x ^ y ^ (x >> 17) ^ (y >> 26); // b, c
	return xs128[1] + y;
}

uint32_t x, y, z, w;

INITBLOCK {
	x = Random();
	y = Random();
	z = Random();
	w = Random();
}

uint32_t xorshift128(void) {
    uint32_t t = x;
    t ^= t << 11;
    t ^= t >> 8;
    x = y; y = z; z = w;
    w ^= w >> 19;
    w ^= t;
    return w;
}

int      init;
uint32_t bias;

uint32_t xorshift128a(void) {
	if(init == 0) {
		x = Random();
		y = Random();
		z = Random();
		w = Random();
		bias = Random();
		init = INT_MAX;
	}
//	init--;
    uint32_t t = x;
    t ^= t << 11;
    t ^= t >> 8;
    x = y; y = z; z = w;
    w ^= w >> 19;
    w ^= t;
    return w ^ bias;
}

template <class I, class T, class L>
int FindLowerBound__(I v, int count, const T& val, const L& less = std::less<T>())
{
	int pos = 0;
	while(count > 0) {
		int half = count >> 1;
		int m = pos + half;
		if(less(v[m], val)) {
			pos = m + 1;
			count = count - half - 1;
		}
		else
			count = half;
	}
	return pos;
}

CONSOLE_APP_MAIN
{
	Vector<int> v;
	
	FindLowerBound__(v.begin(), v.GetCount(), 1, std::less<int>());
	
	DUMP(xorshift1024star());
	DUMP(xorshift1024star());
	DUMP(xorshift1024star());
	DUMP(xorshift1024star());

	{
		RTIMING("xorshift1024*");
		for(int i = 0; i < 100000000; i++)
			xorshift1024star();
	}
	{
		RTIMING("xorshift128+");
		for(int i = 0; i < 100000000; i++)
			xorshift128plus();
	}
	{
		RTIMING("Random");
		for(int i = 0; i < 100000000; i++)
			Random();
	}
	{
		RTIMING("Random 50");
		for(int i = 0; i < 100000000; i++)
			Random(50);
	}
	{
		RTIMING("xorshift128");
		for(int i = 0; i < 100000000; i++)
			xorshift128();
	}
	{
		RTIMING("xorshift128a");
		for(int i = 0; i < 100000000; i++)
			xorshift128a();
	}
}
