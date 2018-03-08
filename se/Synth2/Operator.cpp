#include "Synth.h"

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
	fdrift = exp2(fdrift / 44100);
}

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
#if 0
	if(v * volume) {
		DDUMP(t);
		DDUMP(f);
	}
#endif
	double arg = mf * f * (t + mod);
	double fn;
	if(waveform == WAVEFORM_SIN)
		fn = sin(arg);
	else {
		arg = fmod(arg, M_2PI);
		fn = waveform == WAVEFORM_SQUARE ? sgn(abs(M_PI - arg) / M_PI - 1) :
		     waveform == WAVEFORM_TRIANGLE ? abs(M_PI - arg) / M_PI - 1 :
		     waveform == WAVEFORM_SAWTOOTH ? arg / M_PI - 1 :
		     waveform == WAVEFORM_TOOTHSAW ? 1 - arg / M_PI :
		     0;
	}

	return volume * v * fn;
}
