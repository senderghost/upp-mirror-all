#include "CtrlPropCommon.h"
#include <CtrlLib/CtrlLib.h>

bool PropSetUndoSteps(const Value& v, TextCtrl& o) { if(!IsNumber(v)) return false; o.UndoSteps(v); return true; }
bool PropGetUndoSteps(Value& v, const TextCtrl& o) { v = o.GetUndoSteps(); return true; }
bool PropSetProcessTab(const Value& v, TextCtrl& o) { if(!IsNumber(v)) return false; o.ProcessTab(v); return true; }
bool PropGetProcessTab(Value& v, const TextCtrl& o) { v = o.IsProcessTab(); return true; }
bool PropSetProcessEnter(const Value& v, TextCtrl& o) { if(!IsNumber(v)) return false; o.ProcessEnter(v); return true; }
bool PropGetProcessEnter(Value& v, const TextCtrl& o) { v = o.IsProcessEnter(); return true; }
bool PropSetNoBackground(const Value& v, TextCtrl& o) { if(!IsNumber(v)) return false; o.NoBackground(v); return true; }
bool PropGetNoBackground(Value& v, const TextCtrl& o) { v = o.IsNoBackground(); return true; }

PROPERTIES(TextCtrl, Ctrl)
PROPERTY("undosteps", PropSetUndoSteps, PropGetUndoSteps)
PROPERTY("processtab", PropSetProcessTab, PropGetProcessTab)
PROPERTY("processenter", PropSetProcessEnter, PropGetProcessEnter)
PROPERTY("nobackground", PropSetNoBackground, PropGetNoBackground)
END_PROPERTIES

PROPS(Ctrl, TextCtrl, Ctrl)
