#ifndef _LionBenchmark_LionBenchmark_h
#define _LionBenchmark_LionBenchmark_h

#include <CtrlLib/CtrlLib.h>
#include <Painter/Painter.h>

using namespace Upp;

void  PaintLion(Painter& sw);
Sizef GetLionSize();

void MTPaint(ImageBuffer& ib, const Painting& p);

#endif
