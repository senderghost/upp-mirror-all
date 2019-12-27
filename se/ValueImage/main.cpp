#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
	Image m = CreateImage(Size(10, 10), Black());
	
	Value v = m;
	DDUMP(v.GetType());
	DDUMP(v.Is<Image>());
	
	m = v;
	DDUMP(m.GetSize());
	
	v = m;
	DDUMP(v.GetType());
	DDUMP(v.Is<Image>());
}
