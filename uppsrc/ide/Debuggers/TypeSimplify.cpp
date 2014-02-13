#include "TypeSimplify.h"

static VectorMap<String, TYPE_SIMPLIFIER_HANDLER> &GetSimplifierMap(void)
{
	static VectorMap<String, TYPE_SIMPLIFIER_HANDLER> map;
	return map;
}

void RegisterSimplifier(const char *pattern, TYPE_SIMPLIFIER_HANDLER handler)
{
	GetSimplifierMap().Add(pattern, handler);
}

TYPE_SIMPLIFIER_HANDLER GetSimplifier(String const &pattern)
{
	VectorMap<String, TYPE_SIMPLIFIER_HANDLER> &map = GetSimplifierMap();
	for(int i = 0; i < map.GetCount(); i++)
	{
		if(pattern.StartsWith(map.GetKey(i)))
			return map[i];
	}
	return NULL;
}
