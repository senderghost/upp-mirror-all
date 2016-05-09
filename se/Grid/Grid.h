template <class T>
struct GridRef {
	DataArray<T> *data;
	int          *dim;
	int           offset;
	GridRef       operator[](int i)     { GridRef<T> r = *this; r.offset += *dim++ * i; return r; }
	T             operator=(const T& x) { data->Set(offset, x); return x; }
	operator T() const                  { return data->Get(offset); }
};

template <class T>
struct Grid {
	DataArray<T> data;
	int          dim[5];

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
