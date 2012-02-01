#pragma once

#include "theLibrary.h"
#include "UniversalText.h"
#include "swMap.h"

typedef CswMap<CUniversalText, CUniversalText> CswUTPairs;
typedef CswMap<CUniversalText, CswUTPairs> CswNamedUTPairs;

bool swParseINIFile (CswFile& file, CswNamedUTPairs& arSections);
bool swWriteINIFile (CswFile& file, const CswNamedUTPairs& arSections);
