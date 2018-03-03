#include "Synth.h"

double FMOP::Envelope(double t, double duration)
{
	if(t < delay)
		return 0;
	if(t > duration) {
		t -= duration;
		if(t > release)
			return 0;
		return sustain * (release - t) / release;
	}
	t -= delay;
	if(t < attack)
		return t / attack;
	t -= attack;
	if(t < decay) {
		return (sustain * t + decay - t) / decay;
	}
	return sustain;
}

double FMOP::Evaluate(double t, double frequency, double duration, double mod)
{
	return volume * Envelope(t, duration) * sin(frequency * t + mod);
}
