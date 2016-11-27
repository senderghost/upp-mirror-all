#ifndef _Gauge_Gauge_h
#define _Gauge_Gauge_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Gauge/Gauge.lay>
#include <CtrlCore/lay.h>

class Gauge : public WithGaugeLayout<TopWindow> {
public:
	typedef Gauge CLASSNAME;
	Gauge();
};

#endif
