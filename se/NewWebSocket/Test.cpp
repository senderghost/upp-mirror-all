#include "NewWebSocket.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	WebSocket2 h;
	
	h.Connect("wss://echo.websocket.org");

//	h.NonBlocking();
	
//	h.SendText("Test");

	h.BeginText("Hello");
	h.Continue(" ");
	h.Fin("world!");
	
	while(!h.IsClosed()) {
		if(h.IsError()) {
			DDUMP(h.GetError());
			break;
		}
		h.Do();
		if(h.IsMessage()) {
			Cout() << h.Fetch() << "\n";
		}
	}
}
