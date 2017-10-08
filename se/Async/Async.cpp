#include <Core/Core.h>
#include <future>

using namespace Upp;

template <class D, class P, class F, class... Args>
void set_future_value(D *dummy, P&& p, F&& f, Args&&... args)
{
	p.set_value(f(args...));
}

template <class P, class F, class... Args>
void set_future_value(void *dummy, P&& p, F&& f, Args&&... args)
{
	f(args...);
	p.set_value();
}

template< class Function, class... Args>
std::future<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>>
Async2(Function&& f, Args&&... args )
{
	std::promise<std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)>> p;
	auto ftr = p.get_future();
	CoWork::Schedule([=, p = pick(p)]() mutable {
		std::result_of_t<std::decay_t<Function>(std::decay_t<Args>...)> *dummy = NULL;
		set_future_value(dummy, pick(p), pick(f));
	});
	return ftr;
}

CONSOLE_APP_MAIN
{
	String h;
	auto f = Async2([&h] { h = "Hello world"; });
	f.get();
	DDUMP(h);
	DDUMP(Async2([] { return "Hello world"; }).get());
	
	auto eh = Async2([] { throw "error"; });
	try {
		eh.get();
	}
	catch(...) {
		DLOG("Exception!");
	}
	
	
	auto p = Async(
	
	p.Cancel();
	
	
}

