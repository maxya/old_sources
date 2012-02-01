// UniversalText.h: interface for the CUniversalText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNIVERSALTEXT_H__41CDEA32_972B_4258_BC49_5A2376810C66__INCLUDED_)
#define AFX_UNIVERSALTEXT_H__41CDEA32_972B_4258_BC49_5A2376810C66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "swMap.h"

class CswUTArray;
class CswFile;
class CUniversalText  
{
public:
	BOOL CaseInsensitiveCompare (const CUniversalText& utCompareWith) const;
	DWORD GetHashKey () const; 
	CUniversalText ();
	CUniversalText (const CUniversalText& utSrc);
	CUniversalText (LPCWSTR szText);
	CUniversalText (LPCSTR szText);

	virtual ~CUniversalText ();

	DWORD GetLength () const;
	bool IsEmpty() const;
	void Empty ();
	
	DWORD GetSizeA () const;
	DWORD GetSizeW () const;
	
	CUniversalText& UseAnsi ();
	CUniversalText& UseUnicode ();

	bool IsPureUnicode () const;

	CUniversalText& __cdecl Format (CUniversalText utFormat, ...);
	CUniversalText& __cdecl FormatV (CUniversalText utFormat, va_list argList);

	void MakeLower();
	void MakeUpper();
	
	BOOL Save (CswFile &File, BOOL fForceUNICODE = FALSE);
	BOOL Load (CswFile &File);

	BOOL SaveAsPlain (CswFile &File, DWORD dwSize = EOF, BOOL fUnicode = TRUE);
	BOOL LoadAsPlain (CswFile &File, DWORD dwSize = EOF, BOOL fUnicode = TRUE);
	
	BOOL SaveAsLine (CswFile &File, BOOL fUnicode = TRUE);
	BOOL LoadAsLine (CswFile &File, BOOL fUnicode = TRUE);

	CUniversalText& operator = (const CUniversalText &op);
	CUniversalText& operator = (LPCSTR szText);
	CUniversalText& operator = (LPCWSTR szText);

	CUniversalText& operator += (const CUniversalText &op);
	CUniversalText& operator += (LPCSTR szText);
	CUniversalText& operator += (LPCWSTR szText);

	friend CUniversalText operator + (const CUniversalText& op1, const CUniversalText& op2);
	friend CUniversalText operator + (const CUniversalText& op1, LPCSTR szText);
	friend CUniversalText operator + (const CUniversalText& op1, LPCWSTR szwText);
	friend CUniversalText operator + (LPCSTR szText, const CUniversalText& op1);
	friend CUniversalText operator + (LPCWSTR szwText, const CUniversalText& op1);
	
	operator LPSTR () const;
	operator LPWSTR () const;

	//operator UINT ();

	WCHAR	GetWCHAR	(UINT nPos = 0) const;
	CHAR	GetCHAR		(UINT nPos = 0) const;
	
	int		Find (CUniversalText utToFind,int nPos = 0) const;
	int		FindCHAR (CHAR chToFind, int nPos = 0) const;
	int		FindWCHAR (WCHAR wcToFind, int nPos = 0) const;

	CUniversalText	Left (int count) const;
	CUniversalText	Right (int count) const;
	CUniversalText	Mid (int nFirst, int count) const;

	int		Insert (int nIndex, CUniversalText utStr);
	void	Delete (int count=1, int pos=0);

	UINT Explode(const CUniversalText& utSplitter, CswUTArray& pieces, BOOL fIngnoreEmpty = FALSE) const;
	
	// Inserts space after every symbol except last
	CUniversalText DoubleWidth () const;
	CUniversalText Reverse() const;

protected:
	LPWSTR m_szwText;
	LPSTR m_szText;
	static HANDLE m_hHeap;
	static LPSTR g_szCRLF;
	static LPWSTR g_szwCRLF;
	bool m_fPureUnicode;
protected:
	void Init ();
	
	LPCSTR GetTextA () const;
	LPCWSTR GetTextW () const;

	void SetTextA (LPCSTR szText);
	void SetTextW (LPCWSTR szwText);
	
	// concatenation
	void ConcatenateWith (const CUniversalText& utText);
	void ConcatenateWith (LPCWSTR szwText);
	void ConcatenateWith (LPCSTR szText);

	// Memory management
	static LPVOID AllocateMemory (DWORD dwBytes);
	static LPVOID ReAllocateMemory (DWORD dwBytes, LPVOID pvPointer);
	static void FreeMemory (LPVOID pvPointer);
	static DWORD GetAllocatedSize (LPVOID pvPointer);

	// Simple conversions
	static void ConvertANSItoUNICODE (LPWSTR szwTarget, LPCSTR szStr, DWORD cbTarget);
	static void ConvertUNICODEtoANSI (LPSTR szTarget, LPCWSTR szwStr, DWORD cbTarget);

	// Operations with allocations
	static LPWSTR Convert (LPCSTR szStr);
	static LPSTR Convert (LPCWSTR szwStr);

	static LPSTR Copy (LPCSTR szStr);
	static LPWSTR Copy (LPCWSTR szwStr);

};

typedef CUniversalText UNIVERSALTEXT, *LPUNIVERSALTEXT, UTEXT, *PUTEXT;

bool operator == (const CUniversalText &op1, const CUniversalText &op2);
bool operator != (const CUniversalText &op1, const CUniversalText &op2);
bool operator < (const CUniversalText &op1, const CUniversalText &op2);
bool operator > (const CUniversalText &op1, const CUniversalText &op2);

// UT Array - class used in explode/implode operations
class CswUTArray : public CswArray<CUniversalText>
{
public:
	CswUTArray()											{  	}
	CswUTArray(UINT uBucketArrayLength)						{   }
	CswUTArray(const CswArray<CUniversalText> &swMap)		{ (*this) += swMap; }
	CswUTArray(const CswMap<UINT, CUniversalText> &swMap)	{ (*this) += swMap; }

	CUniversalText Implode (const CUniversalText& utGlue, BOOL fIngnoreEmpty = FALSE) const;

	CswUTArray& operator = (const CswUTArray& swMap)		{ Clear ();	return (*this) += swMap; }
	CswUTArray& operator += (const CswUTArray& swMap)		
	{ 
		(*static_cast< CswArray<CUniversalText>* >(this)) +=  
			static_cast< CswArray<CUniversalText> > (swMap);
		return (*this);
	}
	CswUTArray& operator += (const CswArray<CUniversalText>& swMap)		
	{ 
		(*static_cast< CswArray<CUniversalText>* >(this)) += swMap;
		return (*this);
	}
	CswUTArray& operator += (const CswMap<UINT, CUniversalText>& swMap)		
	{ 
		(*static_cast< CswArray<CUniversalText>* >(this)) += swMap;
		return (*this);
	}
	
	friend CswUTArray operator + (const CswUTArray& op1, const CswUTArray& op2)
	{
		CswUTArray res = op1;
		res += op2;
		return res;
	}
};

//////////////////////////////////////////////////////////////////////
// CswMap support
inline UINT HashIt(const CUniversalText& utText)
{
	return const_cast<CUniversalText&>(utText).GetHashKey ();
}


#endif // !defined(AFX_UNIVERSALTEXT_H__41CDEA32_972B_4258_BC49_5A2376810C66__INCLUDED_)
