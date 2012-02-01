
unit mymouse;
interface
uses crt;
{ mouse pointer }
const
maxx:longint=800;
maxy:longint=600;

var
  mx,my,mb:word;

procedure setbunc(n:byte);
procedure initmouse;
{procedure restoremouse;}
procedure hidemouse;
procedure showmouse;
{procedure setpal(a,r,g,b:byte);}
{procedure putcartin (w:string);}
function getmkey:byte;
{procedure putbmp(x,y:longint;fname:string);}
{$F+}
implementation
const seta:array[0..15,0..9] of word=(
 (  0,999,999,999,999,999,999,999,999,999),
 (  0,15,  0,999,999,999,999,999,999,999),
 (  0,15,15,  0,999,999,999,999,999,999),
 (  0,15,15,15,  0,999,999,999,999,999),
 (  0,15,15,15,15,  0,999,999,999,999),
 (  0,15,15,15,15,15, 0,999,999,999),
 (  0,15,15,15,15,15,15,  0,999,999),
 (  0,15,15,15, 15,15,15,15,   0 ,999),
 (  0,15,15,15,15,15,15,15,15,0),
 (  0,15,15,15,15,15, 0,999,999,999),
 (  0,15, 0, 0,15,15,15, 0,999,999),
 (  999,999,999, 0, 0,15,15,15, 0,999),
 (  999,999,999,999, 0,15,15,15, 0,999),
 (  999,999,999,999,999, 0,15,15,15,0),
 (  999,999,999,999,999, 0,15,15,15,0),
 (  999,999,999,999,999,999,999,999,999,999)
 );
var mode,co,n,m,xmax,ymax,mxmax:word;
    c:char;
    flag:boolean;
    buf:array[0..255] of byte;
    sos,ooo:word;
    bank:byte;
    mask:array[0..15,0..9] of byte;  { mask of mouse pointer }
    oldseg,oldofs,oldmask:word;
    newseg,newofs,newmask:word;
    oldbank:word;

