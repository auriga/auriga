@rem original version from eAthena, thanks. 

@echo off
if "%1" == "boot" goto boot

IF NOT EXIST .\save\con echo creating .\save
IF NOT EXIST .\save\con md .\save
IF NOT EXIST .\mail_data echo creating .\save\mail_data
IF NOT EXIST .\mail_data md .\save\mail_data
IF NOT EXIST .\log\con echo creating .\log
IF NOT EXIST .\log\con md .\log
cd .\conf
IF NOT EXIST .\import\con echo creating .\conf\import
IF NOT EXIST .\import\con md .\import
IF NOT EXIST .\import\con echo creating .\conf\import
cd ..
IF NOT EXIST .\save\athena.txt echo creating .\save\athena.txt
IF NOT EXIST .\save\athena.txt type nul > .\save\athena.txt
IF NOT EXIST .\save\homun.txt echo creating .\save\homun.txt
IF NOT EXIST .\save\homun.txt type nul > .\save\homun.txt
IF NOT EXIST .\save\guild.txt echo creating .\save\guild.txt
IF NOT EXIST .\save\guild.txt type nul > .\save\guild.txt
IF NOT EXIST .\save\party.txt echo creating .\save\party.txt
IF NOT EXIST .\save\party.txt type nul > .\save\party.txt
IF NOT EXIST .\save\pet.txt echo creating .\save\pet.txt
IF NOT EXIST .\save\pet.txt type nul > .\save\pet.txt
IF NOT EXIST .\save\storage.txt echo creating .\save\storage.txt
IF NOT EXIST .\save\storage.txt type nul > .\save\storage.txt
IF NOT EXIST .\save\g_storage.txt echo creating .\save\g_storage.txt
IF NOT EXIST .\save\g_storage.txt type nul > .\save\g_storage.txt
IF NOT EXIST .\conf\import\atcommand_conf.txt echo creating .\conf\import\atcommand_conf.txt
IF NOT EXIST .\conf\import\atcommand_conf.txt type nul > .\conf\import\atcommand_conf.txt
IF NOT EXIST .\conf\import\battle_conf.txt echo creating .\conf\import\battle_conf.txt
IF NOT EXIST .\conf\import\battle_conf.txt type nul > .\conf\import\battle_conf.txt
IF NOT EXIST .\conf\import\char_conf.txt echo creating .\conf\import\char_conf.txt
IF NOT EXIST .\conf\import\char_conf.txt type nul > .\conf\import\char_conf.txt
IF NOT EXIST .\conf\import\inter_conf.txt echo creating .\conf\import\inter_conf.txt
IF NOT EXIST .\conf\import\inter_conf.txt type nul > .\conf\import\inter_conf.txt
IF NOT EXIST .\conf\import\login_conf.txt echo creating .\conf\import\login_conf.txt
IF NOT EXIST .\conf\import\login_conf.txt type nul > .\conf\import\login_conf.txt
IF NOT EXIST .\conf\import\map_conf.txt echo creating .\conf\import\map_conf.txt
IF NOT EXIST .\conf\import\map_conf.txt type nul > .\conf\import\map_conf.txt

IF NOT EXIST .\save\account.txt echo creating .\save\account.txt
IF NOT EXIST .\save\account.txt set _athenatmp_=1
if "%_athenatmp_%" == "1" echo 0	s1	p1	-	S	0	0 >.\save\account.txt
if "%_athenatmp_%" == "1" echo 1	s2	p2	-	S	0	0 >>.\save\account.txt
if "%_athenatmp_%" == "1" echo 2	s3	p3	-	S	0	0 >>.\save\account.txt
if "%_athenatmp_%" == "1" echo 3	s4	p4	-	S	0	0 >>.\save\account.txt
if "%_athenatmp_%" == "1" echo 4	s5	p5	-	S	0	0 >>.\save\account.txt
if "%_athenatmp_%" == "1" set _athenatmp_=

IF NOT EXIST .\save\castle.txt echo creating .\save\castle.txt
IF NOT EXIST .\save\castle.txt set _athenatmp_=1
if "%_athenatmp_%" == "1" echo 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >.\save\castle.txt
if "%_athenatmp_%" == "1" echo 1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 2,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 3,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 4,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 5,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 6,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 7,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 8,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 9,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 10,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 11,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 12,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 13,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 14,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 15,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 16,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 17,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 18,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" echo 19,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 >>.\save\castle.txt
if "%_athenatmp_%" == "1" set _athenatmp_=

IF NOT EXIST .\conf\login_athena.conf echo Missing .\conf\login_athena.conf
IF NOT EXIST .\conf\login_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\char_athena.conf echo Missing .\conf\char_athena.conf
IF NOT EXIST .\conf\char_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\inter_athena.conf echo Missing .\conf\inter_athena.conf
IF NOT EXIST .\conf\inter_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\map_athena.conf echo Missing .\conf\map_athena.conf
IF NOT EXIST .\conf\map_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\battle_athena.conf echo Missing .\conf\battle_athena.conf
IF NOT EXIST .\conf\battle_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\atcommand_athena.conf echo Missing .\conf\atcommand_athena.conf
IF NOT EXIST .\conf\atcommand_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\script_athena.conf echo Missing .\conf\script_athena.conf
IF NOT EXIST .\conf\script_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\msg_athena.conf echo Missing .\conf\msg_athena.conf
IF NOT EXIST .\conf\msg_athena.conf set _athenatmp_=1
IF NOT EXIST .\conf\grf-files.txt echo Missing .\conf\grf-files.txt
IF NOT EXIST .\conf\grf-files.txt set _athenatmp_=1
if "%_athenatmp_%" == "1" pause
if "%_athenatmp_%" == "1" goto end

set __bin__=
if exist "bin\login-server.exe" set __bin__=bin\
start win32_start boot %__bin__%login-server.exe
start win32_start boot %__bin__%char-server.exe
start win32_start boot %__bin__%map-server.exe
goto end

:boot
if not exist %2 goto end
echo Athena 自動再起動スクリプト for WIN32
echo.
echo %2 の異常終了を監視中です。
echo サーバーを終了するには、最初にこのウィンドウを閉じてください。
start /wait %2
cls
echo %2 が終了しました。再起動します。
echo. | date /T
echo. | time /T
goto boot

:end
if "%_athenatmp_%" == "1" set _athenatmp_=
echo %2
