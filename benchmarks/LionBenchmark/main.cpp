#include "LionBenchmark.h"

double tm[4];

void Task(Painter& sw)
{
//	sw.Scale(2);
//	sw.Opacity(0.3);
//	PaintLion(sw);
	PythagorasTree(sw);
}

struct MyApp : public TopWindow {
	bool co = true;

	virtual void LeftDown(Point p, dword keyflags)
	{
		co = !co;
		Refresh();
	}

	virtual void Paint(Draw& w) {
		RLOG("========== PAINT");
		w.DrawRect(GetSize(), White());

		ImageBuffer ib(1200, 1200);
		{
			BufferPainter sw(ib);
			sw.Co();
			sw.Clear(White());
			Task(sw);
		}
		w.DrawImage(0, 0, ib);

		int x = 1200;
		int y = 0;
		w.DrawText(x, y += 50, Format("Standard %.4f", tm[0]));
		w.DrawText(x, y += 50, Format("Multithreaded %.4f", tm[1]));
		w.DrawText(x, y += 50, Format("Standard / Multithreaded %.4f", tm[0] / tm[1]));
		w.DrawText(x, y += 50, Format("Preclipped Standard %.4f", tm[2]));
		w.DrawText(x, y += 50, Format("Preclipped Multithreaded %.4f", tm[3]));
		w.DrawText(x, y += 50, co ? "MT" : "");
	}
};

GUI_APP_MAIN
{
#if 1 && !defined(_DEBUG)
	RDUMP(MemoryUsedKb());
	
	RDUMP(sizeof(Rasterizer));
	
//	PeakMemoryProfile();
	ImageBuffer ib(1200, 1200);
	BufferPainter sw(ib);
	sw.Co();
//	for(int i = 0; i < 10; i++)
		PaintLion(sw);
	for(int pass = 0; pass < 4; pass++) {
		int time0 = msecs();
		int n = 0;
		BufferPainter sw(ib);
		while(msecs(time0) < 3000) {
			n++;
			sw.Co(pass & 1);
			sw.PreClip(pass & 2);
			Task(sw);
		}
		tm[pass] = (double)msecs(time0) / n;
		RLOG(pass << ": " << n << ", " << tm[pass] << " ms");
	}
	RLOG("=========================");
//	RLOG(*PeakMemoryProfile());
	RLOG("Standard " << tm[0]);
	RLOG("MT " << tm[1]);
#endif
	MyApp().Title("6").Run();
}
