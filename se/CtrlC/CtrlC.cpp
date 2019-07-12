#include <Core/Core.h>

using namespace Upp;

EXITBLOCK {
	RLOG("Exit");
}

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	Buffer<byte> x(1000);
	RLOG("Here");
	for(;;) Sleep(1);
	RLOG("After ctrl+c");
}
