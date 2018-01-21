template <class T, class FN>
void Benchmark(const T& data, FN fn, const char *name) {
	Vector<double> d = clone(data);
	int t = msecs();
	for(auto& h : d)
		h = fn(h);
	RLOG(name << " " << 1e6 * msecs(t) / data.GetCount() << " ns");
}
