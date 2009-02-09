#include "Examples.h"

#if 0

void RichTextExample(Painter& sw)
{
	const char *qtf =
		"[ $$0,0#00000000000000000000000000000000:Default]"
		"[*C@3+75 $$1,1#36268203433472503231438721581057:code]"
		"[*/+117 $$2,0#07143242482611002448121871408047:title]"
		"[@(128.0.255)2 $$3,0#65874547464505293575048467215454:QTF Chr]"
		"[{_}%EN-US "
		"[s0;= [*8 QTF]&]"
		"[s0; &]"
		"[s0; QTF is the native format of Ultimate`+`+ rich texts (formatted "
		"texts).&]"
		"[s0; &]"
		"[s0; It is byte oriented format. Bytes with values 2`-31 are ignored. "
		"Other are interpreted as characters or formatting commands.&]"
		"[s0; &]"
		"[s0; Letters ([@4 a]`-[@4 zA]`-[@4 Z]), numbers ([@4 0]`-[@4 9]), space (32) "
		"and characters&]"
		"[s0; &]"
		"[s0; [*@4 . , ; ! ? % ( ) / < > #]&]"
		"[s0; &]"
		"[s0; and bytes greater than 127 are guaranteed to be never used as "
		"command characters (not even in future versions of QTF). Other "
		"characters should be prefixed with escape character `` (reverse "
		"apostrophe). Group of characters can be escaped using byte 1. "
		"Example:&]"
		"[s0; &]"
		"[s1; `\"`\1a`[x`]`\1`[`* bold`]`\"&]"
		"[s0; &]"
		"[s0; Byte 0 represents the end of input sequence.&]"
		"[s0; &]"
		"[s0; Dimension units of QTF are dots `- one dot is defined as 1/600 "
		"of inch.&]"
		"[s0; &]"
		"[s0; Colors are described as either number [@(128.0.255) 0]`-[@(128.0.255) 9], "
		"with meaning&]"
		"[s0; &]"
		"[ {{1000:1000:1000:1000:1000:1000:1000:1000:1000:1000<96;>96;f4; [s0;%- [* 0]]"
		":: [s0;%- [* 1]]"
		":: [s0;%- [* 2]]"
		":: [s0;%- [* 3]]"
		":: [s0;%- [* 4]]"
		":: [s0;%- [* 5]]"
		":: [s0;%- [* 6]]"
		":: [s0;%- [* 7]]"
		":: [s0;%- [* 8]]"
		":: [s0;%- [* 9]]"
		"::l/0r/0t/0b/0@0 [s0; ]"
		"::@1 [s0; ]"
		"::@2 [s0; ]"
		"::@3 [s0; ]"
		"::@4 [s0; ]"
		"::@5 [s0; ]"
		"::@6 [s0; ]"
		"::@7 [s0; ]"
		"::@8 [s0; ]"
		"::@9 [s0; ]"
		"::l/25r/25t/15b/15@2 [s0;%- [1 Black]]"
		":: [s0; [1 LtGray]]"
		":: [s0; [1 White]]"
		":: [s0;%- [1 Red]]"
		":: [s0;%- [1 Green]]"
		":: [s0;%- [1 Blue]]"
		":: [s0;%- [1 LtRed]]"
		":: [s0;%- [1 WhiteGray]]"
		":: [s0;%- [1 LtCyan]]"
		":: [s0;%- [1 Yellow]]}}&]"
		"[s0; &]"
	;
	sw.Scale(0.18);
	ParseQTF(qtf).Paint(sw, 10, 10, 5000);
}

INITBLOCK
{
	RegisterExample("RichText", RichTextExample);
}

#endif
