#include <RichEdit/RichEdit.h>

using namespace Upp;

String FileName() {
	return GetHomeDirFile("test.qtf");
}

GUI_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);
	SetLanguage(LNGC_('C', 'S', 'C', 'Z', CHARSET_UTF8));
	
	Ctrl::SetUHDEnabled();

	RichEditWithToolBar e;
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
