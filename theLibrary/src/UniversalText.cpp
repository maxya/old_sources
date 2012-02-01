// UniversalText.cpp: implementation of the CUniversalText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UniversalText.h"
#include "File.h"
#include "..\include\universaltext.h"

// Static members 
LPSTR CUniversalText::g_szCRLF = "\r\n";
LPWSTR CUniversalText::g_szwCRLF = L"\r\n";
HANDLE CUniversalText::m_hHeap = GetProcessHeap ();

//////////////////////////////////////////////////////////////////////
// Construction/Destruction, Initialization and assigment
//////////////////////////////////////////////////////////////////////

void CUniversalText::Init ()
{
	m_szText = NULL;
	m_szwText = NULL;
	m_fPureUnicode = FALSE;
	m_hHeap = GetProcessHeap ();
}

//////////////////////////////////////////////////////////////////////

CUniversalText::CUniversalText()
{
	Init ();
}

///////////////////////`///////////////////////////////////////////////

CUniversalText::CUniversalText (const CUniversalText& utSrc)
{
	Init ();
	*this = utSrc;
}

//////////////////////////////////////////////////////////////////////

CUniversalText::CUniversalText (LPCWSTR szText)
{
	Init ();
	m_szwText = Copy (szText);
	m_fPureUnicode = TRUE;
}

//////////////////////////////////////////////////////////////////////

CUniversalText::CUniversalText (LPCSTR szText)
{
	Init ();
	m_szText = Copy (szText);
}

//////////////////////////////////////////////////////////////////////

CUniversalText::~CUniversalText()
{
	Empty ();
}

//////////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::operator = (const CUniversalText &op)
{
	if (op.m_szwText)
		SetTextW (op.GetTextW ());
	else
		SetTextA (op.GetTextA ());
	m_fPureUnicode = op.m_fPureUnicode;
	return *this;
}

//////////////////////////////////////////////////////////////////////
CUniversalText& CUniversalText::operator = (LPCSTR szText)
{
	SetTextA (szText);
	return *this;
}

//////////////////////////////////////////////////////////////////////
CUniversalText& CUniversalText::operator = (LPCWSTR szText)
{
	SetTextW (szText);
	return *this;
}

void CUniversalText::Empty ()
{
	if (m_szwText)
	{
		FreeMemory (m_szwText);
		m_szwText = NULL;
	}
	if (m_szText)
	{
		FreeMemory (m_szText);
		m_szText = NULL;
	}
	m_fPureUnicode = FALSE;
}

//////////////////////////////////////////////////////////////////////
// Internal text retrieving, Uni/Ansi setup
//////////////////////////////////////////////////////////////////////

LPCSTR CUniversalText::GetTextA () const
{
	if (!m_szText && m_szwText)
		const_cast<LPSTR>(m_szText) = Convert ( m_szwText);
	if (!m_szText)
		return "";
	return m_szText;
}

//////////////////////////////////////////////////////////////////////////

LPCWSTR CUniversalText::GetTextW () const
{
	if (!m_szwText && m_szText)
		const_cast<LPWSTR>(m_szwText) = Convert (m_szText);
	if (!m_szwText)
		return L"";
	return m_szwText;
}

//////////////////////////////////////////////////////////////////////////

