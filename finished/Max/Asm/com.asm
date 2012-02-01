
cseg    segment


  org 100h



Start:  jmp  begin
        em equ  13,10,"$"
        msg1  db  "Hello Dork!!!",em
        msg2  db  "This time you reed this message - your computer is dieng...",em
        msg3  db  "Now your sistem in INFECTED...",em
        msg4  db  "Press any key",em
begin:
        mov ah,09h
        ;mov dx, offset msg1
        lea dx,msg1
        int 21h
        lea dx,msg2
        int 21h
        lea dx,msg3
        int 21h
        lea dx,msg4
        int 21h

        mov ah,10h
        int 16h

;int 20h or ret

ret
cseg ends
END Start