#include <Core/Core.h>

#include <vector>

using namespace Upp;

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

template <class O, class M>
Callback new_pteback(O *object, void (M::*method)()) {
	Ptr<O> ptr = object;
	return [=] { if(ptr) (ptr->*method)(); };
}


template <class O, class M, class Q, class T1>
Callback callback1(O *object, void (M::*method)(Q), T1 t1)
{
	return [=, t1 = pick(t1)] {
		(object->*method)(t1);
	};
}

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
	Function<void (int)> l = [&](int v) { RDUMP(x); RDUMP(h); RDUMP(v); };

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
		
	//	cb = callback1(&foo, &Foo::Add, 5);
		cb();
		RDUMP(foo.x);
		
		{
			Vector<int> a{1, 2, 3, 4, 5};
			cb = callback1(&foo, &Foo::Set, pick(a));
	//		cb = [&, a = pick(a)] { foo.Set(a); };
		}
		
		DUMP(foo.v);
		cb();
		DUMP(foo.v);
		
		cb = new_pteback(&foo, &Foo::Ping);
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


