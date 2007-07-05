@echo off
@echo →Aurigaをサービスとして登録します。

@rem -----設定部---------
set aurigasrv="c:\auriga"
@rem Aurigaのバイナリのある場所を指定します。
@rem --------------------
if "%aurigasrv%"=="" goto error

sc.exe Create AurigaLogin binPath= %aurigasrv%\login-server.exe
sc.exe Create AurigaChar binPath= %aurigasrv%\char-server.exe
sc.exe Create AurigaMap binPath= %aurigasrv%\map-server.exe

@echo ★Login.Char.MapサーバをWindowsのサービスとして登録しました。
@echo ★障害時の自動起動をONにする場合はWindowsの「管理ツール」から「サービス」を選択してください。
goto end

:error
@echo ●環境変数　set aurigasrv=　にサーバプログラムのパスが設定されていない状態です。
@echo 環境変数設定例　set aurigasrv="c:\auriga"　など
:end
pause
