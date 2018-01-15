#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

extern double sin_wave[2048];
extern double square_wave[2048];
extern double triangle_wave[2048];
extern double saw_wave[2048];
extern double was_wave[2048];

extern double noise_wave[65536];
extern double pink_wave[65536];
extern double brown_wave[65536];

struct SoundContext {
	int    t;
	double p[16];
};

void AddSound(Gate<SoundContext&, double *, int> ef);

struct Instrument {
	double delay;
	double attack;
	double decay;
	double sustain;
	double release;
	double mod_frequency;
	double mod_amplitude;
	int    noise_kind;
	double noise_amplitude;

	String wave;
	String mod_wave;

	Instrument();
};

void Play(double volume, double frequency, double duration_, const Instrument& m);

void InitSoundSynth();
void CloseSoundSynth();
int  GetSynthChannelCount();

#endif
