.MODEL small
.STACK 100h
.386
.DATA
 msgend equ  13,10,"$"

  msghi1  db "Copyright (c) by *********",msgend
  msghi2  db "Made by DIABLO",msgend

data  struc

data ends

matr  db 1,2,3,4
      db 5,6,7,8
      db 9,10,11,12

.CODE
    begin:
      mov ax,@data
      mov ds,ax

;show copyright

      mov ah,09h
      lea dx,msghi1
      int 21h
      lea dx,msghi2
      int 21h

;The body of the programm




;Exit Code
      mov ah,4ch
      int 21h
      END begin
