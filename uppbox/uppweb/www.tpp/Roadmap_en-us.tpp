topic "Roadmap";
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[ph2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;t246;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*_@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
[t4167;C2 $$10,0#37138531426314131251341829483380:class]
[l288;a17;*1 $$11,11#70004532496200323422659154056402:requirement]
[i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam]
[b167;C2 $$13,13#92430459443460461911108080531343:item1]
[i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2]
[*@2$(0.128.128)2 $$15,15#34511555403152284025741354420178:NewsDate]
[l321;*C$7;2 $$16,16#03451589433145915344929335295360:result]
[l321;b83;a83;*C$7;2 $$17,17#07531550463529505371228428965313:result`-line]
[l160;t4167;*C+117 $$18,5#88603949442205825958800053222425:package`-title]
[2 $$19,0#53580023442335529039900623488521:gap]
[t4167;C2 $$20,20#70211524482531209251820423858195:class`-nested]
[b50;2 $$21,21#03324558446220344731010354752573:Par]
[b125;a21;*2 $$22,22#72A57D7B347482931820FBB21B426750:subtitle]
[l42;b42;a42;phO0;2 $$23,23#42C8ED58A1FE5FAB0FCEA41746BFF560:point]
[b83;*_2 $$24,24#F44F66EA0BD27C61EACACB2D8ED88A05:release]
[2 $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[s2; Roadmap&]
[s24; Upcoming release&]
[s3; 2018.1 (rev 11834) (Mar 2018)&]
[s22; Core&]
[s5;l160;i150;O0; New low`-overhead CoWork [^https`:`/`/www`.ultimatepp`.org`/srcdoc`$Core`$Tutorial`$en`-us`.html`#Section`_7`_7^ p
arallelization method / pattern `- Loop]&]
[s5;l160;i150;O0; Throughout the Core, many rvalue / universal reference 
related optimizations&]
[s5;l160;i150;O0; CoPartition optimized to perform the work in calling 
thread if data size is small&]
[s5;l160;i150;O0; SeedRandom without parameter now reseeds the random 
with host entropy&]
[s5;l160;i150;O0; Array/Vector new [^https`:`/`/www`.ultimatepp`.org`/srcdoc`$Core`$Tutorial`$en`-us`.html`#Section`_3`_2^ G
et/Set] methods&]
[s5;l160;i150;O0; New features for WebSocket client mode&]
[s5; &]
[s5; [* plugin/bz2]&]
[s5;l160;i150;O0; plugin/bz2: Streaming support&]
[s5; &]
[s5; [* Painter]&]
[s5;l160;i150;O0; Co Option to run parallel&]
[s5;l160;i150;O0; BufferPainter`::PreClipDashed&]
[s5; &]
[s5; [* PdfDraw]&]
[s5;l160;i150;O0; PdfDraw: DrawJPEG to directly embed JPEG compressed 
images into PDF&]
[s5; &]
[s5; [* GUI programming]&]
[s5;l160;i150;O0; In Windows, owned windows now have minimize box 
disabled (as minimizing of owned windows leads to strange behaviour)&]
[s5;l160;i150;O0; LineEdit`::WhenScroll event&]
[s5;l160;i150;O0; New OptionBox widget (Option with LabelBox like 
graphics, also able to automatically enable/disable contained 
widgets)&]
[s5;l160;i150;O0; FileSel now has option to add widgets into the 
dialog (e.g. to specify save format)&]
[s5; &]
[s5; [* TheIDE]&]
[s5;* &]
[s5;l160;i150;O0; Very long files (>400MB) are now opened for view 
rather than edit.&]
[s5;l160;i150;O0; Some trivial merge conflict helper tools&]
[s5;l160;i150;O0; IconDes improvements&]
[s5;l160;i150;O0; Esc scripting language now has `'continue`' statement&]
[s5; &]
[s5; &]
[s24; Current release&]
[s3; 2017.2 (rev 11540) (Dec 2017)&]
[s22; Core&]
[s5;l160;i150;O0; New [* AsyncWork ]class `- U`+`+ future`-alike tool&]
[s5;l160;i150;O0; CoWork: Exception propagation from worker threads, 
job cancellation support.&]
[s5;l160;i150;O0; Bits class optimized, it is now possible to set 
multiple bits (count parameter)&]
[s5;l160;i150;O0; WebSocket refactored for asynchronous operation&]
[s5;l160;i150;O0; UTF`-32 support functions, UnicodeCompose and UnicodeDecompose 
functions, support for UTF16 surrogate pairs&]
[s5;l160;i150;O0; DeleteFolderDeep now deletes symlinks&]
[s5;l160;i150;O0; [* MakeOne ]function (alternative to One`::Create)&]
[s5;l160;i150;O0; LoadFromFile, StoreToFile `- Event variant&]
[s5;l160;i150;O0; [* ReverseRange ]and [* SortedRange]&]
[s5;l160;i150;O0; Server Name Indicator support in Socket and HttpRequest&]
[s5;l160;i150;O0; [* SSL1.1] API support&]
[s5;l160;i150;O0; RegisterGlobalSerialize&]
[s5; &]
[s22; GUI programming&]
[s5;l160;i150;O0; ArrayCtrl: Improvements in sorting, new public GetCellRect, 
GetCellRectM, GetSelKeys, SetRowDisplay, SetColumnDisplay, AcceptRow 
methods&]
[s5;l160;i150;O0; Button NakedStyle style.&]
[s5;l160;i150;O0; WithDropChoice: Set/Remove entry in drop`-down list&]
[s5;l160;i150;O0; TextCtrl`::Load refactored, now can break very long 
(>1MB) lines&]
[s5;l160;i150;O0; TreeCtrl: GetOpenIds, OpenIds&]
[s5;l160;i150;O0; IdCtrls, SqlCtrls refactored, improved&]
[s5;l160;i150;O0; Option: SetColor&]
[s5;l160;i150;O0; Edit...Spin: RoundFromMin modifier method&]
[s5;l160;i150;O0; ColorPopup now has button to enter the color as 
text&]
[s5;l160;i150;O0; New features in ScatterDraw, ScatterCtrl&]
[s5;l160;i150;O0; Header / Footer can now be changed using paragraph 
properties&]
[s5;l160;i150;O0; QTFDisplay now ignores text color / paper if style 
is not normal&]
[s22; TheIDE&]
[s5;l192;i150;O0; Improved debugging of console applications with 
MinGW&]
[s5;l192;i150;O0; Debugging with GDB is now much more stable&]
[s5;l192;i150;O0; [* Macro manager]&]
[s5;l192;i150;O0; Explicit `"Go to line.. `"operation (in addition 
to Navigator)&]
[s5;l192;i150;O0; BRC now supports LZ4, LZMA and Zstd compression&]
[s5;l192;i150;O0; File comparison tool improved&]
[s5;l192;i150;O0; Directory comparison now can show/filter new/modified/removed 
files&]
[s5;l192;i150;O0; [* Dark theme] highlighting&]
[s5;l192;i150;O0; Duplicate package function&]
[s5;l192;i150;O0; [* `"Find all`" ]button in normal Search (finds all 
occurrences in current file). &]
[s5;l192;i150;O0; HexView now remembers position&]
[s5;l192;i150;O0; Selection can be interpreted as error list&]
[s5;l192;i150;O0; TheIDE now shows the number of selected characters&]
[s5;l192;i150;O0; Tab size now possible on per`-file basis&]
[s5;l192;i150;O0; Repository synchronize refactored, now supports 
both svn and git&]
[s5;l192;i150;O0; Layout visgen improvements&]
[s5;l192;i150;O0; TheIDE  now supports [* Visual Studio 2017] C`+`+ 
compiler auto setup&]
[s5;l192;i150;O0; MS build tools auto setup&]
[s22; 3rd party modules&]
[s5;l192;i150;O0; MinGW 64 updated to GCC`-7.2.0&]
[s5;l192;i150;O0; OpenSSL for VC`+`+ updated to 1.0.2l&]
[s5;l192;i150;O0; plugin/lz4: lz4 updated to 1.7.3&]
[s5;l192;i150;O0; plugin/bz2: updated to 1.0.6&]
[s5;l192;i150;O0; plugin/jpg: updated to version 9b&]
[s5;l192;i150;O0; plugin/pcre: updated to 8.41&]
[s5;l192;i150;O0; plugin/png: updated to 1.2.57&]
[s5;l192;i150;O0; plugin/sqlite3: updated to 3.17.9&]
[s5;l192;i150;O0; plugin/z: Updated to 1.2.11&]
[s5;l192;i150;O0; plugin/Eigen: Updated to version 3.3.4&]
[s5; &]
[s0; &]
[s3;H4; Archival releases:&]
[s5; If you are looking for informations about archival releases 
`- you can find them on the following [^topic`:`/`/uppweb`/www`/RoadmapHistorical`$en`-us^ s
ite].]]