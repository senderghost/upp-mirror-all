#include "NewWebSocket.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	WebSocket2 h;
	
//	h.Connect("ws://echo.websocket.org");
	h.Connect("ws://echo.websocket.org");

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
