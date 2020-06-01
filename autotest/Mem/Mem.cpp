#include <Core/Core.h>

using namespace Upp;

// TODO: Large array checks

const int MAX = 1024*1024*16;

template <class T, class FN>
void CheckEq(FN eq)
{
	LOG("CheckEq " << sizeof(T));
	T a[2000], b[2000];
	auto Rnd = [] { return (T)Random(26) + 'A'; };
	for(int i = 0; i < 100000; i++) {
		if(i % 10000 == 0)
			LOG(i);
		for(int j = 0; j < 2000; j++)
			a[j] = b[j] = Rnd();
		for(int j = 0; j < 1000; j++) {
			int pos = Random(1000);
			int len = Random(1000);
			if(eq(a + pos, b + pos, len) != !memcmp(a + pos, b + pos, sizeof(T) * len)) {
				RDUMP(i);
				RDUMP(pos);
				RDUMP(len);
				RDUMP(memcmp(a + pos, b + pos, sizeof(T) * len));
				RDUMP(eq(a + pos, b + pos, len));
				auto Read = [&](const T *p) {
					String s;
					for(int i = 0; i < len; i++)
						s.Cat((byte)p[i]);
					return s;
				};
				RDUMP(Read(a + pos));
				RDUMP(Read(b + pos));
				Panic("Failed");
			}
			b[Random(2000)] = Rnd();
		}
	}
}

template <class T, class FN>
void CheckCopy(FN copy)
{
	LOG("CheckCopy " << sizeof(T));
	Buffer<T> b0(MAX), b1(MAX), b2(MAX);
	memset(~b0, 0, MAX * sizeof(T));
	memset(~b1, 0, MAX * sizeof(T));
	memset(~b2, 0, MAX * sizeof(T));
	for(int pass = 0; pass < 5; pass++) {
		LOG(pass);
		for(int i = 0; i < (pass == 4 ? 100 : 500000); i++) {
			int pos = Random(200);
			int len = Random(decode(pass, 0, 20, 1, 200, 2, 2000, 3, 9999, 200)) + (pass == 4) * 7*1024*1024;
			memset(~b0 + pos, i, len * sizeof(T));
			pos = Random(200);
			len = Random(200);
			copy(~b1 + pos, ~b0 + pos, len);
			memcpy(~b2 + pos, ~b0 + pos, len * sizeof(T));
			if(memcmp(b1, b2, 20000)) {
				RDUMP(i);
				RDUMP(pos);
				RDUMP(len);
				Panic("Failed");
			}
		}
	}
}

template <class T, class FN>
void CheckFill(FN fill)
{
	LOG("CheckFill " << sizeof(T));
	Buffer<T> b1(20000, 0), b2(20000, 0);
	for(int pass = 0; pass < 4; pass++) {
		LOG(pass);
		for(int i = 0; i < 500000; i++) {
			int pos = Random(200);
			int len = Random(decode(pass, 0, 20, 1, 200, 2, 2000, 9999));
			fill(~b1 + pos, i, len);
			for(int j = 0; j < len; j++)
				b2[pos + j] = i;
			if(memcmp(b1, b2, sizeof(T) * 20000)) {
				RDUMP(i);
				RDUMP(pos);
				RDUMP(len);
				LOGHEXDUMP(b1 + pos - 4, sizeof(T) * len + 8);
				LOGHEXDUMP(b2 + pos - 4, sizeof(T) * len + 8);
				Panic("Failed");
			}
		}
	}
	LOG("HUGE");
	b1.Alloc(1024*1024*16, 0);
	b2.Alloc(1024*1024*16, 0);
	for(int i = 0; i < 100; i++) {
		int pos = Random(200);
		int len = 1024*1024*7 + Random(200);
		fill(~b1 + pos, i, len);
		for(int j = 0; j < len; j++)
			b2[pos + j] = i;
		if(memcmp(b1, b2, sizeof(T) * 1024*1024*16)) {
			RDUMP(i);
			RDUMP(pos);
			RDUMP(len);
			LOGHEXDUMP(b1 + pos - 8, 32 * sizeof(T));
			LOGHEXDUMP(b1 + pos + len - 8, 16 * sizeof(T));
			DLOG("===============");
			LOGHEXDUMP(b2 + pos - 8, 32 * sizeof(T));
			LOGHEXDUMP(b2 + pos + len - 8, 16 * sizeof(T));
			Panic("Failed");
		}
	}
}

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	CheckEq<byte>(memeq8);
	CheckEq<word>(memeq16);
	CheckEq<dword>(memeq32);
	CheckEq<uint64>(memeq64);

	CheckFill<byte>(memset8);
	CheckFill<word>(memset16);
	CheckFill<dword>(memset32);
	CheckFill<uint64>(memset64);

	struct dqword { qword x[2]; };
	CheckCopy<byte>(memcpy8);
	CheckCopy<word>(memcpy16);
	CheckCopy<dword>(memcpy32);
	CheckCopy<qword>(memcpy64);
	CheckCopy<dqword>(memcpy128);

	LOG("============= OK");
}
