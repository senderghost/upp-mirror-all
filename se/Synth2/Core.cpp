#include "Synth.h"

#include <SDL.h>

SoundGen sch[NUM_CHANNELS];

void SetChannel(int chi, const Sound& c)
{
	SDL_LockAudio();
	SoundGen& ch = sch[chi];
	ch.Start(c);
	SDL_UnlockAudio();
}

void MyAudioCallback(void *, Uint8 *stream, int len)
{
	RTIMING("AudioGenerator");
	float *d = (float *)stream;

	memset(d, 0, sizeof(float) * 512);
	for(int j = 0; j < NUM_CHANNELS; j++) {
		SoundGen& ch = sch[j];
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
