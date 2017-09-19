#include <Core/Core.h>

using namespace Upp;

#include <CtrlLib/CtrlLib.h>

#include <future>

using namespace Upp;

template< class Function, class... Args>
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
Async(Function&& f, Args&&... args )
{
	std::promise<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>> p;
	auto ftr = p.get_future();
	CoWork::Schedule([=, p = pick(p)]() mutable {
		p.set_value(f(args...));
	});
	return ftr;
}

template< class Function, class... Args>
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
Async(Function&& f, Args&&... args )
{
	std::promise<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>> p;
	auto ftr = p.get_future();
	CoWork::Schedule([=, p = pick(p)]() mutable {
		p.set_value(f(args...));
	});
	return ftr;
}

GUI_APP_MAIN
{
	String h;
	auto f = Async([&h] { h = "Hello world"; });
	f.get();
	DDUMP(h);
	DDUMP(Async([] { return "Hello world"; }).get());
}
