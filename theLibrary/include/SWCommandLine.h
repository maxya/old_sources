// SWCommandLine.h: interface for the CSWCommandLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWCOMMANDLINE_H__238135ED_EAAB_4699_8D68_3B960279DE00__INCLUDED_)
#define AFX_SWCOMMANDLINE_H__238135ED_EAAB_4699_8D68_3B960279DE00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UniversalText.h"
#include "SWLists.h"

class CSWCommandLine  
{
public:
	CSWCommandLine();
	CSWCommandLine(CUniversalText utCommandLine);
	virtual ~CSWCommandLine();

public:
	CSWCommandLine& operator = (CUniversalText utCommandLine);
	
	void Cleanup ();

	// Все параметры 
	//(разделители 0x20, \t, \n, \r, кроме случаев, когда они в "")
	UINT GetParametersCount ();		
	CUniversalText GetParameter (UINT uIdx);

	// Ключи (начинаются с '/' или '-' и заканчиваются разделителями)
	UINT GetKeysCount ();
	CUniversalText GetKey (UINT uIdx);

	// Остальные параметры
	UINT GetFormalParametersCount ();
	CUniversalText GetFormalParameter (UINT uIdx);
	
protected:
	void Parse (CUniversalText utCmdLine);
	BOOL IsKey (CUniversalText utToCheck);
	
	CSWOneWayList<CUniversalText*> m_rgputAll;
	CSWOneWayList<CUniversalText*> m_rgputKeys;
	CSWOneWayList<CUniversalText*> m_rgputFormal;
	// All parameters
};

#endif // !defined(AFX_SWCOMMANDLINE_H__238135ED_EAAB_4699_8D68_3B960279DE00__INCLUDED_)
