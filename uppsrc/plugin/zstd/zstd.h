#ifndef _plugin_zstd_zstd_h_
#define _plugin_zstd_zstd_h_

#include <Core/Core.h>

#define ZSTD_STATIC_LINKING_ONLY
#include "common/zstd.h"

namespace Upp {

class ZstdCompressStream : public Stream  {
public:
	virtual   void  Close();
	virtual   bool  IsOpen() const;

protected:
	virtual   void  _Put(int w);
	virtual   void  _Put(const void *data, dword size);
	
	Stream      *out;
	
	Buffer<byte> buffer;
	Buffer<byte> outbuf;
	Buffer<int>  outsz;

	enum { BLOCK_BYTES = 1024*1024 };
	
	int           level;
	
	bool          concurrent;
    
    void          Alloc();
	void          Init();
	void          FlushOut();

public:
#ifdef _MULTITHREADED
	void Co(bool b = true);
#endif
	void Open(Stream& out, int level = 1);

	ZstdCompressStream();
	ZstdCompressStream(Stream& out, int level = 1) : ZstdCompressStream() { Open(out, level); }
	~ZstdCompressStream();
};

class ZstdDecompressStream : public Stream {
public:
	virtual   bool  IsOpen() const;

protected:
	virtual   int   _Term();
	virtual   int   _Get();
	virtual   dword _Get(void *data, dword size);

private:
	Stream        *in;
	struct Workblock {
		Buffer<char> c, d; // compressed, decompressed data
		int          clen = 0, dlen = 0; // compressed, decompressed len
		String       lc; // used when compressed length is too big
		bool         irregular_d = false; // d reallocated to accomodate bigger result
		
		void Clear() { c.Clear(); d.Clear(); lc.Clear(); }
	};
	Workblock wb[16];
	int       count; // count of workblocks fetched
	int       ii; // next workblock to be read
	int       dlen; // length of current workblock
	
	enum { BLOCK_BYTES = 1024*1024 }; // expected decompressed size
	
	int          maxblock;
	int          blockchksumsz;
	byte         lz4hdr;
	bool         eof;
	
	bool         concurrent;

    void          TryHeader();

	void          Init();
	bool          Next();
	void          Fetch();

public:	
	bool Open(Stream& in);

#ifdef _MULTITHREADED
	void Co(bool b = true)                                    { concurrent = b; }
#endif

	ZstdDecompressStream();
	ZstdDecompressStream(Stream& in) : ZstdDecompressStream() { Open(in); }
	~ZstdDecompressStream();
};

int64 ZstdCompress(Stream& out, Stream& in, EventGate<int64, int64> progress = false);
int64 ZstdDecompress(Stream& out, Stream& in, EventGate<int64, int64> progress = false);
String ZstdCompress(const void *data, int64 len, EventGate<int64, int64> progress = false);
String ZstdCompress(const String& s, EventGate<int64, int64> progress = false);
String ZstdDecompress(const void *data, int64 len, EventGate<int64, int64> progress = false);
String ZstdDecompress(const String& s, EventGate<int64, int64> progress = false);

#ifdef _MULTITHREADED
int64 CoZstdCompress(Stream& out, Stream& in, EventGate<int64, int64> progress = false);
int64 CoZstdDecompress(Stream& out, Stream& in, EventGate<int64, int64> progress = false);
String CoZstdCompress(const void *data, int64 len, EventGate<int64, int64> progress = false);
String CoZstdCompress(const String& s, EventGate<int64, int64> progress = false);
String CoZstdDecompress(const void *data, int64 len, EventGate<int64, int64> progress = false);
String CoZstdDecompress(const String& s, EventGate<int64, int64> progress = false);
#endif

bool IsZstd(Stream& s);

};

#endif
