#ifndef _LblBox_LblBox_h
#define _LblBox_LblBox_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <LblBox/LblBox.lay>
#include <CtrlCore/lay.h>

class LblBox : public WithLblBoxLayout<TopWindow> {
public:
	typedef LblBox CLASSNAME;
	LblBox();
};

#endif
