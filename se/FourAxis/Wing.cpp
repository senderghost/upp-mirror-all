#include "Hot4d.h"

void Circle(Path& path, Pt c, double r, double a0)
{
	int steps = int(r / 0.05);
	for(int j = 0; j <= steps; j++) {
		double a = j * M_2PI / steps + a0;
		path.Kerf(c.x - r * sin(a), c.y + r * cos(a));
	}
}

void CutSpar(Path& r, const Vector<Pt>& foil, int& i, Pt pos, Pt dim, bool circle, Point dir)
{
	DLOG("Spar");
	Pt p = LineIntersection(foil[i - 1], foil[i],
	                        Pt(Nvl(pos.x, 0.0), Nvl(pos.y, 0.0)), Pt(Nvl(pos.x, 1.0), Nvl(pos.y, 1.0)));
	if(circle) {
		Pt u = Orthogonal(p - foil[i - 1]) / Distance(p, foil[i - 1]);
		r.Kerf(p);
		r.NewSegment();
		r.To(p - u * dim.y);
		Circle(r, p - u * (dim.x / 2 + dim.y), dim.x / 2, dir.x < 0 ? M_PI : 0);
		r.To(p - u * dim.y);
		r.To(p);
		r.NewSegment();
	}
	else {
		Pt p2 = Null;
		while(i < foil.GetCount()) {
			double t1, t2;
			LineCircleIntersections(p, dim.x, foil[i - 1], foil[i], t1, t2, 999999);
			if(t1 < 0 || t1 > 1)
				t1 = DBL_MAX;
			if(t2 < 0 || t2 > 1)
				t2 = DBL_MAX;
			if(t2 < t1)
				Swap(t1, t2);
			if(t1 <= 1) {
				p2 = foil[i - 1] + (foil[i] - foil[i - 1]) * t1;
				if(dir.x * (p2.x - p.x) + dir.y * (p2.y - p.y) < 0)
					if(t2 <= 1)
						p2 = foil[i - 1] + (foil[i] - foil[i - 1]) * t2;
					else
						p2 = Null;
				if(!IsNull(p2))
					break;
			}
			i++;
		}
		if(!IsNull(p2)) {
			r.Kerf(p);
			r.NewSegment();
			Pt u = Orthogonal(p2 - p) / Distance(p2, p);
			p -= u * dim.y;
			r.Kerf(p);
			p -= Orthogonal(u) * dim.x;
			r.Kerf(p);
			r.Kerf(p2);
			r.NewSegment();
			r.Kerf(foil[i]);
		}
	}
	DLOG("End of spar");
}

bool DoSpar(Path& r, const Vector<Pt>& foil, int& i, Spar& spar)
{
	if(i <= 0)
		return false;
	Pt p = foil[i];
	Pt prev = foil[i - 1];
	if(spar.kind == TOP_SPAR && p.x > spar.pos && p.x > foil[i - 1].x) {
		CutSpar(r, foil, i, Pt(spar.pos, Null), spar.dimension, spar.circle, Point(1, 0));
		spar.kind = Null;
		return true;
	}
	if(spar.kind == BOTTOM_SPAR && p.x < spar.pos && p.x < foil[i - 1].x) {
		CutSpar(r, foil, i, Pt(spar.pos, Null), spar.dimension, spar.circle, Point(-1, 0));
		spar.kind = Null;
		return true;
	}
	return false;
}

bool DoSpars(Path& r, const Vector<Pt>& foil, int& i, Vector<Spar>& spars)
{
	for(Spar& s : spars)
		if(DoSpar(r, foil, i, s))
			return true;
	return false;
}

void ReadSpar(Vector<Spar>& spar, int kind, double le, Ctrl& pos, Ctrl& cx, Ctrl& cy, Ctrl& circle)
{
	Sizef dim = MakePoint(cx, cy);
	if(!IsNull(pos) && dim.cx > 0 && dim.cy > 0) {
		Spar& s = spar.Add();
		s.kind = kind;
		s.dimension = dim;
		s.pos = le - (double)~pos;
		s.circle = (bool)~circle;
		if(!s.circle) {
			if(kind == TOP_SPAR)
				s.pos -= dim.cx / 2;
			if(kind == BOTTOM_SPAR)
				s.pos += dim.cx / 2;
		}
	}
}

