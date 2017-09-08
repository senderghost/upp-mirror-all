#include "OSD.h"

const unsigned char letters[] PROGMEM = {
#include "font.h"
};

volatile int  frame_counter;
volatile int  current_line;
volatile int  max_line;

volatile byte framebuffer[LINES * COLUMNS];
volatile byte dimming[LINES];

int  first_line = 32;

void ProcessBeeps();

void detectframe()
{
	max_line = current_line;
	current_line = 0;
	frame_counter++;
	ProcessBeeps();
}

void detectline()
{
	int ln = current_line - first_line;
	if(ln >= 0 && ln < LINES * 16) {
		byte li = ln >> 4;
		const byte *s = framebuffer + COLUMNS * li;
		const byte *l = letters + ((ln >> 1) & 7);

		DDRD = (byte)((byte)(DDRD & 0x7f) | (byte)(0x80 & dimming[li]));

		byte current = pgm_read_byte_near(l + (*s << 3));
		#define DO SPDR = current; current = pgm_read_byte_near(l + (*++s << 3)); delay17;
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO DO
		DO DO DO DO  DO DO DO
	}

	current_line++;
	
	SPDR = 0; // Let's make sure SPI is not idling high.
	DDRD = (DDRD & 0x7f) | 0x80; // end dimming
}
