#include <Core/Core.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "lib/zstd.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	String s = LoadFile("C:/xxx/test.csv");
	int cbound = ZSTD_compressBound(s.GetCount());

	DDUMP(s.GetCount());
	DDUMP(cbound);

	Buffer<byte> dst(cbound);
	size_t res = ZSTD_compress(dst, cbound, s, s.GetCount() / 2, 1);

	size_t x = ZSTD_findFrameCompressedSize(dst, 0);
	
	DDUMP(ZSTD_isError(x));
	

	x = ZSTD_findFrameCompressedSize(dst, res);
	
	FileOut out("c:/xxx/test.zstd");
	out.Put(dst, res);

	res = ZSTD_compress(dst, cbound, ~s + s.GetCount() / 2, s.GetCount() - s.GetCount() / 2, 1);
	out.Put(dst, res);
	
	return;
	
	DDUMP(res);
	
//	size_t x = ZSTD_findFrameCompressedSize(dst, res);
//	DDUMP(x);
	
	size_t h = ZSTD_getFrameContentSize(dst, res);
	DDUMP(h);
	
	Buffer<byte> orig(h);
	
	size_t osz = ZSTD_decompress(orig, h, dst, x);
	DDUMP(osz);
	
	DDUMP(String(orig, osz) == s);
}
