#include "Tutorial.h"

void Range()
{
	/// .Range
	
	/// Unlike STL, which interface algorithms with data using `begin` / `end` pair, U++ algorithms
	/// usually work on %Ranges%. Range is an object that has `begin` / `end` methods providing
	/// random access to elements (all U++ containers are random access), `operator[]` and
	/// `GetCount` method.
	
	/// Obviously, U++ containers are ranges:
	
	Vector<int> x = { 1, 2, 3, 4, 5, 1, 2, 3, 4 };
	
	DUMP(FindIndex(x, 2)); // FindIndex is a trivial algorithm that does linear search
	
	/// If you want the algorithm to run on part of container only, you can use `SubRange`
	/// instance:
	
	DUMP(SubRange(x, 3, 6));
	DUMP(FindIndex(SubRange(x, 3, 6), 4));

	///

	DUMP(typeid(ValueTypeOf<decltype(x)>).name());
	DUMP(typeid(ValueTypeOf<decltype(SubRange(x, 1, 1))>).name());
	DUMP(typeid(IteratorOf<decltype(x)>).name());
	DUMP(typeid(ConstIteratorOf<decltype(SubRange(x, 1, 1))>).name());
	
	/// While containers themselves and SubRange are the two most common range types, U++ has two
	/// special ranges. `ConstRange` simply provides the range of single value:
	
	DUMP(ConstRange(1, 10));
	
	/// `ViewRange` picks a source range and `Vector` of integer indices a provides a view of
	/// source range through this `Vector`:
	
	Vector<int> h{ 2, 4, 0 };
	
	DUMP(ViewRange(x, clone(h)));

	///
	
	Sort(ViewRange(x, clone(h)));
	DUMP(ViewRange(x, clone(h)));
	DUMP(x);
	
	/// Finally `FilterRange` creates a subrange of elements satisfying certain condition:
	
	DUMP(FilterRange(x, [](int x) { return x > 3; }));
	
	///
}
