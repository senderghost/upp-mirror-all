#include <Core/Core.h>

using namespace Upp;

struct IpAddrInfoWithTimeout : IpAddrInfo {
	int start_time;
	int timeout;

	void      Start(const String& host, int port, int family = FAMILY_ANY) {
		start_time = GetTickCount();
		IpAddrInfo::Start(host, port, family);
	}
	bool      InProgress() {
		return GetTickCount() - start_time < timeout && IpAddrInfo::InProgress();
	}
	
	IpAddrInfoWithTimeout() { timeout = 500; }
};

CONSOLE_APP_MAIN
{
	IpAddrInfoWithTimeout h;
	
	h.Start("www.ultimatepp.org", 80);
	
	TimeStop tm;
	while(h.InProgress());
	DDUMP(tm);
}
