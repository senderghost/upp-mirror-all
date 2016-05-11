template <class T>
struct GridRef {
	DataArray<T> *data;
	size_t       *dim;
	int           offset;
	GridRef       operator[](int i)     { GridRef<T> r = *this; r.offset += *++dim++ * i; return r; }
	T             operator=(const T& x) { data->Set(offset, x); return x; }
	operator T() const                  { return data->Get(offset); }
};

template <int D, typename T>
class Slice;

template <0, class T>
class Slice {
	DataArray<T> *data;
	T            *ptr;

public:
	T             operator=(const T& x) { data->Unshare(); *ptr = x; return x; }
	operator T() const                  { return *ptr; }
};

cu * (cz * (x * cy + y) + z) + u

cu * cz * cy * x + cu * cy * y + cu * z + u



template <int D, class T>
struct Slice {
	DataArray<T> *data;
	T            *ptr;
	size_t       *dim;

public:
	Slice<T>      operator[](int i) const { Slice<D - 1, podT> s; s.data = data; s.ptr = ptr; s.dim = dim + 1; ptr += *dim * i; return s; }
};

template <class T>
struct Grid {
	DataArray<T> data;
	size_t       dim[N];

public:
	GridRef<T> operator[](int i)        { GridRef<T> r; r.offset = i; r.dim = dim; r.data = &data; return r; }
	
	void Create(int cx, int cy = 1, int cz = 1, int cu = 1, int cv = 1) {
		dim[0] = cx;
		dim[1] = cy;
		dim[2] = cz;
		dim[3] = cu;
		dim[4] = cv;
		
		data.Create((int64)cx * cy * cz * cu * cv);
	}
};
