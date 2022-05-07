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
%PROGRAM% "test-data\labyrinth-1.txt" >"%TEMP%\labyrinth-1-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\labyrinth-1-estimated.txt" "%TEMP%\labyrinth-1-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 3
rem
%PROGRAM% "test-data\labyrinth-2.txt" >"%TEMP%\labyrinth-2-result.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\labyrinth-2-estimated.txt" "%TEMP%\labyrinth-2-result.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1