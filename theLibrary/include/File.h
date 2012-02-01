// File.h: interface for the CswFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined SW_FILE_H__0118C3A7_4658_4789_A703_3715FB544D00__INCLUDED_
#define SW_FILE_H__0118C3A7_4658_4789_A703_3715FB544D00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef EOF
#define EOF		-1
#endif

#include "UniversalText.h"
#include <objidl.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// CswFile
//////////////////////////////////////////////////////////////////////
class CUniversalText;
class CswFile
{
public:
	CswFile ();
	CswFile (CswFile& swFile);
	CswFile (IStream* pStream);
	virtual ~CswFile ();
	CswFile& operator = (CswFile &swFile);
	CswFile& operator = (IStream* pStream);

	// Open/create HDD file
	BOOL OpenHDD (CUniversalText utName/* = NULLSTRING*/, 
		DWORD dwDesiredAcess = GENERIC_READ | GENERIC_WRITE, 
		DWORD dwShareMode = 0, DWORD dwCreationDisposition = OPEN_ALWAYS,
		DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL);
	// Attach to opened HDD file
	BOOL OpenHDDFromHandle (HANDLE hFile);
	
	// Open RAM file
	//   fDuplicate no longer used. pvRam MUST be allocated throght HeapAlloc
	BOOL OpenRAM (LPVOID pvRAM, DWORD dwSize, /*no longer used*/ BOOL fDuplicate = FALSE);
	
	// Create RAM file
	BOOL OpenRAM ();
	
	// Close file
	BOOL Close ();
	
	// Copy file to another
	BOOL CopyTo (CswFile& fileTarget, DWORD dwBytes = EOF);

	operator IStream* ()	{ return m_pStream; }

	// * DEPRECATED * // Use Extract?? and ToogleDeleteOnClose members instead
	//BOOL CloseAndDetach (OUT LPVOID* ppvDetachBuffer);

	// Extracts file handle. 
	//   Internal stream *MUST* be an instance of CswStreamOnFile implementation
	BOOL ExtractFileHandle (HANDLE* phFile);
	// Extracts memory buffer. 
	//   Internal stream *MUST* be an instance of CswStreamOnHeap implementation
	BOOL ExtractBuffer (LPVOID* ppvMem);
	// Specifies either stream implementation close its media or no.
	// Call before openning.
	BOOL ToogleDeleteOnClose (BOOL fOn);

	// Read from file
	DWORD Read (LPVOID pvBuffer, DWORD dwBytesToRead);
	// Write to file
	DWORD Write (LPVOID pvBuffer, DWORD dwBytesToWrite);

	// Date (for compatibility. Use "Stat" instead)
	time_t GetCreationDate ();

	// Seek (any kind)
	DWORD Seek (LONG lDistanceToMove, DWORD dwMoveMethod);
	// Seek to begin
	DWORD SeekBegin ();
	// Seek to end
	DWORD SeekEnd ();
	// Get cur. offset
	DWORD GetSeekPos ();
	// Seek to offset
	DWORD SeekTo (DWORD dwPos);
	
	// Get file size (for compatibility. Use "Stat" instead)
	DWORD GetFileSize ();
	// Set file size (RAM files only)
	BOOL SetFileSize (DWORD dwSize);

	// Retrieves the STATSTG structure for this stream
	BOOL Stat (STATSTG *pstatstg, DWORD grfStatFlag = STATFLAG_DEFAULT);


	// * DEPRECATED * //
	// Compression. Call before openning for HDD file and at any time for RAM-file.
	// * ONLY WITH SW-STREAM IMPLEMENTATIONS * //
	// BOOL ToogleCompression (BOOL fOnOff); 


	//////////////////////////////////////////////////////////////////////
	// New functions. Interface attaching/retrieving
	//////////////////////////////////////////////////////////////////////

	// Use specified stream instance. This is similar to openning file.
	BOOL AttachStream (IN IStream* pStream);
	// Put internal stream instance to outer variable. This is similar to closing file.
	BOOL DetachStream (OUT IStream** ppStream);
	// Bind to parent
	BOOL BindToParent (IN IUnknown* pUnkParent);
	// Forced unbind from parent
	BOOL ReleaseParent ();

//////////////////////////////////////////////////////////////////////


protected:
	void Init ();
	void CleanUp ();

private:
	IStream* m_pStream;
	IUnknown* m_pUnkParent;
	BOOL m_fDeleteOnClose;
	//LONG m_lUndoSeek;
	/*struct CSWFILESTREAM_FD6CC328_F77C_4049_92AF_7F6CA4D223D7
	{
		unsigned fRAMfile		: 1;
	} m_bfFlags;*/
};

typedef CswFile CSWFile, SWFILE, *LPSWFILE;


#endif //!defined SW_FILE_H__0118C3A7_4658_4789_A703_3715FB544D00__INCLUDED_
