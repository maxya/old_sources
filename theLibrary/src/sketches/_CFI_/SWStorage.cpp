// SWStorage.cpp: implementation of the CSWStorage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SWStorage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSWStorage::CSWStorage(HANDLE hFile, DWORD grfMode, 
					   DWORD stgfmt, STGOPTIONS * pStgOptions)
{
	m_cRefs = NULL;
	m_pParent = NULL;
	m_hFile = hFile;
	m_grfMode = grfMode;
	memcpy (&m_StgOptions, pStgOptions, sizeof(STGOPTIONS));
}

CSWStorage::CSWStorage(CSWStorage* pParent)
{
	m_cRefs = NULL;
	m_pParent = pParent;
}


CSWStorage::~CSWStorage()
{
	if (!m_pParent)
		CloseHandle(m_hFile);
}

//////////////////////////////////////////////////////////////////////
//IUnknown Methods
//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::QueryInterface(REFIID iid, void ** ppvObject)
{
	if (iid == IID_IUnknown)
		*ppvObject = static_cast<IUnknown*>(this);
	else if(iid == IID_IStorage)
		*ppvObject = static_cast<IStorage*>(this);
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	AddRef ();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

ULONG CSWStorage::AddRef(void)
{
	return InterlockedIncrement (&m_cRefs);
}

//////////////////////////////////////////////////////////////////////

ULONG CSWStorage::Release(void)
{
	if (!InterlockedDecrement (&m_cRefs))
	{
		delete this;
		return 0;
	}
	return m_cRefs;
}

//////////////////////////////////////////////////////////////////////
// IStorage Methods
//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::CreateStream(const WCHAR *pwcsName, DWORD grfMode, 
					 DWORD reserved1, DWORD reserved2, IStream **ppstm)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::OpenStream(const WCHAR *pwcsName, void *reserved1, DWORD grfMode, 
				   DWORD reserved2, IStream **ppstm)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::CreateStorage(const WCHAR *pwcsName, DWORD grfMode, 
					  DWORD reserved1, DWORD reserved2, IStorage **ppstg)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::OpenStorage(const WCHAR *pwcsName, IStorage *pstgPriority, DWORD grfMode, 
					SNB snbExclude, DWORD reserved, IStorage **ppstg)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::CopyTo(DWORD ciidExclude, IID const *rgiidExclude, SNB snbExclude, 
			   IStorage *pstgDest)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::MoveElementTo(const WCHAR *pwcsName, IStorage *pstgDest, 
					  LPWSTR pwcsNewName, DWORD grfFlags)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::Commit(DWORD grfCommitFlags)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::Revert(void)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::EnumElements(DWORD reserved1, void *reserved2, DWORD reserved3,
					 IEnumSTATSTG **ppenum)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::DestroyElement(const WCHAR *pwcsName)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::RenameElement(const WCHAR *pwcsOldName, const WCHAR *pwcsNewName)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::SetElementTimes(const WCHAR *pwcsName, FILETIME const *pctime,
						FILETIME const *patime, FILETIME const *pmtime)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::SetClass(REFCLSID clsid)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::SetStateBits(DWORD grfStateBits, DWORD grfMask)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CSWStorage::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
	return E_NOTIMPL;
}
