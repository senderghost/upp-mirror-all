#ifndef _Gtk3FsTest_Gtk3FsTest_h
#define _Gtk3FsTest_Gtk3FsTest_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Gtk3FsTest/Gtk3FsTest.lay>
#include <CtrlCore/lay.h>

class Gtk3FsTest : public WithGtk3FsTestLayout<TopWindow> {
public:
	typedef Gtk3FsTest CLASSNAME;
	Gtk3FsTest();
};

#endif
