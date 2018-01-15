#include <Core/Core.h>
#include <Synth/Synth.h>

using namespace Upp;

void PlayNote(int note, double duration)
{
	double frequency = 440 * pow(2, (note - 45) / 12.0);

	Instrument t;
	t.attack = 0.02;
	t.decay = 0.2;
	t.sustain = 0.7;
	t.release = 0.5;
	t.wave = "0.9 10:0.3 20:0.2";
	t.mod_frequency = 5;
	t.mod_amplitude = 3;

	Play(0.9, frequency, duration, t);
/*
	t.mod_frequency = 30;
	t.mod_amplitude = frequency / 6;

	Play(0.9, frequency * 3, duration, t);

	t.attack = 0;
	t.decay = 0.4;
	t.sustain = 0.1;
	t.wave = noise_wave;
	t.wavemask = 65535;
	Play(0.8, frequency, duration, t);*/
}

void PlayNoteW(int note, double duration)
{
	PlayNote(note, duration);
	Sleep(int(duration * 1000));
}

 
CONSOLE_APP_MAIN
{
//	StdLogSetup(LOG_COUT|LOG_FILE);
	
	LOG("audiotest");

	InitSoundSynth();


	for(;0;) {
		auto drum = [] {
			{
				Instrument t;
				t.wave = "0.7 0.5 0 0.3 0.01";
				t.attack = 0.01;
				t.decay = 2;
				t.sustain = 0;
				t.mod_wave = "T";
//				t.noise_kind = 3;
//				t.noise_amplitude = 0.5;
				t.mod_amplitude = 10;
				t.mod_frequency = 10;
				
				Play(0.8, 440, 2, t);
				t.mod_frequency = 1;
			}
		};
		
		drum();
		Sleep(2000);
//		return;

/*
		drum(); Sleep(600);
		drum(); Sleep(600);
		drum(); Sleep(300);
		drum(); Sleep(300);
		drum(); Sleep(300);
		Sleep(300);*/
	}

	for(;;) {
//		for(int i = 0; i < 64; i++)
//			PlayNoteW(i, 0.1);
		PlayNoteW(10, 5);
		Sleep(1000);
		
		PlayNoteW(24, 0.3);
		PlayNoteW(26, 0.3);
		PlayNoteW(28, 0.3);
		PlayNoteW(29, 0.3);
		PlayNoteW(31, 0.6);
		PlayNoteW(31, 0.6);
		PlayNoteW(33, 0.6);
		PlayNoteW(33, 0.6);
		PlayNoteW(31, 0.6);
		PlayNoteW(29, 0.3);
		PlayNoteW(29, 0.3);
		PlayNoteW(29, 0.3);
		PlayNoteW(29, 0.3);
		PlayNoteW(28, 0.6);
		PlayNoteW(28, 0.6);
		PlayNoteW(26, 0.6);
		PlayNoteW(26, 0.6);
		PlayNoteW(24, 0.6);
		Sleep(2000);
	}
	
	for(;;) {
	/*
		double freq = 1000;
		DDUMP((44100 << 16) / freq);
		AddSound([=](SoundContext& sc, int16 *b, int len) -> bool {
			int& t = sc.p[0];
			for(int i = 0; i < len; i++) {
				*b++ = sin_wave[HIWORD(t) & 2047];
				t += ((dword)44100 << 16) / freq;
			}
			return sc.t < 1000000;
		}
	*/
		int c = getchar();
		if(c == 'q')
			break;
	}
/*
	while(!done)
	{
		if(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_LALT || event.key.keysym.sym == SDLK_TAB)
						break;
					
				case SDL_QUIT:
					done = true;
					break;
				default:
					break;
			}
		}
		
	}
*/
	CloseSoundSynth();
}
