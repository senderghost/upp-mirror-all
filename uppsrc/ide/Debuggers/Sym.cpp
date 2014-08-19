#include "Debuggers.h"

#ifdef COMPILER_MSC

#define LLOG(x)  // DLOG(x)

#ifdef _DEBUG
char * SymTagAsString( DWORD symTag )
{
	switch( symTag )
	{
#define SYMTAG(t) case SymTag##t: return #t;
		SYMTAG(Function)
		SYMTAG(Data)
		SYMTAG(PublicSymbol)
		SYMTAG(UDT)
		SYMTAG(Enum)
		SYMTAG(Typedef)
		SYMTAG(PointerType)
		SYMTAG(ArrayType)
		SYMTAG(BaseType)
		SYMTAG(VTableShape)
		SYMTAG(VTable)
#undef SYMTAG
		default: return "???";
	}
}

char * BaseTypeAsString( DWORD baseType )
{
	switch ( baseType )
	{
	case btNoType: return "btNoType";
	case btVoid: return "btVoid";
	case btChar: return "btChar";
	case btWChar: return "btWChar";
	case btInt: return "btInt";
	case btUInt: return "btUInt";
	case btFloat: return "btFloat";
	case btBCD: return "btBCD";
	case btBool: return "btBool";
	case btLong: return "btLong";
	case btULong: return "btULong";
	case btCurrency: return "btCurrency";
	case btDate: return "btDate";
	case btVariant: return "btVariant";
	case btComplex: return "btComplex";
	case btBit: return "btBit";
	case btBSTR: return "btBSTR";
	case btHresult: return "btHresult";
	default: return "???";
	}
}
#endif

adr_t Pdb::GetAddress(FilePos p)
{
	LONG dummy;
	IMAGEHLP_LINE ln;
	ln.SizeOfStruct = sizeof(ln);
	char h[MAX_PATH];
	strcpy(h, p.path);
	if(SymGetLineFromName(hProcess, NULL, h, p.line + 1, &dummy, &ln)) {
		LLOG("GetAddress " << p.path << "(" << p.line << "): " << Hex(ln.Address));
		return ln.Address;
	}
	LLOG("GetAddress " << p.path << "(" << p.line << "): ??");
	return NULL;
}

Pdb::FilePos Pdb::GetFilePos(adr_t address)
{
	FilePos fp;
	DWORD dummy;
	IMAGEHLP_LINE ln;
	ln.SizeOfStruct = sizeof(ln);
	fp.address = address;
	if(SymGetLineFromAddr(hProcess, (uintptr_t)address, &dummy, &ln) && FileExists(ln.FileName)) {
		fp.line = ln.LineNumber - 1;
		fp.path = ln.FileName;
		fp.address = ln.Address;
	}
	LLOG("GetFilePos(" << Hex(address) << "): " << fp.path << ": " << fp.line);
	return fp;
}

#define MAX_SYM_NAME 1024

Pdb::FnInfo Pdb::GetFnInfo(adr_t address)
{
	DWORD64 h;

	ULONG64 buffer[(sizeof(SYMBOL_INFO) + MAX_SYM_NAME + sizeof(ULONG64) - 1) / sizeof(ULONG64)];
	SYMBOL_INFO *f = (SYMBOL_INFO*)buffer;

	f->SizeOfStruct = sizeof(SYMBOL_INFO);
	f->MaxNameLen = MAX_SYM_NAME;

	FnInfo fn;
	if(SymFromAddr(hProcess, address, &h, f)) {
		LLOG("GetFnInfo " << f->Name
		     << ", type index: " << f->TypeIndex
		     << ", Flags: " << FormatIntHex(f->Flags)
		     << ", Address: " << Hex((dword)f->Address)
		     << ", Size: " << FormatIntHex((dword)f->Size)
		     << ", Tag: " << SymTagAsString(f->Tag));
		fn.name = f->Name;
		fn.address = (adr_t)f->Address;
		fn.size = f->Size;
		fn.pdbtype = f->TypeIndex;
	}
	return fn;
}

