#include <CtrlLib/CtrlLib.h>

#include <Synth2/Synth.h>

using namespace Upp;

int LetterToNote(byte c) {
	static byte cv[256];
	ONCELOCK {
		int q = 0;
		memset(cv, 255, 256);
		for(int c : "AbBCdDeEFgGhHiIKlLmMN")
			cv[c] = q++;
	}
	return cv[c] < 255 ? cv[c] : -1;
}

GUI_APP_MAIN
{
	/*
	0 - 220Hz 3
	110 2
	55 1
	22.5 0
	*/
	
	DDUMP(sizeof(Sound));

	InitSoundSynth();

	const char *s = "CDHG";
	
	int ii = 0;
	int duration = 1/4.0;
	
	for(const char *s = "CDHG--HGDC------"; *s; s++) {
		if(*s == '-')
			Sleep(500);
		int note = LetterToNote(*s);
		if(note >= 0) {
			Sound snd;
			snd.Load("440.00:L1V100A80D60S90R30:L0.25A90D35S30R35:V120f2D40R20");
			snd.f = 220 * exp2(note / 12.0) / snd.op[0].f;
			snd.op[0].duration = 500;
			SetChannel(ii, snd);
			ii = (ii + 1) & 15;
			Sleep(500);
		}
	}
	
	Sleep(1000);
	
	CloseSoundSynth();
}
