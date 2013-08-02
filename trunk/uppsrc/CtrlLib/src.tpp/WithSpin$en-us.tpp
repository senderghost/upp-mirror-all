topic "WithSpin template and Value editors with spin buttons";
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
[ {{10000@(113.42.0) [s0; [*@7;4 WithSpin]]}}&]
[s3;%- &]
[s1;:noref:%- [@(0.0.255)3 template][3 _<][@(0.0.255)3 class][3 _][*@4;3 DataType][3 , 
][@(0.0.255)3 class][3 _][*@3;3 Base][3 , ][@(0.0.255)3 class][3 _][*@4;3 IncType][3 _`=_][*@4;3 Da
taType][3 >]&]
[s1;:WithSpin`:`:class:%- [@(0.0.255) class]_[* WithSpin]_:_[@(0.0.255) public]_[*@3 Base]&]
[s2;%- &]
[s2;%- 
@@image:369&148
��ǀ���������������ᔌ����֞��������ڡ��Ά��������޻��Ð�������ܞ���������֯
������ԉ�ԏ�����������������τ�����������������Ѭ�̈́��Ȳ�Ꝓ��ی��Ȃ��������λ�
�����ϟ��������䨄�����ӑ���ӟ����Ȉ�Ռ��ϑ������֏���Ǥ������������婠�ڈ������
�׾��Ӵ�����̑�ˬ��ڑ������ڀ��؂��̪�߁������덪�����Āꆖ���۔��ɭ���������
���������������������������󨢠㱱�ꔌ�Ѡ���������
&]
[s2; &]
[s2; This template adds spin buttons to the [%-*@3 Base] widget to 
increment and decrement its value. [%-*@3 Base] musts be descendant 
of Ctrl and must have defined methods [* MinMax]([%-*@4 DataType,] 
[%-*@4 DataType]), [* GetMin ]and [* GetMax]. [%-*@4 DataType] is a type 
of Value contained in [%-*@3 Base], [%-*@4 IncType] type of increment 
value.&]
[s2; There two global function templates that can be used to customize 
increment/decrement process:  [* WithSpin`_DefaultIncValue] defines 
the default increment value and [* WithSpin`_Add] defines a way 
how the value is incremented or decremented.&]
[s0;i448;a25;kKO9;:noref:@(0.0.255)%- &]
[ {{10000F(128)G(128)@1 [s0; [* Public Method List]]}}&]
[s3;%- &]
[s5;:WithSpin`:`:SetInc`(IncType`):%- [_^WithSpin^ WithSpin][@(0.0.255) `&]_[* SetInc]([*@4 I
ncType]_[*@3 `_inc]_`=_[@3 1])&]
[s2; Sets the increment value.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:GetInc`(`)const:%- [*@4 DataType]_[* GetInc]()_[@(0.0.255) const]&]
[s2; Returns current increment value.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:OnSides`(bool`):%- [_^WithSpin^ WithSpin][@(0.0.255) `&]_[* OnSides]([@(0.0.255) b
ool]_[*@3 b]_`=_[@(0.0.255) true])&]
[s2; Instead of putting both buttons at the right side of widget, 
puts decrement button to the left and increment to the right.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:IsOnSides`(`)const:%- [@(0.0.255) bool]_[* IsOnSides]()_[@(0.0.255) const]&]
[s2; True is OnSides is active.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:ShowSpin`(bool`):%- [_^WithSpin^ WithSpin][@(0.0.255) `&]_[* ShowSpin]([@(0.0.255) b
ool]_[*@3 s]_`=_[@(0.0.255) true])&]
[s2; Shows/hides spin buttons.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:IsSpinVisible`(`)const:%- [@(0.0.255) bool]_[* IsSpinVisible]()_[@(0.0.255) c
onst]&]
[s2; Returns true if spin buttes are shown.&]
[s3; &]
[s4; &]
[s5;:WithSpin`:`:SpinButtonsObject`(`):%- [_^SpinButtons^ SpinButtons][@(0.0.255) `&]_[* Sp
inButtonsObject]()&]
[s5;:WithSpin`:`:SpinButtonsObject`(`)const:%- [@(0.0.255) const]_[_^SpinButtons^ SpinBut
tons][@(0.0.255) `&]_[* SpinButtonsObject]()_[@(0.0.255) const]&]
[s2; Returns a reference to internal SpinButtons object.&]
[s0; &]
[s0;%- &]
[ {{10000@(113.42.0) [s0; [*@7;4 Predefined WithSpin widgets]]}}&]
[s3;%- &]
[s5;:EditIntSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[@(0.0.255) int],
 [_^EditInt^ EditInt]>_[* EditIntSpin]&]
[s5;:EditInt64Spin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^int64^ int6
4], [_^EditInt64^ EditInt64]>_[* EditInt64Spin]&]
[s5;:EditDoubleSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[@(0.0.255) d
ouble], [_^EditDouble^ EditDouble]>_[* EditDoubleSpin]&]
[s5;:EditDateSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^Date^ Date],
 [_^EditDate^ EditDate], [@(0.0.255) int]>_[* EditDateSpin]&]
[s5;:EditTimeSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^Time^ Time],
 [_^EditTime^ EditTime], [@(0.0.255) int]>_[* EditTimeSpin]&]
[s5;:EditIntNotNullSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[@(0.0.255) i
nt], [_^EditIntNotNull^ EditIntNotNull]>_[* EditIntNotNullSpin]&]
[s5;:EditInt64NotNullSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^int64^ i
nt64], [_^EditInt64NotNull^ EditInt64NotNull]>_[* EditInt64NotNullSpin]&]
[s5;:EditDoubleNotNullSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[@(0.0.255) d
ouble], [_^EditDoubleNotNull^ EditDoubleNotNull]>_[* EditDoubleNotNullSpin]&]
[s5;:EditDateNotNullSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^Date^ D
ate], [_^EditDateNotNull^ EditDateNotNull], [@(0.0.255) int]>_[* EditDateNotNullSpin]&]
[s5;:EditTimeNotNullSpin`:`:typedef:%- [@(0.0.255) typedef]_[_^WithSpin^ WithSpin]<[_^Time^ T
ime], [_^EditTimeNotNull^ EditTimeNotNull], [@(0.0.255) int]>_[* EditTimeNotNullSpin]&]
[s2; These typedefs predefine common EditField based value editors 
with spin buttons.&]
[s3; ]]