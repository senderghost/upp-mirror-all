#include "Core.h"

#ifdef PLATFORM_WIN32
#define Ptr Ptr_
#define byte byte_
#define CY win32_CY_

#include <shellapi.h>
#include <wincon.h>
#include <shlobj.h>

#undef Ptr
#undef byte
#undef CY
#endif

NAMESPACE_UPP

#ifdef PLATFORM_WIN32


String GetEnv(const char *id)
{
	return WString(_wgetenv(WString(id))).ToString();
}

String GetExeFilePath()
{
	return GetModuleFileName();
}

String  GetHomeDirectory() {
	return GetEnv("HOMEDRIVE") + GetEnv("HOMEPATH");
}

#endif

#ifdef PLATFORM_POSIX

String GetEnv(const char *id)
{
	return FromSystemCharset(getenv(id));
}

char Argv0__[_MAX_PATH + 1];

static void sSetArgv0__(const char *title)
{
	strcpy(Argv0__, title);
}

extern char Argv0__[];

const char *procexepath_() {
	static char h[_MAX_PATH + 1];
	ONCELOCK {
		char link[100];
#ifdef PLATFORM_BSD
		sprintf(link, "/proc/%d/file", getpid());
#else
		sprintf(link, "/proc/%d/exe", getpid());
#endif
		int ret = readlink(link, h, _MAX_PATH);
		if(ret > 0 && ret < _MAX_PATH)
			h[ret] = '\0';
		else
			*h = '\0';
	}
	return h;
}

String GetExeFilePath()
{
	static String exepath;
	ONCELOCK {
		const char *exe = procexepath_();
		if(*exe)
			exepath = exe;
		else {
			String x = Argv0__;
			if(IsFullPath(x) && FileExists(x))
				exepath = x;
			else {
				exepath = GetHomeDirFile("upp");
				Vector<String> p = Split(FromSystemCharset(Environment().Get("PATH")), ':');
				if(x.Find('/') >= 0)
					p.Add(GetCurrentDirectory());
				for(int i = 0; i < p.GetCount(); i++) {
					String ep = NormalizePath(AppendFileName(p[i], x));
					if(FileExists(ep))
						exepath = ep;
				}
			}
		}
	}
	return exepath;
}

#endif

String GetExeDirFile(const char *filename)
{
	return AppendFileName(GetFileFolder(GetExeFilePath()), filename);
}

String GetExeTitle()
{
	return GetFileTitle(GetExeFilePath());
}

#ifdef PLATFORM_POSIX

static StaticCriticalSection sHlock;

String& sHomeDir() {
	static String s;
	return s;
}

String  GetHomeDirectory() {
	String r;
	INTERLOCKED_(sHlock) {
		String& s = sHomeDir();
		if(s.IsEmpty()) {
			s = Nvl(GetEnv("HOME"), "/root");
		}
		r = s;
	}
	return r;
}

void    SetHomeDirectory(const char *dir)
{
	INTERLOCKED_(sHlock) {
		sHomeDir() = dir;
	}
}

#endif//PLATFORM_POSIX

String  GetHomeDirFile(const char *fp) {
	return AppendFileName(GetHomeDirectory(), fp);
}

static bool sHomecfg;

void    UseHomeDirectoryConfig(bool b)
{
	sHomecfg = b;
}

String  ConfigFile(const char *file) {
#if defined(PLATFORM_WIN32)
	if(sHomecfg) {
		String p = GetHomeDirFile(GetExeTitle());
		ONCELOCK
			RealizeDirectory(p);
		return AppendFileName(p, file);
	}
	return GetExeDirFile(file);
#elif defined(PLATFORM_POSIX)
	String p = GetHomeDirFile(".upp/" + GetExeTitle());
	ONCELOCK
		RealizeDirectory(p);
	return AppendFileName(p, file);
#else
#error ConfigFile not implemented for this platform, comment this line to get input string back
	return file;
#endif//PLATFORM
}

String  ConfigFile() {
	return ConfigFile(GetExeTitle() + ".cfg");
}

GLOBAL_VAR(Vector<String>, coreCmdLine__)

const Vector<String>& CommandLine()
{
	return coreCmdLine__();
}

