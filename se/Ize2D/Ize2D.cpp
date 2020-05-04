#include <Core/Core.h>

using namespace Upp;

void FixDimensions(Vector<Vector<double>>& data, int m, int n)
{
	data.SetCount(m);
	for(auto& row : data)
		row.SetCount(n, 0);
}

void FixDimensions(Vector<Vector<Vector<double>>>& data, int m, int n, int o)
{
	data.SetCount(m);
	for(auto& plane : data) {
		plane.SetCount(n);
		for(auto& row : plane)
			row.SetCount(n, 0);
	}
}

Value ToValue(const Vector<double>& data)
{
	ValueArray va;
	for(auto& a : data)
		va.Add(a);
	return va;
}

void ValueTo(Vector<double>& data, const Value& v)
{
	data.Clear();
	ValueArray va = v;
	for(double a : va)
		data.Add(a);
}

Value ToValue(const Vector<Vector<double>>& data)
{
	ValueArray va;
	for(auto& a : data) {
		ValueArray row;
		for(auto& v : a)
			row.Add(v);
		va.Add(row);
	}
	return va;
}

void ValueTo(Vector<Vector<double>>& data, const Value& v)
{
	data.Clear();
	ValueArray va = v;
	for(ValueArray row : va) {
		data.Add();
		for(double v : row)
			data.Top().Add(v);
	}
}

Value ToValue(const Vector<Vector<Vector<double>>>& data)
{
	ValueArray va;
	for(auto& a : data) {
		ValueArray plane;
		for(auto& p : a) {
			ValueArray row;
			for(auto& v : p)
				row.Add(v);
			plane.Add(row);
		}
		va.Add(plane);
	}
	return va;
}

void ValueTo(Vector<Vector<Vector<double>>>& data, const Value& v)
{
	data.Clear();
	ValueArray va = v;
	for(ValueArray plane : va) {
		data.Add();
		for(ValueArray row : plane) {
			data.Top().Add();
			for(double v : row)
				data.Top().Top().Add(v);
		}
	}
}

template <class T>
void IzeDataArray(JsonIO& io, const char *id, T& data)
{
	if(io.IsStoring())
		io.Set(id, ToValue(data));
	else
		ValueTo(data, io.Get(id));
}

template <class T>
void IzeDataArray(XmlIO& xio, const char *id, T& data)
{
	if(xio.IsStoring())
		xio.Node().Add(id).AddText(AsJSON(ToValue(data)));
	else
		ValueTo(data, ParseJSON(xio.Node()[id].GatherText()));
}

struct Foo {
	int x;
	Vector<double> line;
	Vector<Vector<double>> data;
	Vector<Vector<Vector<double>>> cube;

	template <class T>
	void Ize(T& io) {
		io("x", x);
		IzeDataArray(io, "line", line);
		IzeDataArray(io, "array", data);
		IzeDataArray(io, "cube", cube);
	}
	
	void Jsonize(JsonIO& io) { Ize(io); }
	void Xmlize(XmlIO& io) { Ize(io); }
};

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);
	
	Vector<Vector<double>> data;
	data.Add().Add(123);
	FixDimensions(data, 3, 3);
	DDUMP(data);

	Vector<Vector<Vector<double>>> cube;
	cube.Add().Add() << 1 << 2;
	FixDimensions(cube, 3, 3, 3);
	DDUMP(cube);

	Foo bar;

	bar.line << 1 << 2 << 3;

	bar.data.Add() << 11 << 12 << 13 << 14;
	bar.data.Add() << 21 << 22 << 23 << 24;
	
	bar.cube.Add().Add() << 111 << 112;
	bar.cube.Top().Add() << 121 << 122;
	bar.cube.Add().Add() << 211 << 212;
	bar.cube.Top().Add() << 221 << 222;
	
	bar.x = 123;
	
	String json = StoreAsJson(bar);
	DDUMP(json);

	String xml = StoreAsXML(bar);
	DDUMP(xml);
	
	Foo bar2;
	LoadFromJson(bar2, json);
	DDUMP(bar2.x);
	DDUMP(bar2.line);
	DDUMP(bar2.data);
	DDUMP(bar2.cube);

	Foo bar3;
	LoadFromXML(bar3, xml);
	DDUMP(bar3.x);
	DDUMP(bar3.line);
	DDUMP(bar3.data);
	DDUMP(bar3.cube);
}
