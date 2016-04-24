#include <Core/Core.h>

using namespace Upp;

CONSOLE_APP_MAIN
{
	CoWork pl;
	
	String out;
	
	for(int i = 0; i < 1000; i++)
		pl.Step(0, [=, &pl] {
			double x = Randomf();
			DDUMP(x);
			pl.Step(1, [=, &pl] {
				double y = exp(x);
				pl.Step(2, [=, &pl] {
					LOG(AsString(y));
				});
			});
		});
}
