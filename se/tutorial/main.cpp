#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define BEGIN     {
#define END       }
#define TITLE(x)  } LOG("----------------------"); LOG(x); {

GUI_APP_MAIN
{
	BEGIN;

	TITLE("Logging");
	
	LOG("Hello world");
	
	int x = 123;
	LOG("Value of x is " << x);
	
	DUMP(x);
	
	RLOG("This will also log in release mode");
	RDUMP(x);
	
	DLOG("This will not compile in release mode");
	DDUMP(x);
	
	String h = "Hello world!";
	DUMPHEX(h);
	
	struct Foo {
		String a;
		int    b;
		
		String ToString() const { return String() << "[a: " << a << ", b: " << b << "]"; }
	};
	
	Foo foo;
	foo.a = "Text";
	foo.b = 123;
	
	DUMP(foo);
	
	TITLE("Basic utilities");
	
	DUMP(max(1, 4, 2, 3));
	DUMP(clamp(10, 1, 4));

	DUMP(findarg("beta", "alfa", "beta", "gamma"));

	DUMP(findarg("unknown", "alfa", "beta", "gamma"));
	
	DUMP(decode(1, 0, "zero", 1, "one", 2, "two", "unknown"));
	
	TITLE("Null");
	
	int i = Null;
	
	DUMP(i);
	
	DUMP(IsNull(i));
	
	int64 bug = i;
	DUMP(bug);
	
	struct Foo {
		String a;
		int    b;
		
		bool IsNullInstance() const { return a.GetCount() == 0 && b == 0; }
	};
	
	Foo  f;
	f.b = 0;
	DUMP(IsNull(f));
	
	f.b++;
	DUMP(IsNull(f));
	
	END
}