#include "CtrlCore.h"

#ifdef GUI_X11

NAMESPACE_UPP

Vector<Rect> RectRgn(const Rect& r)
{
	Vector<Rect> q;
	q.Add(r);
	return q;
}

Vector<Rect> Intersect(const Vector<Rect>& r1, const Vector<Rect>& r2)
{
	Vector<Rect> q;
	for(int i = 0; i < r1.GetCount(); i++)
		for(int j = 0; j < r2.GetCount(); j++) {
			Rect r = r1[i] & r2[j];
			if(!r.IsEmpty())
				q.Add(r);
		}
	return q;
}

Vector<Rect> Subtract(const Vector<Rect>& r1, const Vector<Rect>& r2)
{
	Vector<Rect> q;
	bool dummy;
	q <<= r1;
	for(int i = 0; i < r2.GetCount(); i++)
		q = Subtract(q, r2[i], dummy);
	return q;
}

Vector<Rect> Xor(const Vector<Rect>& r1, const Vector<Rect>& r2)
{
	Vector<Rect> is = Intersect(r1, r2);
	Vector<Rect> q = Subtract(r1, is);
	q.Append(Subtract(r2, is));
	return q;
}

Vector<Rect> GetFrameRgn(const Rect& rect, int n) {
	Vector<Rect> q = RectRgn(rect);
	q.Add(rect);
	Rect r = rect;
	r.Deflate(n);
	if(r.Width() > 0 && r.Height() > 0)
		q = Xor(q, RectRgn(r));
	return q;
}

void DrawDragRect(SystemDraw& w, const Rect& rect1, const Rect& rect2, const Rect& clip, int n,
                  Color color, uint64 pattern)
{
	char bd[8];
	for(int i = 0; i < 8; i++)
		bd[i] = ~(byte)(pattern >> (8 * (7 - i)));
	Pixmap stipple = XCreateBitmapFromData(Xdisplay, w.GetDrawable(), bd, 8, 8);
	Point offset = w.GetOffset();
	GC gc = XCreateGC(Xdisplay, w.GetDrawable(), 0, 0);
	SetClip(gc, w.GetXftDraw(),
	        Intersect(Xor(GetFrameRgn(rect1 + offset, n), GetFrameRgn(rect2 + offset, n)),
	                  RectRgn(clip + offset)));

	XGCValues gcv;
	gcv.function = X11_ROP2_XOR;
	gcv.foreground = GetXPixel(color);
	gcv.fill_style = FillStippled;
	gcv.stipple = stipple;
	XChangeGC(Xdisplay, gc, GCForeground|GCFunction|GCStipple|GCFillStyle, &gcv);
	XFillRectangle(Xdisplay, w.GetDrawable(), gc, 0, 0, Xwidth, Xheight);
	XFreePixmap(Xdisplay, stipple);
}

END_UPP_NAMESPACE

#endif
