topic "Vector";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[*C+75 $$10,10#20308344770720113750957135429985:code]
[{_}%EN-US 
[s1; [*@3;4 Vector]&]
[s1;:noref:%- [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 T][@(0.0.255)3 >]&]
[s1;:Vector`:`:class:%- [@(0.0.255) class]_[* Vector]_:_[@(0.0.255) public]_[*@3 MoveableAndDe
epCopyOption][@(0.0.255) <]_[* Vector][@(0.0.255) <][*@4 T][@(0.0.255) >]_>&]
[s8; [*C@4 T]-|Type of elements stored in Vector. T is required to be 
[*/^topic`:`/`/Core`/srcdoc`/Moveable`$en`-us^ moveable][*/  ]and 
must have either [*/^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ deep 
copy constructor], [*/^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ pick 
constructor] or [*/ default constructor].&]
[s9; The most effective flavor of basic random access container. 
Its features are derived from fact that it is implemented as 
simple C`-like vector of elements.&]
[s9; Disadvantage of Vector is common requirement for elements to 
be stored in it `- they must be [*/^topic`:`/`/Core`/srcdoc`/Moveable`$en`-us^ move
able]. Another disadvantage is fact that many operations invalidate 
references (that means C`+`+ references and pointers) to elements.&]
[s9; Like any other NTL container, Vector is [*/^topic`:`/`/Core`/srcdoc`/Moveable`$en`-us^ m
oveable][*/  ]type with [*/^topic`:`/`/Core`/srcdoc`/pick`_`$en`-us^ pick 
and optional deep copy] transfer semantics. Calling methods of 
picked Vector is logic error with exception of&]
[s10;%- &]
[s10;%- void_operator`=([@(0.128.128) pick`_]_[_^Vector^ Vector]`&_[@3 v])&]
[s10; void operator<<`=(const Vector`& [@3 v]) [/ (defined using DeepCopyOptionTemplate)]&]
[s10;%- void_Clear()&]
[s10;%- bool_IsPicked()_const&]
[s10; &]
[s0; Optional deep copy is implemented through DeepCopyOptionTemplate 
macro.&]
[s1; &]
[ {{10000F(128)G(128)@1 [s0; [* Constructor Detail]]}}&]
[s0;%- &]
[s5;:Vector`:`:Vector`(`):%- [* Vector]()&]
[s2; Default constructor. Constructs empty Vector.&]
[s3; &]
[s4;%- &]
[s5;:Vector`:`:Vector`(pick`_ Vector`&`):%- [* Vector]([@(0.128.128) pick`_]_[* Vector][@(0.0.255) `&
]_[*@3 v])&]
[s2; Pick constructor. Transfers source Vector in low constant time, 
but destroys it by picking.&]
[s7; v-|Source Vector.&]
[s3; &]
[s4;%- &]
[s5;:Vector`:`:Vector`(const Vector`&`,int`):%- [* Vector]([@(0.0.255) const]_[* Vector][@(0.0.255) `&
]_[*@3 v], [@(0.0.255) int])&]
[s2; Optional deep copy constructor.&]
[s6; Requires T to have deep copy constructor or optional deep copy 
constructor.&]
[s2; [*C@3 v]-|Source Vector. [%-*@3 v].&]
[s3; &]
[s4;%- &]
[s5;:Vector`:`:`~Vector`(`):%- [@(0.0.255) `~][* Vector]()&]
[s2; Destructor. Calls destructors of all elements in Vector.&]
[s1; &]
[ {{10000F(128)G(128)@1 [s0; [* Public Member List]]}}&]
[s4;H0;%- &]
[s5;:Vector`:`:Add`(`):%- [*@4 T][@(0.0.255) `&]_[* Add]()&]
[s2; Adds new default constructed element to Vector.&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*/ Return value]-|Reference to newly added default constructed 
element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Add`(const T`&`):%- [@(0.0.255) void]_[* Add]([@(0.0.255) const]_[*@4 T][@(0.0.255) `&
]_[*@3 x])&]
[s2; Adds new element with specified value to Vector.&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|The value that is copied to newly created element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:AddPick`(pick`_ T`&`):%- [@(0.0.255) void]_[* AddPick]([@(0.128.128) pick`_]_
[*@4 T][@(0.0.255) `&]_[*@3 x])&]
[s2; Adds new element to Vector and picks value of parameter to it. 
&]
[s6; Requires T to have pick constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|Source instance of T that is to be picked.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:AddN`(int`):%- [@(0.0.255) void]_[* AddN]([@(0.0.255) int]_[*@3 n])&]
[s2; Adds specified number of default constructed elements to Vector.&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 n]-|Number of elements to add&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator`[`]`(int`)const:%- [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[* opera
tor`[`]]([@(0.0.255) int]_[*@3 i])_[@(0.0.255) const]&]
[s2; Returns a reference to the element at specified position.&]
[s7; [*C@3 i]-|Position of element.&]
[s7; [*/ Return value]-|Constant reference to the element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator`[`]`(int`):%- [*@4 T][@(0.0.255) `&]_[* operator`[`]]([@(0.0.255) int
]_[*@3 i])&]
[s2; Returns a reference to the element at specified position.&]
[s7; [*C@3 i]-|Position of element.&]
[s7; [*/ Return value]-|Reference to the element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:GetCount`(`)const:%- [@(0.0.255) int]_[* GetCount]()_[@(0.0.255) const]&]
[s2; Return the number of elements in Vector.&]
[s7; [*/ Return value]-|Actual number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:IsEmpty`(`)const:%- [@(0.0.255) bool]_[* IsEmpty]()_[@(0.0.255) const]&]
[s2; Tests whether Vector  is empty. Same as GetCount() `=`= 0.&]
[s7; [*/ Return value]-|true if Vector is empty, false otherwise.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Trim`(int`):%- [@(0.0.255) void]_[* Trim]([@(0.0.255) int]_[*@3 n])&]
[s2; Reduces number of elements in Vector to specified number. Required 
number must be less than or equal to actual number of elements 
in Vector.&]
[s6; Invalidates iterators to Vector.&]
[s7; [*C@3 n]-|Required number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:SetCount`(int`):%- [@(0.0.255) void]_[* SetCount]([@(0.0.255) int]_[*@3 n])&]
[s2; Changes count of elements in Vector to specified value. If required 
number of elements is greater than actual number, newly added 
elements are default constructed. If Vector has to increase capacity, 
the new capacity will exactly match required number of elements 
(unlike [* SetCountR]).&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 n]-|Required number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:SetCount`(int`,const T`&`):%- [@(0.0.255) void]_[* SetCount]([@(0.0.255) int
]_[*@3 n], [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 init])&]
[s2; Changes count of elements in Vector to specified value. If required 
number of elements is greater than actual number, newly added 
elements are initialized to specified value using copy constructor. 
If Vector has to increase capacity, the new capacity will exactly 
match required number of elements (unlike [* SetCountR]).&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 n]-|Required number of elements.&]
[s7; [*C@3 init]-|Initialization value of newly added elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:SetCountR`(int`):%- [@(0.0.255) void]_[* SetCountR]([@(0.0.255) int]_[*@3 n])&]
[s2; Changes count of elements in Vector to specified value. If required 
number of elements is greater than actual number, newly added 
elements are default constructed. If Vector has to increase capacity, 
the new capacity will be greater than required number of elements 
(unlike [* SetCount]) to allow adding other elements without further 
increasing capacity.&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 n]-|Required number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:SetCountR`(int`,const T`&`):%- [@(0.0.255) void]_[* SetCountR]([@(0.0.255) i
nt]_[*@3 n], [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 init])&]
[s2; Changes count of elements in Vector to specified value. If required 
number of elements is greater than actual number, newly added 
elements are initialized to specified value using copy constructor. 
If Vector has to increase capacity, the new capacity will be 
greater than required number of elements (unlike [* SetCount]) 
to allow adding other elements without further increasing capacity.&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 n]-|Required number of elements.&]
[s7; [*C@3 init]-|Initialization value of newly added elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Clear`(`):%- [@(0.0.255) void]_[* Clear]()&]
[s2; Removes all elements from Vector. Capacity is also cleared to 
zero.&]
[s6; Invalidates iterators and references to Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:At`(int`):%- [*@4 T][@(0.0.255) `&]_[* At]([@(0.0.255) int]_[*@3 i])&]
[s2; If specified position is lower than number of elements in Vector 
([* i < GetCount()]), returns reference to element at specified 
position. Otherwise increases number of elements in Vector to 
[* i `+ 1]. Newly added elements are default constructed. If Vector 
has to increase capacity, the new capacity will be greater than 
required number of elements to allow adding other elements without 
further increasing capacity.&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position of required element.&]
[s7; [*/ Return value]-|Reference to required element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:At`(int`,const T`&`):%- [*@4 T][@(0.0.255) `&]_[* At]([@(0.0.255) int]_[*@3 i], 
[@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 x])&]
[s2; If specified position is lower than number of elements in Vector 
([* i < GetCount()]), returns reference to element at specified 
position. Otherwise increases number of elements in Vector to 
[* i `+ 1]. Newly added elements are copy constructed from [* x]. 
If Vector has to increase capacity, the new capacity will be 
greater than required number of elements to allow adding other 
elements without further increasing capacity.&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position of required element.&]
[s7; [*C@3 x]-|Initialization value of newly added elements.&]
[s7; [*/ Return value]-|Reference to required element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Shrink`(`):%- [@(0.0.255) void]_[* Shrink]()&]
[s2; Minimizes memory consumption of Vector by decreasing capacity 
to number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Reserve`(int`):%- [@(0.0.255) void]_[* Reserve]([@(0.0.255) int]_[*@3 n])&]
[s2; Reserves capacity. If required capacity is greater than current 
capacity, capacity is increased to the required value.&]
[s7; [*C@3 xtra]-|Required capacity.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:GetAlloc`(`)const:%- [@(0.0.255) int]_[* GetAlloc]()_[@(0.0.255) const]&]
[s2; Returns current capacity of Vector.&]
[s7; [*/ Return value]-|Capacity of Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Set`(int`,const T`&`,int`):%- [@(0.0.255) void]_[* Set]([@(0.0.255) int]_[*@3 i
], [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 x], [@(0.0.255) int]_[*@3 count]_`=_[@3 1])&]
[s2; Sets requested number of elements starting at the position [* i] 
to the specified value. If required number of elements exceeds 
existing elements of Vector then elements are added to Vector.&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Starting position.&]
[s7; [*C@3 x]-|Value.&]
[s7; [*C@3 count]-|Number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Remove`(int`,int`):%- [@(0.0.255) void]_[* Remove]([@(0.0.255) int]_[*@3 i], 
[@(0.0.255) int]_[*@3 count]_`=_[@3 1])&]
[s2; Removes requested number of elements.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position.&]
[s7; [*C@3 count]-|Number of elements to remove.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Remove`(const int`*`,int`):%- [@(0.0.255) void]_[* Remove]([@(0.0.255) const
]_[@(0.0.255) int]_`*[*@3 sorted`_list], [@(0.0.255) int]_[*@3 n])&]
[s2; Removes number of elements from Vector. Time of operation almost 
does not depend on number of elements.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 sorted`_list]-|Pointer to array of positions to remove. It 
must be sorted from lowest to greatest value.&]
[s7; [*C@3 n]-|Number of elements to remove.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Remove`(const Vector`<int`>`&`):%- [@(0.0.255) void]_[* Remove]([@(0.0.255) c
onst]_[_^Vector^ Vector][@(0.0.255) <int>`&]_[*@3 sorted`_list])&]
[s2; Removes number of elements form Vector. Same as [* Remove(sorted`_list, 
sorted`_list.GetCount())].&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 sorted`_list]-|Sorted Vector of positions to remove.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:InsertN`(int`,int`):%- [@(0.0.255) void]_[* InsertN]([@(0.0.255) int]_[*@3 i],
 [@(0.0.255) int]_[*@3 count]_`=_[@3 1])&]
[s2; Inserts a specified number of default constructed elements at 
a specified position.&]
[s6; Requires T to have default constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position.&]
[s7; [*C@3 count]-|Number of elements to insert.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Insert`(int`):%- [*@4 T][@(0.0.255) `&]_[* Insert]([@(0.0.255) int]_[*@3 i])&]
[s2; Inserts one default constructed element at the specified position.&]
[s7; [*1 Requires T to have default constructor.]&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Insert`(int`,const T`&`,int`):%- [@(0.0.255) void]_[* Insert]([@(0.0.255) in
t]_[*@3 i], [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 x], [@(0.0.255) int]_[*@3 count]_`=_
[@3 1])&]
[s2; Inserts a specified number of elements, setting them to a specified 
value.&]
[s6;~~~.992; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position.&]
[s7; [*C@3 x]-|Value of inserted elements.&]
[s7; [*C@3 count]-|Number of elements to insert.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Insert`(int`,const Vector`&`):%- [@(0.0.255) void]_[* Insert]([@(0.0.255) in
t]_[*@3 i], [@(0.0.255) const]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x])&]
[s2; Inserts all elements from another Vector.&]
[s6;~~~.992; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Position.&]
[s7; [*C@3 x]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Insert`(int`,const Vector`&`,int`,int`):%- [@(0.0.255) void]_[* Insert]([@(0.0.255) i
nt]_[*@3 i], [@(0.0.255) const]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x], 
[@(0.0.255) int]_[*@3 offset], [@(0.0.255) int]_[*@3 count])&]
[s2; Inserts a range of elements from another Vector.&]
[s6;~~~.992; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Insertion position.&]
[s7; [*C@3 x]-|Source Vector.&]
[s7; [*C@3 offset]-|Position of first element in source Vector to be 
inserted.&]
[s7; [*C@3 count]-|Number of elements to insert.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:InsertPick`(int`,pick`_ Vector`&`):%- [@(0.0.255) void]_[* InsertPick]([@(0.0.255) i
nt]_[*@3 i], [@(0.128.128) pick`_]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x])&]
[s2; Inserts source Vector at specified position using pick transfer 
semantics. It is faster than deep copy insert, does not use deep 
copy constructor for T, but destroys source Vector.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 i]-|Insertion position.&]
[s7; [*C@3 x]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Append`(const Vector`&`):%- [@(0.0.255) void]_[* Append]([@(0.0.255) const]_
[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x])&]
[s2; Appends all elements of source Vector.&]
[s6;~~~.992; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Append`(const Vector`&`,int`,int`):%- [@(0.0.255) void]_[* Append]([@(0.0.255) c
onst]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x], [@(0.0.255) int]_[*@3 o], 
[@(0.0.255) int]_[*@3 c])&]
[s2; Appends a range of elements from source Vector.&]
[s6;~~~.992; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|Source Vector.&]
[s7; [*C@3 o]-|Position of first element in source Vector to be inserted.&]
[s7; [*C@3 c]-|Number of elements to insert.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:AppendPick`(pick`_ Vector`&`):%- [@(0.0.255) void]_[* AppendPick]([@(0.128.128) p
ick`_]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 x])&]
[s2; Appends source Vector using pick transfer semantics. It is faster 
than deep copy insert, does not use deep copy constructor for 
T, but destroys source Vector by picking.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Drop`(int`):%- [@(0.0.255) void]_[* Drop]([@(0.0.255) int]_[*@3 n]_`=_[@3 1])&]
[s2; Drops specified number of last elements in the Vector (same 
as Trim(GetCount() `- n)).&]
[s7; [*C@3 n]-|Number of elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Top`(`):%- [*@4 T][@(0.0.255) `&]_[* Top]()&]
[s2; Returns reference to the last element in the Vector.&]
[s7; [*/ Return value]-|Reference of last element in the Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Top`(`)const:%- [@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[* Top]()_[@(0.0.255) c
onst]&]
[s2; Returns constant reference to the last element in the Vector.&]
[s7; [*/ Return value]-|Reference of last element in the Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Pop`(`):%- [*@4 T]_[* Pop]()&]
[s2; Drops last element of Vector and returns its value.&]
[s6; Requires T to have deep copy constructor.&]
[s7; [*/ Return value]-|Value of dropped element.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator T`*`(`):%- [@(0.0.255) operator]_[*@4 T][@(0.0.255) `*]()&]
[s2; Returns non`-constant pointer to elements.&]
[s7; [*/ Return value]-|Pointer to elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator const T`*`(`)const:%- [@(0.0.255) operator]_[@(0.0.255) const]_[*@4 T
][@(0.0.255) `*]()_[@(0.0.255) const]&]
[s2; Returns constant pointer to elements.&]
[s7; [*/ Return value]-|Pointer to elements.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator`<`<`(const T`&`):%- [_^Vector^ Vector][@(0.0.255) `&]_[* operator<<
]([@(0.0.255) const]_[*@4 T][@(0.0.255) `&]_[*@3 x])&]
[s2; Operator replacement of [* void Add(const T`&x)]. By returning 
reference to to Vector allows adding more elements in single 
expression, thus e.g. allowing to construct temporary Vector 
as part of expression like Foo((Vector<int>() << 1 << 2 << 4)).&]
[s6; Requires T to have deep copy constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|The value that is copied to newly created element.&]
[s7; [*/ Return value]-|Reference to Vector (`*this).&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator`|`(pick`_ T`&`):%- [_^Vector^ Vector][@(0.0.255) `&]_[* operator`|](
[@(0.128.128) pick`_]_[*@4 T][@(0.0.255) `&]_[*@3 x])&]
[s2; Operator replacement of [* void AddPick(pick`_ T`&x)]. By returning 
reference to to Vector allows adding more elements in single 
expression, thus e.g. allowing to construct temporary Vector 
as part of expression.&]
[s6; Requires T to have pick constructor.&]
[s6; Invalidates iterators and references to Vector.&]
[s7; [*C@3 x]-|Source instance of T that is to be picked.&]
[s7; [*/ Return value]-|Reference to Vector (`*this).&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Serialize`(Stream`&`):%- [@(0.0.255) void]_[* Serialize]([_^Stream^ Stream][@(0.0.255) `&
]_[*@3 s])&]
[s2; Serializes content of Vector to/from Stream. Works only if NTL 
is used as part of UPP.&]
[s6; Requires T to have serialization operator defined.&]
[s7; [*C@3 s]-|Target/source stream.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:operator`=`(pick`_ Vector`&`):%- [@(0.0.255) void]_[* operator`=]([@(0.128.128) p
ick`_]_[_^Vector^ Vector][@(0.0.255) `&]_[*@3 v])&]
[s2; Pick operator. Transfers source Vector in low constant time, 
but destroys it by picking.&]
[s7; [*C@3 v]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:IsPicked`(`)const:%- [@(0.0.255) bool]_[* IsPicked]()_[@(0.0.255) const]&]
[s2; Returns [* true] if Vector is in picked state.&]
[s7; [*/ Return value]-|[* true] if Vector is in picked state, [* false] 
otherwise.&]
[s3;%- &]
[s4; &]
[s5;%- friend_T`&_operator<<`=[@(64) (T`&_][@3 dest][@(64) , ][@(0.0.255) const][@(64) _T`&_][@3 s
rc][@(64) )]&]
[s2; Optional deep copy operator. Defined using DeepCopyOptionTemplate.&]
[s6; Requires T to have deep copy operator or optional deep copy 
operator.&]
[s7; [*C@3 v]-|Source Vector.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:ValueType`:`:typedef:%- [@(0.0.255) typedef]_T_[* ValueType]&]
[s2; Typedef of T for use in templated algorithms.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Iterator`:`:typedef:%- [@(0.0.255) typedef]_T_`*[* Iterator]&]
[s2; Iterator type. Iterator is guaranteed to be of T`* type.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:ConstIterator`:`:typedef:%- [@(0.0.255) typedef]_[@(0.0.255) const]_T_`*[* C
onstIterator]&]
[s2; Constant iterator type. Iterator is guaranteed to be of const 
T`* type.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Begin`(`)const:%- [_^Vector`:`:ConstIterator^ ConstIterator]_[* Begin]()_[@(0.0.255) c
onst]&]
[s2; Returns constant iterator to the first element in Vector.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:End`(`)const:%- [_^Vector`:`:ConstIterator^ ConstIterator]_[* End]()_[@(0.0.255) c
onst]&]
[s2; Returns constant iterator to the position just beyond the last 
element in Vector.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:GetIter`(int`)const:%- [_^Vector`:`:ConstIterator^ ConstIterator]_[* GetIt
er]([@(0.0.255) int]_[*@3 i])_[@(0.0.255) const]&]
[s2; Returns constant iterator to the element at specified position. 
Same as [* Begin() `+ i]. Benefit of this methods is that in debug 
mode [* pos] is range checked.&]
[s7; [*C@3 i]-|Required position.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:Begin`(`):%- [_^Vector`:`:Iterator^ Iterator]_[* Begin]()&]
[s2; Returns non`-constant iterator to the first element in Vector.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:End`(`):%- [_^Vector`:`:Iterator^ Iterator]_[* End]()&]
[s2; Returns non`-constant iterator to the position just beyond the 
last element in Vector.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:Vector`:`:GetIter`(int`):%- [_^Vector`:`:Iterator^ Iterator]_[* GetIter]([@(0.0.255) i
nt]_[*@3 i])&]
[s2; Returns non`-constant iterator to the element at specified position. 
Same as [* Begin() `+ pos]. Benefit of this methods is that in 
debug mode [* pos] is range checked.&]
[s7; [*C@3 i]-|Required position.&]
[s7; [*/ Return value]-|Iterator.&]
[s3;%- &]
[s4;%- &]
[s5;:`:`:Vector`:`:Swap`(`:`:Vector`&`,`:`:Vector`&`):%- [@(0.0.255) friend]_[@(0.0.255) v
oid]_[* Swap]([_^`:`:Vector^ Vector][@(0.0.255) `&]_[*@3 a], [_^`:`:Vector^ Vector][@(0.0.255) `&
]_[*@3 b])&]
[s2; Specialization of generic [* Swap] for Vector. Swaps Vector in 
simple constant time operation.&]
[s7; [*C@3 a]-|First Vector to swap.&]
[s7; [*C@3 b]-|Second Vector to swap.&]
[s0; ]