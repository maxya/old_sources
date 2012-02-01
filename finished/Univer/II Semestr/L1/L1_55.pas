PROGRAM LABA_1_55;
USES CRT;
CONST
i:integer=6;
np:integer=0;
nm:integer=0;
VAR
a,a1,c,n:integer;
BEGIN
     ClrScr;
     WriteLn('Enter digits a..an: ');
     for c:=1 to i do
     begin
          Write('A',c,':');
          ReadLn(a);
          if c=1 then a1:=a;
          n:=a*a1;
          if (n>0) then
             begin
                  if a>a1 then WriteLn('Found two digits with sign "+", past ',np);
                  a1:=a;
                  np:=np+1;
             end
          else
              begin
                   if Abs(a)>Abs(a1) then WriteLn('Found two digits with sign "-", past ',nm);
                   a1:=a;
                   nm:=nm+1;
              end;
     end;
END.