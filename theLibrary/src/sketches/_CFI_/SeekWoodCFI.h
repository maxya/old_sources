// SeekWoodCFI.h: interface for the SeekWood Compound File Implementation.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEEKWOODCFI_H__DFC36D86_55FE_412C_87B7_57FDD2160D04__INCLUDED_)
#define AFX_SEEKWOODCFI_H__DFC36D86_55FE_412C_87B7_57FDD2160D04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SWStorage.h"


//////////////////////////////////////////////////////////////////////

STDAPI SWCreateStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen);

//////////////////////////////////////////////////////////////////////

STDAPI SWOpenStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen);

//////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_SEEKWOODCFI_H__DFC36D86_55FE_412C_87B7_57FDD2160D04__INCLUDED_)
