topic "Installing OpenSSL";
[2 $$0,0#00000000000000000000000000000000:Default]
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[H4;b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
[C2 $$10,0#37138531426314131251341829483380:class]
[l288;a17;*1 $$11,11#70004532496200323422659154056402:requirement]
[i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam]
[b167;C2 $$13,13#92430459443460461911108080531343:item1]
[i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2]
[*@2$(0.128.128)2 $$15,15#34511555403152284025741354420178:NewsDate]
[l321;*C$7;2 $$16,16#03451589433145915344929335295360:result]
[l321;b83;a83;*C$7;2 $$17,17#07531550463529505371228428965313:result`-line]
[l160;*C+117 $$18,5#88603949442205825958800053222425:package`-title]
[2 $$19,0#53580023442335529039900623488521:gap]
[C2 $$20,20#70211524482531209251820423858195:class`-nested]
[b50;2 $$21,21#03324558446220344731010354752573:Par]
[{_}%EN-US 
[s2; Installing OpenSSL&]
[s5; [* 1. In Linux]&]
[s5; Just install libopenssl using your package manager.&]
[s5;* &]
[s5; [* 2. In Windows]&]
[s5; These steps are valid for revision 0.9.8l. In other versions 
these instructions may change.&]
[s5;* &]
[s5; [* Common steps for MSC and MinGW ]&]
[s5; 2.1. Download openssl`-0.9.8l.tar.gz from&]
[s7; https://www.openssl.org/source/&]
[s5; &]
[s5; 2.2. Unpack archive to [C1 C:`\temp`\openssl`-0.9.8m]&]
[s5; &]
[s5; 2.3. Download and install ActivePerl&]
[s5; &]
[s5; [* Steps using MSC]&]
[s5; 2.4. Now type in the command line&]
[s5;l224; 1. [C1 C:`\temp`\openssl`-0.9.8m>perl Configure VC`-WIN32 
`-`-prefix`=c:/temp/openssl`-bin/]&]
[s5;l224; 2. Options&]
[s5;l224;i150;O0; For Visual Studio 8&]
[s5;l384; [C1 C:`\temp`\openssl`-0.9.8m>%comspec% /k `"`"c:`\Program 
Files`\Microsoft Visual Studio 8`\VC`\vcvarsall.bat`"`" x86]&]
[s5;l224;i150;O0; For Visual Studio 9&]
[s5;l384; [C1 C:`\temp`\openssl`-0.9.8m>%comspec% /k `"`"c:`\Program 
Files`\Microsoft Visual Studio 9.0`\VC`\vcvarsall.bat`"`" x86]&]
[s5;l224; 3. [C1 C:`\temp`\openssl`-0.9.8m>ms`\do`_masm.bat]&]
[s5;l224; 4. Options&]
[s5;l224;i150;O0; If you need static library&]
[s5;l416; [C1 C:`\temp`\openssl`-0.9.8m>nmake `-f ms`\nt.mak]&]
[s5;l224;i150;O0; If you need dynamic library&]
[s5;l416; [C1 C:`\temp`\openssl`-0.9.8m>nmake `-f ms`\ntdll.mak]&]
[s5;l416;C1 &]
[s5; 2.5. The result is in next folders:&]
[s5;i150;O0; inc32: Include files&]
[s5;i150;O0; out32: `*.lib files for static linking&]
[s5;i150;O0; out32dll: `*.lib `& `*.dll files for dynamic linking&]
[s0; &]
[s0; &]
[s5; [* Steps using MinGW]&]
[s5; 2.4. Now type in the command line&]
[s5; C:`\temp`\openssl`-0.9.8l>ms`\mingw32&]
[s5; &]
[s0; 2.5. The result is in next folders:&]
[s5;i150;O0; inc32: Include files&]
[s5;i150;O0; out32: `*.a `& `*.dll files for dynamic linking&]
[s0; &]
[s0; &]
[s5; [* Last steps]&]
[s5; 2.6. Add in `"Setup/Build methods/Lib directories`" menu, the 
directory where out32 and out32dll have been copied.&]
[s5; ]