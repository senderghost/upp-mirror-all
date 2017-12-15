#include <CtrlLib/CtrlLib.h>

using namespace Upp;

void ShowLen(LineEdit *edit, TopWindow *win)
{
	win->Title(AsString(edit->GetLength()));
}

GUI_APP_MAIN
{
	LineEdit edit;
	edit.ShowSpaces();

#ifdef _DEBUG
	FileIn in("C:\\xxx\\log\\nos.log");
#else
	FileIn in("C:\\xxx\\log\\local1.info");
#endif
	{
		RTIMESTOP("LOAD");
		edit.Load(in);
//		edit.View(in);
	}
	
	RDUMP(edit.GetLineCount());
	RDUMP(edit.GetLength());
	RDUMP(MemoryUsedKb());
	
	
	String txt;
	{ RTIMESTOP("GET");
		txt = ~edit;
	}
	RDUMP(txt.GetCount());
	{
		RTIMESTOP("Compress");
		txt = FastCompress(txt);
	};
	RDUMP(txt.GetCount());
	
	TopWindow win;
//	win.SetRect(100, 100, 100, 100);
	win.Sizeable();
	win.Add(edit.HSizePos(20, 20).VSizePos(20, 20));
	win.Open();
	edit.ShowLineEndings();
	edit.ShowCurrentLine(LtCyan());
	edit <<= callback2(ShowLen, &edit, &win);
	Ctrl::EventLoop();
}

// 156 0x9c ""