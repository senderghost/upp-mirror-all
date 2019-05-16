topic "Date and Time";
[2 $$0,0#00000000000000000000000000000000:Default]
[i448;a25;kKO9;2 $$1,0#37138531426314131252341829483380:class]
[l288;2 $$2,2#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[H6;0 $$4,0#05600065144404261032431302351956:begin]
[i448;a25;kKO9;2 $$5,0#37138531426314131252341829483370:item]
[l288;a4;*@5;1 $$6,6#70004532496200323422659154056402:requirement]
[l288;i1121;b17;O9;~~~.1408;2 $$7,0#10431211400427159095818037425705:param]
[i448;b42;O9;2 $$8,8#61672508125594000341940100500538:tparam]
[b42;2 $$9,9#13035079074754324216151401829390:normal]
[{_} 
[ {{10000@(113.42.0) [s0;%% [*@7;4 Date]]}}&]
[s3;%% &]
[s1;:Date`:`:struct: [@(0.0.255)3 struct][3 _][*3 Date][3 _:_][@(0.0.255)3 public][3 _][*@3;3 RelOps
][3 <_][*3 Date][3 , ][_^Moveable^3 Moveable][3 <][*3 Date][3 >_>_]&]
[s9;%% A simple date object with up to a day precision.&]
[s3; &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s3; &]
[s5;:Date`:`:Date`(`): [* Date]()&]
[s2;%% Default constructor.&]
[s3; &]
[s4; &]
[s5;:Date`:`:Date`(const Nuller`&`): [* Date]([@(0.0.255) const]_[_^Nuller^ Nuller][@(0.0.255) `&
])&]
[s2;%% Construct an empty date.&]
[s3; &]
[s4; &]
[s5;:Date`:`:Date`(int`,int`,int`): [* Date]([@(0.0.255) int]_[*@3 y], 
[@(0.0.255) int]_[*@3 m], [@(0.0.255) int]_[*@3 d])&]
[s2;%% Constructs a date based on [%-*@3 y] [%-*@3 m] [%-*@3 d].&]
[s3;%% &]
[s3;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Member List]]}}&]
[s3; &]
[s5;:Date`:`:day: [_^byte^ byte]_[* day]&]
[s2;%% Day.&]
[s3;%% &]
[s4; &]
[s5;:Date`:`:month: [_^byte^ byte]_[* month]&]
[s2;%% Month.&]
[s3; &]
[s4; &]
[s5;:Date`:`:year: [_^int16^ int16]_[* year]&]
[s2;%% Year.&]
[s3; &]
[s4; &]
[s5;:Date`:`:Serialize`(Stream`&`): [@(0.0.255) void]_[* Serialize]([_^Stream^ Stream][@(0.0.255) `&
]_[*@3 s])&]
[s2;%% Serializes Date to/from [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:Date`:`:IsValid`(`)const: [@(0.0.255) bool]_[* IsValid]()_[@(0.0.255) const]&]
[s2;%% Returns true if the date is valid.&]
[s3; &]
[s4; &]
[s5;:Date`:`:Set`(int`): [@(0.0.255) void]_[* Set]([@(0.0.255) int]_[*@3 scalar])&]
[s2;%% Assign a date that is stored in the numeric [%-*@3 scalar].&]
[s3;%% &]
[s4; &]
[s5;:Date`:`:Get`(`)const: [@(0.0.255) int]_[* Get]()_[@(0.0.255) const]&]
[s2;%% Converts the time into a numeric value.&]
[s3; &]
[s4; &]
[s5;:Date`:`:Compare`(Date`)const: [@(0.0.255) int]_[* Compare]([_^Date^ Date]_[*@3 b])_[@(0.0.255) c
onst]&]
[s2;%% Compares Date with [%-*@3 b], returns `-1 if <b, 0 if `=`= b, 
1 if > b.&]
[s3;%% &]
[s4; &]
[s5;:Date`:`:Low`(`): [@(0.0.255) static] [_^Date^ Date]_[* Low]()&]
[s2;%% Returns the lowest possible date (year 4000).&]
[s3; &]
[s4; &]
[s5;:Date`:`:High`(`): [@(0.0.255) static] [_^Date^ Date]_[* High]()&]
[s2;%% Returns the highest possible date (year 4000).&]
[s3; &]
[s0; &]
[s0; &]
[s0; &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 Time]]}}&]
[s3; &]
[s1;:Time`:`:struct: [@(0.0.255)3 struct][3 _][*3 Time][3 _:_][@(0.0.255)3 public][3 _][*@3;3 Date][3 ,
 ][@(0.0.255)3 public][3 _][*@3;3 RelOps][3 <_][*3 Time][3 , ][_^Moveable^3 Moveable][3 <][*3 Time][3 >
_>_]&]
[s9;%% A simple date time object with up to a second precision.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s3; &]
[s5;:Time`:`:Time`(`): [* Time]()&]
[s2;%% Default constructor.&]
[s3; &]
[s4; &]
[s5;:Time`:`:Time`(const Nuller`&`): [* Time]([@(0.0.255) const]_[_^Nuller^ Nuller][@(0.0.255) `&
])&]
[s2;%% Construcs an empty time.&]
[s3;%% &]
[s4; &]
[s5;:Time`:`:Time`(int`,int`,int`,int`,int`,int`): [* Time]([@(0.0.255) int]_[*@3 y], 
[@(0.0.255) int]_[*@3 m], [@(0.0.255) int]_[*@3 d], [@(0.0.255) int]_[*@3 h]_`=_[@3 0], 
[@(0.0.255) int]_[*@3 n]_`=_[@3 0], [@(0.0.255) int]_[*@3 s]_`=_[@3 0])&]
[s2;%% Constructs a time based on [%-*@3 y] [%-*@3 m] [%-*@3 d] [%-*@3 h] 
[%-*@3 n] [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:Time`:`:Time`(FileTime`): [* Time]([_^FileTime^ FileTime]_[*@3 filetime])&]
[s2;%% Constructs based on a platform specific [%-*@3 filetime].&]
[s3;%% &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Member List]]}}&]
[s3; &]
[s5;:Time`:`:hour: [_^byte^ byte]_[* hour]&]
[s2;%% Hour.&]
[s3; &]
[s4; &]
[s5;:Time`:`:minute: [_^byte^ byte]_[* minute]&]
[s2;%% Minute.&]
[s3; &]
[s4; &]
[s5;:Time`:`:second: [_^byte^ byte]_[* second]&]
[s2;%% Second.&]
[s3; &]
[s4; &]
[s5;:Time`:`:High`(`): [@(0.0.255) virtual] [@(0.0.255) static] [_^Time^ Time]_[* High]()&]
[s2;%% Returns the highest possible time (year 4000).&]
[s3; &]
[s4; &]
[s5;:Time`:`:Low`(`): [@(0.0.255) virtual] [@(0.0.255) static] [_^Time^ Time]_[* Low]()&]
[s2;%% Returns the lowest possible time (year `-4000).&]
[s3; &]
[s4; &]
[s5;:Time`:`:Set`(int64`): [@(0.0.255) void]_[* Set]([_^int64^ int64]_[*@3 scalar])&]
[s2;%% Assign a time that is stored in the numeric [%-*@3 scalar].&]
[s3;%% &]
[s4; &]
[s5;:Time`:`:Get`(`)const: [@(0.0.255) virtual] [_^int64^ int64]_[* Get]()_[@(0.0.255) const]&]
[s2;%% Converts the time into a numeric value.&]
[s3; &]
[s4; &]
[s5;:Time`:`:AsFileTime`(`)const: [_^FileTime^ FileTime]_[* AsFileTime]()_[@(0.0.255) const
]&]
[s2;%% Converst the time into a system specific value.&]
[s3; &]
[s0; ]