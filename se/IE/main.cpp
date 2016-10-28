#include "IE.h"

using namespace Upp;

GUI_APP_MAIN
{
	TopWindow win;
	win.Sizeable();

	InternetExplorerBrowser browser;
	
	win.Add(browser.SizePos());
	
	browser.Browse("www.ultimatepp.org");
	
	win.Run();
}