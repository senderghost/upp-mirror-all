#include <Core/Core.h>

using namespace Upp;

class JsonIO {
	const Value   *src;
	One<ValueMap>  map;
	Value          tgt;

public:
	bool IsLoading() const { return src; }
	bool IsStoring() const { return !src; }
	
	const Value& Get() const                     { ASSERT(IsLoading()); return *src; }
	void         Set(const Value& v)             { ASSERT(IsStoring() && !map); tgt = v; }
	void         Put(Value& v)                   { ASSERT(IsStoring()); if(map) v = *map; else v = tgt; }
	Value        GetResult() const               { ASSERT(IsStoring()); return map ? Value(*map) : tgt; }

	template <class T>
	JsonIO& operator()(const char *key, T& value);
	
	JsonIO(const Value& src) : src(&src) {}
	JsonIO() { src = NULL; }
};

template <class T>
void Jsonize(JsonIO& io, T& var)
{
	var.Jsonize(io);
}

template <class T>
JsonIO& JsonIO::operator()(const char *key, T& value)
{
	if(IsLoading()) {
		const Value& v = (*src)[key];
		if(!v.IsVoid()) {
			JsonIO jio(v);
			Jsonize(jio, value);
		}
	}
	else {
		ASSERT(tgt.IsVoid());
		if(!map)
			map.Create();
		JsonIO jio;
		Jsonize(jio, value);
		if(jio.map)
			map->Add(key, *jio.map);
		else
			map->Add(key, jio.tgt);
	}
	return *this;
}

template <class T>
void JsonizeValue(JsonIO& io, T& var)
{ // bad code
	if(io.IsLoading())
		var = io.Get();
	else
		io.Set(var);
}

template<> inline void Jsonize(JsonIO& io, int& var)      { JsonizeValue(io, var); } // Check for correct types
template<> inline void Jsonize(JsonIO& io, double& var)   { JsonizeValue(io, var); }
template<> inline void Jsonize(JsonIO& io, bool& var)     { JsonizeValue(io, var); }
template<> inline void Jsonize(JsonIO& io, String& var)   { JsonizeValue(io, var); }

template <class T, class V>
void JsonizeArray(JsonIO& io, T& array)
{
	if(io.IsLoading()) {
		const Value& va = io.Get();
		array.SetCount(va.GetCount());
		for(int i = 0; i < va.GetCount(); i++) {
			JsonIO jio(va[i]);
			Jsonize(jio, array[i]);
		}
	}
	else {
		Vector<Value> va;
		va.SetCount(array.GetCount());
		for(int i = 0; i < array.GetCount(); i++) {
			JsonIO jio;
			Jsonize(jio, array[i]);
			jio.Put(va[i]);
		}
		io.Set(ValueArray(va));
	}
}

template <class T>
void Jsonize(JsonIO& io, Vector<T>& var)
{
	JsonizeArray<Vector<T>, T>(io, var);
}

template <class T>
void Jsonize(JsonIO& io, Array<T>& var)
{
	JsonizeArray<Array<T>, T>(io, var);
}

template <class T>
Value StoreAsJsonTree(const T& var)
{
	JsonIO io;
	Jsonize(io, const_cast<T&>(var));
	return io.GetResult();
}

template <class T>
void LoadFromJsonTree(T& var, const Value& x)
{
	JsonIO io(x);
	Jsonize(io, var);
}

template <class T>
String StoreAsJson(const T& var)
{
	return AsJSON(StoreAsJsonTree(var));
}

template <class T>
bool LoadFromJson(T& var, const char *json)
{
	try {
		LoadFromJsonTree(var, ParseJSON(json));
	}
	catch(CParser::Error& e) {
		return false;
	}
	return true;
}


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


CONSOLE_APP_MAIN
{
	Array<Test> test;
	for(int i = 0; i < 10; i++) {
		Test t;
		t.a = 1 + i;
		t.b = 23 + i;
		test.Add(t);
	}
	
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
		LoadFromJsonTree(test2, StoreAsJsonTree(test));
	}
	Value tree;
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("StoreAsJsonTree");
		tree = StoreAsJsonTree(test);
	}
	for(int i = 0; i < N; i++) {
		Array<Test> test2;
		RTIMING("LoadFromJsonTree");
		LoadFromJsonTree(test2, tree);
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
