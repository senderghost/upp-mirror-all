#ifndef _SysInfo_SysInfo_h
#define _SysInfo_SysInfo_h

#if defined(PLATFORM_WIN32) 
#include <vfw.h>
#endif

using namespace Upp;

/////////////////////////////////////////////////////////////////////
// Different functions

// Appends a file after other
bool FileCat(const char *file, const char *appendFile);

// Replace find with replace in str
String Replace(String str, String find, String replace);

// Convert a long into a String
String FormatLong(long a); 

// Search a file under dir with name with wildcards in condFile and with certain text inside.
// Errors are got in errorList 
Array<String> SearchFile(String dir, String condFile, String text, Array<String> &errorList);
Array<String> SearchFile(String dir, String condFile);

// As LoadFile but it works in Linux for files automatically generated by the OS
// #ifdef PLATFORM_POSIX 
String LoadFile_Safe(String fileName);
// #endif
// #if defined(PLATFORM_WIN32) 
// #define LoadFile_Safe LoadFile		// Not necessary in Windows
// #endif

#if defined(PLATFORM_WIN32) 
Value GetVARIANT(VARIANT &result);
#endif

// Gets the program that will open by default the files with extension ext
String GetExtExecutable(String ext);

// Open the file with the adecuated program defined in the OS by default
bool LaunchFile(const String file);

// Functions to launch command line programs
// readCallBack is a function to manage the program output
// Returns the command exit code
int LaunchCommand(const char *cmd, void (*readCallBack)(String &));
// ret gets all the program output
// Returns the command exit code
int LaunchCommand(const char *cmd, String &ret);
// It returns the program output
String LaunchCommand(const char *cmd);

// A ProcessEvents than can be used in non gui programs
inline void DoEvents()
{ 
#ifdef CTRLLIB_H
		Ctrl::ProcessEvents();
#endif
}

// A String based class to parse into
class StringParse :  public String {
public:
	void GoInit()	{pos = 0; lastSeparator='\0';};
	StringParse():String("") {GoInit();};
	StringParse(String s): String(s) {GoInit();};
	bool GoBefore(const String text)
	{
		int newpos = Find(text, pos);
		if (newpos < 0)
			return false;	// If it does not find it, it does not move
		pos = newpos;
		return true;
	};	
	bool GoAfter(const String text)
	{
		if(!GoBefore(text))
			return false;
		pos += strlen(text);
		return true;
	};
	bool GoAfter(const String text, const String text2)
	{
		if(!GoAfter(text))
			return false;
		if(!GoAfter(text2))
			return false;
		return true;
	};
	bool GoAfter(const String text, const String text2, const String text3)
	{
		if(!GoAfter(text))
			return false;
		if(!GoAfter(text2))
			return false;
		if(!GoAfter(text3))
			return false;
		return true;
	};
	bool GoAfter_Init(const String text) {GoInit();	return GoAfter(text);};
	bool GoAfter_Init(const String text, const String text2) {GoInit();	return GoAfter(text, text2);};
	bool GoAfter_Init(const String text, const String text2, const String text3) {GoInit();	return GoAfter(text, text2, text3);};		
	
