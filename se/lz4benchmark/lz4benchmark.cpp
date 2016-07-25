#include <Core/Core.h>
#include <plugin/lz4/lz4.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	RDUMP(sizeof(ConditionVariable));

	FileIn in("C:/u/aws.data/BT2_Full2.blb");
#ifdef _DEBUG0
	String src = in.Get(32 * 1024*1024);
#else
	String src = in.Get(512 * 1024*1024);
#endif
	RDUMP(src.GetCount());
	
	String c, c1;
	{ RTIMING("Compress");
	c = LZ4Compress(src);
	}

	{ RTIMING("CoCompress");
	c1 = CoLZ4Compress(src);
	}
	
//	if(c != c1)
//		Panic("Error");
	
	String d, d1;

	{ RTIMING("Decompress");
	d = LZ4Decompress(c1);
	}

	{ RTIMING("CoDecompress");
	d1 = CoLZ4Decompress(c);
	}
	
	Buffer<byte> d3(src.GetCount());
	memset(d3, 1, src.GetCount());
	{
		RTIMING("Read");
		MemReadStream in(c, c.GetCount());
		LZ4DecompressStream ds(in);
		ds.Get(d3, src.GetCount());
	}
	{
		RTIMING("Co Read");
		MemReadStream in(c, c.GetCount());
		LZ4DecompressStream ds(in);
		ds.Concurrent();
		ds.Get(d3, src.GetCount());
	}
	
	{
		RTIMING("Co To file");
		StringStream ss(src);
		FileOut out("c:/xxx/out.lz4");
		LZ4CompressStream lz4(out);
		lz4.Concurrent();
		lz4.Put(ss);
	}

	{
		RTIMING("To file");
		StringStream ss(src);
		FileOut out("c:/xxx/out.lz4");
		LZ4CompressStream lz4(out);
		lz4.Put(ss);
	}
	
	{
		RTIMING("Save file");
		SaveFile("c:/xxx/out.raw", src);
	}
	
	{
		RTIMING("From file");
		FileIn in("c:/xxx/out.lz4");
		LZ4DecompressStream lz4(in);
		lz4.Get(d3, src.GetCount());
	}

	{
		RTIMING("Co From file");
		FileIn in("c:/xxx/out.lz4");
		LZ4DecompressStream lz4(in);
		lz4.Concurrent();
		lz4.Get(d3, src.GetCount());
	}
	
//	ASSERT(d1 == src);
//	ASSERT(d == src);
	
//	if(d != d1 || d != src)
//		Panic("error");
}
