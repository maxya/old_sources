
TITLE  Simple programm for formating Floppy Disks

.MODEL small
    .DOSSEG
      INCLUDE dos.inc
      INCLUDE bios.inc

.STACK 100h

        .DATA
             drive equ 'A'
             em  equ  13,10,"$"
             msgDos db  "You MS-DOS Version is old,you need Version 8",em
             msgDosOk db "You MS-DOS Version is correct",em
             msgLoad  db  "Continue loading...",em

.CODE
begin:
    mov ax,@DATA
    mov ds,ax

;Check Dos Version - need 8.0(Milenium)
     @GetVer
     .IF al<8

     @ShowStr msgDos
      jmp endflag
     .ENDIF
     @ShowStr msgDosOk
     @ShowStr msgLoad




;end
endflag:
mov ah,4ch
int 21h
End begin