#ifndef _TestChStyle_TestChStyle_h
#define _TestChStyle_TestChStyle_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <TestChStyle/TestChStyle.lay>
#include <CtrlCore/lay.h>

class TestChStyle : public WithTestChStyleLayout<TopWindow> {
public:
	typedef TestChStyle CLASSNAME;
	TestChStyle();
};

#endif
