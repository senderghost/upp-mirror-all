#include <CtrlLib/CtrlLib.h>

using namespace Upp;

String Qtf(Color c)
{
	ImageDraw iw(128, 48);
	iw.DrawRect(0, 0, 128, 48, c);
	DrawFatFrame(iw, 0, 0, 128, 48, Black(), 4);
	return AsQTF(CreateRawImageObject(PNGEncoder().SaveString(iw), 256, 96));
}

GUI_APP_MAIN
{
	String qtf = "{{1:1:1:1 ";
	
	DDUMP(Qtf(Black()));
	
	#define DO(x)       qtf << "[:" << #x << "`(`): " << "Color [* " << #x << "]()]:: :: " << Qtf(x()) << ":: " << Qtf(DarkTheme(x())) << ":: ";
	
	DO(Black)
	DO(Gray)
	DO(LtGray)
	DO(WhiteGray)
	DO(White)
	DO(Red)
	DO(Green)
	DO(Brown)
	DO(Blue)
	DO(Magenta)
	DO(Cyan)
	DO(Yellow)
	DO(LtRed)
	DO(LtGreen)
	DO(LtYellow)
	DO(LtBlue)
	DO(LtMagenta)
	DO(LtCyan)

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
