#include "FSMon.h"

NAMESPACE_UPP

#ifdef PLATFORM_WIN32

//	Enable/Disable process privileges.
BOOL FSMon::EnablePrivilege(LPCTSTR pszPrivName, BOOL fEnable)
{
	// Assume function fails
	BOOL fOk = FALSE;

	// Try to open this process's access token
	HANDLE hToken;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		// privilege
		TOKEN_PRIVILEGES tp = { 1 };

		if (LookupPrivilegeValue(NULL, pszPrivName,  &tp.Privileges[0].Luid))
		{
			tp.Privileges[0].Attributes = fEnable ?  SE_PRIVILEGE_ENABLED : 0;
			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
			fOk = (GetLastError() == ERROR_SUCCESS);
		}
		CloseHandle(hToken);
	}
	return(fOk);
}

// constructor
FSMon::FSMon(bool nOnClose)
{
	// must create completion port on first use
	completionPort = NULL;
	
	// reset completion keys generator
	// skip 0 descriptor, we never know if 0 is returned...
	lastDescriptor = 1;

	// those are needed for ReadDirectoryChangesW
	EnablePrivilege(SE_BACKUP_NAME, true);
	EnablePrivilege(SE_RESTORE_NAME, true);
	EnablePrivilege(SE_CHANGE_NOTIFY_NAME, true);
	
	shutDown = false;
	threadRunning = false;

DLOG("Class constructed");
}

// destructor
FSMon::~FSMon()
{
	// if thread not started, no need to shutdown
	if(threadRunning)
	{
		// cancels all pending IO operations
		// can't use the CancelIoEx (available from Vista+)
		// so we first cancel IO for current thread
		// then we send a packet that causes worker thread to
		// cancel its part
		for(int i = 0; i < monitoredInfo.GetCount(); i++)
		{
			CancelIo(monitoredInfo[i].hDir);
			// no way to pass valid parameters with PostQueuedCompletionStatus(),
			// so we use a 'cancelling' flag inside Info recors
			INTERLOCKED_(fsmMutex2){
				monitoredInfo[i].cancelling = true;
			}
			PostQueuedCompletionStatus(completionPort, 0, monitoredDescriptors[i], NULL);
			while(true)
			{
				bool cancelling;
				INTERLOCKED_(fsmMutex2){
					cancelling = monitoredInfo[i].cancelling;
				}
				if(!cancelling)
					break;
				else
					Sleep(10);
			}
		}
		
		// wait some time just to allow thread to cancel all pending I/O
		Sleep(10);
		
DLOG("Shutting thread down....");
		// signal thread shutdown
		shutDown = true;
		
		// send a completion packet to completion port
		// in order make it return
		PostQueuedCompletionStatus(completionPort, 0, 0, NULL);
		
		while(shutDown)
			;
DLOG("Thread correctly stopped");
		threadRunning = false;
	}
	
	// close handles and completion port
	for(int i = 0; i < monitoredInfo.GetCount(); i++)
		CloseHandle(monitoredInfo[i].hDir);
	CloseHandle(completionPort);
DLOG("Class destructed");
}

// get error string from code
String FSMon::GetErrorStr(HRESULT err)
{
	LPTSTR errorText;
	String res;
	
	FormatMessage(
		// use system message tables to retrieve error text
		FORMAT_MESSAGE_FROM_SYSTEM |
		// allocate buffer on local heap for error text
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		// Important! will fail otherwise, since we're not 
		// (and CANNOT) pass insertion parameters
		FORMAT_MESSAGE_IGNORE_INSERTS,  
		NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&errorText,  // output 
		0, // minimum size for output buffer
		NULL);   // arguments - see note 
	
	if(errorText)
	{
		res = errorText;
		LocalFree(errorText);
	}
	
	return res;
}

