TITLE("Internationalization and translation files")
TOPIC_TEXT(
"[2 $$0,0#00000000000000000000000000000000:Default][l288;i704;a17;O9;~~~.992;2 $$1,0#10431211400427159095818037425705:param][a83;*R6 "
"$$2,5#31310162474203024125188417583966:caption][b83;* $$3,5#07864147445237544204411237157677:title][b167;a42;C2 "
"$$4,6#40027414424643823182269349404212:item][b42;a42;2 $$5,5#45413000475342174754091244180557:text][l288;a17;2 "
"$$6,6#27521748481378242620020725143825:desc][")
TOPIC_TEXT(
"l321;t246;C@5;1 $$7,7#20902679421464641399138805415013:code][b2503; $$8,0#65142375456100023862071332075487:separator][*@(0.0.255)2 "
"$$9,0#83433469410354161042741608181528:base][t4167;C $$10,0#37138531426314131251341829483380:class][l288;a17;*1 "
"$$11,11#70004532496200323422659154056402:requirement][i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam][b167;C2 "
"$$13,13#924304594434")
TOPIC_TEXT(
"60461911108080531343:item1][i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2][*@2$(0.128.128) "
"$$15,15#34511555403152284025741354420178:NewsDate][l321;*C$7;2 $$16,16#03451589433145915344929335295360:result][l321;b83;a83;*C$7;2 "
"$$17,17#07531550463529505371228428965313:result`-line][l160;t4167;*C+117 $$18,5#88603949442205825958800053222425:package`-title][@(128.0.255)2 "
"$$19,0#65874547464")
TOPIC_TEXT(
"505293575048467215454:QTF Chr][{_}%EN-US [s2; Internationalization and translation "
"files&][s0; To internationalize your application, you need to provide versions of "
"string literals in all required languages. In U`+`+, you can do this by using translation "
"files.&][s0; &][s0; To mark string literals for translation in sources, you have "
"to tag them with t`_ macro, like in&][s0; &][s7; printf(t`_(`\"He")
TOPIC_TEXT(
"llo world!`\"));&][s0; &][s0; This macro is expanded to a function call that provides "
"translation of english (more specifically en`-US) text to default language set by "
"SetLanguage function. String literal here is considered to be the key for translation "
"lookup. U`+`+ supports three forms of keys here:&][s0; &][s0;i150;O0; plain keys "
"are just en`-US texts. Example: t`_(`\"Hello world!`\")&][s0;i150;O0")
TOPIC_TEXT(
"; context keys consist of context and en`-US text separated by `\\v, where both "
"are parts of key. Example: t`_(`\"align`\\vTop`\"). This is useful in cases when "
"the context is needed to provide translation.&][s0;i150;O0; id keys consist of id "
"and en`-US text separated by `\\a, but only the id is used as key in the translation "
"lookup. Example: t`_(`\"CtrlCoreReport`\\aReport`\"). &][s0; &][s0; Important: t")
TOPIC_TEXT(
"`_ tag can be used with string literals only.&][s0; &][s0; t`_ macro expands to "
"a function call that provides translation of a given string literal. Where this is "
"not acceptable (like in arrays of literals), tt`_ tag can be used `- it is expanded "
"to a literal which can be later converted using GetLngString macro.&][s0; &][s0; "
"Translations are stored in .t files of regular packages. Format of this ")
TOPIC_TEXT(
"file is rather simple `- it is set of keys followed by translation of keys to required "
"languages. Key is introduced by T`_, translation, translations are introduced by "
"their language codes, e.g.&][s0; &][s0; T`_(`\"Sideways`\")&][s0; csCZ(`\"Na \305\241\303\255\305\231ku`\")&][s0; "
"&][s0; TheIDE provides means for manipulating .t files `- in Workspace menu there "
"is `\"Synchronize translation files`\" operation. This opera")
TOPIC_TEXT(
"tion scans all source files of current project and builds map of t`_ tagged string "
"literals and then combines this information with any valid .t files it finds. This "
"operation also allows adding new languages to .t files.&][s0; &][s0; t. files are "
"always in UTF8 encoding.&][s0; &][s0; TheIDE also maintains translation repository "
"`- it stores ALL translations that it meets into this file. Each time")
TOPIC_TEXT(
" .t file is synchronized, TheIDE tries to supply all missing translations from repository "
"and also adds all translation existing in .t file back to repository. This is e.g. "
"great when some source is moved to another package.&][s0; &][s0; U`+`+ also supports "
"run`-time translations (as opposite to compile`-time .t files). You can use `-`-export`-tr "
"in any U`+`+ application to force the creation of a")
TOPIC_TEXT(
" runtime translation file (with .tr extension). Parameters of this flag is 4 letter "
"language code and single letter character set encoding according this table:&][s0; "
"&][s0; &][ {{1840:8160<330;>1757;f4;h1; [s19;=C `_]:: [s0; utf`-8]:: [s19;=C 0]:: "
"[s0; windows`-1250]:: [s19;=C 1]:: [s0; windows`-1251]:: [s19;=C 2]:: [s0; windows`-1252]:: "
"[s19;=C 3]:: [s0; windows`-1253]:: [s19;=C 4]:: [s0; window")
TOPIC_TEXT(
"s`-1254]:: [s19;=C 5]:: [s0; windows`-1255]:: [s19;=C 6]:: [s0; windows`-1256]:: "
"[s19;=C 7]:: [s0; windows`-1257]:: [s19;=C A]:: [s0; iso`-8859`-1]:: [s19;=C B]:: "
"[s0; iso`-8859`-2]:: [s19;=C C]:: [s0; iso`-8859`-3]:: [s19;=C D]:: [s0; iso`-8859`-4]:: "
"[s19;=C E]:: [s0; iso`-8859`-5]:: [s19;=C F]:: [s0; iso`-8859`-6]:: [s19;=C G]:: "
"[s0; iso`-8859`-7]:: [s19;=C H]:: [s0; iso`-8859`-8]:: [s19;=C I]::")
TOPIC_TEXT(
" [s0; iso`-8859`-9]:: [s19;=C J]:: [s0; iso`-8859`-10]}}&][s0; &][s0; example:&][s0; "
"&][s7; theide `-`-export`-tr dede2&][s0; &][s0; will create dede2.tr file (in exe "
"directory on Win32 and `~/.theide on Posix) ready for translation to deDE in windows`-1252. "
"If the translations are already present, they are supplied, otherwise the .tr file "
"contains empty strings in place of the translations.&][s0;")
TOPIC_TEXT(
" &][s0; Each U`+`+ performs a search for .tr files at startup and uses them to extend "
"internal translation tables.&][s0; &][s0; .tr files can be also imported to .t files "
"using TheIDE`'s `\"Import runtime translation`\" function of Workspace menu. Note "
"that this function does not add new languages to .t files `- just adds translations "
"to languages added manually.&][s0; &][s0; When `-`-export`-tr is ")
TOPIC_TEXT(
"used without parameter, it exports all compile`-time languages. This is useful for "
"maintainance purposes.&][s0;3 ]")
