#include <Core/Core.h>

#include <atomic>
#include <thread>
#include <mutex>

using namespace Upp;

void Foo(const String& h)
{
	DUMP(h);
}

void Execute(Callback cb)
{
	cb();
}

/*
template <class A, class B>
struct Tuple {
	A a;
	B b;
};

template <class A, class B, class C>
struct Tuple {
	A a;
	B b;
	C c;
};
*/
/*
template <size_t N, typename... T>
struct Choose;

template <size_t N, typename H, typename... T>
struct Choose <N, H, T...> : Choose <N-1, T...> { };


template <Args... args>
struct Tuple : TupleN< sizeof(args...) >
{
	
};
*/

template <int N, typename... T>
struct TupleN;

template <typename A>
struct TupleN<1, A>
{
	typedef A type;

	A a;
};

template <typename B, typename... T>
struct TupleN<2, B, T...> : TupleN<1, T...>
{
	B b;
};

template <typename... T>
struct Tuple : TupleN<sizeof...(T), T...>
{
};

/*
template <int N, typename C, typename... T>
struct TupleN<3, C, T...> : TupleN<2, T...>
{
	C c;
};

template <int N, typename D, typename... T>
struct TupleN<4, D, T...> : TupleN<3, T...>
{
	D d;
};
*/

#ifdef _DEBUG
namespace Upp {
void *MemoryAlloc_(size_t sz);
void  MemoryFree_(void *ptr);
};
#else
void *MemoryAlloc_(size_t sz) { return MemoryAlloc(sz); }
void  MemoryFree_(void *ptr) { return MemoryFree(ptr); }
#endif


__m128i val1, val2;
__m128i *vp1 = &val1, *vp2 = &val2;
int count;

force_inline bool Equal16(const char *a, const char *b)
{
	__m128i xmm0 = _mm_loadu_si128((__m128i*)(a));
	__m128i xmm1 = _mm_loadu_si128((__m128i*)(b));
	xmm0 = _mm_cmpeq_epi8(xmm0, xmm1);
	return (_mm_movemask_epi8(xmm0) == 0xffff);
}

force_inline void SetZero16(char *t)
{
	_mm_storeu_si128((__m128i*)t, _mm_setzero_si128());
}

force_inline void Copy16(void *t, const void *s)
{
	_mm_storeu_si128((__m128i*)t, _mm_loadu_si128((__m128i*)s));
}

force_inline void SetZero32(char *t)
{
	SetZero16(t);
	SetZero16(t + 16);
}

char str1[128];
char str2[128];

int acount;

std::atomic<bool> test;

std::atomic<int>  test2 = 10;
std::atomic<int>  r3;

void foo() {
	LOG("HERE!");
}

std::once_flag flag1;

CONSOLE_APP_MAIN
{
	DDUMP(sizeof(CONDITION_VARIABLE));
	return;

	static StaticMutex mtx;
	
	mtx.Enter();
	
	
	int val = --test2;
	r3 = val;
	
	for(int i = 0; i < 10; i++)
		ONCELOCK {
			RLOG("HI!");
		}
	return;
	
	if(test.load(std::memory_order_acquire))
		count++;

	if(--test2 == 0)
		count++;
	

	return;


	DUMP(InitializeConditionVariable);
	DUMP(SleepConditionVariableCS);
	DUMP(IsWinVista());
	return;
	
	
	{
		Function<void ()> a = [] { LOG("A"); };
		Function<void ()> b = [] { LOG("B"); };
		
		Swap(a, b);
		
		a();
	}
	
	{
		String& a = Single<String>('A', 100);
		String& b = Single<String>("Hello!");
		String& c = Single<String>("Hello2");
		String& d = Single<String>();
		
		DUMP(&a);
		DUMP(&b);
		DUMP(&c);
		DUMP(&d);
		return;
	}
	
	{
		String a = "Ahojsalsdkjfglsdj;flgjksdlgksdlkfg lsdkjfglksdj fg;";
		String b = a + a;
		a = AsString(Random());
		b = AsString(Random());
		if(a == b)
			acount++;
		if(memcmp(~a, ~b, a.GetLength()) == 0)
			acount++;
	}
	ValueArray va;
	
	{
		Value a = "ahoj";
		
		Value b = a;
		
		a = b;
	}

	{
		std::string a = "Ahoj";
		std::string b;
		b = pick(a);
	}
	
	
	String *s = tiny_new<String>('x', 100);
	RDUMP(*s);
	tiny_delete(s);
	return;


	char q1[] = "Ahoj kamarade jak se mas 023456789";
	char q2[] = "Ahoj kamarade jak se mas 023456789";
	
	if(Equal16(q1, q2))
		RDUMP("Equal 1");
	
	q1[0] = 'a';

	if(Equal16(q1, q2))
		RDUMP("Equal 2");
	
	String sh;
	
	Cout() << sh;

	MemoryFree48(MemoryAlloc48());
	
	SetZero32(str1);
	
//	Copy16(str2, str1);

	if(Equal16(q1, q2))
		RDUMP("Equal 3");
	
	return;
	MemoryFree48(MemoryAlloc48());
	MemoryFree48(MemoryAlloc48());
	MemoryAlloc_(32);
//	MemoryFree_(MemoryAlloc_(100000));
	MemoryFree_(MemoryAlloc_(32));
//	MemoryFree_(MemoryAlloc_(10000));
	
	for(int i : { 16, 23, 32, 200, 500, 800, 1000, 1200, 100000 }) {
		RDUMP(i);
		void *ptr1 = MemoryAlloc(i);
		RDUMP(ptr1);
		MemoryFree(ptr1);
	}

	struct Prec {
		Prec   *ptr;
		Atomic  n;
	};
	
	DUMP(sizeof(Prec));

	DUMP(sizeof(Atomic));

	{
		Vector<int> a{1, 2}, b;
		
		a << 1 << 2 << 3;
		
		b = clone(a);
		DUMP(a);
		DUMP(b);
		a = pick(b);
		DUMP(a);
		DUMP(b);
	}
	
	
	TupleN<2, int, String> tpl;
/*	
	Tuple<int, String> tpl2;
	tpl2.a = 10;
	tpl2.b = 20;
	
*/	Cout() << String("Hello!") << 1;

	auto x = callback(Foo);
	x("AAA");
	
	auto y = callback1(x, "B");
	y();

	Callback h([=] { LOG("FUN"); });
	Callback h1([=] { LOG("FUN"); });
	
	
	Vector<int> v { 1, 2, 3, 2, 1 };
	
	DUMP(Sum(v));
	
	DUMP(FindMin(v));
	DUMP(FindMax(v));
	
	v.Add(123);
	v.Add(pick(123));

	{
		Vector<String> vs;
		String h;
		vs.Add(h);
		vs.Add(pick(h));
		vs.Add(h + "123");
		vs.Add("aaa");
	}
	
	String a = AsString(123) + "123";
	
	RDUMP(a);

	WString ws;
	ws = a.ToWString();

	RDUMP(ws);
//	h = [] { LOG("FUN2"); };

	
//	Execute([=] { LOG("Execute"); });
/*	
	h();
	h();
*/
}
