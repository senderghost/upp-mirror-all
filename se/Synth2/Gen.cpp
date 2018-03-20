#include "Synth.h"

double Rate(double x)
{
	return pow(10, (6 * x / 100 - 6));
}

void SoundGen::FMOPGen::Comp()
{
	attack = 1 + Rate(attack);
	decay = 1 - Rate(decay);
	release = 1 - Rate(release);
	duration = 44100 * duration / 1000;
	fdrift = exp2(fdrift / 12 / 44100);
	if(volume > 0)
		volume = pow(10, (volume - 100) / 40);
	if(sustain > 0)
		sustain = pow(10, (sustain - 100) / 40);
}

double SoundGen::FMOPGen::Evaluate(int t, double mf, double mod)
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

void SoundGen::Start(const Sound& s)
{
	for(int i = 0; i < OPCOUNT; i++) {
		(FMOP&)op[i] = s.op[i];
		op[i].Comp();
		op[i].Start();
	}
	f = s.f / 22100 * M_PI;
	t = 0;
	delay = clamp(int(s.delay * 44100 / 1000), 0, 8190);
	reverb = pow(10, (s.reverb - 100) / 40);
	memset(feedback, 0, sizeof(feedback));
}

float SoundGen::Get()
{
	float r = feedback[t & 8191] =
		(float)(
			op[0].Evaluate(t, f, op[1].Evaluate(t, f, 0) + op[2].Evaluate(t, f, 0)) *
			(op[3].Evaluate(t, f, op[4].Evaluate(t, f, 0)) + 1) / 2 +
	        feedback[(t - delay) & 8191] * reverb
	     );
	t++;
	return r;
}