VectorMap<WString, WString>& EnvMap()
{
	static VectorMap<WString, WString> x;
	return x;
}

const VectorMap<String, String>& Environment()
{
	static VectorMap<String, String> *ptr = NULL;
	INTERLOCKED {
		static VectorMap<String, String> env;
		static int echrset;
		if(!ptr || GetDefaultCharset() != echrset) {
			env.Clear();
			echrset = GetDefaultCharset();
			for(int i = 0; i < EnvMap().GetCount(); i++)
				env.Add(EnvMap().GetKey(i).ToString(), EnvMap()[i].ToString());
			ptr = &env;
		}
	}
	return *ptr;
}

static int exitcode;
static bool sMainRunning;

void  SetExitCode(int code) { exitcode = code; }
int   GetExitCode()         { return exitcode; }

bool  IsMainRunning()
{
	return sMainRunning;
}

void LoadLangFiles(const char *dir)
{
	FindFile ff(AppendFileName(dir, "*.tr"));
	while(ff) {
		LoadLngFile(AppendFileName(dir, ff.GetName()));
		ff.Next();
	}
}

void CommonInit()
{
#ifdef PLATFORM_WIN32
	LoadLangFiles(GetFileFolder(GetExeFilePath()));
#else
	LoadLangFiles(GetHomeDirectory());
#endif

	Vector<String>& cmd = coreCmdLine__();
	for(int i = 0; i < cmd.GetCount();) {
		if(cmd[i] == "--export-tr") {
			{
				i++;
				int lang = 0;
				byte charset = CHARSET_UTF8;
				String fn = "all";
				if(i < cmd.GetCount())
					if(cmd[i].GetLength() != 4 && cmd[i].GetLength() != 5)
						lang = 0;
					else {
						lang = LNGFromText(cmd[i]);
						fn = cmd[i];
						int c = cmd[i][4];
						if(c >= '0' && c <= '8')
							charset = c - '0' + CHARSET_WIN1250;
						if(c >= 'A' && c <= 'J')
							charset = c - 'A' + CHARSET_ISO8859_1;
					}
				fn << ".tr";
			#ifdef PLATFORM_WIN32
				FileOut out(GetExeDirFile(fn));
			#else
				FileOut out(GetHomeDirFile(fn));
			#endif
				if(lang)
					SaveLngFile(out, SetLNGCharset(lang, charset));
				else {
					Index<int> l = GetLngSet();
					for(int i = 0; i < l.GetCount(); i++)
						SaveLngFile(out, SetLNGCharset(l[i], charset));
				}
			}
			exit(0);
		}
	#if defined(_DEBUG) && defined(UPP_HEAP)
		if(cmd[i] == "--memory-breakpoint__" && i + 1 < cmd.GetCount()) {
			MemoryBreakpoint(atoi(cmd[i + 1]));
			cmd.Remove(i, 2);
		}
		else
			i++;
	#else
		i++;
	#endif
	}
	sMainRunning = true;
}

#ifdef PLATFORM_POSIX

void s_ill_handler(int)
{
	Panic("Illegal instruction!");
}

void s_segv_handler(int)
{
	Panic("Invalid memory access!");
}

void s_fpe_handler(int)
{
	Panic("Invalid arithmetic operation!");
}

void AppInit__(int argc, const char **argv, const char **envptr)
{
	SetLanguage(LNG_ENGLISH);
	sSetArgv0__(argv[0]);
	for(const char *var; (var = *envptr) != 0; envptr++)
	{
		const char *b = var;
		while(*var && *var != '=')
			var++;
		String varname(b, var);
		if(*var == '=')
			var++;
		EnvMap().Add(varname.ToWString(), String(var).ToWString());
	}
	Vector<String>& cmd = coreCmdLine__();
	for(int i = 1; i < argc; i++)
		cmd.Add(argv[i]);
	CommonInit();
	signal(SIGILL, s_ill_handler);
	signal(SIGSEGV, s_segv_handler);
	signal(SIGBUS, s_segv_handler);
	signal(SIGFPE, s_fpe_handler);
}
#endif

#if defined(PLATFORM_WIN32)

