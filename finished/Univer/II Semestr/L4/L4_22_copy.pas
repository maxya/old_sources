PROGRAM LABA_IV_22;
USES WINCRT,STRINGS;
TYPE
   Book=record
     Author:string[30];
     Name:string[30];
     Numpr:string[30];
     Shifr:string[30];
   end;
   Catalog = array[1..200] of Book;
   M1 = array [1..30] of book;
CONST
     poz:integer=5;
VAR
   temp,st,num,lastnum,n,i:integer;
   ToFind,keypr:string;
   Cat:Catalog;
   CTemp:M1;
Procedure menu(i:integer);
 begin
     GotoXY(1,12);
   case i of
      1:repeat
          with cat[lastnum] do
               begin
                 GotoXY(30,poz-3);
                 Write('���� ������ � ����');
                 GotoXY(30,poz);
                 Write('����� ');
                 ReadLn(Author);Inc(poz);GotoXy(30,poz);
                 Write('�������� ����� ');
                 ReadLn(name);Inc(poz);GotoXy(30,poz);
                 Write('���������� ');
                 repeat
                     ReadLn(numpr);
                     Val(numpr,i, temp);
                     if temp <> 0 then
                        begin
                        Gotoxy(41,poz);
                        ClrEol;
                        end;
                 until temp=0;
                 GotoXy(41,poz);
                 Write(numpr);
                 Inc(poz);GotoXy(30,poz);
                 Write('���� ����� ');
                 repeat
                     ReadLn(shifr);
                     Val(shifr, i, temp);
                     if temp <> 0 then
                        begin
                        Gotoxy(41,poz);
                        ClrEol;
                        end;
                 until temp=0;
                 Inc(poz);GotoXy(20,poz+2);
                 Inc(lastnum);
                 Write('���������� ? (���� �� - ENTER  ���� ��� - ESC)');
                 repeat
                   keypr:=ReadKey;
                 until (keypr=#13) or (keypr=#27);
                 poz:=5;
                 ClrScr;
               end;
        until (keypr<>#13) or (keypr=#27);
      2:repeat
             with cat[num] do
                   begin
                    ClrScr;
                    GotoXY(30,poz-1);
                    Write('������ �� ���� ');Inc(poz);GotoXy(30,poz);
                    Write(Author);Inc(poz);GotoXy(30,poz);
                    Write(name);Inc(poz);GotoXy(30,poz);
                    Write(numpr);Inc(poz);GotoXy(30,poz);
                    Write(shifr);Inc(poz);GotoXy(30,poz);
                    keypr:=ReadKey;
                    poz:=5;
                    ClrScr;
                   end;
             if keypr='1' then Dec(num);
             if keypr='2' then Inc(num);
             if keypr=#27 then num:=1;
             if (num=lastnum) then Dec(num);
             if (num<1) then Inc(num);
        until (keypr=#27) or (num=lastnum);
      3:repeat
             with cat[num] do
               begin
                  ClrScr;
                  GotoXY(30,poz-1);
                  Write('�������� ������ ��� ��������������');Inc(poz);GotoXy(30,poz);
                  Write(Author);Inc(poz);GotoXy(30,poz);
                  Write(name);Inc(poz);GotoXy(30,poz);
                  Write(numpr);Inc(poz);GotoXy(30,poz);
                  Write(shifr);Inc(poz);GotoXy(30,poz);
                  keypr:=ReadKey;
                  poz:=5;
                  ClrScr;
               end;
             if (keypr='1') then Dec(num);
             if (keypr='2') then Inc(num);
             if (keypr=#27) then num:=1;
             if (num=lastnum) then Dec(num);
             if (num<1) then Inc(num);
             if (keypr=#13) then
                with cat[num] do
                begin
                     GotoXY(30,poz-1);
                     Write('������� ����� ������');GotoXY(30,poz);
                     Write('����� ');
                     ReadLn(Author);Inc(poz);GotoXy(30,poz);
                     Write('�������� ����� ');
                     ReadLn(name);Inc(poz);GotoXy(30,poz);
                     Write('���������� ');
                     repeat
                           ReadLn(numpr);
                           Val(numpr, i, temp);
                           if temp <> 0 then
                           begin
                             Gotoxy(41,poz);
                             ClrEol;
                           end;
                     until temp=0;
                     Inc(poz);GotoXy(30,poz);
                     Write('���� ����� ');
                       repeat
                             ReadLn(shifr);
                             Val(shifr, i, temp);
                             if temp <> 0 then
                             begin
                               Gotoxy(41,poz);
                               ClrEol;
                             end;
                       until temp=0;
                     Inc(poz);GotoXy(20,poz+2);
                     poz:=5;
                end;
        until (keypr=#27) or (num=lastnum);
      4:repeat
             with cat[num] do
               begin
                  ClrScr;
                  GotoXY(30,poz-1);
                  Write('�������� ������ ��� ��������');Inc(poz);GotoXy(30,poz);
                  Write('Tip: ��� �������� ������� Enter ');Inc(poz);GotoXy(30,poz);
                  Write(Author);Inc(poz);GotoXy(30,poz);
                  Write(name);Inc(poz);GotoXy(30,poz);
                  Write(numpr);Inc(poz);GotoXy(30,poz);
                  Write(shifr);Inc(poz);GotoXy(30,poz);
                  keypr:=ReadKey;
                  poz:=5;
                  ClrScr;
               end;
             if keypr='1' then Dec(num);
             if keypr='2' then Inc(num);
             if keypr=#27 then num:=1;
             if (num=lastnum) then Dec(num);
             if (num<1) then Inc(num);
             if (keypr=#13) then
                with cat[num] do
                begin
                     Author:='';
                     Name:='';
                     Numpr:='';
                     Shifr:='';
                end;
        until (keypr=#27) or (num=lastnum);
      5:repeat
          GotoXY(10,6);
          Write('�������� �����Ĩ� � ������ ���� ������ ���������� y/n :) ? ');
             keypr:=ReadKey;
             if (keypr=#13) then
                     For i:=1 to 200 do
                         with cat[i] do
                              begin
                                Author:='';
                                Name:='';
                                Numpr:='';
                                Shifr:='';
                              end;
             lastnum:=1;
             ClrScr;
        until (keypr=#13) or (keypr=#27);
      6:begin
             GotoXY(25,3);
             Write('����� ������ � ����');
             GotoXY(20,5); Write('������� ������ ��� ������: ');
             GotoXY (25,6);Read(ToFind);
                    temp:=1;
                    for i:=1 to lastnum do
                      begin
                        if (ToFind = cat[i].author) then
                          CTemp[temp].author:=cat[i].author;
                          with cat[i] do
                            begin
                              writeLn('�����: ',Author);
                              WriteLn('�����: ',Name);
                            end;
                        if (ToFind = cat[i].Name) then
                          Ctemp[temp].Name:=cat[i].Name;
                      end;
                      Write('���������� �����? ');
                      ReadLn(keypr);
                      if keypr <> #13 then
                         begin
                         end
                         else
                          Write('UPS');
                      Readkey;
                      ClrScr;
        end;

   end
 end;

{**********************************************************
***********************************************************
***********************************************************}
BEGIN
  StrCopy(WindowTitle,'��� (������������ ������ �4 - �������� ������� )');
  ClrScr;
  ScreenSize.X:=80;
  ScreenSize.Y:=25;
  GotoXY(35,2); Write('���� ������ ');
  lastnum:=1;
  repeat
    num:=1;
    GotoXY(27,2); Write('������������ ���� ������');
    Gotoxy(25,4);
    Write('1. ������� ������ � ����');Gotoxy(25,5);
    Write('2. ����������� ����');Gotoxy(25,6);
    Write('3. ������������� ����');Gotoxy(25,7);
    Write('4. ���������� ������ �� ����');Gotoxy(25,8);
    Write('5. ���������� ��� ����');Gotoxy(25,9);
    Write('6. ����� � ����');Gotoxy(25,11);
    Write('������� 0 ��� ������');Gotoxy(25,13);
    ReadLn(i);
    ClrScr;
    menu(i);
  until i=0;
END.
