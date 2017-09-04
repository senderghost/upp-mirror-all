#include "OSD.h"

GPS gps;

void Wait(int ms) {
	while(ms-- > 0) {
		int start = TCNT1;
		while(TCNT1 - start < 15);
	}
}

void Beep(int duration)
{
	Wait(duration);
	digitalWrite(6, LOW);
}

void DUMP(float x)
{
	char h[20];
	memset(h, 0, 20);
	FormatFloat2(x, h, 5);
	Put(h);
	Put('\n');
}

bool GetGPS(int timeout)
{
	int start = TCNT1;
	char buffer1[80], buffer2[80];
	byte len = 0;
	char *t, *buffer;
	bool rmc = false;
	bool gga = false;
	
	timeout *= 15;
	
	t = buffer = buffer1;
	len = 0;
	while(TCNT1 - start < timeout) {
	    if(UCSR0A & (1<<RXC0)) {
	        char c = UDR0;
			if(c == '\n') {
				*t = 0;
				if(len > 5) {
					if(buffer[3] == 'R' && buffer[4] == 'M' && buffer[5] == 'C')
						rmc = true;
					if(buffer[3] == 'G' && buffer[4] == 'G' && buffer[5] == 'A')
						gga = true;
				}
				if(rmc && gga) {
					gps.NMEA(buffer1);
					gps.NMEA(buffer2);
					return true;
				}
				t = buffer = rmc || gga ? buffer2 : buffer1;
				len = 0;
			}
			else
			if(len < 78) {
				*t++ = c;
				len++;
			}
		}
	}
	return false;
}

void Main()
{
	Cls();
	
	while(!gps.valid) {
		Cls();
		Put(2, 0, "WAITING FOR GPS LOCK");
		GetGPS(1500);
		Cls();
		GetGPS(1500);
	}
	

	Beep(1000);
	
	Cls();
	
	GPS home = gps;

	float lf = cosf((home.y) / 360 * (2 * M_PI)) * 111300.0f;
	
	int n = 0;

	for(;;) {
		GetGPS(1500);
		
		FormatFloat1(gps.speed, DisplayPos(0, 0), 3);
		*DisplayPos(5, 0) = 1;
		*DisplayPos(6, 0) = 2;

		float dy = 111300.0f * (gps.y - home.y);
		float dx = lf * (gps.x - home.x);
		float da = (gps.altitude - home.altitude);
		float los = sqrt(dx * dx + dy * dy + da * da);
		FormatFloat(los, DisplayPos(COLUMNS / 2 + 1, 0), 4);
		*DisplayPos(COLUMNS / 2 + 1 + 4, 0) = 4;

		FormatFloat(gps.altitude - home.altitude, DisplayPos(COLUMNS - 5, 0), 4);
		*DisplayPos(COLUMNS - 1, 0) = 4;
		
		double home_angle = atan2(dx, dy) * (180 / M_PI);
		
		int angle = int(gps.direction - home_angle + 360) % 360;
		int a = ((8 * angle + 180) / 360) & 7;
		
		*DisplayPos(COLUMNS / 2, 0) = a + 20;
		Put(0, 1, ' ', COLUMNS);
		Put(0, LINES - 2, ' ', COLUMNS);
		if(angle < 90)
			*DisplayPos(COLUMNS / 2 + COLUMNS * (angle) / 180, 1) = 19;
		else
		if(angle > 270)
			*DisplayPos(COLUMNS / 2 - COLUMNS * (360 - angle) / 180, 1) = 19;
		else
			*DisplayPos(COLUMNS / 2 + COLUMNS * (180 - angle) / 180, LINES - 2) = 19;

		a = ((8 * (int(home_angle + 180 + 360) % 360) + 180) / 360) & 7;
		*DisplayPos(8, 0) = "NNWSSSEN"[a];
		*DisplayPos(9, 0) = " W W E E"[a];

		FormatTime(gps.time - home.time, DisplayPos(0, LINES - 1));

		#if 1
			CursorGoTo(0, 3);
/*			DUMP(lf);
			DUMP(gps.x);
			DUMP(gps.y);
			DUMP(gps.altitude);
			DUMP(gps.speed);
			DUMP(gps.direction);
			DUMP(dx);
			DUMP(dy);*/
			DUMP(home_angle);
			DUMP(angle);
			DUMP(a);
	//		Put(gps.gga_valid ? "GGA VALID  " : "GGA INVALID");
	//		Put(gps.rmc_valid ? "RMC VALID  " : "RMC INVALID");
		#endif
	
		FormatInt(n++, DisplayPos(18, 15), 5);
	}
}
