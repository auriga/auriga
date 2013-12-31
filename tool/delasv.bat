@echo off
rem Windowsサービスから削除を行うバッチファイル

rem ----------------------------------------------------------------
rem サービス名設定
set __LOGIN_SVC__=AurigaLoginServer
set __CHAR_SVC__=AurigaCharServer
set __MAP_SVC__=AurigaMapServer
rem ----------------------------------------------------------------

echo ■Aurigaをサービスから削除します■

if "%__LOGIN_SVC__%"=="" goto SKIP1
echo UnInstalling Service "%__LOGIN_SVC__%" ...
sc.exe delete %__LOGIN_SVC__%
echo.
:SKIP1

if "%__CHAR_SVC__%"=="" goto SKIP2
echo UnInstalling Service "%__CHAR_SVC__%" ...
sc.exe delete %__CHAR_SVC__%
echo.
:SKIP2

if "%__MAP_SVC__%"=="" goto SKIP3
echo UnInstalling Service "%__MAP_SVC__%" ...
sc.exe delete %__MAP_SVC__%
echo.
:SKIP3

echo ★Login, Char, MapサーバをWindowsのサービスから解除を試みました。
echo ★エラーが発生している場合は、あらかじめサービスを停止してから再度実行してください。

pause
