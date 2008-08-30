@echo off
rem VC++ でのビルド用バッチファイル

rem 対応するコンパイラのバージョン
rem  - Visual C++ 6.0
rem  - Visual C++ .NET (Visual C++ .NET 2002)
rem  - Visual C++ .NET 2003
rem  - Visual C++ Toolkit 2003
rem  - Visual C++ 2005 (Express Edition 含む)

rem ----------------------------------------------------------------
rem 共通設定
echo vc_make.bat - Auriga makefile for Visual C++
set __VCVER__=7

rem ----------------------------------------------------------------
rem パケット定義
rem 2008-01-02aSakexe: 14
rem 2007-11-28aSakexe: 13
rem 2007-11-06aSakexe: 12
rem 2007-09-04aSakexe: 11
rem 2007-07-11aSakexe: 10
rem 2007-05-21aSakexe:  9
rem 2007-02-12aSakexe:  8
set __PACKETDEF__=/D "PACKETVER=14" /D "NEW_006b"

rem ----------------------------------------------------------------
rem コンパイラごとの設定（自分の環境にあうもののコメントアウトをはずす）

rem ---- VC++ Toolkit 2003 の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files\Microsoft Visual C++ Toolkit 2003\bin;C:\Program Files\Microsoft Platform SDK\Bin;C:\Program Files\Microsoft Platform SDK\Bin\winnt;C:\Program Files\Microsoft Platform SDK\Bin\Win64;%PATH%
rem set INCLUDE=C:\Program Files\Microsoft Visual C++ Toolkit 2003\include;C:\Program Files\Microsoft Platform SDK\include;%INCLUDE%
rem set LIB=C:\Program Files\Microsoft Visual C++ Toolkit 2003\lib;C:\Program Files\Microsoft Platform SDK\Lib;%LIB%
rem ---- VC++ Toolkit 2003 の設定ここまで

rem ---- VC++ 2005 Express Edition の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files\Microsoft Visual Studio 8\VC\bin;C:\Program Files\Microsoft Visual Studio 8\Common7\IDE;C:\Program Files\Microsoft Platform SDK\Bin;C:\Program Files\Microsoft Platform SDK\Bin\winnt;C:\Program Files\Microsoft Platform SDK\Bin\Win64;%PATH%
rem set INCLUDE=C:\Program Files\Microsoft Visual Studio 8\VC\include;C:\Program Files\Microsoft Platform SDK\include;%INCLUDE%
rem set LIB=C:\Program Files\Microsoft Visual Studio 8\VC\lib;C:\Program Files\Microsoft Platform SDK\Lib;%LIB%
rem set __VCVER__=8
rem ---- VC++ 2005 Express Edition の設定ここまで

rem ---- VC++ 2005 (Express以外) の設定 / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio 8\VC\bin\VCVARS32.BAT"
rem set __VCVER__=8
rem ---- VC++ 2005 (Express以外) の設定ここまで

rem ---- VC++ .NET 2003 の設定 / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio .NET 2003\Vc7\bin\vcvars32.bat"
rem ---- VC++ .NET 2003 の設定ここまで

rem ---- VC++ .NET (2002) / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio .NET\Vc7\bin\vcvars32.bat"
rem ---- VC++ .NET (2002) の設定 ここまで

rem ---- VC++ 6.0 / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio\VC98\Bin\vcvars32.bat"
rem set __VCVER__=6
rem ---- VC++ 6.0 の設定ここまで

rem ----------------------------------------------------------------
rem SQL の設定 / 必要ならコメントアウトをはずす
rem set INCLUDE=C:\Program Files\MySQL\MySQL Server 5.0\Include;%INCLUDE%
rem set LIB=C:\Program Files\MySQL\MySQL Server 5.0\Lib\Opt;%LIB%

rem ----------------------------------------------------------------
rem VC8 で指定できないオプションの回避処理
if "%__VCVER__%"=="8" goto SKIPVC8
set __OPT_OP__=/Op
:SKIPVC8

rem ----------------------------------------------------------------
rem VC6 で指定できないオプションの回避処理
if "%__VCVER__%"=="6" goto SKIPVC6
set __FIXOPT2__=/MAP /nologo
:SKIPVC6

rem ----------------------------------------------------------------
rem ビルドオプションの選択

