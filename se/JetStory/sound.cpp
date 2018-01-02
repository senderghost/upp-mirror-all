#include "jetstory.h"
#include <windows.h>
#include <mmreg.h>
#include <mmsystem.h>

#define SAMPLE_RATE     11025
#define OUT_BUFFER_SIZE  409600

static HWAVEOUT     hWaveOut ;
static BYTE         pBuffer1[OUT_BUFFER_SIZE];
static WAVEHDR      pWaveHdr1[1];
static WAVEFORMATEX waveformat ;

VOID FillBuffer (PBYTE pBuffer, int iFreq)
{
     static double fAngle ;
     int           i ;

     for (i = 0 ; i < OUT_BUFFER_SIZE ; i++)
     {
          pBuffer [i] = (BYTE) (127 + 127 * sin (fAngle)) ;

          fAngle += 2 * M_PI * iFreq / SAMPLE_RATE ;

          if (fAngle > 2 * M_PI)

               fAngle -= 2 * M_PI ;
     }
}

void CALLBACK waveOutProc(HWAVEOUT m_hWO, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR wParam, DWORD_PTR lParam) {
	switch(uMsg) {
     case WOM_OPEN:
         DLOG("OPEN");
        pWaveHdr1->lpData          = (LPSTR)pBuffer1 ;
        pWaveHdr1->dwBufferLength  = OUT_BUFFER_SIZE ;
        pWaveHdr1->dwBytesRecorded = 0 ;
        pWaveHdr1->dwUser          = 0 ;
        pWaveHdr1->dwFlags         = 0 ;
        pWaveHdr1->dwLoops         = 1 ;
        pWaveHdr1->lpNext          = NULL ;
        pWaveHdr1->reserved        = 0 ;
        
        waveOutPrepareHeader (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
          FillBuffer (pBuffer1, 1000) ;
          DDUMP(waveOutWrite (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)));
          DDUMP(GetLastErrorMessage());
          return;

     case WOM_DONE:
         DLOG("DONE");
          FillBuffer ((BYTE *)((PWAVEHDR) lParam)->lpData, 500) ;
          waveOutWrite (hWaveOut, (PWAVEHDR) lParam, sizeof (WAVEHDR)) ;
          return;
          
     case WOM_CLOSE:
         DLOG("CLOSE");
          waveOutUnprepareHeader (hWaveOut, pWaveHdr1, sizeof (WAVEHDR)) ;
          hWaveOut = NULL ;
          return;
	}
}

void InitSound()
{
	waveformat.wFormatTag      = WAVE_FORMAT_PCM;
	waveformat.nChannels       = 1;
	waveformat.nSamplesPerSec  = SAMPLE_RATE;
	waveformat.nAvgBytesPerSec = SAMPLE_RATE;
	waveformat.nBlockAlign     = 1 ;
	waveformat.wBitsPerSample  = 8 ;
	waveformat.cbSize          = 0 ;

	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveformat, (DWORD_PTR) waveOutProc, 0, CALLBACK_FUNCTION/* | WAVE_ALLOWSYNC*/)
	      != MMSYSERR_NOERROR) {
		hWaveOut = NULL;
		return;
	}
}

void Sound(void *ptr)
{
}
