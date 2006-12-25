#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow {
	DropList fontlist;

	void Paint(Draw& w) {
		w.DrawRect(GetSize(), White);
		w.Offset(50, 50);
		const char *text = "Programming is a good job";
		Font fnt(~fontlist, 60);
		FontInfo fi = fnt.Info();
		int x = 0;
		Vector<int> dx;
		for(const char *s = text; *s; s++) {
			int width = fi[*s];
			w.DrawRect(x, 0, width - 1, fi.GetAscent(), Color(255, 255, 200));
			w.DrawRect(x, fi.GetAscent(), width - 1, fi.GetDescent(), Color(255, 200, 255));
			w.DrawRect(x + width - 1, 0, 1, fi.GetHeight(), Black());
			dx.Add(width + 4);
			x += width;
		}
		w.DrawRect(0, 0, 4, 4, Black());
		w.DrawText(0, 0, text, fnt);
		w.DrawText(0, 70, text, fnt, Blue(), dx.GetCount(), dx.Begin());
		w.End();
	}

	void NewFont() {
		Refresh();
	}

	typedef MyApp CLASSNAME;

	MyApp() {
		for(int i = 0; i < Font::GetFaceCount(); i++)
			fontlist.Add(i, Font::GetFaceName(i));
		Add(fontlist.TopPos(0, MINSIZE).LeftPosZ(0, 200));
		fontlist <<= 0;
		fontlist <<= THISBACK(NewFont);
	}
};

GUI_APP_MAIN
{
	MyApp().Sizeable().Run();
}
