@echo off
rem Clean MSVC unit test build products.
rem Keep lists in sync with Makefile / vc_test.bat (see doc/unit_test.txt).

setlocal EnableExtensions
cd /d "%~dp0"

del /Q unit_tests.exe 2>nul
for %%F in (test_main test_md5calc test_utils test_db test_misc md5calc utils db lock nullpo unity) do (
  del /Q %%F.obj 2>nul
)
del /Q stubs\malloc_stub.obj 2>nul
exit /b 0
