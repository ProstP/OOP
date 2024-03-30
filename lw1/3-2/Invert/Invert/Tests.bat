@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Run Program with 0, 2 arguments
%MyProgram% && goto err
echo Test 1 passed
%MyProgram% File.txt Needless.txt && goto err
echo Test 2 passed

REM Input file is missing
%MyProgram% Missing.txt && goto err
echo Test 3 passed

REM Input file is empty
%MyProgram% Empty.txt && goto err
echo Test 4 passed

REM Matrix do not have row
%MyProgram% MatrixWithoutRow.txt && goto err
echo Test 5 passed

REM Matrix do not have one element
%MyProgram% MatrixWithoutElt.txt && goto err
echo Test 6 passed

REM Succes invert matrix
%MyProgram% Matrix.txt > "%TEMP%\output.txt" || goto err
fc CorrectInvertMatrix.txt "%TEMP%\output.txt" > nil || goto err
echo Test 7 passed

REM MatrixX4 in input
%MyProgram% MatrixX4.txt > "%TEMP%\output.txt" || goto err
fc CorrectInvertMatrix.txt "%TEMP%\output.txt" > nil || goto err
echo Test 8 passed

REM Element have no digit sybmol
%MyProgram% MatrixWithNoDigitElt.txt && goto err
echo Test 9 passed

REM Matrix do not have invert matrix
%MyProgram% MatrixWithoutInvertMatrix.txt > "%TEMP%\output.txt" || goto err
echo Invert matrix can not be> "%TEMP%\ans.txt"
fc "%TEMP%\ans.txt" "%TEMP%\output.txt" > nil || goto err
echo Test 10 passed

echo All tests passed successfully
exit /B 0

:err
echo Test failed
exit /B 1