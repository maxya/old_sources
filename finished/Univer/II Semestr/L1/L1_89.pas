USES WINCRT;
CONST
     f:integer=1;
     m:integer=0;
VAR
   n,x,i:integer;
BEGIN
     ClrScr;
     write('Enter digit N ');
     ReadLn(n);
     x:=n;
     repeat
           i:=x;
           x:=0;
           While i>=2 do
                 begin
                      i:=i-2;
                      x:=x+1;
                 end;
           m:=m+(i*f);
           f:=f*10;
     until x=0;
     Write('Binary number is ',m);
     ReadKey;
END.
