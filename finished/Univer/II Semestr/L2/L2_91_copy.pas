PROGRAM LABA_2_3;
USES WINCRT;
CONST
   max=100;
   x:integer=0;
   y:integer=0;
TYPE
   Masiv = Array [1..max,1..max] of integer;
VAR
   M1:Masiv;
   M2:Masiv;
   i,j,c,temp,xnow,ynow:integer;
BEGIN
   ClrScr;
   WriteLn('Enter size of the Matrix ');
   Write('i= ');ReadLn(xnow);
   Write('j= ');ReadLn(ynow);
{******************************************************
*******************************************************}
{Vvod 1go massiva }
   WriteLn('Enter Matrix I');
   for y:=1 to ynow do
     begin
          for x:=1 to xnow do
              begin
                 Write('M1[',x,' ',y,'] ');
                 Read(M1[x,y]);
              end;
          x:=0;
     end;
{*******************************************************
********************************************************}
{Sortirovka 1go massiva}
  repeat
     c:=0;
     for y:=1 to ynow do
         begin
              for x:=1 to xnow do
                  begin
                       if M1[x,y]<M1[x+1,y] then
                          begin
                               temp:=M1[x,y];
                               M1[x,y]:=M1[x+1,y];
                               M1[x+1,y]:=temp;
                               Inc(c);
                          end;
                 end;
              x:=0;
           end;
  until c=0;
{*****************************************************
******************************************************}
{Vvod Massiva #2, bez sortirovki}
     WriteLn('');
     WriteLn('Enter Matrix II (Without Sorting..)');
     for y:=1 to ynow do
         begin
           for x:=1 to xnow do
               begin
                 Write('M2[',x,'][',y,'] ');
                 Read(M2[x,y]);
               end;
           x:=0;
        end;
{Zapis massiva M2 v massiv M1 s sortirovkoy}
 for j:=1 to ynow do
  begin
    for i:=1 to xnow do
      begin
       for y:=1 to ynow do
           begin
                for x:=1 to xnow do
                    begin
                         if M1[i,j]>M2[x,y] then
                            begin
                              Write('.');
                              for c:=i to xnow do
                                  begin
                                  Write('+');
                                  end;

                            end;
                    end;
           end;
      end;
  end;
 {Вывод отсортированого массива}
   for j:=1 to ynow do
     begin
       for i:=1 to ynow do
         begin
           WriteLn('M: ');
           Write(M1[i,j]);
         end;
     end;
END.