	void GoBeginLine()
	{
		for (; pos >= 0; --pos) {
			if ((ToString()[pos-1] == '\r') || (ToString()[pos-1] == '\n'))
				return;
		} 
	}
	bool IsBeginLine()
	{
		if (pos == 0)
			return true;
		if ((ToString()[pos-1] == '\r') || (ToString()[pos-1] == '\n'))
			return true;
		return false;
	}
	bool IsSpaceRN(int c)
	{
		if (IsSpace(c))
			return true;
		if ((c == '\r') || (c == '\n'))
		     return true;
		return false;
	}
	// Gets text between "" or just a word until an space
	// It considers special characters with \ if between ""
	// If not between "" it gets the word when it finds one of the separator characters
	String GetText(String separators = "")	
	{
		String ret = "";
		if (pos > GetCount())
			return ret;
		int newpos = pos;
		
		while ((IsSpaceRN(ToString()[newpos]) && (ToString()[newpos] != '\"') && 
			   (ToString()[newpos] != '\0')))
			newpos++;
		if (ToString()[newpos] == '\0') {
			pos = newpos;
			return "";
		}
	
		if (ToString()[newpos] == '\"') {	// Between ""
			newpos++;
			while (ToString()[newpos] != '\"' && ToString()[newpos] != '\0') {
				if (ToString()[newpos] == '\\') {
					newpos++;
					if (ToString()[newpos] == '\0')
						return "";
				} 
				ret.Cat(ToString()[newpos]);
				newpos++;
			}
			lastSeparator = '"';
		} else if (separators == "") {		// Simple word
			while (!IsSpaceRN(ToString()[newpos]) && ToString()[newpos] != '\0') {
				if (ToString()[newpos] == '\"') {
					newpos--;	// This " belongs to the next
					break;
				}
				ret.Cat(ToString()[newpos]);
				newpos++;
			}
			lastSeparator = ToString()[newpos];
		} else {							// Simple word, special separator
			while (ToString()[newpos] != '\0') {// Only consider included spaces (!IsSpaceRN(ToString()[newpos]) && ToString()[newpos] != '\0') {
				if (ToString()[newpos] == '\"') {
					newpos--;	// This " belongs to the next
					break;
				}				
				if (separators.Find(ToString()[newpos]) >= 0) {
					lastSeparator = ToString()[newpos];
					break;
				}
				ret.Cat(ToString()[newpos]);
				newpos++;
			} 
			lastSeparator = ToString()[newpos];
		}
		pos = ++newpos;		// After the separator: ", space or separator
		return ret;
	}
	String GetLine()
	{
		return GetText("\r\n");
	}
	double GetDouble(String separators = "")  	{return atof(GetText(separators));};
	int GetInt(String separators = "")			{return atoi(GetText(separators));};
	long GetLong(String separators = "")		{return atol(GetText(separators));};
	uint64 GetUInt64(String separators = "")	
#if defined(PLATFORM_WIN32) 
	{return _atoi64(GetText(separators));};
#endif
#ifdef PLATFORM_POSIX
	{return atoll(GetText(separators));};
#endif
	
	String Right() {return String::Right(GetLength()-pos);}
	int GetLastSeparator() {return lastSeparator;}
	void MoveRel(int val)
	{
		pos += val;
		if (pos < 0)
			pos = 0;
		else if (pos >= GetCount())
			pos = GetCount() - 1;
	}
	int GetPos() {return pos;};
	bool SetPos(int i) 
	{
		if (i < 0 || i >= GetCount())
			return false;
		else {
			pos = i;
			return true;
		}
	}
	bool Eof()
	{
		return pos >= GetCount();
	}
	unsigned Count(String s)
	{
		int from = 0;
		unsigned count = 0;
		
		while ((from = ToString().Find(s, from)) >= 0) {
			count++;
			from++;
		}
		return count;
	}
private:
	int pos;
	int lastSeparator;
};

/////////////////////////////////////////////////////////////////////
// Special Folders
// Get the path to special folders
String GetDesktopFolder();
String GetProgramsFolder();
String GetAppDataFolder();
String GetMusicFolder();
String GetPicturesFolder();
String GetVideoFolder();
String GetPersonalFolder();
String GetTemplatesFolder();
String GetDownloadFolder();
String GetRootFolder();
String GetTempFolder();
String GetOsFolder();
String GetSystemFolder();

/////////////////////////////////////////////////////////////////////
// Processor Info
void GetSystemInfo(String &manufacturer, String &productName, String &version, int &numberOfProcessors);
void GetBiosInfo(String &biosVersion, Date &biosReleaseDate);
bool GetProcessorInfo(int number, String &vendor, String &identifier, String &architecture, int &speed);		
// Gets the real CPU speed in MHz
int GetCpuSpeed();

#if defined(PLATFORM_WIN32) 
bool GetVideoInfo(Array <Value> &name, Array <Value> &description, Array <Value> &videoProcessor, 
												Array <Value> &ram, Array <Value> &videoMode);
bool GetPackagesInfo(Array <Value> &name, Array <Value> &version, Array <Value> &vendor, 
			Array <Value> &installDate, Array <Value> &caption, Array <Value> &description, Array <Value> &state);
#endif

/////////////////////////////////////////////////////////////////////
// Memory Info
bool GetMemoryInfo(int &memoryLoad, uint64 &totalPhys, uint64 &freePhys, uint64 &totalPageFile, uint64 &freePageFile, uint64 &totalVirtual, uint64 &freeVirtual);

/////////////////////////////////////////////////////////////////////
// Windows list
// They get arrays with handles to all the opened windows with additional info as 
// pid: Handle to the process that manages the window
// name: Window name
// fileName: Window process program file name
// title: Window title (caption)
void GetWindowsList(Array<long> &wid, Array<long> &pid, Array<String> &name, Array<String> &fileName, Array<String> &title);
Array<long> GetWindowsList();

