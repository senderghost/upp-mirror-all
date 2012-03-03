#include "Json.h"

using namespace Upp;

struct Test {
	int a, b;
	
	void Jsonize(JsonIO& io) {
		io("a", a)
		  ("b", b);
	}
	
	void Serialize(Stream& s) {
		s % a % b;
	}
};

template <class T>
void TestJsonize(T x)
{
	DLOG("==============================");
	DDUMP(x);
	String json = StoreAsJson(x);
	DDUMP(json);
	T y;
	CHECK(LoadFromJson(y, json));
	DDUMP(y);
	ASSERT(x == y);
	
	if(Value(x).Is<bool>())
		return;

	json = StoreAsJson((T)Null);
	DDUMP(json);
	CHECK(LoadFromJson(y, json));
	DDUMP(y);
	ASSERT(IsNull(y));
}

struct TestValue : ValueType<TestValue, 678> {
	int x;
	String ToString() const { return AsString(x); }
	void Serialize(Stream& s) { s % x; }
	
	operator Value() const  { return RichToValue(*this); }
	
	TestValue() { x = 0; }
};

INITBLOCK {
	Value::Register<TestValue>();
}


CONSOLE_APP_MAIN
{
	{
		TestValue a;
		a.x = 1234567;
		Value v = a;
		DDUMP(v);
		String h = StoreAsString(v);
		Value vv;
		LoadFromString(vv, h);
		DDUMP(vv);
	}
	
	TestJsonize((int)1);
	TestJsonize(true);
	TestJsonize(false);
	TestJsonize(1.1);
	TestJsonize(String("hello"));
	TestJsonize(WString("world"));
	TestJsonize(Date(2012, 7, 20));
	TestJsonize(Time(2012, 7, 20, 20, 55, 59));
	TestJsonize(I64(123456));
	TestJsonize(I64(INT_MAX) + I64(INT_MAX));
	TestJsonize(Complex(1.23, 1.33));

	ArrayMap<double, Test> maptest;
	Array<Test> test;
	for(int i = 0; i < 10; i++) {
		Test t;
		t.a = 1 + i;
		t.b = 23 + i;
		test.Add(t);
		maptest.Add(1.0 / (i + 1), t);
	}
	
	RDUMP(StoreAsJson(test));
	RDUMP(StoreAsJsonValue(maptest));
	RDUMP(StoreAsJson(maptest));

	Index<String> x;
	x.Add("One");
	x.Add("Two");
	x.Add("Three");
	
	RDUMP(StoreAsJson(x));
	Index<String> x2;
	LoadFromJson(x2, StoreAsJson(x));
	RDUMP(StoreAsJson(x2));
	x.Unlink(1);
	RDUMP(StoreAsJson(x));
	

	ArrayMap<double, Test> map2;
	LoadFromJson(map2, StoreAsJson(maptest));
	RDUMP(StoreAsJson(map2));
	
	String json = StoreAsJson(test);
	RDUMP(json);
	Array<Test> test2;
	LoadFromJson(test2, json);
	RDUMP(StoreAsJson(test2));

#ifdef _DEBUG
	return;
#endif
	
	const int N = 100000;
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("JSONIZE");
		LoadFromJson(test2, StoreAsJson(test));
	}
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("Jsonize tree");
		LoadFromJsonValue(test2, StoreAsJsonValue(test));
	}
	Value tree;
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("StoreAsJsonTree");
		tree = StoreAsJsonValue(test);
	}
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("LoadFromJsonTree");
		LoadFromJsonValue(test2, tree);
	}
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("Serialize");
		LoadFromString(test2, StoreAsString(test));
	}
	
	Test tt;
	tt.a = 1; tt.b = 2;
	for(int i = 0; i < 10 * N; i++) {
		RTIMING("Jsonize one");
		Test tt2;
		LoadFromJson(tt2, StoreAsJson(tt));
	}
	for(int i = 0; i < 10 * N; i++) {
		RTIMING("Serialize one");
		Test tt2;
		LoadFromString(tt2, StoreAsString(tt));
	}
}
