#include "OSD.h"

void Main()
{
	char h[20];
	
	ltoa(current_time, h, 10);

	byte *t = &framebuffer[0][0];
	for(const char *s = h; *s; s++)
		*t++ = *s;
}
