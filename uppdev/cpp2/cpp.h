#ifndef _cpp_cpp_h_
#define _cpp_cpp_h_

#include <Core/Core.h>

#include <CppBase/CppBase.h>

using namespace Upp;

void RemoveComments(String& l, bool& incomment);

struct CppMacro : Moveable<CppMacro>, DeepCopyOption<CppMacro> {
	String        body;
	Index<String> param;
	bool          variadic;
	
	String Define(const char *s);

	String Expand(const Vector<String>& p) const;
	
	String ToString() const;
	
	CppMacro()    { variadic = false; }
	rval_default(CppMacro);
	CppMacro(const CppMacro& s, int) { body = s.body, param = clone(s.param); variadic = s.variadic; }
};

enum PPItemType {
	PP_DEFINE,
	PP_INCLUDE,
	PP_USING,
	PP_NAMESPACE,
	PP_NAMESPACE_END
};

struct PPItem {
	int      type;
	String   id;
	CppMacro macro;
};

struct PPFile { // contains "macro extract" of file, only info about macros defined and namespaces
	FileTime       filetime;
	Array<PPItem>  item;
	Index<String>  includes;
	
	void Parse(Stream& in);
	
	void Dump() const;

private:
	void CheckEndNamespace(Vector<int>& namespace_block, int level);
};

const PPFile& GetPPFile(const char *path);

String GetIncludePath(const String& s, const String& filedir, const String& include_path);

bool   IncludesFile(const String& parent_path, const String& header_path, const String& include_path);

struct Cpp {
	bool                        incomment;
	bool                        done;
	
	String                      include_path;
	
	VectorMap<String, CppMacro> macro;

	String                      output;
	Index<String>               usedmacro;
	Index<String>               namespace_using;
	Vector<String>              namespace_stack;
	
	void   Define(const char *s);

	static const char *SkipString(const char *s);
	void   ParamAdd(Vector<String>& param, const char *b, const char *e);
	String Expand(const char *s, Index<String>& notmacro);
	String Expand(const char *s);
	void   Do(const String& sourcefile, Stream& in, const String& currentfile, Index<String>& visited);

	bool   Preprocess(const String& sourcefile, Stream& in, const String& currentfile);
	
	typedef Cpp CLASSNAME;
};

#endif
