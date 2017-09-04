#include "OSD.h"

struct NParser {
	const char *s;
	
	void  Next();
	void  Spaces();
	char  Char();
	bool  IsNumber()   { return *s >= '0' && *s <= '9'; }
	int   Number();
	long  Long();
	float Fraction();
	float Float();
	float Coord();
};

char NParser::Char()
{
	return *s ? *s++ : 0;
}

void NParser::Next()
{
	s = strchr(s, ',');
	if(s)
		s++;
	else
		s = "\0";
}

void NParser::Spaces()
{
	while(*s == ' ')
		s++;
}

int NParser::Number()
{
	Spaces();
	int n = 0;
	while(*s >= '0' && *s <= '9')
		n = n * 10 + *s++ - '0';
	return n;
}

long NParser::Long()
{
	Spaces();
	long n = 0;
	while(*s >= '0' && *s <= '9')
		n = n * 10 + *s++ - '0';
	return n;
}

float NParser::Fraction()
{
	Spaces();
	float d = 0;
	if(*s == '.') {
		s++;
		float rank = 0.1f;
		while(*s >= '0' && *s <= '9') {
			d += rank * (*s++ - '0');
			rank *= 0.1f;
		}
	}
	return d;
}

float NParser::Float()
{
	return Number() + Fraction();
}

float NParser::Coord()
{
	int n = Number();
	float h = Fraction();
	
	int deg = n / 100;
	int minutes = n % 100;
	
	h = deg + (h + minutes) / 60;
	
	Next();
	if(*s == 'S' || *s == 'W')
		h = -h;
	Next();
	
	return h;
}

void GPS::NMEA(const char *s)
{
	NParser p;
	p.s = s;
	if(s[0] == 0 || s[1] == 0 || s[2] == 0)
		return;
	if(s[3] == 'R' && s[4] == 'M' && s[5] == 'C') {
		p.Next();
		long m = p.Long();
		time = (m / 10000) * 3600 + (m / 100 % 100) * 60 + (m % 100);
		p.Next();
		p.Next();
		rmc_valid = p.IsNumber();
		y = p.Coord();
		rmc_valid = rmc_valid && p.IsNumber();
		x = p.Coord();
		speed = 1.852f * p.Float();
		p.Next();
		direction = p.Float();
		valid = rmc_valid && gga_valid;
	}
	if(s[3] == 'G' && s[4] == 'G' && s[5] == 'A') {
		for(int i = 0; i < 9; i++)
			p.Next();
		gga_valid = p.IsNumber();
		altitude = p.Float();
		valid = rmc_valid && gga_valid;
	}
}

GPS::GPS()
{
	rmc_valid = gga_valid = valid = false;
}
