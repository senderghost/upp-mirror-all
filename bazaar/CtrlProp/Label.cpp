#include "CtrlPropCommon.h"
#include <CtrlLib/CtrlLib.h>

bool PropSetText(const Value& v, Label& o) { o.SetText(AsString(v)); return true; }
bool PropGetText(Value& v, const Label& o) { v = o.GetText(); return true; }

PROPERTIES(Label, StaticText)
PROPERTY("text", PropSetText, PropGetText)
END_PROPERTIES

PROPS(Ctrl, Label, StaticText)
