Program masiv;
USES CRT;
VAR
  i,n:byte;
  s,average:real;
  A:array [1..100] of real;
  F:text;
 BEGIN
	clrscr;
	assign(f,'prn');
        rewrite(f);
	Writeln('������ ������⢮ ������⮢ ���ᨢ�');
	Readln(n);
        Writeln('n=',n);
        Writeln('������ ',n,' ���祭�� ���ᨢ� A');
	    for i:=1 to n do
        begin
         Writeln('������ ',i, '-� �஡�� ������� ���ᨢ�');
         Readln(A[i]);
        end;
	     s:=0;
             {n:=0;}
             for i:=1 to n do
               s:=s+A[i];
               n:=n+1;
             if n<>0 then
                begin
                  average:=s/n;
                  Writeln( '�㬬� ࠢ�� ',S:8:2,'':2,
                          ' �।��������筮� ���祭�� �஡��� �ᥫ ���ᨢ�'
                         ,average:8:2)
                end
             else
               Writeln('� ���ᨢ� ��� �஡��� �ᥫ');
            Repeat until keypressed
 END.












	  end;
    end;
 if l>0 then   w:=(s*s)/(l*l);
    Writeln(w:8:3,'�।��������筮� ���祭�� �஡��� �ᥫ ���ᨢ�');
  Repeat Until Keypressed
End.
