topic "U++ Core vs D programming language";
[ $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[s0; [*R6 U`+`+ Core vs D programming language]&]
[s0;>*^topic`:`/`/uppweb`/www`/vsd`$ru`-ru^1 &]
[s0;^topic`:`/`/uppweb`/www`/comparison`$ru`-ru^ &]
[s0; Autoři programovacího jazyka D mají na svých stránkách 
pěkný příklad jeho použití:&]
[s0; &]
[s0; [^http`:`/`/www`.digitalmars`.com`/d`/2`.0`/cppstrings`.html^ http://www.digitalmar
s.com/d/2.0/cppstrings.html]&]
[s0; &]
[s0; Využili jsme ho a přepsali jej do U`+`+. Testovali jsme na 
systému s Ubuntu 64 s použitím `"gdc`" kompilátoru s nastavením 
doporučeným v zmiňovaném článku.&]
[s0; &]
[s0; Museli jsme použít větší soubor než `"Alice30.txt`", protože 
náš systém byl na tak malý soubor příliš rychlý. Proto 
jsme zkombinovali několik souborů ze stejného [^http`:`/`/www`.gutenberg`.org`/ebooks`/11^ s
tejného zdroje] do 2MB souboru.&]
[s0; &]
[s0; Také jsme z kódu odstranili části starající se o výstup 
abychom docílili relevantnějších výsledků.&]
[s0; &]
[s0; Výsledky:&]
[s0; &]
[ {{3333:3333:3334<768;>800;h1;@7 [s0; [* Jazyk D]]
:: [s0; [* U`+`+]]
:: [s0; [* U`+`+ / Jazyk D]]
::@2 [s0; 0.072s]
:: [s0; 0.043s]
:: [s0; 1.7]}}&]
[s0; &]
[s0; To znamená, že C`+`+ je pořád o dost napřed před of D 
(o 70%) pokud jej nebrzdí design standartní knihovny a průměrná 
implementace...&]
[s0; &]
[ {{10000@(254.254.208) [s0; [*C@5 #include <Core/Core.h>]&]
[s0;*C@5 &]
[s0; [*C@5 using namespace Upp;]&]
[s0;*C@5 &]
[s0; [*C@5 #define NOOUTPUT]&]
[s0;*C@5 &]
[s0; [*C@5 int main(int argc, const char `*argv`[`])]&]
[s0; [*C@5 `{]&]
[s0; [*C@5 -|int n;]&]
[s0; [*C@5 -|VectorMap<String, int> map;]&]
[s0; [*C@5 -|Cout() << `"   lines   words   bytes file`\n`";]&]
[s0; [*C@5 -|int total`_lines `= 0;]&]
[s0; [*C@5 -|int total`_words `= 0;]&]
[s0; [*C@5 -|int total`_bytes `= 0;]&]
[s0; [*C@5 -|for(int i `= 1; i < argc; i`+`+) `{]&]
[s0; [*C@5 -|-|String f `= LoadFile(argv`[i`]);]&]
[s0; [*C@5 -|-|int lines `= 0;]&]
[s0; [*C@5 -|-|int words `= 0;]&]
[s0; [*C@5 -|-|const char `*q `= f;]&]
[s0; [*C@5 -|-|for(;;) `{]&]
[s0; [*C@5 -|-|-|int c `= `*q;]&]
[s0; [*C@5 -|-|-|if(IsAlpha(c)) `{]&]
[s0; [*C@5 -|-|-|-|const char `*b `= q`+`+;]&]
[s0; [*C@5 -|-|-|-|while(IsAlNum(`*q)) q`+`+;]&]
[s0; [*C@5 -|-|-|-|map.GetAdd(String(b, q), 0)`+`+;]&]
[s0; [*C@5 -|-|-|-|words`+`+;]&]
[s0; [*C@5 -|-|-|`}]&]
[s0; [*C@5 -|-|-|else `{]&]
[s0; [*C@5 -|-|-|-|if(!c) break;]&]
[s0; [*C@5 -|-|-|-|if(c `=`= `'`\n`')]&]
[s0; [*C@5 -|-|-|-|-|`+`+lines;]&]
[s0; [*C@5 -|-|-|-|q`+`+;]&]
[s0; [*C@5 -|-|-|`}]&]
[s0; [*C@5 -|-|`}]&]
[s0; [*C@5 -|-|Cout() << Format(`"%8d%8d%8d %s`\n`", lines, words, f.GetCount(), 
argv`[i`]);]&]
[s0; [*C@5 -|-|total`_lines `+`= lines;]&]
[s0; [*C@5 -|-|total`_words `+`= words;]&]
[s0; [*C@5 -|-|total`_bytes `+`= f.GetCount();]&]
[s0; [*C@5 -|`}]&]
[s0; [*C@5 -|Vector<int> order `= GetSortOrder(map.GetKeys());]&]
[s0; [*C@5 #ifndef NOOUTPUT]&]
[s0; [*C@5 -|Cout() << Format(`"`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-`-
`-`-`-`-`-`-`-`-`-`-%8d%8d%8d total`\n`", total`_lines, total`_words, 
total`_bytes);]&]
[s0;*C@5 &]
[s0; [*C@5 -|for(int i `= 0; i < order.GetCount(); i`+`+)]&]
[s0; [*C@5 -|-|Cout() << map.GetKey(order`[i`]) << `": `" << map`[order`[i`]`] 
<< `'`\n`';]&]
[s0; [*C@5 #endif]&]
[s0; [*C@5 -|return 0;]&]
[s0; [*C@5 `}]&]
[s0;*C@5 ]}}&]
[s0; ]