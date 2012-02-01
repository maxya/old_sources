# Microsoft Developer Studio Generated NMAKE File, Based on TheLibrary.dsp
!IF "$(CFG)" == ""
CFG=TheLibrary - Win32 Unicode Debug
!MESSAGE No configuration specified. Defaulting to TheLibrary - Win32 Unicode Debug.
!ENDIF 

!IF "$(CFG)" != "TheLibrary - Win32 Release" && "$(CFG)" != "TheLibrary - Win32 Debug" && "$(CFG)" != "TheLibrary - Win32 Unicode Debug" && "$(CFG)" != "TheLibrary - Win32 Unicode Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TheLibrary.mak" CFG="TheLibrary - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TheLibrary - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "TheLibrary - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TheLibrary - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "TheLibrary - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
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

!IF  "$(CFG)" == "TheLibrary - Win32 Release"

OUTDIR=.\..\Lib
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Lib
# End Custom Macros

ALL : "$(OUTDIR)\TheLibrary.lib"


CLEAN :
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWCommandLine.obj"
	-@erase "$(INTDIR)\swDirectory.obj"
	-@erase "$(INTDIR)\swINIworks.obj"
	-@erase "$(INTDIR)\SWPtrArray.obj"
	-@erase "$(INTDIR)\swStreamOnFile.obj"
	-@erase "$(INTDIR)\swStreamOnHeap.obj"
	-@erase "$(INTDIR)\TheLibrary.obj"
	-@erase "$(INTDIR)\TheLibrary.pch"
	-@erase "$(INTDIR)\UniversalText.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TheLibrary.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /Ox /Og /Os /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\TheLibrary.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TheLibrary.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\TheLibrary.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWCommandLine.obj" \
	"$(INTDIR)\swDirectory.obj" \
	"$(INTDIR)\swINIworks.obj" \
	"$(INTDIR)\SWPtrArray.obj" \
	"$(INTDIR)\swStreamOnFile.obj" \
	"$(INTDIR)\swStreamOnHeap.obj" \
	"$(INTDIR)\TheLibrary.obj" \
	"$(INTDIR)\UniversalText.obj"

"$(OUTDIR)\TheLibrary.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Debug"

OUTDIR=.\..\Lib
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Lib\ 
# End Custom Macros

ALL : "$(OUTDIR)\TheLibraryD.lib"


CLEAN :
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWCommandLine.obj"
	-@erase "$(INTDIR)\swDirectory.obj"
	-@erase "$(INTDIR)\swINIworks.obj"
	-@erase "$(INTDIR)\SWPtrArray.obj"
	-@erase "$(INTDIR)\swStreamOnFile.obj"
	-@erase "$(INTDIR)\swStreamOnHeap.obj"
	-@erase "$(INTDIR)\TheLibrary.obj"
	-@erase "$(INTDIR)\TheLibrary.pch"
	-@erase "$(INTDIR)\UniversalText.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TheLibraryD.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\TheLibrary.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TheLibrary.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\TheLibraryD.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWCommandLine.obj" \
	"$(INTDIR)\swDirectory.obj" \
	"$(INTDIR)\swINIworks.obj" \
	"$(INTDIR)\SWPtrArray.obj" \
	"$(INTDIR)\swStreamOnFile.obj" \
	"$(INTDIR)\swStreamOnHeap.obj" \
	"$(INTDIR)\TheLibrary.obj" \
	"$(INTDIR)\UniversalText.obj"

"$(OUTDIR)\TheLibraryD.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Unicode Debug"

OUTDIR=.\..\Lib
INTDIR=.\UDebug
# Begin Custom Macros
OutDir=.\..\Lib
# End Custom Macros

ALL : "$(OUTDIR)\TheLibraryDU.lib"


