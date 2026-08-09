@echo off
rem Clean MSVC unit test build products.

setlocal EnableExtensions
cd /d "%~dp0"

del /Q unit_tests.exe 2>nul
del /Q test_main.obj test_md5calc.obj test_utils.obj test_db.obj test_misc.obj md5calc.obj utils.obj db.obj lock.obj nullpo.obj unity.obj 2>nul
del /Q stubs\malloc_stub.obj 2>nul
exit /b 0
