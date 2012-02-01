// SWStream.h: interface for the CSWStream class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWSTREAM_H__1F5D942E_E56F_45FF_BD96_B15EC43A1BCA__INCLUDED_)
#define AFX_SWSTREAM_H__1F5D942E_E56F_45FF_BD96_B15EC43A1BCA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Supported interfaces:
// ---------------------
// IUnknown
// ISequentialStream
// IStream

class CSWStream : public IStream
{
public:
	CSWStream();
	virtual ~CSWStream();
public:
	//////////////////////////////////////////////////////////////////////
	// IUnknown Methods
	//////////////////////////////////////////////////////////////////////

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
	
	//////////////////////////////////////////////////////////////////////
	// ISequentialStream Methods
	//////////////////////////////////////////////////////////////////////
	
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

	//////////////////////////////////////////////////////////////////////
	// IStream Methods
	//////////////////////////////////////////////////////////////////////
	
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
private:
	LONG m_cRefs;
};

#endif // !defined(AFX_SWSTREAM_H__1F5D942E_E56F_45FF_BD96_B15EC43A1BCA__INCLUDED_)
