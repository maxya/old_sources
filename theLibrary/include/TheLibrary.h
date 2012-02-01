// TheLibrary.h
// ------------
// Main include file for TheLibrary.
//
// Copyright (c) by SeekWood Corp.
// All rights reserved.
//////////////////////////////////////////////////////////////////////

#if !defined SW_THE_LIBRARY_H__9F0BCCAA_9986_400d_96B0_5BC52DA66E59__INCLUDED_
#define SW_THE_LIBRARY_H__9F0BCCAA_9986_400d_96B0_5BC52DA66E59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define THELIBRARY_VER	0x0140
#define THELIBRARY_ALPHA	3

//////////////////////////////////////////////////////////////////////
#ifndef _WINDOWS_
#error Windows.h must be included before theLibrary.h
#endif
#include "stdio.h"
#include "Macros.h"
#include "Compress.h"
#include "File.h"
#include "UniversalText.h"
#include "SWPtrArray.h"
#include "swStreamOnFile.h"
#include "swStreamOnHeap.h"
#include "swDirectory.h"
#include "SWCommandLine.h"
#include "swNotify.h"
#include "swregkey.h"
//#include "Performance.h"

#if defined _DEBUG
#pragma comment (lib, "TheLibrary_D.lib")
#else
#pragma comment (lib, "TheLibrary.lib")
#endif

//////////////////////////////////////////////////////////////////////

extern BOOL g_fUnicodeSystem;

//////////////////////////////////////////////////////////////////////

void GetWindowTextUT (IN HWND hWnd, IN OUT CUniversalText &utString);
void SetWindowTextUT (IN HWND hWnd, IN CUniversalText utString);
void GetDlgItemTextUT (IN HWND hDlg, IN INT nIDDlgItem, IN OUT CUniversalText &utString);
void SetDlgItemTextUT (IN HWND hDlg, IN INT nIDDlgItem, IN CUniversalText utString);
int WINAPI MessageBoxUT (IN HWND hWnd, IN CUniversalText utText, IN CUniversalText utCaption, IN UINT uType);
BOOL WINAPI AppendMenuUT (IN HMENU hMenu, IN UINT uFlags, IN UINT_PTR uIDNewItem, IN CUniversalText utNewItem);
BOOL WINAPI InsertMenuUT (IN HMENU hMenu, IN UINT uPosition, IN UINT uFlags, IN UINT_PTR uIDNewItem, IN CUniversalText utNewItem);

HANDLE WINAPI CreateFileUT(
    IN CUniversalText utFileName,
    IN DWORD dwDesiredAccess,
    IN DWORD dwShareMode,
    IN LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    IN DWORD dwCreationDisposition,
    IN DWORD dwFlagsAndAttributes,
    IN HANDLE hTemplateFile
    );
BOOL DetectNT ();
BOOL SWCopyFile (IN CswFile &SrcFile, CswFile &DestFile, DWORD dwBufferSize = 1024 << 8);
CUniversalText GetCurrentDirectoryUT();
BOOL SetCurrentDirectoryUT (CUniversalText utPathName);

BOOL GetOpenFileNameUT (IN HWND hWndOwner, IN LPWSTR wszFilter, IN LPSTR szFilter,
						IN CUniversalText utDefExtension,
						OUT CUniversalText& utFileName);
BOOL GetSaveFileNameUT (IN HWND hWndOwner, IN LPWSTR wszFilter, IN LPSTR szFilter,
						IN CUniversalText utDefExtension,
						OUT CUniversalText& utFileName);
CUniversalText GetVKNameTextUT (IN UINT uVK);

INT GetBitCount(BYTE bTest);
INT GetBitCount(WORD wTest);
INT GetBitCount(DWORD dwTest);


//////////////////////////////////////////////////////////////////////
// SeekWood Console I/O
//////////////////////////////////////////////////////////////////////

BOOL SWConsoleOutput (CUniversalText utStr,						// Выводимая строка
					  CUniversalText utToConsole = (LPSTR)NULL, // Имя консоли вывода.
					  BOOL fRenameUnnamedConsole = FALSE);		// Переименоать или нет доступную неименованую консоль.

#define SWDEBUGTRACE_ENABLE()							\
	CswFile __logFile;									\
	BOOL __logEnabled = FALSE;

#define SWDEBUGTRACE_DECLARE()							\
	extern CswFile __logFile;							\
	extern BOOL __logEnabled;

#define SWDEBUGTRACE_START(utLogFile)						\
	__logEnabled = (BOOL) __logFile.OpenHDD(				\
		utLogFile, GENERIC_WRITE, FILE_SHARE_READ ) &&		\
		( __logFile.SeekEnd(), TRUE );	
#define SWDEBUGTRACE_END()								\
	__logEnabled && ( __logFile.Close(), true );		\
	__logEnabled = FALSE;
#define SWDEBUGTRACE(utStr, nLevel)						\
	__logEnabled && ( CUniversalText(utStr).SaveAsPlain(__logFile, EOF, FALSE) )

#if defined _DEBUG
#define SWOutputDebugString(utStr) SWConsoleOutput (utStr); SWDEBUGTRACE(CUniversalText().Format( "%s" , (LPSTR)(utStr) ), 0)
#define SWOutputDebugStringNamed(utStr, utName) SWConsoleOutput (utStr, utName); SWDEBUGTRACE(CUniversalText().Format( "<%s>:\t%s" , (LPSTR)(utName), (LPSTR)(utStr) ), 0)
#define SWOutputDebugStringNamedRename(utStr, utName) SWConsoleOutput (utStr, utName, TRUE); SWDEBUGTRACE(utStr, 0)
#else
#define SWOutputDebugString(utStr)
#define SWOutputDebugStringNamed(utStr, utName)
#define SWOutputDebugStringNamedRename(utStr, utName)
#endif

//////////////////////////////////////////////////////////////////////

const CUniversalText& i18n (const CUniversalText&);
void i18n_translate (const CUniversalText&, const CUniversalText&);

//////////////////////////////////////////////////////////////////////

#endif //!defined SW_THE_LIBRARY_H__9F0BCCAA_9986_400d_96B0_5BC52DA66E59__INCLUDED_