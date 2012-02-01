program Laba_3_5;
USES WINCRT;
CONST
     i:integer=0;
VAR
     Lat,n:integer;
     Ryad:string;
BEGIN
     Write('Enter String: ');
     repeat
       Inc(i);
       ryad[i]:=ReadKey;
       Write (Ryad[i]);
     until (Ryad[i] = '0') or (Ryad[i] = #13);
     for n:=1 to i do
       if (UpCase(Ryad[n])) in ['A'..'Z'] then Inc(Lat);
     WriteLn;
     Write('Latin: ',Lat);
END.
