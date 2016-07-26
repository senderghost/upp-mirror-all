#include <Core/Core.h>

using namespace Upp;

#define ZSTD_STATIC_LINKING_ONLY
#include <plugin/zstd/common/zstd.h>

#include <plugin/zstd/zstd.h>
#include <plugin/lz4/lz4.h>

const char *zstd = "c:/xxx/zstd";

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

//	String s = LoadFile("C:/u/aws.data/EastDurham_GE_1p6-100_80mHH_14WTGs_BatCurtailment_11May16.blb");

#if 0
	int csz = ZSTD_compressBound(s.GetCount());
	
	RDUMP(s.GetLength());
	
	for(int i = 1; i < 2; i++) {
		RLOG("-------");
		RDUMP(i);
		Buffer<byte> c(csz);
		TimeStop tm;
		int len = ZSTD_compress(c, csz, s, s.GetCount(), i);
		RDUMP(tm);
		RDUMP(len);
		RDUMPHEX(String(~c, 16));
		RDUMP(ZSTD_getDecompressedSize(c, len));
		
		FileOut out(zstd);
		out.Put(c, len);
	}
#endif
	
	{
		FileOut out(zstd);
		ZstdCompressStream zstd(out);
//		FileIn in("C:/u/aws.data/BT2_Full.blb");
		FileIn in("C:/xxx/log/local0.info");
		RTIMING("Compress");
		zstd.Put(in);
	}

	{
		FileOut out(ForceExt(zstd, ".info"));
		FileIn in(zstd);
		ZstdDecompressStream zstd(in);
//		FileIn in("C:/u/aws.data/BT2_Full.blb");
		RTIMING("Decompress");
		out.Put(zstd);
	}

	{
		FileOut out(zstd);
		ZstdCompressStream zstd(out);
		zstd.Concurrent();
		FileIn in("C:/u/aws.data/BT2_Full.blb");
		RTIMING("CoCompress");
		zstd.Put(in);
	}

	{
		FileOut out(ForceExt(zstd, ".info"));
		FileIn in(zstd);
		ZstdDecompressStream zstd(in);
		zstd.Concurrent();
//		FileIn in("C:/u/aws.data/BT2_Full.blb");
		RTIMING("CoDecompress");
		out.Put(zstd);
	}
	
	String lz4 = ForceExt(zstd, ".lz4");

	{
		FileOut out(lz4);
		LZ4CompressStream lz4(out);
		lz4.Concurrent();
		FileIn in("C:/u/aws.data/BT2_Full.blb");
		RTIMING("CoCompress LZ4");
		lz4.Put(in);
	}

	RDUMP(GetFileLength(zstd));
	RDUMP(GetFileLength(lz4));
}
