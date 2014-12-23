#include "PainterSvg.h"

NAMESPACE_UPP

void BoundsPainter::New()
{
	boundingbox = Null;
	current = ccontrol = qcontrol = Pointf(0, 0);
}

Pointf BoundsPainter::PathPoint(const Pointf& p, bool rel)
{
	Pointf r;
	r.x = IsNull(p.x) ? current.x : rel ? p.x + current.x : p.x;
	r.y = IsNull(p.y) ? current.y : rel ? p.y + current.y : p.y;
	return r;
}

void BoundsPainter::Bounds(Pointf p)
{
	boundingbox.Union(p);
}

Pointf BoundsPainter::SetCurrent(Pointf p, bool rel)
{
	current = PathPoint(p, rel);
	Bounds(current);
	return current;
}

void BoundsPainter::MoveOp(const Pointf& p, bool rel)
{
	sw.Move(p, rel);
	 qcontrol = ccontrol = current = PathPoint(p, rel);
}

void BoundsPainter::LineOp(const Pointf& p, bool rel)
{
	sw.Line(p, rel);
	Bounds(current);
	ccontrol = qcontrol = SetCurrent(p, rel);
}

void QuadraticMinMax(double p1, double p2, double p3, double& l, double& h) {
    double a = p1 - 2 * p2 + p3;
    double b = p2 - p1;
    if(a) {
	    double tv = b/a;
	    if (tv > 0 && tv < 1) {
			tv = ((p1 - 2 * p2 + p3) * tv + 2 * (p2 - p1)) * tv + p1;
			if(tv < l)
				l = tv;
			if(tv > h)
				h = tv;
	    }
    }
}
    
void BoundsPainter::Quadratic(const Pointf& p1, const Pointf& p)
{
	Bounds(current);
	Bounds(p);
	if(!boundingbox.Contains(p1)) {
		QuadraticMinMax(current.x, p1.x, p.x, boundingbox.left, boundingbox.right);
		QuadraticMinMax(current.y, p1.y, p.y, boundingbox.top, boundingbox.bottom);
	}
	qcontrol = p1;
	current = p;
}

void BoundsPainter::QuadraticOp(const Pointf& p1, const Pointf& p, bool rel)
{
	sw.Quadratic(p1, p, rel);
	Quadratic(PathPoint(p1, rel), PathPoint(p, rel));
}

void BoundsPainter::QuadraticOp(const Pointf& p, bool rel)
{
	sw.Quadratic(p, rel);
	Quadratic(2.0 * current - qcontrol, PathPoint(p, rel));
}

int SolveQuadraticEquation(double a, double b, double c, double *r)
{
	if(a == 0) {
		if(b == 0)
			return 0;
  		r[0] = r[1] = -c / b;
  		return 1;
    }
	double d = b * b - 4 * a * c;
	if (d < 0)
		return 0;
	a *= 2;
	if (d == 0) {
		r[0] = r[1] = -b / a;
		return 1;
	}
	d = sqrt(d);
	if(b == 0) {
		r[0] = d / a;
		r[1] = -r[0];
    }
	else {
		r[0] = (-b + d) / a;
		r[1] = (-b - d) / a;
    }
	return 2;
}

void CubicMinMax(double p1, double p2, double p3, double p4, double& l, double& h) {
	double c0 = 3 * (p2 - p1);
	double c1 = 6 * (p3 - p2);
	double c2 = 3 * (p4 - p3);
	double r[2];
	int n = SolveQuadraticEquation(c2 - c1 + c0, c1 - 2 * c0, c0, r);
	for(int i = 0; i < n; i++) {
		double tv = r[i];
		if(tv > 0 && tv < 1) {
			tv = ((1 - tv) * (1 - tv) * (1 - tv) * p1 +
			     3 * tv * (1 - tv) * (1 - tv) * p2 +
			     3 * tv * tv * (1 - tv) * p3 +
			     tv * tv * tv * p4);
			if(tv < l)
				l = tv;
			if(tv > h)
				h = tv;
		}
	}
}

void BoundsPainter::Cubic(const Pointf& p1, const Pointf& p2, const Pointf& p)
{
	Bounds(current);
	Bounds(p);
	if(!boundingbox.Contains(p1) || !boundingbox.Contains(p2)) {
		CubicMinMax(current.x, p1.x, p2.x, p.x, boundingbox.left, boundingbox.right);
		CubicMinMax(current.y, p1.y, p2.y, p.y, boundingbox.top, boundingbox.bottom);
	}
	ccontrol = p2;
	current = p;
}

void BoundsPainter::CubicOp(const Pointf& p1, const Pointf& p2, const Pointf& p, bool rel)
{
	sw.Cubic(p1, p2, p, rel);
	Cubic(PathPoint(p1, rel), PathPoint(p2, rel), PathPoint(p, rel));
}

void BoundsPainter::CubicOp(const Pointf& p2, const Pointf& p, bool rel)
{
	sw.Cubic(p2, p, rel);
	CubicOp(2.0 * current - ccontrol, PathPoint(p2, rel), PathPoint(p, rel), rel);
}

void BoundsPainter::ArcOp(const Pointf& c, const Pointf& r, double angle, double sweep, bool rel)
{
	DoArc(rel ? current + c : c, r, angle, sweep, 0);
}

void BoundsPainter::SvgArcOp(const Pointf& r, double xangle, bool large, bool sweep, const Pointf& p, bool rel)
{
	DoSvgArc(r, xangle, large, sweep, PathPoint(p, rel), current);
}

void BoundsPainter::CloseOp()
{
	sw.Close();
}

void BoundsPainter::DivOp()
{
	sw.Div();
}

void BoundsPainter::TextOp(const Pointf& p, const wchar *text, Font fnt, int n, double *dx)
{
	Painter::TextOp(p, text, fnt, n, dx);
}

void BoundsPainter::CharacterOp(const Pointf& p, int ch, Font fnt)
{
	PaintCharacter(*this, p, ch, fnt);
}

void BoundsPainter::Finish(double width)
{
	if(!IsNull(boundingbox)) {
		Rectf h = boundingbox.Inflated(width / 2);
		Pointf a = mtx.Top().Transform(h.TopLeft());
		Pointf b = mtx.Top().Transform(h.BottomRight());		
		DLOG("BoundsPainter FINISH " << h << " -> " << Rectf(a, b));
		DDUMP(svg_boundingbox);
		svg_boundingbox.Union(a);
		svg_boundingbox.Union(b);
		DDUMP(svg_boundingbox);
	}
}

void BoundsPainter::TransformOp(const Xform2D& m)
{
	mtx.Top() = m * mtx.Top();
	sw.Transform(m);
}

void BoundsPainter::BeginOp()
{
	mtx.Add();
	mtx.Top() = mtx[mtx.GetCount() - 2];
	boundingbox = Null;
	sw.Begin();
}

void BoundsPainter::EndOp()
{
	mtx.Drop();
	sw.End();
}

END_UPP_NAMESPACE
