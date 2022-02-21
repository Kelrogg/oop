rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

echo Test 1
rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

echo Test 2
rem ��������� ������ ������ ������� ����� (�������� ��� �� ��������� ����� �������� ������������)
%PROGRAM% crypt "test-data\empty.txt" "%TEMP%\empty.txt" 256
if NOT ERRORLEVEL 1 goto err

echo Test 3
rem ��������� ��������/���������� ����� 5 � 9
%PROGRAM% "crypt" "test-data\5.txt" "%TEMP%\5-encrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" "%TEMP%\5-encrypt.txt" "%TEMP%\5-decrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "test-data\5.txt" "%TEMP%\5-decrypt.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem ��������� ��������/���������� ����� 5 � 9
%PROGRAM% "crypt" "test-data\422.txt" "%TEMP%\422-encrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
%PROGRAM% "decrypt" "%TEMP%\422-encrypt.txt" "%TEMP%\422-decrypt.txt" 12 >nul
if ERRORLEVEL 1 goto err
fc.exe "test-data\422.txt" "%TEMP%\422-decrypt.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 5
rem ��������� ��������/���������� �� ��������
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