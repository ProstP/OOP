@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Run Program with 0, 1, 2, 3, 5 arguments
%MyProgram% && goto err
echo Test 1 passed
%MyProgram% crypt && goto err
echo Test 2 passed
%MyProgram% crypt input.txt && goto err
echo Test 3 passed
%MyProgram% crypt input.txt output.txt && goto err
echo Test 4 passed
%MyProgram% crypt input.txt ouput.txt 20 excessArg && goto err
echo Test 5 passed

REM Invalid mode
%MyProgram% invalid input.txt ouput.txt 2 && goto err
echo Test 6 passed

REM Key less min and more max acceptable value
%MyProgram% crypt input.txt ouput.txt -1 && goto err
echo Test 7 passed
%MyProgram% crypt input.txt ouput.txt 256 && goto err
echo Test 8 passed

REM Input file not found
%MyProgram% crypt Missing.txt output.txt 2 && goto err
echo Test 9 passed

REM Input file empty
%MyProgram% crypt Empty.txt "%TEMP%\output.txt" 2 || goto err
fc Empty.txt "%TEMP%\output.txt" > nil || goto err
echo Test 10 passed

REM Crypt and decrypt file with one line
%MyProgram% crypt OneLine.txt "%TEMP%\output.txt" 2 || goto err
fc OneLine.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% decrypt "%TEMP%\output.txt" "%TEMP%\output1.txt" 2 || goto err
fc OneLine.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 11 passed

REM Crypt and decrypt file with many line
%MyProgram% crypt ManyLines.txt "%TEMP%\output.txt" 20 || goto err
fc OneLine.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% decrypt "%TEMP%\output.txt" "%TEMP%\output1.txt" 20 || goto err
fc ManyLines.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 12 passed

echo All tests passed successfully
exit /B 0

:err
echo Tests failed
exit /B 1