#include "NewWebSocket.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	WebSocket h;
	
	h.Connect("174.129.224.73");

	h.NonBlocking();
	
	h.SendText("Test");
	for(;;) {
		if(h.IsError()) {
			DDUMP(h.GetError());
			break;
		}
		h.Do();
		if(h.IsText()) {
			DDUMP(h.GetMessage());
			break;
		}
	}
}
