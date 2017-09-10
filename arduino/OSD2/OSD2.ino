#include "OSD.h"

void setup() {
  // Set pin-modes:
	pinMode(10,OUTPUT);
	pinMode(11,OUTPUT);
	pinMode(12,OUTPUT);
	pinMode(13,OUTPUT);
	
	pinMode(0,INPUT);
	pinMode(1,INPUT);
	pinMode(2,INPUT);
	pinMode(3,INPUT);
	pinMode(4,INPUT);
	pinMode(5,INPUT);
	pinMode(6,OUTPUT);
	pinMode(7,OUTPUT);
	pinMode(8,INPUT);
	pinMode(9,INPUT);

// Init Serial communication. 
	Serial.begin(BAUD);
	UBRR0H = (unsigned char) (BAUD_SETTINGS>>8);
	UBRR0L = (unsigned char) (BAUD_SETTINGS);
	UCSR0A = 0b0000000;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
 
// Enable SPI for pixel generation
// Set SPI;  
	SPCR =
		(1 << SPE)  | //Enable SPI
		(1 << MSTR) | // Set as master
		(0 << SPR1) | // Max speed
		(0 << SPR0) | // Max speed
		(0 << DORD) | // Year, Try to set this to 1 :D (Will mirror the byte)
		(1 << CPOL) | // Doesnt really matter, its the SCK polarity
		(1 << CPHA);
  
//	SPSR = (1 << SPI2X); // SPI double speed - we want 8 mhz output speed.
	SPSR = (0 << SPI2X); // SPI double speed - we want 4 mhz output speed.
	SPDR = 0b00000000; // IMPORTANT.. The SPI will idle random at low or high in the beginning. If it idles high you will get black screen = bad idea in FPV.

	// It will always idle at the last bit sent, so always be sure the last bit is 0. The main-loop and end of each line will always send 8 zeros - so it should
	// be pretty safe.
  
// Analog read enable and set prescale. You can change prescale if you like.
//	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
  
// Disable standard Arduino interrupts used for timer etc. (you can clearly see the text flicker if they are not disabled)
	TIMSK0=0;
	TIMSK1=0;
	TIMSK2=0;

	TCCR1A = 0; // normal mode for timer 1
    TCCR1B = (1 << CS12) | (1 << CS10); // 1024 prescaler
      
	attachInterrupt(0, detectline, FALLING);
	attachInterrupt(1, detectframe, RISING);

	digitalWrite(7, LOW);
	
	Cls();
	
	Put(0, LINES / 2, "OSD by Mirek Fidler");
}

void loop()
{
	Main();
}