// add a monitored path
bool FSMon::Add(String const &path)
{
DLOG("Path = " << path);
	// should enable privileges on first call
	// @@ to do
	
	//open the directory to watch
	HANDLE hDir = CreateFile(
		path,
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE ,//| FILE_SHARE_DELETE, <-- removing FILE_SHARE_DELETE prevents the user or someone else from renaming or deleting the watched directory. This is a good thing to prevent.
		NULL, //security attributes
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS | //<- the required priviliges for this flag are: SE_BACKUP_NAME and SE_RESTORE_NAME.  CPrivilegeEnabler takes care of that.
		FILE_FLAG_OVERLAPPED, // for async mode
		NULL
	);

	if (hDir == INVALID_HANDLE_VALUE)
	{
DLOG("Error opening dir to watch '" << path << "'");
		return false;
	}

	//create a IO completion port/or associate this key with
	//the existing IO completion port
	completionPort = CreateIoCompletionPort(
		hDir,
		// if completionPort is NULL, hDir is associated with a NEW completion port,
		// if completionPort is NON-NULL, hDir is associated with the existing completion
		// port that the handle completionPort references
		completionPort,
		// the completion 'key'... this ptr is returned from GetQueuedCompletionStatus() when one of the events in the dwChangesToWatchFor filter takes place
		lastDescriptor,
		0
	);
	if(!completionPort)
	{
		SetError(GetLastError());
		CloseHandle(hDir);
DLOG("Error creating completion port");	
		return false;
	}
	
	// completion port created, we can now store monitored path and its key
	// and update key generator

	// must lock here to avoid working threat to access
	// removed stuffs
	INTERLOCKED_(fsmMutex2)
	{
		monitoredPaths.Add(path);
		monitoredDescriptors.Add(lastDescriptor++);
		monitoredInfo.Add();
	}
	
	CHANGESINFO &info = monitoredInfo.Top();
	info.hDir = hDir;
	
	// overlapped MUST be zero filled, otherwise ReadDirectoryChangesW fails
	memset(&info.overlapped, 0, sizeof(OVERLAPPED));

DLOG("hDir = " << hDir);	
	// an now, if not already done, we must start working thread
	if(!threadRunning)
	{
		shutDown = false;
		fsmThread.Start(THISBACK(monitorCb));
		threadRunning = true;
	}

	// thread is started, we shall add the monitored folder with ReadDirectoryChangesW
	DWORD bufLen;
	if (!ReadDirectoryChangesW(
			info.hDir,
			info.buffer,
			READ_DIR_CHANGE_BUFFER_SIZE,
			true, // we want subdirs events
			FILE_NOTIFY_CHANGE_FILE_NAME	|
			FILE_NOTIFY_CHANGE_DIR_NAME		|
			FILE_NOTIFY_CHANGE_ATTRIBUTES	|
			FILE_NOTIFY_CHANGE_SIZE			|
			FILE_NOTIFY_CHANGE_LAST_WRITE	|
			FILE_NOTIFY_CHANGE_CREATION		|
			FILE_NOTIFY_CHANGE_SECURITY,
			&bufLen,//this var not set when using asynchronous mechanisms...
			&info.overlapped,
			NULL)) //no completion routine!
	{
		SetError(GetLastError());
DLOG("Error on ReadDirectoryChangesW : " << GetErrorStr(errCode));
		return false;
	}
DLOG("Success starting monitor of '" << path << "'");
	return true;
}

bool FSMon::Remove(String const &path)
{
	int idx = monitoredPaths.Find(path);
	if(idx < 0)
		return false;
	
	CHANGESINFO &info = monitoredInfo[idx];
	
	// camcels io for corresponding path
	// as usual, we can't use CancelIoEx because we want it working on XP
	// so we cancel io in current thread and fake the behaviour
	// sending a cancel packet to worker thread
DLOG("Posting completion cancel packet....");
	// no way to pass valid parameters with PostQueuedCompletionStatus(),
	// so we use a 'cancelling' flag inside Info recors
	INTERLOCKED_(fsmMutex2)	{
		info.cancelling = true;
	}
	PostQueuedCompletionStatus(completionPort, 0, monitoredDescriptors[idx], NULL);
	CancelIo(info.hDir);
	
	// wait for tread get the cancelling packet and reset the flag...
	while(true)
	{
		bool cancelling;
		INTERLOCKED_(fsmMutex2){
			cancelling = info.cancelling;
		}
		if(!cancelling)
			break;
		else
			Sleep(10);
	}
DLOG("Should have got and cancelled");
	
	// free dir handle
	CloseHandle(info.hDir);

	// must lock here to avoid working threat to access
	// removed stuffs
	INTERLOCKED_(fsmMutex2)
	{
		monitoredPaths.Remove(idx);
		monitoredInfo.Remove(idx);
		monitoredDescriptors.Remove(idx);
	}
	return true;
}

