@ECHO OFF
@echo 古いオブジェクトファイル等のクリーンアップ

del src\char\*.obj > NUL
del src\char\char.exe > NUL
del src\login\*.obj > NUL
del src\login\login.exe > NUL
del src\map\*.obj > NUL
del src\map\map.exe > NUL
del login-server.exe > NUL
del char-server.exe > NUL
del map-server.exe > NUL
del char-converter.exe > NUL
del login-converter.exe > NUL
del src\converter\*.obj > NUL
del src\converter\*.exe > NUL

@echo コンパイル開始
@rem パスの追加ですが環境変数に既に組み込んでいる人は不要です。
set path=%path%;C:\borland\bcc55\bin;C:\borland\bcc55\Include;C:\borland\bcc55\lib

set __common__=..\common\core.c ..\common\db.c ..\common\grfio.c ..\common\lock.c ..\common\malloc.c ..\common\nullpo.c ..\common\socket.c ..\common\timer.c ..\common\httpd.c ..\common\graph.c ..\common\md5calc.c ..\common\utils.c

@rem コンパイルオプション
@rem SQL⇔TEXTの切り替え、SQL版にする場合は以下のコンパイルオプションをコメントアウトしてください
:set __base__=-DTXT_ONLY

@rem Zlib.dllをコンパイルする(通常はコメントアウト)
:set __ZLIB__=-DLOCALZLIB

@rem Login_ID2で、IPを見るようにします(通常はコメントアウト)
@rem Passwordの代わりにIPを見て接続します、最新の日蔵が使えるようになりますが
@rem ケーブルTV等グローバルIPが外部に出ないプロバイダからは接続不可になります
:set __SKIP__=-DCMP_AUTHFIFO_IP -DCMP_AUTHFIFO_LOGIN2

@rem httpd を完全に無効にする場合コメントアウトをはずす(通常はコメントアウト)
:set __NO_HTTPD__=-DNO_HTTPD

@rem DKDCでごにょごにょ (通常はコメントアウト)
:set __EXCLASS__=-DCLASS_DKDC

@rem 動的にMOBのsc_dataを確保したい人はコメントアウトをはずす
:set __DYNAMIC_STATUS_CHANGE__=-DDYNAMIC_SC_DATA

@rem account regist MailAddress
:set __AC_MAIL__=-DAC_MAIL

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

set __define__=%__cpu__% -DPACKETVER=7 -DNEW_006b -DFD_SETSIZE=4096 %__base__% %__NO_HTTPD__% %__ZLIB__% %__SKIP__% %__EXCLASS__% %__DYNAMIC_STATUS_CHANGE__% %__AC_MAIL__%
set __include__=-I../common/

@echo ■コンパイルオプション表示■
@echo ◆───────────────────────────────◆
@echo [%__define__%]
@echo ◆───────────────────────────────◆

@rem Warning が900個弱出てきて何がなんだか分からないので、全部抑制。
@rem 修正する気力起きないので他力本願モードっぽいです。
@rem     W7035 : 符号付き値と符号なし値の比較
@rem     W8004 : **** に代入した値は使われていない
@rem     W8012 : 符号付き値と符号なし値の比較
@rem     W8017 : マクロ '****' の重複定義
@rem     W8057 : パラメータ **** は一度も使用されない
@rem     W8060 : おそらく不正な代入
@rem     W8064 : プロトタイプ宣言のない関数
@rem     W8065 : プロトタイプ宣言のない関数
@rem     W8066 : 実行されないコード
@rem     W8070 : 関数は値を返すべき
@rem     W8075 : 問題のあるポインタの変換
@rem 取敢えずコンパイル出来なくなる深刻なものとエラーのみの表示

set __warning__=-w-7035 -w-8004 -w-8012 -w-8017 -w-8057 -w-8060 -w-8064 -w-8065 -w-8066 -w-8070 -w-8075

@echo ログインサーバーコンパイル
cd src\login
bcc32 -j255 %__warning__% %__define__% %__include__% login.c libmysql.lib %__common__%
copy login.exe ..\..\login-server.exe > NUL

@echo キャラクターサーバーコンパイル
cd ..\char
bcc32 -j255 %__warning__% %__define__% %__include__% char.c libmysql.lib int_pet.c int_guild.c int_party.c int_storage.c inter.c %__common__%
copy char.exe ..\..\char-server.exe > NUL

@echo コンバーターコンパイル
cd ..\converter
bcc32 -j255 %__warning__% %__define__% %__include__% char-converter.c libmysql.lib converter.c login-converter.c inter-converter.c %__common__%
copy converter.exe ..\..\converter.exe > NUL

cd ..\..\
@echo オブジェクトファイル等のクリーンアップ
del src\char\*.obj > NUL
del src\char\char.exe > NUL
del src\login\*.obj > NUL
del src\login\login.exe > NUL
del src\map\*.obj > NUL
del src\map\map.exe > NUL
pause