rem データ保存方法の選択 ： SQL にするならコメントアウトする
set __TXT_MODE__=/D "TXT_ONLY"

rem データ保存方法が TXT の時、ジャーナルを使うならコメントアウトをはずす
rem set __TXT_MODE__=/D "TXT_ONLY" /D "TXT_JOURNAL"

rem データ保存方法が SQL の時、txt-converter が不要ならコメントアウトをはずす
rem set __TXTCONVERTER__=SKIP

rem zlib.dllをコンパイルするならコメントアウトをはずす
rem set __ZLIB__=/D "LOCALZLIB"

rem login_id2 や IP で AUTHFIFO を比較する場合はコメントアウトをはずす
rem set __CMP_AFL2__=/D "CMP_AUTHFIFO_LOGIN2"
rem set __CMP_AFIP__=/D "CMP_AUTHFIFO_IP"

rem httpd を完全に無効にする場合コメントアウトをはずす
rem set __NO_HTTPD__=/D "NO_HTTPD"

rem httpd で外部 CGI を使う場合はコメントアウトする
set __NO_HTTPD_CGI__=/D "NO_HTTPD_CGI"

rem csvdb のスクリプトからの利用を無効にする場合コメントアウトをはずす
rem set __NO_CSVDB_SCRIPT__=/D "NO_CSVDB_SCRIPT"

rem DK DC を使う場合はコメントアウトをはずす
rem set __EXCLASS__=/D "CLASS_DKDC"

rem 動的にMOBの sc_data を確保する場合はコメントアウトをはずす
rem set __DYNAMIC_STATUS_CHANGE__=/D "DYNAMIC_SC_DATA"

rem キャラの削除にメールアドレスを使う場合はコメントアウトをはずす
rem set __AC_MAIL__=/D "AC_MAIL"

rem ステータス異常データの保存を無効にする場合はコメントアウトをはずす
rem set __NO_SCDATA_SAVING__=/D "NO_SCDATA_SAVING"

rem ---------------------------
rem コンパイルオプション設定

@rem CPU最適化スイッチ(By Nameless)
@rem 以下の例を参考にスイッチ名を記入してください。
set _model_=x32

@rem 最適化なし
if "%_model_%"=="NOOPTIMIZE" set __cpu__=/c /W3 /Od /Zi

@rem CPUアーキテクチャ32BitCPU/64BitCPU
if "%_model_%"=="x32" set __cpu__=/c /W3 /O2 %__OPT_OP__% /GA /TC /Zi
if "%_model_%"=="x64" set __cpu__=/c /arch:SSE2 /W3 /O2 %__OPT_OP__% /GA /TC /Zi

@rem メモリー1024以上搭載の32bitCPU/64bitCPU
if "%_model_%"=="HiMemL" set __cpu__=/c /bigobj /W3 /O2 %__OPT_OP__% /GA /TC /Zi
if "%_model_%"=="HiMemH" set __cpu__=/c /bigobj /arch:SSE2 /W3 /O2 %__OPT_OP__% /GA /TC /Zi

@rem スタック制御をコンパイラで行う場合
if "%_model_%"=="Stac32" set __cpu__=/c /F4096 /W3 /O2 %__OPT_OP__% /GA /TC /Zi
if "%_model_%"=="Stac64" set __cpu__=/c /F4096 /arch:SSE2 /W3 /O2 %__OPT_OP__% /GA /TC /Zi
@rem AMD系64bitCPU用
if "%_model_%"=="A64x2" set __cpu__=/c /favor:blend /W3 /O2 %__OPT_OP__% /GA /TC /Zi
if "%_model_%"=="A64x1" set __cpu__=/c /favor:AMD64 /W3 /O2 %__OPT_OP__% /GA /TC /Zi

@rem Intel系64bitCPU用
if "%_model_%"=="EM64T" set __cpu__=/c /favor:EM64T /W3 /O2 %__OPT_OP__% /GA /TC /Zi


