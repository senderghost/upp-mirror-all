#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#undef LOG
#define LOG(a)           UPP::VppLog() << __FILE__ << ':' << __LINE__ << ':' << a << UPP::EOL

GUI_APP_MAIN
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
	
	DUMP(x);
	
	// All normal LOGs are removed in release mode. If you need to log things in release mode,
	// you need to use RLOG / RDUMP macro instead:

/*	
	RLOG("This will also log in release mode");
	RDUMP(x);
	
	DLOG("This will not compile in release mode");
	DDUMP(x);
	
	String h = "Hello world!";
	DUMPHEX(h);
	
	struct Foo {
		String a;
		int    b;
		
		String ToString() const { return String() << "[a: " << a << ", b: " << b << "]"; }
	};
	
	Foo foo;
	foo.a = "Text";
	foo.b = 123;
	
	DUMP(foo);

	TITLE("Basic utilities");
	
	DUMP(max(1, 4, 2, 3));
	DUMP(clamp(10, 1, 4));

	DUMP(findarg("beta", "alfa", "beta", "gamma"));

	DUMP(findarg("unknown", "alfa", "beta", "gamma"));
	
	DUMP(decode(1, 0, "zero", 1, "one", 2, "two", "unknown"));
	
	TITLE("Null");
	
	int i = Null;
	
	DUMP(i);
	
	DUMP(IsNull(i));
	
	int64 bug = i;
	DUMP(bug);
	
	struct Foo {
		String a;
		int    b;
		
		bool IsNullInstance() const { return a.GetCount() == 0 && b == 0; }
	};
	
	Foo  f;
	f.b = 0;
	DUMP(IsNull(f));
	
	f.b++;
	DUMP(IsNull(f));
	
	CParser p("x + 123");
	String x
	
	
	
	FindFile
	
*/
}