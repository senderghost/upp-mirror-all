topic "Tutorial";
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
[s2; About Watchdog&]
[s0; &]
[s0; Watchdog is a skylark based platform for testing and continuous 
integration. It consist of two parts, the Server and reference 
implementation of [^topic`:`/`/Watchdog`/srcdoc`/Client`$en`-us^ Client]. 
However, anyone is free to create their own clients, using the 
public [^topic`:`/`/Watchdog`/srcdoc`/API`$en`-us^ API].&]
[s0; &]
[s0; The Server monitors activity in SVN, and can distribute the 
work among clients. The client can do pretty much anything, e.g. 
compile a package, run unit tests, etc. After the client does 
it`'s job, it calls back to the server, announcing the result. 
All the results, commits and registered clients are browsable 
through the web interface provided by the Server.&]
[s0; &]
[s0; Everything from server behavior to SVN  address is fully configurable. 
It should be possible to use this application for monitoring 
of any project as long as it is available through SVN. With a 
little bit of extra work, support for other version control systems 
should be possible as well.&]
[s0; &]
[s0; Some notable features:&]
[s0;l192;i150;O0; Distributed work, many different clients can work 
in parallel&]
[s0;l192;i150;O0; Simple, fast `& easy to use web interface&]
[s0;l192;i150;O0; Public HTTP API, client can be anything&]
[s0;l192;i150;O0; Configurable RSS feeds to keep interested users 
up`-to`-date&]
[s0;l192;i150;O0; Web interface can be skinned (by simply modifying 
witz templates)&]
[s0;l192;i150;O0; Can be used `'as is`' or embedded into existing 
web pages&]
[s0; ]]