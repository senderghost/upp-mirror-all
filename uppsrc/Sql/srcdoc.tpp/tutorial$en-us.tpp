topic "SQL Tutorial";
[2 $$0,0#00000000000000000000000000000000:Default]
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[H4;b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;ph2 $$5,5#45413000475342174754091244180557:text]
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
[s2; SQL Tutorial&]
[s3; Table of contents&]
[s0; &]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#1^ 1. SqlSession, 
Sql, opening database connection]&]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#2^ 2. Using global 
main database, executing statements with parameters, getting 
resultset info]&]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#3^ 3. Using SqlExp]&]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#4^ 4. Schema file]&]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#5^ 5. Using schema 
file to define SqlId constants]&]
[s0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us`#6^ 6. Using structures 
defined by schema files]&]
[s0; &]
[s3;:1: 1. SqlSession, Sql, opening database connection&]
[s5; SqlSession derived objects represent database connection. Each 
SQL database (Sqlite3, Microsoft SQL, Oracle, MySQL, PostgreSQL) 
has its own session class derived from SqlSession. Sql class 
is used to issue SQL statements and retrieve results:&]
[s7; &]
[s7; #include <Core/Core.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|[* Sqlite3Session ]sqlite3;&]
[s7; -|if(!sqlite3.[* Open](ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.[* SetTrace();]&]
[s7; #endif&]
[s7; &]
[s7; -|[* Sql] sql(sqlite3);&]
[s7; -|sql.[* Execute](`"select date(`'now`')`");&]
[s7; -|while(sql.[* Fetch]())&]
[s7; -|-|Cout() << [* sql`[0`] ]<< `'`\n`' << ;&]
[s7; `}&]
[s7; &]
[s5; In this tutorial, we are using Sqlite3 database. The connection 
method varies with database; in this case it is done using [* Open 
]statement.&]
[s5; [* SetTrace ]is useful in debug mode `- all issued SQL statements 
and SQL errors are logged in standard U`+`+ log.&]
[s5; Each [* Sql] instance has to be associated to some SqlSession 
`- it is passed as constructor parameter (parameter`-less Sql 
constructor uses global session, more on that in section 2.). 
To execute SQL statements, use [* Execute]. If executed statement 
is Select, it may return a result set, which is retrieved using 
[* Fetch]. Columns of result set are then accessed by Sql`::operator`[`] 
using index of column (starts with 0). Values are returned as 
Value type.&]
[s5; &]
[s3;:2: 2. Using global main database, executing statements with 
parameters, getting resultset info&]
[s5; Most applications need to work with just single database backend, 
therefore repeating SqlSession parameter in all Sql declarations 
would be tedious.&]
[s5; To this end U`+`+ supports concept of `"main database`" which 
is represented by [* SQL] variable. [* SQL] is of Sql type. When 
any other Sql variable is created with default constructor (no 
session parameter provided), it uses the same session as the 
one the SQL is bound to. To assign session to global SQL, use 
operator`=:&]
[s7; #include <Core/Core.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; &]
[s7; -|[* SQL `= ]sqlite3;&]
[s7; -|&]
[s7; -|[* SQL.]Execute(`"drop table TEST`");&]
[s7; -|SQL.ClearError();&]
[s7; -|SQL.Execute(`"create table TEST (A INTEGER, B TEXT)`");&]
[s7; &]
[s7; -|for(int i `= 0; i < 10; i`+`+)&]
[s7; -|-|SQL.[* Execute](`"insert into TEST(A, B) values ([* ?], [* ?])`", 
i, AsString(3 `* i));&]
[s7; &]
[s7; -|Sql sql;&]
[s7; -|sql.Execute(`"select `* from TEST`");&]
[s7; -|for(int i `= 0; i < sql.[* GetColumns](); i`+`+)&]
[s7; -|-|Cout() << sql.[* GetColumnInfo](i).[* name ]<< `'`\n`';&]
[s7; -|while(sql.Fetch())&]
[s7; -|-|Cout() << sql`[0`] << `" `\`'`" << sql`[1`] << `"`\`'`\n`";&]
[s7; `}&]
[s7; &]
[s5; As global [* SQL] is regular Sql variable too, it can be used 
to issue SQL statements.&]
[s5; [/ Warning: While it is possible to issue ][*/ select][/  statements 
through ][*/ SQL][/ , based on experience this is not recommended 
`- way too often result set of ][*/ select][/  is canceled by issuing 
some other command, e.g. in routine called as part of Fetch loop. 
One exception to this rule is using SQL`::operator% to fetch single 
value like ][*C@5+75 String txt `= SQL % Select(TEXT).From(DOCTEMPLATE).Where(ID 
`=`= id); ][/ (see further tutorial topics for detailed explanation 
of this code).]&]
[s5; To get information about result set columns, you can use [* GetColumns 
]to retrieve the number of columns and [* GetColumnInfo] to retrieve 
information about columns `- returns [* SqlColumnInfo] reference 
with information like name or type of column.&]
[s5; &]
[s3;:3: 3. Using SqlExp&]
[s5; U`+`+ contains an unique feature, `"SqlExp`". This is a mechanism 
where you construct SQL statements as C`+`+ expressions (using 
heavily overloaded operators).&]
[s5; There are three advantages to this approach:&]
[s5;l160;i150;O0; SQL statements are at least partially checked at 
compile time&]
[s5;l160;i150;O0; As such statements are yet to be interpreted, it 
is possible to hide some differences between DB engines&]
[s5;l160;i150;O0; It is much easier to create complex dynamic SQL 
statements&]
[s5; Database entity identifiers (like table or column names) can 
be defined as [* SqlId] type. For the complete lest of supported 
SQL statements, see [^topic`:`/`/Sql`/src`/SqlExp`$en`-us^ SqlExp 
in examples].&]
[s7; #include <Core/Core.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; &]
[s7; -|SQL `= sqlite3;&]
[s7; -|&]
[s7; -|SQL.Execute(`"drop table TEST`");&]
[s7; -|SQL.ClearError();&]
[s7; -|SQL.Execute(`"create table TEST (A INTEGER, B TEXT)`");&]
[s7; &]
[s7; -|[* SqlId] A(`"A`"), B(`"B`"), TEST(`"TEST`");&]
[s7; &]
[s7; -|for(int i `= 0; i < 10; i`+`+)&]
[s7; -|-|SQL [* `* Insert(TEST)(A, ]i[* )(B, ]AsString(3 `* i)[* );]&]
[s7; &]
[s7; -|Sql sql;&]
[s7; -|sql [* `* Select(A, B).From(TEST);]&]
[s7; -|while(sql.Fetch())&]
[s7; -|-|Cout() << [* sql`[A`]] << `" `\`'`" << [* sql`[B`]] << `"`\`'`\n`";&]
[s7; `}&]
[s7; &]
[s5; SqlId identifiers can be also used as parameter of Sql`::operator`[`] 
to retrieve particular columns of result`-set.&]
[s5; &]
[s3;:4: 4. Schema file&]
[s5; Schema files can be used to describe the database schema. Such 
schema files can be used to upload the schema to the database, 
to defined SqlId constants and also to work with database records 
as C`+`+ structures.&]
[s5; Following example demonstrates using schema file to create database 
schema in SQL database server.&]
[s5; MyApp.sch:&]
[s7; &]
[s7; [* TABLE(TEST)]&]
[s7; [* -|INT        (A)]&]
[s7; [* -|STRING     (B, 200)]&]
[s7; [* END`_TABLE]&]
[s7; &]
[s5; MyApp.h&]
[s7; &]
[s7; &]
[s7; #ifndef `_MyApp`_h`_&]
[s7; #define `_MyApp`_h`_&]
[s7; &]
[s7; #include <Core/Core.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; [* #define SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>]&]
[s7; [* #define MODEL <Sql04/MyApp.sch>]&]
[s7; [* #include `"Sql/sch`_header.h`"]&]
[s7; &]
[s7; #endif&]
[s7;* &]
[s5; main.cpp&]
[s7; #include `"MyApp.h`"&]
[s7; &]
[s7; [* #include <Sql/sch`_schema.h>]&]
[s7; [* #include <Sql/sch`_source.h>]&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; &]
[s7; -|SQL `= sqlite3;&]
[s7; &]
[s7; [* -|SqlSchema sch(SQLITE3);]&]
[s7; [* -|All`_Tables(sch);]&]
[s7; [* -|SqlPerformScript(sch.Upgrade());]&]
[s7; [* -|SqlPerformScript(sch.Attributes());]&]
[s7; [* -|SQL.ClearError();]&]
[s7; &]
[s7; -|SqlId A(`"A`"), B(`"B`"), TEST(`"TEST`");&]
[s7; &]
[s7; -|for(int i `= 0; i < 10; i`+`+)&]
[s7; -|-|SQL `* Insert(TEST)(A, i)(B, AsString(3 `* i));&]
[s7; &]
[s7; -|Sql sql;&]
[s7; -|sql `* Select(A, B).From(TEST);&]
[s7; -|while(sql.Fetch())&]
[s7; -|-|Cout() << sql`[A`] << `" `\`'`" << sql`[B`] << `"`\`'`\n`";&]
[s7; `}&]
[s7;* &]
[s5; &]
[s3;:5: 5. Using schema file to define SqlId constants&]
[s5; As names of columns are present in the database schema, it is 
natural to recycle them to create SqlId constants.&]
[s5; However, due to C`+`+ one definition rule (.sch files are interpreted 
as C`+`+ sources, using changing set of macros), you have to 
mark identifiers using underscore:&]
[s5; MyApp.sch:&]
[s7; [* TABLE`_](TEST)&]
[s7; -|[* INT`_]        (A)&]
[s7; -|[* STRING`_]     (B, 200)&]
[s7; END`_TABLE&]
[s7; &]
[s7; TABLE`_(TEST2)&]
[s7; -|[* INT]        (A)&]
[s7; -|[* STRING]     (B, 200)&]
[s7; END`_TABLE&]
[s5; &]
[s5; MyApp.h:&]
[s7; #ifndef `_MyApp`_h`_&]
[s7; #define `_MyApp`_h`_&]
[s7; &]
[s7; #include <Core/Core.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; #define SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>&]
[s7; #define MODEL <Sql05/MyApp.sch>&]
[s7; #include `"Sql/sch`_header.h`"&]
[s7; &]
[s7; #endif&]
[s7; &]
[s5; main.cpp:&]
[s7; &]
[s7; #include `"MyApp.h`"&]
[s7; &]
[s7; #include <Sql/sch`_schema.h>&]
[s7; #include <Sql/sch`_source.h>&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; &]
[s7; -|SQL `= sqlite3;&]
[s7; &]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; -|SQL.ClearError();&]
[s7; &]
[s7; -|for(int i `= 0; i < 10; i`+`+)&]
[s7; -|-|SQL `* Insert(TEST)(A, i)(B, AsString(3 `* i));&]
[s7; &]
[s7; -|Sql sql;&]
[s7; -|sql `* Select(A, B).From(TEST);&]
[s7; -|while(sql.Fetch())&]
[s7; -|-|Cout() << sql`[A`] << `" `\`'`" << sql`[B`] << `"`\`'`\n`";&]
[s7; `}&]
[s7; &]
[s5; &]
[s3;:6: 6. Using structures defined by schema files&]
[s5; Schema files also define structures that can be used to fetch, 
insert or update database records. Names of such structures are 
identical to the names of tables, with [* S`_] prefix:&]
[s7; #include `"MyApp.h`"&]
[s7; &]
[s7; #include <Sql/sch`_schema.h>&]
[s7; #include <Sql/sch`_source.h>&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"simple.db`"))) `{&]
[s7; -|-|Cout() << `"Can`'t create or open database file`\n`";&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; &]
[s7; -|SQL `= sqlite3;&]
[s7; &]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; -|SQL.ClearError();&]
[s7; &]
[s7; -|[* S`_TEST] x;&]
[s7; -|for(int i `= 0; i < 10; i`+`+) `{&]
[s7; -|-|[* x.A `= i;]&]
[s7; -|-|[* x.B `= AsString(3 `* i);]&]
[s7; -|-|[* SQL `* Insert(x);]&]
[s7; -|`}&]
[s7; &]
[s7; -|Sql sql;&]
[s7; -|sql `* Select([* x]).From(TEST);&]
[s7; -|while(sql.Fetch([* x]))&]
[s7; -|-|Cout() << [* x.A] << `" `\`'`" << [* x.B] << `"`\`'`\n`";&]
[s7; `}&]
[s5; &]
[s3; Recommended tutorials:&]
[s5; If you want to learn more, we have several tutorials that you 
can find useful:&]
[s5;l160;i150;O0;~~~0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us^ Skylark] 
`- now you know everything about databases `- why not to use 
your knowledge to become web development star?&]
[s5;l160;i150;O0;~~~0; [^topic`:`/`/Core`/srcdoc`/CoreTutorial`$en`-us^ U`+`+ 
Core value types] `- still not very confident with U`+`+. In 
this tutorial you will learn basics.]]