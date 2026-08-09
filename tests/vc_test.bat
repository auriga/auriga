@echo off
rem Build and run Unity unit tests with MSVC (cl.exe).
rem Run from a Developer Command Prompt, or after vcvars64.bat.

setlocal EnableExtensions
cd /d "%~dp0"

set COMMON=..\src\common
set UNITY=..\third_party\unity\src
set CFLAGS=/nologo /W3 /Od /D_CRT_SECURE_NO_WARNINGS /I"%COMMON%" /I"%UNITY%" /TC

if not exist stubs mkdir stubs

echo Building unit tests (MSVC)...
cl %CFLAGS% /c /Fotest_main.obj test_main.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fotest_md5calc.obj test_md5calc.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fotest_utils.obj test_utils.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fotest_db.obj test_db.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fotest_misc.obj test_misc.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fostubs\malloc_stub.obj stubs\malloc_stub.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fomd5calc.obj "%COMMON%\md5calc.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Foutils.obj "%COMMON%\utils.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fodb.obj "%COMMON%\db.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Folock.obj "%COMMON%\lock.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Fonullpo.obj "%COMMON%\nullpo.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /c /Founity.obj "%UNITY%\unity.c"
if errorlevel 1 exit /b 1

cl /nologo /Fe:unit_tests.exe ^
  test_main.obj test_md5calc.obj test_utils.obj test_db.obj test_misc.obj ^
  stubs\malloc_stub.obj md5calc.obj utils.obj db.obj lock.obj nullpo.obj unity.obj
if errorlevel 1 exit /b 1

echo Running unit_tests.exe...
unit_tests.exe
exit /b %ERRORLEVEL%
