// swStreamOnFile.h: interface for the CswStreamOnFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWSTREAMONFILE_H__7A00773B_497B_4170_A591_484B75165820__INCLUDED_)
#define AFX_SWSTREAMONFILE_H__7A00773B_497B_4170_A591_484B75165820__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Supported interfaces:
// ---------------------
// IUnknown
// ISequentialStream
// IStream
// ILockBytes

// No aggregation supported.
#include "Macros.h"
#include "UniversalText.h"

class CswStreamOnFile  : public IStream, ILockBytes
{
public:
	CswStreamOnFile(const CUniversalText& utName, HANDLE hFile, BOOL fCloseOnRelease);
	virtual ~CswStreamOnFile();
	static HRESULT STDMETHODCALLTYPE CreateInstance (/*[out]*/ IStream** ppStream,
		BSTR szName,											// file name
		DWORD dwDesiredAccess = GENERIC_READ,					// access mode
		DWORD dwShareMode = FILE_SHARE_READ,					// share mode
		DWORD dwCreationDisposition = OPEN_EXISTING,			// how to create
		DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,		// file attributes
		BOOL fCloseOnRelease = TRUE			
		);
	static HRESULT STDMETHODCALLTYPE CreateInstanceFromHandle (/*[out]*/ IStream** ppStream,
		/*[in]*/ HANDLE hFile, BOOL fCloseOnRelease = TRUE, const CUniversalText& utName = NULLSTRING);
	
	static HRESULT STDMETHODCALLTYPE GetFileHandle (/*[in]*/ IStream* pStream, 
		/*[out]*/ HANDLE* phFile);
	
	// IUnknown Methods
public:

	//Returns pointers to supported interfaces.
	HRESULT STDMETHODCALLTYPE QueryInterface(
		REFIID iid,			//Identifier of the requested interface
		void ** ppvObject	//Address of output variable that receives the 
							//interface pointer requested in iid
	);
	//Increments the reference count
	ULONG STDMETHODCALLTYPE AddRef(void);
	//Decrements the reference count.
	ULONG STDMETHODCALLTYPE Release(void);
	
	// ISequentialStream Methods
public:	
	// Reads a specified number of bytes from the stream object into memory starting 
	// at the current seek pointer.
	HRESULT STDMETHODCALLTYPE Read(
		void *pv,		//Pointer to buffer into which the stream is read
		ULONG cb,		//Specifies the number of bytes to read
		ULONG *pcbRead  //Pointer to location that contains actual number of bytes read
	);
	
	// Writes a specified number of bytes into the stream object starting at the current 
	// seek pointer.
	HRESULT STDMETHODCALLTYPE Write(
		void const *pv,		//Pointer to the buffer address from which the stream is written
		ULONG cb,			//Specifies the number of bytes to write
		ULONG *pcbWritten	//Specifies the actual number of bytes written
	);
	
	// IStream Methods
public:	
	// Changes the seek pointer to a new location relative to the beginning of the stream,
	// the end of the stream, or the current seek pointer. 
	HRESULT STDMETHODCALLTYPE Seek(
	  LARGE_INTEGER dlibMove,          //Offset relative to dwOrigin
	  DWORD dwOrigin,                  //Specifies the origin for the offset
	  ULARGE_INTEGER *plibNewPosition  //Pointer to location containing
									   // new seek pointer
	);
	
	// Changes the size of the stream object. 
	HRESULT STDMETHODCALLTYPE SetSize(
	  ULARGE_INTEGER libNewSize  //Specifies the new size of the stream object
	);
	
	// Copies a specified number of bytes from the current seek pointer in the stream 
	// to the current seek pointer in another stream. 
	HRESULT STDMETHODCALLTYPE CopyTo(
	  IStream *pstm,               //Pointer to the destination stream
	  ULARGE_INTEGER cb,           //Specifies the number of bytes to copy
	  ULARGE_INTEGER *pcbRead,     //Pointer to the actual number of bytes 
								   // read from the source
	  ULARGE_INTEGER *pcbWritten   //Pointer to the actual number of 
								   // bytes written to the destination
	);
	
	// Ensures that any changes made to a stream object open in transacted mode are 
	// reflected in the parent storage object.
	HRESULT STDMETHODCALLTYPE Commit(
		DWORD grfCommitFlags  //Specifies how changes are committed
		);

