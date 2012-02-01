#include "StdAfx.h"
#include "swConfig.h"
#include "swINIworks.h"

CswConfig::CswConfig(void) :
	m_mpConfig()
{
}

CswConfig::~CswConfig(void)
{
}

int CswConfig::Load(SWFILE& file)
{
	return (int) swParseINIFile( file, m_mpConfig );
}

int CswConfig::Save(SWFILE& file)
{
	return (int) swWriteINIFile( file, m_mpConfig );
}

bool CswConfig::GetValue(const UTEXT& utSection, const UTEXT& utName, UTEXT& utRef)
{
	if(m_mpConfig.IsSet(utSection))
	{
		CswUTPairs &sec = m_mpConfig[utSection];
		if(sec.IsSet(utName))
		{
			utRef = sec[utName];
			return true;
		}
	}
	return false;
}

bool CswConfig::SetValue(const UTEXT& utSection, const UTEXT& utName, const UTEXT& utRef)
{
	m_mpConfig[utSection][utName] = utRef;
	return true;
}

bool CswConfig::GetValue(const UTEXT& utSection, const UTEXT& utName, unsigned int& uRef)
{
	UTEXT utVal;
	if(GetValue(utSection, utName, utVal))
	{
		if(sscanf(utVal, "0x%X", &uRef) > 0)
			return true;
		else if(sscanf(utVal, "0x%x", &uRef) > 0)
			return true;
		else if(sscanf(utVal, "0%o", &uRef) > 0)
			return true;
		else if(sscanf(utVal, "%u", &uRef) > 0)
			return true;
	}
	return false;
}

bool CswConfig::SetValue(const UTEXT& utSection, const UTEXT& utName, const unsigned int& uRef, const UTEXT& utFormat)
{
	UTEXT utVal;
	utVal.Format(utFormat, uRef);
	m_mpConfig[utSection][utName] = utVal;
	return true;
}

bool CswConfig::GetValue(const UTEXT& utSection, const UTEXT& utName, bool& bRef)
{
	UTEXT utVal;
	if(GetValue(utSection, utName, utVal))
	{
		if(utVal.CaseInsensitiveCompare("True") ||
			utVal.CaseInsensitiveCompare("Yes") ||
			(utVal == UTEXT("1")))
		{
			bRef = true;
			return true;
		}
		else if(utVal.CaseInsensitiveCompare("False") ||
			utVal.CaseInsensitiveCompare("No") ||
			(utVal == UTEXT("0")))
		{
			bRef = false;
			return true;
		}
	}
	return false;
}

bool CswConfig::SetValue(const UTEXT& utSection, const UTEXT& utName, const bool& bRef)
{
	UTEXT utVal = bRef ? "True" : "False";
	m_mpConfig[utSection][utName] = utVal;
	return true;
}

bool CswConfig::GetValue(const UTEXT& utSection, const UTEXT& utName, CswUTArray& arRef)
{
	int i = 0;
	UTEXT utElem;
	while( GetValue(utSection, utName + UTEXT().Format("[%u]", i), utElem) )
	{
		arRef.Push(utElem);
		i++;
	}
	return true;
}

bool CswConfig::SetValue(const UTEXT& utSection, const UTEXT& utName, const CswUTArray& arRef)
{
	CswUTArray tokill;
	CswMap< UTEXT, UTEXT > &sec = m_mpConfig[utSection];
	UTEXT* puKey;
	for (UTEXT* puVal = sec.Reset (&puKey) ; puVal ; puVal = sec.Next (&puKey))
	{
		if((*puKey).Left(utName.GetLength() + 1) == (utName + "["))
			tokill.Push(*puKey);
	}
	
	while(tokill.Pop(*puKey))
		sec.UnSet(*puKey);

	UTEXT utSuffix;
	for( unsigned i = 0; i < arRef.Count(); i++ )
	{
		utSuffix.Format("[%u]", i);
		SetValue(utSection, utName + utSuffix, const_cast<CswUTArray&>(arRef)[i]);
	}
	return true;
}


