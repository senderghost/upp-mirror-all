#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	try {
		throw LoadingError();
	}
	catch(LoadingError)
	{
		LOG("Catch");
	}
}
