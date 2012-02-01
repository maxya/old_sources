// SWPtrArray.h: interface for the CSWPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWPTRARRAY_H__87372D7D_810B_4F91_AB29_FF54945741CB__INCLUDED_)
#define AFX_SWPTRARRAY_H__87372D7D_810B_4F91_AB29_FF54945741CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CswFile;
class CSWPtrArray  
{
public:
	CSWPtrArray();
	virtual ~CSWPtrArray();
	
	LONG Add (LPVOID pItem, LONG lInsertAt = -1);
	LPVOID Item (LONG lIndex);
	void Remove (LONG lIndex);
	LONG Count ();
	void Empty ();
	LPVOID operator [] (LONG lItem);
private:
	LONG InsertAt(long lItem, LPVOID ptr);
	CswFile& m_buff;
};

typedef CSWPtrArray SWPTRARRAY, *LPSWPTRARRAY;

#endif // !defined(AFX_SWPTRARRAY_H__87372D7D_810B_4F91_AB29_FF54945741CB__INCLUDED_)
