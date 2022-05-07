rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

echo Test 1
rem 
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

echo Test 2
rem
%PROGRAM% "test-data\matrix.txt" >"%TEMP%\matrix-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\matrix-estimated.txt" "%TEMP%\matrix-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 3
rem
%PROGRAM% "test-data\E.txt" >"%TEMP%\E-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\E-estimated.txt" "%TEMP%\E-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem
%PROGRAM% "test-data\zero_determinant.txt" >"%TEMP%\zero_determinant-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\zero_determinant-estimated.txt" "%TEMP%\zero_determinant-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 5
rem
%PROGRAM% "test-data\degenerate.txt" >"%TEMP%\degenerate-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\degenerate-estimated.txt" "%TEMP%\degenerate-result.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1