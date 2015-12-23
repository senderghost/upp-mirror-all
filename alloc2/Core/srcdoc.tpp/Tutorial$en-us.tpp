topic "NTL Tutorial";
[2 $$0,0#00000000000000000000000000000000:Default]
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[H4;b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
[C2 $$10,0#37138531426314131251341829483380:class]
[l288;a17;*1 $$11,11#70004532496200323422659154056402:requirement]
[i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam]
[b167;C2 $$13,13#92430459443460461911108080531343:item1]
[i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2]
[*@2$(0.128.128)2 $$15,15#34511555403152284025741354420178:NewsDate]
[l321;*C$7;2 $$16,16#03451589433145915344929335295360:result]
[l321;b83;a83;*C$7;2 $$17,17#07531550463529505371228428965313:result`-line]
[l160;*C+117 $$18,5#88603949442205825958800053222425:package`-title]
[2 $$19,0#53580023442335529039900623488521:gap]
[C2 $$20,20#70211524482531209251820423858195:class`-nested]
[b50;2 $$21,21#03324558446220344731010354752573:Par]
[{_}%EN-US 
[s2; U`+`+ Containers Tutorial&]
[s3; 1. Vector basics&]
[s5; Let us start with a simple [* Vector] of ints&]
[s7; -|[* Vector<int>] v;&]
[s5; You can add elements to the Vector as parameters of the [* Add] 
method&]
[s7; -|v.[* Add](1);&]
[s7; -|v.Add(2);&]
[s7; -|v.Add(3);&]
[s5; To iterate Vector you can use indices&]
[s7; -|for(int i `= 0; i < v.[* GetCount](); i`+`+)&]
[s7; -|-|LOG(v[* `[]i[* `]]);&]
[s16;  1&]
[s16;  2&]
[s16;  3&]
[s5; Alternative, U`+`+ also provides iterators&]
[s7; -|for(Vector<int>`::[* Iterator] q `= v.[* Begin](), e `= v.[* End](); 
q !`= e; q`+`+)&]
[s7; -|-|LOG([* `*]q);&]
[s16;  1&]
[s16;  2&]
[s16;  3&]
[s5; however the use of iterators is usually reserved for special 
opportunities in U`+`+ (like implementing algorithm code) and 
generally deprecated. We suggest you to use indices unless you 
have a really good reason to do otherwise.&]
[s5; [/ Note: LOG is diagnostics macro that outputs its argument to 
the .log file in debug mode. Another similar macros we will use 
in this tutorial are DUMP (similar to the LOG, but dumps the 
source expression too) and DUMPC (dumps the content of the container).]&]
[s5;/ &]
[s3; 2. Vector operations&]
[s5; You can [* Insert] or [* Remove] elements at random positions of 
Vector&]
[s7; -|Vector<int> v;&]
[s7; -|v.Add(1);&]
[s7; -|v.Add(2);&]
[s7; -|&]
[s7; -|v.[* Insert](1, 10);&]
[s17;  v `= `{ 1, 10, 2 `}&]
[s7; -|v.[* Remove](0);&]
[s17;  v `= `{ 10, 2 `}&]
[s5; [* At] method returns element at specified position ensuring that 
such a position exists. If there is not enough elements in Vector, 
required number of elements is added. If second parameter of 
At is present, newly added elements are initialized to this value. 
As an example, we will create distribution of RandomValue with 
unknown maximal value&]
[s7; &]
[s7; -|v.Clear();&]
[s7; -|for(int i `= 0; i < 10000; i`+`+)&]
[s7; -|-|v.[* At](RandomValue(), 0)`+`+;&]
[s17;  v `= `{ 958, 998, 983, 1012, 1013, 1050, 989, 998, 1007, 992 
`}&]
[s5; You can apply algorithms on containers, e.g. [* Sort]&]
[s7; -|[* Sort](v);&]
[s17;  v `= `{ 958, 983, 989, 992, 998, 998, 1007, 1012, 1013, 1050 
`}&]
[s0; &]
[s3; 3. Transfer issues&]
[s5; Often you need to pass content of one container to another of 
the same type. NTL containers always support [^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ p
ick semantics], and, depending on type stored, also might support 
[^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ clone sematics]. When 
transfering the value, you have to explicitly specify which one 
to use:&]
[s7; -|Vector<int> v;&]
[s7; -|v.Add(1);&]
[s7; -|v.Add(2);&]
[s7; &]
[s7; -|Vector<int> v1 [* `=] pick(v);&]
[s5; now source Vector [C v] is destroyed `- picked `- and you can 
no longer access its content. This behaviour has many advantages. 
First, it is consistently fast and in most cases, transfer of 
value instead of full copy is exactly what you need. Second, 
NTL containers can store elements that lack copy operation `- 
in that case, pick transfer is the only option anyway.&]
[s5; If you really need to preserve value of source (and elements 
support deep copy operation), you can use [^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ c
lone]&]
[s7; -|v [* `=] clone(v1);&]
[s7; &]
[s3; 4. Client types&]
[s5; So far we were using int as type of elements. In order to store 
client defined types into the Vector (and the Vector [^topic`:`/`/Core`/src`/Overview`$en`-us^ f
lavor]) the type must satisfy [^topic`:`/`/Core`/src`/Moveable`$en`-us^ moveable] 
requirement `- in short, it must not contain back`-pointers nor 
virtual methods. Type must be marked as moveable in order to 
define interface contract using&]
[s7; -|struct Distribution : [* Moveable]<Distribution> `{&]
[s7; -|-|String      text;&]
[s7; -|-|Vector<int> data;&]
[s7; &]
[s7; -|-|rval`_default(Distribution);&]
[s7; -|-|Distribution() `{`}&]
[s7; -|`};&]
[s5; Note that rval`_default macro is helper to restore default deleted 
r`-value constructor in C`+`+11 and default constructor is also 
default deleted in C`+`+11.&]
[s5; Now to add Distribution elements you cannot use Add with parameter, 
because it requires elements to have default deep`-copy constructor 
`- and Distribution does not have one, as Vector<int> has default 
pick`-constructor, so Distribution itself has pick`-constructor. 
It would no be a good idea either, because deep`-copy would involve 
 expensive copying of inner Vector.&]
[s5; Instead, [* Add] without parameters has to be used `- it default 
constructs (that is cheap) element in Vector and returns reference 
to it&]
[s7; -|Vector<Distribution> dist;&]
[s7; -|for(int n `= 5; n <`= 10; n`+`+) `{&]
[s7; -|-|Distribution`& d `= dist.[* Add]();&]
[s7; -|-|d.text << `"Test `" << n;&]
[s7; -|-|for(int i `= 0; i < 10000; i`+`+)&]
[s7; -|-|-|d.data.At(rand() % n, 0)`+`+;&]
[s7; -|`}&]
[s7; &]
[s16;  Test 5: `{ 2018, 1992, 2025, 1988, 1977 `}&]
[s16;  Test 6: `{ 1670, 1682, 1668, 1658, 1646, 1676 `}&]
[s16;  Test 7: `{ 1444, 1406, 1419, 1493, 1370, 1418, 1450 `}&]
[s16;  Test 8: `{ 1236, 1199, 1245, 1273, 1279, 1302, 1250, 1216 `}&]
[s16;  Test 9: `{ 1115, 1111, 1100, 1122, 1192, 1102, 1089, 1064, 1105 
`}&]
[s16;  Test 10: `{ 969, 956, 1002, 1023, 1006, 994, 1066, 1022, 929, 
1033 `}&]
[s5; Another possibility is to use AddPick method, which uses pick`-constructor 
instead of deep`-copy constructor. E.g. Distribution elements 
might be generated by some function &]
[s7; -|Distribution CreateDist(int n);&]
[s5; and code for adding such elements to Vector then looks like&]
[s7; -|for(n `= 5; n <`= 10; n`+`+)&]
[s7; -|-|dist.[* AddPick](CreateDist(n));&]
[s5; alternatively, you can use default`-constructed variant too&]
[s7; -|-|dist.Add() `= CreateDist(); // alternative&]
[s7; &]
[s3; 5. Array flavor&]
[s5; If elements do not satisfy requirements for Vector flavor, they 
can still be stored in Array flavor. Another reason for using 
Array is need for referencing elements `- Array flavor never 
invalidates references or pointers to them.&]
[s5; Example of elements that cannot be stored in Vector flavor are 
STL containers (STL does not specify the NTL flavor for obvious 
reasons):&]
[s7; -|[* Array]< std`::list<int> > al;&]
[s7; -|for(int i `= 0; i < 4; i`+`+) `{&]
[s7; -|-|std`::list<int>`& l `= al.Add();&]
[s7; -|-|for(int q `= 0; q < i; q`+`+)&]
[s7; -|-|-|l.push`_back(q);&]
[s7; -|`}&]
[s7; &]
[s3; 6. Polymorphic Array&]
[s5; Array can even be used for storing polymorphic elements &]
[s7; struct Number `{&]
[s7; -|virtual double Get() const `= 0;&]
[s7; &]
[s7; -|String ToString() const `{ return AsString(Get()); `}&]
[s7; -|&]
[s7; -|virtual `~Number() `{`}&]
[s7; `};&]
[s7; &]
[s7; struct Integer : public Number `{&]
[s7; -|int n;&]
[s7; -|virtual double Get() const `{ return n; `}&]
[s7; &]
[s7; -|Integer() `{`}&]
[s7; `};&]
[s7; &]
[s7; struct Double : public Number `{&]
[s7; -|double n;&]
[s7; -|virtual double Get() const `{ return n; `}&]
[s7; &]
[s7; -|Double() `{`}&]
[s7; `};&]
[s7; &]
[s7; bool operator<(const Number`& a, const Number`& b)&]
[s7; `{&]
[s7; -|return a.Get() < b.Get();&]
[s7; `}&]
[s7; &]
[s5; In this case, elements are added using Add with pointer to base 
element type parameter. Do not be confused by new and pointer, 
Array takes ownership of passed object and  behaves like container 
of base type elements&]
[s7; -|Array<Number> num;&]
[s7; -|num.Create<Double>().n `= 15.5;&]
[s7; -|num.Create<Integer>().n `= 3;&]
[s17;  num `= `{ 15.5, 3 `}&]
[s5; Thanks to well defined algorithm requirements, you can e.g. 
directly apply Sort on such Array&]
[s7; -|bool operator<(const Number`& a, const Number`& b)&]
[s7; -|`{&]
[s7; -|-|return a.Get() < b.Get();&]
[s7; -|`}&]
[s7; &]
[s7; .......&]
[s7; &]
[s7; -|Sort(num);&]
[s17;  num `= `{ 3, 15.5 `}&]
[s3; 7. Bidirectional containers&]
[s5; Vector and Array containers allow fast adding and removing elements 
at the end of sequence. Sometimes, same is needed at begin of 
sequence too (usually to support FIFO like operations). In such 
case, BiVector and BiArray should be used&]
[s7; -|BiVector<int> n;&]
[s7; -|n.[* AddHead](1);&]
[s7; -|n.[* AddTail](2);&]
[s7; -|n.AddHead(3);&]
[s7; -|n.AddTail(4);&]
[s17;  n `= `{ 3, 1, 2, 4 `}&]
[s7; -|n.[* DropHead]();&]
[s17;  n `= `{ 1, 2, 4 `}&]
[s7; -|n.[* DropTail]();&]
[s17;  n `= `{ 1, 2 `}&]
[s7; -|BiArray<Number> num;&]
[s7; -|num.CreateHead<Integer>().n `= 3;&]
[s7; -|num.CreateTail<Double>().n `= 15.5;&]
[s7; -|num.CreateHead<Double>().n `= 2.23;&]
[s7; -|num.CreateTail<Integer>().n `= 2;&]
[s17;  num `= `{ 2.23, 3, 15.5, 2 `}&]
[s3; 8. Index&]
[s5; Index is a container very similar to the plain Vector (it is 
random access array of elements with fast addition at the end) 
with one unique feature `- it is able to fast retrieve position 
of element with required value using [* Find] method&]
[s7; -|[* Index]<String> ndx;&]
[s7; -|ndx.[* Add](`"alfa`");&]
[s7; -|ndx.Add(`"beta`");&]
[s7; -|ndx.Add(`"gamma`");&]
[s7; -|ndx.Add(`"delta`");&]
[s7; -|ndx.Add(`"kappa`");&]
[s17;  ndx `= `{ alfa, beta, gamma, delta, kappa `}&]
[s7; -|DUMP(ndx.[* Find](`"beta`"));&]
[s17;  ndx.Find(`"beta`") `= 1&]
[s5; If element is not present in Index, Find returns a negative 
value&]
[s7; -|DUMP(ndx.Find(`"something`"));&]
[s17;  ndx.Find(`"something`") `= `-1&]
[s5; Any element can be replaced using [* Set] method&]
[s7; -|ndx.[* Set](0, `"delta`");&]
[s17;  ndx `= `{ delta, beta, gamma, delta, kappa `}&]
[s5; If there are more elements with the same value, they can be 
iterated using [* FindNext] method&]
[s7; -|int fi `= ndx.Find(`"delta`");&]
[s7; -|while(fi >`= 0) `{&]
[s7; -|-|DUMP(fi);&]
[s7; -|-|fi `= ndx.[* FindNext](fi);&]
[s7; -|`}&]
[s7; -|cout << `'n`';&]
[s17;  0 3-|&]
[s5; [* FindAdd] method retrieves position of element like Find, but 
if element is not present in Index, it is added&]
[s7; -|DUMP(ndx.[* FindAdd](`"one`"));&]
[s7; -|DUMP(ndx.FindAdd(`"two`"));&]
[s7; -|DUMP(ndx.FindAdd(`"three`"));&]
[s7; -|DUMP(ndx.FindAdd(`"two`"));&]
[s7; -|DUMP(ndx.FindAdd(`"three`"));&]
[s7; -|DUMP(ndx.FindAdd(`"one`"));&]
[s7; &]
[s16;  ndx.FindAdd(`"one`") `= 5&]
[s16;  ndx.FindAdd(`"two`") `= 6&]
[s16;  ndx.FindAdd(`"three`") `= 7&]
[s16;  ndx.FindAdd(`"two`") `= 6&]
[s16;  ndx.FindAdd(`"three`") `= 7&]
[s16;  ndx.FindAdd(`"one`") `= 5&]
[s5; Removing elements from random access sequence is always expensive, 
that is why rather than remove, Index supports [* Unlink] and [* UnlinkKey 
]operations, which leave element in Index but make it invisible 
for Find operation&]
[s7; -|ndx.[* Unlink](2);&]
[s7; -|ndx.[* UnlinkKey](`"kappa`");&]
[s7; &]
[s7; -|DUMP(ndx.Find(ndx`[2`]));&]
[s7; -|DUMP(ndx.Find(`"kappa`"));&]
[s7; &]
[s16;  ndx.Find(ndx`[2`]) `= `-1&]
[s16;  ndx.Find(`"kappa`") `= `-1&]
[s5; You can test whether element at given position is unlinked using 
[* IsUnlinked] method&]
[s7; -|DUMP(ndx.[* IsUnlinked](1));&]
[s7; -|DUMP(ndx.IsUnlinked(2));&]
[s7; &]
[s16;  ndx.IsUnlinked(1) `= 0&]
[s16;  ndx.IsUnlinked(2) `= 1&]
[s5; Unlinked positions can be reused by [* Put] method&]
[s7; -|ndx.[* Put](`"foo`");&]
[s17;  ndx `= `{ delta, beta, foo, delta, kappa, one, two, three `}&]
[s7; -|DUMP(ndx.Find(`"foo`"));&]
[s17;  ndx.Find(`"foo`") `= 2&]
[s5; You can also remove all unlinked elements from Index using [* Sweep] 
method&]
[s7; -|ndx.Sweep();&]
[s17;  ndx `= `{ delta, beta, foo, delta, one, two, three `}&]
[s5; As we said, operations directly removing or inserting elements 
of Index are very expensive, but sometimes this might not matter, 
so they are available too&]
[s7; -|ndx.[* Remove](1);&]
[s17;  ndx `= `{ delta, foo, delta, one, two, three `}&]
[s7; -|ndx.[* RemoveKey](`"two`");&]
[s17;  ndx `= `{ delta, foo, delta, one, three `}&]
[s7; -|ndx.[* Insert](0, `"insert`");&]
[s17;  ndx `= `{ insert, delta, foo, delta, one, three `}&]
[s5; Finally, [* PickKeys] operation allows you to obtain Vector of 
elements of Index in low constant time operation (while destroying 
source Index)&]
[s7; -|Vector<String> d `= ndx.[* PickKeys]();&]
[s7; -|Sort(d);&]
[s17;  d `= `{ delta, delta, foo, insert, one, three `}&]
[s3; 9. Index and client types&]
[s5; In order to store elements to Index, they must be moveable (you 
can use [* ArrayIndex] for types that are not) and they must have 
defined the operator`=`= and a function to compute hash value. 
Notice usage THE of [* CombineHash] to combine hash values of types 
already known to U`+`+ into final result&]
[s7; &]
[s7; struct Person : Moveable<Person> `{&]
[s7; -|String name;&]
[s7; -|String surname;&]
[s7; &]
[s7; -|unsigned [* GetHashValue]() const          `{ return [* CombineHash](name, 
surname); `}&]
[s7; -|bool [* operator`=`=](const Person`& b) const `{ return name 
`=`= b.name `&`& surname `=`= b.surname; `}&]
[s7; &]
[s7; -|Person(String name, String surname) : name(name), surname(surname) 
`{`}&]
[s7; -|Person() `{`}&]
[s7; `};&]
[s7; &]
[s7; .......&]
[s7; &]
[s7; -|Index<Person> p;&]
[s7; -|p.Add(Person(`"John`", `"Smith`"));&]
[s7; -|p.Add(Person(`"Paul`", `"Carpenter`"));&]
[s7; -|p.Add(Person(`"Carl`", `"Engles`"));&]
[s7; -|      &]
[s7; -|DUMP(p.Find(Person(`"Paul`", `"Carpenter`")));&]
[s17;  p.Find(Person(`"Paul`", `"Carpenter`")) `= 1&]
[s3; 10. VectorMap, ArrayMap&]
[s5; VectorMap is nothing more than a simple composition of Index 
and Vector. You can use [* Add] methods to put elements into the 
VectorMap&]
[s7; -|[* VectorMap]<String, Person> m;&]
[s7; -|&]
[s7; -|m.[* Add](`"1`", Person(`"John`", `"Smith`"));&]
[s7; -|m.Add(`"2`", Person(`"Carl`", `"Engles`"));&]
[s7; &]
[s7; -|Person`& p `= m.[* Add](`"3`");&]
[s7; -|p.name `= `"Paul`";&]
[s7; -|p.surname `= `"Carpenter`";&]
[s5; VectorMap provides constant access to its underlying Index and 
Vector&]
[s7; -|DUMP(m.[* GetKeys]());&]
[s7; -|DUMP(m.[* GetValues]());&]
[s7; &]
[s16; m.GetKeys() `= `{ 1, 2, 3 `}&]
[s16; m.GetValues() `= `{ John Smith, Carl Engles, Paul Carpenter 
`}&]
[s7; &]
[s5; You can use indices to iterate map contents&]
[s7; -|for(int i `= 0; i < m.GetCount(); i`+`+)&]
[s7; -|-|LOG(m.[* GetKey](i) << `": `" << m[* `[]i[* `]]);&]
[s7; &]
[s16; 1: John Smith&]
[s16; 2: Carl Engles&]
[s16; 3: Paul Carpenter&]
[s7; &]
[s5; You can use [* Find] method to retrieve position of element with 
required key&]
[s7; -|DUMP(m.[* Find](`"2`"));&]
[s17; m.Find(`"2`") `= 1&]
[s5; or [* Get] method to retrieve corresponding value&]
[s7; -|DUMP(m.[* Get](`"2`"));&]
[s17; m.Get(`"2`") `= Carl Engles&]
[s5; Passing key not present in VectorMap as Get parameter is a logic 
error, but there exists two parameter version that returns second 
parameter if key is not in VectorMap&]
[s7; -|DUMP(m.Get(`"33`", Person(`"unknown`", `"person`")));&]
[s17; m.Get(`"33`", Person(`"unknown`", `"person`")) `= unknown person&]
[s5; As with Index, you can use [* Unlink] to make elements invisible 
for Find operations&]
[s7; -|m.Unlink(1);&]
[s7; -|DUMP(m.Find(`"2`"));&]
[s17; m.Find(`"2`") `= `-1&]
[s5; You can use [* SetKey] method to change the key of the element&]
[s7; -|m.[* SetKey](1, `"33`");&]
[s7; -|DUMP(m.Get(`"33`", Person(`"unknown`", `"person`")));&]
[s17; m.Get(`"33`", Person(`"unknown`", `"person`")) `= Carl Engles&]
[s5; If there are more elements with the same key in VectorMap, you 
can iterate them using [* FindNext] method&]
[s7; -|m.Add(`"33`", Person(`"Peter`", `"Pan`"));&]
[s7; &]
[s16; m.GetKeys() `= `{ 1, 33, 3, 33 `}&]
[s16; m.GetValues() `= `{ John Smith, Carl Engles, Paul Carpenter, 
Peter Pan `}&]
[s7; &]
[s7; -|int q `= m.Find(`"33`");&]
[s7; -|while(q >`= 0) `{&]
[s7; -|-|cout << m`[q`] << `'n`';&]
[s7; -|-|q `= m.[* FindNext](q);&]
[s7; -|`}&]
[s7; -|&]
[s16; Carl Engles&]
[s16; Peter Pan&]
[s7; &]
[s5; You can reuse unlinked positions using [* Put] method&]
[s7; -|m.[* UnlinkKey](`"33`");&]
[s7; -|m.[* Put](`"22`", Person(`"Ali`", `"Baba`"));&]
[s7; -|m.Put(`"44`", Person(`"Ivan`", `"Wilks`"));&]
[s7; &]
[s16; m.GetKeys() `= `{ 1, 22, 3, 44 `}&]
[s16; m.GetValues() `= `{ John Smith, Ali Baba, Paul Carpenter, Ivan 
Wilks `}&]
[s7; &]
[s5; [* GetSortOrder] algorithm returns order of elements as Vector<int> 
container. You can use it to order content of VectorMap without 
actually moving its elements&]
[s7; -|bool operator<(const Person`& a, const Person`& b)&]
[s7; -|`{&]
[s7; -|-|return a.surname `=`= b.surname ? a.name < b.name&]
[s7; -|                              : a.surname < b.surname;&]
[s7; -|`}&]
[s7; &]
[s7; .......&]
[s7; &]
[s7; -|Vector<int> order `= [* GetSortOrder](m.GetValues());&]
[s17; order `= `{ 1, 2, 0, 3 `}&]
[s7; -|for(int i `= 0; i < order.GetCount(); i`+`+)&]
[s7; -|-|cout << m.GetKey(order`[i`]) << `": `" << m`[order`[i`]`] << 
`'n`';&]
[s7; &]
[s16; 22: Ali Baba&]
[s16; 3: Paul Carpenter&]
[s16; 1: John Smith&]
[s16; 44: Ivan Wilks&]
[s7; &]
[s5; You can get Vector of values or keys using [* PickValues] resp. 
[* PickKeys] methods in low constant time, while destroying content 
of source VectorMap&]
[s7; -|Vector<Person> ps `= m.[* PickValues]();&]
[s17; ps `= `{ John Smith, Ali Baba, Paul Carpenter, Ivan Wilks `}&]
[s5; If type of values does not satisfy requirements for Vector elements 
or if references to elements are needed, you can use [* ArrayMap] 
instead&]
[s7; -|[* ArrayMap]<String, Number> am;&]
[s7; -|am.Create<Integer>(`"A`").n `= 11;&]
[s7; -|am.Create<Double>(`"B`").n `= 2.1;&]
[s7; &]
[s16; am.GetKeys() `= `{ A, B `}&]
[s16; am.GetValues() `= `{ 11, 2.1 `}&]
[s7; &]
[s7; -|DUMP(am.Get(`"A`"));&]
[s7; -|DUMP(am.Find(`"B`"));&]
[s7; &]
[s16; am.Get(`"A`") `= 11&]
[s16; am.Find(`"B`") `= 1&]
[s16; &]
[s3; 11. One&]
[s5; One is a container that can store none or one element of T or 
derived from T. It functionally quite similiar to std`::unique`_ptr, 
but has some more convenient features (like Create method).&]
[s7; struct Base `{&]
[s7; -|virtual String Get() `= 0;&]
[s7; -|virtual `~Base() `{`}&]
[s7; `};&]
[s7; &]
[s7; struct Derived1 : Base `{&]
[s7; -|virtual String Get() `{ return `"Derived1`"; `}&]
[s7; `};&]
[s7; &]
[s7; struct Derived2 : Base `{&]
[s7; -|virtual String Get() `{ return `"Derived2`"; `}&]
[s7; `};&]
[s7; &]
[s7; void MakeDerived1(One<Base>`& t)&]
[s7; `{&]
[s7; -|t.Create<Derived1>();&]
[s7; `}&]
[s7; &]
[s7; void MakeDerived2(One<Base>`& t)&]
[s7; `{&]
[s7; -|t.Create<Derived2>();&]
[s7; `}&]
[s7; &]
[s7; .......&]
[s7; -|[* One]<Base> s;&]
[s5; Operator bool of one returns true if it contains an element:&]
[s7; -|DUMP([* (bool)]s);&]
[s7; &]
[s16; (bool)s `= false&]
[s7; &]
[s7; -|&]
[s7; -|s.[* Create]<Derived1>();&]
[s7; -|DUMP((bool)s);&]
[s7; -|DUMP(s`->Get());&]
[s7; &]
[s16; (bool)s `= true&]
[s16; s`->Get() `= Derived1&]
[s7; &]
[s5; Clear method removes the element from One:&]
[s7; -|s.[* Clear]();&]
[s7; -|DUMP((bool)s);&]
[s7; &]
[s16; (bool)s `= false&]
[s7; &]
[s7; &]
[s5; One represents a convenient and recommended method how to deal 
with class factories in U`+`+: Define them as a function (or method) 
with reference to One parameter, e.g.:&]
[s7; void MakeDerived1(One<Base>`& t)&]
[s7; `{&]
[s7; -|t.Create<Derived1>();&]
[s7; `}&]
[s7; &]
[s7; void MakeDerived2(One<Base>`& t)&]
[s7; `{&]
[s7; -|t.Create<Derived2>();&]
[s7; `}&]
[s7; &]
[s7; VectorMap<int, void (`*)(One<Base>`&)> factories;&]
[s7; &]
[s7; INITBLOCK `{&]
[s7; -|factories.Add(0, MakeDerived1);&]
[s7; -|factories.Add(1, MakeDerived2);&]
[s7; `};&]
[s7; &]
[s7; void Create(One<Base>`& t, int what)&]
[s7; `{&]
[s7; -|(`*factories.Get(what))(t);&]
[s7; `}&]
[s7; &]
[s3; 12. Any&]
[s5; Any is a container that can contain none or one element of [*/ any] 
type, the only requirement is that the type has default constructor. 
Important thing to remember is that [* Is] method matches [/ exact] 
type ignoring class hierarchies (FileIn is derived from Stream, 
but if Any contains FileIn, Is<Stream>() returns false).&]
[s7; void Do([* Any]`& x)&]
[s7; `{&]
[s7; -|if(x.[* Is]<String>())&]
[s7; -|-|LOG(`"String: `" << x.[* Get]<String>());&]
[s7; -|if(x.[* Is]<FileIn>()) `{&]
[s7; -|-|LOG(`"`-`-`- File: `");&]
[s7; -|-|LOG(LoadStream(x.[* Get]<FileIn>()));&]
[s7; -|-|LOG(`"`-`-`-`-`-`-`-`-`-`-`");&]
[s7; -|`}&]
[s7; -|if(x.[* IsEmpty]())&]
[s7; -|-|LOG(`"empty`");&]
[s7; `}&]
[s7; &]
[s7; .....&]
[s7; &]
[s7; -|Any x;&]
[s7; -|x.[* Create]<String>() `= `"Hello!`";&]
[s7; -|Do(x);&]
[s7; -|x.[* Create]<FileIn>().Open(GetDataFile(`"Ntl12.cpp`"));&]
[s7; -|Do(x);&]
[s7; -|x.[* Clear]();&]
[s7; -|Do(x);&]
[s7; &]
[s3; 13. InVector, InArray&]
[s5; InVector and InArray are vector types quite similar to Vector/Array, 
but they trade the speed of operator`[`] with the ability to 
insert or remove elements at any position quickly. You can expect 
operator`[`] to be about 10 times slower than in Vector (but 
that is still very fast), while Insert at any position scales 
well up to hundreds of megabytes of data (e.g. InVector containing 
100M of String elements is handled without problems).&]
[s7; -|[* InVector]<int> v;&]
[s7; -|for(int i `= 0; i < 1000000; i`+`+)&]
[s7; -|-|v.Add(i);&]
[s7; -|v.[* Insert](0, `-1); // This is fast&]
[s7; &]
[s5; While the interface of InVector/InArray is almost identical 
to Vector/Array, InVector/InArray in addition implements FindLowerBound/FindUpper
Bound functions `- while normal random access algorithms work, 
it is possible to provide InVector specific optimization that 
basically matches the performace of Find`*Bound on sample Vector.&]
[s7; &]
[s7; -|DUMP(v.[* FindLowerBound](55));&]
[s7; &]
[s3; 14. SortedIndex, SortedVectorMap, SortedArrayMap&]
[s5; SortedIndex is similar to regular Index, but keeps its elements 
in sorted order (sorting predicate is a template parameter, defaults 
to StdLess). Implementation is using InVector, so it works fine 
even with very large number of elements (performance is similar 
to tree based std`::set). Unlike Index, SortedIndex provides lower/upper 
bounds searches, so it allow range search.&]
[s7; -|[* SortedIndex]<int> x;&]
[s7; -|x.Add(5);&]
[s7; -|x.Add(3);&]
[s7; -|x.Add(7);&]
[s7; -|x.Add(1);&]
[s7; -|&]
[s7; -|DUMPC(x);&]
[s7; -|DUMP(x.[* Find](3));&]
[s7; -|DUMP(x.[* Find](3));&]
[s7; -|DUMP(x.[* FindLowerBound](3));&]
[s7; -|DUMP(x.[* FindUpperBound](6));&]
[s7; &]
[s5; SortedVectorMap and SortedArrayMap are then SortedIndex based 
equivalents to VectorMap/ArrayMap `- maps that keep keys sorted:&]
[s7; -|[* SortedVectorMap]<String, int> m;&]
[s7; -|m.Add(`"zulu`", 11);&]
[s7; -|m.Add(`"frank`", 12);&]
[s7; -|m.Add(`"alfa`", 13);&]
[s7; -|&]
[s7; -|DUMPM(m);&]
[s7; -|DUMP(m.[* Get](`"zulu`"));&]
[s7; &]
[s3; 15. Tuples&]
[s5; U`+`+ has template classes Tuple2, Tuple3 and Tuple4 for combining 
2`-4 values with different types. These are quite similiar to 
std`::tuple class, with some advantages.&]
[s5; To create a Tuple value, you can use the Tuple function. If 
correct types canot be deduced from parameters, you can specify 
them explicitly:&]
[s7; -|Tuple3<int, String, String> x `= [* Tuple]<int, String, String>(12, 
`"hello`", `"world`");&]
[s7; &]
[s5; Individual values are accessible as members a .. d:&]
[s7; &]
[s7; -|DUMP(x.a);&]
[s7; -|DUMP(x.b);&]
[s7; -|DUMP(x.c);&]
[s7; -|&]
[s5; As long as all individual types have conversion to String (AsString), 
the tuple also has such conversion and thus can e.g. be easily 
logged:&]
[s7; &]
[s7; -|DUMP(x);&]
[s7; &]
[s5; Also, as long as individual types have defined GetHashValue, 
so does Tuple:&]
[s7; &]
[s7; -|DUMP(GetHashValue(x));&]
[s7; &]
[s5; As long as individual types have defined operator`=`=, Tuple 
has defined operator`=`= and operator!`=&]
[s7; &]
[s7; -|Tuple3<int, String, String> y `= x;&]
[s7; -|DUMP(x !`= y);&]
[s7; &]
[s5; Finally, as long as all individual types have defined SgnCompare 
(most U`+`+ types have), Tuple has SgnCompare, Compare method 
and operators <, <`=, >, >`=:&]
[s7; &]
[s7; -|DUMP(x.Compare(y));&]
[s7; -|&]
[s7; -|y.b `= `"a`";&]
[s7; -|&]
[s7; -|DUMP(SgnCompare(x, y));&]
[s7; -|DUMP(x < y);&]
[s7; -|&]
[s7; &]
[s5; U`+`+ Tuples are strictly designed as POD type, which allows 
POD arrays to be intialized with classic C style:&]
[s7; -|static Tuple2<int, const char `*> map`[`] `= `{&]
[s7; -|-|`{ 1, `"one`" `},&]
[s7; -|-|`{ 2, `"one`" `},&]
[s7; -|-|`{ 3, `"one`" `},&]
[s7; -|`};&]
[s7; -|&]
[s5; &]
[s5; Simple FindTuple template function is provided to search for 
tuple based on the first value:&]
[s7; &]
[s3; 15. Sorting&]
[s5; IndexSort is sort variant that is able to sort two random access 
container (like Vector or Array) of the same size, based on values 
in on of containers:&]
[s7; -|Vector<int> a;&]
[s7; -|Vector<String> b;-|&]
[s7; -|&]
[s7; -|a << 5 << 10 << 2 << 9 << 7 << 3;&]
[s7; -|b << `"five`" << `"ten`" << `"two`" << `"nine`" << `"seven`" 
<< `"three`";&]
[s7; -|&]
[s7; -|[* IndexSort](a, b);&]
[s7; &]
[s16; a `= `[2, 3, 5, 7, 9, 10`]&]
[s16; b `= `[two, three, five, seven, nine, ten`]&]
[s7; &]
[s7; -|[* IndexSort](b, a);&]
[s7; &]
[s16; a `= `[5, 9, 7, 10, 3, 2`]&]
[s16; b `= `[five, nine, seven, ten, three, two`]&]
[s5; Order of sorted items is defined by sorting predicate. By default, 
operator< comparing items of container is used (this predicate 
can be provided by StdLess template), but it is possible to specify 
different sorting order, e.g. by using predefined StdGreater 
predicate:&]
[s7; -|Sort(a, [* StdGreater]<int>());&]
[s7; &]
[s16; a `= `[10, 9, 7, 5, 3, 2`]&]
[s5; Sometimes, instead of sorting items in the container, it is 
useful to know the order of items as sorted, using GetSortOrder:&]
[s7; -|Vector<int> o `= [* GetSortOrder](a);&]
[s7; &]
[s16; o `= `[5, 4, 3, 2, 1, 0`]&]
[s5; FieldRelation predefined predicate can be used to sort container 
of structures by specific field:&]
[s7; -|Vector<Point> p;&]
[s7; -|p << Point(5, 10) << Point(7, 2) << Point(4, 8) << Point(1, 
0);&]
[s7; -|&]
[s7; -|Sort(p, [* FieldRelation](`&Point`::x, StdLess<int>()));&]
[s7; &]
[s16; p `= `[`[1, 0`], `[4, 8`], `[5, 10`], `[7, 2`]`]&]
[s5; MethodRelation is good for sorting of structures based on constant 
method of structure:-|&]
[s7; struct Foo `{&]
[s7; -|String a;&]
[s7; -|&]
[s7; -|int [* Get]() const `{ return atoi(a); `}&]
[s7; -|....&]
[s7; `};&]
[s7; ....&]
[s7; -|Array<Foo> f;&]
[s7; -|f << `"12`" << `"1`" << `"10`" << `"7`" << `"5`";&]
[s7; -|&]
[s7; -|Sort(f, [* MethodRelation](`&Foo`::[* Get], StdLess<int>()));&]
[s7; &]
[s16; f `= `[1, 5, 7, 10, 12`]&]
[s5; Normal Sort is not stable `- equal items can appear in sorted 
sequence in random order. If maintaining original order of equal 
items is important, use StableSort variant (with slight performance 
penalty):&]
[s7; -|Vector<Point> t;&]
[s7; -|t << Point(10, 10) << Point(7, 1) << Point(7, 2) << Point(7, 
3) << Point(1, 0);&]
[s7; -|[* StableSort](t, FieldRelation(`&Point`::x, StdLess<int>()));&]
[s7; &]
[s16; t `= `[`[1, 0`], `[7, 1`], `[7, 2`], `[7, 3`], `[10, 10`]`]&]
[s7; ]]