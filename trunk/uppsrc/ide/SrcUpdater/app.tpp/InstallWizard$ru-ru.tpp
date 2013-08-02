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
[{_}%RU-RU 
[s2; Мастер первоначальной настройки 
(описание)&]
[s0; [@6 (только для POSIX`-систем)]&]
[s0; &]
[s0; В момент первого запуска TheIDE, появляется 
диалог в стиле `"Мастера`" (wizard), цель 
которого помочь пользователю настроить 
все необходимое для правильной работы 
TheIDE. Этот диалог может, так же, быть 
вызван позже запуском TheIDE с параметром 
[/ `-install] или из меню [/ Setup (Настройка)]. 
Более детальное и иллюстрированное 
описание вы можете посмотреть в [^topic`:`/`/ide`/SrcUpdater`/app`/LinuxInstallGuide`$ru`-ru^ п
ошаговом описании Мастера].&]
[s0; &]
[s0; Мастер позволяет пользователю выбрать, 
как должен обслуживаться и обновляться 
исходный код, на настоящий момент 
доступно четыре метода:&]
[s0;i150;O0; Локальная копия исходников, 
расположенная в /usr/share/upp (или что`-нибудь 
подобное). Предполагается, что в этом 
случае она обслуживаются и обновляются 
программами управления пакетами.&]
[s0;i150;O0; Сборки только`-для`-чтения в /usr/share/upp. 
Здесь файлы тоже должны обновляться 
менеджером пакетов. В этом случае 
предполагается, так же, что пользователю 
никогда не понадобиться изменять 
исходники U`+`+.&]
[s0;i150;O0; Сборки, на основе SVN. Этот метод 
предусматривает проверку исходников 
U`+`+ в SVN`-репозитории и настройку сборок 
на их основе&]
[s0;i150;O0; Без репозиториев. Этот вариант 
для пользователей, которые предпочитают 
управлять исходниками самостоятельно.&]
[s0; &]
[s0; Если пользователь выбрал сборки, 
основанные на SVN, Мастер запрашивает 
у него дополнительные параметры для 
настройки сервера SVN, это может быть 
либо зеркало по умолчанию на code.google.com, 
либо выборочная настройка. Выборочная 
настройка позволяет указать адрес 
репозитория, пользователя и пароль. 
Кроме того, пользователь может выбрать 
один из трех режимов синхронизации:&]
[s0;i150;O0; Всегда получать самые новые 
доступные исходники.&]
[s0;i150;O0; Синхронизировать исходный код 
с версией TheIDE (полезно, когда, например, 
TheIDE обновлен менеджером пакетов до 
стабильной версии).&]
[s0;i150;O0; Обновление вручную.&]
[s0; &]
[s0; В заключительная части параметров 
настройки предлагается указать сборки, 
которые должны быть созданы. Параметры 
полность редактируемы. Чтобы упростить 
работу по вводу, могут быть заданы 
значения для подстановки `$(SRC) и `$(OUT), 
которые можно будет использовать 
в параметрах.&]
[s0; &]
[s0; Процесс разрабатывался для достижения 
двух основных целей:&]
[s0;i150;O0; Быть как можно более простым 
и дружественным пользователю даже 
для новичков.&]
[s0;i150;O0; Быть достаточно гибким, чтобы 
не создавать никаких ограничений 
опытным пользователям.&]
[s0; Автор использовал все свое воображение 
и зравый смысл для достижения этих 
целей. Новичек может просто нажать 
[/ Finish (Закончить)] и сразу начать изчать 
TheIDE. С другой стороны, диалог должен 
быть достаточно гибок, чтобы служить 
не только для управления исходниками 
U`+`+, но и любым другим проектом, не 
зависимо от того, основан он на U`+`+ 
или нет.&]
[s0; &]
[s0; Чтобы применить и схранить все изменения, 
в любой момент щелкните по кнопке 
[/ Finish (Завешить)] (для всех пропущенных 
шагов будут сохранены значения по 
умолчанию). Кнопка [/ Cancel (Отменить)] 
используется, чтобы немедленно покинуть 
Мастер без сохранения изменений.&]
[s0; &]
[s2; [+150 Дополнительные замечания:]&]
[s0;i150;O0; Допускается многократный запуск 
Мастера.&]
[s0;i150;O0; Только самые последние настройки 
используются для автоматических 
обновлений.&]
[s0;i150;O0; Если уже имеются какие`-либо 
сборки, они не будут удалены, сборки 
с совпадающими именами будут перезаписаны.&]
[s0;i150;O0; Результаты установки могут быть 
отменены использованием [/^topic`:`/`/ide`/SrcUpdater`/app`/Uninstall`$ru`-ru^ о
пции командной строки `-uninstall].&]
[s0;%% ]