topic "Math utility";
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
[{_} 
[ {{10000@(113.42.0) [s0;%% [*@7;4 Math utility]]}}&]
[s3; &]
[s0;%% A number of mathematical functions and constants.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constant List]]}}&]
[s3; &]
[s5;:M`_E: [* M`_E]&]
[s2;%% [/ e-|-|-|]2.71828182845904523536&]
[s3;%% &]
[s4; &]
[s5;:M`_LOG2E: [* M`_LOG2E]&]
[s2;%% [/ log][/, 2][/ e-|-|-|]1.44269504088896340736&]
[s3;%% &]
[s4; &]
[s5;:M`_LOG10E: [* M`_LOG10E]&]
[s2;%% [/ log10e]-|-|-|0.434294481903251827651&]
[s3;%% &]
[s4; &]
[s5;:M`_LN2: [* M`_LN2]&]
[s2;%% [/ ln2]-|-|-|0.693147180559945309417&]
[s3;%% &]
[s4; &]
[s5;:M`_LN10: [* M`_LN10]&]
[s2;%% [/ ln10]-|-|-|2.30258509299404568402&]
[s3;%% &]
[s4; &]
[s5;:M`_PI: [* M`_PI]&]
[s2;%% [/ Pi]-|-|-|3.14159265358979323846&]
[s3;%% &]
[s4; &]
[s5;:M`_PI`_2: [* M`_PI`_2]&]
[s2;%% [/ Pi / 2]-|-|-|1.57079632679489661923&]
[s3;%% &]
[s4; &]
[s5;:M`_PI`_4: [* M`_PI`_4]&]
[s2;%% [/ Pi / 4]-|-|-|0.785398163397448309616&]
[s3;%% &]
[s4; &]
[s5;:M`_1`_PI: [* M`_1`_PI]&]
[s2;%% [/ 1 / Pi]-|-|-|0.318309886183790671538&]
[s3;%% &]
[s4; &]
[s5;:M`_2`_PI: [* M`_2`_PI]&]
[s2;%% [/ 2 / Pi]-|-|-|0.636619772367581343076&]
[s3;%% &]
[s4; &]
[s5;:M`_1`_SQRTPI: [* M`_1`_SQRTPI]&]
[s2;%% [/ 1 / sqrt(Pi)]-|-|0.564189583547756286948&]
[s3;%% &]
[s4; &]
[s5;:M`_2`_SQRTPI: [* M`_2`_SQRTPI]&]
[s2;%% [/ 2 / sqrt(Pi)]-|-|1.12837916709551257390&]
[s3;%% &]
[s4; &]
[s5;:M`_SQRT2: [* M`_SQRT2]&]
[s2;%% 1.41421356237309504880&]
[s3;%% &]
[s4; &]
[s5;:M`_SQRT`_2: [* M`_SQRT`_2]&]
[s2;%% 0.707106781186547524401&]
[s3;%% &]
[s4; &]
[s5;:M`_2PI: [* M`_2PI]&]
[s2;%% [/ 2Pi]&]
[s3; &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Function List]]}}&]
[s3; &]
[s5;:Random`(`): [_^dword^ dword]_[* Random]()&]
[s2;%% Returns the next random generated number. MT safe and efficient 
variant of Merssene twister MT19937 by Takuji Nishimura and Makoto 
Matsumoto is used to get random numbers, with the seed obtained 
from host platform specific resources (`'/dev/urandom`' in Posix 
systems, GUID generator in Win32).&]
[s3;%% &]
[s4; &]
[s5;:Random`(dword`): [_^dword^ dword]_[* Random]([_^dword^ dword]_[*@3 n])&]
[s2; Returns the nextrandom generated number smaller than [*@3 n].&]
[s3;%% &]
[s4; &]
[s5;:sqr`(double`): [@(0.0.255) double]_[* sqr]_([@(0.0.255) double]_[*@3 a])&]
[s2;%% Returns the square of [%-*@3 a].&]
[s3;%% &]
[s4; &]
[s5;:argsinh`(double`): [@(0.0.255) double]_[* argsinh]_([@(0.0.255) double]_[*@3 s])&]
[s2;%% Returns the hyperbolic arcsin of [%-*@3 s].&]
[s3;%% &]
[s4; &]
[s5;:argcosh`(double`): [@(0.0.255) double]_[* argcosh]_([@(0.0.255) double]_[*@3 c])&]
[s2;%% Returns the hyperbolic arcsin of [%-*@3 c].&]
[s3;%% &]
[s4; &]
[s5;:argtanh`(double`): [@(0.0.255) double]_[* argtanh]_([@(0.0.255) double]_[*@3 t])&]
[s2;%% Returns the hyperbolic arctan of [%-*@3 t].&]
[s3;%% &]
[s4; &]
[s5;:iscale`(int`,int`,int`): [@(0.0.255) int]_[* iscale]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y], [@(0.0.255) int]_[*@3 z])&]
[s2;%% Returns [%-*@3 x] `* [%-*@3 y] / [%-*@3 z].&]
[s3;%% &]
[s4; &]
[s5;:iscalefloor`(int`,int`,int`): [@(0.0.255) int]_[* iscalefloor]([@(0.0.255) int]_[*@3 x],
 [@(0.0.255) int]_[*@3 y], [@(0.0.255) int]_[*@3 z])&]
[s2;%% Returns [%-*@3 x] `* [%-*@3 y] / [%-*@3 z][%-* ,][%-  rounded towards 
negative infinity].&]
[s3;%% &]
[s4; &]
[s5;:iscaleceil`(int`,int`,int`): [@(0.0.255) int]_[* iscaleceil]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y], [@(0.0.255) int]_[*@3 z])&]
[s2;%% Returns [%-*@3 x] `* [%-*@3 y] / [%-*@3 z][%-* ,][%-  rounded towards 
positive infinity].&]
[s3;%% &]
[s4; &]
[s5;:idivfloor`(int`,int`): [@(0.0.255) int]_[* idivfloor]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y])&]
[s2;%% Returns [%-*@3 x] / [%-*@3 y], truncated towards [%- negative infinity].&]
[s3;%% &]
[s4; &]
[s5;:idivceil`(int`,int`): [@(0.0.255) int]_[* idivceil]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y])&]
[s2;%% Returns [%-*@3 x] / [%-*@3 y], truncated towards [%- positive infinity].&]
[s3;%% &]
[s4; &]
[s5;:itimesfloor`(int`,int`): [@(0.0.255) int]_[* itimesfloor]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y])&]
[s2; Moves [*@3 x] to nearest lower multiple of [*@3 y].&]
[s3;%% &]
[s4; &]
[s5;:itimesceil`(int`,int`): [@(0.0.255) int]_[* itimesceil]([@(0.0.255) int]_[*@3 x], 
[@(0.0.255) int]_[*@3 y])&]
[s2; Moves [*@3 x] to nearest higher multiple of [*@3 y].&]
[s3;%% &]
[s4; &]
[s5;:fround`(double`): [@(0.0.255) int]_[* fround]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to nearest integer. Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:ffloor`(double`): [@(0.0.255) int]_[* ffloor]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to integer rounding towards negative infinity. 
Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:fceil`(double`): [@(0.0.255) int]_[* fceil]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to integer rounding towards `+infinity. 
Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:fround64`(double`): [_^int64^ int64]_[* fround64]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to nearest integer. Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:ffloor64`(double`): [_^int64^ int64]_[* ffloor64]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to integer rounding towards negative infinity. 
Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:fceil64`(double`): [_^int64^ int64]_[* fceil64]([@(0.0.255) double]_[*@3 x])&]
[s2; Converts double [*@3 x ]to integer rounding towards `+infinity. 
Checks integer limits.&]
[s3;%% &]
[s4; &]
[s5;:modulo`(double`,double`): [@(0.0.255) double]_[* modulo]([@(0.0.255) double]_[*@3 x], 
[@(0.0.255) double]_[*@3 y])&]
[s2;%% Returns the floating`-point remainder of [%-*@3 x]/[%-*@3 y].&]
[s2;%% &]
[s2;%% The remainder of a division operation is the result of subtracting 
the integral quotient multiplied by the denominator from the 
numerator:&]
[s2;%% &]
[s2;%% remainder `= numerator `- quotient `* denominator.&]
[s3;%% &]
[s4; &]
[s5;:ilog10`(double`): [@(0.0.255) int]_[* ilog10]_([@(0.0.255) double]_[*@3 d])&]
[s2;%%  [%-*@3 d].&]
[s3;%% &]
[s4; &]
[s5;:ipow10`(int`): [@(0.0.255) double]_[* ipow10]_([@(0.0.255) int]_[*@3 i])&]
[s2;%%  [%-*@3 i].&]
[s3;%% &]
[s4; &]
[s5;:normalize`(double`,int`&`): [@(0.0.255) double]_[* normalize]_([@(0.0.255) double]_[*@3 d
], [@(0.0.255) int`&]_[*@3 exponent])&]
[s2;%%  [%-*@3 d] [%-*@3 exponent].&]
[s3;%% &]
[s4; &]
[s5;:roundr`(double`,int`): [@(0.0.255) double]_[* roundr]_([@(0.0.255) double]_[*@3 d], 
[@(0.0.255) int]_[*@3 digits])&]
[s2;%%  [%-*@3 d] [%-*@3 digits].&]
[s3;%% &]
[s4; &]
[s5;:floorr`(double`,int`): [@(0.0.255) double]_[* floorr]_([@(0.0.255) double]_[*@3 d], 
[@(0.0.255) int]_[*@3 digits])&]
[s2;%%  [%-*@3 d] [%-*@3 digits].&]
[s3;%% &]
[s4; &]
[s5;:ceilr`(double`,int`): [@(0.0.255) double]_[* ceilr]_([@(0.0.255) double]_[*@3 d], 
[@(0.0.255) int]_[*@3 digits])&]
[s2;%%  [%-*@3 d] [%-*@3 digits].&]
[s3;%% &]
[s4; &]
[s5;:AsString`(double`,int`): [_^String^ String]_[* AsString]([@(0.0.255) double]_[*@3 x], 
[@(0.0.255) int]_[*@3 nDigits])&]
[s2;%% [%- Returns the string representation of ][%-*@3 x][%-  with] [%-*@3 nDigits][%-  
precision].&]
[s3; &]
[s0; ]