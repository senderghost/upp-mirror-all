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
		DUMP(angle);
		DUMP(t);
		Pointf c = t * (k1 - k0) + k0;
		DDUMP(Distance(p1, c));
		if(angle > M_PI - 0.001 && angle < M_PI + 0.001) // Almost straight line, just use k1
			path << k1;
		else
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

#ifdef _DEBUG
struct KerfTestWindow : TopWindow {
	Pointf p0 = Pointf(200, 200);
	Pointf p1 = Pointf(300, 100);
	Pointf p2 = Pointf(400, 100);
	Pointf p3 = Pointf(500, 200);
	
	virtual void Paint(Draw& w) {
		double kerf = 10;

		ImagePainter p(GetSize());
		p.Clear(White());
		
		Vector<Pointf> in, path;
		in << Pointf(50, 150) << p0 << p1 << p2 << p3 << Pointf(600, 400);
		
		
		path.Add(in[0]);
		path.Append(KerfCompensation(Pointf(0, 0), in, 1, 4, kerf));
		path.Add(in[5]);

		bool first = true;
		for(auto x : path)
			if(!IsNaN(x))
				if(first) {
					p.Move(x);
					first = false;
				}
				else
					p.Line(x);
		if(!first)
			p.LineCap(LINECAP_ROUND).LineJoin(LINEJOIN_ROUND).Stroke(2 * kerf, Blend(White(), LtRed(), 20)).Stroke(1, Red());

		p.Move(0, 0);
		for(auto pt : in)
			p.Line(pt);
		p.Stroke(1, Black());

		w.DrawImage(0, 0, p);
	}
	
	virtual void MouseMove(Point p, dword keyflags) {
		p2 = p;
		Refresh();
	}
	
	virtual void LeftDown(Point p, dword keyflags) {
		p1 = p;
		Refresh();
	}

	virtual void RightDown(Point p, dword keyflags) {
		p3 = p;
		Refresh();
	}
	
	KerfTestWindow() {
		Sizeable().Zoomable();
	}
};

void TestKerf()
{
	KerfTestWindow().Run();
}
#endif
