@echo off
rem Build and run Unity unit tests with MSVC (cl.exe).
rem Run from a Developer Command Prompt, or after vcvars64.bat.
rem Keep TEST_SRCS / COMMON_NAMES in sync with Makefile (see doc/unit_test.txt).

setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"

set COMMON=..\src\common
set MAP=..\src\map
set UNITY=..\third_party\unity\src
set CFLAGS=/nologo /W3 /Od /D_CRT_SECURE_NO_WARNINGS /I"%COMMON%" /I"%MAP%" /I"%UNITY%" /TC

if not exist stubs mkdir stubs

echo Building unit tests (MSVC)...

set OBJS=
for %%F in (test_main.c test_md5calc.c test_utils.c test_db.c test_misc.c test_status_calc_ctrl.c) do (
  cl %CFLAGS% /c /Fo%%~nF.obj %%F
  if errorlevel 1 exit /b 1
  set OBJS=!OBJS! %%~nF.obj
)

cl %CFLAGS% /c /Fostubs\malloc_stub.obj stubs\malloc_stub.c
if errorlevel 1 exit /b 1
set OBJS=!OBJS! stubs\malloc_stub.obj

for %%N in (md5calc utils db lock nullpo) do (
  cl %CFLAGS% /c /Fo%%N.obj "%COMMON%\%%N.c"
  if errorlevel 1 exit /b 1
  set OBJS=!OBJS! %%N.obj
)

cl %CFLAGS% /c /Fostatus_calc_ctrl.obj "%MAP%\status_calc_ctrl.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! status_calc_ctrl.obj

cl %CFLAGS% /c /Founity.obj "%UNITY%\unity.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! unity.obj

cl /nologo /Fe:unit_tests.exe %OBJS%
if errorlevel 1 exit /b 1

echo Running unit_tests.exe...
unit_tests.exe
exit /b %ERRORLEVEL%
