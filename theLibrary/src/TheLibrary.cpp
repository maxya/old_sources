// TheLibrary.cpp: 
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TheLibrary.h"
#include "swMap.h"

//////////////////////////////////////////////////////////////////////

BOOL g_fUnicodeSystem = DetectNT ();
CswMap<CUniversalText /*english*/, CUniversalText/*translated*/> g_mpI18N;

//////////////////////////////////////////////////////////////////////

void SetWindowTextUT (IN HWND hWnd, IN CUniversalText utString)
{
	if (IsWindowUnicode (hWnd))
		SetWindowTextW (hWnd, (LPWSTR) utString);
	else
		SetWindowTextA (hWnd, (LPSTR) utString);
}

//////////////////////////////////////////////////////////////////////

void GetDlgItemTextUT (IN HWND hDlg, IN INT nIDDlgItem, IN OUT CUniversalText &utString)
{
	GetWindowTextUT (GetDlgItem(hDlg, nIDDlgItem), utString);
}

//////////////////////////////////////////////////////////////////////

void SetDlgItemTextUT (IN HWND hDlg, IN INT nIDDlgItem, IN CUniversalText utString)
{
	SetWindowTextUT (GetDlgItem(hDlg, nIDDlgItem), utString);
}

//////////////////////////////////////////////////////////////////////

