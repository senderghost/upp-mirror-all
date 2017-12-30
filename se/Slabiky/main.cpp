#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow {
	String text;
	
	virtual void Paint(Draw& w) {
		w.DrawRect(GetSize(), White());
		w.DrawText(50, 50, text, Roman(700));
	}
	
	virtual void LeftUp(Point p, dword keyflags)
	{
		WString a = "rščřžrtpsdfghjklcvbnm";
		WString b = "ýáíéeuioaů";
//		WString a = "rpsdk";
//		WString b = "aeiou";
		text = a.Mid(Random(a.GetCount()), 1).ToString() + b.Mid(Random(b.GetCount()), 1).ToString();
		text = ToUpper(text);
		Refresh();
	}

};

GUI_APP_MAIN
{
	MyApp().Run();
}
