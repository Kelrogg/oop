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
%PROGRAM% "test-data\empty.txt" "%TEMP%\empty.txt" a b
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty.txt" "test-data\empty.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 3
rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% "test-data\fox.txt" "%TEMP%\fox.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\fox.txt" "test-data\fox-replace-dog-with-cat.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1