#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	HttpRequest::Trace();
	HttpRequest("https://epsg.io/5072").Execute();
}
