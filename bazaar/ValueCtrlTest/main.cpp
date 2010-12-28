#include "ValueCtrlTest.h"

ValueCtrlTest::ValueCtrlTest()
{
	CtrlLayout(*this, "Window title");
	clear <<= THISBACK(Clear);
	vc <<= THISBACK(ActionCB);
	Add(vc.HSizePos().BottomPos(0, 20));
}

void ValueCtrlTest::ActionCB()
{
	Value v = vc.GetData();
	String s = "# Value Type: ";
	s << v.GetType() << "\n\t";
	s << "data: ";
	s << AsString(v);
	ToInfo(s);
	RLOG(s);
}

GUI_APP_MAIN
{
	ValueCtrlTest().Run();
}

