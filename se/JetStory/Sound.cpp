#include "jetstory.h"

void PlaySound(const char *s)
{
	int n = 0;
	Sound snd;
	snd.Load(s);
	SetChannel(n++, snd);
	if(n >= NUM_CHANNELS)
		n = 0;
}
