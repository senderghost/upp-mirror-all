#include "OSD.h"

#include "config.h"
#include "output.h"
#include "variables.h"

#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>

const unsigned char letters[] PROGMEM = {
#include "font.h"
};

int  frame_count;
int  current_line;
int  max_line;
byte framebuffer[LINES * COLUMNS];

int  first_line = 32;

void detectframe()
{
	max_line = current_line;
	current_line = 0;
	frame_count++;
}

void detectline()
{
	int ln = current_line - first_line;
	if(ln >= 0 && ln < LINES * 16) {
		const byte *s = framebuffer + COLUMNS * (ln >> 4);
		const byte *l = letters + ((ln >> 1) & 7);

		byte current = pgm_read_byte_near(l + (*s << 3));
		#define DO DDRD = ((DDRD & 0x7f) | (0x80 & *s)); SPDR = current; current = pgm_read_byte_near(l + (*++s << 3)); delay8; delay4;
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO
	}

	current_line++;
	
	SPDR = 0; // Let's make sure SPI is not idling high.
	DDRD = (DDRD & 0x7f) | 0x80; // end dimming
}
