
{46. Написати програму, що організує обробку вихідних текстів .pas-програм
з метою приведення до верхнього регістра перших літер у ключових словах
(інші літери приводяться до нижнього регістра).
Інформацію про ключові слова див. у спец. літературі.
Ім'я оброблюваного файла указується в командному рядку одразу за виконавчим файлом.}

PROGRAM LABA_5_46;
USES WinCrt,Strings;
VAR
   F1:text;
   F2:text;
   Bufer: array [0..1000] of char;
BEGIN
   if ParamCount=0 then
      begin
       Write('Параметры не Введены');
       Halt;
      end;
   assign(f1,ParamStr(1));
   if IOResult<>0 then
      begin
        Write('файл',ParamStr(1),'не открыт');
        Halt;
      end
      else
          Write('Файл открыт');
   Reset(F1);
   Close(F1);
END.