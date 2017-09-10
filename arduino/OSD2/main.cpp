#include "OSD.h"

GPS gps;

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

void ShowSats()
{
	*DisplayPos(9, LINES - 1) = 'S';
	FormatInt(gps.satellites, DisplayPos(10, LINES - 1), 2);
}

void ShowTime(long time)
{
	FormatTime(time, DisplayPos(0, LINES - 1));
}

void ShowVoltage()
{
	int voltage = analogRead(0);
	FormatFloat1(0.02137 * voltage, DisplayPos(COLUMNS - 5, LINES - 1), 2);
	*DisplayPos(COLUMNS - 1, LINES - 1) = 'V';
}

void Main()
{
	Cls();
	
	DimLine(0);

	Beep(2); AddBeep(4, 2); LoopBeep(100);
	
	while(!gps.valid) {
		DimLine(0);
		DimLine(LINES - 1);
		ShowVoltage();
		ShowSats();
		ShowTime(gps.time);
		Flash(1, 0, "WAITING FOR GPS LOCK");
		GetGPS(1500);
	}

	Beep(1000);
	AddBeep(1000, 2000);
	
	Cls();
	
	GPS home = gps;

	float lf = cosf((home.y) / 360 * (2 * M_PI)) * 111300.0f;
	
	int n = 0;
	
	bool wait_home = true;
	long last_movement_time = gps.time;
	long time0 = gps.time;

	Beep(1);LoopBeep(50);

	for(;;) {
		DimLine(0);
		DimLine(LINES - 1);

		if(wait_home) {
			Flash(5, 8, "LOCKING HOME");
			Beep(2);
		}

		GetGPS(1500);
		
		if(gps.speed > 1)
			last_movement_time = gps.time;

		int stop_time = int(gps.time - last_movement_time);

		if(wait_home && (stop_time > 15 || gps.time - time0 > 20 && gps.speed > 5)) {
			Cls();
			wait_home = false;
			Beep(50);
		}

		if(wait_home)
			home = gps;
		
		if((!wait_home && stop_time > 120 || !gps.valid) && !IsBeeping()) {
			Beep(4); AddBeep(4, 4); AddBeep(4, 4);
			AddBeep(4, 12); AddBeep(4, 12); AddBeep(4, 12);
			AddBeep(4, 4); AddBeep(4, 4); AddBeep(4, 4);
			LoopBeep(150);
		}

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
		
		float home_angle = atan2(dx, dy) * (180 / M_PI);
		
		int angle = (int(gps.direction - home_angle) + 360) % 360;
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

		ShowTime(wait_home ? gps.time - time0 : gps.time - home.time);
		
		ShowSats();
		
		ShowVoltage();

		#if 0
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
	
//		FormatInt(n++, DisplayPos(18, 15), 5);
	}
}
