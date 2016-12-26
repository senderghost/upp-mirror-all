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
	for(auto&& e : ~GetCtrlMap(parent))
		*e.value <<= json[e.key];
}

ValueMap GetValues(Ctrl& parent)
{
	ValueMap m;
	for(auto&& e : ~GetCtrlMap(parent))
		m.Add(e.key, ~*e.value);
	return m;
}