void CUniversalText::SetTextA (LPCSTR szText)
{
	if (szText == m_szText)
		return;
	Empty ();
	if (szText != NULL)
	{
		m_szText = Copy (szText);
		m_fPureUnicode = FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////

void CUniversalText::SetTextW (LPCWSTR szwText)
{
	if (szwText == m_szwText)
		return;
	Empty ();
	if (szwText != NULL)
	{
		m_szwText = Copy (szwText);
		m_fPureUnicode = TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::UseAnsi()
{
	if (!m_szText && m_szwText)
		m_szText = Convert (m_szwText);
	if (m_szwText)
	{
		FreeMemory (m_szwText);
		m_szwText = NULL;
	}
	m_fPureUnicode = FALSE;
	return *this;
}

//////////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::UseUnicode()
{
	if (!m_szwText && m_szText)
		m_szwText = Convert (m_szText);
	if (m_szText)
	{
		FreeMemory (m_szText);
		m_szText = NULL;
	}
	return *this;
}

//////////////////////////////////////////////////////////////////////////

bool CUniversalText::IsPureUnicode () const
{
	return (bool) m_fPureUnicode;
}


//////////////////////////////////////////////////////////////////////
// Length and size retrieving, content availablility checking
//////////////////////////////////////////////////////////////////////

DWORD CUniversalText::GetLength () const
{
	if (m_szText)
		return ::strlen (m_szText);
	else if (m_szwText)
		return ::wcslen (m_szwText);
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////

DWORD CUniversalText::GetSizeA () const
{
	GetTextA ();
	if (m_szText)
		return GetLength () + 1;//GetAllocatedSize (m_szText);
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////

DWORD CUniversalText::GetSizeW () const
{
	GetTextW ();
	if (m_szwText)
		return (GetLength () + 1) << 1;//GetAllocatedSize (m_szwText);
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////

bool CUniversalText::IsEmpty () const
{
	if (m_szText)
	{
		if (strlen (m_szText) > 0)
			return FALSE;
		else
			return TRUE;
	}
	else if (m_szwText)
	{
		if (wcslen (m_szwText) > 0)
			return FALSE;
		else
			return TRUE;
	}
	else
		return TRUE;
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Type-cast overloads
//////////////////////////////////////////////////////////////////////

CUniversalText::operator LPSTR () const
{
	return const_cast<LPSTR>(GetTextA ());		// !!!!!!!!!!!!!!!!!!
}

//////////////////////////////////////////////////////////////////////

CUniversalText::operator LPWSTR () const
{
	return const_cast<LPWSTR>(GetTextW ());
}

//////////////////////////////////////////////////////////////////////////
// String persistence: Loading/Saving methods
//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::Save (CswFile &File, BOOL fForceUNICODE)
{
	BYTE fUniText = IsPureUnicode () || fForceUNICODE;
	if (File.Write (&fUniText, sizeof(fUniText)) == EOF)
		return FALSE;
	
	if (fUniText)
		GetTextW ();
	else
		GetTextA ();

	DWORD dwSize = fUniText ? GetSizeW () : GetSizeA ();
	if (File.Write (&dwSize, sizeof (dwSize)) == EOF)
		return FALSE;
	
	if (dwSize != NULL)
		if (File.Write (fUniText ? (LPVOID) m_szwText : (LPVOID) m_szText, dwSize) == EOF)
			return FALSE;
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////

BOOL CUniversalText::Load (CswFile &File)
{	
	Empty ();

	BYTE fUniText;
	if (File.Read (&fUniText, sizeof(fUniText)) == EOF)
		return FALSE;
	
	DWORD dwSize;
	if (File.Read (&dwSize, sizeof (dwSize)) == EOF)
		return FALSE;
	
	if (dwSize != NULL)
	{
		LPVOID pvData = AllocateMemory (dwSize);
		if (!pvData)
			return FALSE;
		if (fUniText)
			m_szwText = static_cast<LPWSTR>(pvData);
		else
			m_szText = static_cast<LPSTR>(pvData);
		if (File.Read (pvData, dwSize) != dwSize)
		{
			Empty ();
			return FALSE;
		}
		m_fPureUnicode = fUniText ? true : false;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::SaveAsPlain (CswFile &File, DWORD dwSize, BOOL fUnicode)
{
	if (IsEmpty ())
		return TRUE;
	DWORD dwMySize = fUnicode ? GetSizeW () - 2 : GetSizeA () - 1;
	if (dwSize > dwMySize)
		dwSize = dwMySize;
	if (fUnicode)
	{
		GetTextW ();
		if (File.Write (m_szwText, dwSize) == EOF)
			return FALSE;
	}
	else
	{
		GetTextA ();
		if (File.Write (m_szText, dwSize) == EOF)
			return FALSE;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::LoadAsPlain (CswFile &File, DWORD dwSize, BOOL fUnicode)
{
	Empty ();
	DWORD dwMySize = File.GetFileSize ();
	if (dwSize > dwMySize)
		dwSize = dwMySize;
	if (dwSize == -1)
		return FALSE;
	if (!dwSize)
		return TRUE;

	if (fUnicode)
	{
		m_szwText = (LPWSTR) AllocateMemory (dwSize + 2);
		if (!m_szwText)
			return FALSE;
		if (File.Read (m_szwText, dwSize) != -1)
		{
			m_szwText [(dwSize) >> 1] = L'\0';
			m_fPureUnicode = true;		
		}
		else
		{
			FreeMemory (m_szwText);
			m_szwText = NULL;
			return FALSE;
		}
	}
	else
	{
		m_szText = (LPSTR) AllocateMemory (dwSize + 1);
		if (!m_szText)
			return FALSE;
		if (File.Read (m_szText, dwSize) != -1)
		{
			m_szText [dwSize] = '\0';
		}
		else
		{
			FreeMemory (m_szText);
			m_szText = NULL;
			return FALSE;
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::SaveAsLine (CswFile &File, BOOL fUnicode)
{
	CUniversalText utLine;
	utLine = (*this) + g_szCRLF;
	return utLine.SaveAsPlain (File, EOF, fUnicode);
}

//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::LoadAsLine (CswFile &File, BOOL fUnicode)
{
	Empty ();

	if (File.Seek (0, FILE_CURRENT) >= File.GetFileSize ()) // EOF
		return FALSE;

	CswFile StringFile;
	if (!StringFile.OpenRAM ())
		return FALSE;
	
	static WCHAR wchNULL = L'\0';
	static CHAR chNULL = '\0';
	
	BYTE cSpots = 0;

	if (fUnicode)
	{
		WCHAR wchIn;
		WCHAR wchLastSpot = L'\0';
		BOOL fEOF = true;
		while (File.Read (&wchIn, sizeof (wchIn)) != EOF)
		{
			if (wchIn == g_szwCRLF[0] || wchIn == g_szwCRLF[1])
			{
				cSpots++;
				if (wchIn == wchLastSpot)
				{
					File.Seek (-static_cast<INT>(sizeof(wchIn)), FILE_CURRENT);
					break;
				}
				if (cSpots == 2)
					break;
				wchLastSpot = wchIn;
			}
			else
			{
				if (cSpots)
				{
					File.Seek (-static_cast<INT>(sizeof(wchIn)), FILE_CURRENT);
					break;
				}
				StringFile.Write (&wchIn, sizeof (wchIn));
			}
		}
		StringFile.Write (&wchNULL, sizeof(wchNULL));
	}
	else
	{
		CHAR chIn;
		CHAR chLastSpot = L'\0';
		while (File.Read (&chIn, sizeof (chIn)) != EOF)
		{
			if (chIn == g_szCRLF[0] || chIn == g_szwCRLF[1])
			{
				cSpots++;
				if (chIn == chLastSpot)
				{
					File.Seek (-static_cast<INT>(sizeof(chIn)), FILE_CURRENT);
					break;
				}
				if (cSpots == 2)
					break;
				chLastSpot = chIn;
			}
			else
			{
				if (cSpots)
				{
					File.Seek (-static_cast<INT>(sizeof(chIn)), FILE_CURRENT);
					break;
				}
				StringFile.Write (&chIn, sizeof (chIn));
			}
		}
		StringFile.Write (&chNULL, sizeof(chNULL));
	}
	

	DWORD dwReadSize = StringFile.GetFileSize ();
	LPVOID pvRead;
	LPVOID pvPrivate = AllocateMemory (dwReadSize);
	DWORD dwFileSize = StringFile.GetFileSize ();
	StringFile.ExtractBuffer (&pvRead);
	memcpy (pvPrivate, pvRead, dwReadSize);
	StringFile.Close ();

	if (fUnicode)
		m_szwText = (LPWSTR) pvPrivate;
	else 
		m_szText = (LPSTR) pvPrivate;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// UNICODE-ANSI conversions
//////////////////////////////////////////////////////////////////////////

void CUniversalText::ConvertANSItoUNICODE (LPWSTR szTarget, LPCSTR szAnsiStr, DWORD cbTarget) 
{
	MultiByteToWideChar(CP_ACP,0,szAnsiStr,-1,szTarget,cbTarget);
}

//////////////////////////////////////////////////////////////////////////

void CUniversalText::ConvertUNICODEtoANSI (LPSTR szTarget, LPCWSTR szUniStr, DWORD cbTarget) 
{
	WideCharToMultiByte(CP_ACP,0,szUniStr,-1,szTarget,cbTarget,NULL,NULL);
}

//////////////////////////////////////////////////////////////////////////

LPWSTR CUniversalText::Convert (LPCSTR szAnsiStr) 
{
	DWORD dwBytes = (strlen (szAnsiStr) + 1) << 1;
	LPWSTR lpTarget = (LPWSTR) AllocateMemory (dwBytes);
	ConvertANSItoUNICODE (lpTarget,  szAnsiStr, dwBytes);
	return lpTarget;
}

//////////////////////////////////////////////////////////////////////////

LPSTR CUniversalText::Convert (LPCWSTR szUniStr)
{
	DWORD dwBytes = wcslen (szUniStr) + 1;
	LPSTR lpTarget = (LPSTR) AllocateMemory (dwBytes);
	ConvertUNICODEtoANSI (lpTarget,  szUniStr, dwBytes);
	return lpTarget;
}

//////////////////////////////////////////////////////////////////////

LPSTR CUniversalText::Copy (LPCSTR szAnsiStr)
{
	if (!szAnsiStr)
		return NULL;
	DWORD dwBytes = strlen (szAnsiStr) + 1;
	LPSTR lpTarget = (LPSTR) AllocateMemory (dwBytes);
	memcpy (lpTarget, szAnsiStr, dwBytes);
	return lpTarget;
}

//////////////////////////////////////////////////////////////////////////

LPWSTR CUniversalText::Copy (LPCWSTR szUniStr)
{
	if (!szUniStr)
		return NULL;
	DWORD dwBytes = (wcslen(szUniStr) + 1) << 1;
	LPWSTR lpTarget = (LPWSTR) AllocateMemory (dwBytes);
	memcpy (lpTarget, szUniStr, dwBytes);
	return lpTarget;
}

//////////////////////////////////////////////////////////////////////////
// Memory management
//////////////////////////////////////////////////////////////////////

LPVOID CUniversalText::AllocateMemory (DWORD dwBytes)
{
	return HeapAlloc (m_hHeap, 0, dwBytes);
	//return malloc (dwBytes);
}

//////////////////////////////////////////////////////////////////////

LPVOID CUniversalText::ReAllocateMemory (DWORD dwBytes, LPVOID pvPointer)
{
//	LPVOID pvNew = HeapAlloc (m_hHeap, 0, dwBytes);
//	memcpy (pvNew, pvPointer, GetAllocatedSize (pvPointer));
//	FreeMemory (pvPointer);
//	return pvNew;
	return HeapReAlloc (m_hHeap, 0, pvPointer, dwBytes);
	//return realloc (pvPointer, dwBytes);
}

//////////////////////////////////////////////////////////////////////

void CUniversalText::FreeMemory (LPVOID pvPointer)
{
	HeapFree (m_hHeap, 0, pvPointer);
	//free (pvPointer);
}

//////////////////////////////////////////////////////////////////////

DWORD CUniversalText::GetAllocatedSize (LPVOID pvPointer)
{
	return HeapSize (m_hHeap, 0, pvPointer);
	//return _msize (pvPointer);
}

//////////////////////////////////////////////////////////////////////
// Comparison (==) operators
//////////////////////////////////////////////////////////////////////

bool operator == (const CUniversalText &op1, const CUniversalText &op2)
{
	{
		// Check 4 empties
#		pragma warning(disable: 4800)
		bool f1 = op1.IsEmpty ();
		bool f2 = op2.IsEmpty ();
#		pragma warning(default: 4800)
		if (f1 || f2)
			return  (f1 && f2);
	}

	if (op1.IsPureUnicode () || op2.IsPureUnicode ())
		return (::wcscmp (op1, op2) == 0);
	else
		return (::strcmp (op1, op2) == 0);
}

bool operator < (const CUniversalText &op1, const CUniversalText &op2)
{
	// Check 4 empties
	bool f1 = op1.IsEmpty ();
	bool f2 = op2.IsEmpty ();
	if (f1 && !f2)
		return  true;
	if (!f1 && !f2)
	{
		if (op1.IsPureUnicode () || op2.IsPureUnicode ())
			return (::wcscmp (op1, op2) < 0);
		else
			return (::strcmp (op1, op2) < 0);
	}
	return false;			
}



bool operator > (const CUniversalText &op1, const CUniversalText &op2)
{
	// Check 4 empties
	bool f1 = op1.IsEmpty ();
	bool f2 = op2.IsEmpty ();
	if (!f1 && f2)
		return  true;
	if (!f1 && !f2)
	{
		if (op1.IsPureUnicode () || op2.IsPureUnicode ())
			return (::wcscmp (op1, op2) > 0);
		else
			return (::strcmp (op1, op2) > 0);
	}
	return false;			
}


//////////////////////////////////////////////////////////////////////

BOOL CUniversalText::CaseInsensitiveCompare(const CUniversalText& utCompareWith) const
{
	{
		// Check 4 empties
#pragma warning(disable: 4800)
		bool f1 = IsEmpty ();
		bool f2 = utCompareWith.IsEmpty ();
#pragma warning(default: 4800)
		if (f1 || f2)
			return  (f1 && f2);
	}

	if (IsPureUnicode () || utCompareWith.IsPureUnicode ())
		return (::wcsicmp (GetTextW (), utCompareWith) == 0);
	else
		return (::stricmp (GetTextA (), utCompareWith) == 0);
}

//////////////////////////////////////////////////////////////////////

bool operator != (const CUniversalText &op1, const CUniversalText &op2)
{
	return !(op1 == op2);
}

//////////////////////////////////////////////////////////////////////
// Concatenation (+=, +) operators
//////////////////////////////////////////////////////////////////////

void CUniversalText::ConcatenateWith (const CUniversalText& utText)
{
	// Check 4 empties
	if (utText.IsEmpty ())
		return;
	if (IsEmpty ())
	{
		(*this) = utText;
		return;
	}
	
	if (m_fPureUnicode || utText.IsPureUnicode ())
		ConcatenateWith (utText.GetTextW ());
	else
		ConcatenateWith (utText.GetTextA ());
}

//////////////////////////////////////////////////////////////////////

void CUniversalText::ConcatenateWith (LPCWSTR szwText)
{
	if (IsEmpty ())
		SetTextW (szwText);
	else
	{
		UseUnicode ();
		DWORD dwBytes = GetSizeW () + ((wcslen (szwText)) << 1);
		m_szwText = (LPWSTR) ReAllocateMemory (dwBytes, m_szwText);
		wcscat (m_szwText, szwText);
	}
	if (!IsEmpty ())
		m_fPureUnicode = TRUE;
}

//////////////////////////////////////////////////////////////////////

void CUniversalText::ConcatenateWith (LPCSTR szText)
{
	if (IsEmpty ())
		SetTextA (szText);
	else
		if (m_fPureUnicode)
		{
			UseUnicode ();
			LPWSTR szwText = Convert (szText);
			ConcatenateWith (szwText);
			FreeMemory (szwText);			
		}
		else
		{
			UseAnsi ();
			DWORD dwBytes = GetSizeA () + strlen (szText);
			m_szText = (LPSTR) ReAllocateMemory (dwBytes, m_szText);
			strcat (m_szText, szText);
		}
}

//////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::operator += (const CUniversalText &op)
{
	ConcatenateWith (op);
	return *this;
}

//////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::operator += (LPCSTR szText)
{
	ConcatenateWith (szText);
	return *this;
}

//////////////////////////////////////////////////////////////////////

CUniversalText& CUniversalText::operator += (LPCWSTR szText)
{
	ConcatenateWith (szText);
	return *this;
}

//////////////////////////////////////////////////////////////////////
CUniversalText operator + (const CUniversalText& op1, const CUniversalText& op2)
{
	CUniversalText utNew = op1;
	utNew += op2;
	return utNew;
}

//////////////////////////////////////////////////////////////////////

CUniversalText operator + (const CUniversalText& op1, LPCSTR szText)
{
	CUniversalText utNew = op1;
	utNew += szText;
	return utNew;
}

//////////////////////////////////////////////////////////////////////

CUniversalText operator + (const CUniversalText& op1, LPCWSTR szwText)
{
	CUniversalText utNew = op1;
	utNew += szwText;
	return utNew;
}

//////////////////////////////////////////////////////////////////////

CUniversalText operator + (LPCSTR szText, const CUniversalText& op1)
{
	CUniversalText utNew = szText;
	utNew += op1;
	return utNew;
}

//////////////////////////////////////////////////////////////////////

CUniversalText operator + (LPCWSTR szwText, const CUniversalText& op1)
{
	CUniversalText utNew = szwText;
	utNew += op1;
	return utNew;
}

//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Formatting (printf-like)
//////////////////////////////////////////////////////////////////////

CUniversalText& __cdecl CUniversalText::Format (CUniversalText utFormat, ...)
{
	va_list argList;
	va_start(argList, utFormat);
	FormatV(utFormat, argList);
	va_end(argList);
	return *this;
}

//////////////////////////////////////////////////////////////////////
CUniversalText& __cdecl CUniversalText::FormatV (CUniversalText utFormat, va_list argList)
{
	Empty ();
	m_fPureUnicode = utFormat.IsPureUnicode ();
	if (utFormat.IsEmpty ())
		return *this;

	va_list argListSave = argList;

	if (utFormat.m_szwText)
	{
		int nLen = utFormat.GetSizeW () + 4096;
		m_szwText = (LPWSTR) AllocateMemory (nLen);
		int i;
		while ((i = _vsnwprintf(m_szwText, nLen, utFormat, argListSave)) == nLen)
		{
			nLen <<= 1;
			m_szwText = (LPWSTR) ReAllocateMemory (nLen, m_szwText);
		};
		
		m_szwText = (LPWSTR) ReAllocateMemory ((i + 1) << 1, m_szwText);
	}
	else
	{
		int nLen = utFormat.GetSizeA () + 2048;
		m_szText = (LPSTR) AllocateMemory (nLen);
		int i;
		while ((i = _vsnprintf(m_szText, nLen, utFormat, argListSave)) == nLen)
		{
			nLen <<= 1;
			m_szText = (LPSTR) ReAllocateMemory (nLen, m_szText);
		};
		
		m_szText = (LPSTR) ReAllocateMemory (i + 1, m_szText);
	}
	va_end(argListSave);
	return *this;
}


//////////////////////////////////////////////////////////////////////
// Find operations
//////////////////////////////////////////////////////////////////////

int CUniversalText::Find (CUniversalText utToFind, int nPos) const
{
	if (m_fPureUnicode || utToFind.IsPureUnicode ())
	{
		GetTextW ();
		LPWSTR szwStart = m_szwText + nPos;
		LPWSTR szwFound = wcsstr (szwStart, utToFind);
		return szwFound ? (szwFound - m_szwText) : -1;
	}
	else
	{
		GetTextA ();
		LPSTR szStart = m_szText + nPos;
		LPSTR szFound = strstr (szStart, utToFind);
		return szFound ? (szFound - m_szText) : -1;
	}
}

//////////////////////////////////////////////////////////////////////

int CUniversalText::FindCHAR (CHAR chToFind, int nPos) const
{
	GetTextA ();
	LPSTR szStart = m_szText + nPos;
	LPSTR szFound = strchr (szStart, chToFind);
	return szFound ? (szFound - m_szText) : -1;
}

//////////////////////////////////////////////////////////////////////

int	CUniversalText::FindWCHAR (WCHAR wcToFind,int nPos) const
{
	GetTextW ();
	LPWSTR szwStart = m_szwText + nPos;
	LPWSTR szwFound = wcschr (szwStart, wcToFind);
	return szwFound ? (szwFound - m_szwText) : -1;
}

//////////////////////////////////////////////////////////////////////
// Additional services like Insert, Delete, Left, Right etc.
//////////////////////////////////////////////////////////////////////

void CUniversalText::Delete(int count,int pos)
{
	if (IsEmpty ())
		return;
	if (m_fPureUnicode)
	{
		UseUnicode ();
		LPWSTR szwDest = m_szwText + pos;
		LPWSTR szwSource = szwDest + count;
		wcscpy (szwDest, szwSource);
		DWORD dwNewSize = (GetLength () + 1) << 1;
		m_szwText = (LPWSTR) ReAllocateMemory (dwNewSize, m_szwText);
	}
	else
	{
		UseAnsi ();
		LPSTR szDest = m_szText + pos;
		LPSTR szSource = szDest + count;
		strcpy (szDest, szSource);
		DWORD dwNewSize = (GetLength () + 1);
		m_szText = (LPSTR) ReAllocateMemory (dwNewSize, m_szText);
	}
}

//////////////////////////////////////////////////////////////////////

CUniversalText CUniversalText::Left (int count) const
{
	CUniversalText utNew = *this;
	register DWORD dwLen = utNew.GetLength () - count;
	utNew.Delete (dwLen, count);
	return utNew;
}

////////////////////////////////////////////////////////////////////////

CUniversalText CUniversalText::Right(int count) const
{
	CUniversalText utNew = *this;
	register DWORD dwLen = utNew.GetLength () - count;
	utNew.Delete (dwLen, 0);
	return utNew;	
}
//////////////////////////////////////////////////////////////////////

CUniversalText CUniversalText::Mid (int nFirst, int count) const
{
	CUniversalText utNew = *this;
	utNew = utNew.Left (nFirst + count);
	utNew = utNew.Right (count);
	return utNew;		
}

//////////////////////////////////////////////////////////////////////

int CUniversalText::Insert (int nIndex, CUniversalText utStr)
{
	if (static_cast <DWORD> (nIndex) > GetLength ())
		nIndex = GetLength ();
	CUniversalText utLeft = Left (nIndex);
	CUniversalText utRight = Right (GetLength () - nIndex);
	*this = utLeft + utStr + utRight;
	return GetLength ();
}
void CUniversalText::MakeUpper()
{
	if (IsEmpty ())
		return;
	if (m_fPureUnicode)
	{
		UseUnicode ();
		_wcsupr (m_szwText);
	}
	else
	{
		UseAnsi ();
		strupr (m_szText);
	}
}

//////////////////////////////////////////////////////////////////////
void CUniversalText::MakeLower()
{
	if (IsEmpty ())
		return;
	if (m_fPureUnicode)
	{
		UseUnicode ();
		_wcslwr (m_szwText);
	}
	else
	{
		UseAnsi ();
		strlwr (m_szText);
	}
}

//////////////////////////////////////////////////////////////////////
void GetWindowTextUT (IN HWND hWnd, IN OUT CUniversalText &utString)
{
	INT nLen = GetWindowTextLength (hWnd) + 1;
	if (nLen <= 1)
		utString.Empty ();
	else
		if (IsWindowUnicode (hWnd))
		{	
			LPWSTR szwString = new WCHAR [nLen];
			GetWindowTextW (hWnd, szwString, nLen);
			utString = szwString;
			delete szwString;
		}
		else
		{
			LPSTR szString = new CHAR [nLen];
			GetWindowTextA (hWnd, szString, nLen);
			utString = szString;
			delete szString;
		}
}


//////////////////////////////////////////////////////////////////////

DWORD CUniversalText::GetHashKey() const
{
	DWORD dwHash = 0;

	if (IsEmpty ())
		return 0;

	GetTextW ();

	if (m_szwText)
	{
		LPWSTR szwText = m_szwText;
		while (*szwText)
			dwHash = (dwHash<<5) + dwHash + *szwText++;
	}
	
	return dwHash;
}
//////////////////////////////////////////////////////////////////////

WCHAR CUniversalText::GetWCHAR(UINT nPos) const
{
	if (IsEmpty () || nPos >= GetLength ())
		return L'\0';
	GetTextW ();
	return m_szwText [nPos];
}

//////////////////////////////////////////////////////////////////////

CHAR CUniversalText::GetCHAR(UINT nPos) const
{
	if (IsEmpty () || nPos >= GetLength ())
		return '\0';
	GetTextA ();
	return m_szText [nPos];
}


UINT CUniversalText::Explode (const CUniversalText& utSplitter, CswUTArray& pieces, 
							 BOOL fIngnoreEmpty) const
{
	int nBeg = 0, nPos = 0;
	CUniversalText utPiece;
	while ((nPos = Find (utSplitter, nBeg)) != -1)
	{
		utPiece = Mid (nBeg, nPos - nBeg);
		if (!fIngnoreEmpty || !utPiece.IsEmpty ())
			pieces.Push (utPiece);
		nBeg = nPos + utSplitter.GetLength();
	}
	utPiece = Right (GetLength() - nBeg);
	if (!fIngnoreEmpty || !utPiece.IsEmpty ())
		pieces.Push (utPiece);
	return pieces.Count();
}

CUniversalText CswUTArray::Implode (const CUniversalText& utGlue, BOOL fIngnoreEmpty) const
{
	CUniversalText utRes;
	for (UINT i = 0; i < Count () ; i++)
	{
		CUniversalText& utPiece = const_cast<CswUTArray&>(*this)[i];
		if (!fIngnoreEmpty || !utPiece.IsEmpty ())
			utRes += utPiece;
		if (Count () - i > 1)
			utRes += utGlue;
	}
	return utRes;
}

CUniversalText CUniversalText::DoubleWidth() const
{
	CUniversalText utNew;
	if (!IsEmpty ())
	{
		utNew.m_fPureUnicode = m_fPureUnicode;
		if (m_szwText)
		{
			utNew.m_szwText = (LPWSTR) AllocateMemory ((GetSizeW () << 1) - 2);
			LPWSTR szwThisTxt = m_szwText;
			LPWSTR szwNewTxt = utNew.m_szwText;
			while (*szwThisTxt)
			{
				*szwNewTxt = *szwThisTxt; szwNewTxt++;
				*szwNewTxt = *(++szwThisTxt) ? L' ' : L'\0'; szwNewTxt++;
			}
		}
		else
		{

			utNew.m_szText = (LPSTR) AllocateMemory ((GetSizeA () << 1) - 2);
			LPSTR szThisTxt = m_szText;
			LPSTR szNewTxt = utNew.m_szText;
			while (*szThisTxt)
			{
				*szNewTxt = *szThisTxt; szNewTxt++;
				*szNewTxt = *(++szThisTxt) ? ' ' : '\0'; szNewTxt++;
			}
		}
	}
	return utNew;
}

CUniversalText CUniversalText::Reverse() const
{
	CUniversalText utOut = (*this);
	int len = utOut.GetLength();
	if (utOut.m_szwText)
	{
		utOut.UseUnicode();
		for( int i = 0; i < ( len >> 1 ); i++ )
		{
			utOut.m_szwText[i] = m_szwText[len - i - 1];
			utOut.m_szwText[len - i - 1] = m_szwText[i];
		}
	}
	else
	{
		utOut.UseAnsi();
		for( int i = 0; i < ( len >> 1 ); i++ )
		{
			utOut.m_szText[i] = m_szText[len - i - 1];
			utOut.m_szText[len - i - 1] = m_szText[i];
		}
	}
	return utOut;
}
