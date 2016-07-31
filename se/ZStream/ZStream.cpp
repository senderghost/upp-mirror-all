#include <Core/Core.h>
#include <plugin/lz4/lz4.h>

using namespace Upp;

class ZCompressStream : public OutFilterStream {
	Zlib         z;

public:
	void Open(Stream& out_);

	ZCompressStream();
	ZCompressStream(Stream& out) : LZ4CompressStream() { Open(out); }
};

CONSOLE_APP_MAIN
{
}
