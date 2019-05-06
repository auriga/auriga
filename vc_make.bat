@echo off
rem VC++ でのビルド用バッチファイル

rem 対応するコンパイラのバージョン
rem  - Visual C++ 6.0
rem  - Visual C++ .NET (Visual C++ .NET 2002)
rem  - Visual C++ .NET 2003
rem  - Visual C++ Toolkit 2003
rem  - Visual C++ 2005 (Express Edition 含む)
rem  - Visual C++ 2008 Express Edition
rem  - Visual C++ 2008 64bitコンパイル
rem  - Visual C++ 2010 Express Edition

rem ----------------------------------------------------------------
rem 共通設定
echo vc_make.bat - Auriga makefile for Visual C++
set __VCVER__=7
set __BITTYPE__=x32

rem ----------------------------------------------------------------
rem パケット定義
rem 2017-06-14bRagexeRE: 20170614
rem 2016-12-28aRagexeRE: 20161228
rem 2015-10-29aRagexeRE: 20151029
rem 2015-05-13aRagexe: 20150513
rem 2014-10-22bRagexe: 20141022
rem 2014-03-05bRagexe: 20140305
rem 2014-01-15eRagexe: 20140115
rem 2013-12-23cRagexe: 20131223
rem 2013-07-31aRagexe: 20130731
rem 2012-09-25aRagexeRE: 20120925
rem 2012-06-18aRagexeRE: 20120618
rem 2012-04-10aRagexeRE: 20120410
rem 2012-04-04aRagexeRE: 20120404
rem 2012-03-28aRagexeRE: 20120328
rem 2012-03-07aRagexeRE: 20120307
rem 2012-02-22aRagexeRE: 20120222
rem 2012-02-01aRagexeRE: 20120201
rem 2011-11-02aRagexeRE: 20111102
rem 2011-10-25aRagexeRE: 20111025
rem 2011-09-28aRagexeRE: 20110928
rem 2011-07-19aRagexeRE: 20110719
rem 2011-03-09aRagexeRE: 20110309
rem 2011-01-11aRagexeRE: 20110111
rem 2010-10-20aRagexeRE: 20101020
rem 2010-08-03aRagexeRE: 20100803
rem 2010-07-28aRagexeRE: 20100728
rem 2010-07-21aRagexeRE: 20100721
rem 2010-06-29aRagexeRE: 20100629
rem 2010-06-15aRagexeRE: 20100615
rem 2010-04-14aRagexeRE: 20100414
rem 2010-02-23aRagexeRE: 20100223
rem 2009-12-08aRagexeRE: 20091208
rem 2009-11-18cRagexeRE: 20091118
rem 2009-11-04aRagexeRE: 20091104
rem 2009-07-15aRagexeRE: 20090715
rem 2009-06-17aRagexeRE: 20090617
rem 2009-06-03aRagexeRE: 20090603
rem 2008-11-26cSakexe or 2008-11-26aRagexeRE: 20081126
rem 2008-11-13aSakexe: 20081113
rem 2008-08-20aSakexe: 20080820
rem 2008-05-28aSakexe or 2008-08-27aRagexeRE: 20080827
rem 2008-01-02aSakexe: 20080102
rem 2007-11-28aSakexe: 20071128
rem 2007-11-06aSakexe: 20071106
rem 2007-09-04aSakexe: 20070904
rem 2007-07-11aSakexe: 20070711
rem 2007-05-21aSakexe: 20070521
rem 2007-02-12aSakexe: 20070212
rem 2006-10-23aSakexe: 20061023
set __PACKETDEF__=/D "PACKETVER=20151029" /D "NEW_006b"

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

rem ---- VC++ 2008 Express Edition の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files\Microsoft Visual Studio 9.0\VC\bin;C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE;C:\Program Files\Microsoft Platform SDK\Bin;C:\Program Files\Microsoft Platform SDK\Bin\winnt;C:\Program Files\Microsoft Platform SDK\Bin\Win64;%PATH%
rem set INCLUDE=C:\Program Files\Microsoft Visual Studio 9.0\VC\include;C:\Program Files\Microsoft Platform SDK\include;%INCLUDE%
rem set LIB=C:\Program Files\Microsoft Visual Studio 9.0\VC\lib;C:\Program Files\Microsoft Platform SDK\Lib;%LIB%
rem set __VCVER__=9
rem ---- VC++ 2008 Express Edition の設定ここまで

