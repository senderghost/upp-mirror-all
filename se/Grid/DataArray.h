struct StringStreamVals : StringStream {
	Vector<Value> va;
	int           ii;
	
	void  PutValue(const Value& v)                      { va.Add(v); }
	Value GetValue()                                    { return va[ii++]; }
	
	StringStreamVals()                                  { ii = 0; }
	StringStreamVals(const String& s) : StringStream(s) { ii = 0; }
};

template <class T>
class DataArray : public ValueType<DataArray<T>, 3150, Moveable_<DataArray<T>>> {
	struct Rc {
		Atomic refcount;
		int64  count;
	};
	
	Rc *Ref() const                    { return (Rc *)data - 1; }
	
	T *data;
	
	void Copy(const DataArray& b);
	void Release();
	void Clone();
	void Unshare();
	void CheckWriting()                { ASSERT(data->refcount == 0); }

public:
	void Create(int64 count);

	T   *BeginWrite();
	void EndWrite()                    { ASSERT(Ref()->refcount == 0); Ref()->refcount = 1; }
	
	const T& operator[](int i) const   { ASSERT(i < GetCount()); return data[i]; }
	const T& Get(int i) const          { ASSERT(i < GetCount()); return data[i]; }
	void  Set(int i, const T& v)       { ASSERT(i < GetCount()); Unshare(); data[i] = v; }
	int64 GetCount() const             { return data ? Ref()->count : 0; }

	DataArray& operator=(const DataArray& b) { if(this != &b) { Release(); Copy(b); } return *this; }
	
	String ToString() const            { String h; for(int i = 0; i < GetCount(); i++) { if(i) h << ", "; h << data[i]; }; return h; }
	
	void Serialize(Stream& s);

	operator Value() const             { return RichValue<DataArray>(*this); }
	DataArray(const Value& q)          { Copy(q.Get<DataArray>()); }
	
	DataArray(const Nuller&)           { DataArray(); }
	
	DataArray();
	DataArray(const DataArray& b)      { Copy(b); }
	~DataArray()                       { Release(); }
};

template <class T>
DataArray<T>::DataArray()
{
	static Rc h;
	h.refcount = INT_MAX / 2;
	data = (T *)(&h + 1);
}

template <class T>
void DataArray<T>::Serialize(Stream& s)
{
	if(auto vs = dynamic_cast<StringStreamVals *>(&s))
		if(vs->IsLoading())
			*this = DataArray(vs->GetValue());
		else
			vs->PutValue(*this);
	else {
		int64 count = GetCount();
		s % count;
		if(s.IsLoading())
			Create(count);
		for(int i = 0; i < count; i++)
			s % data[i];
	}
}

template <class T>
void DataArray<T>::Copy(const DataArray& b)
{
	data = b.data;
	ASSERT(Ref()->refcount > 0);
	AtomicInc(Ref()->refcount);
}

template <class T>
void DataArray<T>::Create(int64 count)
{
	DDUMP(count);
	Release();
	Rc *rc = (Rc *)(new byte[sizeof(Rc) + sizeof(T) * (size_t)count]);
	rc->refcount = 1;
	rc->count = count;
	data = (T *)(rc + 1);
}

template <class T>
void DataArray<T>::Release()
{
	ASSERT(Ref()->refcount > 0);
	if(data) {
		Rc *rc = Ref();
		ASSERT(rc->refcount > 0);
		if(AtomicDec(rc->refcount) == 0)
			delete[] (byte *)rc;
		data = NULL;
	}
}

template <class T>
void DataArray<T>::Clone()
{
	int64 count = GetCount();
	T *s = data;
	Create(count);
	T *t = data;
	T *e = data + count;
	while(t < e)
		*t++ = *s++;
}

template <class T>
void DataArray<T>::Unshare()
{
	if(Ref()->refcount != 1)
		Clone();
}

template <class T>
T *DataArray<T>::BeginWrite()
{
	Unshare();
	Ref()->refcount = 0;
	return data;
}
