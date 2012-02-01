
{46. Написати програму, що організує обробку вихідних текстів .pas-програм
з метою приведення до верхнього регістра перших літер у ключових словах
(інші літери приводяться до нижнього регістра).
Інформацію про ключові слова див. у спец. літературі.
Ім'я оброблюваного файла указується в командному рядку одразу за виконавчим файлом.}

PROGRAM LABA_5_46;
USES WinCrt;
VAR
   F1:file;
   F2:file;
   Bufer: array [0..1000] of char;
BEGIN
   if ParamCount=0 then Write('NO parametrs');

   assign(f1,ParamStr(1));
   if IOResult<>0 then
      begin
        Write('file',ParamStr(1),'is not open');
        Halt;
      end;
   Close(f1);
END.


{
USES WinCRT;
VAR
    f1:file;
    f2:file;
    s,buf:array[0..22000]of char ;
    l:string[4];
    kk,res,z:word;
    code:integer;
CONST
       i:word=0;
       j:longint=-1;
       c:byte=1;
BEGIN
       if ParamCount<>3 then
         begin
           write('parameters is not correct');
           halt;
         end;
      assign(f1,ParamStr(1));
      {$i-};
{      reset(f1,1);
      {$i+};
 {     if IOResult<>0 then
         begin
           write('file',ParamStr(1),'is not open');
           halt;
         end;
       assign(f2,ParamStr(2));
       rewrite(f2,1);
       l:=paramstr(3);
       val(l,kk,code);
       inc(kk);
       if code<>0 then
                       begin
                             write('file',ParamStr(3),'is not correct');
                             halt;
                       end;
         repeat
               blockread(f1,buf,sizeof(buf),res);
               if res>0 then
               begin
               for i:=0 to res do
               begin
                       inc(j);
                      if (j=(c*kk)-1) then
                      begin
                           inc(c);
                           s[j]:=#13;
                           inc(j);
                      end;

                      if(buf[i]=#9)then
                      begin
                        if c>1 then
                        begin
                            repeat
                                  s[j]:=' '  ;
                                  inc(j);
                            until j=(c*kk)-1;
                            s[j]:=#13;
                            inc(j);
                            inc(c);
                        end;
                         for z:=1 to 4 do
                           begin
                                 s[j]:=' ';
                                 inc(j);
                           end;
                           dec(j);
                           continue;
                      end;
                      if (buf[i]<>#13)and(buf[i]<>#10)and(buf[i]<>'-') then   s[j]:=buf[i]
                                                         else
                                                     begin
                                                          dec(j);
                                                          CONTINUE;
                                                     end;
               end;
                  s[j]:=#13;
                 blockwrite(f2,s,j,res);
             end;
         until res=0;
       close(f1);
       close(f2);
end.
}