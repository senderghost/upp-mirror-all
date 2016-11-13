#include "Tutorial.h"

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
