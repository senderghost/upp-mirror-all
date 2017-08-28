#include "OSD.h"

#include "config.h"
#include "font.h"
#include "output.h"
#include "variables.h"

#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

int  frame_count;
int  current_line;
int  max_line;
byte framebuffer[LINES][COLUMNS];

int  first_line = 32;

unsigned int time_l;
unsigned int time_h;

long current_time;

void detectframe()
{
	max_line = current_line;
	current_line = 0;
	frame_count++;
	
	unsigned int ntm = TCNT1;
	if(ntm < time_l)
		time_h++;
	time_l = ntm;
	
	current_time = ((long)time_h << 16) | time_l;
}

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

void detectline()
{
	int ln = current_line - first_line;
	if(ln >= 0 && ln < LINES * 16) {
		const byte *s = framebuffer[ln >> 4];
		const byte *l = letters + ((ln >> 1) & 7);

		byte current = pgm_read_byte_near(l + (*s << 3));
		#define DO DDRD = ((DDRD & 0x7f) | (0x80 & *s)); SPDR = current; current = pgm_read_byte_near(l + (*++s << 3)); delay8; delay4;
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO DO
	}

	current_line++;
	
	SPDR = 0; // Let's make sure SPI is not idling high.
	DDRD = (DDRD & 0x7f) | 0x80; // end dimming
}
