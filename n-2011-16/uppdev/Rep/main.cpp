#include <CtrlLib/CtrlLib.h>
#include <Report/Report.h>

using namespace Upp;

GUI_APP_MAIN
{
	Report r;
	r << "[ $$0,0#00000000000000000000000000000000:Default]"
	"[{_} "
	"[ {{1755:848:856:846:834:869:795:3197@7|2 [s0;=%% [*2 Points]]"
	"::|2 [s0;=%% [*2 CH]]"
	":: [s0;=%% [*2 Dist]]"
	":: [s0;=%% [*2 GS]]"
	":: [s0;=%% [*2 ETE]]"
	":: [s0;=%% [*2 ETA]]"
	":: [s0;=%% [*2 Fuel U]]"
	"::|2 [s0;=%% [*2 Notes]]"
	"::@2 [s0; ]"
	":: [s0; ]"
	"::@7 [s0;=%% [*2 Rem]]"
	":: [s0;=%% [*2 Act]]"
	":: [s0;=%% [*2 ATE]]"
	":: [s0;=%% [*2 ATA]]"
	":: [s0;=%% [*2 Fuel R]]"
	"::@2 [s0; ]"
	":: [s0; ]"
	":: [s0; ]"
	"::@7 [s0;=%% [*2 `@TD]]"
	":: [s0;=%% [*2 <`- Tot]]"
	":: [s0;=%% [*2 Off `->]]"
	"::@2 [s0;=*2%% ]"
	"::@7 [s0;=%% [*2 `@FT]]"
	"::@2 [s0; ]"
	":: [s0;= `@SP]"
	"::|1 [s0;= `@CH]"
	":: [s0;=%% `@D]"
	":: [s0;=%% `@GS]"
	":: [s0;=%% `@E]"
	":: [s0;=%% ]"
	":: [s0;=%% `@FU]"
	"::|1 [s0; `@N]"
	"::|1 [s0;= `@P]"
	":: [s0; ]"
	":: [s0;=%% `@DR]"
	":: [s0;=%% ]"
	":: [s0;=%% ]"
	":: [s0;=%% ]"
	":: [s0;=%% `@FR]"
	":: [s0; ]"
	":: [s0; ]"
	"::|1 [s0;= `@CH]"
	":: [s0;=%% `@D]"
	":: [s0;=%% `@GS]"
	":: [s0;=%% `@E]"
	":: [s0;=%% ]"
	":: [s0;=%% `@FU]"
	"::|1 [s0; `@N]"
	"::|1 [s0;= `@P]"
	":: [s0; ]"
	":: [s0;=%% `@DR]"
	":: [s0;=%% ]"
	":: [s0;=%% ]"
	":: [s0;=%% ]"
	":: [s0;=%% `@FR]"
	":: [s0; ]"
	":: [s0; ]"
	"::@7 [s0;= [*2 Totals]]"
	"::@2 [s0;=%% `@DT]"
	":: [s0;=%% `@GA]"
	":: [s0;=%% `@ET]"
	":: [s0;=%% `-]"
	":: [s0;=%% `@FT]"
	":: [s0; `-]}}]";
		
	Perform(r);
}
