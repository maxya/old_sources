// SWImgFile.h: interface for the CSWImgFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWIMGFILE_H__F5751D79_FD4C_4846_B410_5D8D75AFDE1A__INCLUDED_)
#define AFX_SWIMGFILE_H__F5751D79_FD4C_4846_B410_5D8D75AFDE1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <stdio.h>

class CSWImgFile  
{
public:
	long	Tell();
	long	Size();
	long	Flush();
	long	Eof();
	long	Error();
	long	PutC(unsigned char c);
	long	GetC();
	long	GetPos(fpos_t *pos);
	void*	GetStream() const {return m_stream;}
	void*	Alloc(DWORD nBytes);
	void	Free();
	void	Transfer(CSWImgFile &from);

protected:
	void	*m_stream;	//file or memory pointer or whatever
	long	m_StorageType; //type (0=file, 1=memory, ...)
	long	m_Position;	//current position
	long	m_Size;		//file size
	long	m_Edge;		//buffer size
	long	m_DontCloseOnExit;
};

#endif // !defined(AFX_SWIMGFILE_H__F5751D79_FD4C_4846_B410_5D8D75AFDE1A__INCLUDED_)
