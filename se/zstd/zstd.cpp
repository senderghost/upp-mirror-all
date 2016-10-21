#include <Core/Core.h>

using namespace Upp;

#define ZSTD_STATIC_LINKING_ONLY
#include <plugin/zstd/common/zstd.h>

#include <plugin/zstd/zstd.h>
#include <plugin/lz4/lz4.h>

#ifdef PLATFORM_POSIX
String infn = "/home/centrum/export.log";
String zstd = GetHomeDirFile("test.zst");
#else
String infn = "C:/xxx/log/local0.info";
String zstd = "c:/xxx/test.zst";
#endif

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	{
		FileOut out(zstd);
		ZstdCompressStream zstd(out);
//		FileIn in("C:/u/aws.data/BT2_Full.blb");
		FileIn in(infn);
		RTIMING("Compress");
		zstd.Put(in);
	}

	{
		FileOut out(ForceExt(zstd, ".out"));
		FileIn in(zstd);
		ZstdDecompressStream zstd(in);
		RTIMING("Decompress");
		out.Put(zstd);
	}

	{
		FileOut out(zstd);
		ZstdCompressStream zstd(out);
		zstd.Concurrent();
		FileIn in(infn);
		RTIMING("CoCompress");
		zstd.Put(in);
	}

	{
		FileOut out(ForceExt(zstd, ".out"));
		FileIn in(zstd);
		ZstdDecompressStream zstd(in);
		zstd.Concurrent();
		RTIMING("CoDecompress");
		out.Put(zstd);
	}
	
	String lz4 = ForceExt(zstd, ".lz4");

	{
		FileOut out(lz4);
		LZ4CompressStream lz4(out);
		lz4.Concurrent();
		FileIn in(infn);
		RTIMING("CoCompress LZ4");
		lz4.Put(in);
	}

	RDUMP(GetFileLength(zstd));
	RDUMP(GetFileLength(lz4));
}
