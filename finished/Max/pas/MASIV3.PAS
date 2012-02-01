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
	Writeln('Введите количество элементов массива');
	Readln(n);
        Writeln('n=',n);
        Writeln('Введите ',n,' значения массива A');
	    for i:=1 to n do
        begin
         Writeln('Введите ',i, '-й дробный элемент массива');
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
                  Writeln( 'Сумма равна ',S:8:2,'':2,
                          ' Среднеквадратичное значение дробных чисел массива'
                         ,average:8:2)
                end
             else
               Writeln('В массиве нет дробных чисел');
            Repeat until keypressed
 END.












	  end;
    end;
 if l>0 then   w:=(s*s)/(l*l);
    Writeln(w:8:3,'Среднеквадратичное значение дробных чисел массива');
  Repeat Until Keypressed
End.
