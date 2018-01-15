#include "Synth.h"

#include <Core/Core.h>
#include <SDL.h>

using namespace Upp;

double sin_wave[2048];
double square_wave[2048];
double triangle_wave[2048];
double saw_wave[2048];
double was_wave[2048];
double noise_wave[65536];
double pink_wave[65536];
double brown_wave[65536];

struct WaveForm {
	double wave[2048];
};

void MakeWave(const char *s, WaveForm& h)
{
	for(int i = 0; i < 2048; i++)
		h.wave[i] = 0;
	
	CParser p(s);
	try {
		int harm = 1;
		if(p.Char('T')) {
			for(int i = 0; i < 2048; i++)
				h.wave[i] = (1024 - abs(1024 - i)) / 512.0 - 1;
			return;
		}
		if(p.Char('Z')) {
			for(int i = 0; i < 2048; i++)
				h.wave[i] = 2.0 * i / 2047 - 1;
			return;
		}
		if(p.Char('z')) {
			for(int i = 0; i < 2048; i++)
				h.wave[i] = -2.0 * i / 2047 - 1;
			return;
		}
		while(!p.IsEof()) {
			double a = p.ReadDouble();
			if(p.Char(':'))
				harm = (int)a;
			else
				for(int i = 0; i < 2048; i++)
					h.wave[i] += a * sin(M_2PI * i * harm / 2048);
			harm++;
		}
	}
	catch(...) {}
}

double *GetWave(const String& h)
{
	static Mutex _;
	Mutex::Lock __(_);
	static ArrayMap<String, WaveForm> cache;
	int q = cache.Find(h);
	if(q >= 0)
		return cache[q].wave;
	MakeWave(h, cache.Add(h));
	return cache.Top().wave;
}

INITBLOCK
{
	for(int i = 0; i < 2048; i++) {
		square_wave[i] = sgn(sin_wave[i] = sin(M_2PI * i / 2048));
		saw_wave[i] = 2.0 * i / 2047 - 1;
		was_wave[i] = -saw_wave[i];
		triangle_wave[i] = (1024 - abs(1024 - i)) / 512.0 - 1;
	}
	for(int i = 0; i < 65536; i++)
		noise_wave[i] = Randomf();
	for(int i = 0; i < 65536; i++) {
		pink_wave[i] = (noise_wave[i] + noise_wave[(i + 1) & 0xffff] + noise_wave[(i + 2) & 0xffff]) / 3;
	}
	for(int i = 0; i < 65536; i++) {
		brown_wave[i] = (pink_wave[i] + pink_wave[(i + 1) & 0xffff] + pink_wave[(i + 2) & 0xffff]) / 3;
	}
}

struct SoundChannel {
	int                                pos = 0;
	SoundContext                       context;
	Gate<SoundContext&, double *, int>  ef;
};

Array<SoundChannel> ch;

int GetSynthChannelCount()
{
	return ch.GetCount();
}

void AddSound(Gate<SoundContext&, double *, int> ef)
{
	SDL_LockAudio();
//	ch.Clear();
	SoundChannel& sc = ch.Add();
	sc.ef = ef;
	memset(&sc.context, 0, sizeof(sc.context));
	SDL_UnlockAudio();
}

void MyAudioCallback(void *, Uint8 *stream, int len)
{
	double h[512];
	float *d = (float *)stream;
	Fill(d, d + 512, 0.0f);
	for(int i = ch.GetCount() - 1; i >= 0; i--) {
		SoundChannel& e = ch[i];
		if(!e.ef(e.context, h, 512))
			ch.Remove(i);
		else
			e.context.t += 512;
		for(int j = 0; j < 512; j++)
			d[j] = float(d[j] + h[j]);
	}
}

Instrument::Instrument()
{
	delay = 0;
	attack = 0;
	decay = 0;
	sustain = 1;
	release = 0;
	wave = "1";
	mod_wave = "1";
	mod_amplitude = 0;
	mod_frequency = 1;
	noise_kind = 0;
	noise_amplitude = 1;
};

