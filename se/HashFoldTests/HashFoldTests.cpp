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

dword FoldHashT(dword x)
{
	return FoldHash1(x);
}

int PopCnt(dword n)
{
	int cnt = 0;
	for(dword b = 0x80000000; b; b >>= 1)
		cnt += !!(b & n);
	return cnt;
}

void NumberInfo(dword n)
{
	RLOG("====================================");
	RLOG(FormatIntHex(n));
	RLOG(n);
	RLOG(FormatIntBase(n, 2));
	RLOG("Bit count: " << PopCnt(n));
}

dword MakeHashNumber()
{
	dword w = 0x80000001;
	while(PopCnt(w) < 16)
		w |= 1 << Random(32);
	return w;
}

dword sum;

CONSOLE_APP_MAIN
{
	/*
	NumberInfo(0x45d9f3b);
	NumberInfo(2833151717);
	NumberInfo(0x1b873593);
	NumberInfo(0xcc9e2d51);
	NumberInfo(0xa3613c16);
	*/
	
	hash_const1 = MakeHashNumber();
	hash_const2 = MakeHashNumber();
	hash_const3 = MakeHashNumber();
	NumberInfo(hash_const1);
	NumberInfo(hash_const2);
	NumberInfo(hash_const3);

	FoldHash1(0);
	

#ifndef _DEBUG
	RDUMP(hash_const1);
	SeedRandom(0);
	{
		Vector<int> data;
		for(int i = 0; i < 100000000; i++)
			data.Add(Random());

		RTIMING("Hash");
		for(int i = 0; i < 100000000; i++) {
			sum += FoldHash1(data[i]);
		}
	}
	return;
#endif

	for(int i = 0; i < 20; i++)
		NumberInfo(MakeHashNumber());
	
	Vector<int> porter;
	const int SEQ = 10;
	const int MAX = 3000000 * SEQ;
	const int JUMP = 100;
	for (int j = 0; j < MAX; j += JUMP)
		for (int i = j; i < j + SEQ; i++)
			porter.At(FoldHashT(i) & 0x3fffff, 0)++;
	
	RDUMP(Min(porter));
	RDUMP(Max(porter));
	
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
}
