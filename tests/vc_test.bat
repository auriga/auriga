@echo off
rem Build and run Unity unit tests with MSVC (cl.exe).
rem Run from a Developer Command Prompt, or after vcvars64.bat.
rem Keep TEST_SRCS / COMMON_NAMES in sync with Makefile (see doc/unit_test.txt).

setlocal EnableExtensions EnableDelayedExpansion
cd /d "%~dp0"

set COMMON=..\src\common
set MAP=..\src\map
set UNITY=..\third_party\unity\src
set XXHASH=..\third_party\xxhash
set LZ4=..\third_party\lz4
set CFLAGS=/nologo /W3 /Od /D_CRT_SECURE_NO_WARNINGS /I"%COMMON%" /I"%MAP%" /I"%UNITY%" /I"%XXHASH%" /I"%LZ4%" /TC

if not exist stubs mkdir stubs

echo Building unit tests (MSVC)...

set OBJS=
for %%F in (test_main.c test_md5calc.c test_utils.c test_db.c test_misc.c test_status_calc_ctrl.c test_pc_ui.c test_cashshop.c test_account_cashshop.c test_stylist.c test_searchstore.c test_grf_protected.c) do (
  cl %CFLAGS% /c /Fo%%~nF.obj %%F
  if errorlevel 1 exit /b 1
  set OBJS=!OBJS! %%~nF.obj
)

for %%S in (malloc_stub grfio_stub) do (
  cl %CFLAGS% /c /Fostubs\%%S.obj stubs\%%S.c
  if errorlevel 1 exit /b 1
  set OBJS=!OBJS! stubs\%%S.obj
)

for %%N in (md5calc utils db lock nullpo grf_protected) do (
  cl %CFLAGS% /c /Fo%%N.obj "%COMMON%\%%N.c"
  if errorlevel 1 exit /b 1
  set OBJS=!OBJS! %%N.obj
)

cl %CFLAGS% /c /Fostatus_calc_ctrl.obj "%MAP%\status_calc_ctrl.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! status_calc_ctrl.obj

cl %CFLAGS% /c /Fopc_ui.obj "%MAP%\pc_ui.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! pc_ui.obj

cl %CFLAGS% /c /Focashshop.obj "%MAP%\cashshop.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! cashshop.obj

cl %CFLAGS% /c /Fostylist.obj "%MAP%\stylist.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! stylist.obj

cl %CFLAGS% /c /Fosearchstore.obj "%MAP%\searchstore.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! searchstore.obj

cl %CFLAGS% /c /Focashshopdb_txt.obj ..\src\char\txt\cashshopdb_txt.c
if errorlevel 1 exit /b 1
set OBJS=!OBJS! cashshopdb_txt.obj

cl %CFLAGS% /c /Folz4.obj "%LZ4%\lz4.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! lz4.obj

cl %CFLAGS% /c /Founity.obj "%UNITY%\unity.c"
if errorlevel 1 exit /b 1
set OBJS=!OBJS! unity.obj

cl /nologo /Fe:unit_tests.exe %OBJS%
if errorlevel 1 exit /b 1

echo Running unit_tests.exe...
unit_tests.exe
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /Dfflush=journal_test_fflush /Dfwrite=journal_test_fwrite /Dfclose=journal_test_fclose /DJOURNAL_TIME_SOURCE=journal_test_time /DJOURNAL_TELL_SOURCE=journal_test_tell /DJOURNAL_READ_SOURCE=journal_test_read /c /Fojournal.obj "%COMMON%\journal.c"
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /c /Fotest_journal.obj test_journal.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /c /Fotest_cashshop_journal.obj test_cashshop_journal.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /c /Focashshopdb_journal.obj ..\src\char\txt\cashshopdb_txt.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /c /Fotest_cashshop_journal.obj test_cashshop_journal.c
if errorlevel 1 exit /b 1
cl %CFLAGS% /DTXT_JOURNAL /c /Focashshopdb_journal.obj ..\src\char\txt\cashshopdb_txt.c
if errorlevel 1 exit /b 1
cl /nologo /Fe:journal_tests.exe test_journal.obj test_cashshop_journal.obj cashshopdb_journal.obj journal.obj db.obj utils.obj nullpo.obj lock.obj stubs\malloc_stub.obj unity.obj
if errorlevel 1 exit /b 1
journal_tests.exe
exit /b %ERRORLEVEL%
