topic "class RealTimeStop";
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
[{_}%EN-US 
[ {{10000@(113.42.0) [s0; [*@7;4 Functions4U Reference. RealTimeStop]]}}&]
[s4;2 &]
[s1;:Upp`:`:RealTimeStop`:`:class: [@(0.0.255)3 class][3 _][*3 RealTimeStop]&]
[s2; &]
[s0; RealTimeStop class is a timer class that can be paused and set 
back.&]
[s0; In addition it monitors itself so in case that the main program 
is paused by other process or because the computer is suspended 
during minutes or hours, it readjust itself to manage just running 
time and not clock time.&]
[s3; &]
[ {{10000F(128)G(128)@1 [s0; [* Public Method List]]}}&]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:Start`(`): [@(0.0.255) void]_[* Start]()&]
[s2; Starts the timer.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:Pause`(bool`): [@(0.0.255) void]_[* Pause]([@(0.0.255) bool]_[*@3 p
ause])&]
[s2; If [*@3 pause] is true it pauses the timer and if it is false 
it continues it.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:Pause`(`): [@(0.0.255) void]_[* Pause]()&]
[s2; Pauses the timer&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:Continue`(`): [@(0.0.255) void]_[* Continue]()&]
[s2; Continues the timer&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:Seconds`(`): [@(0.0.255) double]_[* Seconds]()&]
[s2; Returs the numer of elapsed seconds&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:SetBack`(double`): [@(0.0.255) void]_[* SetBack]([@(0.0.255) do
uble]_[*@3 secs])&]
[s2; Sets back the timer [*@3 secs] seconds.&]
[s3; &]
[s4; &]
[s5;:Upp`:`:RealTimeStop`:`:IsPaused`(`): [@(0.0.255) bool]_[* IsPaused]()&]
[s2; Returns true if it is paused.&]
[s3;%- &]
[s0; ]]