Path Wing::Get(double inverted)
{
	DLOG("=============== WING");
	Path r;
	
	double t = Nvl((double)~te);
	double w = Nvl((double)~width);
	
	Pt ledim = MakePoint(le_spar_width, le_spar_height);
	Pt tedim = MakePoint(te_spar_width, te_spar_height);
	
	Pt start = MakePoint(x, y);
	
	if(right)
		start.x = Nvl((double)~other->width, 0.0) + Nvl((double)~other->x, 0.0) - start.x - w;

	Vector<Spar> spars;
	ReadSpar(spars, TOP_SPAR, w, top_spar, top_spar_width, top_spar_height, top_spar_circle);
	ReadSpar(spars, BOTTOM_SPAR, w, bottom_spar, bottom_spar_width, bottom_spar_height, bottom_spar_circle);

	Vector<Pt> foil = airfoil.Get();
	for(int i = 0; i < foil.GetCount(); i++) {
		Pt& a = foil[i];
		a.x = 1 - a.x;
		a *= width;
		if(t && a.x < width / 2 && i < foil.GetCount() / 2) // adjust te thickness
			a.y = max(a.y, t);
	}
	
	if(!IsNull(inverted)) {
		Reverse(foil);
		for(auto& p : foil)
			p.y = -p.y;
	}

	double rot = Nvl((double)~rotate);
	if(!IsNull(inverted))
		rot = -rot;

	if(rot)
		r.Rotate(width - Nvl((double)~rotate_around) + start.x, start.y, M_2PI * rot / 360.0);
	
	r.Offset(start.x, start.y);
	if(rot)
		r.Rotate(width - Nvl((double)~rotate_around), 0, M_2PI * rot / 360.0);

	Pt pp(-start.x, te);
	r.NewSegment();
	r.To(pp);
	r.NewSegment();

	r.Kerf(-(start.x > 5 ? 5 : start.x / 3), te); // this is lead-in to avoid long stay of wire
	r.NewSegment();

	bool top = true;
	for(int i = 0; i < foil.GetCount(); i++) {
		r.MainShape();
		Pt p = foil[i];
		if(top && i + 1 < foil.GetCount() && p.x > foil[i + 1].x) { // LE split to new segment
			top = false;
			r.NewSegment();
		}
		if(DoSpars(r, foil, i, spars))
			;
		else
		if(tedim.x > 0 && i > 0 && p.x < foil[i - 1].x && Distance(p, Pt(0, 0)) <= tedim.x) {
			double t, t2;
			Pt p0 = foil[i - 1];
			LineCircleIntersections(Pt(0, 0), tedim.x, p0, p, t, t2);
			if(t < 0 || t > 1)
				t = t2;
			if(t >= 0 && t <= 1) {
				p = (p - p0) * t + p0;
				Pt u = (p - p0) / Distance(p, foil[i - 1]);
				r.Kerf(p);
				r.NewSegment();
				r.Kerf(p - Orthogonal(u) * tedim.y);
				r.NewSegment();
				r.Kerf(p - Orthogonal(u) * tedim.y + u * tedim.x);
				break;
			}
		}
		else
		if(ledim.x > 0 && p.y < ledim.x / 2 && i > 0 && p.y < foil[i - 1].y && !le_spar_circle) {
			CutSpar(r, foil, i, Pt(Null, ledim.x / 2), ledim, le_spar_circle, Point(0, -1));
			ledim.x = 0;
		}
		else
		if(le_spar_circle && ledim.x > 0 && i > 0 && p.y < foil[i - 1].y && p.y < 0) {
			r.NewSegment();
			Pt p1(width, 0);
			r.Kerf(p1);
			r.To(width - ledim.y, 0);
			Circle(r, Pt(width - ledim.y - ledim.x / 2, 0), ledim.x / 2, -M_PI / 2);
			r.To(p1);
			r.Kerf(p);
			ledim.x = 0;
			r.NewSegment();
		}
		else
			r.Kerf(p);
		if(i == 0)
			r.NewSegment();
	}
	
//	airfoil.Render(r, Nvl((double)~width), start, t, ~smooth);

	DLOG("======== ENDING");

	r.EndMainShape();

	if(cutte) {
		r.NewSegment();
		r.Kerf(0 /*-kerf*/, te); // TODO
	}

	r.NewSegment();
	r.Kerf(-(start.x > 5 ? 5 : start.x / 3), 0); // this is lead-out to avoid long stay of wire

	r.NewSegment();
	r.Kerf(-start.x, 0);

	r.NewSegment();

	r.Identity();

	return r;
}

Wing::Wing()
{
	CtrlLayout(*this);
	
	width <<= 180;
	y <<= 15;
	x <<= 10;
	te <<= 0.3;
	
	other = NULL;
	dlg = NULL;
	right = false;
}
