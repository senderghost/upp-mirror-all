#ifndef _OSD_Osd_h_
#define _OSD_Osd_h_

#include <avr/pgmspace.h>
#include "Arduino.h"

extern int  frame_count;
extern int  max_line;
extern long current_time;

#define LINES   16
#define COLUMNS 24

extern byte framebuffer[LINES][COLUMNS];

void Main();

#endif
