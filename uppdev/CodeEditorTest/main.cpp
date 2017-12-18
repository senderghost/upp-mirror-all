#include <CodeEditor/CodeEditor.h>

using namespace Upp;

GUI_APP_MAIN
{
	CodeEditor edit;
	edit.ShowSpaces();
/*
#ifdef _DEBUG
	FileIn in("C:\\xxx\\belogs\\local2 (2).info");
#else
	FileIn in("C:\\xxx\\log\\local1.info");
#endif
*/
//	FileIn in("C:\\xxx\\belogs\\local2 (2).info");
	FileIn in("C:\\xxx\\log\\local1.info");

	if(1)
		edit.View(in);
	else
	{
		RTIMESTOP("LOAD");
		edit.Load(in);
	}
	
	edit.Highlight("log");

//	LoadFromFile([&](Stream& s) { edit.SerializeViewMap(s); });
	
	RDUMP(edit.GetLineCount());
	RDUMP(edit.GetLength());
	RDUMP(MemoryUsedKb());
	
	TopWindow win;
//	win.SetRect(100, 100, 100, 100);
	win.Sizeable();
	win.Add(edit.HSizePos(20, 20).VSizePos(20, 20));
	win.Open();
	edit.ShowLineEndings();
	edit.ShowCurrentLine(LtCyan());

	edit.WhenSel = [&] {
		win.Title(AsString(edit.GetLine(edit.GetCursor()) % 256) + " " + AsString(edit.GetLine(edit.GetCursor()) / 256));
	};

	Ctrl::EventLoop();
	
	StoreToFile([&](Stream& s) { edit.SerializeViewMap(s); });
}

// 156 0x9c ""