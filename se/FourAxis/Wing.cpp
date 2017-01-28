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

Rectf Wing::GetBounds()
{
	Pointf start = MakePoint(x, y);
	double w = Nvl((double)~width);
	return Rectf(start, Sizef(w, 1));
}

Path Wing::Get(double inverted)
{
	DLOG("=============== WING");
	Path r;
	
	double t = Nvl((double)~te);
	double w = Nvl((double)~width);
	
	double ts = ~top_spar;
	Pt tdim = MakePoint(top_spar_width, top_spar_height);

	double bs = ~bottom_spar;
	Pt bdim = MakePoint(bottom_spar_width, bottom_spar_height);

	Pt ledim = MakePoint(le_spar_width, le_spar_height);
	Pt tedim = MakePoint(te_spar_width, te_spar_height);

	Pt start(Nvl((double)~x), Nvl((double)~y));

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

	DLOG("!!!");
	r.Kerf(-(start.x > 5 ? 5 : start.x / 3), te); // this is lead-in to avoid long stay of wire
	r.NewSegment();
	DLOG("!!!");

	bool top = true;
	for(int i = 0; i < foil.GetCount(); i++) {
		Pt p = foil[i];
		if(top && i + 1 < foil.GetCount() && p.x > foil[i + 1].x) { // LE split to new segment
			top = false;
			r.NewSegment();
		}
		if(!IsNull(ts) && p.x > ts && i > 0) {
			CutSpar(r, foil, i, Pt(ts, Null), tdim, top_spar_circle, Point(1, 0));
			ts = Null;
		}
		else
		if(!IsNull(bs) && p.x < bs && i > 0 && p.x < foil[i - 1].x) {
			CutSpar(r, foil, i, Pt(bs, Null), bdim, bottom_spar_circle, Point(-1, 0));
			bs = Null;
		}
		else
			r.Kerf(p);
	}
	
//	airfoil.Render(r, Nvl((double)~width), start, t, ~smooth);

	DLOG("======== ENDING");

	if(cutte) {
		r.NewSegment();
		r.Kerf(0, te);
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
}
