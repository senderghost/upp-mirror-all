namespace New {

force_inline
void HashBase::Link(int& m, Hash& hh, int ii)
{
	if(m < 0)
		m = hh.prev = next[ii] = ii;
	else {
		next[ii] = m;
		hh.prev = hash[m].prev;
		next[hh.prev] = ii;
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
	int ni = next[ii];
	if(ii == m) { // this is item pointed by map
		if(next[ii] == ii) { // this is the only item in the bucket
			m = -1; // bucket is now empty
			return;
		}
		m = ni; // move bucket pointer to the next item
	}
	hash[ni].prev = hh.prev; // unlink
	next[hh.prev] = ni;
}

inline
void HashBase::Ins(int& m, Hash& hh, int i)
{
/*
	if(m < 0) { // first
		m = i;
		hh.prev = hh.next = i;
	}
	else { // find the correct position to insert
		int q = m;
		if(i < hash[q].prev) {
			do {
				if(i < q)
					break;
				q = hash[q].next;
			}
			while(q != m);
			if(q == m)
				m = i;
		}
		Hash& hq = hash[q];
		hh.next = q;
		hh.prev = hq.prev;
		hash[hh.prev].next = i;
		hq.prev = i;
	}
*/
}

inline
int  HashBase::PutUnlinked(dword sh)
{
	int i = unlinked;
	Hash& hh = hash[unlinked];
	Del(unlinked, hh, unlinked);
	Ins(map[sh & mask], hh, i);
	hh.hash = sh;
	return i;
}

template <typename T>
void Index<T>::GrowAdd(const T& k, dword sh)
{
	int n = key.GetCount();
	key.GrowAdd(k);
	Hash *h = (Hash *)MemoryAlloc(key.GetAlloc() * sizeof(Hash));
	int  *x = (int *)MemoryAlloc(key.GetAlloc() * sizeof(int));
	if(hash) {
		memcpy(h, hash, sizeof(Hash) * n);
		MemoryFree(hash);
		memcpy(x, next, sizeof(int) * n);
		MemoryFree(next);
	}
	hash = h;
	next = x;
}

template <typename T>
void Index<T>::AddS(int& m, const T& k, dword sh)
{
	int ii = key.GetCount();
	if(ii >= key.GetAlloc())
		GrowAdd(k, sh);
	else
		new(key.Rdd()) T(clone(k));
	Hash& hh = hash[ii];
	hh.hash = sh;
	if(ii >= (int)mask)
		GrowMap(key.GetCount());
	else
		Link(m, hh, ii);
}

template <typename T>
void Index<T>::AddS(const T& k, dword sh)
{
	AddS(map[sh & mask], k, sh);
}

template <typename T>
force_inline
int Index<T>::FindFrom(int i, const T& k, int end) const
{
	if(i >= 0)
		do {
			if(key[i] == k)
				return i;
			i = next[i];
		}
		while(i != end);
	return -1;
}

template <class T>
int Index<T>::Find(const T& k) const
{
	int& m = map[Smear(k) & mask];
	return FindFrom(m, k, m);
}

template <class T>
int Index<T>::FindNext(int i) const
{
	const Hash& hh = hash[i];
	int end = map[hash[i].hash & mask];
	return next[i] == end ? -1 : FindFrom(next[i], key[i], end);
}

template <typename T>
force_inline
int Index<T>::FindBack(int i, const T& k, int end) const
{
	do {
		if(key[i] == k)
			return i;
		i = hash[i].prev;
	}
	while(i != end);
	return -1;
}

template <class T>
int Index<T>::FindLast(const T& k) const
{
	dword sh = Smear(k);
	int& m = map[sh & mask];
	return m < 0 ? -1 : FindBack(hash[m].prev, k, m);
}

template <class T>
int Index<T>::FindPrev(int i) const
{
	const Hash& hh = hash[i];
	int end = map[hash[i].hash & mask];
	return hh.prev == end ? -1 : FindBack(hh.prev, key[i], end);
}

template <class T>
template <class OP>
force_inline
int Index<T>::FindAdd(const T& k, OP op) {
	dword sh = Smear(k);
	int& m = map[sh & mask];
	int i = m;
	if(i >= 0)
		do {
			if(key[i] == k)
				return i;
			i = next[i];
		}
		while(i != m);
	i = key.GetCount();
	AddS(m, k, sh);
	op();
	return i;
}

template <typename T>
void Index<T>::Unlink(int ii)
{
	Hash& hh = hash[ii];
	Del(map[hh.hash & mask], hh, ii);
	Link(unlinked, hh, ii);
	unlinked = ii;
	hh.hash = 0;
}

template <typename T>
void Index<T>::UnlinkKey(const T& k)
{
	dword sh = Smear(k);
	int& m = map[sh & mask];
	int i = m;
	if(i >= 0)
		do {
			Hash& hh = hash[i];
			int ni = next[i];
			if(key[i] == k) {
				Del(m, hh, i);
				Link(unlinked, hh, i);
				unlinked = i;
				hh.hash = 0;
				if(i == ni) // last item removed
					break;
			}
			i = ni;
		}
		while(i != m);
}

template <typename T>
int Index<T>::Put(const T& k)
{
	dword sh = Smear(k);
	int i;
	if(HasUnlinked()) {
		i = PutUnlinked(sh);
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
	Ins(map[sh & mask], hh, ii);
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
		h << i << ": " << key[i] << '/' << hash[i].hash << " -> " << hash[i].prev << ":" << next[i];
	}
	return h;
}

};