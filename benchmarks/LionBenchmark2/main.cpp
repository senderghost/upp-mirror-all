#include "LionBenchmark.h"

double tm[8];

int band = 100;

struct MyApp : public TopWindow {
	bool co = true;

	virtual void LeftDown(Point p, dword keyflags)
	{
		co = !co;
		Refresh();
	}
	
	void MouseMove(Point, dword) override {
		Refresh();
	}

	virtual void Paint(Draw& w) {
		RLOG("========== PAINT");
		Size sz = GetSize();
		w.DrawRect(sz, White());
	//	sz.cy = band;
		ImageBuffer ib(sz);
		{
			BufferPainter sw(ib);
//			sw.PreClip();
			sw.Co();
//			sw.Co(co);
			sw.Clear(White());
//			sw.Scale(2);
//			sw.Opacity(0.98);
			PaintLion(sw);
		}
		
		w.DrawImage(0, 0, ib);
		
		w.DrawImage(0, 500, CoPaint(sz, [&](BufferPainter& sw) {
			sw.Clear(White());
			PaintLion(sw);
		}));
	#ifndef _DEBUG
		int x = 500;
		w.DrawText(x, 0, Format("Standard %.4f", tm[0]));
		w.DrawText(x, 50, Format("Multithreaded %.4f", tm[1]));
		w.DrawText(x, 100, Format("Standard / Multithreaded %.4f", tm[0] / tm[1]));
		w.DrawText(x, 150, Format("Preclipped Standard %.4f", tm[2]));
		w.DrawText(x, 200, Format("Preclipped Multithreaded %.4f", tm[3]));
		w.DrawText(x, 250, Format("Banded MT %.4f", tm[4]));
		w.DrawText(500, 300, co ? "MT" : "");
	#endif
	}
};

GUI_APP_MAIN
{
#ifndef _DEBUG
	RDUMP(MemoryUsedKb());
	PeakMemoryProfile();
	ImageBuffer ib(500, 500);
	for(int pass = 0; pass < 5; pass++) {
		int time0 = msecs();
		int n = 0;
		while(msecs(time0) < 1000) {
			n++;
			if(pass == 4) {
				CoPaint(Size(500, 500), [](BufferPainter& sw) {
					sw.Scale(2, 2);
					sw.Opacity(0.1);
					sw.PreClip(false);
					PaintLion(sw);
				});
			}
			else
			{
				BufferPainter sw(ib);
				if(pass & 1)
					sw.Co();
				sw.PreClip(pass & 2);
				sw.Scale(2, 2);
				sw.Opacity(0.1);
				PaintLion(sw);
			}
		}
		tm[pass] = (double)msecs(time0) / n;
		RDUMP(msecs(time0));
		RDUMP(pass);
		RDUMP(n);
		RDUMP(tm[pass]);
	}

	RLOG("=========================");
	RDUMP(GetLionSize());
	RLOG(*PeakMemoryProfile());
	RLOG("Standard " << tm[0]);
	RLOG("MT " << tm[1]);
	RLOG("Banded " << tm[4]);
	RLOG("WTF?");
#endif
	MyApp().Run();
}