BOOL DetectNT ()
{
	OSVERSIONINFO osver;
	osver.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	GetVersionEx (&osver);
	
	if(osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
		return true;
	else
		return false;	
}

//////////////////////////////////////////////////////////////////////

#define SWCON_FLAG_UNICODE		0x0001
#define SWCON_FLAG_NAME			0x0002
#define SWCON_FLAG_ACCEPTNAME	0x0004

BOOL SWConsoleOutput (CUniversalText utStr, CUniversalText utToConsole, BOOL fRenameUnnamedConsole)
{
	HWND hWndConsole = NULL;

	while (1)
	{
		hWndConsole = FindWindowEx (NULL, hWndConsole, "SW Console", NULL);
		if (!hWndConsole)
			break;
		
		BOOL fUnicodeCopy;
		COPYDATASTRUCT cds;
		
		fUnicodeCopy = utToConsole.IsPureUnicode ();
		cds.cbData = fUnicodeCopy? utToConsole.GetSizeW () : utToConsole.GetSizeA ();
		cds.dwData = fUnicodeCopy | SWCON_FLAG_NAME;
		if (fRenameUnnamedConsole)
			cds.dwData |= SWCON_FLAG_ACCEPTNAME;
		cds.lpData = fUnicodeCopy ? (LPVOID)(LPWSTR) utToConsole : (LPVOID)(LPSTR) utToConsole;
		if (!SendMessage (hWndConsole, WM_COPYDATA, 0, (LPARAM) &cds))
			continue;
		
		fUnicodeCopy = utStr.IsPureUnicode ();
		cds.cbData = fUnicodeCopy? utStr.GetSizeW () : utStr.GetSizeA ();
		cds.dwData = fUnicodeCopy;
		cds.lpData = fUnicodeCopy ? (LPVOID)(LPWSTR) utStr : (LPVOID)(LPSTR) utStr;
		return SendMessage (hWndConsole, WM_COPYDATA, 0, (LPARAM) &cds);	
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

int WINAPI MessageBoxUT (IN HWND hWnd, IN CUniversalText utText, IN CUniversalText utCaption, IN UINT uType)
{
	if (g_fUnicodeSystem)
		return MessageBoxW (hWnd, utText, utCaption, uType);
	else
		return MessageBoxA (hWnd, utText, utCaption, uType);
}

//////////////////////////////////////////////////////////////////////

BOOL WINAPI AppendMenuUT(
    IN HMENU hMenu,
    IN UINT uFlags,
    IN UINT_PTR uIDNewItem,
    IN CUniversalText utNewItem
    )
{
	if (g_fUnicodeSystem)
		return AppendMenuW (hMenu, uFlags, uIDNewItem, utNewItem);
	else
		return AppendMenuA (hMenu, uFlags, uIDNewItem, utNewItem);
}

//////////////////////////////////////////////////////////////////////

BOOL WINAPI InsertMenuUT (IN HMENU hMenu, IN UINT uPosition, IN UINT uFlags, IN UINT_PTR uIDNewItem, IN CUniversalText utNewItem)
{
	if (g_fUnicodeSystem)
		return InsertMenuW (hMenu, uPosition, uFlags, uIDNewItem, utNewItem);
	else
		return InsertMenuA (hMenu, uPosition, uFlags, uIDNewItem, utNewItem);
}

//////////////////////////////////////////////////////////////////////

BOOL SWCopyFile (IN CswFile &SrcFile, CswFile &DestFile, DWORD dwBufferSize)
{
	HANDLE hHeap = GetProcessHeap ();
	LPVOID pvBuffer = HeapAlloc (hHeap, 0, dwBufferSize);
	if (!pvBuffer)
		return FALSE;

	DWORD dwRead;
	while (dwRead = SrcFile.Read (pvBuffer, dwBufferSize), dwRead != EOF)
	{
		if (DestFile.Write (pvBuffer, dwRead) == EOF)
			return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

HANDLE WINAPI CreateFileUT(
    IN CUniversalText utFileName,
    IN DWORD dwDesiredAccess,
    IN DWORD dwShareMode,
    IN LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    IN DWORD dwCreationDisposition,
    IN DWORD dwFlagsAndAttributes,
    IN HANDLE hTemplateFile
    )
{
	HANDLE hFile;
	if (g_fUnicodeSystem)
		hFile = CreateFileW(
			utFileName,
			dwDesiredAccess,
			dwShareMode,
			lpSecurityAttributes,
			dwCreationDisposition,
			dwFlagsAndAttributes,
			hTemplateFile
		);
	else
		hFile = CreateFileA(
			utFileName,
			dwDesiredAccess,
			dwShareMode,
			lpSecurityAttributes,
			dwCreationDisposition,
			dwFlagsAndAttributes,
			hTemplateFile
		);
	return hFile;
}

//////////////////////////////////////////////////////////////////////

CUniversalText GetCurrentDirectoryUT()
{
	CUniversalText utPath;
	if (g_fUnicodeSystem)
	{
		DWORD cbNeeded = GetCurrentDirectoryW (0, NULL);
		if (cbNeeded)
		{
			LPWSTR wszPath = new WCHAR [cbNeeded];
			GetCurrentDirectoryW (cbNeeded, wszPath);
			utPath = wszPath;
			delete wszPath;
		}
	}
	else
	{
		DWORD cbNeeded = GetCurrentDirectoryA (0, NULL);
		if (cbNeeded)
		{
			LPSTR szPath = new CHAR [cbNeeded];
			GetCurrentDirectoryA (cbNeeded, szPath);
			utPath = szPath;
			delete szPath;
		}
	}
	return utPath;
}

//////////////////////////////////////////////////////////////////////

BOOL SetCurrentDirectoryUT ( CUniversalText utPathName)
{
	if (g_fUnicodeSystem)
		return SetCurrentDirectoryW (utPathName);
	else
		return SetCurrentDirectoryA (utPathName);
}

//////////////////////////////////////////////////////////////////////

BOOL GetOpenFileNameUT (IN HWND hWndOwner, IN LPWSTR wszFilter, IN LPSTR szFilter,
						IN CUniversalText utDefExtension,
						OUT CUniversalText& utFileName)
{
	if (g_fUnicodeSystem)
	{
		WCHAR wszFile [MAX_PATH];
		ZeroMemory (wszFile, MAX_PATH);
		
		WCHAR wszFileTitle [256];
		ZeroMemory (wszFileTitle, 256);

		OPENFILENAMEW ofn;
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.hwndOwner = hWndOwner;
		ofn.hInstance = (HINSTANCE) GetWindowLong (hWndOwner, GWL_HINSTANCE);
		ofn.lpstrFilter = wszFilter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = wszFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFileTitle = wszFileTitle;
		ofn.nMaxFileTitle = 256;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;	
		ofn.Flags =
			OFN_FILEMUSTEXIST |
			OFN_EXPLORER | 
			OFN_HIDEREADONLY | 
			OFN_NOREADONLYRETURN | 
			OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = utDefExtension;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;
		if (GetOpenFileNameW (&ofn))
		{
			utFileName = wszFile;
			return TRUE;
		}
	}
	else
	{
		CHAR szFile [MAX_PATH];
		ZeroMemory (szFile, MAX_PATH);
		
		CHAR szFileTitle [256];
		ZeroMemory (szFileTitle, 256);

		OPENFILENAMEA ofn;
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.hwndOwner = hWndOwner;
		ofn.hInstance = (HINSTANCE) GetWindowLong (hWndOwner, GWL_HINSTANCE);
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = 256;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;	
		ofn.Flags =
			OFN_FILEMUSTEXIST |
			OFN_EXPLORER | 
			OFN_HIDEREADONLY | 
			OFN_NOREADONLYRETURN | 
			OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = utDefExtension;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;
		if (GetOpenFileNameA (&ofn))
		{
			utFileName = szFile;
			return TRUE;
		}
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL GetSaveFileNameUT (IN HWND hWndOwner, IN LPWSTR wszFilter, IN LPSTR szFilter,
						IN CUniversalText utDefExtension,
						OUT CUniversalText& utFileName)
{
	if (g_fUnicodeSystem)
	{
		WCHAR wszFile [MAX_PATH];
		ZeroMemory (wszFile, MAX_PATH);
		
		WCHAR wszFileTitle [256];
		ZeroMemory (wszFileTitle, 256);

		OPENFILENAMEW ofn;
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.hwndOwner = hWndOwner;
		ofn.hInstance = (HINSTANCE) GetWindowLong (hWndOwner, GWL_HINSTANCE);
		ofn.lpstrFilter = wszFilter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = wszFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFileTitle = wszFileTitle;
		ofn.nMaxFileTitle = 256;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;	
		ofn.Flags =
			OFN_FILEMUSTEXIST |
			OFN_EXPLORER | 
			OFN_HIDEREADONLY | 
			OFN_NOREADONLYRETURN | 
			OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = utDefExtension;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;
		if (GetSaveFileNameW (&ofn))
		{
			utFileName = wszFile;
			return TRUE;
		}
	}
	else
	{
		CHAR szFile [MAX_PATH];
		ZeroMemory (szFile, MAX_PATH);
		
		CHAR szFileTitle [256];
		ZeroMemory (szFileTitle, 256);

		OPENFILENAMEA ofn;
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.hwndOwner = hWndOwner;
		ofn.hInstance = (HINSTANCE) GetWindowLong (hWndOwner, GWL_HINSTANCE);
		ofn.lpstrFilter = szFilter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFileTitle = szFileTitle;
		ofn.nMaxFileTitle = 256;
		ofn.lpstrInitialDir = NULL;
		ofn.lpstrTitle = NULL;	
		ofn.Flags =
			OFN_FILEMUSTEXIST |
			OFN_EXPLORER | 
			OFN_HIDEREADONLY | 
			OFN_NOREADONLYRETURN | 
			OFN_OVERWRITEPROMPT;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = utDefExtension;
		ofn.lCustData = NULL;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;
		if (GetSaveFileNameA (&ofn))
		{
			utFileName = szFile;
			return TRUE;
		}
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

CUniversalText GetVKNameTextUT (IN UINT uVK)
{
	BYTE bScan = MapVirtualKey (uVK, 0);
	LONG uCode = (LONG) uVK | (bScan << 16) | (1 << 24);

	if (g_fUnicodeSystem)
	{
		WCHAR wszCh[15];
		wszCh[0] = L'\0';
		int n = GetKeyNameTextW (uCode ,wszCh, 15);
		return wszCh;
	}
	else
	{
		CHAR szCh[15];
		szCh[0] = '\0';
		GetKeyNameTextA (uCode ,szCh, 15);
		return szCh;
	}
}

INT GetBitCount(BYTE bTest)
{
	static BYTE mpbCount[0x10] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
	return (mpbCount[bTest & '\x0F'] + mpbCount[(bTest >> 0x4) & '\x0F']);
}

INT GetBitCount(WORD wTest)
{
	return GetBitCount (HIBYTE(wTest)) + GetBitCount(LOBYTE(wTest));
}

INT GetBitCount(DWORD dwTest)
{
	return GetBitCount (HIWORD(dwTest)) + GetBitCount(LOWORD(dwTest));
}

const CUniversalText& i18n (const CUniversalText& utText)
{
	CUniversalText* putTrans = g_mpI18N.Lookup (utText);
	if (putTrans)
		return *putTrans;
	return utText;
}

void i18n_translate (const CUniversalText& utText, const CUniversalText& utTrans)
{
	g_mpI18N[utText] = utTrans;
}
