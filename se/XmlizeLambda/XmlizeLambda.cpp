#include <Core/Core.h>

using namespace Upp;

#include <Core/Core.h>

using namespace Upp;

struct Item {
	int  value;
	
	String ToString() const { return AsString(value); }
};

struct Data {
	bool        option;
	Vector<bool> x;
	Array<Item> array;

	void Dump();
	void Xmlize(XmlIO& xml);
};

template <class IO>
void Data::Xmlize(IO& io)
{
	io
		("option", option);
		("array", array, [=] (IO& io, Item& m) {
			io(option ? "value1" : "value2", m.data);
		});
	;
}

void   Data::Dump()
{
	DUMP(option);
	DUMP(array);
}

CONSOLE_APP_MAIN
{
	StdLogSetup(LOG_COUT|LOG_FILE);

	Data x;
	x.option = true;
	
	LOG(StoreAsXML(x));

	StoreAsXMLFile(x);

	Data y;
	LoadFromXMLFile(y);
	y.Dump();
}
