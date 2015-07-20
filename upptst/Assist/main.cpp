#include <CtrlLib/CtrlLib.h>
#include <Sql/Sql.h>
#include <vector>
#include <map>

using namespace std;

#if 0 // Do not compile these tests in nightly job

// Each test in separate function to activate grounding

void Autocomplete()
{
	String x;
	// Should not show anything here - qualification missing
	x.
}

void Autocomplete()
{
	Upp::String x;
	x.
}

void Autocomplete()
{
	Upp::MD5String
}

void Autocomplete()
{
	Upp::String
}

using namespace Upp;

void Autocomplete()
{
	MD5String
}

void Autocomplete()
{
	String
}

void Autocomplete()
{
	String h;
	h.
}

void Autocomplete()
{ // Check that this displays String autocomplete (not One)
	One<String>()->
}

void Autocomplete()
{ // Check that this displays One autocomplete (not String)
	One<String>().
}

void Autocomplete()
{ // Displays String, it is OK as Single is function
	Single<String>().
}

void Autocomplete()
{
	EditDouble x; // Also try jump to HSizePos
	x.HSizePos().
}

void Autocomplete()
{
	EditDouble x;
	x.SetFilter(Char
}

void Autocomplete()
{
	Point p;
	p.
}

Index<String>& Tags();

void Autocomplete()
{
	Tags().
}

void Autocomplete()
{
	Tags()[i].
}

void Autocomplete()
{
	Index<String> x;
	x[i].
}

VectorMap<String, String>& Map();

void Autocomplete()
{
	Map().
}

void Autocomplete()
{
	Map()[i].
}

void Autocomplete()
{
	VectorMap<String, String> map;
	map[i].
}

void Autocomplete()
{
	type // check that there are not wrong items in the list for 'type'
}

void Autocomplete()
{
	Select().From().LeftJoinRef().Where().OrderBy().Lim
}

struct Ide { 
	struct ErrorInfo {
		String file;
	};
}

void Ide::AutoComplete()
{
	Value v;
	ValueTo<ErrorInfo>().
}

void Ide::AutoComplete()
{
	Value v;
	v.To<ErrorInfo>().
}

enum {
	TEST_ONE,
	TEST_TWO
};

void Autocomplete()
{
	b ? TEST_ONE : TES
}

void Autocomplete()
{
	Splitter popup;
	popup.Ctrl::PopUp
}

void Autocomplete()
{
	Vector<String> v;
	v.begin()->
}

void Autocomplete()
{
	Array<String> v;
	v.begin()->
}

void Autocomplete()
{
	Vector<String> v;
	auto x = v[0];
	x.
}

void Autocomplete()
{
	Array<String> v;
	for(const auto& i : v)
		i.
}

void Autocomplete()
{
	Vector<String> v;
	for(const auto& i : v)
		i.
}

void Autocomplete()
{
	VectorMap<int, String> m;
	for(auto i : m)
		i.
}

void Autocomplete()
{
	VectorMap<int, String> m;
	auto i = m.Begin();
	i.
}

void Autocomplete()
{
	VectorMap<Point, String> m;
	auto i = m.KeyBegin();
	i.
}

void Autocomplete()
{
	vector<string> v;
	for(const auto& i : v)
		i.
}

void Autocomplete()
{
	vector<string> v;
	auto q = v.end();
	q.
}

void Autocomplete()
{
	map<int, string> m;
	for(const auto& i : m)
		i.second.
}

void Autocomplete()
{
	map<string, int> m;
	auto q = m.begin();
	q.first.
}

void Autocomplete()
{
	std::vector<std::string> v;
	for(const auto& i : v)
		i.
}

void Autocomplete()
{
	String txt[2]; // does not work yet!!!!
	txt[1].
}

void JumpTo()
{
	Point p;
	int x;
	p.x // should jump to Point::x, not local variable
}

void JumpTo()
{
	int local_var;
	Point foo;	
	local_var // should jump to local variable declaration two lines above
}

struct JumpToTest {
	int x; // test that this does not jump anywhere...
}

#endif

GUI_APP_MAIN
{
}
