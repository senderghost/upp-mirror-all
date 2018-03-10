#include "Synth.h"

#include <SDL.h>

double Rate(double x)
{
	return pow(10, (6 * x / 100 - 6));
}

void FMOP::Comp()
{
	attack = 1 + Rate(attack);
	decay = 1 - Rate(decay);
	release = 1 - Rate(release);
	duration *= 44100;
	fdrift = exp2(fdrift / 12 / 44100);
	if(volume > 0)
		volume = pow(10, (volume - 100) / 40);
	if(sustain > 0)
		sustain = pow(10, (sustain - 100) / 40);
}

void Sound::Start()
{
	for(int i = 0; i < OPCOUNT; i++)
		op[i].Comp();
	f = f / 22100 * M_PI;
	t = 0;
	for(int i = 0; i < OPCOUNT; i++)
		op[i].Start();
}

force_inline
double FMOP::Evaluate(int t, double mf, double mod)
{
	if(t >= duration) {
		v *= release;
	}
	else
	switch(p) {
	case 0:
		v *= attack;
		if(v >= 1.0) {
			v = 1.0;
			p = 1;
		}
		break;
	case 1:
		v *= decay;
		if(v < sustain) {
			v = sustain;
			p = 2;
		}
		break;
	default:
		v = sustain;
	}
	f *= fdrift;
	double arg = mf * f * t + mod;
	double fn;
	if(waveform == WAVEFORM_SIN)
		fn = sin(arg);
	else
	if(findarg(waveform, WAVEFORM_BROWN, WAVEFORM_WHITE) >= 0) {
		static dword state = 1;
		state ^= state << 13;
		state ^= state >> 17;
		state ^= state << 5;
		fn = 2.0 / 4294967295.0 * state - 1;
		if(waveform == WAVEFORM_BROWN)
			fn = n = clamp(n + 0.06 * fn, -1.0, 1.0);
	}
	else {
		arg = fmod(arg, M_2PI);
		fn = waveform == WAVEFORM_SQUARE ? sgn(abs(M_PI - arg) / (M_PI / 2) - 1) :
		     waveform == WAVEFORM_TRIANGLE ? abs(M_PI - arg) / (M_PI / 2) - 1 :
		     waveform == WAVEFORM_SAWTOOTH ? arg / M_PI - 1 :
		     waveform == WAVEFORM_TOOTHSAW ? 1 - arg / M_PI :
		     0;
	}

	return volume * v * fn;
}

force_inline
float Sound::Get()
{
	return float(op[0].Evaluate(t++, f, op[1].Evaluate(t, f, 0) + op[2].Evaluate(t, f, 0)));
}

Sound sch[NUM_CHANNELS];

void SetChannel(int chi, const Sound& c, bool start)
{
	SDL_LockAudio();
	Sound& ch = sch[chi];
	ch = c;
	ch.Start();
	SDL_UnlockAudio();
}

void MyAudioCallback(void *, Uint8 *stream, int len)
{
	RTIMING("AudioGenerator");
	float *d = (float *)stream;

	memset(d, 0, sizeof(float) * 512);
	for(int j = 0; j < NUM_CHANNELS; j++) {
		Sound& ch = sch[j];
		d = (float *)stream;
		for(int i = 0; i < 512; i++)
			*d++ += ch.Get();
	}
}

void InitSoundSynth()
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
		return;
	
	SDL_AudioSpec want;
	memset(&want, 0, sizeof(want));
	want.freq = 44100;
	want.format = AUDIO_F32SYS;
	want.channels = 1;
	want.samples = 512;
	want.callback = MyAudioCallback;
	
	if(SDL_OpenAudio(&want, NULL) < 0)
	   LOG("Failed to open audio: " + (String)SDL_GetError());
	
	SDL_PauseAudio(0);
}

void CloseSoundSynth()
{
	SDL_CloseAudio();
	SDL_Quit();
}

/*
		static dword state = 1;
		state ^= state << 13;
		state ^= state >> 17;
		state ^= state << 5;
		
		double white =  2 * Randomf() - 1;
		static double brown, bs = 0.1;
		brown = clamp(brown + bs * white, -1.0, 1.0);
		bs = -bs;

		*d++ = h + add_white * white + add_brown * brown;


	double add_white = 0;
	double add_brown = 0;
	for(ChSound& ch : sch) {
		add_white += ch.white_noise;
		add_brown += ch.brown_noise;
	}

*/
