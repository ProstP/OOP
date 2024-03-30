@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Run Program with 0, 1, 2, 4 arguments
%MyProgram% && goto err
echo Test 1 passed
%MyProgram% 10 && goto err
echo Test 2 passed
%MyProgram% 10 16 && goto err
echo Test 3 passed
%MyProgram% 10 16 120 1222 && goto err
echo Test 4 passed

REM Notation is not int value
%MyProgram% A 12 12 && goto err
echo Test 5 passed
%MyProgram% 10 B 12 && goto err
echo Test 6 passed

REM Notation is not between acceptable values
%MyProgram% 10 1555 12 && goto err
echo Test 7 passed
%MyProgram% 1000 15 12 && goto err
echo Test 8 passed

REM Convert 0
%MyProgram% 2 10 0 > "%TEMP%\output.txt" || goto err
fc "%TEMP%\output.txt" FileWithZero.txt > nil || goto err
echo Test 9 passed

REM Convert from min to max notation
%MyProgram% 2 36 110001011 > "%TEMP%\output.txt" || goto err
echo AZ> "%TEMP%\expected.txt"
fc "%TEMP%\output.txt" "%TEMP%\expected.txt" > nil || goto err
echo Test 10 passed

REM Convert value bigger maxint
%MyProgram% 36 10 ZIK0ZZ > "%TEMP%\output.txt" && goto err
echo Test 11 passed

REM Convert value less minint
%MyProgram% 36 10 -ZIK0ZZ > "%TEMP%\output.txt" && goto err
echo Test 12 passed

REM value has digit bigger source radix
%MyProgram% 2 10 1002 > "%TEMP%\output.txt" && goto err
echo Test 13 passed

REM value has invalid symbol
%MyProgram% 7 10 123:4 > "%TEMP%\output.txt" && goto err
echo Test 14 passed

REM Convert from small to big radix
%MyProgram% 7 23 6632111 > "%TEMP%\output.txt" || goto err
echo 2KM0M> "%TEMP%\expected.txt"
fc "%TEMP%\output.txt" "%TEMP%\expected.txt" > nil || goto err
echo Test 15 passed

REM Convert from big to small radix
%MyProgram% 30 15 AF54G > "%TEMP%\output.txt" || goto err
echo B31591> "%TEMP%\expected.txt"
fc "%TEMP%\output.txt" "%TEMP%\expected.txt" > nil || goto err
echo Test 16 passed

REM Convert negative value
%MyProgram% 13 6 -AC5 > "%TEMP%\output.txt" || goto err
echo -12323> "%TEMP%\expected.txt"
fc "%TEMP%\output.txt" "%TEMP%\expected.txt" > nil || goto err
echo Test 17 passed

echo All tests passed successfuly
exit /B 0

:err
echo Test failed
exit /B 1