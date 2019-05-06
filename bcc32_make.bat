@ECHO OFF

@echo コンパイル開始
@rem パスの追加ですが環境変数に既に組み込んでいる人は不要です。
set PATH=C:\borland\bcc55\bin;C:\borland\bcc55\Include;C:\borland\bcc55\lib;%PATH%

@rem SQLで必要ならコメントアウトをはずして設定する
:set __sqlinclude__=-I"C:\Program Files\MySQL\MySQL Server 5.0\Include"
:set __sqllib__=-L"C:\Program Files\MySQL\MySQL Server 5.0\Lib\Opt" libmysql.lib

@rem パケット定義
@rem 2017-06-14bRagexeRE: 20170614
@rem 2016-12-28aRagexeRE: 20161228
@rem 2015-10-29aRagexeRE: 20151029
@rem 2015-05-13aRagexe: 20150513
@rem 2014-10-22bRagexe: 20141022
@rem 2014-03-05bRagexe: 20140305
@rem 2014-01-15eRagexe: 20140115
@rem 2013-12-23cRagexe: 20131223
@rem 2013-07-31aRagexe: 20130731
@rem 2012-09-25aRagexeRE: 20120925
@rem 2012-06-18aRagexeRE: 20120618
@rem 2012-04-10aRagexeRE: 20120410
@rem 2012-04-04aRagexeRE: 20120404
@rem 2012-03-28aRagexeRE: 20120328
@rem 2012-03-07aRagexeRE: 20120307
@rem 2012-02-22aRagexeRE: 20120222
@rem 2012-02-01aRagexeRE: 20120201
@rem 2011-11-02aRagexeRE: 20111102
@rem 2011-10-25aRagexeRE: 20111025
@rem 2011-09-28aRagexeRE: 20110928
@rem 2011-07-19aRagexeRE: 20110719
@rem 2011-03-09aRagexeRE: 20110309
@rem 2011-01-11aRagexeRE: 20110111
@rem 2010-10-20aRagexeRE: 20101020
@rem 2010-08-03aRagexeRE: 20100803
@rem 2010-07-28aRagexeRE: 20100728
@rem 2010-07-21aRagexeRE: 20100721
@rem 2010-06-29aRagexeRE: 20100629
@rem 2010-06-15aRagexeRE: 20100615
@rem 2010-04-14aRagexeRE: 20100414
@rem 2010-02-23aRagexeRE: 20100223
@rem 2009-12-08aRagexeRE: 20091208
@rem 2009-11-18cRagexeRE: 20091118
@rem 2009-11-04aRagexeRE: 20091104
@rem 2009-07-15aRagexeRE: 20090715
@rem 2009-06-17aRagexeRE: 20090617
@rem 2009-06-03aRagexeRE: 20090603
@rem 2008-11-26cSakexe or 2008-11-26aRagexeRE: 20081126
@rem 2008-11-13aSakexe: 20081113
@rem 2008-08-20aSakexe: 20080820
@rem 2008-05-28aSakexe or 2008-08-27aRagexeRE: 20080827
@rem 2008-01-02aSakexe: 20080102
@rem 2007-11-28aSakexe: 20071128
@rem 2007-11-06aSakexe: 20071106
@rem 2007-09-04aSakexe: 20070904
@rem 2007-07-11aSakexe: 20070711
@rem 2007-05-21aSakexe: 20070521
@rem 2007-02-12aSakexe: 20070212
@rem 2006-10-23aSakexe: 20061023
set __PACKETDEF__=-DPACKETVER=20151029 -DNEW_006b

@rem コンパイルオプション
@rem SQL⇔TEXTの切り替え、SQL版にする場合は以下のコンパイルオプションをコメントアウトしてください
set __base__=-DTXT_ONLY

@rem txt モードでジャーナルを使うならコメントアウトをはずす
:set __base__=-DTXT_ONLY -DTXT_JOURNAL

@rem データ保存方法が SQL の時、txt-converter が不要ならコメントアウトをはずす
:set __TXTCONVERTER__=SKIP

@rem zlib.dllをコンパイルする(通常はコメントアウト)
:set __ZLIB__=-DLOCALZLIB

