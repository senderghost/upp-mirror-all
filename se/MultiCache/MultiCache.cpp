#include <Core/Core.h>

using namespace Upp;

struct Data {
	int x;
	int y;
	
	void Serialize(Stream& s)         { s % x % y; }
	void Compute(int& output) const   { output = x * y; }
	typedef int Output;
	
	Data(int x, int y) : x(x), y(y) {}
};

struct Data2 {
	int x;
	int y;
	
	void Serialize(Stream& s)         { s % x % y; }
	void Compute(int& output) const   { output = x + y; }
	typedef int Output;
	
	Data2(int x, int y) : x(x), y(y) {}
};

struct AnyCache {
	LRUCache<Any> cache;

	template <class I>
	struct Maker : LRUCache<Any>::Maker {
		const I& input;
		
		virtual String Key() const
		{
			Sha1Stream hash;
			const_cast<I&>(input).Serialize(hash);
			byte h[20];
			hash.Finish(h);
			return String(h, 20);
		}
		virtual int    Make(Any& output) const
		{
			input.Compute(output.Create<I::Output>());
			return 1;
		}
		
		Maker(const I& input) : input(input) {}
	};
	
	template <class I>
	typename const I::Output& Get(const I& input) {
		Maker<I> m(input);
		return cache.Get(m).Get<typename const I::Output>();
	}
	
	void Shrink(int count) { cache.Shrink(INT_MAX, count); }

};

CONSOLE_APP_MAIN
{
	AnyCache cache;
	
	DDUMP(cache.Get(Data(3, 4)));
	DDUMP(cache.Get(Data2(3, 4)));
	DDUMP(cache.Get(Data(3, 4)));
	DDUMP(cache.Get(Data2(3, 4)));
}
