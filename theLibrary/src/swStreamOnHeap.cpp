// swStreamOnHeap.cpp: implementation of the CswStreamOnHeap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UniversalText.h"
#include "swStreamOnHeap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CswStreamOnHeap::CswStreamOnHeap(HANDLE hHeap, LPVOID pvBuffer, DWORD dwRamPos, 
								 DWORD dwRamSize, BOOL fDeleteOnRelease)
{
	m_fDeleteOnRelease = fDeleteOnRelease;
	if (!pvBuffer)
	{
		if (!hHeap)
			m_hHeap = GetProcessHeap ();
		else
			m_hHeap = hHeap;
		m_dwRAMpos = 0;
		m_dwRAMsize = 0;
		m_pvRAMfile = HeapAlloc (m_hHeap, 0, 0);
	}
	else
	{
		m_hHeap = NULL;
		m_dwRAMpos = dwRamPos;
		m_dwRAMsize = dwRamSize;
		m_pvRAMfile = pvBuffer;
	}
	m_cRefs = 0;
}

CswStreamOnHeap::~CswStreamOnHeap()
{
	if (m_hHeap && m_fDeleteOnRelease && m_pvRAMfile)
		HeapFree (m_hHeap, 0, m_pvRAMfile);
}

HRESULT CswStreamOnHeap::CreateInstance (/*[out]*/ IStream** ppStream,
										 HANDLE hHeap, PVOID pvBuffer, BOOL fDeleteOnRelease, DWORD dwActualSize)
{
	if (IsBadWritePtr (ppStream, sizeof(*ppStream)))
		return E_POINTER;
	*ppStream = new CswStreamOnHeap (hHeap, pvBuffer, 0, dwActualSize, fDeleteOnRelease);
	if (!*ppStream)
		return E_OUTOFMEMORY;
	(*ppStream)->AddRef ();
	return S_OK;
}

HRESULT CswStreamOnHeap::GetBufferFromIStream (/*[in]*/ IStream* pStream, 
											   /*[out]*/ LPVOID* ppvMem)
{
	//	if (IsBadWritePtr (ppvMem, sizeof(*ppvMem)))
	//		return E_POINTER;
	(*ppvMem) = reinterpret_cast<CswStreamOnHeap*>(pStream)->m_pvRAMfile;
	return S_OK;	
}

HRESULT CswStreamOnHeap::GetHeapFromIStream (/*[in]*/ IStream* pStream, /*[out]*/ HANDLE* phHeap)
{
	//	if (IsBadWritePtr (phHeap, sizeof(*phHeap)))
	//		return E_POINTER;
	(*phHeap) = reinterpret_cast<CswStreamOnHeap*>(pStream)->m_hHeap;
	return S_OK;	
}
//////////////////////////////////////////////////////////////////////
// IUnknown Methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::QueryInterface(REFIID iid, void ** ppvObject)
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

ULONG CswStreamOnHeap::AddRef(void)
{
	return InterlockedIncrement (&m_cRefs);
}

//////////////////////////////////////////////////////////////////////

ULONG CswStreamOnHeap::Release(void)
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

