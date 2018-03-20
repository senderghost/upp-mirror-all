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
	double duration = 99000;
	double volume = 0;

	double f = 1;
	double fdrift = 0;

	double attack = 100;
	double decay = 100;
	double sustain = 100;
	double release = 100;
	
	int    waveform = WAVEFORM_SIN;
	
	String Save() const;
	const char *Load(const char *s);
};

#define OPCOUNT 5

struct Sound {
	double f = 440;
	FMOP   op[OPCOUNT];

	double delay = 0;
	double reverb = 0;
	
	String Save() const;
	void   Load(const char *s);
	
	Sound();
};

struct SoundGen {
	struct FMOPGen : FMOP {
		int    p;
		double v;
		double n;
		
		void   Start() { v = 1e-3; p = 0; n = 0; }
		void   Comp();
		
		double Evaluate(int t, double mf, double mod);
	};
	
	double   f = 440;
	int      t;
	int      delay;
	double   reverb;
	FMOPGen  op[OPCOUNT];
	float    feedback[8192];
	
	void     Start(const Sound& s);
	float    Get();
};

#define NUM_CHANNELS 32

void InitSoundSynth();
void CloseSoundSynth();

void SetChannel(int chi, const Sound& c);

#endif