rem ---- VC++ 2008 (Express以外) の設定 / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio 9.0\VC\bin\VCVARS32.BAT"
rem set __VCVER__=9
rem ---- VC++ 2008 (Express以外) の設定ここまで

rem ---- VC++ 2008 64bitコンパイル (Express以外) の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin\x86_amd64;C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin;C:\Program Files\Microsoft SDKs\Windows\v6.0A\Bin;C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools\bin;C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\Tools;C:\Program Files (x86)\Microsoft Visual Studio 9.0\Common7\IDE;%PATH%
rem set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\altmfc\include;C:\Program Files\Microsoft SDKs\Windows\v6.0A\Include;%INCLUDE%
rem set LIB=C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib\amd64;C:\Program Files\Microsoft SDKs\Windows\v6.0A\Lib\x64;C:\Program Files (x86)\Microsoft Visual Studio 9.0\SDK\v2.0\lib\amd64;%LIB%
rem set __VCVER__=9
rem set __BITTYPE__=x64
rem ---- VC++ 2008 64bitコンパイル (Express以外) の設定ここまで

rem ---- VC++ 2010 Express Edition の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files\Microsoft Visual Studio 10.0\VC\bin;C:\Program Files\Microsoft Visual Studio 10.0\Common7\IDE;C:\Program Files\Microsoft Platform SDK\Bin;C:\Program Files\Microsoft Platform SDK\Bin\winnt;C:\Program Files\Microsoft Platform SDK\Bin\Win64;%PATH%
rem set INCLUDE=C:\Program Files\Microsoft Visual Studio 10.0\VC\include;C:\Program Files\Microsoft Platform SDK\include;%INCLUDE%
rem set LIB=C:\Program Files\Microsoft Visual Studio 10.0\VC\lib;C:\Program Files\Microsoft Platform SDK\Lib;%LIB%
rem set __VCVER__=10
rem ---- VC++ 2010 Express Edition の設定ここまで

rem ---- VC++ 2010 (Express以外) の設定 / 必要ならコメントアウトをはずす
rem call "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\VCVARS32.BAT"
rem set __VCVER__=10
rem ---- VC++ 2010 (Express以外) の設定ここまで

rem ---- VC++ 2010 64bitコンパイル (Express以外) の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin\x86_amd64;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\bin;C:\Program Files\Microsoft SDKs\Windows\v7.1\Bin;C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools\bin;C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\Tools;C:\Program Files (x86)\Microsoft Visual Studio 10.0\Common7\IDE;%PATH%
rem set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\altmfc\include;C:\Program Files\Microsoft SDKs\Windows\v7.1\Include;%INCLUDE%
rem set LIB=C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\amd64;C:\Program Files\Microsoft SDKs\Windows\v7.1\Lib\x64;C:\Program Files (x86)\Microsoft Visual Studio 10.0\SDK\v2.0\lib\amd64;%LIB%
rem set __VCVER__=10
rem set __BITTYPE__=x64
rem ---- VC++ 2010 64bitコンパイル (Express以外) の設定ここまで

rem ---- VC++ 2012 64bitコンパイル (Express以外) の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\bin\x86_amd64;C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\bin;C:\Program Files\Windows Kits\8.0\bin;C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools\bin;C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\Tools;C:\Program Files (x86)\Microsoft Visual Studio 11.0\Common7\IDE;%PATH%
rem set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\altmfc\include;C:\Program Files (x86)\Windows Kits\8.0\Include\um;C:\Program Files (x86)\Windows Kits\8.0\Include\shared;%INCLUDE%
rem set LIB=C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\lib\amd64;C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x64;C:\Program Files (x86)\Microsoft Visual Studio 11.0\SDK\v2.0\lib\amd64;%LIB%
rem set __VCVER__=11
rem set __BITTYPE__=x64
rem ---- VC++ 2012 64bitコンパイル (Express以外) の設定ここまで

rem ---- VC++ 2013 64bitコンパイル の設定 / 必要ならコメントアウトをはずす
rem sset PATH=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\x86_amd64;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin;C:\Program Files (x86)\Windows Kits\8.1\bin\x64;C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools;%PATH%
rem sset INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\altmfc\include;C:\Program Files (x86)\Windows Kits\8.1\Include\um;C:\Program Files (x86)\Windows Kits\8.1\Include\shared;%INCLUDE%
rem sset LIB=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib\amd64;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\atlmfc\lib;C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x64;%LIB%
rem sset __VCVER__=12
rem sset __BITTYPE__=x64
rem ---- VC++ 2013 64bitコンパイル の設定ここまで

