#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	String text = "\xC4\x8C\x65\x73\x6B\xC3\xBD\x20\xEC\x95\x84\xEC\xB9\xA8\xEA\xB8\x80\x0A\xF0\x9F\x98\x8D\x1F";
	
	DUMPHEX(text);
	
	String json = AsJSON(text);
	
	DUMP(json);
	
	ASSERT(json == "\"Český 아침글\\n\\uD83D\\uDE0D\\u001F\"");
	
	String text2 = ParseJSON(json);
	
	DUMP(text2);
	DUMPHEX(text2);
	
	ASSERT(text2 == text);
	
	String h127;
	h127.Cat(127);
	ASSERT(AsJSON(h127) == "\"\\u007F\"");
	
	LOG("=================== OK");
}