@rem Login_ID2で、IPを見るようにします(通常はコメントアウト)
@rem Passwordの代わりにIPを見て接続します、最新の日蔵が使えるようになりますが
@rem ケーブルTV等グローバルIPが外部に出ないプロバイダからは接続不可になります
:set __SKIP__=-DCMP_AUTHFIFO_IP -DCMP_AUTHFIFO_LOGIN2

@rem httpd を完全に無効にする場合コメントアウトをはずす
set __NO_HTTPD__=-DNO_HTTPD

@rem httpd で外部 CGI を使う場合はコメントアウトする
set __NO_HTTPD_CGI__=-DNO_HTTPD_CGI

@rem csvdb のスクリプトからの利用を無効にする場合コメントアウトをはずす
:set __NO_CSVDB_SCRIPT__=-DNO_CSVDB_SCRIPT

@rem R化前のシステムを使う場合はコメントアウトをはずす
:set __PRE_RENEWAL__=-DPRE_RENEWAL

@rem MBでごにょごにょ (通常はコメントアウト)
:set __EXCLASS__=-DCLASS_MB

@rem 動的にMOBのsc_dataを確保したい人はコメントアウトをはずす
set __DYNAMIC_STATUS_CHANGE__=-DDYNAMIC_SC_DATA

@rem キャラの削除にメールアドレスを使う場合はコメントアウトをはずす
:set __AC_MAIL__=-DAC_MAIL

@rem キャラの削除に誕生日を使う場合はコメントアウトをはずす
:set __AC_BIRTHDATE__=-DAC_BIRTHDATE

@rem ステータス異常データの保存を無効にする場合コメントアウトをはずす
:set __NO_SCDATA_SAVING__=-DNO_SCDATA_SAVING

@rem タイマーをキャッシュするならコメントアウトをはずす
:set __TIMER_CACHE__=-DTIMER_CACHE=256

@rem CPU最適化スイッチ 以下の例を参考にCPU名を記入してください。
set _model_=Pentium4

@rem 8000サンプル 統計の結果をコンパイルに反映させます
if "%_model_%"=="Athlon" set __cpu__=-6 -O2
if "%_model_%"=="Athlon_XP" set __cpu__=-5
if "%_model_%"=="Athlon_MP" set __cpu__=-5
if "%_model_%"=="Duron" set __cpu__=-5
if "%_model_%"=="Sempron" set __cpu__=-5
if "%_model_%"=="586" set __cpu__=-4 -VI
if "%_model_%"=="686" set __cpu__=-4 -VI
if "%_model_%"=="Pentium2" set __cpu__=-4
if "%_model_%"=="Pentium3" set __cpu__=-5
if "%_model_%"=="Pentium4" set __cpu__=-5
if "%_model_%"=="P2_Celeron" set __cpu__=-4
if "%_model_%"=="P3_Celeron" set __cpu__=-5
if "%_model_%"=="P4_Celeron" set __cpu__=-5 -Ov
if "%_model_%"=="P3_Xeon" set __cpu__=-6
if "%_model_%"=="P4_Xeon" set __cpu__=-6 -O2 -f
if "%_model_%"=="CeleronD" set __cpu__=-5
if "%_model_%"=="MobileP2" set __cpu__=-4 -O2 -Ov
if "%_model_%"=="MobileP3" set __cpu__=-5 -O2
if "%_model_%"=="MobileP4" set __cpu__=-5 -Oc -Ov
if "%_model_%"=="PentiumM" set __cpu__=-5 -O1
if "%_model_%"=="Crusoe" set __cpu__=-4 -Oc
if "%_model_%"=="Opteron" set __cpu__=-5 -O2 -Oi -f -tWM
if "%_model_%"=="Athlon_64" set __cpu__=-6 -Oi -tWM
if "%_model_%"=="Athlon_64x2" set __cpu__=-6 -Ov -Oi -f -ff -tWM
if "%_model_%"=="Turion64" set __cpu__=-4 -Oc -Ov -Oi
if "%_model_%"=="Itanium64" set __cpu__=-4 -Oc -Ov -Oi
if "%_model_%"=="Prescott" set __cpu__=-5 -Oc -Ov -tWM
if "%_model_%"=="Prescott2" set __cpu__=-5 -Oc -Ov -Oi -f -ff -tWM
if "%_model_%"=="Smithfield" set __cpu__=-6 -Oc -Ov -Oi -tWM
if "%_model_%"=="Prestonia" set __cpu__=-6 -Oc -Ov -Oi -f -ff -tWM
if "%_model_%"=="Manchester" set __cpu__=-6 -Oi -f -ff -tWM
if "%_model_%"=="Pentium4X" set __cpu__=-5 -Oc -Ov -Oi -f -ff -tWM
if "%_model_%"=="Athlon_X" set __cpu__=-5 -Oc -Ov -Oi -f -ff -tWM
if "%_model_%"=="Pentium4C" set __cpu__=-5 -Ov -Oi
if "%_model_%"=="AMD32" set __cpu__=-5 -Oc -Ov -f -ff
if "%_model_%"=="AMD64" set __cpu__=-6 -Oc -Ov -f -ff -tWM
if "%_model_%"=="DCORE" set __cpu__=-6 -a16 -C -d -f -ff -Hc -i133 -Jgd -k- -Oc -Oxt -Ve -VF -xf -xp

