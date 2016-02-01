#include <Core/Core.h>

using namespace Upp;

template<class T = void(void)> class Lambda { };

template<typename Res, typename... ArgTypes>
class Lambda<Res(ArgTypes...)> : Moveable<Lambda<Res(ArgTypes...)>> {
	struct WrapperBase {
		virtual Res Execute(ArgTypes... args) = 0;
		virtual ~WrapperBase() {}
	};

	template <class F>
	struct SmallWrapper : WrapperBase {
		F fn;
		virtual Res Execute(ArgTypes... args) { return fn(args...); }
		
		SmallWrapper(F fn) : fn(fn) {}
	};

	template <class F, int fsz>
	struct DualWrapper : WrapperBase {
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
		LARGE,
		KIND = 63,
		MAXSMALL = KIND,
	};
	
	union {
		LargeWrapperBase *large;
		byte              data[64];
	} data;
	
	byte& Kind()               { return data.data[KIND]; }
	byte  Kind() const         { return data.data[KIND]; }
	WrapperBase *Small() const { return (WrapperBase *)(data.data); }
	
	void Free() {
		if(Kind() == LARGE) {
			if(AtomicDec(data.large->refcount) == 0)
				delete data.large;
		}
		else
			Small()->WrapperBase::~WrapperBase();
	}
	
	void Copy(const Lambda& a) {
		if(a.Kind() == LARGE) {
			data.large = a.data.large;
			Kind() = LARGE;
			AtomicInc(data.large->refcount);
			return;
		}
		data = a.data;
//		Kind() = a.Kind();
//		memcpy(data.data, a.data.data, Kind());
	}

	template <class F>
	void Create(const F& fn) {
		DUMP(sizeof(SmallWrapper<F>));
		if(sizeof(SmallWrapper<F>) <= MAXSMALL) {
			::new(data.data) SmallWrapper<F>(fn);
			Kind() = sizeof(SmallWrapper<F>);
		}
		else {
			data.large = new LargeWrapper<F>(fn);
			Kind() = LARGE;
		}
	}

public:
	Lambda() {
		Kind() = EMPTY;
	}
	
	Lambda(const Lambda& a) {
		Copy(a);
	}
	
	Lambda& operator=(const Lambda& a) {
		if(&a != this) {
			Free();
			Copy(a);
		}
		return *this;
	}
	
	template <class F>
	Lambda(const F& fn) {
		Create(fn);
	}
	
	template <class F>
	Lambda& operator<<(const F& fn) {
		LOG("operator<<");
		DUMP(sizeof(SmallWrapper<F>));
		DUMP(sizeof(F));
		Lambda h = *this;
		auto l = [=](ArgTypes... args) -> Res { h(args...); fn(args...); };
		DUMP(sizeof(l));
		Free();
		Create(l);
		return *this;
	}
	
	Res operator()(ArgTypes... args) const {
		if(Kind() == LARGE)
			return data.large->Execute(args...);
		if(Kind())
			return Small()->Execute(args...);
		return Res();
	}

	~Lambda() {
		Free();
	}
};

#define Callback NewCallback
#define callback newcallback

#define Callback1 NewCallback1
#define callback1 newcallback1

typedef Lambda<void ()> Callback;

Callback callback(void (*fn)()) { return fn; }

template <class O, class M>
Callback callback(O *object, void (M::*method)()) {
	return [=] { (object->*method)(); };
}

template <class O, class M, class T1>
Callback callback1(O *object, void (M::*method)(T1), T1 t1) {
	return [=] { (object->*method)(t1); };
}

template <class P1>
using Callback1 = Lambda<void (P1)>;

template <class O, class M, class P1>
Callback1<P1> callback(O *object, void (M::*method)(P1)) {
	return [=](P1 p1) { (object->*method)(p1); };
}

void Test1()
{
	LOG("Test1");
}

struct Foo {
	int x = 0;
	
	void Inc()             { ++x; }
	void Add(int m) { x += m; }
};

CONSOLE_APP_MAIN
{
	String h = "123";
	int    x = 10;
	
	const int N = 20000000;
	
	std::function<void (int)> fn = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };
	Lambda<void (int)> l = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };

	LOG("----------- COMBINE");
	l << [&](int v) { DDUMP(v + 1); };
	l(77777);

	Callback cb;
	cb = callback(Test1);
	cb();
	
	Foo foo;
	DDUMP(foo.x);
	cb = callback(&foo, &Foo::Inc);
	
	cb();
	DDUMP(foo.x);

	Callback1<int> cb1 = callback(&foo, &Foo::Add);
	cb1(10);
	DDUMP(foo.x);
	
	cb = callback1(&foo, &Foo::Add, 5);
	cb();
	DDUMP(foo.x);

#ifndef _DEBUG
	{
		std::function<void (int)> fna[1024];
		RTIMING("std::function");
		for(int i = 0; i < N; i++)
			fna[i & 1023] = fn;
		fna[0](123456789);
	}
	{
		Lambda<void (int)> fna[1024];
		RTIMING("Lambda");
		for(int i = 0; i < N; i++)
			fna[i & 1023] = l;
		fna[0](123456789);
	}
#endif
}


