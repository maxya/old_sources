(*

        This program computes a solution to game #5 on a Merlin!

*)

{$M 16300,0,655360}
program ai_1;
uses
  crt,mouse,graph;

procedure display(config_num:integer);
var x,y:integer;
begin
  y:=0;
  for x:=1 to 9 do begin
    y:=y+1;
    if (config_num and 1)=1
      then write('*  ')
      else write('   ');
    if y=3 then begin
      writeln;
      y:=0
      end;
    config_num:=config_num shr 1
    end
  end;

function config_after(config_num,move_num:integer):integer;
begin
  case move_num of
    1: config_after:=config_num xor 27;    {  1  2   4    }
    2: config_after:=config_num xor 7;     {  8  16  32   }
    3: config_after:=config_num xor 54;    {  64 128 256  }
    4: config_after:=config_num xor 73;
    5: config_after:=config_num xor 186;
    6: config_after:=config_num xor 292;
    7: config_after:=config_num xor 216;   (*** 495 ***)
    8: config_after:=config_num xor 448;
    9: config_after:=config_num xor 432
    end
  end;

procedure human_plays;
var move_num,config_num : integer;
begin
  write('Initial Config # '); readln(config_num);
  display(config_num);
  while true do begin
    write('Move # '); readln(move_num);
    config_num:=config_after(config_num,move_num);
    writeln('Generates config ',config_num);
    display(config_num)
    end
  end;
type c_or_p = (con,poi);
     chain9pointer = ^chain9;
     config_or_pointer = record
                           kind : c_or_p;
                           config : word;
                           point  : chain9pointer
                           end;
     c_or_p9 = array[1..9] of config_or_pointer;
     chain9 = record
                nextchain : chain9pointer;
                data : c_or_p9
                end;

var  initial_move : c_or_p9;

procedure create_initial_chain(config_num:integer);
var x:integer;
begin
  for x:=1 to 9 do begin
    initial_move[x].kind:=con;
    initial_move[x].config:=config_after(config_num,x);
    if initial_move[x].config=495 then begin
      writeln('I got it... just press ',x);
      halt
      end
    end
  end;

function is_in(a_chain : c_or_p9):boolean;
var x:integer;
begin
  is_in:=false;
  for x:=1 to 9 do
    if a_chain[x].kind=poi
      then if is_in(a_chain[x].point^.data)
        then begin
               writeln('Middle move ',x);
               is_in:=true;
               exit
               end
        else
      else if a_chain[x].config=495 then begin
        writeln('Final move ',x);
        is_in:=true;
        exit
        end
  end;


procedure trace_out;
var x : integer;
begin
  for x:=1 to 9 do
    if is_in(initial_move[x].point^.data) then begin
      writeln('First move ',x);
      halt
      end;
  writeln('Done tracing');
  halt
  end;


procedure make_a_chain(thechain:chain9pointer;initial_config:integer);
var x: integer;
begin
    for x:=1 to 9 do begin
      thechain^.data[x].kind:=con;
      thechain^.data[x].config:=config_after(initial_config,x);
      if thechain^.data[x].config=495 then trace_out
      end
    end;

var chain_levelptr : array[1..7] of chain9pointer;

procedure make_second_chain(var initial_move : c_or_p9;
                                       level : integer;
                                  var engineptr : chain9pointer;
                                  var cabooseptr : chain9pointer);
var y : integer;
    nextchain9,oldchain : chain9pointer;

begin
  oldchain:=nil;

  for y:=1 to 9 do begin
    new(nextchain9);
    gotoxy(1,1); writeln(memavail,' ');
    nextchain9^.nextchain:=nil;
    if oldchain<>nil
      then oldchain^.nextchain:=nextchain9
      else engineptr:=nextchain9;
    oldchain:=nextchain9;

    initial_move[y].kind:=poi;
    initial_move[y].point:=nextchain9;
    cabooseptr:=nextchain9;

    make_a_chain(nextchain9,initial_move[y].config)


    end
  end;

procedure make_third_chain(curr_chain : chain9pointer;level:integer);
var engineptr,cabooseptr,oldcabooseptr : chain9pointer;
begin
  while curr_chain<>nil do begin
    make_second_chain(curr_chain^.data,level,engineptr,cabooseptr);
    if chain_levelptr[level]=nil
      then chain_levelptr[level]:=engineptr
      else oldcabooseptr^.nextchain:=engineptr;
    oldcabooseptr:=cabooseptr;
    curr_chain:=curr_chain^.nextchain
    end
  end;

 { here is a mouse_area array used by calls to mouse_area  }
 { You should make the first index as small as needed, but }
 { the function can take up to 100. Note that the last     }
 { entry is all zeros }
const
  ma : array[1..10,1..4] of word =
         ( (30,130,30,60) , (160,260,30,60) , (290,390,30,60) ,
           (30,130,80,110) , (160,260,80,110) , (290,390,80,110) ,
           (30,130,130,160) , (160,260,130,160) , (290,390,130,160) ,
           (0,0,0,0) );

procedure read_config(var config_num : integer);
var num_buttons : word;
    grDriver,
    grMode,
    ErrCode     : Integer;
    button,x,y : word;
label finish;
begin
  config_num:=0;
  if not mouseparams(num_buttons) then begin    { call first to reset }
     writeln('Need a mouse for this.');         { the mouse }
     halt
     end;
  grDriver := Detect;
  InitGraph(grDriver,grMode,'c:\program\turbopas\bgi');
  ErrCode := GraphResult;
  if ErrCode = grOk then
    begin
      for x:= 1 to 9 do rectangle(ma[x,1],ma[x,3],ma[x,2],ma[x,4]);
      settextstyle(defaultfont,vertdir,1);
      outtextxy(640,20,'Click here when done');

      set_speed2(100);       { sets the double speed to 100 cps }
      mouse_cursor(true);    { displays the mouse cursor }
      set_mouse_cursor(5,2,hand); { sets the cursor to a hand & hot spots }
      while true do begin
        while mousebutton=0 do;   { mousebutton = 0 if not pressing anything }
        if mousex>630 then goto finish; { mousex = x location }
        x:=mouse_area(ma);              { returns 1 - 9 or 0 if not in any }
        if x>0 then begin
          config_num:=config_num or (1 shl (x-1));
          mouse_cursor(false);          { shuts off cursor before drawing over it}
          bar(ma[x,1],ma[x,3],ma[x,2],ma[x,4]);
          mouse_cursor(true)            { turns it back on }
          end
        end
      end
    else
      WriteLn('Graphics error:',
              GraphErrorMsg(ErrCode));
      halt;
finish:
    closegraph;
    end;

var
    x,move_num,
    config_num : integer;
    garbage : chain9pointer;

begin                          (* 499 - 2 moves , 453 - 3 moves *)
  read_config(config_num);
clrscr;
{  if config_num=0 then human_plays;
}
  for x:=1 to 7 do chain_levelptr[x]:=nil;
  writeln('Move 1');
  create_initial_chain(config_num);
  writeln('Move 2');
  make_second_chain(initial_move,1,chain_levelptr[1],garbage);

  for x:=1 to 90 do begin
    writeln('Move ',x+2);
    make_third_chain(chain_levelptr[x],x+1)
    end;


  end.


