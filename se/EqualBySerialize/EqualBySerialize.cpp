#include <Core/Core.h>

using namespace Upp;

struct CompareBySerializeStream : OutStream {
	virtual  void  Out(const void *data, dword size) {
	}

	struct ComparyBySerializeStream2 {
		virtual  void  Out(const void *data, dword size);
	};
};

CONSOLE_APP_MAIN
{
}
