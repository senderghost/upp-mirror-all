#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
//	__float128 x;

	for(int i = 0; i < 1024; i++) {
		int x = i * 1.0 / 1024 / 1024;
	}

	int LI = 32, QI = 32, TI = 32, NI = 32, MI = 32;
	int ELI = 32, EQI = 32, ETI = 32, ENI = 32, EMI = 32;
	for(dword i = 32; i > 0; i--) {
		double x = 1.0 / (1 << i);
		double F = expm1(x);
		double L = expm1(2 * x) / 2;
		double Q = x + x*x / 2;
		double T = x + x*x / 2 + x * x * x / 6; x * (1 + x* (1/2 + x * 1/6)
		double N = x + x*x / 2 + x * x * x / 6 + x * x * x * x / 24;
		double M = x + x*x / 2 + x * x * x / 6 + x * x * x * x / 24 + x * x * x * x * x / 120;
		LOG(i << " " <<
		     x << " " << F <<
		     ", L: " << L <<
		     ", Q: " << Q <<
		     ", T: " << T <<
		     ", N: " << N <<
		     ", M: " << M
		);
		if(F == L) LI = i;
		if(F == Q) QI = i;
		if(F == T) TI = i;
		if(F == N) NI = i;
		if(F == M) MI = i;

		F++;
		if(F == L + 1) ELI = i;
		if(F == Q + 1) EQI = i;
		if(F == T + 1) ETI = i;
		if(F == N + 1) ENI = i;
		if(F == M + 1) EMI = i;
	}
	
	DUMP(LI);
	DUMP(QI);
	DUMP(TI);
	DUMP(NI);
	DUMP(MI);

	DUMP(ELI);
	DUMP(EQI);
	DUMP(ETI);
	DUMP(ENI);
	DUMP(EMI);

	int N = 1024;
	for(int i = 1; i < 1024; i++) {
		double x = 1.0 * i / N;
		double s = log(x);
		double p = x - 1.0 / N;
		double l = (log(p) + log(x + 1.0 / N)) / 2;
		LOG(x << " " << s
		      << ", L: " << l << ", " << abs(s - l));
	}
}