void AppInitEnvironment__()
{
#ifndef PLATFORM_WINCE
	wchar *env = GetEnvironmentStringsW();
	for(wchar *ptr = env; *ptr; ptr++)
	{
		const wchar *b = ptr;
		if(*ptr)
			ptr++;
		while(*ptr && *ptr != '=')
			ptr++;
		WString varname(b, ptr);
		if(*ptr)
			ptr++;
		b = ptr;
		while(*ptr)
			ptr++;
		EnvMap().GetAdd(ToUpper(varname)) = WString(b, ptr);
	}
	FreeEnvironmentStringsW(env);
#endif
	CommonInit();
}

void AppInit__(int argc, const char **argv)
{
	SetLanguage(LNG_ENGLISH);
	Vector<String>& cmd = coreCmdLine__();
	for(int i = 1; i < argc; i++)
		cmd.Add(argv[i]);
	AppInitEnvironment__();
}
#endif

void AppExit__()
{
	sMainRunning = false;
#ifdef PLATFORM_POSIX
	MemoryIgnoreLeaksBegin(); // Qt leaks on app exit...
#endif
}

void    LaunchWebBrowser(const String& url)
{
#if defined(PLATFORM_WIN32) && !defined(PLATFORM_WINCE)
	ShellExecute(NULL, "open", url, NULL, ".", SW_SHOWDEFAULT);
#endif
#ifdef PLATFORM_POSIX
	const char * browser[] = {
		"htmlview", "xdg-open", "x-www-browser", "firefox", "konqueror", "opera", "epiphany", "galeon", "netscape"
	};
	for(int i = 0; i < __countof(browser); i++)
		if(system("which " + String(browser[i])) == 0) {
			system(String(browser[i]) + " " + url + " &");
			break;
		}
#endif
}

String GetDataFile(const char *filename)
{
	String s = GetEnv("UPP_MAIN__");
	return s.GetCount() ? AppendFileName(s, filename) : GetExeDirFile(filename);
}

String GetComputerName()
{
	char temp[256];
	*temp = 0;
#if defined(PLATFORM_WIN32)
	dword w = 255;
	::GetComputerNameA(temp, &w);
#else
	gethostname(temp, sizeof(temp));
#endif
	return FromSystemCharset(temp);
}

String GetUserName()
{
	char temp[256];
	*temp = 0;
#if defined(PLATFORM_WIN32)
	dword w = 255;
	::GetUserNameA(temp, &w);
	return FromSystemCharset(temp);
#else
	return Nvl(GetEnv("USER"), "boot");
#endif
}

String GetDesktopManager()
{
#if defined(PLATFORM_WIN32) && !defined(PLATFORM_WINCE)
	return "windows";
#endif
#ifdef PLATFORM_POSIX
    if(GetEnv("GNOME_DESKTOP_SESSION_ID").GetCount())
		return "gnome";
	if(GetEnv("KDE_FULL_SESSION").GetCount() || GetEnv("KDEDIR").GetCount())
        return "kde"; 
	return GetEnv("DESKTOP_SESSION");
#endif	
}

#if defined(PLATFORM_WIN32)

String GetShellFolder(int clsid) 
{
	wchar path[MAX_PATH];
	if(SHGetFolderPathW(NULL, clsid, NULL, SHGFP_TYPE_CURRENT, path) == S_OK)
		return FromUnicodeBuffer(path);
	return Null;
}

String GetDesktopFolder()	{ return GetShellFolder(CSIDL_DESKTOP); }
String GetProgramsFolder()	{ return GetShellFolder(CSIDL_PROGRAM_FILES); }
String GetAppDataFolder()	{ return GetShellFolder(CSIDL_APPDATA);}
String GetMusicFolder()		{ return GetShellFolder(CSIDL_MYMUSIC);}
String GetPicturesFolder()	{ return GetShellFolder(CSIDL_MYPICTURES);}
String GetVideoFolder()		{ return GetShellFolder(CSIDL_MYVIDEO);}
String GetDocumentsFolder()	{ return GetShellFolder(CSIDL_MYDOCUMENTS);}
String GetTemplatesFolder()	{ return GetShellFolder(CSIDL_TEMPLATES);}

#define MY_DEFINE_KNOWN_FOLDER(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
static const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

