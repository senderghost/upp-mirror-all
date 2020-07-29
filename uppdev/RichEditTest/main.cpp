#include <RichEdit/RichEdit.h>

using namespace Upp;

String FileName() {
	return GetDataFile("test.txt");
}

GUI_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);
	SetLanguage(LNGC_('C', 'S', 'C', 'Z', CHARSET_UTF8));
	
	Ctrl::SetUHDEnabled();

	RichEditWithToolBar e;
	PaintInfo pi;
	pi.DrawSelection = [](Draw& dw, int x, int y, int cx, int cy) {
		static Image m;
		ONCELOCK {
			m = CreateImage(Size(128, 128), 50 * Blue());
		}
		dw.Clip(x, y, cx, cy);
		for(int w = 0; w < cx; w += 128)
			for(int h = 0; h < cy; h += 128)
				dw.DrawImage(x + w, y + h, m);
		dw.End();
	};
	e.SetPaintInfo(pi);
	e.Pick(ParseQTF(LoadFile(FileName())));
//	e.SetPage(Size(4000, 1600));
	TopWindow w;
	w.SetRect(0, 0, DPI(700), DPI(500));
	w.Sizeable().Zoomable();
	StaticRect r;
	w.Add(e.SizePos());

	w.Run();
	String x = e.GetQTF();
	SaveFile(FileName(), x);
	
	LOG("Exit");
}
