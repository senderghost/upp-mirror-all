#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
	ArrayCtrl list;
	
	list.AddColumn("Column1").Sorting(); // default sorting
	list.AddColumn("Column2") // we provide compare function that sorts based on string length
		.SortingBy([](const Value& a, const Value& b) -> int { return SgnCompare(a, b); });
		
	list.AddColumn("Column3").With([](One<Ctrl>& o) { o.Create<Option>(); });
	
	list.Add("Not sorted");

	for(int i = 0; i < 100; i++)
		list.Add((int)Random(), (int)Random(), (int)Random());
	
	list.SortingFrom(1);
	
	TopWindow win;
	win.Add(list.SizePos());
	
	win.Run();
}
