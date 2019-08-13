#include <Core/Core.h>

using namespace Upp;

String GetProcessName(DWORD processId)
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

CONSOLE_APP_MAIN
{
	DDUMP(GetProcessName(14300));
}
