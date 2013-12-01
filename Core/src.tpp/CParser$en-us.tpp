topic "CParser";
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
[ {{10000@(113.42.0) [s0;%% [*@7;4 CParser]]}}&]
[s3; &]
[s1;:CParser`:`:class: [@(0.0.255) class]_[* CParser]&]
[s9;%% CParser is simple yet very useful lexical analyzer suitable 
for building descent parsers of languages with C`-like syntax.&]
[s9;%% CParser works on `'`\0`' terminated text in memory (not Stream), 
so to parse the file you have to load it into the memory first. 
Text has to exist during the time it is processed by CParser 
(no copy is made).&]
[s9;%% Many CParser methods can throw CParser`::Error exception to 
indicate the failure to parse required symbol. When using CParser 
to build concrete parser, it is common to use this exception 
(preferably via ThrowError method) to indicate errors as well.&]
[s9;%% CParser objects cannot be transfered (copied).&]
[s3;%% &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor Detail]]}}&]
[s3; &]
[s5;:CParser`:`:CParser`(const char`*`): [* CParser]([@(0.0.255) const]_[@(0.0.255) char]_`*
[*@3 ptr])&]
[s2; [%% Constructs the ][%%* CParser ][%% which can parse input buffer 
][*@3 ptr].&]
[s3; &]
[s4; &]
[s5;:CParser`:`:CParser`(const char`*`,const char`*`,int`): [* CParser]([@(0.0.255) const
]_[@(0.0.255) char]_`*[*@3 ptr], [@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 fn], 
[@(0.0.255) int]_[*@3 line]_`=_[@3 1])&]
[s2;%% Constructs the [* CParser], with additional information for 
the text. The additional info can be used when reporting error:&]
[s7;%% [%-*C@3 ptr]-|Pointer to the input text.&]
[s7;%% [%-*C@3 fn]-|The name of file (in fact, can be anything, value 
is just stored).&]
[s7;%% [%-*C@3 line]-|First line number.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:CParser`(`): [* CParser]()&]
[s2;%% Constructs the [* CParser]. Input text has to be assigned using 
the [* SetPos ]method.&]
[s3; &]
[s0; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Member List]]}}&]
[s3; &]
[s5;:CParser`:`:ThrowError`(const char`*`): [@(0.0.255) void]_[* ThrowError]([@(0.0.255) co
nst]_[@(0.0.255) char]_`*[*@3 s])&]
[s2;%% Throws [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ CPar
ser`::Error] with the error message [%-*@3 s].&]
[s3; &]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:SkipSpaces`(bool`): [_^CParser^ CParser][@(0.0.255) `&]_[* SkipSpaces]([@(0.0.255) b
ool]_[*@3 b]_`=_[@(0.0.255) true])&]
[s2;%% Sets the mode of skipping spaces. If [%-*@3 b] is true, sets 
[* CParser ]to the mode where white`-spaces are automatically skipped. 
First skip is performed when position in input text is assigned 
via constructor or [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:SetPos`(const CParser`:`:Pos`&`)^ S
etPos], then the skip is performed after any symbol. If [%-*@3 b] 
is false, sets [* CParser ]to the mode where white`-spaces are 
not automatically skipped, but have to be skipped by [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Spaces`(`)^ S
paces][*  ]method. Default is true.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:NoSkipSpaces`(`): [_^CParser^ CParser][@(0.0.255) `&]_[* NoSkipSpaces]()&]
[s2;%% Same as SkipSpaces(false).&]
[s3; &]
[s4; &]
[s5;:CParser`:`:UnicodeEscape`(bool`): [_^CParser^ CParser][@(0.0.255) `&]_[* UnicodeEscape
]([@(0.0.255) bool]_[*@3 b]_`=_[@(0.0.255) true])&]
[s2;%% Activates/deactivates whether CParser should recognize Java/JavaScript 
`\u unicode escape sequences in String.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Spaces`(`): [@(0.0.255) bool]_[* Spaces]()&]
[s2;%% Skips white`-spaces. Returns [* true] if there were white`-space 
to skip, [* false] otherwise. Stores the position before advancing 
as `"space pointer`" to be retrieved by GetSpacePtr.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:PeekChar`(`)const: [@(0.0.255) char]_[* PeekChar]()_[@(0.0.255) const]&]
[s2;%% Returns the current single character.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetChar`(`): [@(0.0.255) char]_[* GetChar]()&]
[s2;%% Advances the position in the input text by one character and 
returns the character at the position before advancing.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsChar`(char`)const: [@(0.0.255) bool]_[* IsChar]([@(0.0.255) char]_[*@3 c])_
[@(0.0.255) const]&]
[s2;%% Tests whether there is a specific character [%-*@3 c ]at the 
current position.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:IsChar2`(char`,char`)const: [@(0.0.255) bool]_[* IsChar2]([@(0.0.255) char]_
[*@3 c1], [@(0.0.255) char]_[*@3 c2])_[@(0.0.255) const]&]
[s2;%% Tests whether there is a specific character pair ([%-*@3 c1], 
[%-*@3 c2]) at the current position.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:IsChar3`(char`,char`,char`)const: [@(0.0.255) bool]_[* IsChar3]([@(0.0.255) c
har]_[*@3 c1], [@(0.0.255) char]_[*@3 c2], [@(0.0.255) char]_[*@3 c3])_[@(0.0.255) const]&]
[s2;%% Test for a specific character triplet ([%-*@3 c1], [%-*@3 c2], 
[%-*@3 c3]) at the current position.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Char`(char`): [@(0.0.255) bool]_[* Char]([@(0.0.255) char]_[*@3 c])&]
[s2;%% Tests for a single character [%-*@3 c] at the current position. 
If there is match, position is advanced and [* true] is returned. 
If no match is found position remains unmodified and [* false] 
is returned.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Char2`(char`,char`): [@(0.0.255) bool]_[* Char2]([@(0.0.255) char]_[*@3 c1], 
[@(0.0.255) char]_[*@3 c2])&]
[s2;%% Tests for a character pair ([%-*@3 c1], [%-*@3 c2]) at the current 
position. If there is match, position is advanced by two characters 
and [* true] is returned. If no match is found position remains 
unmodified and [* false] is returned.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Char3`(char`,char`,char`): [@(0.0.255) bool]_[* Char3]([@(0.0.255) char]_[*@3 c
1], [@(0.0.255) char]_[*@3 c2], [@(0.0.255) char]_[*@3 c3])&]
[s2;%% Tests for a character triplet ([%-*@3 c1], [%-*@3 c2], [%-*@3 c3]) 
at the current position. If there is match, position is advanced 
by three characters and [* true] is returned. If no match is found 
position remains unmodified and [* false] is returned.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:PassChar`(char`)throw`(CParser`:`:Error`): [@(0.0.255) void]_[* PassChar](
[@(0.0.255) char]_[*@3 c])_[@(0.0.255) throw](Error)&]
[s2;%% Calls [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Char`(char`)^ Char](c)
. If it returns false, throws error.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:PassChar2`(char`,char`)throw`(CParser`:`:Error`): [@(0.0.255) void]_[* Pa
ssChar2]([@(0.0.255) char]_[*@3 c1], [@(0.0.255) char]_[*@3 c2])_[@(0.0.255) throw](Error)&]
[s2;%% Calls [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Char2`(char`,char`)^ C
har2](c1, c2). If it returns [* false], throws [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error].&]
[s3; &]
[s4; &]
[s5;:CParser`:`:PassChar3`(char`,char`,char`)throw`(CParser`:`:Error`): [@(0.0.255) voi
d]_[* PassChar3]([@(0.0.255) char]_[*@3 c1], [@(0.0.255) char]_[*@3 c2], 
[@(0.0.255) char]_[*@3 c3])_[@(0.0.255) throw](Error)&]
[s2;%% Calls [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Char3`(char`,char`,char`)^ C
har3](c1, c2, c3). If it returns [* false], throws [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error].&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Id`(const char`*`): [@(0.0.255) bool]_[* Id]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 s])&]
[s2;%% Tests for given C`-like identifier [%-*@3 s]. If there is match, 
advances position by [* strlen](s) characters. Returns [* true] on 
match and [* false] otherwise.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:PassId`(const char`*`)throw`(CParser`:`:Error`): [@(0.0.255) void]_[* Pas
sId]([@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 s])_[@(0.0.255) throw](Error)&]
[s2;%% Invokes the [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Id`(const char`*`)^ I
d] method with [%-*@3 s] as parameter. If it returns [* false], throws 
[^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ CParser`::Error
].&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsId`(`)const: [@(0.0.255) bool]_[* IsId]()_[@(0.0.255) const]&]
[s2;%% Tests whether there is any C`-like identifier at the current 
position.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsId`(const char`*`)const: [@(0.0.255) bool]_[* IsId]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 s])_[@(0.0.255) const]&]
[s2;%% Tests whether there is C`-like identifier [%-*@3 s] at current 
position.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:ReadId`(`)throw`(CParser`:`:Error`): [_^String^ String]_[* ReadId]()_[@(0.0.255) t
hrow](Error)&]
[s2;%% Reads C`-like identifier from the current position. If there 
is none, a [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ CPa
rser`::Error] is thrown.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadIdt`(`)throw`(CParser`:`:Error`): [_^String^ String]_[* ReadIdt]()_[@(0.0.255) t
hrow](Error)&]
[s2;%% Special variant of [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:ReadId`(`)throw`(CParser`:`:Error`)^ R
eadId] that considers different non`-alphanumeric characters 
to be the part of identifier as long as they form C`+`+ normal 
or template based type.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsInt`(`)const: [@(0.0.255) bool]_[* IsInt]()_[@(0.0.255) const]&]
[s2;%% Test for integer at current position `- there either must 
be digit, or `'`+`' or `'`-`' sign followed by any number of 
spaces and digit.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Sgn`(`): [@(0.0.255) int]_[* Sgn]()&]
[s2;%% If there are characters `'`-`' or `'`+`' at current posisition, 
skips them. If `'`-`' was skipped, returns `-1, otherwise 1.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadInt`(`)throw`(CParser`:`:Error`): [@(0.0.255) int]_[* ReadInt]()_[@(0.0.255) t
hrow](Error)&]
[s2;%% Reads the integer from the current position. If [* IsInt ]is 
false, throws an [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error.]&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadInt`(int`,int`)throw`(CParser`:`:Error`): [@(0.0.255) int]_[* ReadInt
]([@(0.0.255) int]_[*@3 min], [@(0.0.255) int]_[*@3 max])_[@(0.0.255) throw](Error)&]
[s2;%% Performs ReadInt and then checks the result to be in [%-*@3 min] 
<`= result <`= [%-*@3 max]. If not, throws a [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error], otherwise returns it.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:ReadInt64`(`)throw`(CParser`:`:Error`): [_^int64^ int64]_[* ReadInt64]()_
[@(0.0.255) throw](Error)&]
[s2;%% Reads the 64`-bit integer from the current position. If [* IsInt 
]is false, throws an [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error.]&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadInt64`(int64`,int64`)throw`(CParser`:`:Error`): [_^int64^ int64]_[* R
eadInt64]([_^int64^ int64]_[*@3 min], [_^int64^ int64]_[*@3 max])_[@(0.0.255) throw](Error)
&]
[s2;%% Performs ReadInt64 and then checks the result to be in [%-*@3 min] 
<`= result <`= [%-*@3 max]. If not, throws a [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error], otherwise returns it.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:IsNumber`(`)const: [@(0.0.255) bool]_[* IsNumber]()_[@(0.0.255) const]&]
[s2;%% Tests for sign`-less number at current position `- there must 
be digit at current position.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsNumber`(int`)const: [@(0.0.255) bool]_[* IsNumber]([@(0.0.255) int]_[*@3 ba
se])_[@(0.0.255) const]&]
[s2;%% Tests for sign`-less number with given base `- there must 
be digit or letter `'A`' `- `'Z`' or `'a`' `- `'z`', where range 
is limit by actual [%-*@3 base ](e.g. for base 12 letters `'a`' 
`'A`' `'b`' `'B`' are allowed).&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadNumber`(int`)throw`(CParser`:`:Error`): [_^uint32^ uint32]_[* ReadNum
ber]([@(0.0.255) int]_[*@3 base]_`=_[@3 10])_[@(0.0.255) throw](Error)&]
[s2;%% Reads a number with the given numeric [%-*C@3 base]. If [* IsNumber]([%-*@3 base]) 
is false, throws an [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Error`:`:struct^ C
Parser`::Error.]&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadNumber64`(int`)throw`(CParser`:`:Error`): [_^uint64^ uint64]_[* ReadN
umber64]([@(0.0.255) int]_[*@3 base]_`=_[@3 10])_[@(0.0.255) throw](Error)&]
[s2;%% Reads 64`-bit unsigned number with given numeric [%-*@3 base].&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:IsDouble`(`)const: [@(0.0.255) bool]_[* IsDouble]()_[@(0.0.255) const]&]
[s2;%% Test for floating point number at current position `- there 
either must be digit, or `'`+`' or `'`-`' sign followed by any 
number of spaces and digit.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadDouble`(`)throw`(CParser`:`:Error`): [@(0.0.255) double]_[* ReadDoubl
e]()_[@(0.0.255) throw](Error)&]
[s2;%% Reads a floating point number with C based lexical rules.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsString`(`)const: [@(0.0.255) bool]_[* IsString]()_[@(0.0.255) const]&]
[s2;%% Tests for C`-like string literal at the current position. 
Same as [* IsChar](`'`\`"`');&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadOneString`(bool`)throw`(CParser`:`:Error`): [_^String^ String]_[* Rea
dOneString]([@(0.0.255) bool]_[*@3 chkend]_`=_[@(0.0.255) false])_[@(0.0.255) throw](Erro
r)&]
[s2;%% Reads C`-like string literal from current position (follow 
C lexical rules, including escape codes). Literals on different 
lines are not concatenated (unlike C). When [%-*C@3 chkend] [* false], 
[* ReadOneString ]is more permissive as it allows unterminated 
string literals `- string is then also delimited by end of line 
or text.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadString`(bool`)throw`(CParser`:`:Error`): [_^String^ String]_[* ReadSt
ring]([@(0.0.255) bool]_[*@3 chkend]_`=_[@(0.0.255) false])_[@(0.0.255) throw](Error)&]
[s2;%% Reads C`-like string literal from current position (follow 
C lexical rules, including escape codes). Literals on different 
lines are concatenated (as in C). When [%-*C@3 chkend] [* false], 
[* ReadOneString ]is more permissive as it allows unterminated 
string literals `- string is then also delimited by end of line 
or text.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadOneString`(int`,bool`)throw`(CParser`:`:Error`): [_^String^ String]_
[* ReadOneString]([@(0.0.255) int]_[*@3 delim], [@(0.0.255) bool]_[*@3 chkend]_`=_[@(0.0.255) f
alse])_[@(0.0.255) throw](Error)&]
[s2;%% Reads C`-like string literal from current position (follow 
C lexical rules, including escape codes) with different delimiter 
[%-*C@3 delim] than `'`\`"`'. Literals on different lines are not 
concatenated (unlike C). When [%-*C@3 chkend] is false, [* ReadOneString 
]is more permissive as it allows unterminated string literals 
`- string is then also delimited by end of line or text.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:ReadString`(int`,bool`)throw`(CParser`:`:Error`): [_^String^ String]_[* R
eadString]([@(0.0.255) int]_[*@3 delim], [@(0.0.255) bool]_[*@3 chkend]_`=_[@(0.0.255) fals
e])_[@(0.0.255) throw](Error)&]
[s2;%% Reads C`-like string literal from current position (follow 
C lexical rules, including escape codes). with different delimiter 
[%-*C@3 delim] than `'`\`"`'. Literals on different lines are concatenated 
(as in C). When [%-*C@3 chkend] is false, [* ReadOneString ]is more 
permissive as it allows unterminated string literals `- string 
is then also delimited by end of line or text.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:SkipTerm`(`): [@(0.0.255) void]_[* SkipTerm]()&]
[s2;%% Skips a single symbol. Decimal numbers, identifiers and string 
literals are skipped as whole symbols, otherwise input position 
is advanced by 1 character.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetPtr`(`)const: [@(0.0.255) const]_[@(0.0.255) char]_`*[* GetPtr]()_[@(0.0.255) c
onst]&]
[s2;%% Returns a pointer to the current position.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetSpacePtr`(`)const: [@(0.0.255) const]_[@(0.0.255) char]_`*[* GetSpacePtr
]()_[@(0.0.255) const]&]
[s2;%% Returns a pointer to the position of last whitespace before 
current position, or current position if there was none whitespace. 
This pointer is set at the start of Space call, Space is called 
after each token processed (unless SkipWhitespaces is false).&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetPos`(`)const: [_^CParser`:`:Pos^ Pos]_[* GetPos]()_[@(0.0.255) const]&]
[s2;%% Gets the current position. It contains the pointer as well 
as the line number and the filename.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:SetPos`(const CParser`:`:Pos`&`): [@(0.0.255) void]_[* SetPos]([@(0.0.255) c
onst]_[_^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:Pos`:`:struct^ CParser`:
:Pos][@(0.0.255) `&]_[*@3 p])&]
[s2; [%% Sets the current position to ][*@3 p][%% . ][*@3 p ]can be from 
a different [* CParser].&]
[s3; &]
[s4; &]
[s5;:CParser`:`:IsEof`(`)const: [@(0.0.255) bool]_[* IsEof]()_[@(0.0.255) const]&]
[s2;%% Test for the end of input text.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:operator bool`(`)const: [* operator_bool]()_[@(0.0.255) const]&]
[s2; Returns [* true ]if end of file has not been reached, [* false ]otherwise.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetLine`(`)const: [@(0.0.255) int]_[* GetLine]()_[@(0.0.255) const]&]
[s2; Returns the current line number.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:GetFileName`(`)const: [_^String^ String]_[* GetFileName]()_[@(0.0.255) cons
t]&]
[s2; Returns the actual filename.&]
[s3;%% &]
[s3; &]
[s4; &]
[s5;:CParser`:`:Set`(const char`*`,const char`*`,int`): [@(0.0.255) void]_[* Set]([@(0.0.255) c
onst]_[@(0.0.255) char]_`*[*@3 ptr], [@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 fn], 
[@(0.0.255) int]_[*@3 line]_`=_[@3 1])&]
[s2;%% Sets the new input string (with filename and line).&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:Set`(const char`*`): [@(0.0.255) void]_[* Set]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 ptr])&]
[s2;%% Sets the new input string.&]
[s0;%% &]
[s0;%% &]
[s0;%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 CParser`::Error]]}}&]
[s3; &]
[s1;:CParser`:`:Error`:`:struct: [@(0.0.255)3 struct][3 _][*3 Error][3 _:_][@(0.0.255)3 public][3 _
][*@3;3 Exc]&]
[s0; &]
[s0;%% Type used as [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:class^ CParser] 
exception. Contains single [^topic`:`/`/Core`/src`/String`$en`-us`#String`:`:class^ S
tring] with error description.&]
[s0;/%% &]
[s0; [%%/ Derived from][%%  ][^topic`:`/`/Core`/src`/Exc`$en`-us`#Exc`:`:class^ Exc]&]
[s3;%% &]
[s0;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor Detail]]}}&]
[s3; &]
[s5;:Exc`:`:Exc`(`): [* Exc]()&]
[s2;%% Default constructor. Error message is empty.&]
[s3;%% &]
[s4; &]
[s5;:Exc`:`:Exc`(const String`&`): [* Exc]([@(0.0.255) const]_[_^String^ String][@(0.0.255) `&
]_[*@3 desc])&]
[s2; [%% Construct an ][%%* Error][%%  with ][*@3 desc] as an error message.&]
[s3;%% &]
[s0;%% &]
[s0;%% &]
[s0;%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 CParser`::Pos]]}}&]
[s3;%% &]
[s1;:CParser`:`:Pos`:`:struct: [@(0.0.255)3 struct][3 _][*3 Pos]&]
[s3; &]
[s5;:`:`:CParser`:`:Pos`:`:struct:%% Position in parsed text.&]
[s3;%% &]
[ {{10000F(128)G(128)@1 [s0;%% [* Constructor Detail]]}}&]
[s3; &]
[s5;:CParser`:`:Pos`:`:Pos`(const char`*`,int`,String`): [* Pos]([@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 ptr]_`=_NULL, [@(0.0.255) int]_[*@3 line]_`=_[@3 1], [_^String^ String]_[*@3 fn]_
`=_Null)&]
[s2; Constrcuts a [* Pos ]based on pointer in input buffer, line number 
and anme of the file.&]
[s7;%% [%-*@3 ptr]-|Pointer to the position in the input text &]
[s7;%% [%-*@3 line]-|Line number.&]
[s7;%% [%-*@3 fn]-|Filename.&]
[s3; &]
[ {{10000F(128)G(128)@1 [s0;%% [* Public Member List]]}}&]
[s3; &]
[s5;:CParser`:`:Pos`:`:ptr: [@(0.0.255) const]_[@(0.0.255) char]_`*[* ptr]&]
[s2;%% Pointer to the position in the input text &]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:Pos`:`:wspc: [@(0.0.255) const]_[@(0.0.255) char]_`*[* wspc]&]
[s2;%% Pointer to the position of last whitespace before current 
position, or current position if there was none whitespace.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Pos`:`:lineptr: [@(0.0.255) const]_[@(0.0.255) char]_`*[* lineptr]&]
[s2;%% Pointer to the beginning of the last line.&]
[s3; &]
[s4; &]
[s5;:CParser`:`:Pos`:`:line: [@(0.0.255) int]_[* line]&]
[s2;%% Line number.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:Pos`:`:fn: [_^topic`:`/`/Core`/src`/String`$en`-us`#String`:`:class^ St
ring]_[* fn]&]
[s2;%% Filename.&]
[s3;%% &]
[s4; &]
[s5;:CParser`:`:Pos`:`:GetColumn`(int`)const: [@(0.0.255) int]_[* GetColumn]([@(0.0.255) in
t]_[*@3 tabsize]_`=_[@3 4])_[@(0.0.255) const]&]
[s2;%% Returns the column, for given [%-*@3 tabsize].&]
[s0;%% &]
[s0;%% &]
[ {{10000@(113.42.0) [s0;%% [*@7;4 C`-like string literal formatting]]}}&]
[s3;%% &]
[s0;%% [* AsCString] routines produce C`-like literals (compatible 
with [^topic`:`/`/Core`/src`/CParser`$en`-us`#CParser`:`:class^ CParser]) 
from character data:&]
[s0;%% &]
[s5;:AsCString`(const char`*`,const char`*`,int`,const char`*`,dword`): [_^String^ Stri
ng]_[* AsCString]([@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 s], [@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 end], [@(0.0.255) int]_[*@3 linemax]_`=_INT`_MAX, [@(0.0.255) const]_[@(0.0.255) c
har]_`*[*@3 linepfx]_`=_NULL, [_^dword^ dword]_[*@3 flags]_`=_[@3 0])&]
[s2;%% Creates C`-like literal.&]
[s7;%% [%-*@3 s]-|Pointer to characters.&]
[s7;%% [%-*@3 end] -|End of characters array (`'`\0`' characters are 
allowed inside data).&]
[s7;%% [%-*@3 linemax] -|Maximal length of line. If this is exceeded, 
ending `"`\`"`\n`" and [@3 linepfx] is inserted and literal continues 
on the new line.&]
[s7;%% [%-*@3 linepfx]-|Pointer to zero`-terminated text to be inserted 
at the beginning of the line when the line length is exceeded.&]
[s7;%% [%-*@3 flags]-|a combination of flags:&]
[s0;~~~1408;%% -|ASCSTRING`_SMART-|breaks string into lines when too 
long&]
[s0;~~~1408;%% -|ASCSTRING`_OCTALHI-|escapes characters >128&]
[s0;~~~1408;%% -|ASCSTRING`_JSON-|uses JSON notation for escapes (`\u0001 
-|                                          instead of `\001)&]
[s0;~~~1408;%% &]
[s0;%% &]
[s7;%% [*/ Return value]-|C`-like literal.&]
[s3;%% &]
[s4; &]
[s5;:AsCString`(const char`*`,int`,const char`*`,dword`): [_^String^ String]_[* AsCString
]([@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 s], [@(0.0.255) int]_[*@3 linemax]_`=_INT`_MA
X, [@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 linepfx]_`=_NULL, [_^dword^ dword]_[*@3 flag
s]_`=_[@3 0])&]
[s2;%% Creates C`-like literal from zero terminated character data. 
Same as [^topic`:`/`/Core`/src`/CParser`$en`-us`#AsCString`(const char`*`,const char`*`,int`,const char`*`,dword`)^ A
sCString]([%-*@3 s],[%- _][%-*@3 s][%- _]`+[%- _][* strlen]([%-*@3 s]),[%- _][%-*@3 linemax],[%- _][%-*@3 l
inepfx],[%- _][%-*@3 flags]).&]
[s3;%% &]
[s4; &]
[s5;:AsCString`(const String`&`,int`,const char`*`,dword`): [_^String^ String]_[* AsCStri
ng]([@(0.0.255) const]_[_^String^ String][@(0.0.255) `&]_[*@3 s], [@(0.0.255) int]_[*@3 linem
ax]_`=_INT`_MAX, [@(0.0.255) const]_[@(0.0.255) char]_`*[*@3 linepfx]_`=_NULL, 
[_^dword^ dword]_[*@3 flags]_`=_[@3 0])&]
[s2;%% Creates C`-like literal from [^topic`:`/`/Core`/src`/String`$en`-us`#String`:`:class^ S
tring]. String can contain zero characters. Same as [^topic`:`/`/Core`/src`/CParser`$en`-us`#AsCString`(const char`*`,const char`*`,int`,const char`*`,dword`)^ A
sCString]([%-*@3 s].[^topic`:`/`/Core`/src`/String`$en`-us`#String0`:`:Begin`(`)const^ B
egin](),[%- _][%-*@3 s].[^topic`:`/`/Core`/src`/String`$en`-us`#String0`:`:End`(`)const^ E
nd](),[%- _][%-*@3 linemax],[%- _][%-*@3 linepfx],[%- _][%-*@3 flags]).&]
[s3;%% &]
[s0; ]]