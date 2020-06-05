#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
  MEMORYSTATUSEX statex;

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

	DDUMP(statex.dwMemoryLoad);
	DDUMP(statex.ullTotalPhys);
	DDUMP(statex.ullAvailPhys);
}

