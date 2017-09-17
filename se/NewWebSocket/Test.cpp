#include "NewWebSocket.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	WebSocket2 h;
	
	h.Connect("wss://echo.websocket.org");

	h.NonBlocking();
	
	h.SendText("Test");
	while(!h.IsClosed()) {
		if(h.IsError()) {
			DDUMP(h.GetError());
			break;
		}
		h.Do();
		if(h.IsText()) {
			Cout() << h.Fetch() << "\n";
			h.SendClose();
		}
	}
}
