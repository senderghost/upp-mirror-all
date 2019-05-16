topic "Implementation details";
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
[s2; SysInfo&]
[s0; &]
[s0; [*+92 1. Introduction]&]
[s0; &]
[s0; A goal in the design of these functions has been to avoid accessing 
external software not included internally in the OS by default.&]
[s5;i150;O0; Windows implementation use internal DLL and wmi.&]
[s0;i150;O0; Posix implementation uses X11 libraries, XTest and OS 
related utilities like mount and xdg.&]
[s0; &]
[s0; Another goal is to provide the running program information about 
the environment including hardware and software to adapt itself 
after program compiling. This way for example a program compiled 
in Ubuntu can run properly in Fedora without recompiling.&]
[s0; &]
[s0; &]
[s0; [*+92 2. Compiler support and Requirements]&]
[s0; &]
[s0; SysInfo has been tested in Linux using Gcc and in Windows using 
MinGW and MSC.&]
[s0; &]
[s0;~~~2048; [*@6 IMPORTANT][* :] To compile using MinGW it is required 
to copy the next files from SysInfo/plugin:&]
[s0;i150;O0; To `\MinGW`\include: &]
[s0;l96; Files [* Rpcsal.h, DispEx.h, WbemCli.h, WbemDisp.h, Wbemidl.h, 
WbemProv.h and WbemTran.h.]&]
[s0; &]
[s0;i150;O0;%- To `\MinGW`\lib: &]
[s0;l96; File [* wbemuuid.lib]&]
[s0; &]
[s0; [*@6 IMPORTANT][* :] To compile it in Linux it is necessary to include 
package XTest. In Ubuntu the aptitude package name is [* libxtst`-dev].&]
[s0; &]
[s0; &]
[s0; [*+92 3. OS and Desktop implementation]&]
[s0; &]
[s0; OS and Desktop implementation is a work in process as in some 
implementations it requires a level of hacking so all feedback 
will be acknowledged.&]
[s0; &]
[s0; Here are enclosed the testing results divided in two tables:&]
[s0; &]
[ {{10000@(128) [s0; [* Testing results]]}}&]
[s0; &]
[ {{833:833:833:833:833:833:833:833:833:833:833:837h1;@1 [s0; Distro]
:: [s0; Version]
:: [s0; Architecture]
:: [s0; Desktop]
:: [s0; Version]
:: [s0; Comments]
:: [s0; Special folders]
:: [s0; System Info]
:: [s0; Memory Info]
:: [s0; OS Info]
:: [s0; Distro Info]
:: [s0; Default Exes]
::@2 [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.3]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Kubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.1.2]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Kde]
:: [s0; ]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.24]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
::@9 [s0; No virtual memory]
::@2 [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Opengeu]
:: [s0; 8.04]
:: [s0; 32]
:: [s0; Enlightenment]
:: [s0; 0.16]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; ]
::@9 [s0; Some not detected]
::@2 [s0; Ok]
::@9 [s0; No virtual memory]
::@2 [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.4]
:: [s0; ]
::@9 [s0; Some not detected]
::@2 [s0; Ok]
::@9 [s0; No virtual memory]
::@2 [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Slax]
:: [s0; ]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 3.5.9]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ubuntu]
:: [s0; 8.04]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ubuntu]
:: [s0; 8.04]
:: [s0; 64]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Xubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Xfce]
:: [s0; ]
::@9 [s0; Partial test. Expected better results]
:: [s0; Some not detected]
::@2 [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
::@9 [s0; No version]
::@2 [s0; Ok]
:: [s0; Vista]
:: [s0; Home Premium Edition]
:: [s0; 32]
:: [s0; Vista]
:: [s0; ]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; XP]
:: [s0; 5.1 SP3]
:: [s0; 32]
:: [s0; XP]
:: [s0; ]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]}}&]
[s0;0 &]
[s0;%- &]
[ {{998:998:998:998:998:998:998:998:998:1018h1;@1 [s0; Distro]
:: [s0; Version]
:: [s0; Architecture]
:: [s0; Desktop]
:: [s0; Version]
:: [s0; Drives Info]
:: [s0; Launch File]
:: [s0; Find and Kill Window]
:: [s0; Windows List]
:: [s0; Process List]
::@2 [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.3]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Kubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.1.2]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Kde]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.24]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Opengeu]
:: [s0; 8.04]
:: [s0; 32]
:: [s0; Enlightenment]
:: [s0; 0.16]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.4]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Slax]
:: [s0; ]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 3.5.9]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ubuntu]
:: [s0; 8.04]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ubuntu]
:: [s0; 8.04]
:: [s0; 64]
:: [s0; Gnome]
:: [s0; 2.22]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Xubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Xfce]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Vista]
:: [s0; Home Premium Edition]
:: [s0; 32]
:: [s0; Vista]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; XP]
:: [s0; 5.1 SP3]
:: [s0; 32]
:: [s0; XP]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]}}&]
[s0; &]
[s0; It seems OS CPU speed report is not reliable in Linux as it 
varies between program runs.&]
[s0; The same error has been found in system reporting programs and 
desktop cpu speed icons.&]
[s0;%- &]
[ {{1250:1250:1250:1250:1250:1250:1250:1250h1;@1 [s0; Distro]
:: [s0; Version]
:: [s0; Architecture]
:: [s0; Desktop]
:: [s0; Version]
:: [s0; Screen Snap]
:: [s0; Screen Record]
:: [s0; Installed software list]
::@2 [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Fedora]
:: [s0; 9]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.3]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Kubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.1.2]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Kde]
:: [s0; ]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Mandriva]
:: [s0; 2009]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.24]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Opengeu]
:: [s0; 8.04]
:: [s0; 32]
:: [s0; Enlightenment]
:: [s0; 0.16]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; OpenSuse]
:: [s0; 11]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 4.0.4]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Slax]
:: [s0; ]
:: [s0; 32]
:: [s0; Kde]
:: [s0; 3.5.9]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Ubuntu]
:: [s0; 8.04`-9.04]
:: [s0; 32]
:: [s0; Gnome]
:: [s0; 2.22`-]
:: [s0; Ok]
::@9 [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Ubuntu]
:: [s0; 8.04`-9.04]
:: [s0; 64]
:: [s0; Gnome]
:: [s0; 2.22`-]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Xubuntu]
:: [s0; 8.10]
:: [s0; 32]
:: [s0; Xfce]
:: [s0; ]
::@9 [s0; Not tested]
:: [s0;%- Not implement.]
:: [s0;%- Not implement.]
::@2 [s0; Vista]
:: [s0; Home Premium Edition]
:: [s0; 32]
:: [s0; Vista]
:: [s0; ]
::@9 [s0; Not tested]
:: [s0; Not tested]
:: [s0; Not tested]
::@2 [s0; XP]
:: [s0; 5.1 SP2`-3 Professional]
:: [s0; 32]
:: [s0; XP]
:: [s0; ]
:: [s0; Ok]
:: [s0; Ok]
:: [s0; Ok]}}&]
[s0; &]
[s0; &]
[s0; Next table includes the list of OS and Distros unsuccesfully 
tried and the reason:&]
[s0; &]
[ {{10000@(128) [s0; [* OS and Distros not tested]]}}&]
[s0;%- &]
[ {{1665:1665:1665:1665:1665:1675h1;@1 [s0; Distro]
:: [s0; Version]
:: [s0; Architecture]
:: [s0; Desktop]
:: [s0; Version]
:: [s0; Comments]
::@2 [s0; Freesbie]
:: [s0; 2.0]
:: [s0; 32]
:: [s0; ]
:: [s0; ]
:: [s0; [$2 Not possible to run without password]]
:: [s0; Fluxbox]
:: [s0; 7.10]
:: [s0; 32]
:: [s0; ]
:: [s0; ]
:: [s0; [$2 Live version not found]]
:: [s0; Gentoo]
:: [s0; ]
:: [s0; 32]
:: [s0; Xfce]
:: [s0; ]
:: [s0; [$2 Not possible to mount internal or usb HD]]
:: [s0; Knoppix]
:: [s0; 5.11]
:: [s0; 32]
:: [s0; Kde]
:: [s0; ]
:: [s0; [$2 Old Glib version]]
:: [s0; Slackware]
:: [s0; ]
:: [s0; 32]
:: [s0; ]
:: [s0; ]
:: [s0; [$2 Live version not found]]}}&]
[s0; ]