rem ---- VC++ 2015 64bitコンパイル の設定 / 必要ならコメントアウトをはずす
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\x86_amd64;C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin;C:\Program Files\Windows Kits\8.1\bin;C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\bin;C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools;C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE;%PATH%
rem set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\include;C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\altmfc\include;C:\Program Files (x86)\Windows Kits\8.1\Include\um;C:\Program Files (x86)\Windows Kits\8.1\Include\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.10150.0\ucrt;%INCLUDE%
rem set LIB=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib\amd64;C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x64;C:\Program Files (x86)\Microsoft Visual Studio 14.0\SDK\v3.5\lib\amd64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10150.0\ucrt\x64;%LIB%
rem set __VCVER__=14
rem set __BITTYPE__=x64
rem ---- VC++ 2015 64bitコンパイル の設定ここまで

rem ---- VC++ 2017 64bitコンパイル の設定
rem set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\bin\HostX64\x64;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\bin;C:\Program Files\Windows Kits\8.1\bin;C:\Program Files\Windows Kits\10\bin;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\bin;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE;%PATH%
rem set INCLUDE=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\include;C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\atlmfc\include;C:\Program Files (x86)\Windows Kits\8.1\Include\um;C:\Program Files (x86)\Windows Kits\8.1\Include\shared;C:\Program Files (x86)\Windows Kits\10\Include\10.0.10150.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\ucrt;C:\Program Files (x86)\Windows Kits\10\Li\10.0.14393.0\ucrt;%INCLUDE%
rem set LIB=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.10.25017\lib\x64;C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10150.0\ucrt\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10240.0\ucrt\x64;C:\Program Files (x86)\Windows Kits\10\Lib\10.0.14393.0\ucrt\x64;%LIB%
rem set __VCVER__=2017
rem set __BITTYPE__=x64
rem ---- VC++ 2017 64bitコンパイル の設定ここまで

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
rem set INCLUDE=C:\Program Files\MySQL\MySQL Server 5.5\include;%INCLUDE%
rem set LIB=C:\Program Files\MySQL\MySQL Server 5.5\lib;%LIB%

rem ----------------------------------------------------------------
rem VC8以上 で指定できないオプションの回避処理
if "%__VCVER__%"=="8" goto SKIPVC8
if "%__VCVER__%"=="9" goto SKIPVC8
if "%__VCVER__%"=="10" goto SKIPVC8
if "%__VCVER__%"=="11" goto SKIPVC8
if "%__VCVER__%"=="12" goto SKIPVC8
if "%__VCVER__%"=="14" goto SKIPVC8
if "%__VCVER__%"=="2017" goto SKIPVC8
set __OPT_OP__=/Op
:SKIPVC8

rem ----------------------------------------------------------------
rem VC6 で指定できないオプションの回避処理
if "%__VCVER__%"=="6" goto SKIPVC6
set __FIXOPT2__=/MAP /nologo
:SKIPVC6

rem ----------------------------------------------------------------
rem VC9以下 で指定できないオプションの回避処理
if "%__VCVER__%"=="6" goto SKIPVC9
if "%__VCVER__%"=="7" goto SKIPVC9
if "%__VCVER__%"=="8" goto SKIPVC9
set __MULTIBUILD__=/MP
:SKIPVC9

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
set __NO_HTTPD__=/D "NO_HTTPD"

rem httpd で外部 CGI を使う場合はコメントアウトする
set __NO_HTTPD_CGI__=/D "NO_HTTPD_CGI"

rem csvdb のスクリプトからの利用を無効にする場合コメントアウトをはずす
rem set __NO_CSVDB_SCRIPT__=/D "NO_CSVDB_SCRIPT"

rem R化前のシステムを使う場合はコメントアウトをはずす
rem set __PRE_RENEWAL__=/D "PRE_RENEWAL"

rem MB を使う場合はコメントアウトをはずす
rem set __EXCLASS__=/D "CLASS_MB"

