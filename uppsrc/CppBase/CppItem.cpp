#include "CppBase.h"

NAMESPACE_UPP

void CppItem::Dump(Stream& s) const
{
	s << Nvl(qitem, "?") << ' ';
	s << decode(kind,
				STRUCT, "STRUCT",
				STRUCTTEMPLATE, "STRUCTTEMPLATE",
				TYPEDEF, "TYPEDEF",
				CONSTRUCTOR, "CONSTRUCTOR",
				DESTRUCTOR, "DESTRUCTOR",
				FUNCTION, "FUNCTION",
				INSTANCEFUNCTION, "INSTANCEFUNCTION",
				CLASSFUNCTION, "CLASSFUNCTION",
				FUNCTIONTEMPLATE, "FUNCTIONTEMPLATE",
				INSTANCEFUNCTIONTEMPLATE, "INSTANCEFUNCTIONTEMPLATE",
				CLASSFUNCTIONTEMPLATE, "CLASSFUNCTIONTEMPLATE",
				INLINEFRIEND, "INLINEFRIEND",
				VARIABLE, "VARIABLE",
				INSTANCEVARIABLE, "INSTANCEVARIABLE",
				CLASSVARIABLE, "CLASSVARIABLE",
				ENUM, "ENUM",
				MACRO, "MACRO",
				FRIENDCLASS, "FRIENDCLASS",
				"?kind:" + AsString(kind)) << ' '
	  << decode(access,
				PUBLIC, "PUBLIC",
				PROTECTED, "PROTECTED",
				PRIVATE, "PRIVATE",
				"?access:" + AsString(access)) << ' '
	  << decode(filetype,
				FILE_H, "FILE_H",
				FILE_HPP, "FILE_HPP",
				FILE_CPP, "FILE_CPP",
				FILE_C, "FILE_C",
				FILE_OTHER, "FILE_OTHER",
				"?filetype:" + AsString(filetype))
	;
#define PUT(x) if(x) s << ' ' << #x;
	PUT(virt);
	PUT(decla);
	PUT(lvalue);
	PUT(isptr);
	PUT(impl);
	PUT(qualify_type);
	PUT(qualify_param);
#undef PUT
	s << ' ' << line << '\n';
#define PUT(x) if(x.GetCount()) s << "      " << #x << ": " << x << '\n';
	PUT(item);
	PUT(name);
	PUT(uname);
	PUT(natural);
	PUT(type);
	PUT(qtype);
	PUT(tparam);
	PUT(param);
	PUT(pname);
	PUT(ptype);
	PUT(qptype);
	PUT(tname);
	PUT(ctname);
#undef PUT
}

END_UPP_NAMESPACE
