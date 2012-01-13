#ifndef _SvoValue_SvoValue_h_
#define _SvoValue_SvoValue_h_

#include <Core/Core.h>

using namespace Upp;

void  DumpNumber(const Value& v);
Value Opt0();
void  Opt();
void CheckString();
void CheckDateTime();
void CheckValueMap();
void OtherChecks();

template <class T>
void CheckNumber()
{
	RLOG("---------------------------");
	RLOG("CheckNumber " << typeid(T).name());
	Value v = (T)123;
	Value v2 = (T)0;
	Value vn = (T)Null;
	Value dv = 123.0;
	ASSERT(IsNumber(v));
	ASSERT(!IsError(v));
	ASSERT(!IsVoid(v));
	ASSERT(!IsString(v));
	ASSERT(!IsDateTime(v));
	ASSERT(vn.Is<bool>() || GetHashValue(v) == GetHashValue(dv));
	ASSERT(v != v2);
	ASSERT(v != vn);
	ASSERT(IsNull(vn) || vn.Is<bool>());
	DumpNumber(v);
	DumpNumber(vn);
	Value v1 = v;
	RDUMP(v1);
	RDUMP(v2);
	RDUMP(v1 != v2);
	ASSERT(v1 != v2);
	v2 = v1;	
	RDUMP(v1);
	RDUMP(v2);
	RDUMP(v1 == v2);
	ASSERT(v1 == v2);
	Opt();
}

template <class T>
void CheckType(const T& x, bool checkhash = false)
{
	RLOG("---------------------------");
	RLOG("CheckType " << typeid(T).name() << " = " << x);
	String fn;
	Value vf;
	Value tt = x;
	bool isvoid = tt.IsVoid();
	if(!isvoid) {
		fn = ConfigFile(AsString(tt.GetType()) + ":" + AsString(x));
		if(FileExists(fn)) {
			LoadFromFile(vf, fn);
			RDUMP(vf.To<T>());
			ASSERT(vf.To<T>() == x);
		}
	}
	Value v = x;
	RDUMP(v);
	ASSERT(isvoid ? v.IsVoid() : v.Is<T>());
	if(!isvoid) {
		StoreToFile(v, fn);
		RDUMP(GetValueTypeNo<T>());
		ASSERT(v.GetType() == GetValueTypeNo<T>());
		if(!tt.Is<ValueArray>() && !tt.Is<ValueMap>())
			ASSERT(v.To<T>() == x);
		ASSERT((T)(v) == x);
	}
	if(!vf.IsVoid())
		ASSERT(vf == v);
	String h = StoreAsString(v);
	Value vv;
	LoadFromString(vv, h);
	RDUMP(vv);
	ASSERT(vv == v);
	T xx = vv;
	RDUMP(xx);
	ASSERT(vv == v);
	RDUMP(GetHashValue(v));
	RDUMP(GetHashValue(xx));
	ASSERT(!checkhash || GetHashValue(v) == GetHashValue(xx));
	
	Value vn = (T)Null;
	ASSERT(IsNull(vn) || vn.Is<bool>());
}

#endif
