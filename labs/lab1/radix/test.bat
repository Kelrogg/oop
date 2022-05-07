rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

echo Test 1
rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

echo Test 2
rem 
%PROGRAM% 36 10 0 >"%TEMP%\radixOld36.txt"
if NOT ERRORLEVEL 1 goto err

echo Test 3
rem 
%PROGRAM% 16 1 0 >"%TEMP%\radixNew1.txt"
if NOT ERRORLEVEL 1 goto err

echo Test 4
rem 
%PROGRAM% 16 10 "1F" >"%TEMP%\31.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\31.txt" "%TEMP%\31.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 5
rem 
%PROGRAM% 20 2 "-FF1" >"%TEMP%\-1100010011101.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\-1100010011101.txt" "%TEMP%\-1100010011101.txt">nul
if ERRORLEVEL 1 goto err

echo Test 6
rem 
%PROGRAM% 16 10 0 >"%TEMP%\0.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\0.txt" "%TEMP%\0.txt">nul
if ERRORLEVEL 1 goto err


echo Test 7
rem 
%PROGRAM% 16 10 1F >"%TEMP%\31.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\31.txt" "%TEMP%\31.txt">nul
if ERRORLEVEL 1 goto err

echo Test 8
rem 
%PROGRAM% 10 16 2147483647 >"%TEMP%\2147483647.txt"
if ERRORLEVEL 1 goto err
fc.exe "test-data\2147483647.txt" "%TEMP%\2147483647.txt">nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1