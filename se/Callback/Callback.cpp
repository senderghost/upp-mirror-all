#include <Core/Core.h>

using namespace Upp;

template<class T = void(void)> class NewCallback { };

template<typename Res, typename... ArgTypes>
class NewCallback<Res(ArgTypes...)> {
	struct WrapperBase {
		virtual Res Execute(ArgTypes... args) = 0;
	};

	template <class F>
	struct SmallWrapper : WrapperBase {
		F fn;
		virtual Res Execute(ArgTypes... args) { return fn(args...); }
		
		SmallWrapper(F fn) : fn(fn) {}
	};

	struct LargeWrapperBase : WrapperBase {
		Atomic refcount;
		
		LargeWrapperBase() { refcount = 1; }
	};

	template <class F>
	struct LargeWrapper : LargeWrapperBase {
		F fn;
		virtual Res Execute(ArgTypes... args) { return fn(args...); }

		LargeWrapper(F fn) : fn(fn) {}
	};

	enum {
		EMPTY,
		SMALL,
		LARGE,
		KIND = 63,
		MAXSMALL = KIND,
	};
	
	union {
		LargeWrapperBase *large;
		byte              data[64];
	} data;
	
	byte& Kind() { return data.data[KIND]; }
	
	void Free() {
		if(Kind() == LARGE)
			if(AtomicDec(data.large->refcount) == 0)
				delete data.large;
	}
	
public:
	template <class F>
	NewCallback() {
		Kind() = EMPTY;
	}
	
	template <class F>
	NewCallback(const F& fn) {
		DDUMP(sizeof(SmallWrapper<F>));
		if(sizeof(SmallWrapper<F>) <= MAXSMALL) {
			ASSERT(::new(data.data) F(fn) == (F *)data.data);
			Kind() = SMALL;
		}
		else {
			data.large = new LargeWrapper<F>(fn);
			Kind() = LARGE;
		}
	}
	
	Res operator()(ArgTypes... args) {
		if(Kind() == LARGE)
			return data.large->Execute(args...);
		if(Kind() == SMALL)
			return ((WrapperBase *)(data.data))->Execute(args...);
		return Res();
	}

	~NewCallback() {
		Free();
	}
};

CONSOLE_APP_MAIN
{
	String h = "123";
	int    x = 10;
	NewCallback<void (int)> fn = [&](int v) { DDUMP(x); DDUMP(h); DDUMP(v); };
	
	fn(11111);
	
	NewCallback<> cb = [&] { LOG("Hello world!"); };
	
	cb();

/*	
	std::function<void ()> fn2 = [=] { DDUMP(x); DDUMP(h); };
	
	fn2();
*/
}
