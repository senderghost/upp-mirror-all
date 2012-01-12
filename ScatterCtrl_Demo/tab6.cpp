#include "ScatterCtrl_Demo.h"


void Tab6::Init()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter.SetRange(6,100);
	scatter.SetMajorUnits(1,20);
	scatter.ShowInfo();
	
	s1 <<Pointf(log10(10.0),14)<<Pointf(log10(1e2),25)<<Pointf(log10(1e3),39)<<Pointf(log10(1e4),44)<<Pointf(log10(1e5),76);
	scatter.AddSeries(s1).Legend("series1");
	scatter.cbModifFormatX = THISBACK(FormatX);
	scatter.LogX();
}

void Tab6::FormatX(String& s, int i, double d)
{
	s = FormatDoubleExp(d, 1);
}

INITBLOCK {
	RegisterExample("Log", new Tab6);
}