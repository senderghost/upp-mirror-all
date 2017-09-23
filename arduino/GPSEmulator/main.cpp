#include <CtrlLib/CtrlLib.h>

using namespace Upp;

HANDLE m_hIDComDev;

bool OpenCom(int nPort, int nBaud)
{
	char szPort[100];

	wsprintf( szPort, "\\\\.\\COM%d", nPort );
	m_hIDComDev = CreateFile( szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if(!m_hIDComDev)
		return false;
	DCB dcb;
	dcb.DCBlength = sizeof( DCB );
	GetCommState( m_hIDComDev, &dcb );
	dcb.BaudRate = nBaud;
	dcb.ByteSize = 8;
	SetCommState( m_hIDComDev, &dcb );
	SetupComm( m_hIDComDev, 10000, 10000 );
	return true;
}

void WriteCom(const char *s)
{
	int n = strlen(s);
	while(n > 0) {
		DWORD dwBytesWritten = 0;
		WriteFile(m_hIDComDev, s, n, &dwBytesWritten, NULL);
		n -= dwBytesWritten;
	}
}

struct GPSEmulator : TopWindow {
	Point  pos, home;
	bool   active = false;
	int    altitude = 100;
	int    heading = 0;
	int    speed = 0;
	
	String rmc, gga;

	virtual void  MouseMove(Point p, dword keyflags);
	virtual void  MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void  LeftDown(Point p, dword keyflags);
	virtual Image CursorImage(Point p, dword keyflags);

	virtual void  Paint(Draw& w);
	
	void Do();
	
	TimeCallback tm;
	
	GPSEmulator();
};

GPSEmulator::GPSEmulator()
{
	tm.Set(-200, [=] {
		Refresh();
		if(active) {
			Do();
			WriteCom(gga);
			WriteCom(rmc);
		}
	});
}

Image GPSEmulator::CursorImage(Point p, dword keyflags)
{
	return Image::Cross();
}

void GPSEmulator::Do()
{
	String coord;

	double gps_y = 50.07 - pos.y / 1000.0 / 111.3;
	double gps_x = 14.42 + pos.x / 1000.0 / 71.6;

	auto do1 = [](double gps, char *pn)->String {
		double agps = abs(gps);
		double deg = (int)agps;
		double minute = (agps - deg) * 60;
		return Format("%.4f,%c,", 100 * deg + minute, pn[gps < 0]);
	};
	
	String gpos = do1(gps_y, "NS") + do1(gps_x, "EW");
	Time tm = GetSysTime();
	String time = Format("%02d%02d%02d", (int)tm.hour, (int)tm.minute, (int)tm.second);
	
	rmc = gga = Null;
	rmc << "$GPRMC," << time << ",A,"
	    << gpos
	    << Format("%.3f,", 0.5399568 * speed)
	    << Format("%.1f,230394,003.1,W*6A\r\n", heading);
	
	
	gga << "$GPGGA," << time << ".0,"
	    << gpos << "2,"
	    << "08,1.02,"
	    << Format("%.1f,M,-2.4,M,,0000*43\r\n", altitude);
	
	Refresh();
}

void GPSEmulator::MouseMove(Point p, dword keyflags)
{
	pos = p;
	Do();
}

void GPSEmulator::MouseWheel(Point p, int zdelta, dword keyflags)
{
	if(keyflags & K_SHIFT)
		speed += sgn(zdelta);
	else
	if(keyflags & K_CTRL)
		altitude += sgn(zdelta);
	else
		heading = (sgn(zdelta) * 10 + 360 + heading) % 360;
	
	Do();
}

void GPSEmulator::LeftDown(Point p, dword keyflags)
{
	home = pos = p;
	active = !active;

	Do();
}

void GPSEmulator::Paint(Draw& w)
{
	Size sz = GetSize();
	
	w.DrawRect(sz, White());

	String qtf;
	qtf << "[G+12 "
	    << "x: " << pos.x << "&"
	    << "y: " << pos.y << "&"
	    << "Altitude: " << altitude << "&"
	    << "LOS: " << Distance(pos, home) << "&"
	    << "Speed: " << speed << "&"
	    << "Heading: " << heading << "&"
	;
	
	if(active)
	    qtf << "\1" << rmc << gga;

	ParseQTF(qtf).Paint(w, 5, 5, sz.cx);
	
	w.DrawRect(home.x - 1, home.y - 1, 3, 3, Blue());
	
	w.DrawText(pos.x, pos.y, -10 * heading, "A", Arial(30));
}

GUI_APP_MAIN
{
	if(!OpenCom(3, 9600)) {
		Exclamation("Failed opening the !");
	}
		
	GPSEmulator().Run();
}
