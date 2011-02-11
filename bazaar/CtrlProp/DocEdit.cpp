#include "CtrlPropCommon.h"
#include <CtrlLib/CtrlLib.h>

bool PropSetAutoHideSb(const Value& v, DocEdit& o) { if(!IsNumber(v)) return false; o.AutoHideSb(v); return true; }
bool PropGetAutoHideSb(Value& v, const DocEdit& o) { v = o.IsAutoHideSb(); return true; }
bool PropSetUpDownLeave(const Value& v, DocEdit& o) { if(!IsNumber(v)) return false; o.UpDownLeave(v); return true; }
bool PropGetUpDownLeave(Value& v, const DocEdit& o) { v = o.IsUpDownLeave(); return true; }
bool PropSetEofLine(const Value& v, DocEdit& o) { if(!IsNumber(v)) return false; o.EofLine(v); return true; }
bool PropGetEofLine(Value& v, const DocEdit& o) { v = o.IsEofLine(); return true; }

PROPERTIES(DocEdit, TextCtrl)
PROPERTY("autohidesb", PropSetAutoHideSb, PropGetAutoHideSb)
PROPERTY("updownleave", PropSetUpDownLeave, PropGetUpDownLeave)
PROPERTY("eofline", PropSetEofLine, PropGetEofLine)
END_PROPERTIES

PROPS(Ctrl, DocEdit, TextCtrl)
