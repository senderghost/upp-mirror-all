#include "OSD.h"

volatile byte beep_queue[10];
volatile int  beep_time;
volatile byte beep_count, beepi;

void StartBeep()
{
	DDRD = byte(DDRD | (1 << 6));
}

void EndBeep()
{
	DDRD = byte((byte)(DDRD & ~(1 << 6)));
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

void ProcessBeeps()
{
	if(beepi < beep_count && frame_counter >= beep_time + beep_queue[beepi]) {
		if(beepi)
			StartBeep();
		else
			EndBeep();
		beepi++;
		beep_time = frame_counter;
	}
}
