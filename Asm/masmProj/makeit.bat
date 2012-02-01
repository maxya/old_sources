@echo off

if not exist rsrc.rc goto over1
D:\DEVELOP\MASM32\BIN\RC.EXE /v rsrc.rc
D:\DEVELOP\MASM32\BIN\CVTRES.EXE /machine:ix86 rsrc.res
:over1

if exist %1.obj del Project.obj
if exist %1.exe del Project.exe

D:\DEVELOP\MASM32\BIN\ML.EXE /c /coff Project.asm
if errorlevel 1 goto errasm

if not exist rsrc.obj goto nores

D:\DEVELOP\MASM32\BIN\LINK.EXE /SUBSYSTEM:WINDOWS Project.obj rsrc.obj
if errorlevel 1 goto errlink

dir Project
goto TheEnd

:nores
D:\DEVELOP\MASM32\BIN\LINK.EXE /SUBSYSTEM:WINDOWS Project.obj
if errorlevel 1 goto errlink
dir %1
goto TheEnd

:errlink
echo _
echo Link error
goto TheEnd

:errasm
echo _
echo Assembly Error
goto TheEnd

:TheEnd

pause

