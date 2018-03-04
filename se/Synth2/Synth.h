#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

struct FMOP {
	double delay = 0;
	double attack = 1e12;
	double decay = 1e-12;
	double sustain = 1;
	double duration = 1;
	double release = 1e-6;
	
	double volume = 0;
	double f = 1;
	
	int    p;
	double v;
	
	void   Start() { v = 1e-12; p = 0; }
	
	void   Envelope(int t);
	double Evaluate(int t, double mod);
};

	
struct Sound {
	FMOP   op[2];
};

#define NUM_CHANNELS 32

void InitSoundSynth();
void CloseSoundSynth();

void SetChannel(int chi, const Sound& c, bool start = false);

#endif
