#include <CtrlLib/CtrlLib.h>
#include <mmsystem.h>
#include <mmreg.h>

using namespace Upp;

static HWAVEOUT  s_hout;
static Semaphore waveSem;
static WAVEHDR   waveHdr[2];
static int       current;

static void CALLBACK WaveOutCb(HWAVEOUT hwo, UINT uMsg, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
    if (uMsg == WOM_DONE)
        waveSem.Release();
}

void MakeAudio(float *s, int channels, int samples)
{
	for(int i = 0; i < channels * samples; i++)
		s[i] = Randomf();
}

bool WaveOutput()
{
	current = !current;
	MakeAudio((float *)waveHdr[current].lpData, 2, 512);
	return waveOutWrite(s_hout, &waveHdr[current], sizeof(waveHdr[current])) == MMSYSERR_NOERROR;
}

GUI_APP_MAIN
{
	WAVEFORMATEX pfmt[1];
	memset(pfmt, 0, sizeof(pfmt));
	pfmt->wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
    pfmt->wBitsPerSample = 32;
    pfmt->nChannels = 2;
    pfmt->nSamplesPerSec = 44100;
    pfmt->nBlockAlign = pfmt->nChannels * (pfmt->wBitsPerSample / 8);
    pfmt->nAvgBytesPerSec = pfmt->nSamplesPerSec * pfmt->nBlockAlign;
	if(waveOutOpen(&s_hout, WAVE_MAPPER, pfmt, (DWORD_PTR) WaveOutCb, NULL, CALLBACK_FUNCTION)
	   != MMSYSERR_NOERROR) {
	       LOG("Error opening waveout");
	       return;
	}
	
	for(int i = 0; i < 2; i++) {
		WAVEHDR *w = &waveHdr[i];
		memset(w, 0, sizeof(WAVEHDR));
		w->dwBufferLength = 2 * 512 * sizeof(float);
        w->dwFlags = WHDR_DONE;
		static byte h[2][2 * 512 * sizeof(float)];
		w->lpData = (LPSTR) h[i];
		if(waveOutPrepareHeader(s_hout, w, sizeof(*w)) != MMSYSERR_NOERROR) {
			LOG("Error preparing buffer");
			return;
		}
	}

	LOG("OK");
	PromptOK("OK");

	Thread::Start([] {
		for(;;) {
			waveSem.Wait();
			WaveOutput();
		}
	});
	
	if(!WaveOutput()) {
		LOG("Error on output");
		return;
	}

	PromptOK("OK");
}
