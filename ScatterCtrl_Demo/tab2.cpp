#include "ScatterCtrl_Demo.h"


double funct1(double x)	{return 3;}
double funct2(double x)	{return (x*x-5);}
double funct3(double x)	{return (-x*x-5);}

void   vfunct1(double& y, double x) {y = 0;}
void   vfunct2(double& y, double x) {y = x*x;}
void   vfunct3(double& y, double x) {y = -x*x;}

Tab2::Tab2()
{
	CtrlLayout(*this);	
	HSizePos().VSizePos();
	scatter.SetRange(12, 60).SetXYMin(-6, -30).SetMajorUnits(2, 10);
	scatter.SetMouseHandling(true);

	scatter.AddSeries(&funct1).Legend("y = 3");
	scatter.AddSeries(&funct2).Legend("x^2-5");
	scatter.AddSeries(&funct3).Legend("-x^2-5");
}
