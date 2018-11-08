#include "LionBenchmark.h"

#define IMAGECLASS TestImg
#define IMAGEFILE <LionBenchmark/test.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS TestImg
#define IMAGEFILE <LionBenchmark/test.iml>
#include <Draw/iml_source.h>

void Demo(Painter& sw)
{
//	PaintLion(sw);
	String txt = "U++ Painter";
	Font fnt = Roman(180).Bold();
	Size tsz = GetTextSize(txt, fnt);
	sw.Text(0.5, 400.5, txt, fnt)
	  .Fill(TestImg::Test(), 0, 400, 500, 400, FILL_REFLECT)
	  .Stroke(5, 0, 500, Blue(), tsz.cx, 500, LtRed())
	  .Stroke(1, White());
	for(int i = 0; i < 10; i++) {
		sw.Begin();
			sw.Opacity(0.5);
			sw.Translate(600, 200);
			sw.Rotate(i / 10.0 * M_2PI);
			sw.Rectangle(0, 0, 200, 500)
			  .Fill(TestImg::Test(), 0, 0, 200, 0);
		sw.End();
	}
}
