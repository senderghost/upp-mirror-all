#include "Hot4d.h"

Path FuseProfile::Get()
{
	Path r;
	
	Pt start = MakePoint(x, y);
	
	double hy = Nvl((double)~head_y, start.y);
	double ty = Nvl((double)~tail_y, start.y);
	
	Sizef dim = MakePoint(cx, top_cy);
	double bcy = Nvl((double)~bottom_cy);
	
	Vector<Pt> foil[2];
	
	double head = Nvl((double)~head_cy) / 2;
	double tail = Nvl((double)~tail_cy) / 2;
	
	DUMP(head);
	DUMP(tail);

	for(int bottom = 0; bottom < 2; bottom++) {
		Vector<Pt>& f = foil[bottom];
		f = GetHalfFoil(airfoil.Get(), bottom);
		double ay = GetMaxY(f, bottom ? -1 : 1);
		if(ay)
			ay = (bottom ? bcy : dim.cy) / ay;
		Mul(f, 1, ay);
		CutHalfFoil(f, head, tail);
		Mul(f, f.GetCount() ? dim.cx / f.Top().x : 0, bottom ? -1 : 1);
	}
	
	Reverse(foil[1]);

	r.To(0, start.y + ty);
	r.Offset(start.x, start.y);
	
	Vector<Pt> shape;
	shape.Add(Pt(0, ty));
	for(int bottom = 0; bottom < 2; bottom++)
		for(Pt p : foil[bottom]) {
			p.y += p.x / dim.cx * (hy - ty) + ty;
			shape.Add(p);
		}
	shape.Add(Pt(0, ty));
	
	if(saddle) {
		Vector<Pt> sa = saddle_airfoil.Get();
		Reverse(sa);
		InvertX(sa);
		double sch = Nvl((double)~saddle_chord);
		Mul(sa, sch, sch);
		double angle = -Nvl((double)~saddle_incidence);
		if(angle) {
			angle = M_2PI * angle / 360;
			double sina = sin(angle);
			double cosa = cos(angle);
			for(Pt& p : sa) {
				p.x = cosa * p.x + sina * p.y;
				p.y = -sina * p.x + cosa * p.y;
			}
		}
		Pt spos = MakePoint(saddle_x, saddle_y);
		for(Pt& p : sa)
			p += spos;
		
		bool dosaddle = true;
		
		Vector<Pt> shape2;
		for(int i = 0; i < shape.GetCount(); i++) {
			int ii = 0;
			Pt pt;
			if(i > 0 && dosaddle && PathIntersection(shape[i - 1], shape[i], sa, ii, pt)) {
				shape2.Add(pt);
				for(int pass = 0; pass < 2 && dosaddle; pass++) {
					while(ii < sa.GetCount()) {
						shape2.Add(sa[ii++]);
						if(ii > 0 && ii < sa.GetCount() && PathIntersection(sa[ii - 1], sa[ii], shape, i, pt)) {
							shape2.Add(pt);
							dosaddle = false;
							break;
						}
					}
					ii = 0;
				}
			}
			if(i < shape.GetCount())
				shape2.Add(shape[i]);
		}
		
		if(dosaddle) {
			Pt ms0(-start.x / 2, ty);
			Pt ms(-start.x / 2, spos.y);
			sa.Insert(0, ms0);
			sa.Insert(1, ms);
			sa.Add(ms);
			sa.Add(ms0);
			shape.Insert(0, sa);
		}
		else
			shape = pick(shape2);
	}

	for(Pt p : shape)
		r.Kerf(p);

	r.Identity();
	r.Kerf(0, start.y + ty);

	return r;
}

FuseProfile::FuseProfile()
{
	CtrlLayout(*this);
	
	y <<= 25;
	head_y <<= 0;
	tail_y <<= 0;
	x <<= 10;
}
