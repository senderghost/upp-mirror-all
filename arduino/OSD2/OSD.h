#ifndef _OSD_Osd_h_
#define _OSD_Osd_h_

#include "Arduino.h"
#include <avr/pgmspace.h>
#include <EEPROM.h>

#define BAUD          9600
#define CLOCK         16000000
#define BAUD_SETTINGS (CLOCK/16/BAUD-1)

extern volatile int  frame_counter;
extern volatile int  max_line;

#define LINES   16
#define COLUMNS 22

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
#define delay13 delay12 delay1
#define delay14 delay13 delay1
#define delay15 delay14 delay1
#define delay16 delay15 delay1
#define delay17 delay16 delay1
#define delay18 delay17 delay1
#define delay19 delay18 delay1
#define delay20 delay19 delay1

void detectline();
void detectframe();

extern volatile byte framebuffer[];
extern volatile byte dimming[];

inline char *DisplayPos(int x, int y) {
	return framebuffer + y * COLUMNS + x;
};

// Development console

void Cls();
void Scroll();
void DimLine(int i, bool dim = true);
void CursorGoTo(int x, int y);
void Put(int chr);
void Put(const char *s);
void Put(int c, int count);
void Put(int x, int y, const char *s);
void Put(int x, int y, int c, int count);
void Flash(int x, int y, const char *s);
void Flash(int y, const char *s);

void Beep(byte duration);
void AddBeep(byte wait, byte duration);
bool IsBeeping();
void LoopBeep(byte wait);
void StopBeeping();

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
	int   satellites;

	bool  rmc_valid;
	bool  gga_valid;
	bool  valid;

	void NMEA(const char *s);
	
	GPS();
};

extern GPS gps;

void Main();

#endif
