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

Pointf LineIntersection(Pointf a1, Pointf a2, Pointf b1, Pointf b2)
{
	Pointf s1 = a2 - a1;
	Pointf s2 = b2 - b1;
	double t = (s2.x * (a1.y - b1.y) - s2.y * (a1.x - b1.x)) / (s1.x * s2.y - s2.x * s1.y);
	if(IsNaN(t))
		return Null;
	return t * (a2 - a1) + a1;
}
