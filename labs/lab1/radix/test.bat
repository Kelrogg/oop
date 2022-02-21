rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

echo Test 1
rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

echo Test 2
rem проверяем замену строки пустого файла (копируем его во временную папку текущего пользователя)
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" a b
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 3
rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem При запуске с правильными параметрами ожидается нулевой код возврата
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-cat.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1