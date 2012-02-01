#pragma once

#include "UniversalText.h"
#include "swMap.h"
#include "File.h"

#define FORMAT_HEX	"0x%X"
#define FORMAT_OCT	"0%o"

class CswConfig
{
protected:
	CswMap< UTEXT, CswMap< UTEXT, UTEXT > > m_mpConfig;

public:
	CswConfig(void);
	virtual ~CswConfig(void);

public:
	int Load(SWFILE& file);
	int Save(SWFILE& file);

	bool GetValue(const UTEXT& utSection, const UTEXT& utName, UTEXT& utRef);
	bool SetValue(const UTEXT& utSection, const UTEXT& utName, const UTEXT& utRef);
	bool GetValue(const UTEXT& utSection, const UTEXT& utName, unsigned int& uRef);
	bool SetValue(const UTEXT& utSection, const UTEXT& utName, const unsigned int& uRef, const UTEXT& utFormat);
	inline bool SetValue(const UTEXT& utSection, const UTEXT& utName, const unsigned int& uRef) 
	{
		return SetValue(utSection, utName, uRef, "%u");
	}
	
	bool GetValue(const UTEXT& utSection, const UTEXT& utName, bool& bRef);
	bool SetValue(const UTEXT& utSection, const UTEXT& utName, const bool& bRef);
	
	bool GetValue(const UTEXT& utSection, const UTEXT& utName, CswUTArray& arRef);
	bool SetValue(const UTEXT& utSection, const UTEXT& utName, const CswUTArray& arRef);
};

