
{46. �������� ��������, �� ������� ������� �������� ������ .pas-�������
� ����� ���������� �� ��������� ������� ������ ���� � �������� ������
(���� ����� ����������� �� �������� �������).
���������� ��� ������ ����� ���. � ����. ��������.
��'� ������������� ����� ��������� � ���������� ����� ������ �� ���������� ������.}

PROGRAM LABA_5_46;
USES WinCrt,Strings;
VAR
   F1:text;
   F2:text;
   Bufer: array [0..1000] of char;
BEGIN
   if ParamCount=0 then
      begin
       Write('��������� �� �������');
       Halt;
      end;
   assign(f1,ParamStr(1));
   if IOResult<>0 then
      begin
        Write('����',ParamStr(1),'�� ������');
        Halt;
      end
      else
          Write('���� ������');
   Reset(F1);
   Close(F1);
END.