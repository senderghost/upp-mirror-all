#include <Core/Core.h>

#include <plugin/lz4/lz4.h>

using namespace Upp;

void Test(const char *fn)
{
	RLOG("==============");
	RLOG(fn);
	String h = LoadFile(fn);
	TimeStop tm;
	String c = FastCompress(h, h.GetCount());
	double secs = tm.Seconds();
	RLOG("Original size:   " << h.GetCount());
	RLOG("Compressed size: " << c.GetCount());
	RLOG("Compression:     " << 100.0 * c.GetCount() / h.GetCount() << "%");
	RLOG("Elapsed:         " << secs << " s");
	RLOG("Throughput:      " << h.GetCount() / secs / 1024 / 1024 << " MB/s");

	String w = FastDecompress(c);
	
	ASSERT(w == h);
	
	tm.Reset();
	SaveFile("c:/xxx/trash.lz4", c);
	RLOG("File save time:  " << tm << " s");
}

enum {
	LZ4F_MAGIC       = 0x184D2204,

	LZ4F_VERSIONMASK = 0b11000000,
	LZ4F_VERSION     = 0b01000000,
	LZ4F_BLOCKINDEPENDENCE = (1 << 5),
	LZ4F_BLOCKCHECKSUM     = (1 << 4),
	LZ4F_CONTENTSIZE       = (1 << 3),
	LZ4F_CONTENTCHECKSUM   = (1 << 2),
	
	LZ4F_MAXSIZEMASK      = 0x70,
    LZ4F_MAXSIZE_64KB     = 0x40,
    LZ4F_MAXSIZE_256KB    = 0x50,
    LZ4F_MAXSIZE_1024KB   = 0x60,
    LZ4F_MAXSIZE_4096KB   = 0x70,
};

void WriteLZ4F(FileOut& out, const char *s, size_t len)
{
	out.SetBufferSize(1024*1024);
	out.Put32le(LZ4F_MAGIC);
	
	byte h[2];
	h[0] = LZ4F_VERSION | LZ4F_BLOCKINDEPENDENCE | LZ4F_CONTENTCHECKSUM,
	h[1] = LZ4F_MAXSIZE_1024KB;
	out.Put(h, 2);
	out.Put(xxHash(h, 2) >> 8);
	
	const size_t maxblock = 1024 * 1024;

	Buffer<char> compressed(LZ4_compressBound(maxblock));
	
	xxHashStream xxh;
	
	while(len > 0) {
		int chunk = min(maxblock, len);
		int clen = LZ4_compress(s, compressed, chunk);
		xxh.Put(s, chunk);
		if(clen >= chunk) {
			out.Put32le(0x80000000 | chunk);
			out.Put(s, chunk);
		}
		else {
			out.Put32le(clen);
			out.Put(compressed, clen);
		}
		s += chunk;
		len -= chunk;
	}
	out.Put32le(0);
	out.Put32le(xxh.Finish());
}

bool DecodeLZ4F(Stream& out, Stream& in)
{
	if(in.Get32le() != LZ4F_MAGIC)
		return false;
	int hdr = in.Get();
	if(hdr < 0 || (hdr & LZ4F_VERSIONMASK) != LZ4F_VERSION)
		return false;
	if(!(hdr & LZ4F_BLOCKINDEPENDENCE))
		return false; // dependent blocks not supported
	int maxblock = in.Get();
	if(maxblock < 0)
		return false;
	maxblock = decode(maxblock & LZ4F_MAXSIZEMASK,
	                  LZ4F_MAXSIZE_64KB, 1024 * 64,
	                  LZ4F_MAXSIZE_256KB, 1024 * 256,
	                  LZ4F_MAXSIZE_1024KB, 1024 * 1024,
	                  LZ4F_MAXSIZE_4096KB, 1024 * 4096,
	                  -1);
	if(maxblock < 0)
		return false;
	if(hdr & LZ4F_CONTENTSIZE)
		in.Get64();
	
	in.Get(); // we just skip descriptor checksum (for now?)
	
	xxHashStream xxh;
	
	Buffer<char> src(maxblock);
	Buffer<char> dst(maxblock);
	
	for(;;) {
		if(in.IsEof())
			return false;
		int blen = in.Get32le();
		if(blen == 0)
			break;
		int len = blen & 0x7fffffff;
		if(len > maxblock || !in.GetAll(src, len))
			return false;
		if(blen & 0x80000000) {
			out.Put(src, len);
			xxh.Put(src, len);
		}
		else {
			int sz = LZ4_decompress_safe(src, dst, len, maxblock);
			if(sz < 0)
				return false;
			xxh.Put(dst, sz);
			out.Put(dst, sz);
		}
		if(hdr & LZ4F_BLOCKCHECKSUM)
			in.Get32(); // we just skip block checksup;
	}
	
	if((hdr & LZ4F_CONTENTCHECKSUM) && in.Get32le() != xxh.Finish())
		return false;
	return true;
}

String DecodeLZ4F(FileIn& in)
{
	StringStream out;
	if(DecodeLZ4F(out, in))
		return out.GetResult();
	return Null;
}

CONSOLE_APP_MAIN
{
	String lz4fn = "c:/xxx/lz4f_test.lz4";
	String h = LoadFile("C:/u/aws.data/EastDurham_GE_1p6-100_80mHH_14WTGs_BatCurtailment_11May16.blb");
	{
		FileOut out(lz4fn);
		TimeStop tm;
		WriteLZ4F(out, ~h, h.GetCount());
		RDUMP(tm);
		RDUMP(out.GetSize());
	}
	
	{
		TimeStop tm;
		FileIn in(lz4fn);
		String dh = DecodeLZ4F(in);
		ASSERT(dh == h);
		RDUMP(tm);
	}
	
	
	Lz4 lz4;

	RLOG("=============================");
	
/*	return;
	Test("C:/xxx/xml.xml");
	Test("C:/xxx/viking.json");
	Test("C:/xxx/SSVS.cpp");
	Test("C:/xxx/NOS-30.html");
	Test("C:/u/aws.data/Middelgrunden_WN_forMirek.blb");*/
	Test("C:/u/aws.data/EastDurham_GE_1p6-100_80mHH_14WTGs_BatCurtailment_11May16.blb");
/*	Test("C:/u/hodnocení_37179.xls");
	Test("C:/u/n-2016-137/uppsrc/ScatterCtrl/ScatterCtrl.cpp");*/
}
