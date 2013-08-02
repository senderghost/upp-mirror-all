TITLE("NTLvsSTL")
TOPIC_TEXT(
"[ $$0,0#00000000000000000000000000000000:Default][l288;i704;a17;O9;~~~.992; $$1,"
"0#10431211400427159095818037425705:param][a83;*R6 $$2,5#3131016247420302412518841"
"7583966:caption][b83;* $$3,5#07864147445237544204411237157677:title][b167;a42;C $"
"$4,6#40027414424643823182269349404212:item][b42;a42; $$5,5#4541300047534217475409"
"1244180557:text][l288;a17; $$6,6#27521748481378242620020725143825:desc][l321;t246"
";C@5;1 $$7,7#20902679421464641399138805415013:code][b2503; $$8,0#6514237545610002"
"3862071332075487:separator][*@(0.0.255) $$9,0#83433469410354161042741608181528:ba"
"se][t4167;C+117 $$10,0#37138531426314131251341829483380:class][l288;a17;*1 $$11,1"
"1#70004532496200323422659154056402:requirement][i416;b42;a42;O9;~~~.416; $$12,12#"
"10566046415157235020018451313112:tparam][b167;C $$13,13#9243045944346046191110808"
"0531343:item1][a42;C $$14,14#77422149456609303542238260500223:item2][*@2$(0.128.1"
"28) $$15,15#34511555403152284025741354420178:NewsDate][l321;*C$7 $$16,16#03451589"
"433145915344929335295360:result][l321;b83;a83;*C$7 $$17,17#0753155046352950537122"
"8428965313:result`-line][l160;t4167;*C+117 $$18,5#8860394944220582595880005322242"
"5:package`-title][{_}%EN-US [s2; NTL - STL Comparison&][s5; NTL was created to so"
"lve following problems we used to encounter when using STL: &][s3; Copy-construct"
"ible requirements&][s5; STL requires the elements stored in containers to meet th"
"e requirements of copy-constructible and assignable types. This causes two proble"
"ms:&][s5;i150;O2; Elements that do not satisfy these requirements cannot be direc"
"tly stored in STL containers.&][s5;i150;O2; For many types of elements, including"
" STL containers themselves, copy-constructor and assign operator is a very expens"
"ive operation, that is why often they cannot be stored in STL containers effectiv"
"ely.&][s5; NTL addresses this problem by introducing [^dpp`:`/`/SourceDoc`/Contai"
"ners`/Overview^ Vector] and [^dpp`:`/`/SourceDoc`/Containers`/Overview^ Array] fl"
"avors of containers.&][s3; Value transfer&][s5; Content o")
TOPIC_TEXT(
"f STL containers can be transfered only using expensive deep-copy constructor/as"
"sigment operator. This causes performance problems especially when using STL cont"
"ainers as function return values, but lack of better functionality is missing els"
"ewhere too. NTL provides [^dpp`:`/`/SourceDoc`/Containers`/pick`_^ transfer seman"
"tics] concepts to deal with this problem.&][s3; Random access and random access n"
"otation&][s5; STL uses iterators as the preferred way how to access and identify "
"elements in containers. While this is generally the most generic way, real-life p"
"roblems often require or at least benefit from random access using indices. NTL p"
"rovides fast random access to all kinds of containers and NTL interfaces prefer n"
"otation using indices. As a side effect, NTL user can completely avoid using iter"
"ators in favor of indices, which in current C`++ results in much simpler and less"
" verbose syntax (using modern optimizing compilers there is no difference in perf"
"ormance).&][s3; Index&][s5; A completely new type of associative container, [^dpp"
"`:`/`/`:`:`/Index`<class T`, class HashFn `= StdHash`<T`> `>`/template `<class T`"
", class HashFn `= StdHash`<T`> `> class Index^ Index], is introduced, as an ideal"
" building block for all kinds of associative operations.&][s3; Algorithm requirem"
"ents&][s5; Requirements of STL algorithms are very loosely defined. NTL tries to "
"provide more specific requirements and also minimal ones. This allows e.g. [^dpp`"
":`/`/www`/pages`/polyarray^ direct sorting of Array of polymorphic elements].&][s"
"3; Minor improvements&][s5; There are also some minor improvements:&][s5;i150;O2;"
" Besides [* reserve] present in STL, NTL provides also [* Shrink] method to minim"
"ize a container's memory consumption.&][s5;i150;O2; Iterators can be assigned a N"
"ULL value.&][s5;i150;O2; Associative containers are based on hashing to provide b"
"etter performance. Utility classes and functions are provided to support building"
" correct hashing functions.")
