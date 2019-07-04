#include <Core/Core.h>

using namespace Upp;

static const char* sa[] = {
"1911",
"1911 AL Record vs. opponents",
"1911 AL Record vs. opponents/doc",
"1911 American League Standings",
"1911 American League standings",
"1911 Big 9 football standings",
"1911 Britannica articles needing updates progress",
"1911 College Football Composite All-Southerns",
"1911 College Football Consensus All-Americans",
"1911 Essendon Bombers premiership players",
"1911 Essendon premiership players",
"1911 Havmanden class submarines",
"1911 Helms Foundation NCAA Men's Basketball All-Americans",
"1911 MLB season by team",
"1911 Missouri Valley football standings",
"1911 NL Record vs. opponents",
"1911 NL Record vs. opponents/doc",
"1911 National League Standings",
"1911 National League standings",
"1911 Philadelphia Athletics",
"1911 Princeton Tigers football navbox",
"1911 RMFAC football standings",
"1911 SAIAA football standings",
"1911 SIAA football standings",
"1911 South Australia State Football Team",
"1911 Western Conference football standings",
"1911 college football independents records",
"1911 college football records",
"1911 films",
"1911 in Asian football (AFC)",
"1911 shipwrecks",
"1911-12 Big Nine Conference men's basketball standings",
"1911-12 Big Ten Conference men's basketball standings",
"1911-12 Essendon Bombers dual premiership players",
"1911-12 NHA season by team",
"1911-12 NHA standings",
"1911-12 Western Conference men's basketball standings",
"1911-12 in English football",
"1911-12 in European Football (UEFA)",
"1911-12 in European football (UEFA)",
"1911-12 in Scottish football",
"1911/12 Essendon Bombers dual premiership players",
"1911/12 Essendon dual premiership players",
"1911/doc",
"1911/sandbox",
"1911EB",
"1911s/doc",
"191112 Big Nine Conference men's basketball standings",
"191112 Big Ten Conference men's basketball standings",
"191112 Essendon Bombers dual premiership players",
"191112 NHA season by team",
"191112 NHA standings",
"191112 Western Conference men's basketball standings",
"191112 in English football",
"191112 in European Football (UEFA)",
"191112 in European football (UEFA)",
"191112 in Scottish football",
"1911s",
NULL,
};

CONSOLE_APP_MAIN
{
	if (String("1911s/doc") < String("1911s"))
		NEVER();
	Vector<String> sv;
	for (int i = 0; sa[i]; ++i)
		sv.Add(sa[i]);
	Sort(sv);
	RDUMPC(sv);
}