void Pdb::TypeVal(Pdb::Val& v, int typeId, adr_t modbase)
{
	adr_t tag;
	for(;;) {
		tag = GetSymInfo(modbase, typeId, TI_GET_SYMTAG);
		if(tag == SymTagPointerType) {
			v.ref++;
			const Type& tptr = GetTypeId(modbase, typeId); // What is this?
		}
		else
		if(tag == SymTagArrayType)
			v.array = true;
		else
			break;
		typeId = GetSymInfo(modbase, typeId, TI_GET_TYPE);
	}
	v.type = UNKNOWN;
	if(tag == SymTagUDT)
		v.type = GetTypeIndex(modbase, typeId);
	else {
		ULONG64 sz = 0;
		SymGetTypeInfo(hProcess, modbase, typeId, TI_GET_LENGTH, &sz);
		dword size = (dword)sz;
		if(tag == SymTagEnum)
			v.type = size == 8 ? SINT8 : size == 4 ? SINT4 : size == 2 ? SINT2 : SINT1;
		else {
			switch(GetSymInfo(modbase, typeId, TI_GET_BASETYPE)) {
			case btBool:
				v.type = BOOL1;
				break;
			case btChar:
			case btWChar:
			case btInt:
			case btLong:
				v.type = size == 8 ? SINT8 : size == 4 ? SINT4 : size == 2 ? SINT2 : SINT1;
				break;
			case btUInt:
			case btULong:
				v.type = size == 8 ? UINT8 : size == 4 ? UINT4 : size == 2 ? UINT2 : UINT1;
				break;
			case btFloat:
				v.type = size == 8 ? DBL : FLT;
				break;
			}
		}
	}
}

struct Pdb::LocalsCtx {
	adr_t                       frame;
	VectorMap<String, Pdb::Val> param;
	VectorMap<String, Pdb::Val> local;
	Pdb                        *pdb;
	Context                    *context;
};

BOOL CALLBACK Pdb::EnumLocals(PSYMBOL_INFO pSym, ULONG SymbolSize, PVOID UserContext)
{
	LocalsCtx& c = *(LocalsCtx *)UserContext;

	if(pSym->Tag == SymTagFunction)
		return TRUE;

	Val& v = (pSym->Flags & IMAGEHLP_SYMBOL_INFO_PARAMETER ? c.param : c.local).GetAdd(pSym->Name);
	v.address = (adr_t)pSym->Address;
	if(pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGRELATIVE) {
		if(pSym->Register == CV_ALLREG_VFRAME) {
		#ifdef CPU_64
			if(c.pdb->win64)
				v.address += c.pdb->GetCpuRegister(*c.context, CV_AMD64_RBP);
			else
		#endif
				v.address += (adr_t)c.pdb->GetCpuRegister(*c.context, CV_REG_EBP);
		}
		else
			v.address += (adr_t)c.pdb->GetCpuRegister(*c.context, pSym->Register);
	}
	if(pSym->Flags & IMAGEHLP_SYMBOL_INFO_FRAMERELATIVE)
		v.address += c.frame;
	if(pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGISTER)
		v.address = pSym->Register;
	c.pdb->TypeVal(v, pSym->TypeIndex, (adr_t)pSym->ModBase);
	LLOG("LOCAL " << pSym->Name << ": " << Format64Hex(v.address));
	return TRUE;
}

void Pdb::GetLocals(Frame& frame, Context& context, VectorMap<String, Pdb::Val>& param,
                    VectorMap<String, Pdb::Val>& local)
{
	static IMAGEHLP_STACK_FRAME f;
	f.InstructionOffset = frame.pc;
	SymSetContext(hProcess, &f, 0);
	LocalsCtx c;
	c.frame = frame.frame;
	c.pdb = this;
	c.context = &context;
	SymEnumSymbols(hProcess, 0, 0, &EnumLocals, &c);
	param = c.param;
	local = c.local;
}

