@echo off
rem Clean MSVC unit test build products.

setlocal EnableExtensions
cd /d "%~dp0"

del /Q unit_tests.exe 2>nul
del /Q test_main.obj test_md5calc.obj test_utils.obj md5calc.obj utils.obj unity.obj 2>nul
del /Q stubs\malloc_stub.obj 2>nul
exit /b 0
