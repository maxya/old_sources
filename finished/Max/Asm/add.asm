.MODEL SMALL
.DATA
x  dw 5
y  dw 3
z  dw ?

.CODE
begin: mov ax,@data
       mov dx,ax
       
  mov ax,x
  add ax,y
  mov z,ax
  mov ah,4ch
  int 21h
  end begin