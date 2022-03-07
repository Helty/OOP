rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

rem ������� �� ���������� 
%PROGRAM% > "%TEMP%\different_base.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\different_base.txt" test_files\different_base_result.txt
if ERRORLEVEL 1 goto err

rem ���� ������
%PROGRAM% 10 10 8313  > "%TEMP%\bases_are_the_same.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\bases_are_the_same.txt" test_files\bases_are_the_same_result.txt
if ERRORLEVEL 1 goto err

rem ������� ����������� 
%PROGRAM% 10 31 8371973193 > "%TEMP%\firstbase_10_second_n.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\firstbase_10_second_n.txt" test_files\firstbase_10_second_n_result.txt
if ERRORLEVEL 1 goto err

rem ������� 3x3
%PROGRAM% 6 10 4324315 > "%TEMP%\secondbase_10_first_n.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\secondbase_10_first_n.txt" test_files\secondbase_10_first_n_result.txt
if ERRORLEVEL 1 goto err

rem ������� 4x4
%PROGRAM% 15 10 0 > "%TEMP%\value_0.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\value_0.txt" test_files\value_0_result.txt
if ERRORLEVEL 1 goto err

rem ��� ��������� 
%PROGRAM% 5 10 -41321432 > "%TEMP%\negative_number.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\negative_number.txt" test_files\negative_number_result.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1