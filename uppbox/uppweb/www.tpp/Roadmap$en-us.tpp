topic "Changelog";
[2 $$0,0#00000000000000000000000000000000:Default]
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;t246;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
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
[{_}%EN-US 
[s0; [*R6 Roadmap]&]
[s0;4 &]
[s0; [*_3 Current release ]&]
[s0;4 &]
[s0; [*_4 1607]&]
[s0; &]
[s0; [* Library]&]
[s0; &]
[s0;i150;O0; Draw&]
[s0;l160;i160;O3; DisplayWithIcon (Display that adds an icon to any 
other Display)&]
[s0;l160;i160;O3; AttrText now has `'SetImage`' (places the icon 
to the left of  text)&]
[s0;i150;O0; CtrlLib: DropTree widget&]
[s0;i150;O0; Web: void AttachSocket(Socket`& socket, SOCKET s, bool 
blocking)&]
[s0;i150;O0; MSSQL: IdentityInsert helper (bypass of IDENTITY column 
insertion)&]
[s0;i150;O0; CtrlCore: RegisterSystemHotKey (system`-wide hotkey) 
&]
[s0;4 &]
[s0; [*_3 Previous releases]&]
[s0;4 &]
[s0; [*_4 1579]&]
[s0; &]
[s0; [* Library]&]
[s0;* &]
[s0;i150;O0; Core: Added support for many various 8`-bit encodings&]
[s0;i150;O0; Geom: Added new Computational Geometry algorithm: 2D convex 
hull calculation (ConvexHullOrder)&]
[s0;i150;O0; Sql: SqlExp, SqlSelect AsTable, Joins accept SqlSet&]
[s0;i150;O0; RichText: Optimized by caching paragraph data and layout&]
[s0;i150;O0; Draw, plugin/tif: Added GetActivePage support&]
[s0;i150;O0; Fixed a lot of minor bugs&]
[s0;*4 &]
[s0; [*_4 1517]&]
[s0; &]
[s0; Major overhaul graphics infrastructure is finished, U`+`+ is 
now capable of headless drawing operations&]
[s0; (e.g. drawing graphics and text into .png files in console applications, 
without X11)&]
[s0; (example: [^http`:`/`/www`.ultimatepp`.org`/reference`$ConsoleDraw`.html^ http://www
.ultimatepp.org/reference`$ConsoleDraw.html])&]
[s0; &]
[s0; Minor improvements:&]
[s0; &]
[s0; [* Library]&]
[s0;* &]
[s0;i150;O0; RegExp fixed to work with mingw, added GetMatchPos method&]
[s0;i150;O0; SetSurface functions for optimized raw output of RGBA 
data to screen (example: [^http`:`/`/www`.ultimatepp`.org`/reference`$SetSurface`.html^ h
ttp://www.ultimatepp.org/reference`$SetSurface.html])&]
[s0;i150;O0; Added Blackfin CPU support into Core&]
[s0;i150;O0; EditField`::NullText method now can provide an icon&]
[s0;i150;O0; RichText, Report: RichTextLayoutTracer ability (example: 
[^http`:`/`/www`.ultimatepp`.org`/reference`$RichTextLayoutTracer`.html^ http://www.
ultimatepp.org/reference`$RichTextLayoutTracer.html])&]
[s0;i150;O0; Core: Added StringStream`::Reserve&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; Added package internal include paths&]
[s0; Ctrl`+mouse wheel changes font size&]
[s0;*4 &]
[s0; [*_4 1314]&]
[s0; &]
[s0; [* Library]&]
[s0; &]
[s0;i150;O0; CtrlCore&]
[s0;l160;i160;O3; Fixed several X11/Compiz/SCIM compatibility issues&]
[s0;i150;O0; RichText&]
[s0;l160;i150;O3; QTF: Added text`-type rich object format&]
[s0;i150;O0; GridCtrl&]
[s0;l160;i150;O3; Added WhenMoveRow, CancelMove&]
[s0;l160;i150;O3; Improved search results highlighting&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; Import directory source tree into package&]
[s0;i150;O0; Support for multiline svn commit messages&]
[s0;i150;O0; Assist`+`+ now supports SQL schema files&]
[s0;i150;O0; FileTabs now persistent&]
[s0;i150;O0; Non`-fixed pitch fonts allowed in editor (used as fixed...)&]
[s0; &]
[s0; [*_4 1254]&]
[s0;*4 &]
[s0; [* Library]&]
[s0; &]
[s0;i150;O0; Various improvements in SQL related stuff (SqlPerformScript, 
SqlBinary enable for PGSQL) &]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; Highlighting of .sch and .sql files &]
[s0;i150;O0; Find in files now has separate output console &]
[s0;i150;O0; Select package dialog `'All`' option replaced by the 
selection of more understandable options, main packages now displayed 
bold&]
[s0; &]
[s0; [*_4 1205]&]
[s0;*4 &]
[s0; [* Library]&]
[s0; &]
[s0;i150;O0; New GUI multithreading architecture &]
[s0; &]
[s0; [* TheIDE ]&]
[s0; &]
[s0;i150;O0; Layout designer: option to resize dialog without springs 
&]
[s0;i150;O0; No more confusing switches of .lay, .iml to text mode 
(instead designer) &]
[s0;i150;O0; One more redesign of code navigator &]
[s0;i150;O0; Ctrl`+Click onto symbol jumps to its definition &]
[s0;i150;O0; Package selector now shows the nest&]
[s0;*4 &]
[s0; [*_4 1124]&]
[s0;*4 &]
[s0;%- [* Library]&]
[s0;*%- &]
[s0;i150;O0; Change in SetDateFilter format, cleanup in related docs 
&]
[s0;i150;O0; Improved translation docs &]
[s0;i150;O0; Added runtime check for serializing RichValue with missing 
Register &]
[s0;i150;O0; Docking: CreateDockable<T> now returns type T &]
[s0;i150;O0; mrjt`'s MultiList now merged into ColumnList &]
[s0;i150;O0; TabBar: Tab Stacking and sorting added. Other changes. 
&]
[s0;i150;O0; Drawing refactored &]
[s0;*%- &]
[s0;*%- &]
[s0;%- [* TheIDE ]&]
[s0;*%- &]
[s0;i150;O0; Refactored CodeNavigator, search symbol (Ctrl`+Q) now 
copies current id search field &]
[s0;*4 &]
[s0;%- [*_4 1096]&]
[s0;*4%- &]
[s0;%- [* Library]&]
[s0;*%- &]
[s0;i150;O0;%- Painter: High quality, `"SVG/PDF strength`" software 
renderer&]
[s0;i150;O0;%- HttpClient improvements&]
[s0;i150;O0;%- JPGRaster now can read EXIF thumbnails&]
[s0;i150;O0;%- ODBC SQL interface&]
[s0;i150;O0;%- Microsoft SQL Server interface improved&]
[s0;i150;O0;%- Multithreading: ConditionVarable and LazyUpdate classes&]
[s0;i150;O0;%- LocalProcess class&]
[s0;i150;O0;%- RichText: EncodeHTML support for superscript, subscript, 
strikeout&]
[s0;i150;O0;%- and smallcaps&]
[s0;i150;O0;%- Mersenne twister based Random&]
[s0;%- &]
[s0;%- [* TheIDE]&]
[s0;*%- &]
[s0;i150;O0;%- Win32 .pdb debugger:&]
[s0;l160;i150;O3;%- shows tooltip with values of variables&]
[s0;l160;i150;O3;%- improved displaying of strings in pdb debugger&]
[s0;l160;i150;O3;%- watches are remembered, Clear all watches function, 
Drag`&Drop to watches&]
[s0;i150;O0;%- Packages can be sorted by name&]
[s0;i150;O0;%- Packages now can be colored and assigned bold/italic 
font&]
[s0;i150;O0;%- Package files underlined if recently changed&]
[s0;i150;O0;%- SVN support, SVN history of file&]
[s0;i150;O0;%- Compare with file, compare with patch&]
[s0;i150;O0;%- Assist`+`+&]
[s0;l160;i150;O3;%- New heurestic error recovery of C`+`+ parser&]
[s0;l160;i150;O3;%- New code navigator bar&]
[s0;l160;i150;O3;%- Position of Assist parameter info improved&]
[s0;l160;i150;O3;%- Context go to (Alt`+J) now jumps to layout designer 
when invoked on layout class template&]
[s0;i150;O0;%- Topic`+`+ finished; documentation now visible (and 
editable) as tooltip annotations of sources&]
[s0;i150;O0;%- Abbreviations: e.g. type `"i`" and press Ctrl`+`[.`] 
to expand it to if() ;&]
[s0;i150;O0;%- Icon editor: free angle rotation&]
[s0;i150;O0;%- Insert`" color or U`+`+ specific includes (.lay, .iml, 
.tpp group)&]
[s0;i150;O0;%- Print command (of source files)&]
[s0;i150;O0;%- Editor: ToUpper/Lower/InitCaps/SwapCase &]
[s0; &]
[s0; [*_4 2008.1]&]
[s0; &]
[s0; [* Library]&]
[s0; &]
[s0;i150;O0; New very fast String/WString implementation&]
[s0;i150;O0; New high performance (mostly) lock`-free heap allocator, 
&]
[s0;i150;O0; Improved multithreading support&]
[s0;i150;O0; CoWork multicore loop paralelization class&]
[s0;i150;O0; Unified Drag`&Drop support&]
[s0;i150;O0; PostgreSQL support&]
[s0;i150;O0; Win64 support (except debugger)&]
[s0;i150;O0; QuickTabs class&]
[s0;i150;O0; HeaderCtrl can now move (reorganize) tabs&]
[s0;i150;O0; ArrayCtrl automated column sorting&]
[s0;i150;O0; Chameleon Look`&feel improvements under GTK and Vista&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; Topic`+`+ documentation editor now integrated into main 
window&]
[s0;i150;O0; Help Help integrated into main window&]
[s0; &]
[s0; &]
[s0; [*_4 2007.1]&]
[s0; &]
[s0; [* Library]&]
[s0;* &]
[s0;i150;O0; Pdf export and printing in Linux finished&]
[s0;i150;O0; Raster image infrastructure completely reworked&]
[s0;i150;O0; `"Chameleon`" skinning system which allows both native 
look of U`+`+ applications across platforms AND custom skins 
to be designed/used.&]
[s0;i150;O0; New useful widgets: GridCtrl, CalendarCtrl and DateTimeCtrl&]
[s0;i150;O0; Sql expressions are now adjusted before being executed 
on particular RDBMS target&]
[s0;i150;O0; Library moved to Upp namespace&]
[s0;i150;O0; FreeBSD port is now regular part of U`+`+&]
[s0;i150;O0; Experimental PocketPC support was introduced&]
[s0;i150;O0; Library fixed to support ARM and PowerPC CPUs&]
[s0;i150;O0; A lot of new documentation and tutorials&]
[s0;i150;O0; Many minor improvements and bug fixes&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; New Icon designer (supports alpha channel and has tools 
to produce antialiased icons)&]
[s0; &]
[s0; [* Distribution]&]
[s0;* &]
[s0;i150;O0; FreeBSD port available&]
[s0;i150;O0; Ubuntu .deb packages released&]
[s0; &]
[s0; &]
[s0; [*_3 Previous releases]&]
[s0;*3 &]
[s0; [*_4 605]&]
[s0; &]
[s0; [* Library]&]
[s0;* &]
[s0;i150;O0; XML parser refinements (faster, easier to use)&]
[s0;* &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; `"Hydra build`" `- multi`-CPU building&]
[s0;i150;O0; further Assist`+`+ improvements&]
[s0; &]
[s0; [* Distribution]&]
[s0;* &]
[s0;i150;O0; new Windows installer `- download size reduced by 50%&]
[s0; &]
[s0;*3 &]
[s0; [*_4 602]&]
[s0; &]
[s0; [* Library]&]
[s0;* &]
[s0;i150;O0; New Report package.&]
[s0;i150;O0; Fixed multi`-threading issues in Linux.&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; Assist`+`+&]
[s0;l160;i150;O2; Fixed many C`+`+ parsing issues and optimized&]
[s0;l160;i150;O2; `"Virtual methods`" tool&]
[s0;l160;i150;O2; `"THISBACKs`" tool&]
[s0;i150;O0; `"Generate code..`" tool of Layout designer able to 
generate useful code snippets&]
[s0;i150;O0; `"Show opposite`" (Alt`+O) switches .h/.cpp files&]
[s0;i150;O0; `"Complete identifier`" (Alt`+,) `- based on identifiers 
in the file (no C`+`+ parsing intelligence)&]
[s0;i150;O0; Fixed support for global variables in PDB debugger&]
[s0;i150;O0; Package organizer redesigned, `"When`" conditions now 
support logical operators, `"uses`" can be conditional&]
[s0;i150;O0; New fine`-grained optimization system with `"Optimize 
for speed`" / `"Optimize for size`" / `"Optimal`" (only explicitly 
marked files are optimized for speed) modes&]
[s0;i150;O0; New TheIDE command`-line mode, including compilation 
(via umk utility)&]
[s0;*_3 &]
[s0; [*_4 511]&]
[s0; &]
[s0; [* U`+`+ Library]&]
[s0; &]
[s0;i150;O0; New XML support in Core&]
[s0;i150;O0; Linux/AMD64 is now supported&]
[s0;i150;O0; X11 fixes improve stability with less common window 
managers, input method problem fixed as well&]
[s0;i150;O0; New kind of callbacks `- pteback `- to avoid dangling 
callback situation problem&]
[s0;i150;O0; Sqlite was added as source`-based plugin together with 
U`+`+ adapter&]
[s0;i150;O0; A lot of new documentation&]
[s0; &]
[s0; [* TheIDE]&]
[s0; &]
[s0;i150;O0; File tabs are redesigned&]
[s0;i150;O0; Source editor has now scripting language&]
[s0;i150;O0; `"Calculator`" console&]
[s0;i150;O0; Layout of IDE now redesigned, bottom pane now contains 
browser/console/debugger/calculator switched by tabs&]
[s0;i150;O0; ASSIST`+`+:&]
[s0;l192;i150;O2; Improved C`+`+ code analysis now able to resolve 
class hierarchy issues, code browser now displays base classes, 
methods, virtual methods, overrides etc...&]
[s0;l192;i150;O2; New assist function now suggests list of methods 
and attributes after typing `'`->`' or `'.`' or after Ctrl`+Space.&]
[s0;l192;i150;O2; Navigate in the file and Navigate functions simplify 
moving to symbol with specified name&]
[s0;l192;i150;O2; Copy definition/declaration is able to convert 
method declaration (inside class declaration) to definition and 
back (works with more than one method as well)&]
[s0;l192;i150;O2; Goto definition/declaration moves between definitions 
and declarations of current method&]
[s0; &]
[s0; [* Distribution]&]
[s0; &]
[s0;i150;O0; U`+`+/Win now ships with SDL library and contains nice 
SDLExample as well as SDL project templates.&]
[s0; ]