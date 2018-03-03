#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

#define WAVEMASK  16383
#define WAVECOUNT (WAVEMASK + 1)

struct FMOP {
	double delay = 0;
	double attack = 0;
	double decay = 0;
	double sustain = 1;
	double release = 0;
	
	double volume = 1;
	double f = 1;
	
	double Envelope(double t, double duration);
	double Evaluate(double t, double frequency, double duration, double mod);
};

	
struct Sound {
	double f = 100;
	double duration = 0.1;
	double volume = 1;
	
	FMOP   op[2];
};

#define NUM_CHANNELS 32

void InitSoundSynth();
void CloseSoundSynth();

void SetChannel(int chi, const Sound& c, bool start = false);

#endif
