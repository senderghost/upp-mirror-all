#include "Hot4d.h"

void Circle(Path& path, Pointf c, double r, double a0)
{
	int steps = int(r / 0.05);
	for(int j = 0; j <= steps; j++) {
		double a = j * M_2PI / steps + a0;
		path.Kerf(c.x - r * sin(a), c.y + r * cos(a));
	}
}

void CutSpar(Path& r, const Vector<Pointf>& foil, int& i, Pointf pos, Pointf dim, bool circle, Point dir)
{
	Pointf p = LineIntersection(foil[i - 1], foil[i],
	                            Pointf(Nvl(pos.x, 0.0), Nvl(pos.y, 0.0)), Pointf(Nvl(pos.x, 1.0), Nvl(pos.y, 1.0)));
	if(circle) {
		Pointf u = Orthogonal(p - foil[i - 1]) / Distance(p, foil[i - 1]);
		r.Kerf(p);
		r.To(p - u * dim.y);
		Circle(r, p - u * (dim.x / 2 + dim.y), dim.x / 2, dir.x < 0 ? M_PI : 0);
		r.To(p - u * dim.y);
		r.To(p);
	}
	else {
		Pointf p2 = Null;
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
			Pointf u = Orthogonal(p2 - p) / Distance(p2, p);
			p -= u * dim.y;
			r.Kerf(p);
			p -= Orthogonal(u) * dim.x;
			r.Kerf(p);
			r.Kerf(p2);
			r.Kerf(foil[i]);
		}
	}
}

Path Wing::Get()
{
	Path r;
	
	double t = Nvl((double)~te);
	double w = Nvl((double)~width);
	
	double ts = ~top_spar;
	Pointf tdim = MakePoint(top_spar_width, top_spar_height);

	double bs = ~bottom_spar;
	Pointf bdim = MakePoint(bottom_spar_width, bottom_spar_height);

	Pointf ledim = MakePoint(le_spar_width, le_spar_height);
	Pointf tedim = MakePoint(te_spar_width, te_spar_height);

	Pointf start(Nvl((double)~x), Nvl((double)~y));
	
	Pointf pp(0, start.y + te);
	
	r.To(pp);
	r.Kerf(pp);

	Vector<Pointf> foil = airfoil.Get();
	for(int i = 0; i < foil.GetCount(); i++) {
		Pointf& a = foil[i];
		a.x = 1 - a.x;
		a *= width;
		if(t && a.x < width / 2 && i < foil.GetCount() / 2) // adjust te thickness
			a.y = max(a.y, t);
	}

	r.Offset(start.x, start.y);
	
	for(int i = 0; i < foil.GetCount(); i++) {
		Pointf p = foil[i];
		if(!IsNull(ts) && p.x > ts && i > 0) {
			CutSpar(r, foil, i, Pointf(ts, Null), tdim, top_spar_circle, Point(1, 0));
			ts = Null;
		}
		else
		if(!IsNull(bs) && p.x < bs && i > 0 && p.x < foil[i - 1].x) {
			CutSpar(r, foil, i, Pointf(bs, Null), bdim, bottom_spar_circle, Point(-1, 0));
			bs = Null;
		}
		else
		if(tedim.x > 0 && i > 0 && p.x < foil[i - 1].x && Distance(p, Pointf(0, 0)) <= tedim.x) {
			double t, t2;
			Pointf p0 = foil[i - 1];
			LineCircleIntersections(Pointf(0, 0), tedim.x, p0, p, t, t2);
			if(t < 0 || t > 1)
				t = t2;
			if(t >= 0 && t <= 1) {
				p = (p - p0) * t + p0;
				Pointf u = (p - p0) / Distance(p, foil[i - 1]);
				r.Kerf(p);
				r.Kerf(p - Orthogonal(u) * tedim.y);
				r.Kerf(p - Orthogonal(u) * tedim.y + u * tedim.x);
				break;
			}
		}
		else
		if(ledim.x > 0 && p.y < ledim.x / 2 && i > 0 && p.y < foil[i - 1].y && !le_spar_circle) {
			CutSpar(r, foil, i, Pointf(Null, ledim.x / 2), ledim, le_spar_circle, Point(0, -1));
			ledim.x = 0;
		}
		else
		if(le_spar_circle && ledim.x > 0 && i > 0 && p.y < foil[i - 1].y && p.y < 0) {
			Pointf p1(width, 0);
			r.Kerf(p1);
			r.To(width - ledim.y, 0);
			Circle(r, Pointf(width - ledim.y - ledim.x / 2, 0), ledim.x / 2, -M_PI / 2);
			r.To(p1);
			r.Kerf(p);
			ledim.x = 0;
		}
		else
			r.Kerf(p);
	}
	
	r.Identity();

//	airfoil.Render(r, Nvl((double)~width), start, t, ~smooth);


	if(cutte) {
		r.Kerf(start.x, start.y + te);
		r.To(0, start.y + te);
	}
	r.Kerf(0, start.y);

	return r;
}

Wing::Wing()
{
	CtrlLayout(*this);
	
	width <<= 18;
	y <<= 15;
	x <<= 10;
	te <<= 0.3;
}
