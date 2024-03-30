@echo off

SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Run Program with 0, 1, 2, 3, 5 agruments
%MyProgram% && goto err
echo Test 1 passed
%MyProgram% input.txt && goto err
echo Test 2 passed
%MyProgram% input.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed
%MyProgram% input.txt "%TEMP%\output.txt" search && goto err
echo Test 4 passed
%MyProgram% input.txt "%TEMP%\output.txt" "search" "replace" "some" && goto err
echo Test 5 passed

REM Input file is missing
%MyProgram% Missing.txt "%TEMP%\output.txt" "search" "replace" && goto err
echo Test 6 passed

REM Input file is empty
%MyProgram% Empty.txt "%TEMP%\output.txt" "search" "replace" || goto err
fc Empty.txt "%TEMP%\output.txt" > nil || goto err
echo Test 7 passed

REM Search string = ""
%MyProgram% input.txt "%TEMP%\output.txt" "" "replace" || goto err
fc input.txt "%TEMP%\output.txt" > nil || goto err
echo Test 8 passed

REM Search string is not contained in input file
%MyProgram% NotEmpty.txt "%TEMP%\output.txt" "search" "replace" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nil || goto err
echo Test 9 passed

REM Replace search string to replace string
REM replace string is not contained in input file
%MyProgram% NotEmpty.txt "%TEMP%\output.txt" "me" "replace" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% "%TEMP%\output.txt" "%TEMP%\output1.txt" "replace" "me" || goto err
fc NotEmpty.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 10 passed

REM Search string inside words
%MyProgram% SearchStringInsideWord.txt "%TEMP%\output.txt" "me" "replace" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% "%TEMP%\output.txt" "%TEMP%\output1.txt" "replace" "me" || goto err
fc SearchStringInsideWord.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 11 passed

REM Multiple occurrences
%MyProgram% MultipleOccurrences.txt "%TEMP%\output.txt" "me" "replace" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% "%TEMP%\output.txt" "%TEMP%\output1.txt" "replace" "me" || goto err
fc MultipleOccurrences.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 12 passed

REM Input file big(10000 lines)
%MyProgram% BigFile.txt "%TEMP%\output.txt" "me" "replace" || goto err
fc NotEmpty.txt "%TEMP%\output.txt" > nil && goto err
%MyProgram% "%TEMP%\output.txt" "%TEMP%\output1.txt" "replace" "me" || goto err
fc BigFile.txt "%TEMP%\output1.txt" > nil || goto err
echo Test 13 passed

REM search string inside string with begin of part of search word
%MyProgram% SearchStringInsideWordWithSearchPart.txt "%TEMP%\output.txt" "1231234" " replace " || goto err
fc ReplacedSearchStringInsideWordWithSearchPart.txt "%TEMP%\output.txt" > nil || goto err
echo Test 14 passed

echo All tests passed successfuly
exit /B 0

:err
echo Tests failed
exit /B 1