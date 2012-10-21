topic "LRUCache";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 LRUCache]]}}&]
[s1;@(0.0.255)3 &]
[s1;:noref: [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 T][3 , 
][@(0.0.255)3 class][3 _][*@4;3 K][3 _`=_String>]&]
[s1;:LRUCache`:`:class: [@(0.0.255) class]_[* LRUCache]&]
[s2;%% This class simplifies implementation of LRU (least recently 
used) type of caches. Cache keeps the track of size of data contained 
and provides Shrink method, that reduces this size to requested 
number, removing least recently used items first. LRUCache also 
provides two size counters, `"found size`" and `"new size`", 
that can be used to further finetuning of cache.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Maker subclass]]}}&]
[s3; &]
[s5; [@(0.0.255) struct]_[* Maker]&]
[s2;%% This structure provides virtual base class for specific LRUCache 
to create requested data if not available in cache. Client code 
derives from Maker, adds required input parameters; Maker then 
provides key for the client parameter set and Make to create 
the data based on parameters.&]
[s3; &]
[s4; &]
[s5;:LRUCache`:`:Maker`:`:Key`(`)const: [@(0.0.255) virtual] [*@4 K]_[* Key]()_[@(0.0.255) co
nst]_`=_[@3 0]&]
[s2;%% Returns key based on parameters.&]
[s3; &]
[s4; &]
[s5;:LRUCache`:`:Maker`:`:Make`(T`&`)const: [@(0.0.255) virtual] [@(0.0.255) int]_[* Make](
[*@4 T][@(0.0.255) `&]_[*@3 object])_[@(0.0.255) const]_`=_[@3 0]&]
[s2;%% Creates the data based on parameters, returns the size of 
created data.&]
[s3;%% &]
[s4; &]
[s5;:LRUCache`:`:Maker`:`:`~Maker`(`): [@(0.0.255) `~][* Maker]()&]
[s2;%% Virtual destructor.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s3; &]
[s5;:LRUCache`:`:GetSize`(`)const: [@(0.0.255) int]_[* GetSize]()_[@(0.0.255) const]&]
[s2;%% Returns the total size of data in cache (as sum of numbers 
returned by Maker`::Make).&]
[s3;%% &]
[s4; &]
[s5;:LRUCache`:`:Shrink`(int`): [@(0.0.255) void]_[* Shrink]([@(0.0.255) int]_[*@3 maxsize])&]
[s2;%% Reduces the cache to contain no more than [%-*@3 maxsize] data 
removing the least recently used items first.&]
[s3;%% &]
[s4; &]
[s5;:LRUCache`:`:Get`(const LRUCache`:`:Maker`&`): [*@4 T][@(0.0.255) `&]_[* Get]([@(0.0.255) c
onst]_[_^LRUCache`:`:Maker^ Maker][@(0.0.255) `&]_[*@3 m])&]
[s2;%% Retrieves data from the cache or creates them if needed [%-*@3 m].&]
[s3;%% &]
[s4; &]
[s5;:LRUCache`:`:Clear`(`): [@(0.0.255) void]_[* Clear]()&]
[s2;%% Clears all data from the cache.&]
[s3; &]
[s4; &]
[s5;:LRUCache`:`:ClearCounters`(`): [@(0.0.255) void]_[* ClearCounters]()&]
[s2;%% Clears the value of both size counters.&]
[s3; &]
[s4; &]
[s5;:LRUCache`:`:GetFoundSize`(`)const: [@(0.0.255) int]_[* GetFoundSize]()_[@(0.0.255) con
st]&]
[s2;%% Returns the size of data that have been retrieved from the 
cache since the last ClearCounters call (or constructor if there 
was none).&]
[s3; &]
[s4; &]
[s5;:LRUCache`:`:GetNewSize`(`)const: [@(0.0.255) int]_[* GetNewSize]()_[@(0.0.255) const]&]
[s2;%% Returns the size of data that have to be created since the 
last ClearCounters call (or constructor if there was none).&]
[s3; &]
[s0;%% ]]