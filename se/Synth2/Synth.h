#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

struct FMOP {
	double attack = 100;
	double decay = 100;
	double sustain = 1;
	double duration = 1;
	double release = 100;
	
	double volume = 1;
	double f = 1;
	double fdrift = 0;
	
	int    p;
	double v;
	
	void   Start() { v = 1e-3; p = 0; }
	void   Comp();
	
	void   Envelope(int t);
	double Evaluate(int t, double mf, double mod);
};

#define OPCOUNT 2

struct Sound {
	double f;
	FMOP   op[2];
};

#define NUM_CHANNELS 32

void InitSoundSynth();
void CloseSoundSynth();

void SetChannel(int chi, const Sound& c, bool start = false);

#endif
