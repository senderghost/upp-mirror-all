#include <Core/Core.h>

using namespace Upp;

struct TinyPtrVectorImp {
	uintptr_t          data;
	
	bool               IsVector() const           { return data & 7 == 7; }
	uintptr_t         *Ptr() const                { return (uintptr_t *) (data & ~7); }
	Vector<uintptr_t> *GetVector() const          { ASSERT(IsVector()); return (Vector<uintptr_t>*) Ptr(); }
	void               Free()                     

public:
	TinyPtrVectorImp()         { 
	int GetCount() const       { int l = data & 7; return l == 7 ? GetVector()->GetCount() : l; }
	intptr_t Get(int i) const  { ASSERT(i < GetCount()); if(data & 7 == 7) return (*Vec())[i] : Ptr()[i]; }
	void Add(uintptr_t p);
};

void TinyPtrVectorImp::Add(uintptr_t p)
{
	ASSERT(p & 7 == 0);
	if(IsVector()) {
		GetVector()->Add(p);
		return;
	}
	int l = data & 7; if(
}

CONSOLE_APP_MAIN
{
}
