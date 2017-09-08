#include "OSD.h"

void FormatInt(int n, char *dest, byte w, char neg, char filler)
{
	char *t = dest + w - 1;
	do {
		*t-- = n % 10 + '0';
		n = n / 10;
		w--;
	}
	while(w && n);
	if(w) {
		*t-- = neg;
		w--;
	}
	while(w) {
		*t-- = ' ';
		w--;
	}
}

void FormatInt(int n, char *dest, byte w)
{
	if(n < 0)
		FormatInt(-n, dest, w, '-', ' ');
	else
		FormatInt(n, dest, w, ' ', ' ');
}

void FormatFloat(float n, char *dest, byte w)
{
	char neg = ' ';
	if(n < 0) {
		neg = '-';
		n = -n;
	}
	FormatInt((int)(n + 0.5), dest, w, neg, ' ');
}

void FormatFloat1(float n, char *dest, byte w)
{
	char neg = ' ';
	if(n < 0) {
		neg = '-';
		n = -n;
	}
	int h = (int)(n + 0.05);
	FormatInt(h, dest, w, neg, ' ');
	n -= h;
	dest[w] = '.';
	dest[w + 1] = byte(n * 10 + 0.5) % 10 + '0';
}

void FormatFloat2(float n, char *dest, byte w)
{
	char neg = ' ';
	if(n < 0) {
		neg = '-';
		n = -n;
	}
	int h = (int)(n + 0.005);
	FormatInt(h, dest, w, neg, ' ');
	n -= h;
	dest[w] = '.';
	dest[w + 1] = byte(n * 10) % 10 + '0';
	dest[w + 2] = byte(n * 100 + 0.5) % 10 + '0';
}

void FormatTime(long seconds, char *t)
{
	t[2] = t[5] = ':';
	t += 8;
	for(byte i = 3; i--;) {
		int rem = seconds % 60;
		*--t = rem % 10 + '0';
		*--t = rem / 10 + '0';
		--t;
		seconds /= 60;
	}
}
