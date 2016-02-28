#define FOLDHASH

enum { UNSIGNED_HIBIT = 0x80000000 };

class HashBase : Moveable<HashBase> {
	struct Link : Moveable<Link> {
		int   next;
		int   prev;
	};
	Vector<unsigned> hash;
	Vector<Link>     link;
	int             *map;
	int              mask;
	int              unlinked;

	void  LinkBefore(int i, Link& l, int bi);
	void  LinkTo(int i, Link& l, int& m);
	void  Unlink(int i, Link& l, int& mi);
	void  Unlink(int i, Link& l);
	int&  Maph(unsigned _hash) const;
	int&  Mapi(int i) const;
	void  FinishIndex();
	void  Zero();
	void  Free();

public:
	void  ClearIndex();
	void  Reindex(int n);
	void  Reindex();

	void  Add(unsigned hash);
	void  Set(int i, unsigned hash);
	void  SetUn(int i, unsigned hash);
	unsigned operator [] (int i) const      { return hash[i]; }
	int   Find(unsigned hash) const;
	int   GetNext(int i) const              { return link[i].next; }
	int   FindNext(int i, int first) const;
	int   FindNext(int i) const;
	int   FindLast(unsigned hash) const;
	int   FindPrev(int i) const;
	int   Put(unsigned hash);

	bool  IsUnlinked(int i) const           { return hash[i] & UNSIGNED_HIBIT; }
	void  Unlink(int i);
	Vector<int> GetUnlinked() const;
	bool  HasUnlinked() const				{ return unlinked >= 0; }

	void  Remove(int i);
	void  Remove(int i, int count);
	void  Remove(const int *sorted_list, int count);
	void  Insert(int i, unsigned hash);

	int   GetCount() const                  { return hash.GetCount(); }
	void  Trim(int count);
	void  Drop(int n);
	void  Clear()                           { hash.Clear(); ClearIndex(); }

	void  Reserve(int n);
	void  Shrink();

#ifdef UPP
	void  Serialize(Stream& s);
#endif

	HashBase();
	~HashBase();

	HashBase(HashBase&& b);
	void operator=(HashBase&& b);
	HashBase(const HashBase& b, int);
	void operator<<=(const HashBase& b);

	const unsigned *Begin() const           { return hash.Begin(); }
	const unsigned *End() const             { return hash.End(); }

	void Swap(HashBase& b);
};

template <class T, class V>
class AIndex {
protected:
	V         key;
	HashBase  hash;

	int      Find0(const T& x, int i) const {
		while(i >= 0 && !(x == key[i])) i = hash.FindNext(i);
		return i;
	}
	int      FindB(const T& x, int i) const {
		while(i >= 0 && !(x == key[i])) i = hash.FindPrev(i);
		return i;
	}
	void     Hash();

public:
	unsigned hashfn(const T& x) const             { return GetHashValue(x); }

	T&       Add(const T& x, unsigned _hash);
	T&       Add(const T& x);
	int      FindAdd(const T& key, unsigned _hash);
	int      FindAdd(const T& key);
	AIndex&  operator<<(const T& x)          { Add(x); return *this; }

	int      Put(const T& x, unsigned _hash);
	int      Put(const T& x);
	int      FindPut(const T& key, unsigned _hash);
	int      FindPut(const T& key);

	int      Find(const T& x, unsigned _hash) const;
	int      Find(const T& x) const;
	int      FindNext(int i) const;
	int      FindLast(const T& x, unsigned _hash) const;
	int      FindLast(const T& x) const;
	int      FindPrev(int i) const;

	T&       Set(int i, const T& x, unsigned _hash);
	T&       Set(int i, const T& x);

	const T& operator[](int i) const         { return key[i]; }
	int      GetCount() const                { return key.GetCount(); }
	bool     IsEmpty() const                 { return key.IsEmpty(); }
	
	unsigned GetHash(int i) const            { return hash[i]; }

	void     Clear()                         { hash.Clear(); key.Clear(); }

	void     ClearIndex()                    { hash.ClearIndex(); }
	void     Reindex(int n)                  { hash.Reindex(n); }
	void     Reindex()                       { hash.Reindex(); }

	void     Unlink(int i)                   { hash.Unlink(i); }
	int      UnlinkKey(const T& k, unsigned h);
	int      UnlinkKey(const T& k);
	bool     IsUnlinked(int i) const         { return hash.IsUnlinked(i); }
	Vector<int> GetUnlinked() const          { return hash.GetUnlinked(); }
	void     Sweep();
	bool     HasUnlinked() const             { return hash.HasUnlinked(); }

	T&       Insert(int i, const T& k, unsigned h);
	T&       Insert(int i, const T& k);
	void     Remove(int i);
	void     Remove(int i, int count);
	void     Remove(const int *sorted_list, int count);
	void     Remove(const Vector<int>& sorted_list);
	int      RemoveKey(const T& k, unsigned h);
	int      RemoveKey(const T& k);

	void     Trim(int n)                     { key.SetCount(n); hash.Trim(n); }
	void     Drop(int n = 1)                 { key.Drop(n); hash.Drop(n); }
	const T& Top() const                     { return key.Top(); }

