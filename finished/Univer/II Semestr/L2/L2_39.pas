{ϳ��� �������� � ��������� ��������� ������������ ������ ����� �����
(� ����� ��������� ������ ����) ������ � ������� �� ����� ������� ���� �����
����������� ��������� �����, �� ����� �����, � �� �����.�������� ������� �����
����������� ����������� <Enter>, �������� ������������ ��������� ����� 0.}

PROGRAM LABAII;
USES WINCRT,STRINGS;
CONST
     long=1000;
     i:integer=0;
     j:integer=0;
     ipr:integer=0;
     num:integer=0;
     c:integer=0;
     cmax:integer=0;
TYPE
    Mas=Array [1..long] of integer;
VAR
   M1,M2:Mas;
   BEGIN
     StrCopy(WindowTitle,'�� �2 ������ �39 ��������: ������ ������� ' );
     ClrScr;
     WriteLn('������� ����� � ������: ');
     repeat
	Inc(i);
	Write('M[',i,']: ');
	Read(M1[i]);
	if M1[i]=ipr then
	   begin
		inc(c);
		if c>cmax then
		   begin
			cmax:=c;
			num:=ipr;
		   end;
	   end
	else c:=0;
	ipr:=M1[i];
     until (M1[i])=0;
     WriteLn('');
     WriteLn('�������� ����������� ����� ',num);
     WriteLn('����� ',num, ' ����������� ',cmax+1,' ���(a).');
END.
