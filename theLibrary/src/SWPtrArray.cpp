// SWPtrArray.cpp: implementation of the CSWPtrArray class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SWPtrArray.h"
#include "File.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSWPtrArray::CSWPtrArray() :
	m_buff ( * new CswFile ())
{
	m_buff.OpenRAM();
}

//////////////////////////////////////////////////////////////////////

CSWPtrArray::~CSWPtrArray()
{
	m_buff.Close();
	delete &m_buff;
}

//////////////////////////////////////////////////////////////////////
// Methods implementation
//////////////////////////////////////////////////////////////////////

LONG CSWPtrArray::Add (LPVOID pItem, LONG lInsertAt)
{
	if (lInsertAt < 0 || lInsertAt > static_cast <LONG>((m_buff.GetFileSize () >> 2) - 1))
	{
		m_buff.SeekEnd();
		long temp = (long)pItem;
		m_buff.Write(&temp,sizeof(temp));
		return (m_buff.GetFileSize () >> 2) - 1;
	}
	else
		return InsertAt (lInsertAt, pItem);
}

//////////////////////////////////////////////////////////////////////

LPVOID CSWPtrArray::Item (LONG lIndex)
{
	long pos = lIndex << 2;
	if (pos > static_cast<long>(m_buff.GetFileSize()))
		return NULL;
	m_buff.Seek(pos,FILE_BEGIN);
	long temp = 0;
	m_buff.Read(&temp,sizeof(temp));
	return (LPVOID)temp;
}

//////////////////////////////////////////////////////////////////////

long CSWPtrArray::Count()
{
	return (long)m_buff.GetFileSize() >> 2;
}

//////////////////////////////////////////////////////////////////////

void CSWPtrArray::Remove (LONG lIndex)
{
	if (lIndex >= Count())
		return;
	LPVOID tempDest;
	int buffsize = m_buff.GetFileSize();
	m_buff.ExtractBuffer(&tempDest);
	long pos = (int)tempDest;
	pos +=lIndex*4+4;
	LPVOID tempSrc = (LPVOID)pos;
	pos-=4;
	LPVOID newDest = (LPVOID)pos;
	int move = buffsize-(lIndex*4+4);
	memmove(newDest,tempSrc,move);
	m_buff.SetFileSize (buffsize-4);
	//m_buff.SetFileSize(buffsize-4);
	buffsize = m_buff.GetFileSize();
}

//////////////////////////////////////////////////////////////////////

void CSWPtrArray::Empty ()
{
	m_buff.Close();
	m_buff.OpenRAM();
}

//////////////////////////////////////////////////////////////////////

LONG CSWPtrArray::InsertAt(long lItem, LPVOID ptr)
{
	if (lItem > Count())
		return -1;
	long buffsize = m_buff.GetFileSize();
	LPVOID tempDest;
	m_buff.ExtractBuffer(&tempDest);
	//m_buff.SetFileSize(buffsize+4);
	long pos = (int)tempDest;
	pos +=lItem*4;
	LPVOID tempSrc = (LPVOID)pos;
	pos+=4;
	LPVOID newDest = (LPVOID)pos;
	int move = buffsize-(lItem*4);
	memmove(newDest,tempSrc,move);

	memcpy(tempSrc,&ptr,4);
	m_buff.SetFileSize(buffsize+4);
	return lItem;
}

//////////////////////////////////////////////////////////////////////

LPVOID CSWPtrArray::operator [] (LONG lItem)
{
	return Item (lItem);
}