	void     Reserve(int n)                  { key.Reserve(n); hash.Reserve(n); }
	void     Shrink()                        { key.Shrink(); hash.Shrink(); }
	int      GetAlloc() const                { return key.GetAlloc(); }

	void     Serialize(Stream& s);
	void     Xmlize(XmlIO& xio, const char *itemtag = "key");
	void     Jsonize(JsonIO& jio);
	String   ToString() const;
	template <class B> bool operator==(const B& b) const { return IsEqualArray(*this, b); }
	template <class B> bool operator!=(const B& b) const { return !operator==(b); }
	template <class B> int  Compare(const B& b) const    { return CompareArray(*this, b); }
	template <class B> bool operator<=(const B& x) const { return Compare(x) <= 0; }
	template <class B> bool operator>=(const B& x) const { return Compare(x) >= 0; }
	template <class B> bool operator<(const B& x) const  { return Compare(x) < 0; }
	template <class B> bool operator>(const B& x) const  { return Compare(x) > 0; }

	V        PickKeys() pick_                  { return pick(key); }
	const V& GetKeys() const                   { return key; }

// Pick assignment & copy. Picked source can only Clear(), ~AIndex(), operator=, operator<<=

	AIndex& operator=(V&& s);

	typedef decltype(((const V *)&key)->begin()) ConstIterator;

// Standard container interface
	ConstIterator begin() const                           { return key.Begin(); }
	ConstIterator end() const                             { return key.End(); }

	void Swap(AIndex& b)                                  { UPP::Swap(hash, b.hash);
	                                                        UPP::Swap(key, b.key); }

#ifdef DEPRECATED
	AIndex& operator<<=(const V& s);
	typedef T                ValueType;
	typedef V                ValueContainer;
	ConstIterator  GetIter(int pos) const                 { return key.GetIter(pos); }
#endif

protected:
	AIndex(V&& s);
	AIndex(const V& s, int);
	AIndex() {}
	AIndex(const AIndex& s, int);
	AIndex(std::initializer_list<T> init);
};

template <class T>
class Index : MoveableAndDeepCopyOption< Index<T> >,
              public AIndex<T, Vector<T>> {
	typedef AIndex<T, Vector<T>> B;
public:
	T        Pop()                           { T x = B::Top(); B::Drop(); return x; }

	Index() {}
	Index(Index&& s) : B(pick(s))        {}
	Index(const Index& s, int) : B(s, 1)     {}
	explicit Index(Vector<T>&& s) : B(pick(s)) {}
	Index(const Vector<T>& s, int) : B(s, 1) {}

	Index& operator=(Vector<T>&& x)          { B::operator=(pick(x)); return *this; }
	Index& operator=(Index<T>&& x)           { B::operator=(pick(x)); return *this; }

	friend void Swap(Index& a, Index& b)     { a.B::Swap(b); }

	typedef typename B::ConstIterator ConstIterator; // GCC bug (?)
	STL_INDEX_COMPATIBILITY(Index<T _cm_ HashFn>)

	Index(std::initializer_list<T> init) : B(init) {}
};

/*
template <class T, class HashFn = StdHash<T> >
class ArrayIndex : MoveableAndDeepCopyOption< ArrayIndex<T, HashFn > >,
                   public AIndex<T, Array<T>> {
	typedef AIndex< T, Array<T>, HashFn > B;
public:
	T&       Add(const T& x, unsigned _hash)        { return B::Add(x, _hash); }
	T&       Add(const T& x)                        { return B::Add(x); }
	T&       Set(int i, const T& x, unsigned _hash) { return B::Set(i, x, _hash); }
	T&       Set(int i, const T& x)                 { return B::Set(i, x); }

	T&       Add(T *newt, unsigned _hash);
	T&       Add(T *newt);
	T&       Set(int i, T *newt, unsigned _hash);
	T&       Set(int i, T *newt);

	T       *PopDetach()                            { B::hash.Drop(1); return B::key.PopDetach(); }
	T       *Detach(int i)                          { B::hash.Remove(i); return B::key.Detach(i); }

	ArrayIndex() {}
	ArrayIndex(ArrayIndex&& s) : B(pick(s))              {}
	ArrayIndex(const ArrayIndex& s, int) : B(s, 1)       {}
	explicit ArrayIndex(Array<T>&& s) : B(pick(s))       {}
	ArrayIndex(const Array<T>& s, int) : B(s, 1)         {}

	ArrayIndex& operator=(Array<T>&& x)                  { B::operator=(pick(x)); return *this; }
	ArrayIndex& operator=(ArrayIndex<T>&& x)             { B::operator=(pick(x)); return *this; }

	friend void Swap(ArrayIndex& a, ArrayIndex& b)       { a.B::Swap(b); }

	typedef typename B::ConstIterator ConstIterator; // GCC bug (?)
	STL_INDEX_COMPATIBILITY(ArrayIndex<T _cm_ HashFn>)

	ArrayIndex(std::initializer_list<T> init) : B(init) {}
};
*/