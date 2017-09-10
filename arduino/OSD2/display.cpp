#include "OSD.h"

void Scroll()
{
	memmove(framebuffer, framebuffer + COLUMNS, (LINES - 1) * COLUMNS);
	memset(framebuffer + (LINES - 1) * COLUMNS, 0, COLUMNS);
}

static byte *cursor = framebuffer;

void CursorGoTo(int x, int y)
{
	cursor = DisplayPos(x, y);
}

void Cls()
{
	memset(framebuffer, 0, LINES * COLUMNS);
	memset(dimming, 0, LINES);
	cursor = framebuffer;
}

void DimLine(int i, bool dim)
{
	dimming[i] = dim ? 0xff : 0;
}

void Put(int chr)
{
	if(chr == '\n') {
		int d = cursor - framebuffer;
		d = (d + COLUMNS) / COLUMNS * COLUMNS;
		while(d > LINES * COLUMNS) {
			Scroll();
			d -= COLUMNS;
		}
		cursor = framebuffer + d;
	}
	else {
		if(cursor >= framebuffer + LINES * COLUMNS) {
			Scroll();
			cursor = framebuffer + (LINES - 1) * COLUMNS;
		}
		*cursor++ = chr;
	}
}

void Put(const char *s)
{
	while(*s)
		Put(*s++);
}

void Put(int c, int count)
{
	while(count--)
		Put(c);
}

void Put(int x, int y, const char *s)
{
	CursorGoTo(x, y);
	Put(s);
}

void Flash(int x, int y, const char *s)
{
	CursorGoTo(x, y);
	if(frame_counter & 128)
		Put(x, y, ' ', strlen(s));
	else
		Put(s);
}

void Put(int x, int y, int c, int count)
{
	CursorGoTo(x, y);
	Put(c, count);
}
