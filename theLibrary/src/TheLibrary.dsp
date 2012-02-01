# Microsoft Developer Studio Project File - Name="TheLibrary" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=TheLibrary - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TheLibrary.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TheLibrary.mak" CFG="TheLibrary - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TheLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TheLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/TheLibrary/Src", BCAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TheLibrary - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Lib\VS6"
# PROP Intermediate_Dir "ReleaseVS6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /Ox /Og /Os /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Oa
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Lib\VS6"
# PROP Intermediate_Dir "DebugVS6"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Lib\VS6\TheLibrary_D.lib"

!ENDIF 

# Begin Target

# Name "TheLibrary - Win32 Release"
# Name "TheLibrary - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Compress.cpp
# End Source File
# Begin Source File

SOURCE=.\File.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SWCommandLine.cpp
# End Source File
# Begin Source File

SOURCE=.\swDirectory.cpp
# End Source File
# Begin Source File

SOURCE=.\swINIworks.cpp
# End Source File
# Begin Source File

SOURCE=.\SWPtrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\swStreamOnFile.cpp
# End Source File
# Begin Source File

SOURCE=.\swStreamOnHeap.cpp
# End Source File
# Begin Source File

SOURCE=.\TheLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\UniversalText.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Include\Compress.h
# End Source File
# Begin Source File

SOURCE=..\Include\File.h
# End Source File
# Begin Source File

SOURCE=..\Include\Macros.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\Include\SWCommandLine.h
# End Source File
# Begin Source File

SOURCE=..\Include\swDirectory.h
# End Source File
# Begin Source File

SOURCE=..\include\swINIworks.h
# End Source File
# Begin Source File

SOURCE=..\Include\SWLists.h
# End Source File
# Begin Source File

SOURCE=..\Include\SWMap.h
# End Source File
# Begin Source File

SOURCE=..\Include\swNotify.h
# End Source File
# Begin Source File

SOURCE=..\Include\SWPtrArray.h
# End Source File
# Begin Source File

SOURCE=..\Include\swRanges.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\swregkey.h
# End Source File
# Begin Source File

SOURCE=..\Include\swStreamOnFile.h
# End Source File
# Begin Source File

SOURCE=..\Include\swStreamOnHeap.h
# End Source File
# Begin Source File

SOURCE=..\Include\TheLibrary.h
# End Source File
# Begin Source File

SOURCE=..\Include\Thread.h
# End Source File
# Begin Source File

SOURCE=..\Include\UniversalText.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
