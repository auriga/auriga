@echo off
@echo →Athenaをサービスとして登録します。

@rem -----設定部---------
set athenasrv="c:\athena"
@rem athenaのバイナリのある場所を指定します。
@rem --------------------
if "%athenasrv%"=="" goto error

sc.exe Create AthenaLogin binPath= %athenasrv%\login-server.exe
sc.exe Create AthenaChar binPath= %athenasrv%\char-server.exe
sc.exe Create AthenaMap binPath= %athenasrv%\map-server.exe

@echo ★Login.Char.MapサーバをWindowsのサービスとして登録しました。
@echo ★障害時の自動起動をONにする場合はWindowsの「管理ツール」から「サービス」を選択してください。
goto end

:error
@echo ●環境変数　set athenasrv=　にサーバプログラムのパスが設定されていない状態です。
@echo 環境変数設定例　set athenasrv="c:\athena"　など
:end
pause