// scans result buffer for FILE_NOTIFY_INFORMATION records
// and process them
/*
typedef struct _FILE_NOTIFY_INFORMATION {
  DWORD NextEntryOffset;
  DWORD Action;
  DWORD FileNameLength;
  WCHAR FileName[1];
} FILE_NOTIFY_INFORMATION, *PFILE_NOTIFY_INFORMATION;
*/
void FSMon::ProcessNotify(FILE_NOTIFY_INFORMATION *buf, String const &path)
{
	do
	{
		switch(buf->Action)
		{
			case FILE_ACTION_ADDED :
DLOG("FILE_ACTION_ADDED"); 
				INTERLOCKED_(fsmMutex)
				{
					Info &info = changed.Add();
					info.flags = FSM_Created;
					WString ws = WString(buf->FileName, buf->FileNameLength / sizeof(WCHAR));
					info.path = AppendFileName(path, ws.ToString());
				}
				callHandlerCb();
				break;
			case FILE_ACTION_REMOVED :
DLOG("FILE_ACTION_REMOVED"); 
				INTERLOCKED_(fsmMutex)
				{
					Info &info = changed.Add();
					info.flags = FSM_Deleted;
					WString ws = WString(buf->FileName, buf->FileNameLength / sizeof(WCHAR));
					info.path = AppendFileName(path, ws.ToString());
				}
				callHandlerCb();
				break;
			case FILE_ACTION_MODIFIED :
DLOG("FILE_ACTION_MODIFIED"); 
				INTERLOCKED_(fsmMutex)
				{
					Info &info = changed.Add();
					info.flags = FSM_Modified;
					WString ws = WString(buf->FileName, buf->FileNameLength / sizeof(WCHAR));
					info.path = AppendFileName(path, ws.ToString());
				}
				callHandlerCb();
				break;
			case FILE_ACTION_RENAMED_OLD_NAME :
DLOG("FILE_ACTION_RENAMED_OLD_NAME"); 
			{
				WString ws = WString(buf->FileName, buf->FileNameLength / sizeof(WCHAR));
				String oldPath = path + ws.ToString();
				if(!buf->NextEntryOffset)
					break;
				buf = (FILE_NOTIFY_INFORMATION *)((byte *)buf + buf->NextEntryOffset);
				if(buf->Action != FILE_ACTION_RENAMED_NEW_NAME)
				{
DLOG("ops.... FILE_ACTION_RENAMED_NEW_NAME expected");
					break;
				}
				INTERLOCKED_(fsmMutex)
				{
					Info &info = changed.Add();
					info.flags = FSM_Moved;
					info.path = oldPath;
					ws = WString(buf->FileName, buf->FileNameLength / sizeof(WCHAR));
					info.newPath = AppendFileName(path, ws.ToString());
				}
				callHandlerCb();
				break;
			}
			case FILE_ACTION_RENAMED_NEW_NAME :
DLOG("ops... that one should be handled by previous case...");
				break;
			default :
DLOG("unknown action notification");
		}
		
		// go to next record
		buf = (FILE_NOTIFY_INFORMATION *)((byte *)buf + buf->NextEntryOffset);
	}
	while(buf->NextEntryOffset);
}

