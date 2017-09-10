#include "OSD.h"

volatile byte beep_queue[20];
volatile int  beep_time;
volatile byte beep_count, beepi;

void StartBeep()
{
	PORTD |= (1 << 6);
}

void EndBeep()
{
	PORTD &= ~(1 << 6);
}

void Beep(byte duration)
{
	beep_queue[0] = duration;
	beep_count = 1;
	StartBeep();
	beep_time = frame_counter;
	beepi = 0;
}

void AddBeep(byte wait, byte duration)
{
	beep_queue[beep_count++] = wait;
	beep_queue[beep_count++] = duration;
}

void LoopBeep(byte wait)
{
	beep_queue[beep_count++] = wait;
	beep_queue[beep_count++] = 255;
}

void StopBeeping()
{
	EndBeep();
	beep_count = 0;
}

void ProcessBeeps()
{
	if(beepi < beep_count && frame_counter >= beep_time + beep_queue[beepi]) {
		if(beepi & 1)
			StartBeep();
		else
			EndBeep();
		if(beep_queue[++beepi] == 255)
			beepi = 0;
		beep_time = frame_counter;
	}
}

bool IsBeeping()
{
	return beepi < beep_count;
}