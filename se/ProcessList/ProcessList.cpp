#include <Core/Core.h>
#include <tlhelp32.h>

using namespace Upp;

VectorMap<String, int> GetProcessList()
{
	VectorMap<String, int> pl;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if(hProcessSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &pe32))
			do
				pl.Add(pe32.szExeFile, pe32.th32ProcessID);
			while(Process32Next(hProcessSnap, &pe32));
		CloseHandle( hProcessSnap );
	}
	return pl;
}

CONSOLE_APP_MAIN
{
	DDUMPM(GetProcessList());
}
