#include "Hot4d.h"

VectorMap<String, Ctrl *> GetCtrlMap(Ctrl& parent)
{
	VectorMap<String, Ctrl *> map;
	for(Ctrl *q = parent.GetFirstChild(); q; q = q->GetNext()) {
		String id = q->GetLayoutId();
		if(!dynamic_cast<Label *>(q))
			map.Add(id, q);
	}
	return map;
}

void SetValues(Ctrl& parent, const ValueMap& json)
{
	auto h = GetCtrlMap(parent);
	for(auto& e : ~h)
		*e.value <<= json[e.key];
}

ValueMap GetValues(Ctrl& parent)
{
	ValueMap m;
	auto h = GetCtrlMap(parent);
	for(auto& e : ~h)
		m.Add(e.key, ~*e.value);
	return m;
}


void Shape::Load(const ValueMap& json)
{
	SetValues(*this, json);
}

ValueMap Shape::Save()
{
	return GetValues(*this);
}

Pointf MakePoint(Ctrl& a, Ctrl& b)
{
	return Pointf(Nvl((double)~a), Nvl((double)~b));
}

double LineIntersectionT(Pointf a1, Pointf a2, Pointf b1, Pointf b2)
{
	Pointf s1 = a2 - a1;
	Pointf s2 = b2 - b1;
	double t = (s2.x * (a1.y - b1.y) - s2.y * (a1.x - b1.x)) / (s1.x * s2.y - s2.x * s1.y);
	return IsNaN(t) ? Null : t;
}

Pointf LineIntersection(Pointf a1, Pointf a2, Pointf b1, Pointf b2)
{
	double t = LineIntersectionT(a1, a2, b1, b2);
	if(IsNaN(t))
		return Null;
	return t * (a2 - a1) + a1;
}

int LineCircleIntersections(Pointf c, double radius, Pointf p1, Pointf p2, double& t1, double& t2, double def)
{
	Pointf d = p2 - p1;
	
	double A = Squared(d);
	double B = 2 * (d.x * (p1.x - c.x) + d.y * (p1.y - c.y));
	double C = Squared(p1 - c) - radius * radius;

	t1 = t2 = def;
	
	double det = B * B - 4 * A * C;
	if(A == 0 || det < 0) // TODO: Check A==0 condition
		return 0;
	else
	if (det == 0) {
		t1 = -B / (2 * A);
		return 1;
	}
	else {
		double h = sqrt(det);
		t1 = (-B + h) / (2 * A);
		t2 = (-B - h) / (2 * A);
		return 2;
	}
}

double PathLength(const Vector<Pointf>& path, int from, int count)
{
	double length = 0;
	for(int i = from; i < from + count - 1; i++)
		length += Distance(path[i], path[i + 1]);
	return length;
}

double PathLength(const Vector<Pointf>& path)
{
	return PathLength(path, 0, path.GetCount());
}

Pointf AtPath(const Vector<Pointf>& path, double at, Pointf *dir1, int from)
{
	double length = 0;
	for(int i = from; i < path.GetCount(); i++) {
		double d = Distance(path[i], path[i + 1]);
		double h = at - length;
		if(h < d) {
			Pointf d1 = (path[i + 1] - path[i]) / d;
			if(dir1)
				*dir1 = d1;
			return path[i] + h * d1;
		}
		length += d;
	}
	return Null;
}