const int TABN = 4096;

static double table[TABN + 2];

double LOGVOL(double x)
{
	return pow(10, x * 60 / 20) / pow(10, 60 / 20);
}

force_inline
double LogVol(double x)
{
	double id = TABN * x;
	int ii = (int)id;
	if(ii < 0) return 0;
	if(ii > TABN) return x;
	double f = id - ii;
	return (1 - f) * table[ii] + f * table[ii + 1];
}

INITBLOCK {
	for(int i = 0; i <= TABN; i++) {
		double q = i / (double)TABN;
		table[i] = LOGVOL(q);
	}
	table[TABN + 1] = (TABN + 1) / 256.0;
	table[0] = 0;
}

double MakeNoise(int kind)
{
	static dword state = 1;
	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
	double white = 2.0 / 4294967295.0 * state - 1;

	static double p;
	static double b0, b1, b2;

	switch(kind) {
	case 1:
		return white;
	case 2:
		b0 = 0.99765 * b0 + white * 0.0990460;
		b1 = 0.96300 * b1 + white * 0.2965164;
		b2 = 0.57000 * b2 + white * 1.0526913;
		return b0 + b1 + b2 + white * 0.1848;
	case 3:
		p = clamp(p + (0.02 * (Randomf() * 2 - 1)) / 1.02, -1/3.5, 1/3.5);
		return p * 3.5;
	}
	return 0;
}

void Play(double volume, double frequency, double duration_, const Instrument& m)
{
	enum { WAVEMASK = 2047 };
	double fdelta = (WAVEMASK + 1) * frequency / 44200;
	double sustain = m.sustain * volume;
	double mdelta = (WAVEMASK + 1) * m.mod_frequency / 44200;
	double mod_amp = (WAVEMASK + 1) * m.mod_amplitude / 44200;
	int    duration = int(44200 * duration_);
	int    delay = int(44200 * m.delay);
	int    attack = int(44200 * m.attack);
	int    decay = int(44200 * m.decay);
	int    release = int(44200 * m.decay);
	double *wave = GetWave(m.wave);
	double *mod_wave = GetWave(m.mod_wave);
	
	AddSound([=](SoundContext& sc, double *b, int len) -> bool {
		double& q = sc.p[0];
		double& w = sc.p[1];
		int t = sc.t;
		bool plays = true;
		for(int i = 0; i < len; i++) {
			double envelope = 0;
			if(t < delay)
				*b++ = 0;
			else {
				if(t < delay + attack)
					envelope = (t * volume) / attack;
				else
				if(t < delay + attack + decay)
					envelope = volume - (volume - sustain) * (t - delay - attack) / decay;
				else
				if(t < duration)
					envelope = sustain;
				else
				if(release) {
					envelope = sustain - sustain * (t - duration) / release;
					if(envelope <= 0) {
						plays = false;
						envelope = 0;
					}
				}
				double a = wave[(int)q & WAVEMASK];
				if(m.noise_kind)
					a += m.noise_amplitude * MakeNoise(m.noise_kind);
				*b++ = LogVol(envelope) * a;
				w += mdelta;
				q += fdelta + mod_amp * mod_wave[(int)w & WAVEMASK];
			}
			t++;
		}
		return plays;
	});
}

void InitSoundSynth()
{
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
		return;
	
	SDL_AudioSpec want;
	SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
	want.freq = 44100;
	want.format = AUDIO_F32SYS;
	want.channels = 1;
	want.samples = 512;
	want.callback = MyAudioCallback; /* you wrote this function elsewhere. */
	
	if(SDL_OpenAudio(&want, NULL) < 0)
	    DLOG("Failed to open audio: " + (String)SDL_GetError());
	
	SDL_PauseAudio(0);
}

void CloseSoundSynth()
{
	SDL_CloseAudio();
	SDL_Quit();
}
