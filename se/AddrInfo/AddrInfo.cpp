#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	// conflict

	struct gaicb req[1], *reqptr[1];
	
	String url = "www.ultimatepp.org";
	
	memset(req, 0, sizeof(req));
	req->ar_name = ~url;
	reqptr[0] = req;
	if(getaddrinfo_a(GAI_NOWAIT, reqptr, 1, NULL) != 0) {
		LOG("Error");
		return;
	}
	
	int c = GetTickCount();
	for(;;) {
		int code = gai_error(req);
		if(code == 0)
			break;
		if(code != EAI_INPROGRESS) {
			DDUMP(GetTickCount() - c);
			LOG("Error processing " << gai_strerror(code));
			return;
		}
	}

	addrinfo *rp = req->ar_result;
	while(rp) {
		DDUMP(rp->ai_family);
		DDUMP(rp->ai_socktype);
		DDUMP(rp->ai_protocol);
		DDUMP(rp->ai_addr);
		DDUMP(rp->ai_addrlen);
		rp = rp->ai_next;
	}

    freeaddrinfo (rp);
}