	// Discards all changes that have been made to a transacted stream since the last 
	// call to IStream::Commit. 
	HRESULT STDMETHODCALLTYPE Revert(void);
	
	// Restricts access to a specified range of bytes in the stream. Supporting this 
	// functionality is optional since some file systems do not provide it. 
	HRESULT STDMETHODCALLTYPE LockRegion(
		ULARGE_INTEGER libOffset,	//Specifies the byte offset for
									// the beginning of the range
		ULARGE_INTEGER cb,			//Specifies the length of the range in bytes
		DWORD dwLockType			//Specifies the restriction on
									// accessing the specified range
	);
	
	// Removes the access restriction on a range of bytes previously restricted with 
	// Stream::LockRegion. 
	HRESULT STDMETHODCALLTYPE UnlockRegion(
	  ULARGE_INTEGER libOffset,  //Specifies the byte offset for
								 // the beginning of the range
	  ULARGE_INTEGER cb,         //Specifies the length of the range in bytes
	  DWORD dwLockType           //Specifies the access restriction
								 // previously placed on the range
	);

	// Retrieves the STATSTG structure for this stream. 
	HRESULT STDMETHODCALLTYPE Stat(
	  STATSTG *pstatstg,  //Location for STATSTG structure
	  DWORD grfStatFlag   //Values taken from the STATFLAG enumeration
	);
	
	// Creates a new stream object that references the same bytes as the original stream 
	// but provides a separate seek pointer to those bytes. 
	HRESULT STDMETHODCALLTYPE Clone(
		IStream **ppstm		//Pointer to location for pointer to the new stream object
	);

	// ILockBytes methods
public:
	// Reads a specified number of bytes starting at a specified offset from the beginning 
	// of the byte array
	HRESULT STDMETHODCALLTYPE ReadAt(
		ULARGE_INTEGER ulOffset, 	// Specifies the starting point for reading data
		void *pv,					// Pointer to the buffer into which the data is read
		ULONG cb,					// Specifies the number of bytes to read
		ULONG *pcbRead				// Pointer to location that contains actual number of bytes read
		);
	
	
	// Writes a specified number of bytes to a specified location in the byte array. 
	HRESULT STDMETHODCALLTYPE WriteAt(
		ULARGE_INTEGER ulOffset, 	// Specifies the starting point for writing data
		void const *pv,				// Pointer to the buffer containing the data to be written
		ULONG cb,					// Specifies the number of bytes to write
		ULONG *pcbWritten			// Pointer to location that contains actual number of bytes written
		);
	
	// Ensures that any internal buffers maintained by the byte array object are written out 
	// to the backing storage. 
	HRESULT STDMETHODCALLTYPE Flush(void);	
		
private:
	CUniversalText& m_utName;
	HANDLE m_hFile;
	BOOL m_fCloseOnRelease;
private:
	LONG m_cRefs;

};

//////////////////////////////////////////////////////////////////////

HRESULT __inline SWCreateStreamOnFile (/*[out]*/ IStream** ppStream,
	BSTR szName,											// file name
	DWORD dwDesiredAccess = GENERIC_READ,					// access mode
	DWORD dwShareMode = FILE_SHARE_READ,					// share mode
	DWORD dwCreationDisposition = OPEN_EXISTING,			// how to create
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,		// file attributes
	BOOL fCloseOnRelease = TRUE
	)
{
	return CswStreamOnFile::CreateInstance (ppStream, szName, dwDesiredAccess, dwShareMode, 
		dwCreationDisposition, dwFlagsAndAttributes, fCloseOnRelease);
}

HRESULT __inline SWCreateStreamOnFileFromHandle (/*[out]*/ IStream** ppStream, 
												 /*[in]*/ HANDLE hFile, BOOL fCloseOnRelease = TRUE)
{
	return CswStreamOnFile::CreateInstanceFromHandle (ppStream, hFile, fCloseOnRelease);
}

HRESULT __inline SWGetFileHandleFromIStream (/*[in]*/ IStream* pStream, 
	/*[out]*/ HANDLE* phFile)
{
	return CswStreamOnFile::GetFileHandle (pStream, phFile);
}

#endif // !defined(AFX_SWSTREAMONFILE_H__7A00773B_497B_4170_A591_484B75165820__INCLUDED_)
