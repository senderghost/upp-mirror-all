TITLE("Esc scripting language")
TOPIC_TEXT(
"[2 $$0,0#00000000000000000000000000000000:Default][b133;a83;*+117 $$1,0#31310162474203024125188417583966:subtitle][b83;*+150 "
"$$2,0#07864147445237544204411237157677:title][l321;t246;C@5;1 $$3,3#20902679421464641399138805415013:code][{_}%EN-US "
"[s0;*R8 Esc scripting language&][s0; &][s0; Esc is simple scripting language intended "
"for embedding in Ultimate`+`+ applications.&][s0; &][s0; It is typeless,")
TOPIC_TEXT(
" value oriented language with simple interfacing with C`+`+/U`+`+ code. It is very "
"simple yet quite complete language.&][s0; &][s2; Value types&][s1; voids&][s0; All "
"variables have void value before assigned any other value. Void type has single value&][s0; "
"&][s3; void&][s0; &][s0; and expression can be tested for voidness using [@(128.0.255) "
"is`_void] function.&][s1; numbers&][s0; Number is float")
TOPIC_TEXT(
"ing point number (corresponding to C type double). Examples of number literals:&][s0; "
"&][s3; 1&][s3; 1.123&][s3; 1.123e`-96&][s3;@4 [@5 0x123-|-|]// hexadecimal&][s3;@4 "
"[@5 0123 -|-|]// octal&][s3;@4 [@5 0b10100100-|-|]// binary&][s3;@4 [@5 `'x`'-|-|-|]// "
"character code&][s0; &][s0; Esc supports common C`-like operations for number values.&][s1; "
"arrays&][s0; Arrays are ordered random access sequen")
TOPIC_TEXT(
"ces of other Esc values (nested arrays included). Array values are specified using "
"[@(128.0.255) `[`]] brackets:&][s0; &][s3;@4 [@5 `[`]-|-|-|-|]// empty array&][s3; "
"`[ 1, 2, 3, 4, 5 `]&][s3;@4 [@5 `[ 1, `[2, 3`], 4 `]-|-|]// array contains nested "
"array&][s3;@4 [@5 `\"Hello`\"-|-|-|]// equivalent to `[`'H`', `'e`', `'l`', `'l`', "
"`'o`'`]&][s3;@4 [@5 `[ 1, 2, 3 `* alfa `]-|]// expressions can be used ")
TOPIC_TEXT(
"as well&][s0; &][s0; Number of elements in the array can be retrieved by standard "
"function count.&][s0; &][s0; Accessing elements of arrays is provided by subscript "
"[@(128.0.255) `[ `]] operator:&][s0; &][s3; a`[0`]&][s3; a`[1`] `= 3&][s0; &][s0; "
"First element of array corresponds to index [@(128.0.255) `[0`]].&][s0; &][s0; Negative "
"indexes are allowed and designate elements from the end of array:")
TOPIC_TEXT(
" [@(128.0.255) `[`-1`]] is last element of array, [@(128.0.255) `[`-2`]] last but "
"one etc.&][s0; &][s3; a`[`-1`]&][s0; &][s0; is equivalent to&][s0; &][s3; a`[count(a) "
"`- 1`]&][s0; &][s0; When index is used for the r`-value (standing on the right side "
"of [@(128.0.255) `=]), index is range checked. For l`-value, if non`-negative index "
"designates element past the of the array, array is expanded with")
TOPIC_TEXT(
" void values to create this element.&][s0; &][s0; `\"Empty`\" index [@(128.0.255) "
"`[`]] designates element past last and can be used to add elements to the array:&][s0; "
"&][s3; x`[`] `= item&][s0; &][s0; is equivalent to&][s0; &][s3; x`[count(x)`] `= "
"item&][s0; &][s0; Range of element in array can be obtained or changed using slices:&][s0; "
"&][s3; array`[pos, count`]&][s0; &][s0; designates array slic")
TOPIC_TEXT(
"e of [/ count] elements starting with [/ pos] element.&][s0; &][s3; x`[start:end`]&][s0; "
"&][s0; designates array slice of [/ end `- start] elements starting with [/ start] "
".&][s0; &][s0; Parts of slices can be ommited&][s0; &][s3; array`[pos,`]&][s0; or&][s3; "
"array`[pos:`]&][s0; &][s0; is equivalent to&][s0; &][s3; array`[pos : count(array)`]&][s0; "
"&][s0; and&][s0; &][s3; array`[,count`]&][s0; or&")
TOPIC_TEXT(
"][s3; array`[:count`]&][s0; &][s0; is equivalent to&][s0; &][s3; array`[0, count`]&][s0; "
"&][s0; When slices are used as l`-value, corresponding part of the array is replaced:&][s0; "
"&][s3; s `= `\"1234`\";&][s3;@4 [@5 s`[1: `-1`] `= `\"xXx`\";-|]// s is now `\"1xXx4`\"&][s0; "
"&][s0; Several operators can be applied to arrays&][s0; &][s3; array1 `+ array2&][s0; "
"&][s0; concatenates two arrays,&][s0; &][s3; ")
TOPIC_TEXT(
"array `* number&][s3; number `* array&][s0; &][s0; repeats array number times.&][s0; "
"&][s3; array `+`= array1&][s0; &][s0; is equivalent to&][s0; &][s3; array `= array "
"`+ array1&][s0; &][s0; also&][s0; &][s3; array << array1 << array2 << array3&][s0; "
"&][s0; is equivalent to&][s0; &][s3; array `= array `+ array1 `+ array2 `+ array3&][s0; "
"&][s0; Esc allows [/ void] value on the right side of array c")
TOPIC_TEXT(
"oncatenation expression `- in such cases, operator has no effect.&][s1; maps&][s0; "
"Maps contain key`-value pairs as entries. Normal subscripts [@(128.0.255) `[`]] are "
"used to access map entries:&][s0; &][s3; map`[key`] `= value&][s0; &][s0; All entries "
"in map that are not assigned particular non`-void value have void value. This way "
"assigning void to the map key can be considered as removing entry")
TOPIC_TEXT(
" from the map&][s0; &][s3; map`[key`] `= void&][s0; &][s0;  and testing entry for "
"being void can be considered as test of key presence in map:&][s0;C &][s3; if(is`_void(map`[key`])) "
"`{ ... `}&][s0; &][s0; As the special exception, when a void value appears before "
"an l`-value [@(128.0.255) `[`]], it is changed to the empty map:&][s0; &][s3; x `= "
"void; // x is void&][s3; x`[key`] `= value; // x is n")
TOPIC_TEXT(
"ow map&][s0; &][s0; Maps are also used to create compound data structures. To make "
"this job easier, special [/ .field] syntax is supported:&][s0; &][s3; x.field `= "
"value;&][s0; &][s0; is equivalent to&][s0; &][s3; x`[`\"field`\"`] `= value;&][s0; "
"&][s0; Map values can also be specified using `{`} braces:&][s0; &][s3; `{`} // empty "
"map&][s3; `{ `\"alfa`\":10, `\"beta`\":20, 20:`\"40`\" `}&][s3; `{ 2 `* a :")
TOPIC_TEXT(
" `\"100`\" `} // map values can contain expressions&][s1; lambdas&][s0; Lambdas "
"represent executable Esc code. Lambda values are introduced using [@(128.0.255) `@] "
"character:&][s0; &][s3; `@(x) `{ return 2 `* x; `}&][s0; &][s0; Assigning lambda "
"value to variable is equivalent to defining a function:&][s0; &][s3;@4 [@5 :foo `= "
"`@(x) `{ return 2 `* x; `};-|]// defines global function foo&][s0; &][s0; ")
TOPIC_TEXT(
"If lambda argument is preceded with [@(128.0.255) `&] character, it designates input`-output "
"argument (other arguments are input only).&][s0; &][s0; [*@(128.0.255) ... ]at the "
"end of the argument list allows variable number of arguments to be present. In that "
"case, additional parameters are passed in [/ argv] variable of type array.&][s0; "
"&][s3; :sum `= `@(...) `{ s `= 0; for(i in argv) s `+`= arg")
TOPIC_TEXT(
"v`[i`]; `}&][s0; &][s0; Parameters can have default values separated by [@(128.0.255) "
"`=]:&][s0; &][s3; :bar `= `@(x `= 0) `{ ... `}&][s0; &][s0; To make life easier, "
"alternative form of function definition is available:&][s0; &][s3; #:foo(x) `{ return "
"2 `* x; `}&][s2;i150;O9; Variables and contexts&][s0; &][s0; Variable names in Esc "
"follow C principles (are case sensitive, start with alphabetic c")
TOPIC_TEXT(
"haracter or [@(128.0.255) `_] and can contain alphabetic characters, [@(128.0.255) "
"`_] and numbers).&][s0; &][s0; Esc distinguishes three types of variables contexts "
"using [*@(128.0.255) .] and [*@(128.0.255) :] characters:&][s0; &][s3;@4 [@5 var-|-|]// "
"local&][s3;@4 [@5 .var-|-|]// instance&][s3;@4 [@5 :var-|-|]// global&][s0; &][s0; "
"Local variables are specific to function, global variables are ")
TOPIC_TEXT(
"shared among all functions. Instance variables &][s0; represent map values (keys "
"designate variable names) of map whose lambda value is invoked, or can be forced "
"using binary [@(128.0.255) !] bind operator:&][s0; &][s3; var.x `= 0;&][s3; var.Next "
"`= `@() `{ .x`+`+; `};&][s3;@4 [@5 var.Next();-|-|-|]// var.x is now 1 &][s3; var1.x "
"`= 0;&][s3;@4 [@5 var.Next()! var1;-|-|]// var1.x is now 1&][s0; &][")
TOPIC_TEXT(
"s0; To make programmer`'s life easier, one exception applies concerning context "
"`- when invoking lambda from local variable and lambda is not present in it, instance "
"and global contexts (in this order) are tried as well:&][s0; &][s3; beta(x)&][s3; "
"&][s0; Tries to get lambda form local [/ beta] variable first, then (if no lambda "
"found) from instance [/ beta ]variable and finally (if still no lambda")
TOPIC_TEXT(
") from global [/ beta]. Of course, [*@(128.0.255) .] and [*@(128.0.255) :] can still "
"be used to designate context:&][s0; &][s3;@4 [@5 :beta(x)-|-|-|-|]// calls global "
"beta even if local or instance beta is present&][s0; &][s2; Expressions&][s0; &][s0;/ "
"[/ When expressions are used as logical values, void, zero number and map or array "
"with zero elements represent ]false[/ , other values are ]true.&")
TOPIC_TEXT(
"][s0;/ &][s0; In following table, thick lines divide operators with the same priority, "
"with topmost items having the highest priority:&][s0; &][ {{4468:5532h1;@(216) [s0; "
"Operator]:: [s0; Comments]::^@2 [s0;*C [*/ map]`[[*/ key]`]]:: [s0; Map value at "
"[/ key].]:: [s0;/C map[*/ .]field]:: [s0; Same as [/ map]`[`\"[/ field]`\"`].]:: "
"[s0;*C [*/ array]`[[*/ index]`]]:: [s0; Array element at position [/ ")
TOPIC_TEXT(
"index].]:: [s0;*C [*/ array]`[[*/ start], [*/ count]`]]:: [s0; Array slice starting "
"at [/ start] of [/ count] elements.]:: [s0;*C [*/ array]`[[*/ start]:[*/ end]`]]:: "
"[s0; Array slice of elements [/ start .. end] `- 1]:: [s0;*C [*/ array]`[,[*/ count]`]&][s0;*C "
"[*/ array]`[:[*/ count]`]]:: [s0; Same as [/ array]`[0, [/ count]`].&][s0; ]:: [s0;*C "
"[*/ array]`[[*/ start]:`]&][s0;*C [*/ array]`[[*/ st")
TOPIC_TEXT(
"art],`]]:: [s0; Same as [/ array]`[[/ start] : count(array)`]. ]:: [s0;*C [*/ lambda]([*/ "
"args])]:: [s0; Invokes [/ lambda] with the set of [/ args]. If lambda is subscript "
"of the map, map becomes instance for [/ lambda] execution (accessible via [* .][/ "
"name] or [* self]).]:: [s0;/C lambda[*/ (]args[*/ ) ! ]instance]:: [s0; Invokes [/ "
"lambda], using[/  instance] as instance for lambda execution (")
TOPIC_TEXT(
"accessible via [* .][/ name] or [* self]).]:: [s0;*C self]:: [s0; Instance.]::t33/15 "
"[s0;/C [*/ `+`+]l`-number&][s0;/C [*/ `-`-]l`-number]:: [s0; Increments/decrements "
"number l`-value.]::t0/15 [s0;/C [*/ `-]number]:: [s0; Unary minus.]:: [s0;/C [*/ "
"`~]number]:: [s0; Bit`-wise complement.]:: [s0;/C [*/ !]value]:: [s0; Logical not. "
"1 when value represents false, 0 otherwise.]:: [s0;*C [*/ l`-number]")
TOPIC_TEXT(
"`-`-&][s0;*C [*/ l`-number]`+`+]:: [s0; Post`-increment / post`-decrement of number "
"l`-value.]::t33/15 [s0;/C array[*/  `* ]number&][s0;/C number[*/  `* ]array]:: [s0; "
"Returns [/ array][*/  ]repeated [/ number] times.]::t0/15 [s0;/C number[*/  `* ]number]:: "
"[s0; Multiplication.]:: [s0;/C number[*/  / ]number]:: [s0; Division.]:: [s0;/C number[*/ "
" % ]number]:: [s0; Modulo.]::t33/15 [s0;/C array[*/ ")
TOPIC_TEXT(
" `+ ]array]:: [s0; Concatenates [/ array]s.]::t0/15 [s0;/C number[*/  `+ ]number]:: "
"[s0; Addition.]:: [s0;/C number[*/  `- ]number]:: [s0; Subtraction.]::t33/15 [s0;/C "
"l`-array[*/  << ]array]:: [s0; Concatenates [/ array ]to [/ l`-array], yielding [/ "
"l`-array ]as l`-value result.]::t0/15 [s0;/C number[*/  << ]number]:: [s0; Shift "
"left.]:: [s0;/C number[*/  >> ]number]:: [s0; Shift right.]::t33/15 ")
TOPIC_TEXT(
"[s0;/C number[*/  < ]number&][s0;/C number[*/  > ]number&][s0;/C number[*/  <`= "
"]number&][s0;/C number[*/  >`= ]number]:: [s0; Comparison of [/ number]s.]::t0/15 "
"[s0;/C array[*/  < ]array&][s0;/C array[*/  > ]array&][s0;/C array[*/  <`= ]array&][s0;/C "
"array[*/  >`= ]array]:: [s0; Comparison of [/ array]s.]::t33/15 [s0;/C value[*/  "
"`=`= ]value]:: [s0; Equality.]::t0/15 [s0;/C value[*/  !`= ]value]:")
TOPIC_TEXT(
": [s0; Inequality.]::t33/15 [s0;/C number[*/  `& ]number]:: [s0; Binary and.]:: "
"[s0;/C number[*/  `^ ]number]:: [s0; Binary xor.]:: [s0;/C number[*/  `| ]number]:: "
"[s0; Binary or.]:: [s0;/C value[*/  `&`& ]value]:: [s0; Logical and. If first value "
"is false, second value is not evaluated, just skipped.]:: [s0;/C value[*/  `|`| ]value]:: "
"[s0; Logical or. If first value is true, second value is not e")
TOPIC_TEXT(
"valuated, just skipped.]:: [s0;/C value [*/ ?] value [*/ :] value]:: [s0; Conditional "
"expression. Only necessary expressions are evaluated.]:: [s0;/C l`-value[*/  `= ]value]:: "
"[s0; Assignment.]::t0/15 [s0;/C l`-array[*/  `+`= ]array]:: [s0; Same as [C l`-array "
"`= l`-array `+ array].]:: [s0;/C l`-number[*/  `+`= ]number]:: [s0; Same as [C l`-number "
"`= l`-number `+ number].]:: [s0;/C l`-number[*/  `")
TOPIC_TEXT(
"-`= ]number]:: [s0; Same as [C l`-number `= l`-number `- number].]:: [s0;/C l`-number[*/ "
" `*`= ]number]:: [s0; Same as [C l`-number `= l`-number `* number].]:: [s0;/C l`-number[*/ "
" /`= ]number]:: [s0; Same as [C l`-number `= l`-number / number].]:: [s0;/C l`-number[*/ "
" %`= ]number]:: [s0; Same as [C l`-number `= l`-number % number].]}}&][s0; &][s0; "
"&][s2; Statements&][s0; &][ {{4508:5492h1;@(216) ")
TOPIC_TEXT(
"[s0; Statement]:: [s0; Comments]::^@2 [s0;*C ;]:: [s0; Empty statement.]:: [s0;*C "
"[*/ expression];]:: [s0; Expression. It gets evaluated.]:: [s0;*C `{ [*/ statement]; "
"... `}]:: [s0; Compound statement.]:: [s0;/C [*/ if(]condition[*/ ) ]statement]:: "
"[s0; Conditional statement.]:: [s0;/C [*/ if(]condition[*/ ) ]statement&][s0;/C [*/ "
"else ]statement]:: [s0; Conditional statement with ]:: [s0;/C [*/ w")
TOPIC_TEXT(
"hile(]condition[*/ ) ]statement]:: [s0; Loop. Statement is performed as long as "
"the [/ condition] is true.]:: [s0;/C [*/ do ]statement&][s0;*C while([*/ condition])]:: "
"[s0; Loop. Statement is performed once and then is repeated as long as the [/ condition] "
"is true.]:: [s0;*C for([*/ init], [*/ condition], [*/ increment])&][s0;/C [*/ -|]statement]:: "
"[s0; Same as&][s0;C [/ init];&][s0;C while([/ con")
TOPIC_TEXT(
"dition]) `{&][s0;C -|[/ statement];&][s0;C -|[/ increment];&][s0;C `}]:: [s0;*C "
"for([*/ l`-value] in [*/ array])&][s0;/C [*/ -|]statement]:: [s0; Same as&][s0;C "
"for([/ l`-value] `= 0; [/ l`-value] < count([/ array]);&][s0;C     [/ l`-value]`+`+)&][s0;/C "
"[/ -|]statement&][s0; ]:: [s0;*C for([*/ l`-value] in [*/ map])&][s0;/C [*/ -|]statement]:: "
"[s0; Iterates through [/ map], assigning keys of eleme")
TOPIC_TEXT(
"nts with non`-void value to the [/ l`-value].]:: [s0;*C break;]:: [s0; Causes exit "
"from innermost loop or switch statement.]:: [s0;/C [*/ switch(]value[*/ ) ]statement]:: "
"[s0; Matches [/ value] to all case statements inside the [/ statement], continues "
"at the case with the same value, or with default if no such case exists and default "
"is present. If neither matching case and default exists, does n")
TOPIC_TEXT(
"othing.]:: [s0;*C case [*/ value]:]:: [s0; Switch case.]:: [s0;*C default:]:: [s0; "
"Default switch case.]:: [s0;*C #[*/ name]([*/ args]) `{ ... `}]:: [s0;C [A Same as "
"][/ name] `= `@([/ args]) `{ ... `};]:: [s0;*C #.[*/ name]([*/ args]) `{ ... `}]:: "
"[s0;C [A Same as ].[/ name] `= `@([/ args]) `{ ... `};]:: [s0;*C #:[*/ name]([*/ "
"args]) `{ ... `}]:: [s0;C [A Same as ]:[/ name] `= `@([/ args]) `{ ...")
TOPIC_TEXT(
" `};]}}&][s0; &][s2;3 Standard library&][s0;3 &][ {{2479:7521h1;@(216) [s0; Function]:: "
"[s0; Comments]::^@2 [s0;*C is`_number([*/ x])]:: [s0; Returns 1 if [/ x] is a number, "
"0 otherwise.]:: [s0;*C is`_array([*/ x])]:: [s0; Returns 1 if [/ x] is a array, 0 "
"otherwise.]:: [s0;*C is`_map([*/ x])]:: [s0; Returns 1 if [/ x] is a map, 0 otherwise.]:: "
"[s0;*C is`_void([*/ x])]:: [s0; Returns 1 if [/ x] is ")
TOPIC_TEXT(
"void, 0 otherwise.]:: [s0;*C int([*/ number])]:: [s0; Returns the [/ number] rounded "
"towards zero.]:: [s0;*C to`_string([*/ x])]:: [s0; Return [/ x] as array representing "
"string representation.]:: [s0;*C to`_number([*/ x])]:: [s0; Converts an array (string) "
"to the number.]:: [s0;*C count([*/ x])]:: [s0; If [/ x ]is void, returns 0.&][s0; "
"If x is a number, returns 1.&][s0; If x is an array, returns")
TOPIC_TEXT(
" number of elements of this array.&][s0; If x is an map, returns number of entries "
"in this map with non`-void values.]:: [s0;*C keys([*/ map])]:: [s0; Returns array "
"of keys of map (ordering is the same as for [* values] function, otherwise is unspecified).]:: "
"[s0;*C values([*/ map])]:: [s0; Returns array of values of map (ordering is the same "
"as for [* keys] function, otherwise is unspecified).]::")
TOPIC_TEXT(
" [s0;*C rand()]:: [s0; Returns random number in range 0..32767.]:: [s0;*C reverse([*/ "
"array])]:: [s0; Returns reversed [/ array].]:: [s0;*C sort([*/ array])]:: [s0; Returns "
"sorted [/ array].]:: [s0;*C order([*/ array])]:: [s0; Returns sort order of elements "
"in the [/ array].]:: [s0;*C IsDate([*/ map])]:: [s0; Returns 1 if map contains `\"day`\", "
"`\"month`\" and `\"year`\" keys, 0 otherwise.]:: [s0;*C Is")
TOPIC_TEXT(
"Time([*/ map])]:: [s0; Returns 1 if map contains `\"second`\", `\"minute`\", `\"hour`\", "
"`\"day`\", `\"month`\" and `\"year`\" members, 0 otherwise.]:: [s0;*C GetSysTime()]:: "
"[s0; Returns current time as map with `\"second`\", `\"minute`\", `\"hour`\", `\"day`\", "
"`\"month`\" and `\"year`\" members.]}}&][s0;3 ]")
