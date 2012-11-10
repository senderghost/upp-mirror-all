#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct Dialog : WithDialogLayout<TopWindow> {
	typedef Dialog CLASSNAME;
	
	IdCtrls ctrls;
	
	Dialog();
};

Dialog::Dialog()
{
	CtrlLayout(*this, "Dialog");

	ctrls
		(FIRSTNAME, firstname)
		(LASTNAME, lastname)
		(YEAR, year)
	;
}

GUI_APP_MAIN
{
	ValueMap m;
	LoadFromJsonFile(m);
	Dialog dlg;
	dlg.ctrls.Set(m);
	dlg.Execute();
	StoreAsJsonFile(m);
}