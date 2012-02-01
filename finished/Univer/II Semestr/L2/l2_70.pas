{Після введення з клавіатури розмірності двохвимірної матриці
(кількість рядків і стовпчиків) цілих чисел (знакового цілого типу),
а також введення її елементів вивести на екран відсортовані в порядку убування мінімальні
елементи кожного стовпчика.}
PROGRAM LABA_2_70;
USES WinCRT;
CONST
    max=100;
    x:integer=0;
    y:integer=0;
TYPE
    Masiv = Array [1..max,1..max] of integer;
    Mas = Array [1..max] of integer;
VAR
    M:Masiv;  M1:Mas;
    min,temp,c,xsize,ysize:integer;
BEGIN
     ClrScr;
     WriteLn('Введите Размер Матрицы ');
     Write('i= ');ReadLn(xsize);
     Write('j= ');ReadLn(ysize);
     repeat
           Inc(y);
           repeat
                 Inc(x);
                 Write('M[',x,'][',y,'] ');
                 Read(M[x,y]);
           until x=xsize;
           x:=0;
     until y=ysize;
     ClrScr;
     WriteLn(' Введённая Матрица: ');
     for y:=1 to ysize do
        begin
             WriteLn('');
             for c:=1 to xsize do
                 Write(' ',M[c,y]);
        end;
     WriteLn('');
     repeat
       c:=0;
       for y:=1 to ysize do
           for x:=1 to xsize do
               if M[x,y]>M[x+1,y] then
                  begin
                       temp:=M[x,y];
                       M[x,y]:=M[x+1,y];
                       M[x+1,y]:=temp;
                       Inc(c);
                  end;
     until c=0;
     for y:=1 to ysize do
             M1[y]:= M[2,y];
     repeat
       c:=0;
       for y:=1 to ysize do
           begin
             if M1[y]<M1[y+1] then
                begin
                  temp:=M1[y];
                  M1[y]:=M1[y+1];
                  M1[y+1]:=temp;
                  Inc(c);
                end;
           end;
     until c=0;
     WriteLn('Наименьшие элементы каждой строчки, выведенные по убыванию: ');
     for c:=1 to ysize do
         begin
           Write(' ',M1[c]);
         end;
END.