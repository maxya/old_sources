;IDEAL
.MODEL small
INCLUDE DOS.INC
.STACK 100h
.DATA

msgend equ 13,10,"$"

        msg1  db  "Hello world",msgend
        msghi db  "Press any key",msgend
.CODE
        start:
        mov ax,@data
        mov ds,ax

        mov ah,09h
        lea dx,msg1
        int 21h

        lea dx,msghi
        int 21h
        
        mov ah,10h
        int 16h
        



        mov ax,4c00h
        int 21h
        end start