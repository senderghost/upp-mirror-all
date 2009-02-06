#include "ScanLine.h"

void Rasterizer::Move(double x, double y)
{
	x1 = x;
	y1 = y;
}

inline int Cv(double x)
{
	return fround(x * 256);
}

void Rasterizer::CvLine(double x1, double y1, double x2, double y2)
{
	LineRaw(Cv(x1), Cv(y1), Cv(x2), Cv(y2));
}

void Rasterizer::LineClip(double x1, double y1, double x2, double y2)
{
	if(y1 < cliprect.top) {
		if(y2 < cliprect.top)
			return;
		x1 = (x2 - x1) * (cliprect.top - y1) / (y2 - y1) + x1;
		y1 = cliprect.top;
	}
	else
	if(y1 > cliprect.bottom) {
		if(y2 > cliprect.bottom)
			return;
		x1 = (x2 - x1) * (cliprect.bottom - y1) / (y2 - y1) + x1;
		y1 = cliprect.bottom;			
	}
	if(y2 < cliprect.top) {
		x2 = (x2 - x1) * (cliprect.top - y1) / (y2 - y1) + x1;
		y2 = cliprect.top;
	}
	else
	if(y2 > cliprect.bottom) {
		x2 = (x2 - x1) * (cliprect.bottom - y1) / (y2 - y1) + x1;
		y2 = cliprect.bottom;
	}
	double y, yy;
	if(x1 < cliprect.left) {
		if(x2 < cliprect.left) {
			CvLine(cliprect.left, y1, cliprect.left, y2);
			return;
		}
		y = (y2 - y1) * (cliprect.left - x1) / (x2 - x1) + y1;
		if(x2 > cliprect.right) {
			yy = (y2 - y1) * (cliprect.right - x1) / (x2 - x1) + y1;
			CvLine(cliprect.left, y1, cliprect.left, y);
			CvLine(cliprect.left, y, cliprect.right, yy);
			CvLine(cliprect.right, yy, cliprect.right, y2);
			return;
		}
		CvLine(cliprect.left, y1, cliprect.left, y);
		CvLine(cliprect.left, y, x2, y2);
		return;
	}
	else
	if(x1 > cliprect.right) {
		if(x2 > cliprect.right) {
			CvLine(cliprect.right, y1, cliprect.right, y2);
			return;
		}
		y = (y2 - y1) * (cliprect.right - x1) / (x2 - x1) + y1;
		if(x2 < cliprect.left) {
			yy = (y2 - y1) * (cliprect.left - x1) / (x2 - x1) + y1;
			CvLine(cliprect.right, y1, cliprect.right, y);
			CvLine(cliprect.right, y, cliprect.left, yy);
			CvLine(cliprect.left, yy, cliprect.left, y2);
			return;
		}
		CvLine(cliprect.right, y1, cliprect.right, y);
		CvLine(cliprect.right, y, x2, y2);
		return;
	}
	if(x2 < cliprect.left) {
		y = (y2 - y1) * (cliprect.left - x1) / (x2 - x1) + y1;
		CvLine(x1, y1, cliprect.left, y);
		CvLine(cliprect.left, y, cliprect.left, y2);
		return;
	}
	else
	if(x2 > cliprect.right) {
		y = (y2 - y1) * (cliprect.right - x1) / (x2 - x1) + y1;
		CvLine(x1, y1, cliprect.right, y);
		CvLine(cliprect.right, y, cliprect.right, y2);
		return;
	}
	CvLine(x1, y1, x2, y2);
}

void Rasterizer::Line(double x2, double y2)
{
	PAINTER_TIMING("Line");
	LineClip(x1, y1, x2, y2);
	x1 = x2;
	y1 = y2;
}
