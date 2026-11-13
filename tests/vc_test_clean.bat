@echo off
rem Clean MSVC unit test build products.
rem Keep lists in sync with Makefile / vc_test.bat (see doc/unit_test.txt).

setlocal EnableExtensions
cd /d "%~dp0"

del /Q unit_tests.exe 2>nul
for %%F in (test_main test_md5calc test_utils test_db test_misc test_status_calc_ctrl test_pc_ui test_grf_protected md5calc utils db lock nullpo grf_protected status_calc_ctrl pc_ui lz4 unity) do (
  del /Q %%F.obj 2>nul
)
for %%S in (malloc_stub grfio_stub) do (
  del /Q stubs\%%S.obj 2>nul
)
exit /b 0
