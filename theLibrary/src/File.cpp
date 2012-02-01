// File.cpp: implementation of the CswFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TheLibrary.h"
#include "swStreamOnHeap.h"
#include "swStreamOnFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CswFile::CswFile ()
{
	Init ();
}

CswFile::CswFile (CswFile& swFile)
{
	Init ();
	*this = swFile;
}

CswFile::CswFile (IStream* pStream)
{
	Init ();
	*this = pStream;
}

CswFile::~CswFile ()
{
	CleanUp ();
}

CswFile& CswFile::operator = (CswFile &swFile)
{
	AttachStream ((IStream*) swFile);
	return *this;
}

CswFile& CswFile::operator = (IStream* pStream)
{
	AttachStream (pStream);
	return *this;
}

void CswFile::Init ()
{
	m_pStream = NULL;
	m_fDeleteOnClose = TRUE;
	m_pUnkParent = NULL;
	//m_lUndoSeek = 0;
}

void CswFile::CleanUp ()
{
	ReleaseParent ();
	if (m_pStream)
	{
		m_pStream->Release ();
		Init ();
	}
}

//////////////////////////////////////////////////////////////////////
// Opening/closing
//////////////////////////////////////////////////////////////////////

BOOL CswFile::OpenHDD (CUniversalText utName, DWORD dwDesiredAcess, DWORD dwShareMode , 
				  DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes)
{
	if (SUCCEEDED(SWCreateStreamOnFile (&m_pStream, utName, dwDesiredAcess, dwShareMode, dwCreationDisposition,
		dwFlagsAndAttributes, m_fDeleteOnClose)))
		return TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::OpenHDDFromHandle (HANDLE hFile)
{
	if (SUCCEEDED(SWCreateStreamOnFileFromHandle (&m_pStream, hFile)))
		return TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::OpenRAM ()
{
	return OpenRAM (NULL, 0);
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::OpenRAM (LPVOID pvRAM, DWORD dwSize, BOOL /*fDuplicate*/)
{
	if (SUCCEEDED(SWCreateStreamOnHeap (&m_pStream, NULL, pvRAM, m_fDeleteOnClose, dwSize)))
		return TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::Close ()
{
	CleanUp();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

//BOOL CswFile::CloseAndDetach (OUT LPVOID* ppvDetachBuffer)
//{
//	return FALSE;
//}

//////////////////////////////////////////////////////////////////////
// Read/Write
//////////////////////////////////////////////////////////////////////

DWORD CswFile::Read (LPVOID pvBuffer, DWORD dwBytesToRead)
{
	ULONG uRead;
	HRESULT hr;
	if (((hr = m_pStream->Read (pvBuffer, dwBytesToRead, &uRead)) == S_OK) && (dwBytesToRead ? uRead : TRUE))
		return uRead;
	else
		return EOF;
}

//////////////////////////////////////////////////////////////////////

DWORD CswFile::Write (LPVOID pvBuffer, DWORD dwBytesToWrite)
{
	ULONG uWritten;
	HRESULT hr;
	if ((hr = m_pStream->Write (pvBuffer, dwBytesToWrite, &uWritten)) == S_OK)
		return uWritten;
	else
		return EOF;
}

//////////////////////////////////////////////////////////////////////
// Date
//////////////////////////////////////////////////////////////////////

time_t CswFile::GetCreationDate ()
{
	STATSTG st;
	m_pStream->Stat (&st, STATFLAG_NONAME);

	
	LONGLONG temp = 23;
	temp = st.ctime.dwHighDateTime;
	temp <<= 32;
	temp |= st.ctime.dwLowDateTime;

	temp -= 116444736000000000;
	temp /= 10000000;

	return (time_t)temp;
}

//////////////////////////////////////////////////////////////////////
// Seekxxxx, GetFileSize
//////////////////////////////////////////////////////////////////////

DWORD CswFile::Seek (LONG lDistanceToMove, DWORD dwMoveMethod)
{
	LARGE_INTEGER liVar;
	ULARGE_INTEGER liVar2;
	LISet32 (liVar, lDistanceToMove);
	m_pStream->Seek (liVar, dwMoveMethod, &liVar2);
	return liVar2.LowPart;
}

//////////////////////////////////////////////////////////////////////
// Seeking
//////////////////////////////////////////////////////////////////////

DWORD CswFile::SeekBegin ()
{
	return Seek (0, FILE_BEGIN);
}

//////////////////////////////////////////////////////////////////////

DWORD CswFile::SeekEnd ()
{
	return Seek (0, FILE_END);
}

//////////////////////////////////////////////////////////////////////

DWORD CswFile::GetSeekPos ()
{
	return Seek (0, FILE_CURRENT);
}

//////////////////////////////////////////////////////////////////////

DWORD CswFile::SeekTo (DWORD dwPos)
{
	return Seek (dwPos, FILE_BEGIN);
}

//////////////////////////////////////////////////////////////////////
// File size
//////////////////////////////////////////////////////////////////////

DWORD CswFile::GetFileSize ()
{
	STATSTG info;
	m_pStream->Stat (&info, STATFLAG_NONAME);
	return info.cbSize.LowPart;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::SetFileSize (DWORD dwSize)
{
	ULARGE_INTEGER uliSize;
	ULISet32 (uliSize, dwSize);
	if (SUCCEEDED(m_pStream->SetSize (uliSize)))
		return TRUE;
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Compression
//////////////////////////////////////////////////////////////////////

//BOOL CswFile::ToogleCompression (BOOL fOnOff)
//{
//	return FALSE;
//}

//////////////////////////////////////////////////////////////////////
// Interface attaching/retrieving
//////////////////////////////////////////////////////////////////////

BOOL CswFile::AttachStream (IN IStream* pStream)
{
	if (!pStream || IsBadReadPtr (pStream, sizeof(*pStream)))
		return FALSE;
	CleanUp ();
	m_pStream = pStream;
	m_pStream->AddRef ();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::DetachStream (OUT IStream** ppStream)
{
	if (m_pStream)
	{
		*ppStream = m_pStream;
		m_pStream->AddRef ();
		CleanUp();
		return TRUE;
	}
	return FALSE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::BindToParent (IN IUnknown* pUnkParent)
{
	ReleaseParent ();
	m_pUnkParent = pUnkParent;
	m_pUnkParent->AddRef();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::ReleaseParent ()
{
	if (m_pUnkParent)
		m_pUnkParent->Release();
	m_pUnkParent = NULL;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::ExtractBuffer(LPVOID* ppvMem)
{
	return SUCCEEDED(SWGetBufferFromIStream (m_pStream, ppvMem));
}

BOOL CswFile::ExtractFileHandle(HANDLE* phFile)
{
	return SUCCEEDED(SWGetFileHandleFromIStream(m_pStream, phFile));
}

BOOL CswFile::ToogleDeleteOnClose(BOOL fOn)
{
	return (m_fDeleteOnClose = fOn);
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::CopyTo(CswFile &fileTarget, DWORD dwBytes)
{
	ULARGE_INTEGER uliBytes, uliRead, uliWritten;
	uliBytes.QuadPart = (ULONGLONG) dwBytes;
	return (S_OK == m_pStream->CopyTo (fileTarget, uliBytes, &uliRead, &uliWritten));
}

//////////////////////////////////////////////////////////////////////

BOOL CswFile::Stat (STATSTG *pstatstg,	//Location for STATSTG structure
			DWORD grfStatFlag //Values taken from the STATFLAG enumeration
	)
{
	return SUCCEEDED(m_pStream->Stat (pstatstg, grfStatFlag));
}
