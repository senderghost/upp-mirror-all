#include <Core/Core.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/vm_statistics.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
	vm_statistics_data_t vmstat;
	if(KERN_SUCCESS != host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count))
		;

    int mib[2];
    int64_t physical_memory;
    size_t length;

    // Get the Physical memory size
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(int64_t);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    
    DDUMP(physical_memory);
/*
#ifdef PLATFORM_POSIX
	int pgsz = getpagesize();
	DDUMP(sysconf (_SC_PHYS_PAGES) * pgsz >> 20);
//	DDUMP(sysconf (_SC_AVPHYS_PAGES) * pgsz >> 20);
#else
  MEMORYSTATUSEX statex;

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

	DDUMP(statex.dwMemoryLoad);
	DDUMP(statex.ullTotalPhys);
	DDUMP(statex.ullAvailPhys);
#endif
*/
}

