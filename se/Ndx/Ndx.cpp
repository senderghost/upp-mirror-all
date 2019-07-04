#include <Core/Core.h>

using namespace Upp;

struct Ndx {
	template <class K, class V>
	struct Entry : Moveable<Entry> {
		K   key;
		int prev;
	};

	Vector<Entry> data;
	Buffer<int>   map;
	
public:
	void Add(const K& key) {
		int& ii = map[GetHashValue(key)];
		int i = data.GetCount();
		if(data.GetCount() > mask)
			Reindex();
		Entry& e = data.Add();
		e.key = key;
		e.prev = ii;
		ii = i;
	}
	void Find(const K& key) {
		GetHashValue
	}
}

CONSOLE_APP_MAIN
{
	
}


