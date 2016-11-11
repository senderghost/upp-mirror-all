#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LOGPOS            UPP::VppLog() << "-=> " << __FILE__ << '@' << __LINE__ << '\n'

#undef LOG
#define LOG(a)            LOGPOS << a << UPP::EOL

#undef DUMP
#define DUMP(a)           LOGPOS << #a << " = " << (a) << UPP::EOL

#define OUT(a)            VppLog() << a << '\n'
