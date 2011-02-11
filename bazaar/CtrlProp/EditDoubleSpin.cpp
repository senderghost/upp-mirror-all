#include "CtrlPropCommon.h"
#include <CtrlLib/CtrlLib.h>

bool PropSetInc(const Value& v, EditDoubleSpin& o) { if(!IsNumber(v)) return false; o.SetInc(v); return true; }
bool PropGetInc(Value& v, const EditDoubleSpin& o) { v = o.GetInc(); return true; }
bool PropSetShowSpin(const Value& v, EditDoubleSpin& o) { if(!IsNumber(v)) return false; o.ShowSpin(v); return true; }
bool PropGetShowSpin(Value& v, const EditDoubleSpin& o) { v = o.IsShowSpin(); return true; }

PROPERTIES(EditDoubleSpin, EditDouble)
PROPERTY("inc", PropSetInc, PropGetInc)
PROPERTY("showspin", PropSetShowSpin, PropGetShowSpin)
END_PROPERTIES

PROPS(Ctrl, EditDoubleSpin, EditDouble)
