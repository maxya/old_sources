// SWStorage.h: interface for the CSWStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWSTORAGE_H__1A3458A3_A57B_4571_B25C_D05BF565A183__INCLUDED_)
#define AFX_SWSTORAGE_H__1A3458A3_A57B_4571_B25C_D05BF565A183__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SWStream.h"

// Supported interfaces:
// ---------------------
// IUnknown
// IStorage

class CSWStorage : public IStorage
{
public:
	CSWStorage(HANDLE hFile, DWORD grfMode, DWORD stgfmt, STGOPTIONS * pStgOptions);
	CSWStorage(CSWStorage* pParent);
	virtual ~CSWStorage();

public:
	//////////////////////////////////////////////////////////////////////
	//IUnknown Methods
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
	// IStorage Methods
	//////////////////////////////////////////////////////////////////////
	
	//CreateStream 
	// Creates and opens a stream object with the specified name contained in this 
	// storage object. 
	HRESULT STDMETHODCALLTYPE CreateStream(
	  const WCHAR *pwcsName,   //Pointer to the name of the new stream
	  DWORD grfMode,           //Access mode for the new stream
	  DWORD reserved1,         //Reserved; must be zero
	  DWORD reserved2,         //Reserved; must be zero
	  IStream **ppstm          //Pointer to new stream object
	);

	//OpenStream 
	// Opens an existing stream object within this storage object using the specified 
	// access permissions in grfMode. 
	HRESULT STDMETHODCALLTYPE OpenStream(
	  const WCHAR *pwcsName,  //Pointer to name of stream to open
	  void *reserved1,        //Reserved; must be NULL
	  DWORD grfMode,          //Access mode for the new stream
	  DWORD reserved2,        //Reserved; must be zero
	  IStream **ppstm         //Pointer to output variable
							  // that receives the IStream interface pointer
	);

	//CreateStorage 
	// Creates and opens a new storage object within this storage object. 
	HRESULT STDMETHODCALLTYPE CreateStorage(
	  const WCHAR *pwcsName,   //Pointer to the name of the new storage object
	  DWORD grfMode,           //Access mode for the new storage object
	  DWORD reserved1,         //Reserved; must be zero
	  DWORD reserved2,         //Reserved; must be zero
	  IStorage **ppstg         //Pointer to new storage object
	);

	//OpenStorage 
	// Opens an existing storage object with the specified name according to the 
	// specified access mode. 
	HRESULT STDMETHODCALLTYPE OpenStorage(
	  const WCHAR *pwcsName,   //Pointer to the name of the
							   // storage object to open
	  IStorage *pstgPriority,  //Must be NULL.
	  DWORD grfMode,           //Access mode for the new storage object
	  SNB snbExclude,          //Must be NULL.
	  DWORD reserved,          //Reserved; must be zero
	  IStorage **ppstg         //Pointer to opened storage object
	);

	//CopyTo 
	// Copies the entire contents of this open storage object into another storage 
	// object. The layout of the destination storage object may differ. 
	HRESULT STDMETHODCALLTYPE CopyTo(
	  DWORD ciidExclude,         //Number of elements in rgiidExclude
	  IID const *rgiidExclude,   //Array of interface identifiers (IIDs)
	  SNB snbExclude,            //Pointer to a block of stream
								 // names in the storage object
	  IStorage *pstgDest         //Pointer to destination storage object
	);
	//MoveElementTo 
	// Copies or moves a substorage or stream from this storage object to another 
	// storage object. 
	HRESULT STDMETHODCALLTYPE MoveElementTo(
	  const WCHAR *pwcsName,   //Name of the element to be moved
	  IStorage *pstgDest,      //Pointer to destination storage object
	  const LPWSTR pwcsNewName,      //Pointer to new name of element in destination
	  DWORD grfFlags           //Specifies a copy or a move
	);

	//Commit 
	// Reflects changes for a transacted storage object to the parent level. 
	HRESULT STDMETHODCALLTYPE Commit(
	  DWORD grfCommitFlags  //Specifies how changes are to be committed
	);

	//Revert 
	// Discards all changes that have been made to the storage object since the last 
	// commit operation. 
	HRESULT STDMETHODCALLTYPE Revert(void);

	//EnumElements 
	// Returns an enumerator object that can be used to enumerate the storage and stream 
	// objects contained within this storage object. 
	HRESULT STDMETHODCALLTYPE EnumElements(
	  DWORD reserved1,        //Reserved; must be zero
	  void *reserved2,        //Reserved; must be NULL
	  DWORD reserved3,        //Reserved; must be zero
	  IEnumSTATSTG **ppenum   //Pointer to output variable that
							  // receives the IEnumSTATSTG interface pointer
	);

	//DestroyElement 
	// Removes the specified storage or stream from this storage object. 
	HRESULT STDMETHODCALLTYPE DestroyElement(
	  const WCHAR *pwcsName  //Pointer to the name of the element to be removed
	);

	//RenameElement 
	// Renames the specified storage or stream in this storage object. 
	HRESULT STDMETHODCALLTYPE RenameElement(
	  const WCHAR *pwcsOldName,  //Pointer to the name of the
								 // element to be changed
	  const WCHAR *pwcsNewName   //Pointer to the new name for
								 // the specified element
	);

	//SetElementTimes 
	// Sets the modification, access, and creation times of the indicated storage element, 
	// if supported by the underlying file system. 
	HRESULT STDMETHODCALLTYPE SetElementTimes(
	  const WCHAR *pwcsName,   //Pointer to name of element to be changed
	  FILETIME const *pctime,  //New creation time for element, or NULL
	  FILETIME const *patime,  //New access time for element, or NULL
	  FILETIME const *pmtime   //New modification time for element, or NULL
	);

	//SetClass 
	// Assigns the specified CLSID to this storage object. 
	HRESULT STDMETHODCALLTYPE SetClass(
	  REFCLSID clsid  //CLSID to be assigned to the storage object
	);

	//SetStateBits 
	// Stores up to 32 bits of state information in this storage object. 
	HRESULT STDMETHODCALLTYPE SetStateBits(
	  DWORD grfStateBits,  //Specifies new values of bits
	  DWORD grfMask        //Specifies mask that indicates which
						   // bits are significant
	);

	//Stat 
	// Returns the STATSTG structure for this open storage object. 
	HRESULT STDMETHODCALLTYPE Stat(
	  STATSTG *pstatstg,  //Location for STATSTG structure
	  DWORD grfStatFlag   //Values taken from the STATFLAG enumeration
	);	

private:
	LONG m_cRefs;
	
	HANDLE m_hFile;	
	CSWStorage* m_pParent;

	DWORD m_grfMode;
	DWORD m_stgfmt;
	STGOPTIONS m_StgOptions;


};

#endif // !defined(AFX_SWSTORAGE_H__1A3458A3_A57B_4571_B25C_D05BF565A183__INCLUDED_)
