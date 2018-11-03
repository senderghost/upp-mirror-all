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

	virtual void Paint(Draw& w) {
		RLOG("========== PAINT");
		Size sz = GetSize();
		w.DrawRect(sz, White());
		sz.cy = band;
		ImageBuffer ib(sz);
		{
			BufferPainter sw(ib);
//			sw.Co(co);
			sw.Clear(White());
//			sw.Scale(2);
//			sw.Opacity(0.98);
			PaintLion(sw);
		}
		w.DrawImage(0, 0, ib);
		int x = 500;
		w.DrawText(x, 0, Format("Standard %.4f", tm[0]));
		w.DrawText(x, 50, Format("Multithreaded %.4f", tm[1]));
		w.DrawText(x, 100, Format("Standard / Multithreaded %.4f", tm[0] / tm[1]));
		w.DrawText(x, 150, Format("Preclipped Standard %.4f", tm[2]));
		w.DrawText(x, 200, Format("Preclipped Multithreaded %.4f", tm[3]));
		w.DrawText(x, 250, Format("Banded MT %.4f", tm[4]));
		w.DrawText(500, 300, co ? "MT" : "");
		
		{
			PaintingPainter pp(500, 500);
			pp.Clear(Blend(White(), LtCyan()));
//			pp.Opacity(0.5);
			PaintLion(pp);
			ImageBuffer ib2(500, 500);
			MTPaint(ib2, pp);
			w.DrawImage(0, 500, ib2);
		}
	}
};

GUI_APP_MAIN
{
#if 1 && !defined(_DEBUG)
	RDUMP(MemoryUsedKb());
	PeakMemoryProfile();
	ImageBuffer ib(500, 500);
	for(int pass = 0; pass < 5; pass++) {
		int time0 = msecs();
		int n = 0;
		while(msecs(time0) < 1000) {
			n++;
			if(pass == 4) {
				PaintingPainter pp(500, 500);
				{
					RTIMING("MakePainter");
					PaintLion(pp);
				}
				RTIMING("MTPaint");
				MTPaint(ib, pp);
			}
			else {
				BufferPainter sw(ib);
//				sw.Co(pass & 1);
				sw.PreClip(pass & 2);
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
#endif
	MyApp().Run();
}
