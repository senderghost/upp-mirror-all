namespace New {

force_inline
void HashBase::Del(int ii)
{ // remove ii from its list
	Hash& h = hash[ii];
	if(h.hash == 0)
		return;
	Bucket& m = map[h.hash & mask];
	int i = m.first;
	ASSERT(i >= 0);
	if(i == ii) {
		if(m.first == m.last) // this is the only item in the bucket
			m.first = m.last = -1;
		else
			m.first = h.next;
	}
	else // need to find the item before ii
		while(i >= 0) {
			Hash& p = hash[i];
			if(p.next == ii) { // item before ii
				p.next = h.next; // point to item after ii
				if(ii == m.last) // ii is the last item
					m.last = i; // set it to item before ii
				break;
			}
			i = p.next;
		}
}

force_inline
void HashBase::Ins(int ii, dword sh)
{ // insert into bucket
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
		while(i >= 0) { // find the position in the the list
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
void HashBase::Set(int ii, dword h)
{
	Del(ii); // remove from original bucket list
	Ins(ii, Smear(h)); // put to new bucket list
}

force_inline
int HashBase::PutUnlinked(dword h)
{
	int ii = unlinked;
	ASSERT(ii >= 0 && IsUnlinked(ii));
	unlinked = hash[ii].next;
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
	h = Smear(h);
	return FindFrom(map[h & mask].first, h, pred);
}

template <class P>
force_inline
void HashBase::UnlinkKey(dword h, P pred)
{
	h = Smear(h);
	Bucket& m = map[h & mask];
	int i = m.first;
	int pi = i;
	while(i >= 0) {
		const Hash& ih = hash[i];
		int ni = ih.next;
		if(h == ih.hash && pred(i)) {
			if(i == m.first)
				m.first = ih.next;
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
}

force_inline
void HashBase::Unlink(int ii)
{
	Del(ii);
	hash[ii].hash = 0;
	hash[ii].next = unlinked;
	unlinked = ii;
}

/*
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
*/

};