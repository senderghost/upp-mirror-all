#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	{
		CoWork co;
		co & [] {};
	}

	double tm = usecs();
	{
		RTIMING("BechCoWork");
		CoWork co;
		for(int i = 0; i < 1000000; i++) {
			co & [] {};
		}
		co.Finish();
		tm = usecs() - tm;
	}
	RLOG(tm / 1000000 << " usec");
}
