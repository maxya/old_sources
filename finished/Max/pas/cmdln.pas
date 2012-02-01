{Sample code for the Val procedure.}
uses strings, wincrt;
var I, Code: Integer;
begin
{ Get text from command line }
  Val(ParamStr(1), I, Code);
  { Error during cnversion to integer? }
  if code <> 0 then
    Writeln('Error at positon: ', Code)
  else
    Writeln('Value = ', I);
end.