#include "Hot4d.h"

Path Wing::Get()
{
	Path r;
	
	double t = Nvl((double)~te);

	Pointf start(Nvl((double)~x), Nvl((double)~y));
	
	r.To(0, start.y + te);
	airfoil.Render(r, Nvl((double)~width), start, t, ~smooth);
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
