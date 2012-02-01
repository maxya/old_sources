#if !defined(AFX_THREAD_H__20000927_7992_09B2_A0EF_0080AD509054__INCLUDED_)
#define AFX_THREAD_H__20000927_7992_09B2_A0EF_0080AD509054__INCLUDED_

#pragma once

/////////////////////////////////////////////////////////////////////////////
// Thread - wrapper for Thread API
//
// Written by Bjarke Viksoe (bjarke@viksoe.dk)
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to you or your
// computer whatsoever. It's free, so don't hassle me about it.
//
// Beware of bugs.
//

#if defined(_MT) || defined(_DLL)
// Due to the nature of the multithreaded C runtime lib we
// need to use _beginthreadex() and _endthreadex() instead
// of CreateThread() and ExitThread(). See Q104641.
#include <process.h>
#endif


/////////////////////////////////////////////////////////////////////////////
// CThread

template<bool t_bManaged>
class CThreadT
{
public:
   HANDLE m_hThread;
   bool m_bSuspended;

   CThreadT() : m_hThread(NULL), m_bSuspended(false)
   {
   }
   virtual ~CThreadT()
   {
      if( t_bManaged ) Release();
   }
   BOOL Create(LPTHREAD_START_ROUTINE pThreadProc, 
               LPVOID pParam=NULL, 
               int iPriority=THREAD_PRIORITY_NORMAL)
   {
      _ASSERTE(m_hThread==NULL);
      _ASSERTE(pThreadProc);
      DWORD dwThreadID;
#if defined(_MT) || defined(_DLL)
      m_hThread = (HANDLE)_beginthreadex(NULL, 0, (UINT (WINAPI*)(void*))pThreadProc, pParam, 0, (UINT*)&dwThreadID);
#else
      m_hThread = ::CreateThread(NULL, 0, pThreadProc, pParam, 0, &dwThreadID);
#endif
      if( m_hThread==NULL ) return FALSE;
      if( iPriority!=THREAD_PRIORITY_NORMAL ) {
         if( !::SetThreadPriority(m_hThread, iPriority) ) {
            _ASSERTE(!"Couldn't set thread priority");
         }
      }
      return TRUE;
   }
   BOOL Release()
   {
      if( m_hThread==NULL ) return TRUE;
      if( ::CloseHandle(m_hThread)==FALSE ) return FALSE;
      m_hThread = NULL;
      return TRUE;
   }
   void Attach(HANDLE hThread)
   {
      _ASSERTE(m_hThread==NULL);
      m_hThread = hThread;
   }
   HANDLE Detach()
   {
      HANDLE hThread = m_hThread;
      m_hThread = NULL;
      return hThread;
   }
   BOOL SetPriority(int iPriority) const
   {
      _ASSERTE(m_hThread);
      return ::SetThreadPriority(m_hThread, iPriority);
   }
   int GetPriority() const
   {
      _ASSERTE(m_hThread);
      return ::GetThreadPriority(m_hThread);
   }
   BOOL Suspend()
   {
      _ASSERTE(m_hThread);
      if( m_bSuspended ) return TRUE;
      if( ::SuspendThread(m_hThread)==-1 ) return FALSE;
      m_bSuspended = true;
      return TRUE;
   }
   BOOL Resume()
   {
      _ASSERTE(m_hThread);
      if( !m_bSuspended ) return TRUE;
      if( ::ResumeThread(m_hThread)==-1 ) return FALSE;
      m_bSuspended = false;
      return TRUE;
   }
   BOOL IsSuspended() const
   {
      _ASSERTE(m_hThread);
      return m_bSuspended==true;
   }
   BOOL IsRunning() const
   {
      if( m_hThread==NULL ) return FALSE;
      DWORD dwCode = 0;
      GetExitCode(&dwCode);
      return dwCode==STILL_ACTIVE;
   }
   BOOL WaitForThread(DWORD dwTimeout=INFINITE) const
   {
      _ASSERTE(m_hThread);
      return ::WaitForSingleObject(m_hThread, dwTimeout);
   }
   BOOL Terminate(DWORD dwExitCode) const
   {
      // See Q254956 why calling this could be a bad idea!
      _ASSERTE(m_hThread);
      return ::TerminateThread(m_hThread, dwExitCode);
   }
   BOOL GetExitCode(DWORD* pExitCode) const
   {
      _ASSERTE(m_hThread);
      _ASSERTE(pExitCode);
      return ::GetExitCodeThread(m_hThread, pExitCode);
   }
#if(WINVER >= 0x0500)
   BOOL GetThreadTimes(LPFILETIME lpCreationTime, LPFILETIME lpExitTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime) const
   {
      _ASSERTE(m_hThread);
      _ASSERTE(lpExitTime!=NULL && lpKernelTime!=NULL && lpUserTime!=NULL);
      return ::GetThreadTimes(m_hThread, lpExitTime, lpKernelTime, lpUserTime);
   }
#endif
   operator HANDLE() const { return m_hThread; }
};

typedef CThreadT<false> CThreadHandle;
typedef CThreadT<true> CThread;


/////////////////////////////////////////////////////////////////////////////
// CThreadImpl

class CThreadImpl : public CThread
{
public:
   bool m_bStopped; // Signals when thread should stop (thread loop should exit)

   CThreadImpl() : m_bStopped(false)
   {
   }
   virtual ~CThreadImpl()
   {
      // NOTE: Remember destructors cannot call overrides!
      Stop();
   }
   virtual BOOL Start()
   {
      m_bStopped = false;
      if( !Create(ThreadProc, (LPVOID)this) ) return FALSE;
      return TRUE;
   }
   virtual void Stop()
   {
      if( SignalStop()==FALSE ) return;
      WaitForThread();
      Release();
   }
   BOOL SignalStop()
   {
      if( m_hThread==NULL ) return FALSE;
      m_bStopped = true;
      if( m_bSuspended ) Resume();
      return TRUE;
   }
   BOOL ShouldStop() const
   {
      _ASSERTE(m_hThread);
      return m_bStopped==true;
   }

   static DWORD WINAPI ThreadProc(LPVOID pData)
   {
      CThreadImpl* pThis = static_cast<CThreadImpl*>(pData);
#if defined(_MT) || defined(_DLL)
      _endthreadex( pThis->Run() );
      return 0;
#else
      return pThis->Run();
#endif
   }
   virtual DWORD Run()
   {
      _ASSERTE(false); // must override this
/*
      // Sample thread code...
      while( !ShouldStop() ) {
         ...
      }
*/
      return 0;
   }
};


#endif // !defined(AFX_THREAD_H__20000927_7992_09B2_A0EF_0080AD509054__INCLUDED_)

