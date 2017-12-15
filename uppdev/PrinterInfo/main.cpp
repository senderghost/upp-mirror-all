#include <CtrlLib/CtrlLib.h>
#include <TDraw/TDraw.h>
#include <Report/Report.h>

using namespace Upp;

GUI_APP_MAIN
{
	Report r;
	r << "Hello world";
	Perform(r);
}
