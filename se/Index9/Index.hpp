namespace New {

force_inline
void HashBase::Link(int& m, Hash& hh, int ii)
{
	if(m < 0)
		m = hh.prev = hh.next = ii;
	else {
		hh.next = m;
		hh.prev = hash[m].prev;
		hash[hh.prev].next = ii;
		hash[m].prev = ii;
	}
}

force_inline
void HashBase::Link(int ii, dword sh)
{
	Link(map[sh & mask], hash[ii], ii);
}

force_inline
void HashBase::Del(int& m, Hash& hh, int ii)
{ // unlink from m
	if(ii == m) { // this is item pointed by map
		if(hh.next == ii) { // this is the only item in the bucket
			m = -1; // bucket is now empty
			return;
		}
		m = hh.next; // move bucket pointer to the next item
	}
	hash[hh.next].prev = hh.prev; // unlink
	hash[hh.prev].next = hh.next;
}

template <typename T>
template <typename U>
never_inline
void Index<T>::GrowAdd(U&& k, dword sh)
{
	int n = key.GetCount();
	key.GrowAdd(std::forward<U>(k));
	Hash *h = (Hash *)MemoryAlloc(key.GetAlloc() * sizeof(Hash));
	if(hash) {
		memcpy(h, hash, sizeof(Hash) * n);
		MemoryFree(hash);
	}
	hash = h;
}

template <typename T>
template <typename U>
void Index<T>::AddS(int& m, U&& k, dword sh)
{
	int ii = key.GetCount();
	if(ii >= key.GetAlloc())
		GrowAdd(std::forward<U>(k), sh);
	else
		new(key.Rdd()) T(std::forward<U>(k));
	Hash& hh = hash[ii];
	hh.hash = sh;
	if(ii >= (int)mask)
		GrowMap(key.GetCount());
	else
		Link(m, hh, ii);
}

template <typename T>
template <typename U>
void Index<T>::AddS(U&& k, dword sh)
{
	AddS(map[sh & mask], std::forward<U>(k), sh);
}

template <typename T>
force_inline
int Index<T>::FindFrom(int i, dword sh, const T& k, int end) const
{
	if(i >= 0)
		do {
			if(key[i] == k)
				return i;
			i = hash[i].next;
		}
		while(i != end);
	return -1;
}

template <class T>
int Index<T>::Find(const T& k) const
{
	dword sh = Smear(k);
	int& m = map[sh & mask];
	return FindFrom(m, sh, k, m);
}

template <class T>
int Index<T>::FindNext(int i) const
{
	const Hash& hh = hash[i];
	int end = map[hash[i].hash & mask];
	return hh.next == end ? -1 : FindFrom(hh.next, hh.hash, key[i], end);
}

template <typename T>
force_inline
int Index<T>::FindBack(int i, dword sh, const T& k, int end) const
{
	do {
		const Hash& ih = hash[i];
		if(key[i] == k)
			return i;
		i = ih.prev;
	}
	while(i != end);
	return -1;
}

template <class T>
int Index<T>::FindLast(const T& k) const
{
	dword sh = Smear(k);
	int& m = map[sh & mask];
	return m < 0 ? -1 : FindBack(hash[m].prev, sh, k, m);
}

template <class T>
int Index<T>::FindPrev(int i) const
{
	const Hash& hh = hash[i];
	int end = map[hash[i].hash & mask];
	return hh.prev == end ? -1 : FindFrom(hh.prev, hh.hash, key[i], end);
}

template <class T>
template <class OP, class U>
force_inline
int Index<T>::FindAdd(U&& k, OP op) {
	dword sh = Smear(k);
	int& m = map[sh & mask];
	int i = m;
	if(i >= 0)
		do {
			if(key[i] == k)
				return i;
			i = hash[i].next;
		}
		while(i != m);
	i = key.GetCount();
	AddS(m, std::forward<U>(k), sh);
	op();
	return i;
}

template <typename T>
void Index<T>::Unlink(int ii)
{
	Hash& hh = hash[ii];
	Del(map[hh.hash & mask], hh, ii);
	Link(unlinked, hh, ii);
	hh.hash = 0;
}

template <typename T>
void Index<T>::UnlinkKey(const T& k)
{
	dword sh = Smear(k);
	int& m = map[sh & mask];
	int i = m;
	if(i >= 0)
		for(;;) {
			Hash& hh = hash[i];
			int ni = hh.next;
			if(key[i] == k) {
				Del(m, hh, i);
				Link(unlinked, hh, i);
				hh.hash = 0;
				if(ni == i) // last item removed
					break;
				i = ni;
			}
			else {
				i = ni;
				if(i == m)
					break;
			}
		}
}

template <typename T>
int Index<T>::Put(const T& k)
{
	dword sh = Smear(k);
	int i;
	if(HasUnlinked()) {
		i = hash[unlinked].prev;
		Hash& hh = hash[i];
		Del(unlinked, hh, i);
		Link(map[sh & mask], hh, i);
		hh.hash = sh;
		key[i] = k;
	}
	else {
		i = GetCount();
		AddS(k, sh);
	}
	return i;
}

template <typename T>
void Index<T>::Set(int ii, const T& k)
{
	Hash& hh = hash[ii];
	if(IsUnlinked(ii))
		Del(unlinked, hh, ii);
	else
		Del(map[hh.hash & mask], hh, ii);
	
	dword sh = Smear(k);
	hh.hash = sh;
	Link(map[sh & mask], hh, ii);
	key[ii] = k;
}

template <typename T>
String Index<T>::ToString() const
{
	String h;
	for(int i = 0; i < key.GetCount(); i++) {
		if(i)
			h << "; ";
		if(IsUnlinked(i))
			h << "#";
		h << i << ": " << key[i] << '/' << (hash[i].hash & 255) << " -> " << hash[i].prev << ":" << hash[i].next;
	}
	return h;
}

};