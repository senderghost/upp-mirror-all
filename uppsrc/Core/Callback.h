enum _CNULL { CNULL };

template <class D, class S>
inline D brutal_cast(const S& source) { return *(D *)&source; }

#include "Cbgen.h"

template <class OBJECT_, class METHOD_, class T>
struct CallbackMethodActionArgPte : public CallbackAction {
	Ptr<OBJECT_>  object;
	METHOD_       method;
	T             arg;

	void    Execute() { if(object) (object->*method)(arg); }

	CallbackMethodActionArgPte(OBJECT_ *object, METHOD_ method, T arg)
	: object(object), method(method), arg(arg) {}
};

template <class Object, class M, class P, class T>
Callback pteback1(Object *object, void (M::*method)(P), T arg) {
	return Callback(new CallbackMethodActionArgPte<Object, void (M::*)(P), T>(object, method, arg));
}

template <class OBJECT_, class METHOD_, class T>
struct CallbackMethodActionArg : public CallbackAction {
	OBJECT_  *object;
	METHOD_   method;
	T         arg;

	void    Execute() { (object->*method)(arg); }

	CallbackMethodActionArg(OBJECT_ *object, METHOD_ method, T arg)
	: object(object), method(method), arg(arg) {}
};

template <class Object, class M, class P, class T>
Callback callback1(Object *object, void (M::*method)(P), T arg) {
	return Callback(new CallbackMethodActionArg<Object, void (M::*)(P), T>
	                    (object, method, arg));
}

template <class Object, class M, class P, class T>
Callback callback1(const Object *object, void (M::*method)(P) const, T arg) {
	return Callback(new CallbackMethodActionArg<const Object, void (M::*)(P) const, T>
	                    (object, method, arg));
}

template <class F, class T, class HC = F>
struct CallbackActionCallArg : public CallbackAction {
	F         fn;
	T         arg;
	void    Execute() { fn(arg); }

	CallbackActionCallArg(F fn, T arg) : fn(fn), arg(arg) {}
};

template <class T, class P>
Callback callback1(void (*fn)(P), T arg)
{
	return Callback(new CallbackActionCallArg<void (*)(P), T, uintptr_t>(fn, arg));
}

template <class OBJECT_, class METHOD_, class P1, class T>
struct CallbackMethodActionArg1Pte : public Callback1Action<P1> {
	Ptr<OBJECT_>  object;
	METHOD_       method;
	T             arg;
	void    Execute(P1 p1) { if(object) (object->*method)(p1, arg); }

	CallbackMethodActionArg1Pte(OBJECT_ *object, METHOD_ method, T arg)
	: object(object), method(method), arg(arg) {}
};

template <class Object, class M, class P1, class P, class T>
Callback1<P1> pteback1(Object *object, void (M::*method)(P1, P), T arg) {
	return Callback1<P1>(new CallbackMethodActionArg1Pte<Object, void (M::*)(P1, P), P1, T> (object, method, arg));
}

template <class OBJECT_, class METHOD_, class P1, class T>
struct CallbackMethodActionArg1 : public Callback1Action<P1> {
	OBJECT_  *object;
	METHOD_   method;
	T         arg;
	void    Execute(P1 p1) { (object->*method)(p1, arg); }

	CallbackMethodActionArg1(OBJECT_ *object, METHOD_ method, T arg)
	: object(object), method(method), arg(arg) {}
};

template <class Object, class M, class P1, class P, class T>
Callback1<P1> callback1(Object *object, void (M::*method)(P1, P), T arg) {
	return Callback1<P1>(new CallbackMethodActionArg1<Object, void (M::*)(P1, P), P1, T>
	                         (object, method, arg));
}

template <class Object, class M, class P1, class P, class T>
Callback1<P1> callback1(const Object *object, void (M::*method)(P1, P) const, T arg) {
	return Callback1<P1>(new CallbackMethodActionArg1<const Object, void (M::*)(P1, P) const, P1, T>
	                         (object, method, arg));
}

template <class F, class P1, class T, class HC = F>
struct CallbackActionCallArg1 : Callback1Action<P1> {
	F         fn;
	T         arg;
	void    Execute(P1 p1) { fn(p1, arg); }

	CallbackActionCallArg1(F fn, T arg) : fn(fn), arg(arg) {}
};

template <class T, class P1, class P>
Callback1<P1> callback1(void (*fn)(P1, P), T arg)
{
	return Callback1<P1>(new CallbackActionCallArg1<void (*)(P1, P), P1, T, uintptr_t>(fn, arg));
}

template <class T, class P>
Callback callback1(Callback1<P> cb, T arg)
{
	return Callback(new CallbackActionCallArg<Callback1<P>, T>(cb, arg));
}

