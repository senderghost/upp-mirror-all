#include <CtrlLib/CtrlLib.h>

using namespace Upp;

struct MyApp : TopWindow {
	Image img;
	double tm = 0;
	bool co = false;
	
	virtual void Paint(Draw& w) {
		Size sz = GetSize();
		tm = msecs();
		DLOG("================");
		Image m = Rescale(img, sz);
//		Image m = co ? CoRescaleFilter(img, sz, FILTER_LANCZOS3) : RescaleFilter(img, sz, FILTER_LANCZOS3);
		tm = (msecs() - tm) / 1000.0;
		w.DrawImage(0, 0, m);
		PostCallback([=] {
			String s;
			if(co)
				s << "Parallel ";
			s << tm;
			Title(s);
		});
	}

	virtual bool Key(dword key, int count) {
		switch(key) {
		case K_SPACE:
			co = !co;
			Refresh();
		}
		return true;
	}
	

	MyApp() {
		Sizeable().Zoomable();
		Sync();
	}
};

GUI_APP_MAIN
{
	MyApp x;
	x.img = StreamRaster::LoadFileAny("C:/Users/cxl/Documents/start12.png");
	x.Run();
}