MY_DEFINE_KNOWN_FOLDER(MY_FOLDERID_Downloads, 0x374de290, 0x123f, 0x4565, 0x91, 0x64, 0x39, 0xc4, 0x92, 0x5e, 0x46, 0x7b);

String GetDownloadFolder()	
{
	static HRESULT (STDAPICALLTYPE * SHGetKnownFolderPath)(const void *rfid, DWORD dwFlags, HANDLE hToken, PWSTR *ppszPath);
	ONCELOCK {
		DllFn(SHGetKnownFolderPath, "shell32.dll", "SHGetKnownFolderPath");
	}
	if(SHGetKnownFolderPath) {
		PWSTR path = NULL;
		if(SHGetKnownFolderPath(&MY_FOLDERID_Downloads, 0, NULL, &path) == S_OK && path) {
			String s = FromUnicodeBuffer(path, wstrlen(path));
			CoTaskMemFree(path);
			return s;
		}
	}
	return Null;
};
#endif

#ifdef PLATFORM_POSIX

String GetPathXdg(String xdgConfigHome, String xdgConfigDirs)
{
	String ret = "";
	if (FileExists(ret = AppendFileName(xdgConfigHome, "user-dirs.dirs"))) ;
  	else if (FileExists(ret = AppendFileName(xdgConfigDirs, "user-dirs.defaults"))) ;
  	else if (FileExists(ret = AppendFileName(xdgConfigDirs, "user-dirs.dirs"))) ;
  	return ret;
}

String GetPathDataXdg(String fileConfig, const char *folder) 
{
	TextSettings settings;
	settings.Load(fileConfig);
	String v = settings.Get(folder);
	if(*v == '\"')
		v = v.Mid(1);
	if(*v.Last() == '\"')
		v.Trim(v.GetCount() - 1);
	String r;
	const char *s = v;
	while(*s) {
		if(*s == '$') {
			CParser p(s + 1);
			p.NoSkipSpaces();
			p.Spaces();
			if(p.IsId()) {
				String id = p.ReadId();
				r.Cat(GetEnv(id));
				s = p.GetPtr();
			}
			else {
				r.Cat('$');
				s++;
			}
		}
		else
			r.Cat(*s++);
	}
	return r;
}

String GetShellFolder(const char *local, const char *users) 
{
 	String xdgConfigHome = GetEnv("XDG_CONFIG_HOME");
  	if (xdgConfigHome == "")		// By default
  		xdgConfigHome = AppendFileName(GetHomeDirectory(), ".config");
  	String xdgConfigDirs = GetEnv("XDG_CONFIG_DIRS");
  	if (xdgConfigDirs == "")			// By default
  		xdgConfigDirs = "/etc/xdg";
  	String xdgFileConfigData = GetPathXdg(xdgConfigHome, xdgConfigDirs);
  	String ret = GetPathDataXdg(xdgFileConfigData, local);
  	if (ret == "" && *users != '\0')
  		return GetPathDataXdg(xdgFileConfigData, users);
  	else
  		return ret;
}

String GetDesktopFolder()
{
	String ret = GetShellFolder("XDG_DESKTOP_DIR", "DESKTOP");
	if (ret.IsEmpty())
		return AppendFileName(GetHomeDirectory(), "Desktop");
	else
		return ret;
}

String GetProgramsFolder()  { return String("/usr/bin"); }
String GetAppDataFolder()   { return GetHomeDirectory(); }
String GetMusicFolder()	    { return GetShellFolder("XDG_MUSIC_DIR", "MUSIC"); }
String GetPicturesFolder()  { return GetShellFolder("XDG_PICTURES_DIR", "PICTURES"); }
String GetVideoFolder()     { return GetShellFolder("XDG_VIDEOS_DIR", "VIDEOS"); }
String GetDocumentsFolder() { return GetShellFolder("XDG_DOCUMENTS_DIR", "DOCUMENTS"); }
String GetTemplatesFolder() { return GetShellFolder("XDG_TEMPLATES_DIR", "XDG_TEMPLATES_DIR"); }
String GetDownloadFolder()  { return GetShellFolder("XDG_DOWNLOAD_DIR", "XDG_DOWNLOAD_DIR"); }

#endif

END_UPP_NAMESPACE
