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
%PROGRAM% "test-data\no-search-string.txt" "%TEMP%\no-search-string.txt" bird cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\no-search-string.txt" "test-data\no-search-string-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test 4
rem ��� ������� � ����������� ����������� ��������� ������� ��� ��������
%PROGRAM% "test-data\search-string-exists.txt" "%TEMP%\search-string-exists.txt" dog cat
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\search-string-exists.txt" "test-data\search-string-exists-result.txt" >nul
if ERRORLEVEL 1 goto err

echo Test5
rem ������ � 4 ����������� (������ replacementString)
%PROGRAM% "test-data\empty-replacementString.txt" "%TEMP%\empty-replacementString.txt" dog
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty-replacementString.txt" "test-data\empty-replacementString-result.txt" >nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1