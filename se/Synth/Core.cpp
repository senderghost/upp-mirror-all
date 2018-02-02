#include "Synth.h"

#include <SDL.h>

ArrayMap<int64, SoundGenerator> sound_channel;

int GetSynthChannelCount()
{
	return sound_channel.GetCount();
}

int64 AddSound(SoundGenerator *new_sg)
{
	int64 id;
	SDL_LockAudio();
	static int64 serial;
	id = ++serial;
	sound_channel.Add(id, new_sg);
	SDL_UnlockAudio();
	return id;
}

void AlterSound(int64 id, Event<SoundGenerator *> alter)
{
	SDL_LockAudio();
	int q = sound_channel.Find(id);
	if(q >= 0)
		alter(&sound_channel[q]);
	SDL_UnlockAudio();
}

void MyAudioCallback(void *, Uint8 *stream, int len)
{
	TIMING("AudioGenerator");
	float h[512];
	float *d = (float *)stream;
	Fill(d, d + 512, 0.0f);
	Vector<int> to_remove;
	for(int i = 0; i < sound_channel.GetCount(); i++) {
		if(!sound_channel[i].Get(h, 512))
			to_remove.Add(i);
		for(int j = 0; j < 512; j++)
			d[j] = d[j] + h[j];
	}
	sound_channel.Remove(to_remove);
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
	    DLOG("Failed to open audio: " + (String)SDL_GetError());
	
	SDL_PauseAudio(0);
}

void CloseSoundSynth()
{
	SDL_CloseAudio();
	SDL_Quit();
}
