#ifndef _Synth_Synth_h
#define _Synth_Synth_h

#include <Core/Core.h>

using namespace Upp;

struct SoundGenerator {
	virtual bool Get(float *e, int) = 0;
	virtual ~SoundGenerator() {}
};

int64 AddSound(SoundGenerator *new_sg);

void  AlterSound(int64 id, Event<SoundGenerator *> alter);

struct Instrument {
	double frequency_mul = 1;
	double delay = 0;
	double attack = 0;
	double decay = 0;
	double sustain = 1;
	double release = 0;
	double mod_frequency = 1;
	double mod_amplitude = 0;
	int    noise_kind = 0;
	double noise_amplitude = 1;
	
	bool   has_noise = false;
	float  noise[8] = { 0 };

	String wave;
	String mod_wave;
	
	void   Read(CParser& p);
	void   Read(const char *s);

	Instrument();
};

int64 Play(float volume, float frequency, float duration_, const Instrument& m);
int64 Play(float volume, float frequency, const Instrument& m);

void  SetVolume(int64 id, float volume);
void  SetFrequency(int64 id, float frequency);
void  StopSound(int64 id);

void InitSoundSynth();
void CloseSoundSynth();
int  GetSynthChannelCount();

#endif
