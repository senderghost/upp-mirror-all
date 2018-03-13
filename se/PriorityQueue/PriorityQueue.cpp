#include <Core/Core.h>

using namespace Upp;

template <class Container, class Pred>
void HeapSwapIn(Container& m, Pred less)
{
	int i = m.GetCount() - 1;
	while(i > 0) {
		int ii = (i - 1) >> 1;
		if(less(m[i], m[ii])) {
			Swap(m[i], m[ii]);
			i = ii;
		}
		else
			break;
	}
}

template <class Container, class Pred>
void HeapSwapOut(Container& m, Pred less)
{
	Swap(m[m.GetCount() - 1], m[0]);
	int i = 0;
	for(;;) {
		int ii = 2 * i + 1;
		if(ii >= m.GetCount() - 1)
			break;
		int ri = 2 * i + 2;
		if(ri < m.GetCount() - 1 && less(m[ri], m[ii]))
			ii = ri;
		if(less(m[ii], m[i])) {
			Swap(m[ii], m[i]);
			i = ii;
		}
		else
			break;
	}
}


template <class K, class T, class Less = StdLess<K>>
class PriorityQueue {
	struct Item : Moveable<Item> {
		K key;
		T value;
		
		bool operator<(const Item& b) const { return Less()(value, b.value); }
	};
	
	Vector<Item> data;
	
public:
	void Push(const K& key, const T& value) { Item& m = data.Add(); m.key = key; m.value = value; HeapSwapIn(data, std::less<Item>()); }
	int  GetCount() const                   { return data.GetCount(); }
	T&   Top()                              { return data[0].value; }
	void Drop()                             { HeapSwapOut(data, std::less<Item>()); data.Drop(); }
	T    Pop()                              { T x = Top(); Drop(); return x; }
	
	~PriorityQueue() { return; AssertMoveable((T *)0); }
};

CONSOLE_APP_MAIN
{
	Vector<int> x;
	for(int s : { 3, 5, 8, 2, 3, 5, 1, 7 }) {
		x.Add(s);
		HeapSwapIn(x, StdLess<int>());
		DDUMP(x);
	}
	DLOG("----");
	while(x.GetCount()) {
		DDUMP(x);
		HeapSwapOut(x, StdLess<int>());
		x.Drop();
	}
	
	Vector<int> h;
	SeedRandom(0);
	for(int i = 0; i < 3000000; i++)
		h.Add(Random(10000));
	
	Vector<int> s1;
	Vector<int> s2;
	Vector<int> heap;
	for(int i = 0; i < h.GetCount(); i++) {
		heap.Add(h[i]);
		HeapSwapIn(heap, StdLess<int>());
	}

	while(heap.GetCount()) {
		s1.Add(heap[0]);
		HeapSwapOut(heap, StdLess<int>());
		heap.Drop();
	}
	
	PriorityQueue<int, int> queue;
	for(int x : h)
		queue.Push(x, x);
	while(queue.GetCount())
		s2.Add(queue.Pop());
	
	
	Sort(h);
	
	DDUMP(h.GetCount());
	DDUMP(s1.GetCount());
	
	DUMP(h);
	DUMP(s1);
	
	ASSERT(h == s1);
	ASSERT(h == s2);
}
