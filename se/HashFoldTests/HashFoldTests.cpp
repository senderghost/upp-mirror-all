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
	return SwapEndian32(h * 2833151717);
//	return h - SwapEndian32((h << 5) - h);
}

inline dword FoldHash3(dword h)
{
	return 0x1b873593 * _rotl(h * 0xcc9e2d51, 15);
}

inline dword FoldHash4(dword h)
{
	h = SwapEndian32(h * 0x45d9f3b) ^ (h * 0x45d9f3b);
	return h;
}

dword FoldHash5(dword x)
{
    x = ((x >> 16) ^ x) * UINT32_C(0x45d9f3b);
    x = ((x >> 16) ^ x) * UINT32_C(0x45d9f3b);
    x = (x >> 16) ^ x;
    return x;
}

dword FoldHashT(dword x)
{
	return FoldHash2(x);
}

void NumberInfo(dword n)
{
	RLOG("====================================");
	RLOG(FormatIntHex(n));
	RLOG(n);
	RLOG(FormatIntBase(n, 2));
	int cnt = 0;
	for(dword b = 0x80000000; b; b >>= 1)
		cnt += !!(b & n);
	RLOG("Bit count: " << cnt);
}

CONSOLE_APP_MAIN
{
	NumberInfo(0x45d9f3b);
	NumberInfo(2833151717);
	NumberInfo(0x1b873593);
	NumberInfo(0xcc9e2d51);
	NumberInfo(0xa3613c16);
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
	
	RDUMP(FoldHash2(0xf0000000) & 255);
	RDUMP(FoldHash2(0xe0000000) & 255);

	RDUMP(FoldHash3(0xf0000000) & 255);
	RDUMP(FoldHash3(0xe0000000) & 255);

	RDUMP(FoldHash4(0xf0000000) & 255);
	RDUMP(FoldHash4(0xe0000000) & 255);

	RDUMP(FoldHash5(0xf0000000) & 255);
	RDUMP(FoldHash5(0xe0000000) & 255);
	
	for(auto& v : c)
		RLOG(v.GetCount() << " " << v);

	for(auto& v : c)
		for(int i = v.GetCount() - 1; i > 0; i--)
			v[i] -= v[i - 1];

	RLOG("==================");
	for(auto& v : c)
		RLOG(v.GetCount() << " " << v);
}
