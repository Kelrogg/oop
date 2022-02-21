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
%PROGRAM% crypt "test-data\empty.txt" "%TEMP%\empty.txt" 256
if NOT ERRORLEVEL 1 goto err

echo Test 3
rem проверяем шифровку/дешифровку числа 5 в 9
%PROGRAM% "crypt" "test-data\5.txt" "%TEMP%\5-encrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" "%TEMP%\5-encrypt.txt" "%TEMP%\5-decrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "test-data\5.txt" "%TEMP%\5-decrypt.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem проверяем шифровку/дешифровку числа 5 в 9
%PROGRAM% "crypt" "test-data\422.txt" "%TEMP%\422-encrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" "%TEMP%\422-encrypt.txt" "%TEMP%\422-decrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "test-data\422.txt" "%TEMP%\422-decrypt.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 5
rem проверяем шифровку/дешифровку на картинке
%PROGRAM% "crypt" "test-data\horder.jpg" "%TEMP%\horder-encrypt.jpg" 12
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" "%TEMP%\horder-encrypt.jpg" "%TEMP%\horder-decrypt.jpg" 12
if ERRORLEVEL 1 goto err
fc.exe "test-data\horder.jpg" "%TEMP%\horder-decrypt.jpg" >nul
if ERRORLEVEL 1 goto err



echo OK
exit 0

:err
echo Program testing failed
exit 1