BOOL CALLBACK Pdb::EnumGlobals(PSYMBOL_INFO pSym, ULONG SymbolSize, PVOID UserContext)
{
	LocalsCtx& c = *(LocalsCtx *)UserContext;

	if(pSym->Tag != SymTagData)
		return TRUE;
	LLOG("GLOBAL: " << pSym->Name << " " << Format64Hex(pSym->Address));

#if 0
	DDUMP(pSym->Scope);
	DDUMP(pSym->Flags);
	DDUMP(pSym->Tag);
	DDUMP(pSym->TypeIndex);

	DWORD dummy;
	IMAGEHLP_LINE ln;
	ln.SizeOfStruct = sizeof(ln);
	ln.Address = pSym->Address;
	if(SymGetLineFromAddr(c.pdb->hProcess, (uintptr_t)pSym->Address, &dummy, &ln)) {
		DDUMP(ln.FileName);
		DDUMP(ln.Address);
		DDUMP(ln.LineNumber);
	}
	else
		DLOG("GetSymLineFromAddr failed!");
	DLOG("=========================");
#endif

	Val& v = c.pdb->global.GetAdd(pSym->Name);
	v.address = (adr_t)pSym->Address;
	c.pdb->TypeVal(v, pSym->TypeIndex, (adr_t)pSym->ModBase);
	return TRUE;
}

void Pdb::LoadGlobals(DWORD64 base)
{
	static IMAGEHLP_STACK_FRAME f;
	LocalsCtx c;
	c.pdb = this;
	c.context = &context;
	SymEnumSymbols(hProcess, base, NULL, &EnumGlobals, &c);
}

Pdb::Val Pdb::GetGlobal(const String& name)
{
	return global.Get(name, Val());
}

String Pdb::GetSymName(adr_t modbase, dword typeindex)
{
    WCHAR *pwszTypeName;
    if(SymGetTypeInfo(hProcess, modbase, typeindex, TI_GET_SYMNAME, &pwszTypeName)) {
		WString w((const wchar *)pwszTypeName);
		LocalFree(pwszTypeName);
		return w.ToString();
    }
    return Null;
}

dword Pdb::GetSymInfo(adr_t modbase, dword typeindex, IMAGEHLP_SYMBOL_TYPE_INFO info)
{
	dword dw = 0;
	SymGetTypeInfo(hProcess, modbase, typeindex, info, &dw);
	return dw;
}

int Pdb::GetTypeIndex(adr_t modbase, dword typeindex)
{
	int q = type.Find(typeindex);
	if(q < 0) {
		q = type.GetCount();
		type.Add(typeindex).modbase = modbase;
	}
	return q;
}

