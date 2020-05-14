#include <Core/Core.h>

using namespace Upp;

#ifdef PLATFORM_WIN32
#include <tlhelp32.h>

VectorMap<String, int> GetProcessList()
{
	VectorMap<String, int> pl;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap != INVALID_HANDLE_VALUE) {
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if(Process32First(hProcessSnap, &pe32))
			do {
				HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
				if(hModuleSnap != INVALID_HANDLE_VALUE) {
					MODULEENTRY32 me32;
					me32.dwSize = sizeof(MODULEENTRY32);
					if(Module32First(hModuleSnap, &me32))
						pl.Add(me32.szExePath, pe32.th32ProcessID);
					CloseHandle(hModuleSnap);
				}
			}
			while(Process32Next(hProcessSnap, &pe32));
		CloseHandle( hProcessSnap );
	}
	return pl;
}
#endif

#ifdef PLATFORM_POSIX

VectorMap<String, int> GetProcessList()
{
	VectorMap<String, int> pl;
	for(FindFile ff("/proc/*"); ff; ff.Next()) {
		String n = ff.GetName();
		if(IsDigit(*n)) {
			int pid = atoi(n);
			static char h[_MAX_PATH + 1];
			int ret = readlink(ff.GetPath() +
			#ifdef PLATFORM_BSD
				"/file"
			#else
				"/exe"
			#endif
			     , h, _MAX_PATH);
			if(ret > 0 && ret < _MAX_PATH) {
				h[ret] = '\0';
				pl.Add(h, pid);
			}
		}
	}
	return pl;
}

#endif

CONSOLE_APP_MAIN
{
	DDUMPM(GetProcessList());
	DLOG("============");
	VectorMap<String, int> m = GetProcessList();
	for(int i = 0; i < m.GetCount(); i++)
		if(GetFileTitle(m.GetKey(i)) == "theide")
			DDUMP(m[i]);
}
