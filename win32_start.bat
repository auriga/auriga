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
IF NOT EXIST .\save\auriga.txt echo creating .\save\auriga.txt
IF NOT EXIST .\save\auriga.txt type nul > .\save\auriga.txt
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
IF NOT EXIST .\save\account.txt set _aurigatmp_=1
if "%_aurigatmp_%" == "1" echo 0	s1	p1	-	S	0	0	@	000000 >.\save\account.txt
if "%_aurigatmp_%" == "1" echo 1	s2	p2	-	S	0	0	@	000000 >>.\save\account.txt
if "%_aurigatmp_%" == "1" echo 2	s3	p3	-	S	0	0	@	000000 >>.\save\account.txt
if "%_aurigatmp_%" == "1" echo 3	s4	p4	-	S	0	0	@	000000 >>.\save\account.txt
if "%_aurigatmp_%" == "1" echo 4	s5	p5	-	S	0	0	@	000000 >>.\save\account.txt
if "%_aurigatmp_%" == "1" set _aurigatmp_=

IF NOT EXIST .\save\castle.txt echo creating .\save\castle.txt

IF NOT EXIST .\conf\login_auriga.conf echo Missing .\conf\login_auriga.conf
IF NOT EXIST .\conf\login_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\char_auriga.conf echo Missing .\conf\char_auriga.conf
IF NOT EXIST .\conf\char_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\inter_auriga.conf echo Missing .\conf\inter_auriga.conf
IF NOT EXIST .\conf\inter_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\map_auriga.conf echo Missing .\conf\map_auriga.conf
IF NOT EXIST .\conf\map_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\battle_auriga.conf echo Missing .\conf\battle_auriga.conf
IF NOT EXIST .\conf\battle_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\atcommand_auriga.conf echo Missing .\conf\atcommand_auriga.conf
IF NOT EXIST .\conf\atcommand_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\script_auriga.conf echo Missing .\conf\script_auriga.conf
IF NOT EXIST .\conf\script_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\msg_auriga.conf echo Missing .\conf\msg_auriga.conf
IF NOT EXIST .\conf\msg_auriga.conf set _aurigatmp_=1
IF NOT EXIST .\conf\grf-files.txt echo Missing .\conf\grf-files.txt
IF NOT EXIST .\conf\grf-files.txt set _aurigatmp_=1
if "%_aurigatmp_%" == "1" pause
if "%_aurigatmp_%" == "1" goto end

start win32_start boot login-server.exe
start win32_start boot char-server.exe
start win32_start boot map-server.exe
goto end

:boot
if not exist %2 goto end
echo Auriga 自動再起動スクリプト for WIN32
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
if "%_aurigatmp_%" == "1" set _aurigatmp_=
echo %2
