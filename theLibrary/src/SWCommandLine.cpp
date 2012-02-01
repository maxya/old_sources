// SWCommandLine.cpp: implementation of the CSWCommandLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SWCommandLine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSWCommandLine::CSWCommandLine()
{

}

CSWCommandLine::CSWCommandLine(CUniversalText utCommandLine)
{
	Parse (utCommandLine);
}

CSWCommandLine::~CSWCommandLine()
{
	Cleanup ();
}

//////////////////////////////////////////////////////////////////////
// =
//////////////////////////////////////////////////////////////////////

CSWCommandLine& CSWCommandLine::operator = (CUniversalText utCommandLine)
{
	Parse (utCommandLine);
	return *this;
}

//////////////////////////////////////////////////////////////////////
// Internals
//////////////////////////////////////////////////////////////////////

void CSWCommandLine::Cleanup ()
{
	while (m_rgputAll.Count () > 0)
	{
		delete m_rgputAll[0];
		m_rgputAll.Remove (0);
	}
	m_rgputFormal.Empty ();
	m_rgputKeys.Empty ();
}

//////////////////////////////////////////////////////////////////////

void CSWCommandLine::Parse (CUniversalText utCmdLine)
{
	Cleanup ();
	static CUniversalText utDelimiters = L" \t\r\n";
	
	UINT uBeg = 0, uEnd = 0, uLen; 
	bool fQuoteOpened = false, fTrimmed = false;

	while (uEnd <= (uLen = utCmdLine.GetLength ()))
	{
		if (uEnd == uLen || (utDelimiters.FindWCHAR (utCmdLine.GetWCHAR (uEnd)) != -1 && !fQuoteOpened))
		{
			if (fTrimmed)
			{
				CUniversalText* pNewWord;
				pNewWord = new CUniversalText (utCmdLine.Mid (uBeg, uEnd - uBeg));

				m_rgputAll.Add (pNewWord);
				if (IsKey (*pNewWord))
					m_rgputKeys.Add ((pNewWord));
				else
					m_rgputFormal.Add (pNewWord);
			}
			fTrimmed = false;
			uBeg = uEnd;
		}
		else
		{
			if (utCmdLine.GetWCHAR (uEnd) == L'"')
			{
				fQuoteOpened = !fQuoteOpened;
				utCmdLine.Delete (1, uEnd);
				continue;
			}
			else
			{
				if (!fTrimmed)
				{
					uBeg = uEnd;
					fTrimmed = true;
				}
			}
		}
		uEnd++;
	}
}

//////////////////////////////////////////////////////////////////////

BOOL CSWCommandLine::IsKey (CUniversalText utToCheck)
{
	static CUniversalText utKeyBegins = "-/";
	if (utKeyBegins.FindWCHAR (utToCheck.GetWCHAR ()) != -1)
		return TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Все параметры 
//////////////////////////////////////////////////////////////////////

UINT CSWCommandLine::GetParametersCount ()
{
	return m_rgputAll.Count ();
}

//////////////////////////////////////////////////////////////////////

CUniversalText CSWCommandLine::GetParameter (UINT uIdx)
{
	return *(m_rgputAll.Item (uIdx));
}

//////////////////////////////////////////////////////////////////////
// Ключи (начинаются с '/' или '-' и заканчиваются разделителями)
//////////////////////////////////////////////////////////////////////

UINT CSWCommandLine::GetKeysCount ()
{
	return m_rgputKeys.Count ();
}

//////////////////////////////////////////////////////////////////////

CUniversalText CSWCommandLine::GetKey (UINT uIdx)
{
	CUniversalText* pKey = m_rgputKeys.Item (uIdx);
	return pKey->Right (pKey->GetLength () - 1);
}

//////////////////////////////////////////////////////////////////////
// Остальные параметры
//////////////////////////////////////////////////////////////////////

UINT CSWCommandLine::GetFormalParametersCount ()
{
	return m_rgputFormal.Count ();
}

//////////////////////////////////////////////////////////////////////

CUniversalText CSWCommandLine::GetFormalParameter (UINT uIdx)
{
	return *(m_rgputFormal.Item (uIdx));
}