template <class T, class P1, class P>
Callback1<P1> callback1(Callback2<P1, P> cb, T arg) {
	return Callback1<P1>(new CallbackActionCallArg1<Callback2<P1, P>, P1, T>(cb, arg));
}

template <class P1>
bool Gate1<P1>::Execute(P1 p1) const {
	return (void *)action == (void *)1 ? true : action ? action->Execute(p1) : false;
}

template <class P1, class P2>
bool Gate2<P1, P2>::Execute(P1 p1, P2 p2) const {
	return (void *)action == (void *)1 ? true : action ? action->Execute(p1, p2) : false;
}

template <class P1, class P2, class P3>
bool Gate3<P1, P2, P3>::Execute(P1 p1, P2 p2, P3 p3) const {
	return (void *)action == (void *)1 ? true : action ? action->Execute(p1, p2, p3) : false;
}

template <class OBJECT_, class METHOD_, class T1, class T2>
struct CallbackMethodActionArg2Pte : public CallbackAction {
	Ptr<OBJECT_>  object;
	METHOD_       method;
	T1            arg1;
	T2            arg2;
	void    Execute() { if(object) (object->*method)(arg1, arg2); }

	CallbackMethodActionArg2Pte(OBJECT_ *object, METHOD_ method, T1 arg1, T2 arg2)
	: object(object), method(method), arg1(arg1), arg2(arg2) {}
};

template <class Object, class R, class O, class A, class B, class T1, class T2>
Callback pteback2(Object *object, R (O::*method)(A, B), T1 arg1, T2 arg2) {
	return Callback(new CallbackMethodActionArg2Pte<Object, R (O::*)(A, B), T1, T2>
	                    (object, method, arg1, arg2));
}

template <class OBJECT_, class METHOD_, class T1, class T2>
struct CallbackMethodActionArg2 : public CallbackAction {
	OBJECT_  *object;
	METHOD_   method;
	T1        arg1;
	T2        arg2;
	void    Execute() { (object->*method)(arg1, arg2); }

	CallbackMethodActionArg2(OBJECT_ *object, METHOD_ method, T1 arg1, T2 arg2)
	: object(object), method(method), arg1(arg1), arg2(arg2) {}
};

template <class Object, class R, class O, class A, class B, class T1, class T2>
Callback callback2(Object *object, R (O::*method)(A, B), T1 arg1, T2 arg2) {
	return Callback(new CallbackMethodActionArg2<Object, R (O::*)(A, B), T1, T2>
	                    (object, method, arg1, arg2));
}

template <class Object, class R, class O, class A, class B, class T1, class T2>
Callback callback2(const Object *object, R (O::*method)(A, B) const, T1 arg1, T2 arg2) {
	return Callback(new CallbackMethodActionArg2<Object, R (O::*)(A, B) const, T1, T2>
	                    (object, method, arg1, arg2));
}

template <class X, class T1, class T2, class HC = X>
struct CallbackActionCallArg2 : public CallbackAction {
	X         x;
	T1        arg1;
	T2        arg2;
	void    Execute() { x(arg1, arg2); }

	CallbackActionCallArg2(X x, T1 arg1, T2 arg2) : x(x), arg1(arg1), arg2(arg2) {}
};

template <class R, class A, class B, class T1, class T2>
Callback callback2(R (*fn)(A, B), T1 arg1, T2 arg2) {
	return Callback(new CallbackActionCallArg2<R (*)(A, B), T1, T2, uintptr_t>(fn, arg1, arg2));
}

template <class A, class B, class T1, class T2>
Callback callback2(Callback2<A, B> cb, T1 arg1, T2 arg2) {
	return Callback(new CallbackActionCallArg2<Callback2<A, B>, T1, T2>(cb, arg1, arg2));
}

#define THISBACK(x)               callback(this, &CLASSNAME::x)
#define THISBACK1(x, arg)         callback1(this, &CLASSNAME::x, arg)
#define THISBACK2(m, a, b)        callback2(this, &CLASSNAME::m, a, b)

#define PTEBACK(x)                pteback(this, &CLASSNAME::x)
#define PTEBACK1(x, arg)          pteback1(this, &CLASSNAME::x, arg)
#define PTEBACK2(m, a, b)         pteback2(this, &CLASSNAME::m, a, b)

template <class T>
class CallbackArgTarget
{
	T result;

	void SetResult(const T& value)      { result = value; }

public:
	typedef CallbackArgTarget CLASSNAME;

	operator const T&()                 { return result; }
	bool IsNullInstance() const         { return IsNull(result); }

	Callback operator[](const T& value) { return THISBACK1(SetResult, value); }

	CallbackArgTarget()                 { result = Null; }
};
