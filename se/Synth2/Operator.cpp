#include "Synth.h"

double FMOP::Evaluate(int t, double mod)
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
	return volume * v * sin(f * t + mod);
}
