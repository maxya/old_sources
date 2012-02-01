#include "stdafx.h"
#include "swINIworks.h"

bool swParseINIFile (CswFile& file, CswNamedUTPairs& arSections)
{
	CswMap<CUniversalText, int> swLineComments;
	swLineComments["//"];
	swLineComments["#"];
	swLineComments[";;"];

	CUniversalText utLine, utSectionName, utFormatted, utLineNum;
	int nLine = 0;
	while (utLine.LoadAsLine (file, FALSE))
	{
		utLineNum.Format ("%u", nLine);
		if (swLineComments.IsSet (utLine.Left(1)) || swLineComments.IsSet (utLine.Left(2)))
			arSections["$lines"][utLineNum] = "p:" + utLine;
		else if (utLine.GetCHAR (0) == '[')
		{
			int nPos = utLine.Find ("]");
			if (nPos != -1) 
			{
				arSections[utSectionName = utLine.Mid (1, nPos - 1)];
				arSections["$lines"][utLineNum] = "s:" + utSectionName;
			}
			else
				arSections["$lines"][utLineNum] = "p:" + utLine;
		}
		else if (!utSectionName.IsEmpty ())
		{
			CswUTArray arParts;
			CUniversalText utKey;
			utLine.Explode ("=", arParts);
			if (arParts.Count () >= 2)
			{
				arParts.Shift (utKey);
				// TODO: Implement CUniversalText::Trim()
				//utKey.Trim ();
				
				arSections[utSectionName][utKey] += arParts.Implode ("=");				
				arSections["$lines"][utLineNum] = "v:" + utKey;
			}
			else
				arSections["$lines"][utLineNum] = "p:" + utLine;
		}
		else
			arSections["$lines"][utLineNum] = "p:" + utLine;
		nLine++;
	}
	return true;
}

bool swWriteINIFile (CswFile& file, const CswNamedUTPairs& arSections)
{
	CswNamedUTPairs arSectionsTmp = arSections;
	CswUTPairs arLines = arSectionsTmp["$lines"];
	arSectionsTmp.UnSet ("$lines");
	
	int nLineCount = arLines.Count ();
	CUniversalText utLineNum, utCurSection;
	CswUTPairs arCurSection;
	for (int nLine = 0; nLine < nLineCount; nLine++)
	{
		utLineNum.Format ("%u", nLine);
		CUniversalText utLineSpec = arLines[utLineNum];
		CUniversalText utLineType = utLineSpec.Left (2);
		utLineSpec.Delete (2);
		//utLineType.SaveAsPlain (file, EOF, FALSE);
		if (utLineType == CUniversalText("p:"))
			utLineSpec.SaveAsLine (file, FALSE);
		else if (utLineType == CUniversalText("s:"))
		{
			if (arCurSection.Count ())
			{
				// write new keys
				CUniversalText* putKey,* putVal;
				while (putVal = arCurSection.Reset (&putKey))
				{
					(*putKey + "=" + *putVal).SaveAsLine (file, FALSE);
					arCurSection.UnSet (*putKey);
				}
				CUniversalText().SaveAsLine (file, FALSE);
			}
			utCurSection = utLineSpec;
			arCurSection = arSectionsTmp[utCurSection];
			arSectionsTmp.UnSet (utCurSection);
			CUniversalText("[" + utLineSpec + "]").SaveAsLine (file, FALSE);
		}
		else if (utLineType == CUniversalText("v:"))
		{
			if(arCurSection.IsSet(utLineSpec))
			{
				(utLineSpec + "=" + arCurSection[utLineSpec]).SaveAsLine (file, FALSE);
				arCurSection.UnSet (utLineSpec);
			}
		}		
	}
	
	if (arCurSection.Count ())
	{
		// write left keys
		CUniversalText* putKey,* putVal;
		while (putVal = arCurSection.Reset (&putKey))
		{
			(*putKey + "=" + *putVal).SaveAsLine (file, FALSE);
			arCurSection.UnSet (*putKey);
		}
	}

	if (arSectionsTmp.Count ())
	{
		// write new sections
		CUniversalText().SaveAsLine (file, FALSE);
		CUniversalText* putSectionName; CswUTPairs* parPairs;
		while (parPairs = arSectionsTmp.Reset(&putSectionName))
		{
			CUniversalText("[" + *putSectionName + "]").SaveAsLine (file, FALSE);
			arCurSection = *parPairs;
			arSectionsTmp.UnSet (*putSectionName);
			if (arCurSection.Count ())
			{
				CUniversalText* putKey,* putVal;
				while (putVal = arCurSection.Reset (&putKey))
				{
					(*putKey + "=" + *putVal).SaveAsLine (file, FALSE);
					arCurSection.UnSet (*putKey);
				}
			}
		}
	}
	return true;
}