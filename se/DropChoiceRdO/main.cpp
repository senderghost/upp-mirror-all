#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
#if 0
	WithDropChoice<EditString> dc;
	dc.AddList("A");
	dc.AddList("B");
	dc.SetReadOnly();
//	dc.Disable();
#else
	EditString ef;
#endif

	TopWindow win;
	win.Add(dc.LeftPosZ(10, 100).TopPosZ(10, 50));

	win.Run();
}
