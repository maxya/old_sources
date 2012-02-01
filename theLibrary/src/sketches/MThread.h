// MThread.h: interface for the CMThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MTHREAD_H__24C46CBC_E78A_4FEB_9DEA_A4EF7DE5BA26__INCLUDED_)
#define AFX_MTHREAD_H__24C46CBC_E78A_4FEB_9DEA_A4EF7DE5BA26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <thread.h>
//#include "MainDlg.h"

#define ID_FUNC_FIND	1
#define ID_FUNC_READ	2


class CSWThread : public CThreadImpl
{
public:


	DWORD Run()
	{
		return 0;
	};
	
	BOOL Start()
	{
		return CThreadImpl::Start();
	}
	
};



#endif // !defined(AFX_MTHREAD_H__24C46CBC_E78A_4FEB_9DEA_A4EF7DE5BA26__INCLUDED_)