set __define__=%__cpu__% %__PACKETDEF__% -DFD_SETSIZE=4096 -D_WIN32 -DWINDOWS %__base__% %__NO_HTTPD__% %__NO_HTTPD_CGI__% %__NO_CSVDB_SCRIPT__% %__ZLIB__% %__SKIP__% %__PRE_RENEWAL__% %__EXCLASS__% %__DYNAMIC_STATUS_CHANGE__% %__AC_MAIL__% %__AC_BIRTHDATE__% %__NO_SCDATA_SAVING__% %__TIMER_CACHE__%
set __include__=-I../common/ -I../common/lua/ -I../common/zlib/ %__sqlinclude__%

if "%__ZLIB__%"=="" goto NOZLIB
set __common__=..\common\zlib\*.c
:NOZLIB
set __common__=..\common\*.c %__common__%
set __lualib__=-L..\common\lua lualib.lib

if "%__base__%"=="" (set __dbmode__=sql) else (set __dbmode__=txt)


@echo ■コンパイルオプション表示■
@echo ◆───────────────────────────────◆
@echo [%__define__%]
@echo ◆───────────────────────────────◆

@rem Warning が900個弱出てきて何がなんだか分からないので、全部抑制。
@rem 修正する気力起きないので他力本願モードっぽいです。
@rem     W8004 : **** に代入した値は使われていない
@rem     W8008 : 条件が常に真
@rem     W8012 : 符号付き値と符号なし値の比較
@rem     W8057 : パラメータ **** は一度も使用されない
@rem     W8060 : おそらく不正な代入
@rem     W8066 : 実行されないコード
@rem 取敢えずコンパイル出来なくなる深刻なものとエラーのみの表示

set __warning__=-w-8004 -w-8008 -w-8012 -w-8057 -w-8060 -w-8066

@echo luaコンパイル
cd src\common\lua
bcc32 -j255 -c *.c
tlib lualib.lib /a *.obj

@echo ログインサーバーコンパイル
cd ..\..\login
bcc32 -j255 -M -e..\..\login-server.exe %__warning__% %__define__% %__include__% *.c .\%__dbmode__%\*.c %__common__% %__sqllib__% %__lualib__%

@echo キャラクターサーバーコンパイル
cd ..\char
bcc32 -j255 -M -e..\..\char-server.exe %__warning__% %__define__% %__include__% *.c .\%__dbmode__%\*.c %__common__% %__sqllib__% %__lualib__%

@echo マップサーバーコンパイル
cd ..\map
bcc32 -j255 -M -e..\..\map-server.exe %__warning__% %__define__% %__include__% *.c .\%__dbmode__%\*.c %__common__% %__sqllib__% %__lualib__%

@rem 必要なら txt-converter をコンパイル
if NOT "%__base__%"=="" goto NOCONVERTER1
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER1
@echo コンバーターコンパイル
cd ..\converter
bcc32 -j255 -M -e..\..\txt-converter.exe %__warning__% %__define__% %__include__% *.c %__common__% %__sqllib__%
:NOCONVERTER1

cd ..\..\
@echo オブジェクトファイル等のクリーンアップ
del src\common\lua\*.obj > NUL
del src\common\lua\*.lib > NUL
del src\char\*.obj > NUL
del src\login\*.obj > NUL
del src\map\*.obj > NUL
if NOT "%__base__%"=="" goto NOCONVERTER2
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER2
del src\converter\*.obj > NUL
:NOCONVERTER2

pause
