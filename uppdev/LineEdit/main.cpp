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
/*
#ifdef _DEBUG
	FileIn in("C:\\xxx\\belogs\\local2 (2).info");
#else
	FileIn in("C:\\xxx\\log\\local1.info");
#endif
*/
//	FileIn in("C:\\xxx\\belogs\\local2 (2).info");
	FileIn in(GetDataFile("bench.txt"));

	edit.Load(in);
	
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
	edit.ShowCurrentColumn(WhiteGray());
	edit <<= callback2(ShowLen, &edit, &win);
	Ctrl::EventLoop();
}

// 156 0x9c ""