const Pdb::Type& Pdb::GetType(int ti)
{
	Type& t = type[ti];
	int typeindex = type.GetKey(ti);
	if(t.size < 0) {
		t.name = GetSymName(t.modbase, typeindex);
		ULONG64 sz = 0;
		SymGetTypeInfo(hProcess, t.modbase, typeindex, TI_GET_LENGTH, &sz);
		t.size = (dword)sz;
		dword count = GetSymInfo(t.modbase, typeindex, TI_GET_CHILDRENCOUNT);
		if(count) {
			Buffer<byte> b(sizeof(TI_FINDCHILDREN_PARAMS) + sizeof(ULONG) * count);
			TI_FINDCHILDREN_PARAMS *children = (TI_FINDCHILDREN_PARAMS *) ~b;
			children->Count = count;
			children->Start = 0;
			if(SymGetTypeInfo(hProcess, t.modbase, typeindex, TI_FINDCHILDREN, children)) {
				for(dword i = 0; i < count; i++) {
					dword ch = children->ChildId[i];
					dword tag = GetSymInfo(t.modbase, ch, TI_GET_SYMTAG);
					dword kind = GetSymInfo(t.modbase, ch, TI_GET_DATAKIND);
					if(tag == SymTagData) {
						String name = GetSymName(t.modbase, ch);
						if(kind == DataIsMember) {
							Val& v = t.member.Add(name);
							TypeVal(v, GetSymInfo(t.modbase, ch, TI_GET_TYPEID), t.modbase);
							v.address = GetSymInfo(t.modbase, ch, TI_GET_OFFSET);
							ULONG64 bitcnt = 0;
							SymGetTypeInfo(hProcess, t.modbase, ch, TI_GET_LENGTH, &bitcnt);
							if(bitcnt) {
								v.bitcnt = (byte)bitcnt;
								v.bitpos = (byte)GetSymInfo(t.modbase, ch, TI_GET_BITPOSITION);
							}
						}
						if(kind == DataIsStaticMember || kind == DataIsGlobal) {
							Val& v = t.static_member.Add(name);
							TypeVal(v, GetSymInfo(t.modbase, ch, TI_GET_TYPEID), t.modbase);
							ULONG64 adr = 0;
							SymGetTypeInfo(hProcess, t.modbase, ch, TI_GET_ADDRESS, &adr);
							v.address = (adr_t)adr;
						}
					}
					else
					if(tag == SymTagBaseClass) {
						Val& v = t.base.Add();
						TypeVal(v, GetSymInfo(t.modbase, ch, TI_GET_TYPEID), t.modbase);
						v.address = GetSymInfo(t.modbase, ch, TI_GET_OFFSET);
					}
					else
					if(tag == SymTagVTable) {
						t.vtbl_offset = GetSymInfo(t.modbase, ch, TI_GET_OFFSET);
						dword typeId = GetSymInfo(t.modbase, ch, TI_GET_TYPEID);
						while(GetSymInfo(t.modbase, typeId, TI_GET_SYMTAG) == SymTagPointerType)
							typeId = GetSymInfo(t.modbase, typeId, TI_GET_TYPE);
						if((t.vtbl_typeindex = type.Find(typeId)) < 0) {
							t.vtbl_typeindex = type.GetCount();
							Type& vt = type.Add(typeId);
							vt.modbase = t.modbase;
							vt.size = 0;
							vt.vtbl_typeindex = -2;
						}
					}
	            }
		    }
		}
	}
	return t;
}

#ifdef _DEBUG

String Pdb::TypeAsString(int ti, bool deep)
{
	String r;
	#define sTYPE(x)     case x: return #x;
	switch(ti) {
	sTYPE(BOOL1)
	sTYPE(UINT1)
	sTYPE(SINT1)
	sTYPE(UINT2)
	sTYPE(SINT2)
	sTYPE(UINT4)
	sTYPE(SINT4)
	sTYPE(UINT8)
	sTYPE(SINT8)
	sTYPE(FLT)
	sTYPE(DBL)
	sTYPE(UNKNOWN)
	}
	if(ti < 0)
		return r;
	const Type& t = GetType(ti);
	r << t.name << "(sizeof = " << t.size << ") ";
	if(!deep)
		return r;
	if(t.member.GetCount()) {
		r << "{ ";
		for(int i = 0; i < t.member.GetCount(); i++) {
			if(i)
				r << ", ";
			r << t.member.GetKey(i) << " +" << t.member[i].address;
			if(t.member[i].ref)
				r << TypeAsString(t.member[i].type, false) << String('*', t.member[i].ref);
			else
				r << ": " << TypeAsString(t.member[i].type);
		}
		r << " }";
	}
	if(t.base.GetCount()) {
		r << " BASE: ";
		for(int i = 0; i < t.base.GetCount(); i++) {
			if(i)
				r << ", ";
			r << " +" << t.base[i].address;
			r << TypeAsString(t.base[i].type);
		}
	}
	return r;
}

#endif

#endif
