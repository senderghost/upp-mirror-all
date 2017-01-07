#include "Hot4d.h"

bool IsNaN(Pointf p)
{
	return IsNaN(p.x) || IsNaN(p.y);
}

Pointf Unit(Pointf p)
{
	return p / Length(p);
}

void KerfLine(Pointf p0, Pointf p1, Pointf& k0, Pointf& k1, double kerf)
{
	Pointf o = Orthogonal(p1 - p0);
	o = Unit(o) * kerf;
	k0 = p0 + o;
	k1 = p1 + o;
}

Vector<Pointf> KerfCompensation(Pointf start, const Vector<Pointf>& in, int from, int count, double kerf)
{
	Vector<Pointf> path;
	
	Pointf k3, p2;
	
	bool first = true;
	
	for(int i = from; i < from + count - 2; i++) {
		Pointf p0 = i > 0 ? in[i] : start;
		Pointf p1 = in[i + 1];
		p2 = in[i + 2];
		
		if(p1 == p0) // TODO: Ugly but working
			p1 += Pointf(0.0001, 0.0001);
		if(p2 == p1)
			p2 += Pointf(0.0001, 0.0001);
		if(p2 == p0)
			p2 += Pointf(0.0001, 0.0001);
		
		Pointf k0, k1;
		KerfLine(p0, p1, k0, k1, kerf);
		
		if(first) {
			path << k0;
			first = false;
		}

		double angle = Bearing(p2 - p1) - Bearing(p0 - p1);
		if(angle < 0)
			angle += M_2PI;

		Pointf axis = -(1 - 2 * (angle < M_PI)) * Unit(Unit(p1 - p0) + Unit(p1 - p2)); // angle axis unit vector
		
		Pointf k2;
		KerfLine(p1, p2, k2, k3, kerf);

		Pointf s1 = k1 - k0;
		Pointf s2 = k3 - k2;
		double t = (s2.x * (k0.y - k2.y) - s2.y * (k0.x - k2.x)) / (s1.x * s2.y - s2.x * s1.y);

		Pointf c = t * (k1 - k0) + k0;
		if(angle < M_PI) {
			if(SquaredDistance(p1, c) > 5 * kerf * kerf)
				path << k1
				     << k1 + Unit(k1 - k0) * 2 * kerf
				     << k2 + Unit(k2 - k3) * 2 * kerf
				     << k2;
			else
				path << c;
		}
		else {
			if(sin(angle / 2) * min(Distance(p0, p1), Distance(p1, p2)) < kerf)
				path << kerf * axis + p1;
			else
			if(SquaredDistance(p1, c) > 1.3 * 1.3 * kerf * kerf)
				path << c
				     << kerf * axis + p1
				     << c;
			else
				path << c;
		}
	}
	path.Add(k3);
	
	for(auto& pt : path)
		if(IsNaN(pt) || IsNull(pt))
			pt = start;
		else
			start = pt;
	
	return path;
}
