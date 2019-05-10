namespace New {


force_inline
void HashBase::Link(int& m, Hash& hh, int ii)
{
	if(m < 0)
		hh.next = ii;
	else {
		hh.next = hash[m].next;
		hash[m].next = ii;
	}
	m = ii;
}


force_inline
void HashBase::Link(int ii, dword sh)
{
	Link(map[sh & mask], hash[ii], ii);
}

force_inline
void HashBase::Del(int& m, Hash& hh, int ii)
{ // unlink from m
#if 0
	if(ii == m) { // this is item pointed by map
		if(hh.next == ii) { // this is the only item in the bucket
			m = -1; // bucket is now empty
			return;
		}
		m = hh.next; // move bucket pointer to the next item
	}
	hash[hh.next].prev = hh.prev; // unlink
	hash[hh.prev].next = hh.next;
#endif
}

inline
void HashBase::Ins(int& m, Hash& hh, int i)
{
#if 0
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
#endif
}

inline
int  HashBase::PutUnlinked(dword sh)
{
	return -1;
/*
	int i = unlinked;
	Hash& hh = hash[unlinked];
	Del(unlinked, hh, unlinked);
	Ins(map[sh & mask], hh, i);
	hh.hash = sh;
	return i;
*/
}

template <typename T>
void Index<T>::GrowAdd(const T& k, dword sh)
{
	int n = key.GetCount();
	key.GrowAdd(k);
	Hash *h = (Hash *)MemoryAlloc(key.GetAlloc() * sizeof(Hash));
	if(hash) {
		memcpy(h, hash, sizeof(Hash) * n);
		MemoryFree(hash);
	}
	hash = h;
}

template <typename T>
force_inline
void Index<T>::FinishAdd(int& m, int ii, dword sh)
{
	Hash& hh = hash[ii];
	hh.hash = sh;
	if(ii >= (int)mask)
		GrowMap(key.GetCount());
	else
		Link(m, hh, ii);
}

template <typename T>
force_inline
void Index<T>::AddS(int& m, const T& k, dword sh)
{
	int ii = key.GetCount();
	if(ii >= key.GetAlloc())
		GrowAdd(k, sh);
	else
		new(key.Rdd()) T(clone(k));
	FinishAdd(m, ii, sh);
}

template <typename T>
force_inline
void Index<T>::AddS(const T& k, dword sh)
{
	AddS(map[sh & mask], k, sh);
}

template <typename T>
force_inline
int Index<T>::FindFrom(int i, dword sh, const T& k, int end) const
{
	if(i >= 0) {
		i = hash[i].next;
		do {
			const Hash& ih = hash[i];
			if((std::numeric_limits<T>::is_integer || sh == ih.hash) && key[i] == k)
				return i;
			i = ih.next;
		}
		while(i != end);
	}
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
__declspec(noinline)
int Index<T>::Add2(int& m, const T& k, dword sh)
{
	int i = key.GetCount();
	AddS(m, k, sh);
	return i;
}

template <class T>
int  Index<T>::FindAdd(const T& k, bool& found) {
	dword sh = Smear(k);
	int& m = map[sh & mask];
	if(m >= 0) {
		int i = hash[m].next;
		do {
			const Hash& ih = hash[i];
			if((std::numeric_limits<T>::is_integer || sh == ih.hash) && key[i] == k) {
				found = true;
				return i;
			}
			i = ih.next;
		}
		while(i != m);
	}
	found = false;
	return Add2(m, k, sh);
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
/*	do {
		const Hash& ih = hash[i];
		if((std::numeric_limits<T>::is_integer || sh == ih.hash) && key[i] == k)
			return i;
		i = ih.prev;
	}
	while(i != end);*/
	return -1;
}

template <class T>
int Index<T>::FindLast(const T& k) const
{
	return -1;
/*	dword sh = Smear(k);
	int& m = map[sh & mask];
	return m < 0 ? -1 : FindBack(hash[m].prev, sh, k, m);*/
}

template <class T>
int Index<T>::FindPrev(int i) const
{
	return -1;
/*
	const Hash& hh = hash[i];
	int end = map[hash[i].hash & mask];
	return hh.prev == end ? -1 : FindFrom(hh.prev, hh.hash, key[i], end);
*/
}

template <typename T>
void Index<T>::Unlink(int ii)
{
	/*
	Hash& hh = hash[ii];
	Del(map[hh.hash & mask], hh, ii);
	Link(unlinked, hh, ii);
	unlinked = ii;
	hh.hash = 0;
	*/
}

template <typename T>
void Index<T>::UnlinkKey(const T& k)
{
	/*
	dword sh = Smear(k);
	int& m = map[sh & mask];
	int i = m;
	if(i >= 0)
		do {
			Hash& hh = hash[i];
			if((std::numeric_limits<T>::is_integer || sh == hh.hash) && key[i] == k) {
				int ni = hh.next;
				Del(m, hh, i);
				Link(unlinked, hh, i);
				unlinked = i;
				hh.hash = 0;
				if(i == ni) // last item removed
					break;
				i = ni;
			}
			else
				i = hh.next;
		}
		while(i != m);
	*/
}

template <typename T>
int Index<T>::Put(const T& k)
{
	return -1;
	/*
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
	*/
}

template <typename T>
void Index<T>::Set(int ii, const T& k)
{
	/*
	Hash& hh = hash[ii];
	if(IsUnlinked(ii))
		Del(unlinked, hh, ii);
	else
		Del(map[hh.hash & mask], hh, ii);
	
	dword sh = Smear(k);
	hh.hash = sh;
	Ins(map[sh & mask], hh, ii);
	key[ii] = k;
	*/
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
		h << i << ": " << key[i] << '/' << hash[i].hash << " -> " << hash[i].next;
	}
	return h;
}

};