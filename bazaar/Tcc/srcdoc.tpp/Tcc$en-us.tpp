topic "Tcc";
[ $$0,0#00000000000000000000000000000000:Default]
[a83;*R6 $$1,0#31310162474203024125188417583966:caption]
[{_}%EN-US 
[s1; Tcc&]
[s0; Tcc is a wrapper for Tiny C Compiler.&]
[s0; &]
[s0; &]
[s0; [* About Tcc package]&]
[s0;* &]
[s0; Tcc wrapper is based in the TCC dynamic code generation characteristics. 
This feature lets to compile, link and run a C program in memory 
so that C language can be used as an scripting language.&]
[s0; &]
[s0; As many functions as necessary in the Tcc C script can be called 
from the main program. Because of it there is no need for any 
`"main()`" function.&]
[s0; &]
[s0; All static and global variables will be lost between function 
calls. All durable storage has to be located in the main program.&]
[s0; &]
[s0; Tcc uses exceptions so any compiling or Tcc C script problem 
can be catched from the main program.&]
[s0; &]
[s0; Tcc sample reference is included [^topic`:`/`/Tcc`/srcdoc`/Sample`$en`-us^ here].&]
[s0; Tcc implementation details are included [^topic`:`/`/Tcc`/srcimp`/Tcc`$en`-us^ her
e].&]
[s0; Tcc class reference is included [^topic`:`/`/Tcc`/src`/Tcc`$en`-us^ here].&]
[s0; &]
[s0; Tcc wrapper is done by Koldo and has BSD license as Ultimate`+`+ 
project (see [^http`:`/`/www`.ultimatepp`.org`/app`$ide`$About`$en`-us`.html^ here])
.&]
[s0; &]
[s0; &]
[s0; [* About TCC]&]
[s0; &]
[s0; Tiny C Compiler (TCC) is an x86 C compiler created by Fabrice 
Bellard. TCC is distributed under the GNU Lesser General Public 
License (LGPL).&]
[s0; &]
[s0; TCC main features are:&]
[s0;i150;O0; Small: DLL size is 200Kb&]
[s0;i150;O0; Fast: It compiles much faster than GCC os MSC&]
[s0;i150;O0; It can be used as a backend for dynamic code generation. 
This feature has been used to develop this TCC wrapper.&]
[s0; &]
[s0; TCC homepage is [^http`:`/`/bellard`.org`/tcc`/^ here.]&]
[s0;^http`:`/`/bellard`.org`/tcc`/^ &]
[s0;^http`:`/`/bellard`.org`/tcc`/^ ]