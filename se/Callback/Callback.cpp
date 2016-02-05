#include <Core/Core.h>

#include <vector>

using namespace Upp;

template<class T = void(void)> class Function { };

template<typename Res, typename... ArgTypes>
class Function<Res(ArgTypes...)> : Moveable<Function<Res(ArgTypes...)>> {
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

		Wrapper(F&& fn) : fn(pick(fn)) {}
	};

	template <class F>
	struct Wrapper2 : WrapperBase {
		Function l;
		F        fn;

		virtual Res Execute(ArgTypes... args) { l(args...); return fn(args...); }

		Wrapper2(const Function& l, F&& fn) : l(l), fn(pick(fn)) {}
	};

	WrapperBase *ptr;
	
	void Free() {
		if(ptr && AtomicDec(ptr->refcount) == 0)
			delete ptr;
	}
	
	void Copy(const Function& a) {
		ptr = a.ptr;
		if(ptr)
			AtomicInc(ptr->refcount);
	}

public:
	Function() {
		ptr = NULL;
	}
	
	Function(const Function& a) {
		Copy(a);
	}
	
	Function& operator=(const Function& a) {
		if(&a != this) {
			Free();
			Copy(a);
		}
		return *this;
	}
	
	template <class F>
	Function(F fn) {
		ptr = new Wrapper<F>(pick(fn));
	}
	
	template <class F>
	Function& operator<<(F fn) {
		WrapperBase *p2 = new Wrapper2<F>(*this, pick(fn));
		Free();
		ptr = p2;
		return *this;
	}
	
	Res operator()(ArgTypes... args) const {
		if(ptr)
			return ptr->Execute(args...);
		return Res();
	}

	~Function() {
		Free();
	}
};

#define Callback NewCallback
#define callback newcallback

#define Callback1 NewCallback1
#define callback1 newcallback1

typedef Function<void ()> Callback;

Callback callback(void (*fn)()) { return fn; }

template <class O, class M>
Callback callback(O *object, void (M::*method)()) {
	return [=] { (object->*method)(); };
}

/*
template <class O, class M, class Q, class T1>
Callback callback1(O *object, void (M::*method)(Q), T1 t1)
{
	return [=, t1 = pick(t1)] {
		(object->*method)(t1);
	};
}
*/

template <class P1>
using Callback1 = Function<void (P1)>;

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
	Vector<int> v;
	
	void Inc()                     { ++x; }
	void Add(const int& m)         { x += m; }
	void Set(const Vector<int>& s) { v = clone(s); }
};

CONSOLE_APP_MAIN
{
	String h = "123";
	int    x = 10;
	
	const int N = 1000000;

	std::function<void (int)> fn = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };
	Function<void (int)> l = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };

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
	
//	cb = callback1(&foo, &Foo::Add, 5);
	cb();
	RDUMP(foo.x);
	
	{
		Vector<int> a{1, 2, 3, 4, 5};
//		cb = callback1(&foo, &Foo::Set, pick(a));
		cb = [&, a = pick(a)] { foo.Set(a); };
	}
	
	DUMP(foo.v);
	cb();
	DUMP(foo.v);

#ifndef _DEBUG
	{
		std::vector<std::function<void (int)>> fna;
		RTIMING("std::function");
		for(int i = 0; i < N; i++)
			fna.push_back(fn);
		RDUMP(fna.size());
		fna[0](123456789);
	}
	{
		Vector<Function<void (int)>> fna;
		RTIMING("Function");
		for(int i = 0; i < N; i++)
			fna.Add(l);
		RDUMP(fna.GetCount());
		fna[0](123456789);
	}
#endif
}


