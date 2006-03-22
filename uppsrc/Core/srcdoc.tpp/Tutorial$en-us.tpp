TITLE("NTL Tutorial")
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
"$$17,17#07531550463529505371228428965313:result`-line][l160;t4167;*C+117 $$18,5#88603949442205825958800053222425:package`-title][{_}%EN-US "
"[s2; NTL Tutorial&][s5")
TOPIC_TEXT(
"; This tutorial is as brief as is possible and should serve as basic overview of "
"NTL. See reference documentation for further information.&][s3; 1. Vector basics&][s5; "
"Let us start with a simple [* Vector] of ints&][s7; -|[* Vector<int>] v;&][s5; You "
"can add elements to the Vector as parameters of the [* Add] method&][s7; -|v.[* Add](1);&][s7; "
"-|v.Add(2);&][s7; -|v.Add(3);&][s5; To iterate Vector ")
TOPIC_TEXT(
"you can use indices&][s7; -|for(int i `= 0; i < v.[* GetCount](); i`+`+)&][s7; -|-|cout "
"<< v[* `[]i[* `]] << `'n`';&][s16;  1&][s16;  2&][s16;  3&][s5; or iterators&][s7; "
"-|for(Vector<int>`::[* Iterator] q `= v.[* Begin](), e `= v.[* End](); q !`= e; q`+`+)&][s7; "
"-|-|cout << [* `*]q << `'n`';&][s16;  1&][s16;  2&][s16;  3&][s3; 2. Vector operations&][s5; "
"You can [* Insert] or [* Remove] elements a")
TOPIC_TEXT(
"t random positions of Vector&][s7; -|Vector<int> v;&][s7; -|v.Add(1);&][s7; -|v.Add(2);&][s7; "
"-|&][s7; -|v.[* Insert](1, 10);&][s17;  v `= `{ 1, 10, 2 `}&][s7; -|v.[* Remove](0);&][s17; "
" v `= `{ 10, 2 `}&][s5; [* At] method returns element at specified position ensuring "
"that such a position exists. If there is not enough elements in Vector, required "
"number of elements is added. If second parameter")
TOPIC_TEXT(
" of At is present, newly added elements are initialized to this value. As an example, "
"we will create distribution of RandomValue with unknown maximal value&][s7; &][s7; "
"-|v.Clear();&][s7; -|for(int i `= 0; i < 10000; i`+`+)&][s7; -|-|v.[* At](RandomValue(), "
"0)`+`+;&][s17;  v `= `{ 958, 998, 983, 1012, 1013, 1050, 989, 998, 1007, 992 `}&][s5;* "
"[* You can apply algorithms on containers, e.g. ]Sort&]")
TOPIC_TEXT(
"[s7; -|[* Sort](v);&][s17;  v `= `{ 958, 983, 989, 992, 998, 998, 1007, 1012, 1013, "
"1050 `}&][s3; 3. Transfer issues&][s5; Often you need to pass content of one container "
"to another of the same type. NTL containers follow [^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ "
"default pick semantics], that means that source container is destroyed&][s7; -|Vector<int> "
"v;&][s7; -|v.Add(1);&][s7; -|v.Add(2);&][s7;")
TOPIC_TEXT(
" &][s7; -|Vector<int> v1 [* `=] v;&][s5; now source Vector [C v] is destroyed `- "
"picked `- and you can no longer access its content. This admittedly strange behaviour "
"has many advantages. First, it is consistently fast and in most cases, transfer of "
"value instead of full copy is exactly what you need. Second, NTL containers can store "
"elements that lack copy operation `- in that case, pick transfer")
TOPIC_TEXT(
" is the only option anyway.&][s5;^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ [^^ If "
"you really need to preserve value of source (and elements support deep copy operation), "
"you can use ]optional deep copy operator or constructor&][s7; -|v [* <<`=] v1;&][s5; "
"Now both containers have the same content. Constructor form of same operation is "
"distinguished by an additional int parameter&][s7; -|Vector<int>")
TOPIC_TEXT(
" v2(v[* , 0]);&][s3; 4. Client types&][s5; So far we were using int as type of elements. "
"In order to store client defined types into the Vector (and the Vector [^topic`:`/`/Core`/src`/Overview`$en`-us^ "
"flavor]) the type must satisfy [^topic`:`/`/Core`/src`/Moveable`$en`-us^ moveable] "
"requirement `- in short, it must not contain back`-pointers nor virtual methods. "
"Type must be marked as moveable in")
TOPIC_TEXT(
" order to define interface contract using&][s7; -|struct Distribution : [* Moveable]<Distribution> "
"`{&][s7; -|-|String      text;&][s7; -|-|Vector<int> data;&][s7; -|`};&][s5; Now "
"to add Distribution elements you cannot use Add with parameter, because it requires "
"elements to have default deep`-copy constructor `- and Distribution does not have "
"one, as Vector<int> has default pick`-constructor, so ")
TOPIC_TEXT(
"Distribution itself has pick`-constructor. It would no be a good idea either, because "
"deep`-copy would involve  expensive copying of inner Vector.&][s5; Instead, [* Add] "
"without parameters has to be used `- it default constructs (that is cheap) element "
"in Vector and returns reference to it&][s7; -|Vector<Distribution> dist;&][s7; -|for(n "
"`= 5; n <`= 10; n`+`+) `{&][s7; -|-|Distribution`& d `= dist")
TOPIC_TEXT(
".[* Add]();&][s7; -|-|char h`[20`];&][s7; -|-|sprintf(h, `\"Test %d`\", n);&][s7; "
"-|-|d.text `= h;&][s7; -|-|for(i `= 0; i < 10000; i`+`+)&][s7; -|-|-|d.data.At(rand() "
"% n, 0)`+`+;&][s7; -|`}&][s7; -|for(i `= 0; i < dist.GetCount(); i`+`+)&][s7; -|-|cout "
"<< dist`[i`] << `'`\\n`';&][s7; &][s16;  Test 5: `{ 2018, 1992, 2025, 1988, 1977 "
"`}&][s16;  Test 6: `{ 1670, 1682, 1668, 1658, 1646, 1676 `}&][s16; ")
TOPIC_TEXT(
" Test 7: `{ 1444, 1406, 1419, 1493, 1370, 1418, 1450 `}&][s16;  Test 8: `{ 1236, "
"1199, 1245, 1273, 1279, 1302, 1250, 1216 `}&][s16;  Test 9: `{ 1115, 1111, 1100, "
"1122, 1192, 1102, 1089, 1064, 1105 `}&][s16;  Test 10: `{ 969, 956, 1002, 1023, 1006, "
"994, 1066, 1022, 929, 1033 `}&][s5; Another possibility is to use AddPick method, "
"which uses pick`-constructor instead of deep`-copy constructor. E.g. D")
TOPIC_TEXT(
"istribution elements might be generated by some function &][s7; -|Distribution CreateDist(int "
"n);&][s5; and code for adding such elements to Vector then looks like&][s7; -|for(n "
"`= 5; n <`= 10; n`+`+)&][s7; -|-|dist.[* AddPick](CreateDist(n));&][s5; alternatively, "
"you can use default`-constructed variant too&][s7; -|-|dist.Add() `= CreateDist(); "
"// alternative&][s3; 5. Array flavor&][s5; If elemen")
TOPIC_TEXT(
"ts do not satisfy requirements for Vector flavor, they can still be stored in Array "
"flavor. Another reason for using Array is need for referencing elements `- Array "
"flavor never invalidates references or pointers to them.&][s5; E.g., std`::list implementation "
"is often non`-moveable, so you have to use Array&][s7; -|[* Array]< std`::list<int> "
"> al;&][s7; -|for(int i `= 0; i < 4; i`+`+) `{&][s7; -|-")
TOPIC_TEXT(
"|std`::list<int>`& l `= al.Add();&][s7; -|-|for(int q `= 0; q < i; q`+`+)&][s7; "
"-|-|-|l.push_back(q);&][s7; -|`}&][s3; 6. Polymorphic Array&][s5; Array can even "
"be used for storing polymorphic elements &][s7; -|struct Number `{&][s7; -|-|virtual "
"double Get() const `= 0;&][s7; -|`};&][s7; &][s7; -|struct Integer : public Number "
"`{&][s7; -|-|int n;&][s7; -|-|virtual double Get() const `{ return n; `")
TOPIC_TEXT(
"}&][s7; -|&][s7; -|-|Integer(int n) : n(n) `{`}&][s7; -|`};&][s7; &][s7; -|struct "
"Double : public Number `{&][s7; -|-|double n;&][s7; -|-|virtual double Get() const "
"`{ return n; `}&][s7; -|&][s7; -|-|Double(double n) : n(n) `{`}&][s7; -|`};&][s5; "
"In this case, elements are added using Add with pointer to base element type parameter. "
"Do not be confused by new and pointer, Array takes ownership of p")
TOPIC_TEXT(
"assed object and  behaves like container of base type elements&][s7; -|Array<Number> "
"num;&][s7; -|num.[* Add]([* new] Integer(3));&][s7; -|num.Add(new Double(15.5));&][s7; "
"-|num.Add(new Double(2.23));&][s7; -|num.Add(new Integer(2));&][s7; -|num.Add(new "
"Integer(20));&][s7; -|num.Add(new Double(`-2.333));&][s17;  num `= `{ 3, 15.5, 2.23, "
"2, 20, `-2.333 `}&][s5; Thanks to well defined algorithm requ")
TOPIC_TEXT(
"irements, you can e.g. directly apply Sort on such Array&][s7; -|bool operator<(const "
"Number`& a, const Number`& b)&][s7; -|`{&][s7; -|-|return a.Get() < b.Get();&][s7; "
"-|`}&][s7; &][s7; .......&][s7; &][s7; -|Sort(num);&][s17;  num `= `{ `-2.333, 2, "
"2.23, 3, 15.5, 20 `}&][s3; 7. Bidirectional containers&][s5; Vector and Array containers "
"allow fast adding and removing elements at the end of sequen")
TOPIC_TEXT(
"ce. Sometimes, same is needed at begin of sequence too (usually to support FIFO "
"like operations). In such case, BiVector and BiArray should be used&][s7; -|BiVector<int> "
"n;&][s7; -|n.[* AddHead](1);&][s7; -|n.[* AddTail](2);&][s7; -|n.AddHead(3);&][s7; "
"-|n.AddTail(4);&][s17;  n `= `{ 3, 1, 2, 4 `}&][s7; -|n.[* DropHead]();&][s17;  n "
"`= `{ 1, 2, 4 `}&][s7; -|n.[* DropTail]();&][s17;  n `= `{ 1, 2 `")
TOPIC_TEXT(
"}&][s7; -|BiArray<Number> num;&][s7; -|num.AddHead(new Integer(3));&][s7; -|num.AddTail(new "
"Double(15.5));&][s7; -|num.AddHead(new Double(2.23));&][s7; -|num.AddTail(new Integer(2));&][s7; "
"-|num.AddHead(new Integer(20));&][s7; -|num.AddTail(new Double(`-2.333));&][s17; "
" num `= `{ 20, 2.23, 3, 15.5, 2, `-2.333 `}&][s3; 8. Index&][s5; Index is a container "
"very similar to the plain Vector (it is rand")
TOPIC_TEXT(
"om access array of elements with fast addition at the end) with one unique feature "
"`- it is able to fast retrieve position of element with required value using [* Find] "
"method&][s7; -|[* Index]<String> ndx;&][s7; -|ndx.[* Add](`\"alfa`\");&][s7; -|ndx.Add(`\"beta`\");&][s7; "
"-|ndx.Add(`\"gamma`\");&][s7; -|ndx.Add(`\"delta`\");&][s7; -|ndx.Add(`\"kappa`\");&][s17; "
" ndx `= `{ alfa, beta, gamma, delta, kappa `")
TOPIC_TEXT(
"}&][s7; -|DUMP(ndx.[* Find](`\"beta`\"))&][s17;  ndx.Find(`\"beta`\") `= 1&][s5; "
"If element is not present in Index, Find returns a negative value&][s7; -|DUMP(ndx.Find(`\"something`\"));&][s17; "
" ndx.Find(`\"something`\") `= `-1&][s5; Any element can be replaced using [* Set] "
"method&][s7; -|ndx.[* Set](0, `\"delta`\");&][s17;  ndx `= `{ delta, beta, gamma, "
"delta, kappa `}&][s5; If there are more elements wi")
TOPIC_TEXT(
"th the same value, they can be iterated using [* FindNext] method&][s7; -|int fi "
"`= ndx.Find(`\"delta`\");&][s7; -|while(fi >`= 0) `{&][s7; -|-|cout << fi << `\" "
"`\";&][s7; -|-|fi `= ndx.[* FindNext](fi);&][s7; -|`}&][s7; -|cout << `'n`';&][s17; "
" 0 3-|&][s5; [* FindAdd] method retrieves position of element like Find, but if element "
"is not present in Index, it is added&][s7; -|DUMP(ndx.[* FindAdd](`\"on")
TOPIC_TEXT(
"e`\"));&][s7; -|DUMP(ndx.FindAdd(`\"two`\"));&][s7; -|DUMP(ndx.FindAdd(`\"three`\"));&][s7; "
"-|DUMP(ndx.FindAdd(`\"two`\"));&][s7; -|DUMP(ndx.FindAdd(`\"three`\"));&][s7; -|DUMP(ndx.FindAdd(`\"one`\"));&][s7; "
"&][s16;  ndx.FindAdd(`\"one`\") `= 5&][s16;  ndx.FindAdd(`\"two`\") `= 6&][s16;  "
"ndx.FindAdd(`\"three`\") `= 7&][s16;  ndx.FindAdd(`\"two`\") `= 6&][s16;  ndx.FindAdd(`\"three`\") "
"`= 7&][s16;  ndx.FindAdd(`\"one`\")")
TOPIC_TEXT(
" `= 5&][s5; Removing elements from random access sequence is always expensive, that "
"is why rather than remove, Index supports [* Unlink] and [* UnlinkKey ]operations, "
"which leave element in Index but make it invisible for Find operation&][s7; -|ndx.[* "
"Unlink](2);&][s7; -|ndx.[* UnlinkKey](`\"kappa`\");&][s7; &][s7; -|DUMP(ndx.Find(ndx`[2`]));&][s7; "
"-|DUMP(ndx.Find(`\"kappa`\"));&][s7; &][s16;  ndx.Fin")
TOPIC_TEXT(
"d(ndx`[2`]) `= `-1&][s16;  ndx.Find(`\"kappa`\") `= `-1&][s5; You can test whether "
"element at given position is unlinked using [* IsUnlinked] method&][s7; -|DUMP(ndx.[* "
"IsUnlinked](1));&][s7; -|DUMP(ndx.IsUnlinked(2));&][s7; &][s16;  ndx.IsUnlinked(1) "
"`= 0&][s16;  ndx.IsUnlinked(2) `= 1&][s5; Unlinked positions can be reused by [* "
"Put] method&][s7; -|ndx.[* Put](`\"foo`\");&][s17;  ndx `= `{ delta, be")
TOPIC_TEXT(
"ta, foo, delta, kappa, one, two, three `}&][s7; -|DUMP(ndx.Find(`\"foo`\"));&][s17; "
" ndx.Find(`\"foo`\") `= 2&][s5; You can also remove all unlinked elements from Index "
"using [* Sweep] method&][s7; -|ndx.Sweep();&][s17;  ndx `= `{ delta, beta, foo, delta, "
"one, two, three `}&][s5; As we said, operations directly removing or inserting elements "
"of Index are very expensive, but sometimes this might not ma")
TOPIC_TEXT(
"tter, so they are available too&][s7; -|ndx.[* Remove](1);&][s17;  ndx `= `{ delta, "
"foo, delta, one, two, three `}&][s7; -|ndx.[* RemoveKey](`\"two`\");&][s17;  ndx "
"`= `{ delta, foo, delta, one, three `}&][s7; -|ndx.[* Insert](0, `\"insert`\");&][s17; "
" ndx `= `{ insert, delta, foo, delta, one, three `}&][s5; Finally, [* PickKeys] operation "
"allows you to obtain Vector of elements of Index in low consta")
TOPIC_TEXT(
"nt time operation (while destroying source Index)&][s7; -|Vector<String> d `= ndx.[* "
"PickKeys]();&][s7; -|Sort(d);&][s17;  d `= `{ delta, delta, foo, insert, one, three "
"`}&][s3; 9. Index and client types&][s5; In order to store elements to Index, they "
"must be moveable (you can use [* ArrayIndex] for types that are not) and they must "
"have defined the operator`=`= and a function to compute hash valu")
TOPIC_TEXT(
"e. Notice usage of [* GetHashValue] for types already known to NTL (fundamental "
"types and `[W`]String) and [* CombineHash] to combine both hash values into final "
"result&][s7; -|struct Person : Moveable<Person> `{&][s7; -|-|String name;&][s7; -|-|String "
"surname;&][s7; -|&][s7; -|-|Person(String name, String surname)&][s7; -|-|: name(name), "
"surname(surname) `{`}&][s7; -|-|Person() `{`}&][s7; -|`};&]")
TOPIC_TEXT(
"[s7; &][s7; -|unsigned [* GetHashValue](const Person`& p)&][s7; -|`{&][s7; -|-|return "
"[* CombineHash]([* GetHashValue](p.name), &][s7; -|-|                   [* GetHashValue](p.surname));&][s7; "
"-|`}&][s7; &][s7; -|bool operator`=`=(const Person`& a, const Person`& b)&][s7; -|`{&][s7; "
"-|-|return a.name `=`= b.name `&`& a.surname `=`= b.surname;&][s7; -|`}&][s7; &][s7; "
".......&][s7; &][s7; -|Index<P")
TOPIC_TEXT(
"erson> p;&][s7; -|p.Add(Person(`\"John`\", `\"Smith`\"));&][s7; -|p.Add(Person(`\"Paul`\", "
"`\"Carpenter`\"));&][s7; -|p.Add(Person(`\"Carl`\", `\"Engles`\"));&][s7; -|     "
" &][s7; -|DUMP(p.Find(Person(`\"Paul`\", `\"Carpenter`\")));&][s17;  p.Find(Person(`\"Paul`\", "
"`\"Carpenter`\")) `= 1&][s5; If type cannot be stored in Index or if references to "
"elements are required, [* ArrayIndex] can be used&][s7; -|unsigned Get")
TOPIC_TEXT(
"HashValue(const Number`& n)&][s7; -|`{&][s7; -|-|return GetHashValue(n.Get());&][s7; "
"-|`}&][s7; &][s7; -|bool operator`=`=(const Number`& a, const Number`& b)&][s7; -|`{&][s7; "
"-|-|return a.Get() `=`= b.Get();&][s7; -|`}&][s7; &][s7; .......&][s7; &][s7; -|[* "
"ArrayIndex]<Number> n;&][s7; -|n.Add(new Integer(100));&][s7; -|n.Add(new Double(10.5));&][s7; "
"-|n.Add(new Integer(200));&][s7; -|n.Add(new D")
TOPIC_TEXT(
"ouble(20.5));&][s17;  n `= `{ 100, 10.5, 200, 20.5 `}&][s7; -|DUMP(n.Find(Double(10.5)));&][s17; "
" n.Find(Double(10.5)) `= 1&][s3; 10. VectorMap&][s5; VectorMap is nothing more than "
"a simple composition of Index and Vector. You can use [* Add] methods to put elements "
"into the VectorMap&][s7; -|[* VectorMap]<String, Person> m;&][s7; -|&][s7; -|m.[* "
"Add](`\"1`\", Person(`\"John`\", `\"Smith`\"));&][s7; -|m")
TOPIC_TEXT(
".Add(`\"2`\", Person(`\"Carl`\", `\"Engles`\"));&][s7; &][s7; -|Person`& p `= m.[* "
"Add](`\"3`\");&][s7; -|p.name `= `\"Paul`\";&][s7; -|p.surname `= `\"Carpenter`\";&][s5; "
"VectorMap provides constant access to its underlying Index and Vector&][s7; -|DUMP(m.[* "
"GetKeys]());&][s7; -|DUMP(m.[* GetValues]());&][s7; &][s16; m.GetKeys() `= `{ 1, "
"2, 3 `}&][s16; m.GetValues() `= `{ John Smith, Carl Engles, Paul Carpen")
TOPIC_TEXT(
"ter `}&][s7; &][s5; You can use indices to iterate map contents&][s7; -|for(i `= "
"0; i < m.GetCount(); i`+`+)&][s7; -|-|cout << m.[* GetKey](i) << `\": `\" << m[* "
"`[]i[* `]] << `'n`';&][s7; &][s16; 1: John Smith&][s16; 2: Carl Engles&][s16; 3: "
"Paul Carpenter&][s7; &][s5; You can use [* Find] method to retrieve position of element "
"with required key&][s7; -|DUMP(m.[* Find](`\"2`\"));&][s17; m.Find(`\"2`\")")
TOPIC_TEXT(
" `= 1&][s5; or [* Get] method to retrieve corresponding value&][s7; -|DUMP(m.[* "
"Get](`\"2`\"));&][s17; m.Get(`\"2`\") `= Carl Engles&][s5; Get method is also present "
"in operator form allowing VectorMap to act like functor&][s7; -|DUMP(m(`\"1`\"));&][s17; "
"m(`\"1`\") `= John Smith&][s5; Passing key not present in VectorMap as Get parameter "
"is a logic error, but there exists two parameter version that return")
TOPIC_TEXT(
"s second parameter if key is not in VectorMap&][s7; -|DUMP(m.Get(`\"33`\", Person(`\"unknown`\", "
"`\"person`\")));&][s17; m.Get(`\"33`\", Person(`\"unknown`\", `\"person`\")) `= unknown "
"person&][s5; As with Index, you can use [* Unlink] to make elements invisible for "
"Find operations&][s7; -|m.Unlink(1);&][s7; -|DUMP(m.Find(`\"2`\"));&][s17; m.Find(`\"2`\") "
"`= `-1&][s5; You can use [* SetKey] method to change the k")
TOPIC_TEXT(
"ey of the element&][s7; -|m.[* SetKey](1, `\"33`\");&][s7; -|DUMP(m.Get(`\"33`\", "
"Person(`\"unknown`\", `\"person`\")));&][s17; m.Get(`\"33`\", Person(`\"unknown`\", "
"`\"person`\")) `= Carl Engles&][s5; If there are more elements with the same key "
"in VectorMap, you can iterate them using [* FindNext] method&][s7; -|m.Add(`\"33`\", "
"Person(`\"Peter`\", `\"Pan`\"));&][s7; &][s16; m.GetKeys() `= `{ 1, 33, 3, 33 `}&][s16; ")
TOPIC_TEXT(
"m.GetValues() `= `{ John Smith, Carl Engles, Paul Carpenter, Peter Pan `}&][s7; "
"&][s7; -|int q `= m.Find(`\"33`\");&][s7; -|while(q >`= 0) `{&][s7; -|-|cout << m`[q`] "
"<< `'n`';&][s7; -|-|q `= m.[* FindNext](q);&][s7; -|`}&][s7; -|&][s16; Carl Engles&][s16; "
"Peter Pan&][s7; &][s5; You can reuse unlinked positions using [* Put] method&][s7; "
"-|m.[* UnlinkKey](`\"33`\");&][s7; -|m.[* Put](`\"22`\", Person(`\"")
TOPIC_TEXT(
"Ali`\", `\"Baba`\"));&][s7; -|m.Put(`\"44`\", Person(`\"Ivan`\", `\"Wilks`\"));&][s7; "
"&][s16; m.GetKeys() `= `{ 1, 22, 3, 44 `}&][s16; m.GetValues() `= `{ John Smith, "
"Ali Baba, Paul Carpenter, Ivan Wilks `}&][s7; &][s5; [* GetSortOrder] algorithm returns "
"order of elements as Vector<int> container. You can use it to order content of VectorMap "
"without actually moving its elements&][s7; -|bool operator<(const")
TOPIC_TEXT(
" Person`& a, const Person`& b)&][s7; -|`{&][s7; -|-|return a.surname `=`= b.surname "
"? a.name < b.name&][s7; -|                              : a.surname < b.surname;&][s7; "
"-|`}&][s7; &][s7; .......&][s7; &][s7; -|Vector<int> order `= [* GetSortOrder](m.GetValues());&][s17; "
"order `= `{ 1, 2, 0, 3 `}&][s7; -|for(i `= 0; i < order.GetCount(); i`+`+)&][s7; "
"-|-|cout << m.GetKey(order`[i`]) << `\": `\" << ")
TOPIC_TEXT(
"m`[order`[i`]`] << `'n`';&][s7; &][s16; 22: Ali Baba&][s16; 3: Paul Carpenter&][s16; "
"1: John Smith&][s16; 44: Ivan Wilks&][s7; &][s5; You can get Vector of values or "
"keys using [* PickValues] resp. [* PickKeys] methods in low constant time, while "
"destroying content of source VectorMap&][s7; -|Vector<Person> ps `= m.[* PickValues]();&][s17; "
"ps `= `{ John Smith, Ali Baba, Paul Carpenter, Ivan Wilks ")
TOPIC_TEXT(
"`}&][s5; If type of values does not satisfy requirements for Vector elements or "
"if references to elements are needed, you can use [* ArrayMap] instead&][s7; -|[* "
"ArrayMap]<String, Number> am;&][s7; -|am.Add(`\"A`\", new Integer(1));&][s7; -|am.Add(`\"B`\", "
"new Double(2.0));&][s7; &][s16; am.GetKeys() `= `{ A, B `}&][s16; am.GetValues() "
"`= `{ 1, 2 `}&][s7; &][s7; -|DUMP(am.Get(`\"A`\"));&][s7; -|DUMP(am.")
TOPIC_TEXT(
"Find(`\"B`\"));&][s7; &][s16; am.Get(`\"A`\") `= 1&][s16; am.Find(`\"B`\") `= 1&][s16; "
"&][s0;3 ]")
