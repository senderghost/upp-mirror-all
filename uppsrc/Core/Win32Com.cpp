#include "Core.h"

#ifdef PLATFORM_POSIX
static const char clipboard_file[] = "/tmp/clipboard";
#endif//PLATFORM_POSIX

#ifdef PLATFORM_WIN32

static HINSTANCE app_instance;

HINSTANCE AppGetHandle()
{
	if(!app_instance)
		app_instance = GetModuleHandle(NULL);
	return app_instance;
}

void AppSetHandle(HINSTANCE dll_instance) { app_instance = dll_instance; }

bool IsWinXP()
{
	OSVERSIONINFO of;
	of.dwOSVersionInfoSize = sizeof(of);
	GetVersionEx(&of);
	return of.dwMajorVersion >= 5 && of.dwMinorVersion >= 1;
}

String AsString(const wchar_t *buffer) {
	if(!buffer)
		return Null;
	return AsString(buffer, wcslen(buffer));
}

String AsString(const wchar_t *buffer, int count) { // Convert with code page...
	if(!buffer)
		return Null;
	StringBuffer temp(count);
	for(char *p = temp, *e = p + count; p < e;)
		*p++ = (char)*buffer++;
	return temp;
}

String AsString(const wchar_t *buffer, const wchar_t *end) {
	if(!buffer)
		return Null;
	return AsString(buffer, end - buffer);
}

String GetWinRegString(const char *value, const char *path, HKEY base_key) {
	HKEY key = 0;
	if(RegOpenKeyEx(base_key, path, 0, KEY_READ, &key) != ERROR_SUCCESS)
		return String::GetVoid();
	dword type, data;
	if(RegQueryValueEx(key, value, 0, &type, NULL, &data) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		return String::GetVoid();
	}
	StringBuffer raw_data(data);
	if(RegQueryValueEx(key, value, 0, 0, (byte *)~raw_data, &data) != ERROR_SUCCESS)
	{
		RegCloseKey(key);
		return String::GetVoid();
	}
	if(data > 0 && (type == REG_SZ || type == REG_EXPAND_SZ))
		data--;
	raw_data.SetLength(data);
	RegCloseKey(key);
	return raw_data;
}

int GetWinRegInt(const char *value, const char *path, HKEY base_key) {
	HKEY key = 0;
	if(RegOpenKeyEx(base_key, path, 0, KEY_READ, &key) != ERROR_SUCCESS)
		return Null;
	int data;
	dword type, length = sizeof(data);
	if(RegQueryValueEx(key, value, 0, &type, (byte *)&data, &length) != ERROR_SUCCESS)
		data = Null;
	RegCloseKey(key);
	return data;
}

bool SetWinRegString(const String& string, const char *value, const char *path, HKEY base_key) {
	HKEY key = 0;
	if(RegCreateKeyEx(base_key, path, 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &key, NULL) != ERROR_SUCCESS)
		return false;
	bool ok = (RegSetValueEx(key, value, 0,	REG_SZ, string, string.GetLength() + 1) == ERROR_SUCCESS);
	RegCloseKey(key);
	return ok;
}

bool SetWinRegInt(int data, const char *value, const char *path, HKEY base_key)
{
	HKEY key = 0;
	if(RegCreateKeyEx(base_key, path, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL) != ERROR_SUCCESS)
		return false;
	bool ok = (RegSetValueEx(key, value, 0, REG_DWORD, (const byte *)&data, sizeof(data)) == ERROR_SUCCESS);
	RegCloseKey(key);
	return ok;
}

void DeleteWinReg(const String& key, HKEY base) {
	HKEY hkey;
	if(RegOpenKeyEx(base, key, 0, KEY_READ, &hkey) != ERROR_SUCCESS)
		return;
	Vector<String> subkeys;
	char temp[_MAX_PATH];
	dword len;
	for(dword dw = 0; len = sizeof(temp), RegEnumKeyEx(hkey, dw, temp, &len, 0, 0, 0, 0) == ERROR_SUCCESS; dw++)
		subkeys.Add(temp);
	RegCloseKey(hkey);
	while(!subkeys.IsEmpty())
		DeleteWinReg(key + '\\' + subkeys.Pop(), base);
	RegDeleteKey(base, key);
}

String GetModuleFileName(HINSTANCE instance) {
	char h[_MAX_PATH];
	GetModuleFileName(instance, h, _MAX_PATH);
	return h;
}

String GetSystemDirectory() {
	char temp[MAX_PATH];
	*temp = 0;
	GetSystemDirectory(temp, sizeof(temp));
	return temp;
}

String GetWindowsDirectory() {
	char temp[MAX_PATH];
	*temp = 0;
	GetWindowsDirectory(temp, sizeof(temp));
	return temp;
}

#endif
