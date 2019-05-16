topic "class MAPIContact : public MAPIObject";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 MAPIContact]]}}&]
[s0;i448;kKO9;@(0.0.255)0 &]
[s0;i448;a25;kKO9;:MAPIContact`:`:class: [@(0.0.255)3 class][3 _][*3 MAPIContact][3 _:_][@(0.0.255)3 p
ublic][3 _][*@3;3 MAPIObject]&]
[s9; Outlook contact.&]
[s3;2 &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor detail]]}}&]
[s4; &]
[s5;:MAPIContact`:`:MAPIContact`(`): [* MAPIContact]()&]
[s2;%% Default constructor.&]
[s3; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Method List]]}}&]
[s4; &]
[s5;:MAPIContact`:`:GetName`(ULONG`): [_^String^ String]_[* GetName](ULONG_[*@3 ulNameID]_`=
_PR`_DISPLAY`_NAME)&]
[s2;%% Gets contact name.&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:GetEmail`(int`): [_^String^ String]_[* GetEmail]([@(0.0.255) int]_[*@3 nI
ndex]_`=_[@3 1])&]
[s2;%% Gets contact email index [%-*@3 nIndex ](1, 2, or 3).&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:GetEmailDisplayAs`(int`): [_^String^ String]_[* GetEmailDisplayAs]([@(0.0.255) i
nt]_[*@3 nIndex]_`=_[@3 1])&]
[s2;%% Gets contact email display text index [%-*@3 nIndex] (1, 2 or 
3).&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:GetHomePage`(bool`): [_^String^ String]_[* GetHomePage]([@(0.0.255) boo
l]_[*@3 bBusiness]_`=_[@(0.0.255) true])&]
[s2;%% Gets contact web page address. If [%-*@3 bBusiness] is true 
it returns the business home page. If not, it returns the personal 
home page.&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:GetPhoneNumber`(ULONG`): [_^String^ String]_[* GetPhoneNumber](ULONG_
[*@3 ulPhoneNumberID])&]
[s2;%% Gets contact phone number index [%-*@3 ulPhoneNumberID]. Valid 
values are:&]
[s2;i150;O0;%% PR`_BUSINESS`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_BUSINESS2`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_CALLBACK`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_ASSISTANT`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_BUSINESS`_FAX`_NUMBER&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:GetPostalAddress`(`): [_^String^ String]_[* GetPostalAddress]()&]
[s2;%% Gets contact postal address.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetIMAddress`(`): [_^String^ String]_[* GetIMAddress]()&]
[s2;%% Gets contact instant messenger address.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetFileAs`(`): [_^String^ String]_[* GetFileAs]()&]
[s2;%% Gets the contact filling string.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetTitle`(`): [_^String^ String]_[* GetTitle]()&]
[s2;%% Gets contact company title&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetCompany`(`): [_^String^ String]_[* GetCompany]()&]
[s2;%% Gets contact company name&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetProfession`(`): [_^String^ String]_[* GetProfession]()&]
[s2;%% Gets contact profession&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetDisplayNamePrefix`(`): [_^String^ String]_[* GetDisplayNamePrefix](
)&]
[s2;%% Gets contact display name prefix&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetGeneration`(`): [_^String^ String]_[* GetGeneration]()&]
[s2;%% Gets the contact generational abbreviation that follows the 
full name of the recipient.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetDepartment`(`): [_^String^ String]_[* GetDepartment]()&]
[s2;%% Gets contact department.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetOffice`(`): [_^String^ String]_[* GetOffice]()&]
[s2;%% Gets contact office location.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetManagerName`(`): [_^String^ String]_[* GetManagerName]()&]
[s2;%% Gets contact manager name.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetAssistantName`(`): [_^String^ String]_[* GetAssistantName]()&]
[s2;%% Gets contact  assistant name.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetNickName`(`): [_^String^ String]_[* GetNickName]()&]
[s2;%% Gets contact nickname.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetSpouseName`(`): [_^String^ String]_[* GetSpouseName]()&]
[s2;%% Gets contact spouse name.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetBirthday`(`): [_^Time^ Time]_[* GetBirthday]()&]
[s2;%% Gets contact birthday date.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetAnniversary`(`): [_^Time^ Time]_[* GetAnniversary]()&]
[s2;%% Gets contact anniversary date.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:GetCategories`(`): [_^String^ String]_[* GetCategories]()&]
[s2;%% Gets a String with all contact categories.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:SetName`(const String`&`,ULONG`): [@(0.0.255) bool]_[* SetName]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szName], ULONG_[*@3 ulNameID]_`=_PR`_DISPLAY`_NAME)&]
[s2;%% Sets contact name with [%-*@3 szName].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetEmail`(const String`&`,int`): [@(0.0.255) bool]_[* SetEmail]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szEmail], [@(0.0.255) int]_[*@3 nIndex]_`=_[@3 1])&]
[s2;%% Sets contact email index [%-*@3 nIndex] with [%-*@3 szEmail].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetEmailDisplayAs`(const String`&`,int`): [@(0.0.255) bool]_[* SetEma
ilDisplayAs]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szDisplayAs], 
[@(0.0.255) int]_[*@3 nIndex]_`=_[@3 1])&]
[s2;%% Sets contact email display text index [%-*@3 nIndex] with [%-*@3 szDisplayAs].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetHomePage`(const String`&`,bool`): [@(0.0.255) bool]_[* SetHomePage
]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szHomePage], [@(0.0.255) bool]_[*@3 bBusines
s]_`=_[@(0.0.255) true])&]
[s2;%% Sets contact home name [%-*@3 szHomePage]. If [%-*@3 bBusiness].is 
true it returns the business home page. If not, it returns the 
personal home page.&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetPhoneNumber`(const String`&`,ULONG`): [@(0.0.255) bool]_[* SetPhon
eNumber]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szPhoneNumber], 
ULONG_[*@3 ulPhoneNumberID])&]
[s2;%% Sets contact phone number index [%-*@3 ulPhoneNumberID] with 
[%-*@3 szPhoneNumber]. Valid indexes are:&]
[s2;i150;O0;%% PR`_BUSINESS`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_BUSINESS2`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_CALLBACK`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_ASSISTANT`_TELEPHONE`_NUMBER&]
[s2;i150;O0;%% PR`_BUSINESS`_FAX`_NUMBER&]
[s3;%% &]
[s4;%% &]
[s5;:MAPIContact`:`:SetPostalAddress`(AddressType`): [@(0.0.255) bool]_[* SetPostalAddres
s](ContactAddress`::AddressType_[*@3 nType])&]
[s2;%% Sets contact postal address type from [%-*@3 nType].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetNotes`(const String`&`,bool`): [@(0.0.255) bool]_[* SetNotes]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szNotes], [@(0.0.255) bool]_[*@3 bRTF][@(0.0.255) `=false])
&]
[s2;%% Sets contact notes from [%-*@3 szNotes]. In [%-*@3 bRTF] it indicates 
if text is RTF.&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetFileAs`(const String`&`): [@(0.0.255) bool]_[* SetFileAs]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szFileAs])&]
[s2;%% Sets contact file as from [%-*@3 szFileAs].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetTitle`(const String`&`): [@(0.0.255) bool]_[* SetTitle]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szTitle])&]
[s2;%% Sets contact title from [%-*@3 szTitle].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetCompany`(const String`&`): [@(0.0.255) bool]_[* SetCompany]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szCompany])&]
[s2;%% Sets contact company from [%-*@3 szCompany].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetProfession`(const String`&`): [@(0.0.255) bool]_[* SetProfession](
[@(0.0.255) const]_[_^String^ String]_`&[*@3 szProfession])&]
[s2;%% Sets contact profession from [%-*@3 szProfession].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetDisplayNamePrefix`(const String`&`): [@(0.0.255) bool]_[* SetDispl
ayNamePrefix]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szPrefix])&]
[s2;%% Sets contact display name prefix from [%-*@3 szPrefix].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetGeneration`(const String`&`): [@(0.0.255) bool]_[* SetGeneration](
[@(0.0.255) const]_[_^String^ String]_`&[*@3 szGeneration])&]
[s2;%% Sets contact generation from [%-*@3 szGeneration].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetDepartment`(const String`&`): [@(0.0.255) bool]_[* SetDepartment](
[@(0.0.255) const]_[_^String^ String]_`&[*@3 szDepartment])&]
[s2;%% Sets contact department from [%-*@3 szDepartment].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetOffice`(const String`&`): [@(0.0.255) bool]_[* SetOffice]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szOffice])&]
[s2;%% Sets contact office from [%-*@3 szOffice].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetManagerName`(const String`&`): [@(0.0.255) bool]_[* SetManagerName
]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szManagerName])&]
[s2;%% Sets contact manager name from [%-*@3 szManagerName].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetAssistantName`(const String`&`): [@(0.0.255) bool]_[* SetAssistant
Name]([@(0.0.255) const]_[_^String^ String]_`&[*@3 szAssistantName])&]
[s2;%% Sets contact assistant name from [%-*@3 szAssistantName].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetNickName`(const String`&`): [@(0.0.255) bool]_[* SetNickName]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szNickName])&]
[s2;%% Sets contact nickname from [%-*@3 szNickName].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetSpouseName`(const String`&`): [@(0.0.255) bool]_[* SetSpouseName](
[@(0.0.255) const]_[_^String^ String]_`&[*@3 szSpouseName])&]
[s2;%% Sets contact spouse name from [%-*@3 szSpouseName].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetBirthday`(const Time`&`): [@(0.0.255) bool]_[* SetBirthday]([@(0.0.255) c
onst]_[_^Time^ Time]_`&[*@3 tm])&]
[s2;%% Sets contact birthday from [%-*@3 tm].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetAnniversary`(const Time`&`): [@(0.0.255) bool]_[* SetAnniversary](
[@(0.0.255) const]_[_^Time^ Time]_`&[*@3 tm])&]
[s2;%% Sets contact anniversary from [%-*@3 tm].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:SetCategories`(const String`&`): [@(0.0.255) bool]_[* SetCategories](
[@(0.0.255) const]_[_^String^ String]_`&[*@3 szCategories])&]
[s2;%% Sets contact categories from [%-*@3 szCategories].&]
[s3;%% &]
[s4; &]
[s5;:MAPIContact`:`:HasPicture`(`): [@(0.0.255) bool]_[* HasPicture]()&]
[s2;%% Indicates if contact has a picture.&]
[s3; &]
[s4; &]
[s5;:MAPIContact`:`:SetPicture`(const String`&`): [@(0.0.255) bool]_[* SetPicture]([@(0.0.255) c
onst]_[_^String^ String]_`&[*@3 szPath])&]
[s2;%% Sets contact picture from image file in [%-*@3 szPath].&]
[s3;%% &]
[s0;%% ]