{Після введення з клавіатури довільного одновимірного масиву цілих чисел
(у межах знакового цілого типу) знайти і вивести на екран довжину самої довгої
послідовності однакових чисел, що йдуть підряд, і це число.Введення кожного числа
завершується натисканням <Enter>, введення припиняється введенням числа 0.}

PROGRAM LABAII;
USES WINCRT,STRINGS;
CONST
     long=1000;
     i:integer=0;
     j:integer=0;
     ipr:integer=0;
     num:integer=0;
     c:integer=0;
     cmax:integer=0;
TYPE
    Mas=Array [1..long] of integer;
VAR
   M1,M2:Mas;
   BEGIN
     StrCopy(WindowTitle,'ЛР №2 Задача №39 Выполнил: Максим Горбанёв ' );
     ClrScr;
     WriteLn('Введите цифры в массив: ');
     repeat
	Inc(i);
	Write('M[',i,']: ');
	Read(M1[i]);
	if M1[i]=ipr then
	   begin
		inc(c);
		if c>cmax then
		   begin
			cmax:=c;
			num:=ipr;
		   end;
	   end
	else c:=0;
	ipr:=M1[i];
     until (M1[i])=0;
     WriteLn('');
     WriteLn('Наиболее повторяемая цифра ',num);
     WriteLn('Цифра ',num, ' повторяется ',cmax+1,' раз(a).');
END.
