program ScanKey;
uses Crt;



var
   key:Char;


begin

Writeln('Press any Key...');
key:=ReadKey;
Writeln(' You pressed ', key, ', its ASCII value is ', Ord(key), '.');
END.