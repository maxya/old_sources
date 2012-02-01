{3.62.Після введення з клавіатури довільного рядка визначити його належність
 до того або іншого алфавіту. Символи, які не входять в алфавіти, не аналізувати.
 Мож-ливий третій варіант відповіді.
}
PROGRAM Laba_3_62;
USES WINCRT;
CONST
     i:integer=0;
     Lat:integer=1;
VAR
     n:integer;
     Ryad:string;
Const
     latletter=['A'..'Z'];
BEGIN
     Write('Enter String: ');
     repeat
       Inc(i);
       ryad[i]:=ReadKey;
       ryad:=Concat(ryad,ryad[i]);
       Write (Ryad[i]);
     until (Ryad[i] = #13);
     for n:=1 to i do
       if (UpCase(Ryad[n])) in latletter then Inc(Lat);
     WriteLn;
     if i=Lat then Write('Latin Simbols')
	else if (Lat=1) then Write('Rus Simbols')
		else Write('RUS and Lat simbols');
END.
