#include <CtrlLib/CtrlLib.h>

using namespace Upp;

String Qtf(Color c)
{
	return String() << "$(" << c.GetR() << '.' << c.GetG() << '.' << c.GetB() << ")";
}

GUI_APP_MAIN
{
	String qtf;
	
	#define DO(x)       qtf << #x << " " << "[" << Qtf(x()) << " ____]" << ", in dark theme: [" << Qtf(DarkTheme(x())) << " ____]&";
	DO(SBlack)
	DO(SGray)
	DO(SLtGray)
	DO(SWhiteGray)
	DO(SWhite)
	DO(SRed)
	DO(SGreen)
	DO(SBrown)
	DO(SBlue)
	DO(SMagenta)
	DO(SCyan)
	DO(SYellow)
	DO(SLtRed)
	DO(SLtGreen)
	DO(SLtYellow)
	DO(SLtBlue)
	DO(SLtMagenta)
	DO(SLtCyan)
	
	DO(SColorPaper)
	DO(SColorText)
	DO(SColorFace)
	DO(SColorHighlight)
	DO(SColorHighlightText)
	DO(SColorMenu)
	DO(SColorMenuText)
	DO(SColorInfo)
	DO(SColorInfoText)
	DO(SColorMark)
	DO(SColorMenuMark)
	DO(SColorDisabled)
	DO(SColorLight)
	DO(SColorLabel)
	DO(SColorShadow)
	
	DO(SColorLtFace)
	DO(SColorDkShadow)

	DDUMP(qtf);

	PromptOK(qtf);
}
