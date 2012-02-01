PROGRAM Laba_1_23;
USES WINCRT;
VAR
   m,n,r,y2:word;

BEGIN
     ClrScr;
     WriteLn ('Enter two digits to find NOD for them');
     Write ('M= ');
     ReadLn(m);
     Write ('N= ');
     ReadLn(n);

     r:=m-n;
     y2:=n;
     while m<>n do
           if m>n then m:=m-n
                  else n:=n-m;
     while y2<>r do
           if y2>n then y2:=y2-r
                   else r:=r-y2;

     if m=y2 then Write('Found NOD = ',m)
             else Write ('Nod not found');
     ReadKey;
END.
