namespace New {

force_inline
void HashBase::Unlink(int ii)
{
	hash[ii].hash = unlinked;
	unlinked = ii;
}

force_inline
void HashBase::Del(int ii)
{
	Hash& h = hash[ii];
	Bucket& m = map[h.hash & mask];
	int i = m.first;
	if(i == ii)
		m.first = h.next;
	else // need to find the item before ii
		while(i >= 0) {
			Hash& p = hash[i];
			if(p.next == ii) { // item before ii
				p.next = h.next; // point to item after ii
				if(m.last == ii) // if last item is ii
					m.last = i; // set it to item before ii
				break;
			}
			i = p.next;
		}
}

force_inline
void HashBase::Ins(int ii, dword sh)
{
	Hash& h = hash[ii];
	h.hash = sh;
	h.next = -1;
	Bucket& m = map[sh & mask];
	int i = m.first;
	if(i < 0) // first in bucket
		m.first = m.last = ii;
	else
	if(ii < i) { // before first
		h.next = i;
		m.first = ii;
	}
	else
	if(ii > m.last) { // after last
		hash[m.last].next = ii;
		m.last = ii;
	}
	else
		while(i >= 0) { // find the position
			Hash& p = hash[i];
			if(ii < p.next) {
				h.next = p.next;
				p.next = ii;
				break;
			}
			i = p.next;
		}
}

force_inline
int HashBase::PutUnlinked(dword h)
{
	int ii = unlinked;
	ASSERT(ii >= 0 && ii != NOUNLINKED);
	h = Smear(h);
	unlinked = hash[ii].hash;
	Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
	return ii;
}

force_inline
void HashBase::Link(int ii, dword sh)
{
	Bucket& m = map[sh & mask];
	if(m.first == -1)
		m.first = m.last = ii;
	else {
		hash[m.last].next = ii;
		m.last = ii;
	}
}


force_inline
void HashBase::AddS(dword sh)
{
	int ii = hash.GetCount();
	Hash& hh = hash.Add();
	hh.hash = sh;
	hh.next = -1;
	if(ii >= (int)mask)
		GrowMap();
	else
		Link(ii, sh);
}

force_inline
void HashBase::Add(dword h)
{
	AddS(Smear(h));
}

template <typename P>
force_inline
int HashBase::FindFrom(int i, dword sh, P pred) const
{
	while(i >= 0) {
		const Hash& ih = hash[i];
		if(sh == ih.hash && pred(i))
			break;
		i = ih.next;
	}
	return i;
}

template <typename P>
force_inline
int HashBase::Find(dword h, P pred) const
{
	if(!map) return -1;
	h = Smear(h);
	return FindFrom(map[h & mask].first, h, pred);
}

template <class T>
void Index<T>::SweepGrow()
{
	key.RemoveIf([&](int i) { return hash.IsUnlinked(i); });
	hash.SweepGrow();
}

template <class T>
void Index<T>::UnlinkKey(const T& k)
{
	int q = Find(k);
	while(q >= 0) {
		int qq = FindNext(q);
		Unlink(q);
		q = qq;
	}
}

};