#include "CtrlPropCommon.h"
#include <CtrlLib/CtrlLib.h>

bool PropSetLabel(const Value& v, ButtonOption& o) { if(!IsString(v)) return false; o.SetLabel(v); return true; }
bool PropGetLabel(Value& v, const ButtonOption& o) { v = o.GetLabel(); return true; }

PROPERTIES(ButtonOption, Ctrl)
PROPERTY("label", PropSetLabel, PropGetLabel)
END_PROPERTIES

PROPS(Ctrl, ButtonOption, Ctrl)
