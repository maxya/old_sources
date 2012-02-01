# Microsoft Developer Studio Generated NMAKE File, Based on LibraryTest.dsp
!IF "$(CFG)" == ""
CFG=LibraryTest - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LibraryTest - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LibraryTest - Win32 Release" && "$(CFG)" != "LibraryTest - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LibraryTest.mak" CFG="LibraryTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LibraryTest - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "LibraryTest - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "LibraryTest - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LibraryTest.exe"

!ELSE 

ALL : "TheLibrary - Win32 Release" "$(OUTDIR)\LibraryTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TheLibrary - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LibraryTest.obj"
	-@erase "$(INTDIR)\LibraryTest.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWDiskFileStream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LibraryTest.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LibraryTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibraryTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LibraryTest.pdb" /machine:I386 /out:"$(OUTDIR)\LibraryTest.exe" 
LINK32_OBJS= \
	"$(INTDIR)\LibraryTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWDiskFileStream.obj" \
	"..\..\Lib\TheLibrary.lib"

"$(OUTDIR)\LibraryTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LibraryTest - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LibraryTest.exe"

!ELSE 

ALL : "TheLibrary - Win32 Debug" "$(OUTDIR)\LibraryTest.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TheLibrary - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\LibraryTest.obj"
	-@erase "$(INTDIR)\LibraryTest.pch"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWDiskFileStream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LibraryTest.exe"
	-@erase "$(OUTDIR)\LibraryTest.ilk"
	-@erase "$(OUTDIR)\LibraryTest.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LibraryTest.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LibraryTest.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LibraryTest.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LibraryTest.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LibraryTest.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWDiskFileStream.obj" \
	"..\..\Lib\TheLibrary_D.lib"

"$(OUTDIR)\LibraryTest.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LibraryTest.dep")
!INCLUDE "LibraryTest.dep"
!ELSE 
!MESSAGE Warning: cannot find "LibraryTest.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LibraryTest - Win32 Release" || "$(CFG)" == "LibraryTest - Win32 Debug"
SOURCE=.\LibraryTest.cpp

"$(INTDIR)\LibraryTest.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibraryTest.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LibraryTest - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LibraryTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibraryTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LibraryTest - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\LibraryTest.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LibraryTest.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SWDiskFileStream.cpp

"$(INTDIR)\SWDiskFileStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LibraryTest.pch"


!IF  "$(CFG)" == "LibraryTest - Win32 Release"

"TheLibrary - Win32 Release" : 
   cd "\Projects\WIN32\TheLibrary\Src"
   $(MAKE) /$(MAKEFLAGS) /F .\TheLibrary.mak CFG="TheLibrary - Win32 Release" 
   cd "..\Tests\LibraryTest"

"TheLibrary - Win32 ReleaseCLEAN" : 
   cd "\Projects\WIN32\TheLibrary\Src"
   $(MAKE) /$(MAKEFLAGS) /F .\TheLibrary.mak CFG="TheLibrary - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Tests\LibraryTest"

!ELSEIF  "$(CFG)" == "LibraryTest - Win32 Debug"

"TheLibrary - Win32 Debug" : 
   cd "\Projects\WIN32\TheLibrary\Src"
   $(MAKE) /$(MAKEFLAGS) /F .\TheLibrary.mak CFG="TheLibrary - Win32 Debug" 
   cd "..\Tests\LibraryTest"

"TheLibrary - Win32 DebugCLEAN" : 
   cd "\Projects\WIN32\TheLibrary\Src"
   $(MAKE) /$(MAKEFLAGS) /F .\TheLibrary.mak CFG="TheLibrary - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Tests\LibraryTest"

!ENDIF 


!ENDIF 

