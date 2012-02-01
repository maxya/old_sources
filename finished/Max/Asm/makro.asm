

;For using this macro tipe next-->
;@PrintChar 'A'
@PrintChar  MACRO    char
                       mov  ah,09
                       mov  dl,&char
                       int 21h
                       ENDM