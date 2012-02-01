// SeekWoodCFI.cpp: SeekWood Compound File Implementation.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SeekWoodCFI.h"

//////////////////////////////////////////////////////////////////////

STDAPI SWCreateStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen)
{
	if ((stgfmt != STGFMT_STORAGE) && (stgfmt != STGFMT_DOCFILE))
		return STG_E_INVALIDPARAMETER;

	if (!ppObjectOpen || IsBadWritePtr (ppObjectOpen, sizeof (ppObjectOpen)))
		return STG_E_INVALIDPOINTER;
	
	DWORD dwCreationDisposition = OPEN_EXISTING;
	DWORD dwDesiredAccess = 0;
	DWORD dwShareMode = 0;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;

	DWORD dwCurGroup;
	dwCurGroup = grfMode & 0x0000000FL; // Access
	switch (dwCurGroup)
	{
	case STGM_READ:
		dwDesiredAccess |= GENERIC_READ;
		break;
	case STGM_WRITE:
		dwDesiredAccess |= GENERIC_WRITE;
		break;
	case STGM_READWRITE:
		dwDesiredAccess |= GENERIC_READ | GENERIC_WRITE;
		break;
	default:
		return STG_E_INVALIDFLAG;
	}
	
	dwCurGroup = grfMode & 0x000000F0L; // Sharing
	switch (dwCurGroup)
	{
	case STGM_SHARE_DENY_NONE:
		dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
		break;
	case STGM_SHARE_DENY_READ:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case STGM_SHARE_DENY_WRITE:
		dwShareMode = FILE_SHARE_READ;
		break;
	case STGM_SHARE_EXCLUSIVE:
		dwShareMode = 0;
		break;
	default:
		return STG_E_INVALIDFLAG;
	}

	if (grfMode & STGM_PRIORITY)
		return E_NOTIMPL;
	
	if (grfMode & STGM_CREATE)
		dwCreationDisposition = CREATE_ALWAYS;

	if (grfMode & STGM_CONVERT)
		return E_NOTIMPL;

	if (grfMode & STGM_TRANSACTED)
		return E_NOTIMPL;

	if (grfMode & STGM_DELETEONRELEASE)
		dwFlagsAndAttributes |= FILE_FLAG_DELETE_ON_CLOSE;
	
	HANDLE hFile = CreateFileUT (const_cast <LPWSTR> (pwcsName), dwDesiredAccess,  dwShareMode, 
							   NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	CSWStorage* pStorage = new CSWStorage (hFile,grfMode, stgfmt, pStgOptions);

	if (!pStorage)
		return E_FAIL;

	
	if (SUCCEEDED(pStorage->QueryInterface (riid, ppObjectOpen)))
		return S_OK;

	pStorage->AddRef();
	pStorage->Release();

	return E_NOINTERFACE;
}

//////////////////////////////////////////////////////////////////////

STDAPI SWOpenStorageEx (IN const WCHAR* pwcsName,
            IN  DWORD grfMode,
            IN  DWORD stgfmt,              // enum
            IN  DWORD grfAttrs,             // reserved
            IN  STGOPTIONS * pStgOptions,
            IN  void * reserved,
            IN  REFIID riid,
            OUT void ** ppObjectOpen)
{
	return E_NOTIMPL;
}
