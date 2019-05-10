namespace New {

force_inline
void HashBase::Del(int ii)
{ // remove ii from its bucket
#if 0
	Hash& h = hash[ii];
	if(h.hash == 0)
		return;
	Bucket& m = map[h.hash & mask];
	ASSERT(m.first >= 0);
	if(ii == m.first) {
		if(m.first == m.last) // this was the only item in the bucket
			m.first = m.last = -1;
		else
			m.first = h.next;
	}
	else // need to find the item before ii
		for(int i = m.first; i >= 0;) {
			Hash& p = hash[i];
			if(p.next == ii) { // found item before ii, remove
				p.next = h.next; // point to item after ii
				if(ii == m.last) // ii was the last item
					m.last = i; // set it to item before ii
				break;
			}
			i = p.next;
		}
#endif
}

force_inline
void HashBase::Ins(int ii, dword sh)
{ // insert ii into bucket
#if 0
	Hash& h = hash[ii];
	h.hash = sh;
	Bucket& m = map[sh & mask];
	if(m.first < 0) { // first in bucket
		m.first = m.last = ii;
		h.next = -1;
	}
	else
	if(ii < m.first) { // before first
		h.next = m.first;
		m.first = ii;
	}
	else
	if(ii > m.last) { // after last
		hash[m.last].next = ii;
		m.last = ii;
		h.next = -1;
	}
	else
		for(int i = m.first; i >= 0;) { // find the position in the the list
			Hash& p = hash[i];
			if(ii < p.next) { // found item before ii, insert
				h.next = p.next;
				p.next = ii;
				break;
			}
			i = p.next;
		}
#endif
}

force_inline
void HashBase::Set(int ii, dword h)
{
#if 0
	if(IsUnlinked(ii)) { // this should not happen very often...
		if(ii == unlinked)
			unlinked = hash[ii].next;
		else { // remove from unlinked list
			for(int i = unlinked; i >= 0; i = hash[i].next)
				if(hash[i].next == ii) {
					hash[i].next = hash[ii].next;
					break;
				}
		}
	}
	else
		Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
	Check();
#endif
}

force_inline
int HashBase::PutUnlinked(dword h)
{
#if 0
	int ii = unlinked;
	ASSERT(ii >= 0 && IsUnlinked(ii));
	unlinked = hash[ii].next;
	Ins(ii, Smear(h)); // put to new bucket list
	return ii;
#endif
	return -1;
}

force_inline
void HashBase::Link(int& m, Hash& hh, int ii)
{
	if(m == -1)
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
void HashBase::AddS(dword sh)
{
	int ii = hash.GetCount();
	Hash& hh = hash.Add();
	hh.hash = sh;
	if(ii >= (int)mask)
		GrowMap();
	else
		Link(map[sh & mask], hh, ii);
}

force_inline
void HashBase::Add(dword h)
{
	AddS(Smear(h));
}

template <class P>
force_inline
void HashBase::UnlinkKey(dword h, P pred)
{
#if 0
	h = Smear(h);
	Bucket& m = map[h & mask];
	int i = m.first;
	int pi = i;
	while(i >= 0) {
		const Hash& ih = hash[i];
		int ni = ih.next;
		if(h == ih.hash && pred(i)) {
			if(i == m.first) {
				if(i == m.last)
					m.first = m.last = -1;
				else
					m.first = ih.next;
			}
			else {
				if(i == m.last)
					m.last = pi;
				hash[pi].next = ih.next;
			}
			hash[i].hash = 0;
			hash[i].next = unlinked;
			unlinked = i;
		}
		else
			pi = i;
		i = ni;
	}
#endif
}

force_inline
void HashBase::Unlink(int ii)
{
#if 0
	Del(ii);
	hash[ii].hash = 0;
	hash[ii].next = unlinked;
	unlinked = ii;
	Check();
#endif
}

template <typename T>
force_inline
int Index<T>::FindFrom(int i, dword sh, const T& k) const
{
	if(i >= 0) {
		int i0 = i;
		while(i > i0) {
			const Hash& ih = hash[i];
			if((std::numeric_limits<T>::is_integer || sh == ih.hash) && key[i] == k)
				break;
			i = ih.next;
		}
	}
	return i;
}

template <class T>
int Index<T>::Find(const T& k) const
{
	dword sh = Smear(k);
	return FindFrom(map[sh & mask], sh, k);
}

template <class T>
int Index<T>::FindNext(int i) const
{
	return FindFrom(hash[i].next, hash[i].hash, key[i]);
}

template <class T>
int  Index<T>::FindAdd(const T& k) {
	dword sh = Smear(k);
	int i = FindFrom(map[sh & mask], sh, k);
	if(i < 0) {
		i = key.GetCount();
		key.Add(k);
		AddS(sh);
	}
	return i;
}

};