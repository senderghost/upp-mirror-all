#include <Core/Core.h>

using namespace Upp;

template<class T = void(void)> class Lambda { };

template<typename Res, typename... ArgTypes>
class Lambda<Res(ArgTypes...)> : Moveable<Lambda<Res(ArgTypes...)>> {
	struct WrapperBase {
		Atomic  refcount;

		virtual Res Execute(ArgTypes... args) = 0;
		
		WrapperBase() { refcount = 1; }
		virtual ~WrapperBase() {}
	};

	template <class F>
	struct Wrapper : WrapperBase {
		F fn;
		virtual Res Execute(ArgTypes... args) { return fn(args...); }

		Wrapper(F fn) : fn(fn) {}
	};

	template <class F>
	struct Wrapper2 : WrapperBase {
		Lambda l;
		F      fn;

		virtual Res Execute(ArgTypes... args) { l(args...); return fn(args...); }

		Wrapper2(const Lambda& l, F fn) : l(l), fn(fn) {}
	};

	WrapperBase *ptr;
	
	void Free() {
		if(ptr && AtomicDec(ptr->refcount) == 0)
			delete ptr;
	}
	
	void Copy(const Lambda& a) {
		ptr = a.ptr;
		AtomicInc(ptr->refcount);
	}

public:
	Lambda() {
		ptr = NULL;
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
		ptr = new Wrapper<F>(fn);
	}
	
	template <class F>
	Lambda& operator<<(const F& fn) {
		WrapperBase *p2 = new Wrapper2<F>(*this, fn);
		Free();
		ptr = p2;
		return *this;
	}
	
	Res operator()(ArgTypes... args) const {
		if(ptr)
			return ptr->Execute(args...);
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
	l << [&](int v) { RDUMP(v + 1); };
	l(77777);
	l << l;
	l(999);

	Callback cb;
	cb = callback(Test1);
	cb();
	
	Foo foo;
	RDUMP(foo.x);
	cb = callback(&foo, &Foo::Inc);
	
	cb();
	RDUMP(foo.x);

	Callback1<int> cb1 = callback(&foo, &Foo::Add);
	cb1(10);
	RDUMP(foo.x);
	
	cb = callback1(&foo, &Foo::Add, 5);
	cb();
	RDUMP(foo.x);

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


