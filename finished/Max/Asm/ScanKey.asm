;******************************
;******************************
;This proga just scan kode from keyboard and compare it with known
;commands and jmp to them. So it prety easy.
;Copyright (C) by Nightmare
;Made by Max Gorbanev
;NIGHTMARE SOFTWARE CORPORATION
;******************************
;******************************




.MODEL small
.STACK 100h
.386
.DATA

;Here is some macroses

;This macro is not perfect -- something wrong in it.
ClrScr  macro
        pusha
        mov ax,0b800h
        mov es,ax
        mov di,0
        mov ecx,(80*25)/2
        mov eax,0f0fdbdbh
        rep stosd
        popa;not zhopa, it means pop A
endm.


;EQU block

endmsg equ 13,10,"$"

;Messege block

  msgMax db  "Made by Max Gorbanev",endmsg
  msgCopy db  "Copyright (C) by Nightmare 2000",endmsg
  msgHi  db  "Hello",endmsg
  msgPress  db  "Press any key",endmsg
  msgSpace  db  "You pressed Space",endmsg
  msgEscape  db  "You just pressed Escape",endmsg
  msgEnterkey  db  "You just pressed Enter",endmsg
  msgAnyKey  db  "You pressed any other key",endmsg

;************************
;Here is main code begins
;************************
.CODE

  begin:
      mov ax,@data
      mov ds,ax
;ClrScr
;Copyright
           mov ah,09h
           lea dx,msgMax
           int 21h
           lea dx,msgCopy
           int 21h

;Intro
      mov ah,09h
      lea dx,msgHi
      int 21h
      lea dx,msgPress
      int 21h
;End Intro

;Dvizhok

      mov ah,10h
      int 16h
      cmp ah,39h
      je Space
      cmp ah,01h
      je ESCape
      cmp ah,1ch
      je Enterkey

jmp  AnyKey
;End of Dvizhok

;hepe is some probably snswers
        mov ah,09h
Space:
        mov ah,09h
        lea dx,msgSpace
       jmp ContinProg
Enterkey:
          mov ah,09h
          lea  dx,msgEnterkey
       jmp ContinProg
ESCape:
        mov ah,09h
        lea dx,msgESCape
       jmp ContinProg
AnyKey:
        mov ah,09h
        lea dx,msgAnyKey
        jmp ContinProg


ContinProg:
int 21h

exitflag:
;Exit Flag
      mov ah,4ch
      int 21h
      END begin