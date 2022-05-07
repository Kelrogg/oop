rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
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