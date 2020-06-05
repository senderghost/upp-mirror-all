#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{

#ifdef PLATFORM_POSIX
	int pgsz = getpagesize();
	DDUMP(sysconf (_SC_PHYS_PAGES) * pgsz >> 20);
	DDUMP(sysconf (_SC_AVPHYS_PAGES) * pgsz >> 20);
#else
  MEMORYSTATUSEX statex;

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

	DDUMP(statex.dwMemoryLoad);
	DDUMP(statex.ullTotalPhys);
	DDUMP(statex.ullAvailPhys);
#endif
}

