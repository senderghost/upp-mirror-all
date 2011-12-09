topic "SqlExp in examples";
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
[s2; SqlExp in examples&]
[s0; &]
[s0; (with compiled results for PostgreSQL dialect)&]
[s0; &]
[s0; &]
[ {{4918:5082^ [s0;%- [* SqlExp C`+`+]]
:: [s0;%- [* PostgreSQL]]
:: [s0;%- [*C1 Select(COLUMN)]&]
[s0;%- [*C1 .From(TABLE)]]
:: [s0;%- [*C1 select COLUMN]&]
[s0;%- [*C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN.Of(TABLE)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 TABLE.COLUMN]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN.As(A)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 COLUMN as A]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN`&A][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 COLUMN`$A]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN`[3`]][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 COLUMN3]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN1 % COLUMN2][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 mod(COLUMN1, COLUMN2)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 COLUMN1 `| COLUMN2][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 COLUMN1 `|`| COLUMN2]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlFunc(`"any`_fn`", COLUMN, 2)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 any`_fn(COLUMN, 2)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Distinct(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 distinct COLUMN]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Distinct(SqlSet(COLUMN1, COLUMN2))][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 distinct COLUMN1, COLUMN2]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 All(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 all COLUMN]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Count(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 count(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlAll()][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 `*]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlCountRows()][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 count(`*)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .OrderBy(][*C1 Descending(COLUMN)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  order by ][*C1 COLUMN desc]]
:: [s0;%- [C1 Select(][*C1 SqlMax(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 max(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlMin(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 min(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlSum(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 sum(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Avg(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 avg(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Stddev(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 stddev(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Variance(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 variance(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Greatest(COLUMN1, COLUMN2)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 greatest(COLUMN1, COLUMN2)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Least(COLUMN1, COLUMN2)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 least(COLUMN1, COLUMN2)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Upper(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 upper(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Lower(COLUMN)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 lower(COLUMN)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Substr(COLUMN, 1)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 SUBSTR(COLUMN, 1)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Substr(COLUMN, 2, 1)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 SUBSTR(COLUMN, 2, 1)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 Instr(COLUMN, `"hello`")][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 INSTR(COLUMN, `'hello`')]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 SqlNvl(COLUMN1, COLUMN2)][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 coalesce(COLUMN1, COLUMN2)]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(][*C1 NextVal(SEQ)][C1 ).][*C1 Get()]]
:: [s0;%- [C1 select ][*C1 nextval(`'SEQ`')]]
:: [s0;%- [C1 Select(][*C1 CurrVal(SEQ)][C1 ).][*C1 Get()]]
:: [s0;%- [C1 select ][*C1 currval(`'SEQ`')]]
:: [s0;%- [C1 Select(][*C1 SqlArg()][C1 )]&]
[s0;%- [C1 .From(TABLE)]]
:: [s0;%- [C1 select ][*C1 ?]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 COLUMN / 2 > 1 `&`& COLUMN1 `=`= `"A`" `|`|]&]
[s0;%- [*C1        COLUMN2 `=`= Date(2006, 1, 1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN / 2 > 1 and COLUMN1 `= `'A`' or COLUMN2 
`= `'2006`-01`-01`']]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 !(COLUMN `=`= 1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where  ][*C1 not (COLUMN `= 1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 (COLUMN1 `=`= 1) `- (COLUMN2 `=`= 1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN1 `= 1 and not COLUMN2 `= 1]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 IsNull(COLUMN1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN1 is NULL]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 NotNull(COLUMN1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN1 is not NULL]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 Like(COLUMN1, Wild(`"A`*`"))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN1 like `'A%%`']]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 NotLike(COLUMN1, Wild(`"A`*`"))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN1 not like `'A%%`']]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 In(COLUMN, Select(COLUMN).From(TABLE1))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN in (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 COLUMN `=`= Select(COLUMN).From(TABLE1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN in (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 NotIn(COLUMN,]&]
[s0;%- [*C1        Select(COLUMN).From(TABLE1))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN not in (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 COLUMN !`= Select(COLUMN).From(TABLE1)][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 COLUMN not in (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 Exists(Select(COLUMN).From(TABLE1))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 exists (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(][*C1 NotExists(Select(COLUMN).From(TABLE1))][C1 )]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where ][*C1 not exists (select COLUMN from TABLE1)]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(COLUMN `=`= (][*C1 Select(COLUMN1).From(TABLE1) `|]&]
[s0;%- [*C1         Select(COLUMN2).From(TABLE2)][C1 ))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where COLUMN in (][*C1 select COLUMN1 from TABLE1]&]
[s0;%- [*C1         union (select COLUMN2 from TABLE2)][C1 )]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(COLUMN `=`= (][*C1 Select(COLUMN1).From(TABLE1) `&]&]
[s0;%- [*C1         Select(COLUMN2).From(TABLE2)][C1 ))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where COLUMN in (][*C1 select COLUMN1 from TABLE1]&]
[s0;%- [*C1         intersect (select COLUMN2 from TABLE2)][C1 )]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(COLUMN `=`= (][*C1 Select(COLUMN1).From(TABLE1) `-]&]
[s0;%- [*C1         Select(COLUMN2).From(TABLE2)))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where COLUMN in (][*C1 select COLUMN1 from TABLE1]&]
[s0;%- [*C1         minus (select COLUMN2 from TABLE2)][C1 )]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .Where(COLUMN `=`= 0)]&]
[s0;%- [*C1 .GroupBy(COLUMN)]&]
[s0;%- [*C1 .Having(COLUMN1 `=`= 0)]&]
[s0;%- [C1 .OrderBy(Descending(COLUMN))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  where COLUMN `= 0]&]
[s0;%- [*C1  group by COLUMN]&]
[s0;%- [*C1  having COLUMN1 `= 0]&]
[s0;%- [C1  order by COLUMN desc]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)][*C1 .Limit(100)]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE ][*C1 limit 100]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)][*C1 .Limit(100, 10)]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE ][*C1 limit 100, 10]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)][*C1 .Offset(20)]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE ][*C1 offset 20]]
:: [s0;%- [C1 Select(850)][*C1 .Get()]]
:: [s0;%- [C1 select 850]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)][*C1 .Hint(`"hint`")]]
:: [s0;%- [*C1 /`*`+ hint `*/][C1  select COLUMN]&]
[s0;%- [C1  from TABLE]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [*C1 .InnerJoin(TABLE1)]&]
[s0;%- [*C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [*C1  inner join TABLE1]&]
[s0;%- [*C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [*C1 .LeftJoin(TABLE1)]&]
[s0;%- [*C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [*C1  left outer join TABLE1]&]
[s0;%- [*C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [*C1 .RightJoin(TABLE1)]&]
[s0;%- [*C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [*C1  right outer join TABLE1]&]
[s0;%- [*C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
:: [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [*C1 .FullJoin(TABLE1)]&]
[s0;%- [*C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
:: [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [*C1  full outer join TABLE1]&]
[s0;%- [*C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
:: [s0;%- [*C1 Delete(TABLE)]&]
[s0;%- [*C1 .Where(COLUMN < 0)]]
:: [s0;%- [*C1 delete]&]
[s0;%- [*C1  from TABLE]&]
[s0;%- [*C1  where COLUMN < 0]]
:: [s0;%- [*C1 Insert(TABLE)]&]
[s0;%- [*C1  (COLUMN1, 12)]&]
[s0;%- [*C1  (COLUMN2, `"hello`")]&]
[s0;%- [*C1  (COLUMN, Date(2007, 1, 1))]]
:: [s0;%- [*C1 insert into TABLE(COLUMN1, COLUMN2, COLUMN)]&]
[s0;%- [*C1  values (12, `'hello`', `'2007`-01`-01`')]]
:: [s0;%- [*C1 Insert(TABLE)(COLUMN1, 12)(COLUMN2)(COLUMN)]&]
[s0;%- [*C1 .From(TABLE1)]&]
[s0;%- [*C1 .Where(COLUMN >`= 0)]]
:: [s0;%- [*C1 insert into TABLE(COLUMN1, COLUMN2, COLUMN)]&]
[s0;%- [*C1  select 12, COLUMN2, COLUMN]&]
[s0;%- [*C1  from TABLE1]&]
[s0;%- [*C1  where COLUMN >`= 0]]
:: [s0;%- [*C1 Update(TABLE)]&]
[s0;%- [*C1  (COLUMN1, 13)]&]
[s0;%- [*C1  (COLUMN2, `"world`")]&]
[s0;%- [*C1 .Where(COLUMN > Date(2007, 1, 1))]]
:: [s0;%- [*C1 update TABLE]&]
[s0;%- [*C1  set COLUMN1 `= 13, COLUMN2 `= `'world`']&]
[s0;%- [*C1  where COLUMN > `'2007`-01`-01`']]
:: [s0;%- [C1 Insert(TABLE)(COLUMN, Select(COLUMN1)]&]
[s0;%- [C1 .From(TABLE1)]&]
[s0;%- [C1 .Where(COLUMN2 `=`= 21)][*C1 .AsValue][C1 ())]]
::= [s0;%- [C1 insert into TABLE(COLUMN) values (][*C1 (select]&]
[s0;%- [*C1  COLUMN1]&]
[s0;%- [*C1  from TABLE1]&]
[s0;%- [*C1  where COLUMN2 `= 21)][C1 )]]
::^ [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(][*C1 Select(COLUMN).From(TABLE1)][C1 )]]
::= [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from (][*C1 select COLUMN from TABLE1][C1 )]]
::^ [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(Select(COLUMN).From(TABLE1)]&]
[s0;%- [C1  ][*C1 .AsTable(TABLE2)][C1 )]]
::= [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from ((select COLUMN from TABLE1) ][*C1 as TABLE2][C1 )]]
::^ [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .][*C1 LeftJoin][C1 (][*C1 Select(COLUMN).From(TABLE1)][C1 )]&]
[s0;%- [C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
::= [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE ][*C1 left outer join]&]
[s0;%- [C1  (][*C1 select COLUMN from TABLE1][C1 )]&]
[s0;%- [C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
::^ [s0;%- [C1 Select(COLUMN)]&]
[s0;%- [C1 .From(TABLE)]&]
[s0;%- [C1 .LeftJoin(Select(COLUMN).From(TABLE1)]&]
[s0;%- [C1           ][*C1 .AsTable(TABLE2)][C1 )]&]
[s0;%- [C1 .On(COLUMN.Of(TABLE) `=`= COLUMN1.Of(TABLE1))]]
::= [s0;%- [C1 select COLUMN]&]
[s0;%- [C1  from TABLE]&]
[s0;%- [C1  left outer join]&]
[s0;%- [C1  ((select COLUMN from TABLE1) ][*C1 as TABLE2][C1 )]&]
[s0;%- [C1  on TABLE.COLUMN `= TABLE1.COLUMN1]]
::^ [s0;%- [C1 Select(][*C1 TABLE(COLUMN, COLUMN1)][C1 ).From(TABLE)]]
::= [s0;%- [C1 select ][*C1 TABLE.COLUMN, TABLE.COLUMN1][C1  from TABLE]]
::^ [s0;%- [C1 Select(ID(ID, NAME, LASTNAME))]&]
[s0;%- [C1 .From(TABLE1).][*C1 LeftJoinRef][C1 (TABLE2)]&]
[s0;%- [C1 .Where(BDATE `=`= Date(2011, 12, 9))]]
::= [s0;%- [C1 select ID.ID, ID.NAME, ID.LASTNAME]&]
[s0;%- [C1  from TABLE1 ][*C1 left outer join TABLE2]&]
[s0;%- [*C1  on TABLE2.TABLE1`_ID `= TABLE1.NAME]&]
[s0;%- [C1  where BDATE `= date `'2011`-12`-09`']&]
[s0;%- [/R+75 Note: Based on .sch file REFERENCES]]
::^ [s0;%- [C1 Select(ID(ID, NAME, LASTNAME))]&]
[s0;%- [C1 .From(TABLE1).][*C1 LeftJoinRef][C1 (TABLE2)]&]
[s0;%- [C1 .][*C1 On][C1 (IsNull(BDATE))]&]
[s0;%- [C1 .Where(BDATE `=`= Date(2011, 12, 9))]]
::= [s0;%- [C1 select ID.ID, ID.NAME, ID.LASTNAME]&]
[s0;%- [C1  from TABLE1 ][*C1 left outer join TABLE2]&]
[s0;%- [*C1  on TABLE2.TABLE1`_ID `= TABLE1.NAME]&]
[s0;%- [*C1  and BDATE is NULL]&]
[s0;%- [C1  where BDATE `= date `'2011`-12`-09`']&]
[s0;%- [/R+75 Note: Based on .sch file REFERENCES]]}}&]
[s0; ]