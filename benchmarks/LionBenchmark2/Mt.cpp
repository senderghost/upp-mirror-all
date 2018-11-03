#include "LionBenchmark.h"

void MTPaint(ImageBuffer& ib, const Painting& p)
{
	Size sz = ib.GetSize();
	int band_cy = sz.cy / CPU_Cores() / 16;
	CoWork co;
	co * [&] {
		for(;;) {
			int y = co.Next() * band_cy;
			if(y >= sz.cy)
				break;
			BufferPainter iw(ib[y], Size(sz.cx, min(band_cy, sz.cy -y)));
			iw.PreClip();
			iw.Draw::Offset(0, -y);
			iw.Paint(p);
		}
	};
}
