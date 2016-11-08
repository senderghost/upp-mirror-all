#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LOGPOS            UPP::VppLog() << "-=> " << __FILE__ << '@' << __LINE__ << '\n'

#undef LOG
#define LOG(a)            LOGPOS << a << UPP::EOL

#undef DUMP
#define DUMP(a)           LOGPOS << #a << " = " << (a) << UPP::EOL

#define OUT(a)            VppLog() << a << '\n'

void Logging()
{
	//. Logging
	
	// Logging is a useful technique to trace the flow of the code and examine results. In this
	// tutorial we will be using logging extensively, so let us start tutorial with the
	// explanation of logging.
	//
	// In debug mode, macro LOG puts string into output log file. Log file is placed into
	// 'config-directory', which by default is .exe directory in Win32 and ~/.upp/appname in POSIX.
	// In TheIDE, you can access the log using 'Debug'/'View the log file Alt+L'.
	
	LOG("Hello world");
	
	// You can log values of various types, as long as they have AsString function defined
	// (explained later). You can chain values in single LOG using operator<<:
	
	int x = 123;
	LOG("Value of x is " << x);

	// As it is very common to log a value of single variable, DUMP macro provides a useful shortcut,
	// creating a log line with the variable name and value:
	
	for(int i = 0; i < 10; i++)
		DUMP(i);

	LOG("FOOO!");
	
	// All normal LOGs are removed in release mode. If you need to log things in release mode,
	// you need to use RLOG / RDUMP macro instead:
	
	LOG("The end");
	
	//
}

CONSOLE_APP_MAIN
{
	Logging();
	
	String log = LoadFile(GetStdLogPath());
	StringStream ss(log);

	String sourcefile;
	Vector<String> source;
	bool   newfile = true;
	int    li = 0;

	while(!ss.IsEof()) {
		String ln = ss.GetLine();
		if(ln.StartsWith("-=>")) {
			String path, line;
			SplitTo(ln.Mid(4), '@', path, line);
			
			if(path != sourcefile) {
				sourcefile = path;
				li = 0;
				source = Split(Filter(LoadFile(path), [](int c)->int { return c == '\r' ? 0 : c; }), '\n', false);
				newfile = true;
			}
			
			int ln = atoi(line) - 1;
			while(li < source.GetCount() && li <= ln) {
				String h = source[li++];
				if(h.StartsWith("\t//")) {
					while(li < source.GetCount() && !source[li].StartsWith("\t//")) {
						OUT("SRC: " << source[li++]);
					}
					OUT("DOC: " << h.Mid(4));
					newfile = false;
				}
				else
				if(!newfile) {
					while(li < source.GetCount() && !source[li].StartsWith("\t//")) {
						OUT("SRC: " << source[li++]);
					}
				}
			}
		}
		else
		if(sourcefile.GetCount())
			OUT("LOG: " << ln);
	}
}
