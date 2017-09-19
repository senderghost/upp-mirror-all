#include "NewWebSocket.h"

using namespace Upp;

CONSOLE_APP_MAIN
{
	WebSocket2 h;
	
	h.Connect("wss://echo.websocket.org");

	h.NonBlocking();
	
//	h.SendText("Test");

	h.BeginText("Hello");
	h.Continue(" ");
	h.Fin("world!");
	
	while(h.IsOpen()) {
		if(h.IsError()) {
			DDUMP(h.GetError());
			break;
		}
		String s = h.Receive();
		if(s.GetCount()) {
			Cout() << s << "\n";
			if(*s.Last() == '!')
				h.Close();
		}
	}
}