HRESULT CswStreamOnHeap::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
	// Calculate maximum possible bytes to read
	STATSTG st;
	Stat (&st, STATFLAG_NONAME);

	DWORD dwMaximum = ((DWORD) st.cbSize.QuadPart) - m_dwRAMpos;
	if (cb > dwMaximum)
		cb = dwMaximum;
	if (!cb)
	{
		*pcbRead = cb;
		return S_FALSE;
	}

	memcpy (pv, static_cast<PBYTE>(m_pvRAMfile) + m_dwRAMpos, cb);
	m_dwRAMpos += cb;
	*pcbRead = cb;
	return S_OK;
}
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Write(void const *pv, ULONG cb, ULONG *pcbWritten)
{
	STATSTG st;
	Stat (&st, STATFLAG_NONAME);

	// Calculate needed extra memory and new size
	DWORD dwMaximumAvailable = (DWORD) st.cbSize.LowPart - m_dwRAMpos;
	if (cb > dwMaximumAvailable)
	{
		register DWORD dwExtraNeeded = cb - dwMaximumAvailable;
		m_dwRAMsize = (DWORD)st.cbSize.LowPart  + dwExtraNeeded;
		m_pvRAMfile = HeapReAlloc (m_hHeap, HEAP_GENERATE_EXCEPTIONS, m_pvRAMfile, m_dwRAMsize);
	}
	// Write to RAM-file
	memcpy (static_cast<PBYTE>(m_pvRAMfile) + m_dwRAMpos, pv, cb);
	m_dwRAMpos += cb;
	*pcbWritten = cb;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// IStream Methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, 
							  ULARGE_INTEGER *plibNewPosition)
{
	STATSTG stg;
	Stat (&stg, STATFLAG_NONAME);
	register LONG lNewPos;
	switch (dwOrigin)
	{
	case STREAM_SEEK_SET:
		//case FILE_BEGIN:
		lNewPos = dlibMove.LowPart;
		break;
	case STREAM_SEEK_END:
		//case FILE_END:
		lNewPos = stg.cbSize.LowPart + dlibMove.LowPart;
		break;
	case STREAM_SEEK_CUR:
		//case FILE_CURRENT:
		lNewPos = m_dwRAMpos + dlibMove.LowPart;
	}
	if (lNewPos < 0)
		lNewPos = 0;
	if (lNewPos > static_cast <INT>(stg.cbSize.LowPart))
		lNewPos = stg.cbSize.LowPart;
	plibNewPosition->QuadPart = (ULONGLONG)(m_dwRAMpos = lNewPos);
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::SetSize(ULARGE_INTEGER libNewSize)
{
	m_pvRAMfile = HeapReAlloc (m_hHeap, HEAP_GENERATE_EXCEPTIONS, m_pvRAMfile, 
		libNewSize.LowPart);
	if (!m_pvRAMfile)
		return E_UNEXPECTED;

	m_dwRAMsize = libNewSize.LowPart;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::CopyTo(IStream *pstm, ULARGE_INTEGER cb, ULARGE_INTEGER *pcbRead, 
								ULARGE_INTEGER *pcbWritten)
{
	ULONG uRead = 0;
	ULONG uWritten = 0;
	HRESULT hr = S_OK;

	DWORD dwMaximum = m_dwRAMsize - m_dwRAMpos;
	if (cb.LowPart > dwMaximum)
		cb.LowPart = dwMaximum;
	if (cb.LowPart)
	{
		uRead = cb.LowPart;
		pstm->Write (static_cast<PBYTE>(m_pvRAMfile) + m_dwRAMpos, uRead, &uWritten);
		m_dwRAMpos += cb.LowPart;
	}
	else
		hr = S_FALSE;

	pcbRead->QuadPart = (ULONGLONG) uRead;
	pcbWritten->QuadPart = (ULONGLONG) uWritten;

	return hr;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Commit(DWORD grfCommitFlags)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Revert(void)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb,
									DWORD dwLockType)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, 
									  DWORD dwLockType)
{
	return E_NOTIMPL;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
	ZeroMemory (pstatstg, sizeof (STATSTG));
	pstatstg->cbSize.LowPart = m_dwRAMsize;
	pstatstg->type = STGTY_STREAM;
	if (!(STATFLAG_NONAME & grfStatFlag))
	{
		/// make a name of our memory :)
		CUniversalText utText; UINT uLen;
		utText.Format (L"HeapMem_%#.8x", (DWORD) m_pvRAMfile);
		pstatstg->pwcsName = (LPOLESTR) ::CoTaskMemAlloc (uLen = utText.GetSizeW ());
		if (pstatstg->pwcsName)
			CopyMemory (pstatstg->pwcsName, (LPWSTR) utText, uLen);
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::Clone(IStream **ppStream)
{
	if (IsBadWritePtr (ppStream, sizeof(*ppStream)))
		return E_POINTER ;
	*ppStream = new CswStreamOnHeap (m_hHeap, m_pvRAMfile, m_dwRAMpos, m_dwRAMsize, FALSE);
	if (!*ppStream)
		return E_OUTOFMEMORY;
	(*ppStream)->AddRef ();
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// pure ILockBytes methods
//////////////////////////////////////////////////////////////////////

HRESULT CswStreamOnHeap::ReadAt(ULARGE_INTEGER ulOffset, void *pv, ULONG cb, ULONG *pcbRead)
{
	ULARGE_INTEGER ulNewOffset;
	LARGE_INTEGER lOffset;
	lOffset.QuadPart = ulOffset.QuadPart;
	if (FAILED(Seek (lOffset, SEEK_SET, &ulNewOffset)))
		return E_FAIL;
	return Read (pv, cb, pcbRead);
}

HRESULT CswStreamOnHeap::WriteAt(ULARGE_INTEGER ulOffset, void const *pv, 
								 ULONG cb, ULONG *pcbWritten)
{
	ULARGE_INTEGER ulNewOffset;
	LARGE_INTEGER lOffset;
	lOffset.QuadPart = ulOffset.QuadPart;
	if (FAILED(Seek (lOffset, SEEK_SET, &ulNewOffset)))
		return E_FAIL;
	return Write (pv, cb, pcbWritten);
}

HRESULT CswStreamOnHeap::Flush(void)
{
	return S_OK;
}

