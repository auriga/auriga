@echo off
@echo →Athenaをサービスから抹消します

set reskit=
set svname=
if "%svname%"=="" goto error3
if "%reskit%"=="" goto error2
if not exist %reskit%sc.exe goto error1

%reskit%sc.exe %svname% Delete AthenaLogin
%reskit%sc.exe %svname% Delete AthenaChar
%reskit%sc.exe %svname% Delete AthenaMap

@echo ★Login.Char.MapサーバをWindowsのサービスからの解除を試みました。
@echo ★エラーが発生している場合は、あらかじめサービスを停止してから再度実行してください。
goto end

:error3
@echo ●サーバ名が未設定です、Windowsの場合はコンピューター名がサーバー名になります
@echo コントロールパネル内システムのネットワークIDに表示されるコンピュータ名を
@echo 環境変数設定例 set svname="\\myserver"のように設定してください、\\は必須です。
goto end

:error2
@echo ●エラーが発生しました。リソースキットのパスが設定されていません
@echo 環境変数設定例 set reskit="C:\Program Files\Resource Kit\"
goto end

:error1
@echo ●エラーが発生しました。リソースキッド非導入による「SC.EXE」の欠損あるいは
@echo リソースキットにパスが通っていない可能性があります。
@echo リソースキット設定の確認もしくはリソースキットを導入してください
goto end

:error
:end
pause
