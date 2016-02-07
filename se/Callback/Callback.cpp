#include <Core/Core.h>

#include <vector>

using namespace Upp;

#define Callback NewCallback
#define callback newcallback
#define pteback  newpteback

#define Callback1 NewCallback1
#define callback1 newcallback1
#define pteback1  newpteback1

template<typename>
class Function;

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
	
	static void Free(WrapperBase *ptr) {
		if(ptr && AtomicDec(ptr->refcount) == 0)
			delete ptr;
	}
	
	void Copy(const Function& a) {
		ptr = a.ptr;
		if(ptr)
			AtomicInc(ptr->refcount);
	}

public:
	Function() { ptr = NULL; }
	Function(const Function& a) { Copy(a); }
	
	Function& operator=(const Function& other) { WrapperBase *b = ptr; Copy(other); Free(b); return *this; }
	
	template <class F> Function(F fn) { ptr = new Wrapper<F>(pick(fn)); }
	
	template <class F>
	Function& operator<<(F fn) {
		WrapperBase *b = ptr;
		ptr = new Wrapper2<F>(*this, pick(fn));
		Free(b);
		return *this;
	}
	
	Res operator()(ArgTypes... args) const { return ptr ? ptr->Execute(args...) : Res(); }
	
	operator bool() const { return ptr; }
	void Clear()          { Free(ptr); ptr = NULL; }

	~Function()           { Free(ptr); }
};

typedef Function<void ()> Callback;
template <class P1> using Callback1 = Function<void (P1)>;

#define classA
#define A_
#define A_a_
#define a_

#include "CallbackN.i"

#define CB_hasA_

#define classA    , class A1
#define A_        A1
#define A_a_      A1 a1
#define a_        a1

#include "CallbackN.i"

#define classA    , class A1, class A2
#define A_        A1, A2
#define A_a_      A1 a1, A2 a2
#define a_        a1, a2

#include "CallbackN.i"

#define classA    , class A1, class A2, class A3
#define A_        A1, A2, A3
#define A_a_      A1 a1, A2 a2, A3 a3
#define a_        a1, a2, a3

#include "CallbackN.i"

#define classA    , class A1, class A2, class A3, class A4
#define A_        A1, A2, A3, A4
#define A_a_      A1 a1, A2 a2, A3 a3, A4 a4,
#define a_        a1, a2, a3, a4

#include "CallbackN.i"

#define classA    , class A1, class A2, class A3, class A4, class A5
#define A_        A1, A2, A3, A4, A5
#define A_a_      A1 a1, A2 a2, A3 a3, A4 a4, A5 a5
#define a_        a1, a2, a3, a4, a5

#include "CallbackN.i"

void Test1()
{
	LOG("Test1");
}

struct Foo : Pte<Foo> {
	int x = 0;
	Vector<int> v;
	
	void Ping()                    { RLOG("Ping " << ++x); }
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
	Function<void (int64)> l = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };
	
	Function<void (int)> l1 = l;
	
	LOG("----------- Different value");
	
	l1(10000);

	LOG("----------- COMBINE");
	l << [&](int v) { RDUMP(v + 1); };
	
	l(77777);
	l << l;
	l(999);

	Callback cb;
	cb = callback(Test1);
	cb();
	
	{
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
		
		{
			Vector<int> a{1, 2, 3, 4, 5};
	//		cb = newcallback1(&foo, &Foo::Set, pick(a));
	//		cb = [&, a = pick(a)] { foo.Set(a); };
		}
		
		DUMP(foo.v);
		cb();
		DUMP(foo.v);
		
		cb = pteback(&foo, &Foo::Ping);
		cb();
	}
	
	LOG("About to ping");
	cb();
	
	

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