procedure setbunc(n:byte);assembler;
     asm
      mov ax,$4f05
      mov bx,0
      mov dl,n
      int $10
     end;   { Change to Bank # }

procedure setPixel(X, Y : longint; C : byte);  { VESA putpixel }
var l:longint;
begin
 l:=x+pred(y)*800;
 setbunc(l div 65536);
 mem[$a000:l mod 65536]:=c;
end;

function GetPixel(X, Y : longint):byte;
var l:longint;
begin
 l:=x+pred(y)*800;
 setbunc(l div 65536);
 getpixel:=mem[$a000:l mod 65536];
end;

function getmkey:byte;
var
key:byte;
begin
asm
mov ax,3
int 33h
mov key,bl
end;
getmkey:=key;
end;

procedure hidemouse;
var
 hn,hm:word;
begin
flag:=false;
{dec(my);}
 for hn:=0 to 15 do
  for hm:=0 to 9 do
   setpixel(mx+hm,my+hn,mask[hn,hm]);
end;

procedure showmouse;
var
 hn,hm:word;
begin
for hn:=0 to 15 do
 for hm:=0 to 9 do
  mask[hn,hm]:=getpixel(mx+hm,my+hn);
for hn:=0 to 15 do
 for hm:=0 to 9 do
  if seta[hn,hm]<255 then setpixel(mx+hm,my+hn,seta[hn,hm]);
{  inc(my);}
flag:=true;
end;

procedure newmouse(Flags,CS,IP,AX,BX,CX,DX,SI,DI,DS,ES,BP : word);interrupt;
var hx,hy,hb,ev:word;
    hn,hm:integer;
begin
 ev:=ax;
 hx:=cx div 4;
 hy:=dx;
 hb:=bx;
 if flag then begin
 if ((hx<>mx) or (hy<>my)) then
  begin
   for hn:=0 to 15 do
    for hm:=0 to 9 do
     setpixel(mx+hm,my+hn,mask[hn,hm]);
   for hn:=0 to 15 do
    for hm:=0 to 9 do
     mask[hn,hm]:=getpixel(hx+hm,hy+hn);
   for hn:=0 to 15 do
    for hm:=0 to 9 do
    if seta[hn,hm]<255 then
     setpixel(hx+hm,hy+hn,seta[hn,hm]);
   end;
   mx:=hx;
   my:=hy;
  end;
 inline ($8B/ $E5/ $5D/ $07/ $1F/ $5F/ $5E/ $5A/ $59/$5B/ $58/ $CB);
end;

procedure initmouse;
begin
 mx:=0;
 my:=0;
 mode:=$103; { Vesa mode }
 sos:=seg(buf);
 ooo:=ofs(buf[0]); { pointing VESA information Buffer }
 oldbank:=0;
 asm
  mov ax,$4f01
  mov cx,mode
  mov es,sos
  mov di,ooo
  int $10
 end; { Get VESA info }

 if memw[sos:ooo+4]=0 then memw[sos:ooo+4]:=1;
 bank:=memw[sos:ooo+6] div memw[sos:ooo+4];
 { Granularity }

 xmax:=memw[sos:ooo+$12];
 ymax:=memw[sos:ooo+$14];
 if xmax=0 then begin xmax:=320;ymax:=200;bank:=0;end;
 { Get Screen Size }

 { pick up (0,0) mask }
 for n:=0 to 15 do
  for m:=0 to 9 do
   mask[n,m]:=getpixel(m,n);

 newseg:=seg(newmouse);
 newofs:=ofs(newmouse); { pointing to new mouse routine }
 newmask:=1;

 mxmax:=xmax*4;
 asm
  mov ax,0
  int $33    { mouse ? }
  mov ax,1
  int $33    { Show Mouse }
  mov ax,2
  int $33    { Hide Mouse }
  mov ax,7
  mov cx,0
  add mxmax,-38
  mov dx,mxmax
  int $33
  mov ax,8
  mov cx,0
  add ymax,-16
  mov dx,ymax  { Set YMAX for mouse windows }

  int $33
  mov ax,20
  mov cx,newmask
  mov es,newseg
  mov dx,newofs
  int $33      { Active USER Mouse Routine }
  mov ax,$000f
  mov cx,4
  mov dx,4
  int $33
 end;
end;

{procedure restoremouse;assembler;
 asm
  mov ax,20
  mov cx,oldmask
  mov es,oldseg
  mov dx,oldofs
  int $33   { Restore old Mouse Routine }
{ end;}

{procedure setpal(a,r,g,b:byte);
         begin
              port[$3c8]:=a;
              port[$3c9]:=r;
              port[$3c9]:=g;
              port[$3c9]:=b;
         end;

procedure putcartin(w:string);
var
v:array [0..60000] of byte absolute $a000:0;
f:file;
j,i,r,b,g:byte;
begin
assign(f,w);
reset(f,1);
seek(f,54);
for i:=0 to 255 do begin
blockread(f,r,1);
blockread(f,g,1);
blockread(f,b,1);
blockread(f,j,1);
setpal(i,b shr 2,g shr 2,r shr 2);
end;
setbunc(0);
for j:=1 to 7 do
begin
 blockread(f,v,32768);
 blockread(f,v[32768],32768);
 setbunc(j);
end;
 blockread(f,v,21248);
 close(f);
end;

procedure putbmp(x,y:longint;fname:string);
var
v:array [0..60000] of byte absolute $a000:0;
dim:array [1..2000] of byte;
f:file;
i,dx,dy:longint;
j,r,b,g:byte;
begin
assign(f,fname);
reset(f,1);
seek(f,18);
blockread(f,dx,4);
blockread(f,dy,4);
seek(f,54);
for i:=0 to 255 do begin
 blockread(f,r,1);
 blockread(f,g,1);
 blockread(f,b,1);
 blockread(f,j,1);
 setpal(i,b shr 2,g shr 2,r shr 2);
end;
for i:=1 to dy do
begin
 blockread(f,dim,dx);
 if ((pred(y+i)*maxx+x) mod 65536)+dx>65536 then begin
  setbunc((pred(y+i)*maxx+x) div 65536);
  move(dim,v[(pred(y+i)*maxx+x) mod 65536],65536-((pred(y+i)*maxx+x) mod 65536));
  setbunc((pred(y+i)*maxx+x+dx) div 65536);
  move(dim[65536-((pred(y+i)*maxx+x) mod 65536)],v,((pred(y+i)*maxx+x+dx) mod 65536));
 end
 else begin
  setbunc((pred(y+i)*maxx+x) div 65536);
  move(dim,v[(pred(y+i)*maxx+x) mod 65536],dx);
 end;
end;
close(f);
end;}

end.