rem 動的にMOBの sc_data を確保する場合はコメントアウトをはずす
set __DYNAMIC_STATUS_CHANGE__=/D "DYNAMIC_SC_DATA"

rem キャラの削除にメールアドレスを使う場合はコメントアウトをはずす
rem set __AC_MAIL__=/D "AC_MAIL"

rem キャラの削除に誕生日を使う場合はコメントアウトをはずす
rem set __AC_BIRTHDATE__=/D "AC_BIRTHDATE"

rem ステータス異常データの保存を無効にする場合はコメントアウトをはずす
rem set __NO_SCDATA_SAVING__=/D "NO_SCDATA_SAVING"

rem タイマーをキャッシュするならコメントアウトをはずす
rem set __TIMER_CACHE__=/D "TIMER_CACHE=256"

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

if "%__BITTYPE__%"=="x32" set __BITOPTION__=/D "WIN32" /D "_WIN32" /D "_WIN32_WINDOWS"
if "%__BITTYPE__%"=="x64" set __BITOPTION__=/D "WIN64" /D "_WIN64"

set __opt1__=/D "FD_SETSIZE=4096" /D "NDEBUG" /D "_CONSOLE" /D "_CRT_SECURE_NO_DEPRECATE" /D "WINDOWS" %__MULTIBUILD__% %__BITOPTION__% %__PACKETDEF__% %__TXT_MODE__% %__ZLIB__% %__CMP_AFL2__% %__CMP_AFIP__% %__NO_HTTPD__% %__NO_HTTPD_CGI__% %__NO_CSVDB_SCRIPT__% %__PRE_RENEWAL__% %__EXCLASS__% %__DYNAMIC_STATUS_CHANGE__% %__AC_MAIL__% %__AC_BIRTHDATE__% %__NO_SCDATA_SAVING__% %__TIMER_CACHE__%
set __opt2__=/DEBUG %__FIXOPT2__% user32.lib %__LINKZLIB__% ../common/lua/*.lib ../common/*.obj *.obj
set __include__=/I "../common/zlib/" /I "../common/lua/" /I "../common/"

if "%__TXT_MODE__%"=="" (set __dbmode__=sql) else (set __dbmode__=txt)

rem ----------------------------------------------------------------
rem 警告の抑制
rem   C4819 : 表示できない文字を含んでいます
set __warning__=/wd4819

rem ----------------------------------------------------------------
rem コンパイルオプションの表示

echo ■コンパイル情報表示■
echo ◆───────────────────────────────◆
echo [VCVER = %__VCVER__%]
echo [BITTYPE = %__BITTYPE__%]
echo [model = %_model_%]
echo [CompileOption = %__opt1__%]
echo ◆───────────────────────────────◆

rem ビルド作業本体

rem 共通コンポーネントのコンパイル
cd src\common\zlib
if "%__ZLIB__%"=="" goto NOZLIB2
echo zlibのコンパイル
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c

:NOZLIB2
echo luaのコンパイル
cd ..\lua
cl %__BITOPTION__% /D "_LIB" /c *.c
del lua.obj luac.obj
lib /out:lualib.lib *.obj

echo 共通コンポーネントのコンパイル
cd ..\
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c

rem サーバー本体のビルド
echo ログインサーバーコンパイル
cd ..\login
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c .\%__dbmode__%\*.c
link %__opt2__% /out:"../../login-server.exe"

echo キャラクターサーバーコンパイル
cd ..\char
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c .\%__dbmode__%\*.c
link %__opt2__% /out:"../../char-server.exe"

echo マップサーバーコンパイル
cd ..\map
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c .\%__dbmode__%\*.c
link %__opt2__% /out:"../../map-server.exe"

rem 必要なら txt-converter をビルド
if NOT "%__TXT_MODE__%"=="" goto NOCONVERTER1
if "%__TXTCONVERTER__%"=="SKIP" goto NOCONVERTER1

echo コンバーターコンパイル
cd ..\converter
cl %__warning__% %__cpu__% %__opt1__% %__include__% *.c
link %__opt2__% /out:"../../txt-converter.exe"
:NOCONVERTER1

cd ..\..\

rem 不必要なファイルを削除
echo オブジェクトファイル等のクリーンアップ
if "%__ZLIB__%"=="" goto NOZLIB3
del src\common\zlib\*.obj
:NOZLIB3
del src\common\lua\*.obj
del src\common\lua\*.lib
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
