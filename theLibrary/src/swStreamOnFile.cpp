// swStreamOnFile.cpp: implementation of the CswStreamOnFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "swStreamOnFile.h"
#include "UniversalText.h"

#define COPY_BUFFER_SIZE	4096 // size of memory used in CopyTo operation

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CswStreamOnFile::CswStreamOnFile(const CUniversalText& utName, HANDLE hFile, BOOL fCloseOnRelease) :
	m_utName (* new CUniversalText (utName))
{
	m_hFile = hFile;
	m_cRefs = 0;
	m_fCloseOnRelease = fCloseOnRelease;
	if (m_utName.IsEmpty ())
		m_utName.Format (L"FileHandle_%#.8x", (DWORD)m_hFile);
}

CswStreamOnFile::~CswStreamOnFile()
{
	if (m_fCloseOnRelease)
		CloseHandle (m_hFile);
	delete &m_utName;
}

HRESULT CswStreamOnFile::CreateInstance (/*[out]*/ IStream** ppStream, BSTR szName, 
								 DWORD dwDesiredAccess, 
								 DWORD dwShareMode, DWORD dwCreationDisposition, 
								 DWORD dwFlagsAndAttributes, BOOL fCloseOnRelease)
{
	CUniversalText utName = szName;
	HANDLE hFile = CreateFile (utName, dwDesiredAccess, dwShareMode, NULL, 
		dwCreationDisposition, dwFlagsAndAttributes, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;
	return CreateInstanceFromHandle (ppStream, hFile, fCloseOnRelease, utName);
}

HRESULT CswStreamOnFile::CreateInstanceFromHandle (/*[out]*/ IStream** ppStream,
	/*[in]*/ HANDLE hFile, BOOL fCloseOnRelease, const CUniversalText& utName)
{
	if (IsBadWritePtr (ppStream, sizeof (*ppStream)))
		return E_POINTER;
	(*ppStream) = new CswStreamOnFile (utName, hFile, fCloseOnRelease);
	if (!*ppStream)
		return E_OUTOFMEMORY;
	(*ppStream)->AddRef ();
	return S_OK;
}

HRESULT CswStreamOnFile::GetFileHandle (/*[in]*/ IStream* pStream, 
	/*[out]*/ HANDLE* phFile)
{
	if (IsBadWritePtr (phFile, sizeof(*phFile)))
		return E_POINTER;
	(*phFile) = reinterpret_cast<CswStreamOnFile*>(pStream)->m_hFile;
	return S_OK;	
}

//////////////////////////////////////////////////////////////////////
// IUnknown Methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::QueryInterface(REFIID iid, void ** ppvObject)
{
	if (iid == IID_IUnknown)
		*ppvObject = static_cast<IStream*>(this);
	else if (iid == IID_ISequentialStream)
		*ppvObject = static_cast<ISequentialStream*>(this);
	else if(iid == IID_IStream)
		*ppvObject = static_cast<IStream*>(this);
	else if(iid == IID_ILockBytes)
		*ppvObject = static_cast<ILockBytes*>(this);
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}
	AddRef ();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

ULONG CswStreamOnFile::AddRef(void)
{
	return InterlockedIncrement (&m_cRefs);
}

//////////////////////////////////////////////////////////////////////

ULONG CswStreamOnFile::Release(void)
{
	if (!InterlockedDecrement (&m_cRefs))
	{
		delete this;
		return 0;
	}
	return m_cRefs;
}

//////////////////////////////////////////////////////////////////////
// ISequentialStream Methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	if (!ReadFile (m_hFile, pv, cb, pcbRead, NULL))
		return S_FALSE;
	if (!*pcbRead && cb)
		return S_FALSE;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Write(void const *pv, ULONG cb, ULONG *pcbWritten)
{
	if (!WriteFile (m_hFile, pv, cb, pcbWritten, NULL))
		return STG_E_WRITEFAULT;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// IStream Methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, 
						ULARGE_INTEGER *plibNewPosition)
{
	plibNewPosition->LowPart = SetFilePointer (m_hFile, dlibMove.LowPart, 
									   &dlibMove.HighPart, dwOrigin);
	plibNewPosition->HighPart = dlibMove.HighPart;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::SetSize(ULARGE_INTEGER libNewSize)
{
	LARGE_INTEGER libNew;
	ULARGE_INTEGER ulibTemp;
	libNew.QuadPart = libNewSize.QuadPart;
	Seek (libNew, STREAM_SEEK_SET, &ulibTemp);
	SetEndOfFile (m_hFile);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::CopyTo(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, 
						  ULARGE_INTEGER *pcbWritten)
{
	LARGE_INTEGER libNew;
	ULARGE_INTEGER ulibTemp;
	HRESULT hr = S_FALSE;
	HANDLE hHeap = GetProcessHeap ();
	libNew.QuadPart = 0;
	Seek (libNew, STREAM_SEEK_SET, &ulibTemp);

	LPVOID pvCopyBuff = HeapAlloc (hHeap, 0, COPY_BUFFER_SIZE);
	if (!pvCopyBuff)
		return E_OUTOFMEMORY;

	ULONG uRead;
	ULONG uWritten;
	while (1)
	{
		if (S_OK != (hr = Read (pvCopyBuff, COPY_BUFFER_SIZE, &uRead)))
		{
			hr = S_OK;
			break;
		}
		if (S_OK != (hr = pstm->Write (pvCopyBuff, uRead, &uWritten)))
			break;
		if (uRead != uWritten)
			break;
	}
	HeapFree (hHeap, 0, pvCopyBuff);
	return hr;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Commit(DWORD grfCommitFlags)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Revert(void)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
							  DWORD dwLockType)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, 
								DWORD dwLockType)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
	ZeroMemory (pstatstg, sizeof (STATSTG));
	BY_HANDLE_FILE_INFORMATION info;
	GetFileInformationByHandle(m_hFile, &info);
	pstatstg->cbSize.LowPart = info.nFileSizeLow;
	pstatstg->cbSize.HighPart =	info.nFileSizeHigh;
	pstatstg->ctime = info.ftCreationTime;
	pstatstg->atime = info.ftLastAccessTime;
	pstatstg->mtime = info.ftLastWriteTime;
	pstatstg->type = STGTY_STREAM;
	if (!(STATFLAG_NONAME & grfStatFlag))
	{
		UINT uLen;
		pstatstg->pwcsName = (LPOLESTR) ::CoTaskMemAlloc (uLen = m_utName.GetSizeW ());
		if (pstatstg->pwcsName)
			CopyMemory (pstatstg->pwcsName, (LPWSTR) m_utName, uLen);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::Clone(IStream **ppstm)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////
// pure ILockBytes methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnFile::ReadAt(ULARGE_INTEGER ulOffset, void *pv, ULONG cb, ULONG *pcbRead)
{
	ULARGE_INTEGER ulNewOffset;
	LARGE_INTEGER lOffset;
	lOffset.QuadPart = ulOffset.QuadPart;
	if (FAILED(Seek (lOffset, SEEK_SET, &ulNewOffset)))
		return E_FAIL;
	return Read (pv, cb, pcbRead);
}

HRESULT CswStreamOnFile::WriteAt(ULARGE_INTEGER ulOffset, void const *pv, 
								 ULONG cb, ULONG *pcbWritten)
{
	ULARGE_INTEGER ulNewOffset;
	LARGE_INTEGER lOffset;
	lOffset.QuadPart = ulOffset.QuadPart;
	if (FAILED(Seek (lOffset, SEEK_SET, &ulNewOffset)))
		return E_FAIL;
	return Write (pv, cb, pcbWritten);
}

HRESULT CswStreamOnFile::Flush(void)
{
	return ::FlushFileBuffers (m_hFile) ? S_OK : S_FALSE;
}

