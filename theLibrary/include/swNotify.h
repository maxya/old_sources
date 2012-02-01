#pragma once

class CswNotifySource
{
protected:
	CswNotifySource () : m_bound (NULL), m_fBoundWnd (false) {}
public:
	void NotifyWindowAdvice (HWND hWnd, WORD wID) {m_bound = hWnd, m_fBoundWnd = true; m_wID = wID; }
	void NotifyThreadAdvice (DWORD dwThreadID, WORD wID) {m_bound = (HWND) dwThreadID, m_fBoundWnd = false; m_wID = wID; }
	void NotifyUnadvice () {m_bound = NULL, m_fBoundWnd = true; }
protected:
	void FireNotify (WORD wCode, LPARAM lParam = 0)
	{
		if (m_bound)
		{
			if (m_fBoundWnd)
				::PostMessage(m_bound, WM_COMMAND, MAKEWPARAM(m_wID, wCode), lParam);
			else
				::PostThreadMessage((DWORD)m_bound, WM_COMMAND, MAKEWPARAM(m_wID, wCode), lParam);
		}
	}
private:
	HWND m_bound;
	WORD m_wID;
	bool m_fBoundWnd;
};

