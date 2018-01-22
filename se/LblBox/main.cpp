#include "LblBox.h"

LblBox::LblBox()
{
	CtrlLayout(*this, "Window title");
}

GUI_APP_MAIN
{
	LblBox().Run();
}
