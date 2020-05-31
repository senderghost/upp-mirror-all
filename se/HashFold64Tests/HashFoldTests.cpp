#include <Core/Core.h>

using namespace Upp;

namespace Upp {
	int max_collisions;
};

inline dword FoldHash0(dword h)
{
	return h - SwapEndian32(h);
}

inline dword FoldHash2(dword h)
{
//	return SwapEndian32(2833151717 * h);

//	return 0x1b873593 * SwapEndian32(h * 0xcc9e2d51);
//	return 17895441 * SwapEndian32(h * 53731411);
	h = SwapEndian32(h * 0xd418553f);
	h = SwapEndian32(h * 0xa049e5bd);
	return h;
//	return h - SwapEndian32((h << 5) - h);
}

dword hash_const1;
dword hash_const2;
dword hash_const3;

inline dword FoldHash1(dword h)
{
	h = SwapEndian32(h * hash_const1);
	h = SwapEndian32(h * hash_const2);
	return h;
}

qword candidate;

inline dword FoldHash64(uint64 v)
{
	return (dword)SwapEndian64(candidate * v);
}

dword FoldHashT(dword x)
{
	return FoldHash64(x);
}

int PopCnt(qword n)
{
	int cnt = 0;
	for(qword b = 0x8000000000000000; b; b >>= 1)
		cnt += !!(b & n);
	return cnt;
}

void NumberInfo(qword n)
{
	RLOG("====================================");
	RLOG(Format64Hex(n));
	RLOG(n);
	RLOG("Bit count: " << PopCnt(n));
}

uint64 MakeHashNumber()
{
	qword w = I64(0x8000000000000001);
	while(PopCnt(w) < 32)
		w |= (qword)1 << Random(64);
	return w;
}

void Test(qword q)
{
	candidate = q;
	NumberInfo(candidate);
	Vector<int> porter;
	const int SEQ = 10;
	const int MAX = 3000000 * SEQ;
	const int JUMP = 100;
	for (int j = 0; j < MAX; j += JUMP)
		for (int i = j; i < j + SEQ; i++)
			porter.At(FoldHashT(i) & 0x3fffff, 0)++;
	RDUMP(Min(porter));
	RDUMP(Max(porter));
}

dword sum;

#define PRIME64_1 11400714785074694791ULL
#define PRIME64_2 14029467366897019727ULL
#define PRIME64_3  1609587929392839161ULL
#define PRIME64_4  9650029242287828579ULL
#define PRIME64_5  2870177450012600261ULL

CONSOLE_APP_MAIN
{
	/*
	NumberInfo(0x45d9f3b);
	NumberInfo(2833151717);
	NumberInfo(0x1b873593);
	NumberInfo(0xcc9e2d51);
	NumberInfo(0xa3613c16);
	*/

/*	
	hash_const1 = MakeHashNumber();
	hash_const2 = MakeHashNumber();
	hash_const3 = MakeHashNumber();
	NumberInfo(hash_const1);
	NumberInfo(hash_const2);
	NumberInfo(hash_const3);

	FoldHash1(0);
*/	

#ifndef _DEBUG
	RDUMP(hash_const1);
	SeedRandom(0);
	{
		Vector<int> data;
		for(int i = 0; i < 100000000; i++)
			data.Add(Random());

		RTIMING("Hash");
		for(int i = 0; i < 100000000; i++) {
			sum += FoldHashT(data[i]);
		}
	}
	return;
#endif

	Test(PRIME64_1);
	Test(PRIME64_2);
	Test(PRIME64_3);
	Test(PRIME64_4);
	Test(PRIME64_5);

	for(int i = 0; i < 10; i++) {
		Test(MakeHashNumber());
	}
	return;
/*
	Vector<int> counts;
	for(int h : porter)
		counts.At(h, 0)++;
	
	RDUMPC(counts);
	
	Vector<Vector<int>> c;
	for(int i = 0; i < 1000; i++)
		c.At(FoldHashT(i) & 31).Add(i);
	
	RDUMP(FoldHashT(0xf0000000) & 255);
	RDUMP(FoldHashT(0xe0000000) & 255);
	
	for(auto& v : c)
		RLOG(v.GetCount() << " " << v);

	for(auto& v : c)
		for(int i = v.GetCount() - 1; i > 0; i--)
			v[i] -= v[i - 1];

	RLOG("==================");
	for(auto& v : c)
		RLOG(v.GetCount() << " " << v);
	DDUMP(hash_const1);
	DDUMP(hash_const2);
*/
}