// monitoring callback (runs in a separate thread)
void FSMon::monitorCb(void)
{
	DWORD numBytes;
	LONG descriptor;
	LPOVERLAPPED overlapped;

	// completion port is ok, start monitoring it
	while(!shutDown)
	{
		// Retrieve the directory info for this directory
		// through the io port's completion key
		if(!GetQueuedCompletionStatus(
				completionPort,
				&numBytes,
				(ULONG *)&descriptor,
				&overlapped,
				INFINITE // remember to send a completion packet to shut down thread !!
		))
		{
			// error state, if 'overlapped' is NULL, the call timed out
			// with no event, otherwise we got some error
			if(!overlapped)
			{
				// this would mean timeout, but shouldn't happen
				// even if called with a null overlapped, it sets up one
				// so this can't be used for cancel packets
				// we use numBytes parameter, using value of 1 which should
				// be never valid
			}
			else
			{
				// here we land on errors or on CancelIo operations
				int err = GetLastError();
				if(err == ERROR_OPERATION_ABORTED)
				{
					// we land here if a CancelIo was called on this handle
					// just do nothing... we don't have to respawn the I/O
					INTERLOCKED_(fsmMutex2)
					{
						int idx = monitoredDescriptors.Find(descriptor);
						if(idx >= 0)
							CancelIo(monitoredInfo[idx].hDir);
					}
DLOG("IO cancelled");
				}
				else
				{
					SetError(err);
DLOG("GetQueuedCompletionStatus error : " << GetErrorStr(errCode));
				}
			}
		}
		else
		{
			// just quick exit if shutting down
			if(shutDown)
				break;
			
			// get path data from descriptor
			// we use a second mutex here, it just lock adding/removing paths
			INTERLOCKED_(fsmMutex2)
			{
				int idx = monitoredDescriptors.Find(descriptor);
				if(idx < 0)
				{
DLOG("oops... got a descriptor not in list : " << descriptor);
					continue;
				}
				else
				{
					// check flag if we wanna cancel...
					CHANGESINFO &info = monitoredInfo[idx];
					if(info.cancelling)
					{
DLOG("Sent cancelio packet from main thread");
						CancelIo(info.hDir);
						info.cancelling = false;
					}
					else
					{
						String path = monitoredPaths[idx];
DLOG("Got an event for path '" << path << "'");
						// re-post the request, we don't want to loose events here....
						DWORD bufLen;
						if (!ReadDirectoryChangesW(
								info.hDir,
								info.buffer,
								READ_DIR_CHANGE_BUFFER_SIZE,
								true, // we want subdirs events
								FILE_NOTIFY_CHANGE_FILE_NAME	|
								FILE_NOTIFY_CHANGE_DIR_NAME		|
								FILE_NOTIFY_CHANGE_ATTRIBUTES	|
								FILE_NOTIFY_CHANGE_SIZE			|
								FILE_NOTIFY_CHANGE_LAST_WRITE	|
								FILE_NOTIFY_CHANGE_CREATION		|
								FILE_NOTIFY_CHANGE_SECURITY,
								&bufLen, //this var not set when using asynchronous mechanisms...
								&info.overlapped,
								NULL)) //no completion routine!
						{
							SetError(GetLastError());
DLOG("Error respawning ReadDirectoryChangesW : " << GetErrorStr(errCode));
						}
						else
						{
DLOG("Success respawning monitor of '" << path << "'");
						}
						// we got an event, just parse it and fill received event structures
						ProcessNotify((FILE_NOTIFY_INFORMATION *)info.buffer, path);
					}
				}
			}
		}
	}
	
	// reset shutdown flag to signal tread exiting
	shutDown = false;
}

// callback to call event handler in maint thread
// (via PostCallback) when using GUI
void FSMon::callHandlerCb(void)
{
#ifdef flagGUI
DLOG("Postcallback called");
	PostCallback(EventHandler);
#else
DLOG("Handler called");
	EventHandler();
#endif
}

// query for changed files/folders
Vector<FSMon::Info> FSMon::GetChanged(void)
{
	Vector<Info> info;
	INTERLOCKED_(fsmMutex)
	{
		info = changed;
		changed.Clear();
	}
	return info;
}

// gets actually opened files
Index<String> FSMon::GetOpenedFiles(void)
{
	// no way on windows to catch open/close on files
	// without a dedicated filter
	return Index<String>();
}

// check error contidion and get error message
VectorMap<String, int> FSMon::GetErrorMap(void)
{
	// just return last error -- on windows we can't have
	// sequences of errors
	VectorMap<String, int> res;
	res.Add("", (int)errCode);
	return res;
}

#endif

END_UPP_NAMESPACE
