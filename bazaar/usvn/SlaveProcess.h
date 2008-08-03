#ifndef _usvn_SlaveProcess_h_
#define _usvn_SlaveProcess_h_

#include <Core/Core.h>

NAMESPACE_UPP

class SlaveProcess {
	SlaveProcess(const SlaveProcess& sp);
	void         operator = (const SlaveProcess& sp);

public:
	virtual void Kill() = 0;
	virtual bool IsRunning() = 0;
	virtual void Write(String s) = 0;
	virtual bool Read(String& s) = 0;
	virtual int  GetExitCode() = 0;
	virtual void Detach()          {};
	
	String  Get()                  { String x; if(Read(x)) return x; return String::GetVoid(); }

	SlaveProcess() {}
	virtual ~SlaveProcess() {}
};

class LocalProcess : public SlaveProcess {
public:
	virtual void Kill();
	virtual bool IsRunning();
	virtual void Write(String s);
	virtual bool Read(String& s);
	virtual int  GetExitCode();
	virtual void Detach();

private:
	void         Init();
	void         Free();
#ifdef PLATFORM_POSIX
	bool         DecodeExitCode(int code);
#endif

private:
#ifdef PLATFORM_WIN32
	HANDLE       hProcess;
	HANDLE       hOutputRead;
	HANDLE       hInputWrite;
#endif
#ifdef PLATFORM_POSIX
	Buffer<char> cmd_buf;
	Vector<char *> args;
	pid_t        pid;
	int          rpipe[2], wpipe[2];
	String       exit_string;
	bool         output_read;
#endif
	int          exit_code;

public:
	typedef LocalProcess CLASSNAME;

	bool Start(const char *cmdline, const char *envptr = NULL);

	LocalProcess()                                                    { Init(); }
	LocalProcess(const char *cmdline, const char *envptr = NULL)      { Init(); Start(cmdline, envptr); }
	virtual ~LocalProcess()                                           { Kill(); }
};

int    Sys(const char *cmd, String& output);
String Sys(const char *cmd);

END_UPP_NAMESPACE

#endif
