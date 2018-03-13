#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

enum {
	WAVEFORM_SIN,
	WAVEFORM_SQUARE,
	WAVEFORM_TRIANGLE,
	WAVEFORM_SAWTOOTH,
	WAVEFORM_TOOTHSAW,
	WAVEFORM_BROWN,
	WAVEFORM_WHITE,
};

struct FMOP {
	double duration = 99;
	double volume = 0;

	double f = 1;
	double fdrift = 0;

	double attack = 100;
	double decay = 100;
	double sustain = 100;
	double release = 100;
	
	int    waveform = WAVEFORM_SIN;
	
	int    p = 0;
	double v = 0;
	double n = 0;
	
	void   Start() { v = 1e-3; p = 0; n = 0; }
	void   Comp();

	String Save() const;
	const char *Load(const char *s);
	
	void   Envelope(int t);
	double Evaluate(int t, double mf, double mod);
};

#define OPCOUNT 3

struct Sound {
	double f = 440;
	int    t;
	FMOP   op[3];
	
	void Start();
	float Get();
	
	String Save() const;
	void   Load(const char *s);
	
	Sound();
};

#define NUM_CHANNELS 32

void InitSoundSynth();
void CloseSoundSynth();

void SetChannel(int chi, const Sound& c);

#endif
