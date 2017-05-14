#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct App : TopWindow {
	ArrayCtrl a;
	
	typedef App CLASSNAME;

	App() {
		Add(a.SizePos());
		Sizeable().Zoomable();

		a.AddColumn("Test");
		a.AddColumn("Test 2");
		for(int i = 0; i < 200; i++) {
			a.Add(i, i);
		}
		a.SetColumnDisplay(0, StdCenterDisplay());
	}
};

GUI_APP_MAIN
{
	DUMP("Test");
	App().Run();
}
