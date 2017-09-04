#ifndef _OSD_Osd_h_
#define _OSD_Osd_h_

#include <avr/pgmspace.h>
#include "Arduino.h"

extern int  frame_count;
extern int  max_line;
extern long current_time;

#define LINES   16
#define COLUMNS 23

#define delay1  __asm__("nop\n\t");
#define delay2  delay1  delay1
#define delay3  delay2  delay1
#define delay4  delay3  delay1
#define delay5  delay4  delay1
#define delay6  delay5  delay1
#define delay7  delay6  delay1
#define delay8  delay7  delay1
#define delay9  delay8  delay1
#define delay10 delay9  delay1
#define delay11 delay10 delay1
#define delay12 delay11 delay1

extern byte framebuffer[];

inline char *DisplayPos(int x, int y) {
	return framebuffer + y * COLUMNS + x;
};

// Development console

void Cls();
void Scroll();
void CursorGoTo(int x, int y);
void Put(int chr);
void Put(const char *s);
void Put(int c, int count);
void Put(int x, int y, const char *s);
void Put(int x, int y, int c, int count);

void Wait(int ms);
void Beep(int duration);

typedef unsigned char byte;

void FormatInt(int n, char *dest, byte w, char neg, char filler);
void FormatInt(int n, char *dest, byte w, char neg);
void FormatInt(int n, char *dest, byte w);
void FormatFloat(float n, char *dest, byte w);
void FormatFloat1(float n, char *dest, byte w);
void FormatFloat2(float n, char *dest, byte w);
void FormatTime(long seconds, char *dest);

struct GPS {
	long  time;
	float x, y;
	float speed;
	float direction;
	float altitude;
	bool  rmc_valid;
	bool  gga_valid;
	bool  valid;

	void NMEA(const char *s);
	
	GPS();
};

extern GPS gps;

void Main();

#endif
