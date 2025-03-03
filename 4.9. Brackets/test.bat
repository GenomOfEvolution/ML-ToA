@echo off

set PROGRAM="%~1"
set TEST_COUNT=0
set PASSED_COUNT=0

:TEST_LOOP
if not exist tests\input%TEST_COUNT%.txt (
    goto END_TESTS
)

%PROGRAM% tests\input%TEST_COUNT%.txt tests\myOut%TEST_COUNT%.txt

fc tests\myOut%TEST_COUNT%.txt tests\output%TEST_COUNT%.txt >nul
if errorlevel 1 (
   echo Test %TEST_COUNT% failed!
) else (
    set /A PASSED_COUNT+=1
)

set /A TEST_COUNT+=1
goto TEST_LOOP

:END_TESTS
echo All tests passed! Sucessfully completed %PASSED_COUNT% of %TEST_COUNT% tests.
exit /B 0