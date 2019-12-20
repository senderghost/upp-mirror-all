#include "Gtk3FsTest.h"

Gtk3FsTest::Gtk3FsTest()
{
	CtrlLayoutOKCancel(*this, "Window title");
}

GUI_APP_MAIN
{
	Gtk3FsTest().Run();
}
