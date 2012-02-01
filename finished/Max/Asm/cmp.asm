
.MODEL SMALL
.DATA
x  dw  5
y  dw  10
z  dw  1

msg1  db  "X >3",13,10,"$"
msg2  db  "X <3",13,10,"$"

.CODE
  begin:
    mov ax,@data
    mov ds,ax

    mov ah,10h
    int 16h
    cmp ah,6
    jl next

    mov ah,09h
    lea dx,msg1
    int 21h
    jmp exitflag
next:
    mov ah,09h
    lea dx,msg2
    int 21h

exitflag:
    mov ah,4ch
    int 21h
  end begin