CLEAN :
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWCommandLine.obj"
	-@erase "$(INTDIR)\swDirectory.obj"
	-@erase "$(INTDIR)\swINIworks.obj"
	-@erase "$(INTDIR)\SWPtrArray.obj"
	-@erase "$(INTDIR)\swStreamOnFile.obj"
	-@erase "$(INTDIR)\swStreamOnHeap.obj"
	-@erase "$(INTDIR)\TheLibrary.obj"
	-@erase "$(INTDIR)\TheLibrary.pch"
	-@erase "$(INTDIR)\UniversalText.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TheLibraryDU.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\TheLibrary.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TheLibrary.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\TheLibraryDU.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWCommandLine.obj" \
	"$(INTDIR)\swDirectory.obj" \
	"$(INTDIR)\swINIworks.obj" \
	"$(INTDIR)\SWPtrArray.obj" \
	"$(INTDIR)\swStreamOnFile.obj" \
	"$(INTDIR)\swStreamOnHeap.obj" \
	"$(INTDIR)\TheLibrary.obj" \
	"$(INTDIR)\UniversalText.obj"

"$(OUTDIR)\TheLibraryDU.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Unicode Release"

OUTDIR=.\..\Lib
INTDIR=.\URelease
# Begin Custom Macros
OutDir=.\..\Lib
# End Custom Macros

ALL : "$(OUTDIR)\theLibraryU.lib"


CLEAN :
	-@erase "$(INTDIR)\Compress.obj"
	-@erase "$(INTDIR)\File.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SWCommandLine.obj"
	-@erase "$(INTDIR)\swDirectory.obj"
	-@erase "$(INTDIR)\swINIworks.obj"
	-@erase "$(INTDIR)\SWPtrArray.obj"
	-@erase "$(INTDIR)\swStreamOnFile.obj"
	-@erase "$(INTDIR)\swStreamOnHeap.obj"
	-@erase "$(INTDIR)\TheLibrary.obj"
	-@erase "$(INTDIR)\TheLibrary.pch"
	-@erase "$(INTDIR)\UniversalText.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\theLibraryU.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /Ox /Og /Os /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TheLibrary.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TheLibrary.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\theLibraryU.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Compress.obj" \
	"$(INTDIR)\File.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SWCommandLine.obj" \
	"$(INTDIR)\swDirectory.obj" \
	"$(INTDIR)\swINIworks.obj" \
	"$(INTDIR)\SWPtrArray.obj" \
	"$(INTDIR)\swStreamOnFile.obj" \
	"$(INTDIR)\swStreamOnHeap.obj" \
	"$(INTDIR)\TheLibrary.obj" \
	"$(INTDIR)\UniversalText.obj"

"$(OUTDIR)\theLibraryU.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("TheLibrary.dep")
!INCLUDE "TheLibrary.dep"
!ELSE 
!MESSAGE Warning: cannot find "TheLibrary.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TheLibrary - Win32 Release" || "$(CFG)" == "TheLibrary - Win32 Debug" || "$(CFG)" == "TheLibrary - Win32 Unicode Debug" || "$(CFG)" == "TheLibrary - Win32 Unicode Release"
SOURCE=.\Compress.cpp

"$(INTDIR)\Compress.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\File.cpp

"$(INTDIR)\File.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TheLibrary - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /Ox /Og /Os /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\TheLibrary.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TheLibrary.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\TheLibrary.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TheLibrary.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\TheLibrary.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TheLibrary.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TheLibrary - Win32 Unicode Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /Ox /Og /Os /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "UNICODE" /D "_UNICODE" /Fp"$(INTDIR)\TheLibrary.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TheLibrary.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SWCommandLine.cpp

"$(INTDIR)\SWCommandLine.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\swDirectory.cpp

"$(INTDIR)\swDirectory.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\swINIworks.cpp

"$(INTDIR)\swINIworks.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\SWPtrArray.cpp

"$(INTDIR)\SWPtrArray.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\swStreamOnFile.cpp

"$(INTDIR)\swStreamOnFile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\swStreamOnHeap.cpp

"$(INTDIR)\swStreamOnHeap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\TheLibrary.cpp

"$(INTDIR)\TheLibrary.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"


SOURCE=.\UniversalText.cpp

"$(INTDIR)\UniversalText.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TheLibrary.pch"



!ENDIF 