@rem 以下実験段階(人柱求む by Nameless)
@rem 暴走風味…32BitCPU最高速モード
if "%_model_%"=="mode01" set __cpu__=/c /fp:fast /F4096 /bigobj /W3 /Ox /GA /TC /Zi
@rem 暴走風味…64BitCPU最高速モード
if "%_model_%"=="mode02" set __cpu__=/c /arch:SSE2 /fp:fast /F4096 /bigobj /W3 /Ox /Gr /GA /TC /Zi
@rem 暴走風味…AMD 64x2 & FX系最適化・最高速
if "%_model_%"=="mode03" set __cpu__=/c /arch:SSE2 /fp:fast /F4096 /bigobj /favor:AMD64 /W3 /Ox /Gr /GA /TC /Zi
if "%_model_%"=="mode04" set __cpu__=/c /arch:SSE2 /fp:fast /F4096 /bigobj /favor:blend /W3 /Ox /Gr /GA /TC /Zi
@rem 暴走風味…Intel 64bitCPU用最適化・最高速
if "%_model_%"=="mode05" set __cpu__=/c /arch:SSE2 /fp:fast /F4096 /bigobj /favor:EM64T /W3 /Ox /Gr /GA /TC /Zi
@rem 以下リザーブ
if "%_model_%"=="mode06" set __cpu__=/c /W3 /Ox /Gr /GA /TC /Zi
if "%_model_%"=="mode07" set __cpu__=/c /W3 /Ox /Gr /GA /TC /Zi
if "%_model_%"=="mode08" set __cpu__=/c /W3 /Ox /Gr /GA /TC /Zi
if "%_model_%"=="mode09" set __cpu__=/c /W3 /Ox /Gr /GA /TC /Zi



rem ----------------------------------------------------------------
rem 最終的なビルドオプションを生成
if "%__ZLIB__%"=="" goto NOZLIB1
set __LINKZLIB__=../common/zlib/*.obj
:NOZLIB1

set __opt1__=/I "../common/zlib/" /I "../common/" /D "FD_SETSIZE=4096" /D "NDEBUG" /D "_CONSOLE" /D "WIN32" /D "_WIN32" /D "_WIN32_WINDOWS" /D "_CRT_SECURE_NO_DEPRECATE" %__PACKETDEF__% %__TXT_MODE__% %__ZLIB__% %__CMP_AFL2__% %__CMP_AFIP__% %__NO_HTTPD__% %__NO_HTTPD_CGI__% %__NO_CSVDB_SCRIPT__% %__EXCLASS__% %__DYNAMIC_STATUS_CHANGE__% %__AC_MAIL__% %__NO_SCDATA_SAVING__% %__DEBUG_VARS__%
set __opt2__=/DEBUG %__FIXOPT2__% user32.lib %__LINKZLIB__% ../common/*.obj *.obj

rem ----------------------------------------------------------------
rem 警告の抑制
rem   C4819 : 表示できない文字を含んでいます
set __warning__=/wd4819

rem ----------------------------------------------------------------
rem ビルド作業本体

rem 共通コンポーネントのコンパイル
cd src\common\zlib
if "%__ZLIB__%"=="" goto NOZLIB2
cl %__warning__% %__cpu__% %__opt1__% *.c
:NOZLIB2
cd ..\
cl %__warning__% %__cpu__% %__opt1__% *.c 

rem サーバー本体のビルド
cd ..\login
cl %__warning__% %__cpu__% %__opt1__% *.c 
link %__opt2__% /out:"../../login-server.exe"
cd ..\char
cl %__warning__% %__cpu__% %__opt1__% *.c 
link %__opt2__% /out:"../../char-server.exe"
cd ..\map
cl %__warning__% %__cpu__% %__opt1__% *.c 
link %__opt2__% /out:"../../map-server.exe"

rem 必要なら txt-converter をビルド
if NOT "%__TXT_MODE__%"=="" goto NOCONVERTER1
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER1
cd ..\converter
cl %__warning__% %__cpu__% %__opt1__% *.c 
link %__opt2__% /out:"../../txt-converter.exe"
:NOCONVERTER1

cd ..\..\

rem 不必要なファイルを削除
if "%__ZLIB__%"=="" goto NOZLIB3
del src\common\zlib\*.obj
:NOZLIB3
del src\common\*.obj
del src\char\*.obj
del src\login\*.obj
del src\map\*.obj
if NOT "%__TXT_MODE__%"=="" goto NOCONVERTER2
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER2
del src\converter\*.obj
:NOCONVERTER2

rem 結果確認用の一時停止
pause
