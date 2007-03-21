@ECHO OFF

@echo コンパイル開始
@rem パスの追加ですが環境変数に既に組み込んでいる人は不要です。
set PATH=C:\borland\bcc55\bin;C:\borland\bcc55\Include;C:\borland\bcc55\lib;%PATH%

@rem SQLで必要ならコメントアウトをはずして設定する
:set __sqlinclude__=-I"C:\Program Files\MySQL\MySQL Server 5.0\Include"
:set __sqllib__=-L"C:\Program Files\MySQL\MySQL Server 5.0\Lib\Opt" libmysql.lib

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

@rem httpd を完全に無効にする場合コメントアウトをはずす(通常はコメントアウト)
:set __NO_HTTPD__=-DNO_HTTPD

@rem httpd で外部 CGI を使う場合はコメントアウトする
set __NO_HTTPD_CGI__=-DNO_HTTPD_CGI

@rem csvdb のスクリプトからの利用を無効にする場合コメントアウトをはずす
:set __NO_CSVDB_SCRIPT__=-DNO_CSVDB_SCRIPT

@rem DKDCでごにょごにょ (通常はコメントアウト)
:set __EXCLASS__=-DCLASS_DKDC

@rem 動的にMOBのsc_dataを確保したい人はコメントアウトをはずす
:set __DYNAMIC_STATUS_CHANGE__=-DDYNAMIC_SC_DATA

@rem キャラの削除にメールアドレスを使う場合はコメントアウトをはずす
:set __AC_MAIL__=-DAC_MAIL

@rem ステータス異常データの保存を無効にする場合コメントアウトをはずす
:set __NO_SCDATA_SAVING__=-DNO_SCDATA_SAVING

@rem スクリプトで使用された変数の一覧を出力する
:set __DEBUG_VARS__=-DDEBUG_VARS

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

set __define__=%__cpu__% -DPACKETVER=8 -DNEW_006b -DFD_SETSIZE=4096 %__base__% %__NO_HTTPD__% %__NO_HTTPD_CGI__% %__NO_CSVDB_SCRIPT__% %__ZLIB__% %__SKIP__% %__EXCLASS__% %__DYNAMIC_STATUS_CHANGE__% %__AC_MAIL__% %__NO_SCDATA_SAVING__% %__DEBUG_VARS__%
set __include__=-I../common/ -I../common/zlib/ %__sqlinclude__%

if "%__ZLIB__%"=="" goto NOZLIB
set __common__=..\common\zlib\*.c
:NOZLIB
set __common__=..\common\*.c %__common__%


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

@echo ログインサーバーコンパイル
cd src\login
bcc32 -j255 -M -e..\..\login-server.exe %__warning__% %__define__% %__include__% *.c %__common__% %__sqllib__%

@echo キャラクターサーバーコンパイル
cd ..\char
bcc32 -j255 -M -e..\..\char-server.exe %__warning__% %__define__% %__include__% *.c %__common__% %__sqllib__%

@echo マップサーバーコンパイル
cd ..\map
bcc32 -j255 -M -e..\..\map-server.exe %__warning__% %__define__% %__include__% *.c %__common__% %__sqllib__%

@rem 必要なら txt-converter をコンパイル
if NOT "%__base__%"=="" goto NOCONVERTER1
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER1
@echo コンバーターコンパイル
cd ..\converter
bcc32 -j255 -M -e..\..\txt-converter.exe %__warning__% %__define__% %__include__% *.c %__common__% %__sqllib__%
:NOCONVERTER1

cd ..\..\
@echo オブジェクトファイル等のクリーンアップ
del src\char\*.obj > NUL
del src\login\*.obj > NUL
del src\map\*.obj > NUL
if NOT "%__base__%"=="" goto NOCONVERTER2
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER2
del src\converter\*.obj > NUL
:NOCONVERTER2

pause
