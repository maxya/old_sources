{Дані відсортований (М1) і не відсортований (М2) одновимірні масиви цілих чисел.
Одержати масив М3, шляхом упорядкованого розміщення членів М2 у М1.}
PROGRAM LABA_2_91;
USES WINCRT;
CONST
   max=100;
   x:integer=0;
   y:integer=0;
TYPE
   Masiv = Array [1..max] of integer;
VAR
   M1:Masiv;
   M2:Masiv;
   M3:Masiv;
   i,j,c,temp:integer;
   size, newsize:integer;
BEGIN
   ClrScr;
    WriteLn('Enter Matrix I');
    size:=0;
    repeat
      Inc(size);
      Write('M1[',size,'] ');
      Read(M1[size]);
    until M1[size]=0;
   for i:=1 to size-1 do
	for j:=i+1 to size do
		if (M1[j] < M1[i]) then
		begin
			temp:=M1[i];
			M1[i]:=M1[j];
			M1[j]:=temp;
		end;
   WriteLn('');
   WriteLn('Enter Matrix II (Without Sorting..)');
   for i:=1 to size-1 do
	   begin
	     Write('M2[',i,'] ');
	     Read(M2[i]);
	  end;

    newsize := size;
    for i:=1 to size do
	begin
	    j := 1;
	    while (j <= newsize) do
		begin
		    if (M2[i] <= M1[j]) then
		    begin
			Inc (newsize);
			for temp:= newsize downto j+1 do
				M1[temp]:= M1[temp-1];
			M1[j]:= M2[i];
			break;
		    end;
		    Inc (j);
		end;
	end;
    ClrScr;
    WriteLn('Sorted: ');
    for i:=3 to newsize do
	begin

	    Write('M[',i-2,']: ');
	    WriteLn(M1[i]);
	end;
END.
