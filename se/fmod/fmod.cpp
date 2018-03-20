#include <Core/Core.h>
#include <cstddef>
#include <type_traits>
#include <memory>

using namespace Upp;

int GetMonthsP2(Date since, Date till)
{
	return 12 * till.year + till.month - (12 * since.year + since.month) + (till.day > since.day);
}

double fmod2(double a, double b)
{
	return a - trunc(a / b) * b;
}

CONSOLE_APP_MAIN
{
	DDUMP(sin(1e100));
	DDUMP(sin(1.1e100));

	DDUMP(floor(-1.23));
	DDUMP(round(-1.23));
	DDUMP(floor(1E100));
	DDUMP(fmod(1, M_2PI));
	DDUMP(fmod(10, M_2PI));
	DDUMP(fmod(-1, M_2PI));
	DDUMP(fmod(-10, M_2PI));
	DDUMP(fmod(1E100, M_2PI));
	DDUMP(fmod(1.1E100, M_2PI));

	DDUMP(fmod2(1, M_2PI));
	DDUMP(fmod2(10, M_2PI));
	DDUMP(fmod2(-1, M_2PI));
	DDUMP(fmod2(-10, M_2PI));
	DDUMP(fmod2(1E100, M_2PI));
	DDUMP(fmod2(1.1E100, M_2PI));
	
	double x = 1;
	for(int i = 0; i < 200; i++) {
		DLOG("=====================");
		DDUMP(x);
		DDUMP(fmod(x, M_2PI));
		DDUMP(trunc(x / M_2PI));
		DDUMP(trunc(x / M_2PI) * M_2PI);
		DDUMP(x - trunc(x / M_2PI) * M_2PI);
		DDUMP(x / M_2PI);
		DDUMP((x / M_2PI - trunc(x / M_2PI)));
		DDUMP((x / M_2PI - trunc(x / M_2PI)) * M_2PI);
		DDUMP(trunc(x / M_2PI) * M_2PI + fmod(x, M_2PI));
		DDUMP(fmod2(x, M_2PI));
		x *= 1.2;
	}
}