/////////////////////////////////////////////////////////////////////
// Process list
// They get arrays with handles to all the opened processes and process names 
bool GetProcessList(Array<long> &pid, Array<String> &pNames);
Array<long> GetProcessList();
String GetProcessName(long pid);
// Gets the program file name of a process
String GetProcessFileName(long processID);

// Gets the process id of a program with a window with certain title
long GetProcessIdFromWindowCaption(String windowCaption, bool exactMatch = false);

long GetWindowIdFromCaption(String windowCaption, bool exactMatch = false);

long GetProcessIdFromWindowId(long wid);
long GetWindowIdFromProcessId(long pid);

// Ends a process by any means
bool ProcessTerminate(long pid, int timeout = 500);

// Gets the process priority as a number from 0 (minimum) to 10 (maximum)
int GetProcessPriority(long pid);
bool SetProcessPriority(long pid, int priority);

// True if a process with handle pid exists
bool ProcessExists(long pid);

/////////////////////////////////////////////////////////////////////
// Os Info
bool GetOsInfo(String &kernel, String &kerVersion, String &kerArchitecture, String &distro, String &distVersion, String &desktop, String &deskVersion);
String GetDesktopManagerNew();

/////////////////////////////////////////////////////////////////////
// Drives list
// Get the dirve path list
Array<String> GetDriveList();
// Get drives info
// Return false if drive is not mounted or it is not accesible
bool GetDriveSpace(String drive, uint64 &freeBytesUser, uint64 &totalBytesUser, uint64 &totalFreeBytes);
bool GetDriveInformation(String drive, String &type, String &volume, /*uint64 &serial, */int &maxName, String &fileSystem);

/////////////////////////////////////////////////////////////////////
// Others
// Gets process id
long GetProcessId();

// I tries to "logoff", "reboot" or "shutdown"
bool Shutdown(String action);

// It converts an amount of bytes to compact size
String BytesToString(uint64 bytes);

// It converts an amount of seconds to compact size (h:m:s)
String SecondsToString(double seconds);

// It gets compiler info
void GetCompilerInfo(String &name, int &version, String &date);

// It gets info about the battery status
bool GetBatteryStatus(bool &discharging, int &percentage, int &remainingMin);
// Get if there is battery
bool GetBatteryInfo(bool &present/*, int &designCapacity, int &lastFullCapacity, String &vendor, String &type, String &model, String &serial*/);	

/////////////////////////////////////////////////////////////////////
// Key and mouse keys

bool Window_GetRect(long windowId, long &left, long &top, long &right, long &bottom);
void Window_SetRect(long windowId, long left, long top, long right, long bottom);

bool Mouse_GetPos(long &x, long &y);
bool Mouse_SetPos(long x, long y, long windowId);

bool Window_SaveCapture(long windowId, String fileName, int left = -1, int top = -1, int width = -1, int height = -1);

bool Snap_Desktop(String fileName);
bool Snap_DesktopRectangle(String fileName, int left, int top, int width, int height);
bool Snap_Window(String fileName, long handle);

#if defined(PLATFORM_WIN32)

void Mouse_LeftClick();
void Mouse_MiddleClick();
void Mouse_RightClick();
void Mouse_LeftDblClick();
void Mouse_MiddleDblClick();
void Mouse_RightDblClick();

void Keyb_SendKeys(String text, long finalDelay = 100, long delayBetweenKeys = 50);

void GetKeyLockStatus(bool &caps, bool &num, bool &scroll);
void SetKeyLockStatus(bool caps, bool num, bool scroll);

bool Record_Desktop(String fileName, int duration, int secsFrame = 1, bool viewMouse = true);
bool Record_DesktopRectangle(String fileName, int duration, int left, int top, int width, int height, int secsFrame = 1, bool viewMouse = true);
bool Record_Window(String fileName, int duration, long handle, int secsFrame = 1, bool viewMouse = true);

#endif

/////////////////////////////////////////////////////////////////////
// Trash bin handling

void FileToTrashBin(const char *path);
int64 TrashBinGetCount();
void TrashBinClear();


void SetDesktopWallPaper(const char *path);

#endif


// Known bugs
// GetWindowsList does not get the window title in Kde
// Shutdown in Linux only works with option "logoff", probably because of user permissions
