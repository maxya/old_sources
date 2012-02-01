.386
.MODEL flat, stdcall
  option casemap:none
  include D:\develop\masm32\include\windows.inc
  include D:\develop\masm32\include\kernel32.inc
  include D:\develop\masm32\include\user32.inc
  includelib D:\develop\masm32\lib\user32.lib
  includelib D:\develop\masm32\lib\kernel32.lib
  
  .DATA
    x	dw	5
    y	dw	10
    z	dw	?
    MsgCaption    db "First Mb Caption",0
    MsgBoxText    db "Some Fn Text",0  
  
  .CODE
  start:
      invoke MessageBox, NULL, addr MsgBoxText, addr MsgCaption, MB_OK
      invoke ExitProcess, NULL
  end start
