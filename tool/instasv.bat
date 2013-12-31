@echo off
rem Windowsサービスへ登録を行うバッチファイル

rem ----------------------------------------------------------------
rem サービス名設定
set __LOGIN_SVC__=AurigaLoginServer
set __CHAR_SVC__=AurigaCharServer
set __MAP_SVC__=AurigaMapServer

rem サービス表示名・説明設定
set __LOGIN_DESC__=Auriga Login Server
set __CHAR_DESC__=Auriga Char Server
set __MAP_DESC__=Auriga Map Server

rem 標準出力のリダイレクト先ログファイル名設定
set __LOGIN_LOGFILE__=./log/login-stdout.log
set __CHAR_LOGFILE__=./log/char-stdout.log
set __MAP_LOGFILE__=./log/map-stdout.log
rem ----------------------------------------------------------------

rem カレントディレクトリの補正
cd %~dp0
cd ..
set __BASE_DIR__=%cd%

echo ■Aurigaをサービスとして登録します。■

if "%__LOGIN_SVC__%"=="" goto SKIP1
echo Installing Service "%__LOGIN_SVC__%" ...
sc.exe create %__LOGIN_SVC__% DisplayName= "%__LOGIN_DESC__%" binPath= "%__BASE_DIR__%\login-server.exe --service-name %__LOGIN_SVC__% --stdout %__LOGIN_LOGFILE__%"
sc.exe description %__LOGIN_SVC__% "%__LOGIN_DESC__%"
echo.
:SKIP1

if "%__CHAR_SVC__%"=="" goto SKIP2
echo Installing Service "%__CHAR_SVC__%" ...
sc.exe create %__CHAR_SVC__% DisplayName= "%__CHAR_DESC__%" binPath= "%__BASE_DIR__%\char-server.exe --service-name %__CHAR_SVC__% --stdout %__CHAR_LOGFILE__%"
sc.exe description %__CHAR_SVC__% "%__CHAR_DESC__%"
echo.
:SKIP2

if "%__MAP_SVC__%"=="" goto SKIP3
echo Installing Service "%__MAP_SVC__%" ...
sc.exe create %__MAP_SVC__% DisplayName= "%__MAP_DESC__%" binPath= "%__BASE_DIR__%\map-server.exe --service-name %__MAP_SVC__%  --stdout %__MAP_LOGFILE__%"
sc.exe description %__MAP_SVC__% "%__MAP_DESC__%"
echo.
:SKIP3

echo ★Login, Char, MapサーバをWindowsのサービスとして登録しました。
echo ★障害時の自動起動をONにする場合はWindowsの「管理ツール」から「サービス」を選択してください。

pause
