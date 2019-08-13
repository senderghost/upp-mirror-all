#include <Core/Core.h>

using namespace Upp;

#ifdef PLATFORM_WIN32
String GetProcessPath(DWORD processId)
{
    String ret;
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId /* This is the PID, you can find one from windows task manager */
    );
    if(handle) {
        DWORD buffSize = 1024;
        CHAR buffer[1024];
        if(QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
            ret = buffer;
        CloseHandle(handle);
    }
    return ret;
}
#endif


#ifdef PLATFORM_POSIX
String GetProcessPath(int pid)
{
	Buffer<char> h(_MAX_PATH + 1);
	char link[100];
#ifdef PLATFORM_BSD
	sprintf(link, "/proc/%d/file", pid);
#else
	sprintf(link, "/proc/%d/exe", pid);
#endif
	int ret = readlink(link, h, _MAX_PATH);
	if(ret > 0 && ret < _MAX_PATH)
		h[ret] = '\0';
	else
		h[0] = '\0';
	return ~h;
}
#endif

CONSOLE_APP_MAIN
{
	DDUMP(GetProcessPath(30362));
	DDUMP(GetProcessPath(14300));
}
