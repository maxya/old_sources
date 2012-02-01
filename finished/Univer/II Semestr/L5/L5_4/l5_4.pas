{Написати програму-оброблювач текстових файлів, що створює текстовий файл,
який складається лише зі слів заданого діапазоном розміру (букв).
Розділових зна-ків, пропусків, знаків табуляції та інших керуючих символів не торкатися.
Файл-джерело, файл-приймач, а також умову (діапазон розміру слів)
зазначити в коман-дному рядку слідом за виконавчим файлом.
 }
PROGRAM LABA_5_4;
USES CRT,strings;
CONST
WLen:integer=0;
VAR
   f1:text;
   f2:text;
   Str:string;
   StrOK:string;
   StrLen,i:integer;
   TrueWLen,Code:integer;
   TWL:String;
BEGIN
  if ParamCount<>3 then
     begin
       ClrScr;
       Write('Неверно введены параметры');
       Halt;
     end;
  TWL:=ParamStr(3);
  Val(TWL,TrueWLen,Code);
  If (Code<>0) then
     begin
     ClrScr;
     Write('Неверно введены параметры');
     Halt;
     end;
  {$I-}
  Assign(f1,ParamStr(1));
  Reset(f1);
  {$I+}
  if IOResult<>0 then
     begin
       WriteLn('Ошибка открытия файла!');
       Halt(1);
     end;
  {$I-}
  Assign(f2,ParamStr(2));
  Append(f2);
  {$I+}
  if IOResult<>0 then
     begin
       WriteLn('Ошибка открытия файла!');
       Halt(1);
     end;
  while not eof(f1) do
        begin
          ReadLn(f1,Str);
          StrLen:=length(Str);
          for i:=1 to StrLen do
              begin
                   if (UpCase(Str[i])) in ['A'..'Z'] then
                       begin
                         Inc(WLen);
                         StrOK:=StrOK+Str[i];
                       end
                   else
                       begin
                       if (WLen=TrueWLen) then Write(f2,' ',StrOK);
                       Wlen:=0;
                       StrOK:='';
                       end;
              end;
        end;
  Close(f1);
  Close(f2);


END.