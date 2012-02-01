program NOD;
USES CRT;
VAR
   x,y:word;
procedure intro;
begin
ClrScr;
Write('Copyright(C) by Nightmare 2000');
Write('Programm NOD');
end;

BEGIN
intro;
ClrScr;
Write ('X= ');jhreadln(x);
Write ('Y= '); readln(y);

while x<> y do
      if x>y then x:=x-y
         else y:=y-x;
ClrScr;
Write('NOD = ',x);
ReadKey;
END.
